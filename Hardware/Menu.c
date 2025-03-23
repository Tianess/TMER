#include <STC12C5A60S2.H>
#include "main.h"
#include "MENU.H"
#include "OLED.H"
#include "DS1302.H"
#include "UART1.H"
#include "UART2.H"
#include "EEPROM.H"

void Menu(u8 KeyNum)
{
	//��ʾ����
	if(KeyNum == Key1_Single_Click) {OLED_ShowString(0,6,"K1S",8,1);}
	if(KeyNum == Key1_Double_Click) {OLED_ShowString(0,6,"K1D",8,1);}
	if(KeyNum == Key1_Long_Click) 	{OLED_ShowString(0,6,"K1L",8,1);}
	
	if(KeyNum == Key2_Single_Click) {OLED_ShowString(0,6,"K2S",8,1);}
	if(KeyNum == Key2_Double_Click) {OLED_ShowString(0,6,"K2D",8,1);}
	if(KeyNum == Key2_Long_Click) 	{OLED_ShowString(0,6,"K2L",8,1);}
																
	if(KeyNum == Key3_Single_Click) {OLED_ShowString(0,6,"K3S",8,1);}
	if(KeyNum == Key3_Double_Click) {OLED_ShowString(0,6,"K3D",8,1);}
	if(KeyNum == Key3_Long_Click) 	{OLED_ShowString(0,6,"K3L",8,1);}
			
	if(Menu_state==10||Menu_state==12||Menu_state==14)//һ���˵�����
	{
		if(KeyNum==Key1_Single_Click)//����1���¹������
		{
			Menu_state=Menu_state-2;
			if(Menu_state<10){Menu_state=14;}
			OLED_Background1(Menu_state);
		}
		if(KeyNum==Key2_Single_Click)//����2���¹������
		{
			
			Menu_state=Menu_state+2;
			if(Menu_state>14){Menu_state=10;}
			OLED_Background1(Menu_state);
		}
		if(KeyNum==Key3_Single_Click)//����3���½���
		{
			Menu_state+=10;
			KeyNum=0;
			OLED_Clear();
		}
	}
	if(Menu_state==20||Menu_state==22||Menu_state==24)//�����˵�����
	{
		Secondary_Menu(Menu_state,KeyNum);
		if(Menu_state==20)
		{
			if(KeyNum==Key1_Single_Click){Stopwatchflag=1;}//�������
			if(KeyNum==Key2_Single_Click){Stopwatchflag=0;}//�����ͣ
			if(KeyNum==Key2_Long_Click){Msec=0;Sec=0;Min=0;}//ʱ�����
		}
		else if(Menu_state==22)
		{
			if(Countdownflag!=1)//����ʱʱ��ѡ��λ
			{				
				if(KeyNum==Key3_Single_Click)
				{
					Countdown_select++;
					Countdown_select%=3;
				}
				
				switch(Countdown_select)
				{//����ʱʱ������
					case 0://Сʱ����
								if(KeyNum==Key1_Long_Click||KeyNum==Key1_Single_Click){Countdown_Hour++;if(Countdown_Hour>60){Countdown_Hour=0;}}
								if(KeyNum==Key2_Long_Click||KeyNum==Key2_Single_Click){Countdown_Hour--;if(Countdown_Hour<0){Countdown_Hour=60;}}
								if(Countdown_Hour<10){OLED_ShowString(16,02,"0",16,0);OLED_ShowNum(24,02,Countdown_Hour,1,16,0);}
								else{OLED_ShowNum(16,02,Countdown_Hour,2,16,0);}
								if(Countdown_Min<10){OLED_ShowString(48,02,"0",16,1);OLED_ShowNum(56,02,Countdown_Min,1,16,1);}
								else{OLED_ShowNum(48,02,Countdown_Min,2,16,1);}
								if(Countdown_Sec<10){OLED_ShowString(80,02,"0",16,1);OLED_ShowNum(88,02,Countdown_Sec,1,16,1);}
								else{OLED_ShowNum(80,02,Countdown_Sec,2,16,1);}
								break;
					case 1://��������
								if(KeyNum==Key1_Long_Click||KeyNum==Key1_Single_Click){Countdown_Min++;if(Countdown_Min>=60){Countdown_Min=0;}}
								if(KeyNum==Key2_Long_Click||KeyNum==Key2_Single_Click){Countdown_Min--;if(Countdown_Min<0){Countdown_Min=59;}}
								if(Countdown_Hour<10){OLED_ShowString(16,02,"0",16,1);OLED_ShowNum(24,02,Countdown_Hour,1,16,1);}
								else{OLED_ShowNum(16,02,Countdown_Hour,2,16,1);}
								if(Countdown_Min<10){OLED_ShowString(48,02,"0",16,0);OLED_ShowNum(56,02,Countdown_Min,1,16,0);}
								else{OLED_ShowNum(48,02,Countdown_Min,2,16,0);}
								if(Countdown_Sec<10){OLED_ShowString(80,02,"0",16,1);OLED_ShowNum(88,02,Countdown_Sec,1,16,1);}
								else{OLED_ShowNum(80,02,Countdown_Sec,2,16,1);}
								break;
					case 2://��������
								if(KeyNum==Key1_Long_Click||KeyNum==Key1_Single_Click){Countdown_Sec++;if(Countdown_Sec>=60){Countdown_Sec=0;}}
								if(KeyNum==Key2_Long_Click||KeyNum==Key2_Single_Click){Countdown_Sec--;if(Countdown_Sec<0){Countdown_Sec=59;}}
								if(Countdown_Hour<10){OLED_ShowString(16,02,"0",16,1);OLED_ShowNum(24,02,Countdown_Hour,1,16,1);}
								else{OLED_ShowNum(16,02,Countdown_Hour,2,16,1);}
								if(Countdown_Min<10){OLED_ShowString(48,02,"0",16,1);OLED_ShowNum(56,02,Countdown_Min,1,16,1);}
								else{OLED_ShowNum(48,02,Countdown_Min,2,16,1);}
								if(Countdown_Sec<10){OLED_ShowString(80,02,"0",16,0);OLED_ShowNum(88,02,Countdown_Sec,1,16,0);}
								else{OLED_ShowNum(80,02,Countdown_Sec,2,16,0);}
								break;
				}
				if(KeyNum==Key3_Long_Click){Countdownflag=1;}//��������3����
			}
			else
			{//��������ʱ����ʾʱ��
				if(Countdown_Hour<10){OLED_ShowString(16,02,"0",16,1);OLED_ShowNum(24,02,Countdown_Hour,1,16,1);}
				else{OLED_ShowNum(16,02,Countdown_Hour,2,16,1);}
				if(Countdown_Min<10){OLED_ShowString(48,02,"0",16,1);OLED_ShowNum(56,02,Countdown_Min,1,16,1);}
				else{OLED_ShowNum(48,02,Countdown_Min,2,16,1);}
				if(Countdown_Sec<10){OLED_ShowString(80,02,"0",16,1);OLED_ShowNum(88,02,Countdown_Sec,1,16,1);}
				else{OLED_ShowNum(80,02,Countdown_Sec,2,16,1);}
				
			}
			
				
		}
		else if(Menu_state==24)//���ý���
		{
			if(KeyNum==Key1_Single_Click||KeyNum==Key1_Long_Click)
			{
				if(--MenuSet_flag<0){MenuSet_flag=2;}
			}
			if(KeyNum==Key2_Single_Click||KeyNum==Key2_Long_Click)
			{
				if(++MenuSet_flag>2){MenuSet_flag=0;}
			}
			
			if(KeyNum==Key3_Single_Click)
			{
				if(MenuSet_flag==0){MenuSet_state=6;}//DS1302ʱ������
				else if(MenuSet_flag==1){MenuSet_state=8;}//��������
				else if(MenuSet_flag==2){MenuSet_state=10;}//��������
				Menu_state+=MenuSet_state;
				KeyNum=0;
				OLED_Clear();
			}
		}
	}
	if(Menu_state==30||Menu_state==32||Menu_state==34)//�����˵�����
	{
		if(Menu_state==30)
		{	//����DS1302ʱ��
			TimeSetting=1;
			if(KeyNum==Key1_Single_Click||KeyNum==Key1_Long_Click)
			{
				DS1302_Time[TimeSelect]++;
				if(DS1302_Time[0]>99){DS1302_Time[0]=0;}//��+
				if(DS1302_Time[1]>12){DS1302_Time[1]=1;}//��+
				if(DS1302_Time[1]==1||DS1302_Time[1]==3||DS1302_Time[1]==5||DS1302_Time[1]==7||
					 DS1302_Time[1]==8||DS1302_Time[1]==10||DS1302_Time[1]==12)
				{//����+
					if(DS1302_Time[2]>31){DS1302_Time[2]=1;}
				}
				else if(DS1302_Time[1]==4 || DS1302_Time[1]==6 || DS1302_Time[1]==9 || DS1302_Time[1]==11)
				{//С��+
					if(DS1302_Time[2]>30){DS1302_Time[2]=1;}
				}
				else if(DS1302_Time[1]==2)
				{//�Ƿ�����
					if(DS1302_Time[0]%4==0){if(DS1302_Time[2]>29){DS1302_Time[2]=1;}}
					else{if(DS1302_Time[2]>28){DS1302_Time[2]=1;}}
				}
				if(DS1302_Time[3]>23){DS1302_Time[3]=0;}//ʱ
				if(DS1302_Time[4]>59){DS1302_Time[4]=0;}//��
				if(DS1302_Time[5]>59){DS1302_Time[5]=0;}//��
			}
			else if(KeyNum==Key2_Single_Click||KeyNum==Key2_Long_Click)
			{
				DS1302_Time[TimeSelect]--;
				if(DS1302_Time[0]<0){DS1302_Time[0]=99;}//��
				if(DS1302_Time[1]<1){DS1302_Time[1]=12;}//��
				
				if(DS1302_Time[1]==1||DS1302_Time[1]==3||DS1302_Time[1]==5||DS1302_Time[1]==7|| 
					 DS1302_Time[1]==8||DS1302_Time[1]==10||DS1302_Time[1]==12)
				{//����
					if(DS1302_Time[2]<1){DS1302_Time[2]=31;}
				}
				else if(DS1302_Time[1]==4 || DS1302_Time[1]==6 || DS1302_Time[1]==9 || DS1302_Time[1]==11)
				{//С��
					if(DS1302_Time[2]<1){DS1302_Time[2]=30;}
				}
				else if(DS1302_Time[1]==2)//2��
				{//�Ƿ�����
					if(DS1302_Time[0]%4==0)
					{
						if(DS1302_Time[2]<1){DS1302_Time[2]=29;}
					}
					else
					{
						if(DS1302_Time[2]<1){DS1302_Time[2]=28;}
					}
				}
				if(DS1302_Time[3]<0){DS1302_Time[3]=23;}//ʱ
				if(DS1302_Time[4]<0){DS1302_Time[4]=59;}//��
				if(DS1302_Time[5]<0){DS1302_Time[5]=59;}//��
			}
			if(KeyNum==Key3_Single_Click){TimeSelect++;TimeSelect%=6;}
			if(KeyNum==Key3_Long_Click)
			{
				Menu_state-=MenuSet_state;
				if(TimeSetting==1){TimeSetting=0;DS1302_SetTime();}
				OLED_Clear();
				OLED_Background24();
			}
		}
		else if(Menu_state==32)
		{
			OLED_SetVolume();//��������
			if((KeyNum==Key1_Single_Click||KeyNum==Key1_Long_Click)&&Busy_Music==1)
			{
				Volume++;
				UART2_SendHex(Volume_plus,sizeof(Volume_plus));
				Volume%=31;
			}
			else if((KeyNum==Key2_Single_Click||KeyNum==Key2_Long_Click)&&Busy_Music==1)
			{
				Volume--;
				UART2_SendHex(Volume_down,sizeof(Volume_down));
				
				if(Volume<0)
				Volume=30;
			}
			UART2_SendHex(Volume_play1, sizeof(Volume_play1));
			OLED_ShowNum(80,0,Volume,2,16,0);
		}
		else
		{
			Menu_Lock(KeyNum);
		}
			
		if(KeyNum==Key3_Double_Click)
		{//������һ��
			Menu_state-=MenuSet_state;
			if(TimeSetting==1){TimeSetting=0;}
			if(bLock_Set==1){bLock_Set=0;cLockSelect=0;}
			OLED_Clear();
			OLED_Background24();
		}
	}
}

void Secondary_Menu(u8 mode,u8 KeyNum)
{
	switch(mode)
	{
		case 20:OLED_Background20();break;//�������
		case 22:OLED_Background22();break;//����ʱ��
		case 24:OLED_Background24();break;//��������
	}
	if(KeyNum==Key3_Double_Click)
	{//������һ��
		Menu_state-=10;OLED_Clear();OLED_Background1(Menu_state);
		if(Menu_state==12){Countdown_select=0;}
	}
}

void Menu_Lock(u8 KeyNum)
{
	//��ʾ����
	if(KeyNum == Key1_Single_Click) {OLED_ShowString(0,6,"K1S",8,1);}
	if(KeyNum == Key1_Double_Click) {OLED_ShowString(0,6,"K1D",8,1);}
	if(KeyNum == Key1_Long_Click) 	{OLED_ShowString(0,6,"K1L",8,1);}
	
	if(KeyNum == Key2_Single_Click) {OLED_ShowString(0,6,"K2S",8,1);}
	if(KeyNum == Key2_Double_Click) {OLED_ShowString(0,6,"K2D",8,1);}
	if(KeyNum == Key2_Long_Click) 	{OLED_ShowString(0,6,"K2L",8,1);}
																
	if(KeyNum == Key3_Single_Click) {OLED_ShowString(0,6,"K3S",8,1);}
	if(KeyNum == Key3_Double_Click) {OLED_ShowString(0,6,"K3D",8,1);}
	if(KeyNum == Key3_Long_Click) 	{OLED_ShowString(0,6,"K3L",8,1);}
	
	if(Menu_state==0)
	{
		Code_Input(KeyNum);
		if(KeyNum==Key3_Long_Click)
		{
			if(nLockNum==nLockNum_Set)
			{
				bLock = 1;
				cLockSelect=0;
				Menu_state = 10;
				nLockNum=0;
				OLED_Clear();		
				OLED_Background1(Menu_state);
			}
		}
	}
	if(Menu_state==34)
	{
		bLock_Set=1;
		Code_Input(KeyNum);
		if(KeyNum==Key3_Long_Click)
		{
			cLockSelect=0;
			OLED_Clear();
			Menu_state-=10;
			
			nLockNum_Set=nLockNum;
			IAP_EraseSector(0);//����������һ������512�ֽ�
			EEPROM_site=5;
			IAP_ProgramByte(0,nLockNum_Set/256);
			IAP_ProgramByte(1,nLockNum_Set);
			IAP_ProgramByte(2,Countdown_Hour);
			IAP_ProgramByte(3,Countdown_Min);
			IAP_ProgramByte(4,Countdown_Sec);
			
		}
	}	
}

void Code_Input(u8 KeyNum)
{
	char cCode[4];
	
	cCode[0]=nLockNum/1000;
	cCode[1]=nLockNum/100%10;	
	cCode[2]=nLockNum/10%10;	
	cCode[3]=nLockNum%10;	
	
	if(KeyNum==Key1_Single_Click||KeyNum==Key1_Long_Click)
	{
		if(++cCode[cLockSelect]>9){cCode[cLockSelect]=0;}
		nLockNum=cCode[0]*1000+cCode[1]*100+cCode[2]*10+cCode[3];
	}
	if(KeyNum==Key2_Single_Click||KeyNum==Key2_Long_Click)
	{
		if(--cCode[cLockSelect]<0){cCode[cLockSelect]=9;}
		nLockNum=cCode[0]*1000+cCode[1]*100+cCode[2]*10+cCode[3];
	}
	
	if(KeyNum==Key3_Single_Click)
	{
		if(++cLockSelect>3){cLockSelect=0;}
	}
	OLED_Lock();
}	