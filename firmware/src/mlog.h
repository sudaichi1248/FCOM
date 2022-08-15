/*
 * File:    mlog.h
 * Author:  Interark Corp.
 * Summary: Measure log header file.
 * Date:    2022/06/25 (R0)
 *          2022/07/17 (R1) Support temporary SRAM log
 * Note:
 *          Use 2KB of SRAM
 */

#ifndef MLOG_H
#define	MLOG_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "definitions.h"

/*
*   Constants
*/
#define MLOG_LOGS_PER_PAGE              10      // Number of logs per page
#define MLOG_RECORD_SIZE                24      // Record size (bytes)
#define MLOG_MAX_RECORDS                (MLOG_LOGS_PER_PAGE * (((MLOG_ADDRESS_MLOG_LAST - MLOG_ADDRESS_MLOG_TOP) >> 8) + 1))

/*
*   Flash memory address
*/
  // (1) Mlog region (12MB)
#define MLOG_ADDRESS_MLOG_TOP           0x000000    // Mlog region top
//#define MLOG_ADDRESS_MLOG_LAST          0xBFFFFF    // Mlog region last
#define MLOG_ADDRESS_MLOG_LAST          0x000FFF    // Mlog region last
  // (2) Reserved region (4MB)
#define MLOG_ADDRESS_RESERVED_TOP       0xC00000    // Reserved region top
#define MLOG_ADDRESS_RESERVED_LAST      0xFFFFFF    // Reserved region last
  // (3) SRAM
#define MLOG_SRAM_SIZE                  2048        //

// Error codes
#define MLOG_ERR_NONE                   0           // Success(no error)
#define MLOG_ERR_PARAM                  (-1)        // bad parameter(s)
#define MLOG_ERR_EMPTY                  (-3)        // buffer empty
#define MLOG_ERR_READ                   (-4)        // error on read operation
#define MLOG_ERR_READ_ID                (-10)       // error on read ID
#define MLOG_ERR_BAD_ID                 (-11)       // Serial Flash chip's ID is invalid
#define MLOG_ERR_ERASE                  (-20)       // error on erase operation
#define MLOG_ERR_PROGRAM_PAGE           (-21)       // error on program page operation
#define MLOG_ERR_FORMAT                 (-30)       // error on format
#define MLOG_ERR_OVERFLOW               (-40)       // SRAM buffer overflow

/*
*   Types
*/
typedef uint32_t    MLOG_ID_T;              // Mlog ID(24-bit) = (page address(16-bit) << 8) + log offset(8-bit)

typedef struct
{
    uint32_t        second;                 // epoch time JST [sec]
    uint16_t        mSecond;                // millisecond [msec]
} MLOG_TIMESTAMP;

typedef struct
{
    MLOG_TIMESTAMP  timestamp;
    float           measuredValues[2];      // measured values - index 0: CH1/1: CH2 [MhPa..]
    uint16_t        batteryVoltages[2];     // external battery voltage - index 0: External#1/1: External#2 [mV]
    uint8_t         alartStatuses[2];       // alart status - index 0: CH1/1: CH2
    int16_t         temperatureOnBoard;     // x10 [C]
    uint16_t        batteryStatus;          // Battery status
} MLOG_T;

// alart status
#define MLOG_ALART_STATUS_NORMAL            0         // Normal status
#define MLOG_ALART_STATUS_UPPER_EMERGENCY   0x08      // Emergency status(upper-side)
#define MLOG_ALART_STATUS_UPPER_WARING      0x04      // Warning status(upper-side)
#define MLOG_ALART_STATUS_LOWER_WARING      0x02      // Warning status(lower-side)
#define MLOG_ALART_STATUS_LOWER_EMERGENCY   0x01      // Emergency status(lower-side)

// Battery status
#define MLOG_BAT_STATUS_BAT1_NOT_USE        0x00    // Battery #1 not used
#define MLOG_BAT_STATUS_BAT1_IN_USE         0x01    // Battery #1 in used
#define MLOG_BAT_STATUS_BAT1_LOW_VOLTAGE    0x0f    // Battery #1 low voltage
#define MLOG_BAT_STATUS_BAT2_NOT_USE        0x00    // Battery #2 not used
#define MLOG_BAT_STATUS_BAT2_IN_USE         0x10    // Battery #2 not used
#define MLOG_BAT_STATUS_BAT2_LOW_VOLTAGE    0xf0    // Battery #2 low voltage

/*
*   Functions
*/
  // set up function
extern int MLOG_begin(bool checkLogs);          // check chip's ID and check all logs(takes a few seconds)
  // log operations
extern int MLOG_putLog(MLOG_T *log_p);          // put log in fifo buffer
extern int MLOG_getLog(MLOG_T *log_p);          // get oldest unuploaded log from fifo buffer
extern uint32_t MLOG_countUploadableLog(void);  // count number of unuploaded logs in fifo buffer
extern void MLOG_syncTail(void);                // Synchronize tail of uploading and tail of sending
extern int MLOG_getLog2(MLOG_T *log_p);         // get oldest unsent log from fifo buffer
  // Control functions
extern int MLOG_format(void);                   // format chip(takes a few seconds)
extern int MLOG_checkLogs(void);                // full scan the chip to restore the head and tail(takes a few seconds)
  // Switch buffer on Flash <-> SRAM
extern int MLOG_switchToSRAM(void);             // temporarily switch the log storage destination to SRAM
extern int MLOG_returnToFlash(void);            // return the log storage destination to Flash

#ifdef	__cplusplus
}
#endif

#endif	/* MLOG_H */
