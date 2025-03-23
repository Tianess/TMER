#ifndef _MAIN_H
#define _MAIN_H
#include <STC12C5A60S2.H>

//����IO����
sbit KEY3 = P2^5; 
sbit KEY2 = P2^6;					
sbit KEY1 = P2^7;

//�������Ŷ���
sbit SDA = P2^0;  /* ������ */
sbit SCL = P2^1;  /* ʱ���� */

//DS1302���Ŷ���
sbit DS1302_SCLK=P3^6;
sbit DS1302_IO=P3^4;
sbit DS1302_CE=P3^5;

//LED���Ŷ���
sbit LED_W=P0^0;
sbit LED_B=P0^1;
sbit LED_G=P0^2;
sbit LED_R=P0^3;

//�̵������Ŷ���

sbit Relay1=P4^4;
sbit Relay2=P4^5;

//���ֶ���
sbit Busy_Music=P2^3;

#define Key1_Single_Click 11						
#define Key1_Double_Click 12
#define Key1_Long_Click 13	

#define Key2_Single_Click 21	
#define Key2_Double_Click 22	
#define Key2_Long_Click 23		

#define Key3_Single_Click 31	
#define Key3_Double_Click 32	
#define Key3_Long_Click 33		


#endif