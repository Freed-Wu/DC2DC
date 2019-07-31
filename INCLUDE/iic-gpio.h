// =====================================================================================
// 
//       Filename:  iic-gpio.h
// 
//    Description:  
/*
 * iic-gpio.h
 * Copyright (C) 2019  <@ABEL>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef IIC_GPIO_H
#define IIC_GPIO_H
#include <stdbool.h>
#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
//scl gpio22; sda gpio23
#define I2C_SCL_LOW() GpioDataRegs.GPADAT.bit.GPIO22 = 0;
#define I2C_SCL_HIGH() GpioDataRegs.GPADAT.bit.GPIO22 = 1;
#define I2C_SDA_LOW() GpioDataRegs.GPADAT.bit.GPIO23 = 0;
#define I2C_SDA_HIGH() GpioDataRegs.GPADAT.bit.GPIO23 = 1;
#define I2C_SDA_INPUT()  GpioCtrlRegs.GPADIR.bit.GPIO23 = 0;
#define I2C_SDA_OUTPUT()  GpioCtrlRegs.GPADIR.bit.GPIO23 = 1;
#define I2C_SDA_STATUS  GpioDataRegs.GPADAT.bit.GPIO23

void i2c_start();
void i2c_stop();
unsigned char i2c_wait_ack();
void i2c_send_ack();
void i2c_send_nack();
void i2c_write_byte(unsigned char);
unsigned char i2c_read_byte();
void init_dac();

#endif /* !IIC_GPIO_H */
// 
//        Version:  1.0
//        Created:  2019/8/1 16:16:43
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  YOUR NAME (), 
//        Company:  
// 
// =====================================================================================

