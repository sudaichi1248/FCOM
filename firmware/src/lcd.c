/*
 * File:    lcd.c
 * Author:  Interark Corp.
 * Summary: LCD(AE-AQM0802) driver implementation file.
 * Date:    2022/06/16 (R0)
 * Note:    for debugging
 */

#include <stdint.h>
#include <stdbool.h>
#include "lcd.h"

static uint8_t tbuf[6];

void Delay_us(uint32_t time)
{
    int i;
    while (time != 0)
    {
        for (i = 0; i < 10; i++)
        {
            tbuf[4] = i;
        }
        time--;
    }
}

void Delay_ms(uint32_t time)
{
    int j;
    while (time != 0)
    {
        for (j = 0; j < 10000; j++)
        {
            tbuf[4] = j;
        }
        time--;
    }
}

void LCD_data(char data)
{
    tbuf[0] = 0x40;
    tbuf[1] = data;
    SERCOM3_I2C_Write(0x3E, tbuf, 2);
    while (SERCOM3_I2C_IsBusy())
        ;
    Delay_us(30);
}

void LCD_cmd(char cmd)
{
    tbuf[0] = 0x00;
    tbuf[1] = cmd;
    SERCOM3_I2C_Write(0x3E, tbuf, 2);
    while (SERCOM3_I2C_IsBusy())
        ;
    if ((cmd == 0x01) || (cmd == 0x02))
        Delay_ms(2);          // wait for 2mS
    else
        Delay_us(30);         // wait for 30uS
}

void LCD_init(void)
{
    Delay_ms(150);
    LCD_cmd(0x38);          // 8bit 2line Normal mode
    LCD_cmd(0x39);          // 8bit 2line Extend mode
    LCD_cmd(0x14);          // OSC 183Hz BIAS 1/5
    LCD_cmd(0x70);          // Contrast Set
    LCD_cmd(0x5E);          //Booster on 3.3V
//    LCD_cmd(0x5B);          // Booster Off 5V
    LCD_cmd(0x6C);          // Follower
    Delay_ms(300);

    LCD_cmd(0x38);          // Set Normal mode
    LCD_cmd(0x0C);          // Display On
    LCD_cmd(0x01);          // Clear Display
    Delay_ms(3);            // add @dai
}

void LCD_move(uint8_t pos)
{
    LCD_cmd(0x80 | pos);
}

void LCD_clear(void)
{
    LCD_cmd(0x01);
    Delay_ms(3);
    LCD_move(0);
}

void LCD_str(int line, char* ptr)
{
    if (line == 1)
        LCD_cmd(0x80);
    else
        LCD_cmd(0xC0);

    while (*ptr != 0)
    {
        LCD_data(*ptr++);
    }
}
