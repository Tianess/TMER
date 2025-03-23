#ifndef __EEPROM_H__
#define __EEPROM_H__



#define CMD_IDLE	0
#define	CMD_READ	1
#define	CMD_PROGRAM	2
#define	CMD_ERASE	3

#define ENABLE_IAP 	0x82	//if SYSCLK<20MHZ

#define IAP_ADDRESS	0x0000



/*****************外部接口函数******************/
//空闲模式，关闭EEPROM操作
void IAP_Idle(void);
	
//读取内部EEPROM地址addr的数据
unsigned char IAP_ReadByte(unsigned int addr);
	
//写内部EEPROM地址addr的数据
void IAP_ProgramByte(unsigned int addr,unsigned char dat);
	
//擦除内部EEPROM的扇区数据
void IAP_EraseSector(unsigned int addr);


#endif /*__EEPROM_H__*/