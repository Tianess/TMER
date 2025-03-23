 #include <STC12C5A60S2.H>
#include "DS1302.H"
#include "main.h"


//对应寄存器位置定义
#define DS1302_DAY			0X8A
#define DS1302_Year			0x8C    
#define DS1302_Month		0x88    
#define DS1302_Date			0x86     
#define DS1302_Hour			0x84    
#define DS1302_Minutes	0x82   
#define DS1302_Second		0x80
#define DS1302_WP				0x8E


//DS1302初始化
void DS1302_Init()
{
	DS1302_SCLK=0;//将时钟位置0，低电平
	DS1302_CE=0;	//将使能位置0，低电平
}

//DS1302单字节写入函数
//command：写入控制指令的指令，包含要写入寄存器的地址
//Data：将要写入的数据内容
void DS1302_WriteByte(unsigned char Command,Data)
{	unsigned char i;
	DS1302_CE=1;//使能位置高电平
	for(i=0;i<8;i++)
	{//控制寄存器数据需要通过IO线一个一个写入控制寄存器;低位先写入
		DS1302_IO=Command&(0x01<<i);//相当于把第1--7位置0，只留第0位，如果第0位是0，则为0；反之则为1；
		DS1302_SCLK=1;
		DS1302_SCLK=0;
	}
	
	for(i=0;i<8;i++)//数据写入
	{
		DS1302_IO=Data&(0x01<<i);//相当于把第1--7位置0，只留第0位，如果第0位是0，则为0；反之则为1；
		DS1302_SCLK=1;
		DS1302_SCLK=0;
	}
	DS1302_CE=0;

}

//DS1302单字节读出函数
//command：写入控制指令的指令，包含要读出寄存器的地址
//Data：读出的数据
unsigned char DS1302_ReadByte(unsigned Command)
{
	unsigned char i,Data=0x00;
	Command|=0x01;//写入指令与读出指令只在最后一位相差1，故在此利用或运算消除；
	DS1302_CE=1;//使能位置高电平；
	for(i=0;i<8;i++)
	{//控制寄存器数据需要通过IO线一个一个写入控制寄存器;低位先写入
		DS1302_IO=Command&(0x01<<i);
		DS1302_SCLK=0;
		DS1302_SCLK=1;
	}
	for(i=0;i<8;i++)//数据读出
	{	DS1302_SCLK=1;
		DS1302_SCLK=0;
		if(DS1302_IO){Data|=(0x01<<i);}
	}
	
	DS1302_CE=0;
	DS1302_IO=0;
	return Data;
}

// 向DS1302内设定时间
void DS1302_SetTime()
{
	DS1302_WriteByte(DS1302_WP,0x00);//操作 DS1302 之前，关闭写保护，不然指令无法进入控制寄存器
	DS1302_WriteByte(DS1302_Year,DS1302_Time[0]/10*16+DS1302_Time[0]%10);			//写入年，并将10进制转化BCD码
	DS1302_WriteByte(DS1302_Month,DS1302_Time[1]/10*16+DS1302_Time[1]%10);		//写入月，并将10进制转化BCD码
	DS1302_WriteByte(DS1302_Date,DS1302_Time[2]/10*16+DS1302_Time[2]%10);			//写入日，并将10进制转化BCD码
	DS1302_WriteByte(DS1302_Hour,DS1302_Time[3]/10*16+DS1302_Time[3]%10);			//写入时，并将10进制转化BCD码
	DS1302_WriteByte(DS1302_Minutes,DS1302_Time[4]/10*16+DS1302_Time[4]%10);	//写入分，并将10进制转化BCD码
	DS1302_WriteByte(DS1302_Second,DS1302_Time[5]/10*16+DS1302_Time[5]%10);		//写入秒，并将10进制转化BCD码
	DS1302_WriteByte(DS1302_DAY,DS1302_Time[6]/10*16+DS1302_Time[6]%10);//写入星期，并将10进制转化BCD码；
	DS1302_WriteByte( DS1302_WP,0x80);//写入结束，开启写保护；
}

//读取DS1302内时间
void DS1302_ReadTime()
{
	unsigned char Temp;
	
	Temp=DS1302_ReadByte(DS1302_Year);			//读取年BCD码
	DS1302_Time[0]=Temp/16*10+Temp%16;			//BCD码转十进制
	Temp=DS1302_ReadByte(DS1302_Month);			//读取月BCD码
	DS1302_Time[1]=Temp/16*10+Temp%16;
	Temp=DS1302_ReadByte(DS1302_Date);			//读取日BCD码
	DS1302_Time[2]=Temp/16*10+Temp%16;
	Temp=DS1302_ReadByte(DS1302_Hour);			//读取时BCD码
	DS1302_Time[3]=Temp/16*10+Temp%16;
	Temp=DS1302_ReadByte(DS1302_Minutes);		//读取分BCD码
	DS1302_Time[4]=Temp/16*10+Temp%16;
	Temp=DS1302_ReadByte(DS1302_Second);		//读取秒BCD码
	DS1302_Time[5]=Temp/16*10+Temp%16;
	Temp=DS1302_ReadByte(DS1302_DAY);				//读取星期BCD码
	DS1302_Time[6]=Temp/16*10+Temp%16;
}

