#include <STC12C5A60S2.H>

#ifndef __UART2_H
#define __UART2_H


extern	bit busy2;
/*Define UART parity mode*/
/*定义串口校验模式*/
#define NONE_PARITY     0   //None parity
#define ODD_PARITY      1   //Odd parity
#define EVEN_PARITY     2   //Even parity
#define MARK_PARITY     3   //Mark parity
#define SPACE_PARITY    4   //Space parity

#define S2RI  0x01          //S2CON.0
#define S2TI  0x02          //S2CON.1
#define S2RB8 0x04          //S2CON.2
#define S2TB8 0x08          //S2CON.3

#define PARITYBIT EVEN_PARITY   //Testing even parity


void Uart2_Init(void);
void Uart2_SendByte(unsigned char dat);
void Uart2_SendString(unsigned char *dat);
void UART2_SendHex(const unsigned char* hexData, unsigned char length);
#endif