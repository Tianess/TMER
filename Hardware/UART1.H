#include <STC12C5A60S2.H>

#ifndef __UART1_H
#define __UART1_H


extern	bit busy1;
/*Define UART parity mode*/
/*定义串口校验模式*/
#define NONE_PARITY     0   //None parity
#define ODD_PARITY      1   //Odd parity
#define EVEN_PARITY     2   //Even parity
#define MARK_PARITY     3   //Mark parity
#define SPACE_PARITY    4   //Space parity

#define PARITYBIT EVEN_PARITY   //Testing even parity


void Uart1_Init(void);
void Uart1_SendByte(unsigned char dat);
void Uart1_SendString(unsigned char *dat);

#endif