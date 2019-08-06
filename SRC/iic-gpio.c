/*
 * iic-gpio.c
 *
 *  Created on: 2019��7��29��
 *      Author: nszm
 */
#include"DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#include "iic-gpio.h"
#include <string.h>

void i2c_start()
{    // I2C ��ʼʱ��SCL=1ʱ��SDA��1���0.
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
{    // I2C ֹͣʱ��SCL=1ʱ��SDA��0���1.
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
    //������SDA��Ϊ����
    I2C_SDA_INPUT();
    //�ȴ�SDA�ű��ӻ�����
    while(I2C_SDA_STATUS)
    {
        wait_time++;
        //����ȴ�ʱ����������˳��ȴ�
        if (wait_time>=200)
        {
            ack_nack = 0;
            break;
        }
    }
    // SCL��0��Ϊ1������ACK״̬    �����ʱSDA=0������ACK; �����ʱSDA=1������NACK
    DELAY_US(5);
    I2C_SCL_HIGH();
    DELAY_US(5);

    //�ٴν�SCL=0�����ҽ�SDA������Ϊ���
    I2C_SCL_LOW();
    DELAY_US(5);
    I2C_SDA_OUTPUT();
    DELAY_US(5);
    return ack_nack;
}

void i2c_send_ack()
{    // ����ACK������SDA=0ʱ��SCL��0���1
    I2C_SDA_LOW();
    DELAY_US(5);
    I2C_SCL_HIGH();
    DELAY_US(5);
    I2C_SCL_LOW();
    DELAY_US(5);
}

void i2c_send_nack()
{    // ����NACK������SDA=1ʱ��SCL��0���1
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
        //�Ƚ�SCL���ͣ�
        I2C_SCL_LOW();
        DELAY_US(5);
        //Ȼ����SDA�������
        if(aByte&0x80)
        {
            I2C_SDA_HIGH();
        }
        else
        {
            I2C_SDA_LOW();
        }
        DELAY_US(50);
        //���SCL���ߣ���SCL������д������
        I2C_SCL_HIGH();
        DELAY_US(5);
        aByte = aByte<<1;//����λ��    }
        //д��һ���ֽ�ֻ��Ҫ��SCL����
        I2C_SCL_LOW();
        DELAY_US(5);
    }
}

unsigned char i2c_read_byte()
{
    unsigned char i,aByte;
    //�Ƚ�SDA������Ϊ����
    I2C_SDA_INPUT();
    for (i=0;i<8;i++)
    {
        //����λ��
        aByte = aByte << 1;
        //��ʱ�ȴ�SDA�����ȶ�
        DELAY_US(50);
        //SCL=1������SDA����
        I2C_SCL_HIGH();
        DELAY_US(5);
        //��ȡSDA״̬
        if(I2C_SDA_STATUS)
        {
            aByte |= 0x01;
        }
        //SCL=0���������
        I2C_SCL_LOW();
    }
    //����һ���ֽڣ���SDA��������Ϊ���
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


