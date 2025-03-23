#include "EEPROM.h"
#include "intrins.h"


/*注意，该程序仅用于STC12C5A60S2系列单片机，如果用于其他系列单片机，请确认是否需要修改EEPROM，
因为STC单片机的不同系列，内部EEPROM地址不同，例如STC89C51RC系列单片机内部EEPROM起始地址为2000h,
而STC12C5A60S2内部EEPROM起始地址为0000h,且STC89C51RC系列单片机和STC12C5A60S2系列单片机内部与
EEPROM有关的寄存器地址是不同的，具体参考STC89C51RC和STC12C5A60S2系列单片机手册*/

sfr IAP_DATA	=0xc2;
sfr IAP_ADDRH	=0xc3;
sfr IAP_ADDRL	=0xc4;
sfr IAP_CMD		=0xc5;
sfr IAP_TRIG	=0xc6;
sfr IAP_CONTR	=0xc7;




/******************************************************************
 - 函数名称：IAP_Idle
 - 功能描述：关闭IAP读/写/擦除Data Flash/EEPROM功能
 - 函数属性：外部函数，供用户调用
 - 参数说明：无
 - 返回说明：无
 - 注	   ：无
 ******************************************************************/
void IAP_Idle(void)
{
	IAP_CONTR=0;
	IAP_CMD=0;
	IAP_TRIG=0;
	IAP_ADDRH=0x80;
	IAP_ADDRL=0;
	
}	

/******************************************************************
 - 函数名称：IAP_ReadByte
 - 功能描述：读取内部EEPROM地址addr的数据
 - 函数属性：外部函数，供用户调用
 - 参数说明：addr-->内部地址
 - 返回说明：无
 - 注	   ：无
 ******************************************************************/
unsigned char IAP_ReadByte(unsigned int addr)
{
	unsigned dat;
	
	IAP_CONTR=ENABLE_IAP;
	IAP_CMD=CMD_READ;
	IAP_ADDRL=addr;
	IAP_ADDRH=addr>>8;
	IAP_TRIG=0x5a;
	IAP_TRIG=0xa5;
	_nop_();
	
	dat=IAP_DATA;
	IAP_Idle();
	
	return dat;
}

/******************************************************************
 - 函数名称：IAP_ProgramByte
 - 功能描述：写内部EEPROM地址addr的数据
 - 函数属性：外部函数，供用户调用
 - 参数说明：addr-->内部地址
			 dat-->需要写入的数据
 - 返回说明：无
 - 注	   ：无
 ******************************************************************/
void IAP_ProgramByte(unsigned int addr,unsigned char dat)
{
	IAP_CONTR=ENABLE_IAP;
	IAP_CMD=CMD_PROGRAM;
	IAP_ADDRL=addr;
	IAP_ADDRH=addr>>8;
	IAP_DATA=dat;
	IAP_TRIG=0x5a;
	IAP_TRIG=0xa5;
	_nop_();
	
	IAP_Idle();
}

/******************************************************************
 - 函数名称：IAP_EraseSector
 - 功能描述：擦除内部EEPROM的扇区数据
 - 函数属性：外部函数，供用户调用
 - 参数说明：addr-->内部地址
 - 返回说明：无
 - 注	   ：1.只有“扇区擦除”才能将“0”擦除为“1”
 ******************************************************************/
void IAP_EraseSector(unsigned int addr)
{
	IAP_CONTR=ENABLE_IAP;
	IAP_CMD=CMD_ERASE;
	IAP_ADDRL=addr;
	IAP_ADDRH=addr>>8;
	IAP_TRIG=0x5a;
	IAP_TRIG=0xa5;
	_nop_();
	
	IAP_Idle();
}