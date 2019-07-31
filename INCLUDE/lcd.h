// =====================================================================================
//
//       Filename:  lcd.h
//
//    Description:
/*
 * lcd.h
 * Copyright (C) 2019  <@ABEL>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef LCD_H
#define LCD_H

// -----------------发送命令子程序----------------------- P1.0（cs gpio57）,P1.1(SID gpio54),P1.2(CLK gpio56)
#include <stdbool.h>
#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"

#define PTDD_PTDD6 GpioDataRegs.GPBSET.bit.GPIO57
#define PTDD_PTDD2 GpioDataRegs.GPBSET.bit.GPIO56
#define PTDD_PTDD3 GpioDataRegs.GPBSET.bit.GPIO54

void send_command(unsigned char command_data); //发送命令
void send_data(unsigned char command_data);
void lcd_init();
void hz_disp(unsigned char line, unsigned char row, unsigned char hz1, unsigned char hz2); //line行1-4，row列0-7，hz1汉字的高8位，hz2，汉字的低8位
void num_disp(unsigned char line, unsigned char row, unsigned char num, unsigned char numa, unsigned char numb, unsigned char numc); //line行1-4，row列0-7，num要显示的数字
void strDisp(unsigned char line, unsigned char row, char str[], unsigned int count);//line行1-4，row列0-7，num要显示的数字
void LCD12864_Clear();
qian_(int i);
bai_(int i);
shi_(int i);
ge_(int i);
lcd_voltage1(i);
lcd_voltage2(i);
lcd_voltage3(i);
void num2char1(char *str, double number, int g, int l);
void num2char2(char *str, double number, int g, int l);
void num2char3(char *str, double number, int g, int l);

#endif /* !LCD_H */
//
//        Version:  1.0
//        Created:  2019/7/19 17:00:54
//       Revision:  none
//       Compiler:  g++
//
//         Author:  YOUR NAME (),
//        Company:
//
// =====================================================================================

