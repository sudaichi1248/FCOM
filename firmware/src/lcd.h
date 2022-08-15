/*
 * File:    lcd.h
 * Author:  Interark Corp.
 * Summary: LCD(AE-AQM0802) driver header file.
 * Date:    2022/06/16 (R0)
 * Note:    for debugging
 */

#ifndef LCD_H
#define	LCD_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "definitions.h"

// Functions
extern void Delay_ms(uint32_t time);
extern void Delay_us(uint32_t time);
extern void LCD_init(void);
extern void LCD_data(char data);
extern void LCD_cmd(char cmd);
extern void LCD_clear(void);
extern void LCD_str(int line, char* ptr);
extern void LCD_move(uint8_t pos);

#ifdef	__cplusplus
}
#endif

#endif	/* LCD_H */
