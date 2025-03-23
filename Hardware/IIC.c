#include "iic.h"
#include <STC12C5A60S2.H>
#include <intrins.h>
#include "main.h"
 



//开始信号
void IIC_Start(void)
{
		SDA = 1;
    SCL = 1;//当SCL为高电平的时候，SDA线上由高到低的跳变被定义为起始条件
    SDA = 0;
    SCL = 0;	
}
 
//停止信号
void IIC_Stop(void)
{
    SDA = 0;
    SCL = 1;//SCL为高电平的时候，SDA线上由低到高的跳变被定义为停止条件；
    SDA = 1;
}
 
//等待应答信号（作用很大）
bit IIC_Wait_Ack(void)
{
    bit ackbit;
	
    SCL  = 1;
    ackbit = SDA;
    SCL = 0;
    return ackbit;
}
 
//通过I2C总线发送数据
void Write_IIC_Byte(unsigned char byt)
{
    unsigned char i;
 
    for(i=0; i<8; i++)
    {
        SCL  = 0;
        if(byt & 0x80) SDA  = 1;
        else SDA  = 0;
        SCL = 1;
        byt <<= 1;
    }
    SCL  = 0;  
}
 
//从I2C总线上接收数据
unsigned char IIC_RecByte(void)
{
	unsigned char i, da;
	for(i=0; i<8; i++)
	{   
		SCL = 1;
		da <<= 1;
		if(SDA) da |= 1;
		SCL = 0;
	}
	return da;    
}