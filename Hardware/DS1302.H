#ifndef __DS1302_H__
#define __DS1302_H__

void DS1302_Init();//初始化函数
void DS1302_WriteByte(unsigned char Command,Date);//单字节写入函数
unsigned char DS1302_ReadByte(unsigned Command);//单字节读出函数
void DS1302_SetTime();//设置内部时间函数
void DS1302_ReadTime();//读取内部时间函数

extern	char DS1302_Time[];//时间数组
extern	u8 Time2Set[];
#endif