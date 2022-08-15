/*
 * File:   util.h
 * Author:  Interark Corp.
 * Summary: WPFM(code name "DLC_04") project utility header file.
 * Date:    2022/07/02 (R0)
 * Note:
 */

#ifndef UTIL_H
#define	UTIL_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "app.h"

/*
*   Macros
*/
  // GPIO control
#define UTIL_GPIO_set(pin)              (PORT_REGS->GROUP[0].PORT_OUTSET = ((uint32_t)1U << (pin)))
#define UTIL_GPIO_clear(pin)            (PORT_REGS->GROUP[0].PORT_OUTCLR = ((uint32_t)1U << (pin)))
#define UTIL_GPIO_toggle(pin)           (PORT_REGS->GROUP[0].PORT_OUTTGL = ((uint32_t)1U << (pin)))
#define UTIL_GPIO_get(pin)              (((PORT_REGS->GROUP[0].PORT_IN >> (pin))) & 0x01U)

  // LED functions
extern void UTIL_setLED1(void);
extern void UTIL_clearLED1(void);
extern void UTIL_toggleLED1(void);
extern void UTIL_startBlinkLED1(void);
extern void UTIL_stopBlinkLED1(void);
extern void UTIL_setEXT1LED(void);
extern void UTIL_clearEXT1LED(void);
extern void UTIL_toggleEXT1LED(void);
extern void UTIL_startBlinkEXT1LED(void);
extern void UTIL_stopBlinkEXT1LED(void);
extern void UTIL_setEXT2LED(void);
extern void UTIL_clearEXT2LED(void);
extern void UTIL_toggleEXT2LED(void);
extern void UTIL_startBlinkEXT2LED(void);
extern void UTIL_stopBlinkEXT2LED(void);

// USB functions
extern bool UTIL_hasConnectedUSB(void);

// Utility functions
extern void UTIL_delayMicros(uint32_t time);
extern float UTIL_map(float value, float lowerFrom, float upperFrom, float lowerTo, float upperTo);


#ifdef	__cplusplus
}
#endif

#endif	/* UTIL_H */
