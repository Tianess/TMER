#ifndef _IIC_H
#define _IIC_H
 
bit IIC_Wait_Ack(void); 

void IIC_Start(void);  
void IIC_SendAck(bit ackbit); 
void Write_IIC_Byte(unsigned char byt); 
unsigned char IIC_RecByte(void); 
void IIC_Stop(void);
 
#endif