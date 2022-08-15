/*
 * File:    mlog.c
 * Author:  Interark Corp.
 * Summary: Measure log implementation file.
 * Date:    2022/07/15 (R0)
 *          2022/07/17 (R1) Support temporary SRAM log
 * Note:
 *          Use 2KB of SRAM
 */

// build configuration
//#define DEBUG_LCD           // Debug with i2c lcd
#define DEBUG_USB           // Debug with USB

#include <string.h>
#include <stdio.h>
#include "w25q128jv.h"
#include "mlog.h"
#include "debug.h"

/*
*   Macros
*/
#define IS_NOT_USED(ts)         ((ts) == ~0)        // timestamp "ts" is not used

/*
*   Local(static) variables
*/
static uint32_t    _MLOG_headAddress    = 0;        // address of head log (point next address)
static uint32_t    _MLOG_tailAddress    = 0;        // address of tail log for upload
static uint32_t    _MLOG_tailAddress2   = 0;        // address of tail log for USB IF
static uint32_t    _MLOG_oldestAddress  = 0;        // oldest log address in chip (always 0x***000)
static bool        _MLOG_switchToSRAM   = false;    // is the storage destination SRAM ?
static uint8_t     _MLOG_storages[MLOG_SRAM_SIZE];  // log buffer on SRAM (not ring buffer)
static uint32_t    _MLOG_headAddressSRAM= 0;        // address of head log (point next address) on SRAM
static uint32_t    _MLOG_tailAddressSRAM= 0;        // address of tail log for upload on SRAM

static void dumpLog(char const *prefix, int n, MLOG_ID_T mlogID, MLOG_T *log_p);

int MLOG_begin(bool checkLogs)
{
    // Check IDs
    uint8_t manufactureID, deviceID;
    if (W25Q128JV_readManufactureDeviceID(&manufactureID, &deviceID) != W25Q128JV_ERR_NONE)
    {
        return (MLOG_ERR_READ_ID);
    }
    if (manufactureID != W25Q128JV_MANUFACTURE_ID || deviceID != W25Q128JV_DEVICE_ID)
    {
        return (MLOG_ERR_BAD_ID);
    }

    // Set up SRAM buffer
    _MLOG_headAddressSRAM = _MLOG_tailAddressSRAM = (uint32_t)_MLOG_storages;

    // Check all logs
    if (checkLogs)
    {
        return (MLOG_checkLogs());
    }

    return (MLOG_ERR_NONE);
}

int MLOG_putLog(MLOG_T *log_p)
{
    DEBUG_USB_printString(">MLOG_putLog()");
    DEBUG_USB_printFormat("_MLOG_headAddress=%06x", (unsigned int)_MLOG_headAddress);
    if ((_MLOG_headAddress & 0xfff) == 0)
    {
        // if page number and offset are zero - first log in current sector
        DEBUG_USB_printFormat("head=%06x", (unsigned int)_MLOG_headAddress);
        uint16_t sectorNo = (_MLOG_headAddress >> 12) & 0x0fff;
        DEBUG_USB_printFormat("eraseSector(%04x)", (unsigned int)sectorNo);
        if (W25Q128JV_eraseSctor(sectorNo, true) != W25Q128JV_ERR_NONE)
        {
            return (MLOG_ERR_ERASE);
        }
        DEBUG_USB_printFormat("eraseSector(%04x): done", (unsigned int)sectorNo);
    }
    uint16_t pageNo = _MLOG_headAddress >> 8;
    uint8_t offset = _MLOG_headAddress & 0xff;
    DEBUG_USB_printFormat("programPage(%04x,%02x):", (unsigned int)pageNo, (unsigned int)offset);
    if (W25Q128JV_programPage(pageNo, offset, (uint8_t *)log_p, MLOG_RECORD_SIZE, true) != W25Q128JV_ERR_NONE)
    {
        return (MLOG_ERR_PROGRAM_PAGE);
    }
    MLOG_ID_T mlogID = (pageNo << 8) + offset;
    dumpLog(">", 1, mlogID, log_p);
    DEBUG_USB_printString("done");

    // update _MLOG_headAddress for next use
    if (offset < MLOG_RECORD_SIZE * (MLOG_LOGS_PER_PAGE - 1))
    {
        offset += MLOG_RECORD_SIZE;
    }
    else
    {
        offset = 0;
        if (++pageNo > (MLOG_ADDRESS_MLOG_LAST >> 8))
        {
            pageNo = 0;     // back to top
        }
    }
    _MLOG_headAddress = ((uint32_t)pageNo << 8) + offset;
    DEBUG_USB_printFormat("_MLOG_headAddress=%06x", (unsigned int)_MLOG_headAddress);

    DEBUG_USB_printString("<MLOG_putLog()");
    return (MLOG_ERR_NONE);
}

int MLOG_getLog(MLOG_T *log_p)
{
    if (_MLOG_headAddress == _MLOG_tailAddress)
    {
        return (MLOG_ERR_EMPTY);
    }

    if (W25Q128JV_readData(_MLOG_tailAddress, (uint8_t *)log_p, MLOG_RECORD_SIZE) != W25Q128JV_ERR_NONE)
    {
        return (MLOG_ERR_READ);
    }
    MLOG_ID_T mlogID = _MLOG_tailAddress;
    dumpLog("<", 2, mlogID, log_p);

    // update _MLOG_tailAddress for next use
    uint16_t pageNo = _MLOG_tailAddress >> 8;
    uint8_t offset = _MLOG_tailAddress & 0xff;
    if (offset < MLOG_RECORD_SIZE * (MLOG_LOGS_PER_PAGE - 1))
    {
        offset += MLOG_RECORD_SIZE;
    }
    else
    {
        // mark as uploaded
        offset = W25Q128JV_PAGE_SIZE - 1;   // uploaded flag at last offset in the page
        uint8_t flag = 0x00;
        if (W25Q128JV_programPage(pageNo, offset, (uint8_t *)&flag, 1, true) != W25Q128JV_ERR_NONE)
        {
            return (MLOG_ERR_PROGRAM_PAGE);
        }
        DEBUG_USB_printFormat("Mark as uploaded(%04x:%02x)", (unsigned int)pageNo, (unsigned int)offset);

        // turn the page
        offset = 0;
        if (++pageNo > (MLOG_ADDRESS_MLOG_LAST >> 8))
        {
            pageNo = 0;     // back to top
        }
    }
    _MLOG_tailAddress = ((uint32_t)pageNo << 8) + offset;

    return (MLOG_ERR_NONE);
}

uint32_t MLOG_countUploadableLog(void)
{
    uint32_t headAddress = _MLOG_headAddress;
    if (headAddress == _MLOG_tailAddress)
    {
        return (0);     // empty
    }
    else if (headAddress < _MLOG_tailAddress)
    {
        headAddress += MLOG_ADDRESS_MLOG_LAST + 1;
    }

    uint16_t headPageNo = headAddress >> 8;
    uint16_t tailPageNo = _MLOG_tailAddress >> 8;
    uint8_t headFraction = (headAddress & 0xff) / MLOG_RECORD_SIZE;
    uint8_t tailFraction = (_MLOG_tailAddress & 0xff) / MLOG_RECORD_SIZE;
    uint32_t count = ((headPageNo - tailPageNo) * MLOG_LOGS_PER_PAGE) + (headFraction - tailFraction);

    return (count);
}

void MLOG_syncTail(void)
{
    _MLOG_tailAddress2 = _MLOG_tailAddress;
}

int MLOG_getLog2(MLOG_T *log_p)
{
    if (_MLOG_headAddress == _MLOG_tailAddress2)
    {
        return (MLOG_ERR_EMPTY);
    }

    if (W25Q128JV_readData(_MLOG_tailAddress2, (uint8_t *)log_p, MLOG_RECORD_SIZE) != W25Q128JV_ERR_NONE)
    {
        return (MLOG_ERR_READ);
    }

    // update _MLOG_tailAddress2 for next use
    uint16_t pageNo = _MLOG_tailAddress2 >> 8;
    uint8_t offset = _MLOG_tailAddress2 & 0xff;
    if (offset < MLOG_RECORD_SIZE * (MLOG_LOGS_PER_PAGE - 1))
    {
        offset += MLOG_RECORD_SIZE;
    }
    else
    {
        // turn the page
        offset = 0;
        if (++pageNo > (MLOG_ADDRESS_MLOG_LAST >> 8))
        {
            pageNo = 0;     // back to top
        }
    }
    _MLOG_tailAddress2 = ((uint32_t)pageNo << 8) + offset;

    return (MLOG_ERR_NONE);
}

int MLOG_format(void)
{
    DEBUG_LCD_printString(1, "FMT..");
    DEBUG_USB_printFormat(">MLOG_format()");

    // erase mlog data region in chip
    for (uint8_t blockNo = (MLOG_ADDRESS_MLOG_TOP >> 16); blockNo <= (MLOG_ADDRESS_MLOG_LAST >> 16) ; blockNo++) {
        DEBUG_LCD_printFormat(2, "BLK# %02x", (unsigned int)blockNo);
        DEBUG_USB_printFormat("eraseBlock64(%02x)", (unsigned int)blockNo);
        if (W25Q128JV_eraseBlock64(blockNo, true) != W25Q128JV_ERR_NONE)
        {
            return (MLOG_ERR_ERASE);
        }
    }

    DEBUG_LCD_printString(1, "..DONE");
    DEBUG_USB_printString("<MLOG_format()");
    return (MLOG_ERR_NONE);
}

int MLOG_checkLogs(void)
{
    DEBUG_USB_printString(">MLOG_checkLogs()");

    uint32_t latestTS = 0, oldestTS = 0, latestTS2 = 0;
    uint32_t latestAddr = 0, oldestAddr = 0, latestAddr2 = 0;
    for (uint32_t blockNo = 0; blockNo < W25Q128JV_NUM_BLOCK64; blockNo++)
    {
        for (uint32_t sectorNo = 0; sectorNo < W25Q128JV_NUM_SECTOR; sectorNo++)
        {
            for (uint32_t pageNo = 0; pageNo < W25Q128JV_NUM_PAGE; pageNo++)
            {
                uint32_t addr = (blockNo << 16) + (sectorNo << 12) + (pageNo << 8);
                // find head (find the most recent page)
                uint32_t ts;
                uint8_t buf[4];
                if (W25Q128JV_readData(addr, buf, (uint16_t)sizeof(buf)) != W25Q128JV_ERR_NONE)
                {
                    return (MLOG_ERR_READ);
                }
//                ts = (uint32_t)buf;     //@ endian Okey?
                memcpy((void *)&ts, (void *)buf, sizeof(ts));
                if (IS_NOT_USED(ts))
                {
                    continue;       // skip not used page
                }
                if (ts < oldestTS)
                {
                    oldestTS = ts;
                    oldestAddr = addr;
                }
                else if (latestTS < ts)
                {
                    latestTS = ts;
                    latestAddr = addr;
                }
                // find tail (find the most recent not-uploaded page)
                uint8_t flag;   // 0xff: not used or not uploaded/0x00: uploaded this page
                if (W25Q128JV_readData(addr + (W25Q128JV_PAGE_SIZE-1), &flag, 1) != W25Q128JV_ERR_NONE)
                {
                    return (MLOG_ERR_READ);
                }
                if (flag == 0x00)
                {
                    // when this page is not uploaded
                    if (latestTS2 < ts)
                    {
                        latestTS2 = ts;
                        latestAddr2 = addr;
                    }
                }
            }
        }
        DEBUG_USB_printFormat("blockNo=%02x", (unsigned int)blockNo);
    }
    DEBUG_USB_printFormat("oldestTS=%06x,oldestAddr=%06x", (unsigned int)oldestTS, (unsigned int)oldestAddr);
    DEBUG_USB_printFormat("latestTS=%06x,latestAddr=%06x", (unsigned int)latestTS, (unsigned int)latestAddr);
    DEBUG_USB_printFormat("latestTS2=%06x,latestAddr2=%06x", (unsigned int)latestTS2, (unsigned int)latestAddr2);

    // set oldest page
    _MLOG_oldestAddress = oldestAddr;

    // set tail pointer
    if (latestAddr2 == latestAddr)
    {
        _MLOG_tailAddress = latestAddr2;
    }
    else
    {
        latestAddr2 += W25Q128JV_PAGE_SIZE;
        if (latestAddr2 >= (MLOG_ADDRESS_MLOG_LAST & 0xffff00))
        {
            latestAddr2 = 0;
        }
        _MLOG_tailAddress = latestAddr2;
    }
    DEBUG_USB_printFormat("_MLOG_oldestAddress=%06x", (unsigned int)_MLOG_oldestAddress);
    DEBUG_USB_printFormat("_MLOG_tailAddress=%06x", (unsigned int)_MLOG_tailAddress);

    // set head pointer
    bool found = false;
    for (uint32_t addr = latestAddr; addr < latestAddr + (MLOG_RECORD_SIZE * MLOG_LOGS_PER_PAGE); addr += MLOG_RECORD_SIZE)
    {
        uint32_t ts;
        uint8_t buf[4];
        if (W25Q128JV_readData(addr, buf, (uint16_t)sizeof(buf)) != W25Q128JV_ERR_NONE)
        {
            return (MLOG_ERR_READ);
        }
        //ts = (uint32_t)buf;     //@ endian Okey?
        memcpy((void *)&ts, (void *)buf, sizeof(ts));
        if (IS_NOT_USED(ts))
        {
            _MLOG_headAddress = addr;   // latest is previous record
            found = true;
            DEBUG_USB_printFormat("FOUND head: addr=%06x", (unsigned int)addr);
            break;      // exit from for-loop
        }
    }
    if (! found)
    {
        // latest is last record in this page
        _MLOG_headAddress = latestAddr + (MLOG_RECORD_SIZE * (MLOG_LOGS_PER_PAGE - 1));
    }
    DEBUG_USB_printFormat("_MLOG_headAddress=%06x,%d", (unsigned int)_MLOG_headAddress, (int)found);

    DEBUG_USB_printString("<MLOG_checkLogs()");
    return (MLOG_ERR_NONE);
}

int MLOG_switchToSRAM(void)
{
    _MLOG_switchToSRAM = true;

    return (MLOG_ERR_NONE);
}

int MLOG_returnToFlash(void)
{
    // log data on SRAM write to Flash

    _MLOG_switchToSRAM = false;

    return (MLOG_ERR_NONE);
}

/*
*   Local functions
*/
static void dumpLog(char const *prefix, int n, MLOG_ID_T mlogID, MLOG_T *log_p)
{
    char line[200];

    DEBUG_LCD_printFormat(n, "%s%06Xh", prefix, (unsigned int)mlogID);

    snprintf(line, sizeof(line),
        "%s%06x: %06u.%03u,%.3f/%.3f,%u/%u,%02Xh/%02Xh,%d,%04Xh",
        prefix,
        (unsigned int)mlogID,
        (unsigned int)log_p->timestamp.second, (unsigned int)log_p->timestamp.mSecond,
        log_p->measuredValues[0], log_p->measuredValues[1],
        (unsigned int)log_p->batteryVoltages[0], (unsigned int)log_p->batteryVoltages[1],
        (unsigned int)log_p->alartStatuses[0], (unsigned int)log_p->alartStatuses[1],
        (int)log_p->temperatureOnBoard,
        (unsigned int)log_p->batteryStatus);
    APP_printlnUSB(line);  APP_delay(3);
}
