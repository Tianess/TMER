#include <STC12C5A60S2.H>
#include <stdio.h>
#include "UART2.H"

void Uart2_Init(void)	//9600bps@11.0592MHz
{
	AUXR &= 0xF7;		//波特率不倍速
	S2CON = 0x50;		//8位数据,可变波特率
	AUXR &= 0xFB;		//定时器时钟12T模式
	BRT = 0xFD;			//设置定时重载值
	AUXR |= 0x10;		//启动独立波特率发射器
	IE2 |= 0x01;		//使能串口2中断
}

//向串口发送一个字符
void Uart2_SendByte(unsigned char dat)
{
	while (busy2);
	ACC = dat;
	busy2 = 1;
	S2BUF = ACC;
}

//向串口发送一段字符串
void Uart2_SendString(unsigned char *dat)
{
	unsigned char i= 0;
	
	for(i = 0;dat[i]!='\0';i++){Uart2_SendByte(dat[i]);}
	if(dat[i]=='\0')Uart2_SendByte('\0');
}

// 串口2发送16进制数据数组
void UART2_SendHex(const unsigned char* hexData, unsigned char length)
{
	unsigned char i;
	for (i = 0; i < length; i++)
	{
		Uart2_SendByte(hexData[i]);
	}
}