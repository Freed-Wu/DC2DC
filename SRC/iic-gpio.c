/*
 * iic-gpio.c
 *
 *  Created on: 2019年7月29日
 *      Author: nszm
 */
#include"DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#include "iic-gpio.h"
#include <string.h>

void i2c_start()
{    // I2C 开始时序：SCL=1时，SDA由1变成0.
    I2C_SDA_OUTPUT();
    I2C_SDA_HIGH();
    DELAY_US(5);
    I2C_SCL_HIGH();
    DELAY_US(5);
    I2C_SDA_LOW();
    DELAY_US(50);
    I2C_SCL_LOW();
    DELAY_US(5);
}

void i2c_stop()
{    // I2C 停止时序：SCL=1时，SDA由0变成1.
    I2C_SDA_OUTPUT();
    I2C_SDA_LOW();
    DELAY_US(5);
    I2C_SCL_HIGH();
    DELAY_US(5);
    I2C_SDA_HIGH();
}

unsigned char i2c_wait_ack()
{
    unsigned char sda_status;
    unsigned char wait_time=0;
    unsigned char ack_nack = 1;
    //先设置SDA脚为输入
    I2C_SDA_INPUT();
    //等待SDA脚被从机拉低
    while(I2C_SDA_STATUS)
    {
        wait_time++;
        //如果等待时间过长，则退出等待
        if (wait_time>=200)
        {
            ack_nack = 0;
            break;
        }
    }
    // SCL由0变为1，读入ACK状态    如果此时SDA=0，则是ACK; 如果此时SDA=1，则是NACK
    DELAY_US(5);
    I2C_SCL_HIGH();
    DELAY_US(5);

    //再次将SCL=0，并且将SDA脚设置为输出
    I2C_SCL_LOW();
    DELAY_US(5);
    I2C_SDA_OUTPUT();
    DELAY_US(5);
    return ack_nack;
}

void i2c_send_ack()
{    // 发送ACK就是在SDA=0时，SCL由0变成1
    I2C_SDA_LOW();
    DELAY_US(5);
    I2C_SCL_HIGH();
    DELAY_US(5);
    I2C_SCL_LOW();
    DELAY_US(5);
}

void i2c_send_nack()
{    // 发送NACK就是在SDA=1时，SCL由0变成1
    I2C_SDA_HIGH();
    DELAY_US(5);
    I2C_SCL_HIGH();
    DELAY_US(50);
    I2C_SCL_LOW();
    DELAY_US(5);
}

void i2c_write_byte(unsigned char aByte)
{
    unsigned char i;
    for (i=0;i<8;i++)
    {
        //先将SCL拉低；
        I2C_SCL_LOW();
        DELAY_US(5);
        //然后在SDA输出数据
        if(aByte&0x80)
        {
            I2C_SDA_HIGH();
        }
        else
        {
            I2C_SDA_LOW();
        }
        DELAY_US(50);
        //最后将SCL拉高，在SCL上升沿写入数据
        I2C_SCL_HIGH();
        DELAY_US(5);
        aByte = aByte<<1;//数据位移    }
        //写完一个字节只后要将SCL拉低
        I2C_SCL_LOW();
        DELAY_US(5);
    }
}

unsigned char i2c_read_byte()
{
    unsigned char i,aByte;
    //先将SDA脚设置为输入
    I2C_SDA_INPUT();
    for (i=0;i<8;i++)
    {
        //数据位移
        aByte = aByte << 1;
        //延时等待SDA数据稳定
        DELAY_US(50);
        //SCL=1，锁定SDA数据
        I2C_SCL_HIGH();
        DELAY_US(5);
        //读取SDA状态
        if(I2C_SDA_STATUS)
        {
            aByte |= 0x01;
        }
        //SCL=0，解除锁定
        I2C_SCL_LOW();
    }
    //读完一个字节，将SDA重新设置为输出
    I2C_SDA_OUTPUT();
    return aByte;
}

void init_dac()
{
    EALLOW;
    GpioCtrlRegs.GPAMUX2.bit.GPIO22 = 0;
    GpioCtrlRegs.GPADIR.bit.GPIO22 = 1;
    GpioCtrlRegs.GPAMUX2.bit.GPIO23 = 0;
    GpioCtrlRegs.GPADIR.bit.GPIO23 = 1;
    GpioCtrlRegs.GPAPUD.all = 0;
    GpioDataRegs.GPADAT.bit.GPIO22 = 1;
    GpioDataRegs.GPADAT.bit.GPIO23 = 1;
    EDIS;
}


