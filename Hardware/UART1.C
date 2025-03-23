#include <STC12C5A60S2.H>
#include <stdio.h>
#include "UART1.H"



void Uart1_Init(void)	//9600bps@11.0592MHz
{
	PCON &= 0x7F;		//波特率不倍速
	SCON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x04;		//定时器时钟1T模式
	BRT = 0xDC;			//设置定时重载值
	AUXR |= 0x01;		//串口1使用独立波特率发射器为波特率发生器
	AUXR |= 0x10;		//启动独立波特率发射器
	ES = 1;				//使能串口1中断
	
}

//向串口发送一个字符
void Uart1_SendByte(unsigned char dat)
{
    while (busy1);           //Wait for the completion of the previous data is sent
    ACC = dat;              //Calculate the even parity bit P (PSW.0)
    busy1 = 1;
    SBUF = ACC;             //Send data to UART buffer
}

//向串口发送一段字符串
void Uart1_SendString(unsigned char *dat)
{
	unsigned char i= 0;
	
	for(i = 0;dat[i]!='\0';i++){Uart1_SendByte(dat[i]);}
	if(dat[i]=='\0')Uart1_SendByte('\0');
}

//串口重定向
char putchar(char c){
	//输出重定向到串口
	Uart1_SendByte(c);
	return c;  //返回给函数的调用者printf
}