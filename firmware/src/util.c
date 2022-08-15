/*
 * File:    util.c
 * Author:  Interark Corp.
 * Summary: WPFM(code name "DLC_04") project utility implementation file.
 * Date:    2022/07/15 (R0)
 * Note:    use TC3 for LED1 blinking, use TC4 for EXT1_LED and EXT2_LED blinking
 */


#include <stdio.h>
#include "util.h"
#include "wpfm.h"
#include "gpioexp.h"

// Local functions
static void _UTIL_ISR_toggleLED1(TC_TIMER_STATUS status, uintptr_t context);
static void _UTIL_ISR_toggleEXT1LED(TC_TIMER_STATUS status, uintptr_t context);
static void _UTIL_ISR_toggleEXT2LED(TC_TIMER_STATUS status, uintptr_t context);


void UTIL_delayMicros(uint32_t time)
{
    static uint16_t dummy[4];
    volatile int i;

    while (time > 0)
    {
        for (i = 0; i < 20; i++)
            dummy[i % 4] = (uint8_t)i;
        time--;
    }
    (void)dummy[0];
}

float UTIL_map(float value, float lowerFrom, float upperFrom, float lowerTo, float upperTo)
{
    if (value > upperFrom)
        value = upperFrom;
    else if (value < lowerFrom)
        value = lowerFrom;

    float mappedValue = (((upperTo - lowerTo) / (upperFrom - lowerFrom)) * value) + lowerTo;

    return (mappedValue);
}

void UTIL_setLED1(void)
{
    uint8_t port = 0;
    GPIOEXP_readPort(&port);
    port |= GPIOEXP_SET_BIT(WPFM_GPIO_LED1);
    GPIOEXP_writePort(port);
}

void UTIL_clearLED1(void)
{
    uint8_t port = 0;
    GPIOEXP_readPort(&port);
    port &= GPIOEXP_CLEAR_BIT(WPFM_GPIO_LED1);
    GPIOEXP_writePort(port);
}

void UTIL_toggleLED1(void)
{
    uint8_t port = 0;
    GPIOEXP_readPort(&port);
    port ^= GPIOEXP_SET_BIT(WPFM_GPIO_LED1);
    GPIOEXP_writePort(port);
}

void UTIL_startBlinkLED1(void)
{
    TC3_TimerCallbackRegister(_UTIL_ISR_toggleLED1, (uintptr_t)0);
    TC3_TimerStart();
}

void UTIL_stopBlinkLED1(void)
{
    TC3_TimerStop();
}

void UTIL_setEXT1LED(void)
{
    uint8_t port = 0;
    GPIOEXP_readPort(&port);
    port |= GPIOEXP_SET_BIT(WPFM_GPIO_EXT1_LED);
    GPIOEXP_writePort(port);
}

void UTIL_clearEXT1LED(void)
{
    uint8_t port = 0;
    GPIOEXP_readPort(&port);
    port &= GPIOEXP_CLEAR_BIT(WPFM_GPIO_EXT1_LED);
    GPIOEXP_writePort(port);
}

void UTIL_toggleEXT1LED(void)
{
    uint8_t port = 0;
    GPIOEXP_readPort(&port);
    port ^= GPIOEXP_SET_BIT(WPFM_GPIO_EXT1_LED);
    GPIOEXP_writePort(port);
}

void UTIL_startBlinkEXT1LED(void)
{
    TC4_TimerCallbackRegister(_UTIL_ISR_toggleEXT1LED, (uintptr_t)0);
    TC4_TimerStart();
}

void UTIL_stopBlinkEXT1LED(void)
{
    TC4_TimerStop();
}

void UTIL_setEXT2LED(void)
{
    uint8_t port = 0;
    GPIOEXP_readPort(&port);
    port |= GPIOEXP_SET_BIT(WPFM_GPIO_EXT2_LED);
    GPIOEXP_writePort(port);
}

void UTIL_clearEXT2LED(void)
{
    uint8_t port = 0;
    GPIOEXP_readPort(&port);
    port &= GPIOEXP_CLEAR_BIT(WPFM_GPIO_EXT2_LED);
    GPIOEXP_writePort(port);
}

void UTIL_toggleEXT2LED(void)
{
    uint8_t port = 0;
    GPIOEXP_readPort(&port);
    port ^= GPIOEXP_SET_BIT(WPFM_GPIO_EXT2_LED);
    GPIOEXP_writePort(port);
}

void UTIL_startBlinkEXT2LED(void)
{
    TC4_TimerCallbackRegister(_UTIL_ISR_toggleEXT2LED, (uintptr_t)0);
    TC4_TimerStart();
}

void UTIL_stopBlinkEXT2LED(void)
{
    TC4_TimerStop();
}

bool UTIL_hasConnectedUSB(void)
{
    return (VBUS_CHECK_Get());
}

static void _UTIL_ISR_toggleLED1(TC_TIMER_STATUS status, uintptr_t context)
{
    UTIL_toggleLED1();
}

static void _UTIL_ISR_toggleEXT1LED(TC_TIMER_STATUS status, uintptr_t context)
{
    UTIL_toggleEXT1LED();
}

static void _UTIL_ISR_toggleEXT2LED(TC_TIMER_STATUS status, uintptr_t context)
{
    UTIL_toggleEXT2LED();
}
