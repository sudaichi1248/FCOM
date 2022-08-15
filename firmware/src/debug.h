/*
 * File:    debug.h
 * Author:  Interark Corp.
 * Summary: Debug macro header file.
 * Date:    2022/07/17 (R0)
 * Note:
 */

#ifndef DEBUG_H
#define	DEBUG_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <string.h>
#include <stdio.h>

/*
*   Macros & symbols
*/
#define DEBUG_HALT()                        while (true)

#ifdef DEBUG_LCD
#   include "lcd.h"
#   define DEBUG_LCD_printString(n,s)       { LCD_str((n), (s)); }
#   define DEBUG_LCD_printFormat(n,...)     { char _line[9]; snprintf(_line, sizeof(_line), __VA_ARGS__); LCD_str((n), _line); }
#   define DEBUG_LCD_clearLine(n)           { char *_emptyLine = "        "; LCD_str((n), _emptyLine); }
#   define DEBUG_LCD_clear()                { LCD_clear(); }
#else
#   define DEBUG_LCD_printString(n,s)
#   define DEBUG_LCD_printFormat(n,...)
#   define DEBUG_LCD_clearLine(n)
#   define DEBUG_LCD_clear()
#endif // DEBUG_USB

#ifdef DEBUG_USB
#   include "app.h"
#   define DEBUG_USB_printString(s)         { APP_printUSB((s)); }
#   define DEBUG_USB_printlnString(s)       { APP_printlnUSB((s)); }
#   define DEBUG_USB_printFormat(...)       { char _line[80]; snprintf(_line, sizeof(_line),  __VA_ARGS__); APP_printUSB(_line); }
#   define DEBUG_USB_printlnFormat(...)     { char _line[80]; snprintf(_line, sizeof(_line),  __VA_ARGS__); APP_printlnUSB(_line); }
#else
#   define DEBUG_USB_printString(s)
#   define DEBUG_USB_printlnString(s)
#   define DEBUG_USB_printFormat(...)
#   define DEBUG_USB_printlnFormat(...)
#endif // DEBUG_USB

#ifdef DEBUG_UART
#   include "uart_debug.h"
#   define DEBUG_UART_printString(s)        { UART_DEBUG_writeBytes((s), strlen(s)); }
#   define DEBUG_UART_printlnString(s)      { UART_DEBUG_writeBytes((s), strlen(s)); UART_DEBUG_writeBytes("\n", 1); }
#   define DEBUG_UART_printFormat(...)      { char _line[80]; snprintf(_line, sizeof(_line),  __VA_ARGS__); UART_DEBUG_writeBytes(_line, strlen(_line)); }
#   define DEBUG_UART_printlnFormat(...)    { char _line[80]; snprintf(_line, sizeof(_line),  __VA_ARGS__); UART_DEBUG_writeBytes(_line, strlen(_line)); UART_DEBUG_writeBytes("\n", 1); }
#else
#   define DEBUG_UART_printString(s)
#   define DEBUG_UART_printlnString(s)
#   define DEBUG_UART_printFormat(...)
#   define DEBUG_UART_printlnFormat(...)
#endif // DEBUG_UART

#ifdef	__cplusplus
}
#endif

#endif	/* DEBUG_H */
