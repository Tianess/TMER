#include <STC12C5A60S2.H>
#include <stdio.h>
#include "main.h"
#include "OLED.H"
#include "Timer0.H"
#include "PCA.H"
#include "Timer0.H"
#include "KEY.H"
#include "MENU.H"
#include "DS1302.H"
#include "UART1.H"
#include "UART2.H"
#include "EEPROM.H"

/*************界面处理相关************************************/
u32		Menu_state,Menu_vaule;
char	MenuSet_flag;
u8		MenuSet_state;
/*************按键处理相关************************************/
u8 		Key_KeyNumber,LastKey,NowKey,KeyNum,OnceKey,KeyNumber,Count;
u8		KeyTime;
u32 	PCA0_cnt;
/*************秒表处理相关***********************************/
u8		Msec,Sec,Min;
bit		Stopwatchflag;
/*************倒计时处理相关*********************************/
char	Countdown_Hour,Countdown_Min,Countdown_Sec;
char	Countdown_select;
bit		Countdownflag;
u8		Countdowntimer;
/*************串口处理相关*********************************/
bit		busy1;
bit		busy2;
u8		uart1_rx_data;
/*************音频处理相关*********************************/
const	u8 code Volume_play8[]={0x04,0xFB,0x09,0x07,0x2F,0x31,0x2F,0x38,0x2E,0x6D,0x70,0x33,0x14};//播放
const	u8 code Volume_play1[]={0x04,0xFB,0x09,0x07,0x2F,0x31,0x2F,0x31,0x2E,0x6D,0x70,0x33,0x0D};
const u8 code	Volume_plus[]={0x06,0xF9,0x01,0x02,0x02};//音量加
const u8 code	Volume_down[]={0x06,0xF9,0x01,0x03,0x03};//音量减
const u8 code	Volume_set[]={ 0x06,0xF9,0x02,0x01,0x0F,0x11};//音量默认设置15
char	Volume=15;
bit		bMusic;
/*************EEPROM处理相关**************/
u16		EEPROM_site;
/*************密码锁处理相关**************/
bit		bLock;
bit		bLock_Set;
u16		nLockNum;
u16		nLockNum_Set=1234;
char	cLockSelect;
/*************DS1302时间设定*****/
//用于存放时间,   年 月 日 时 分 秒 星期
char	DS1302_Time[7]={24,01,01,00,00,00,1};
bit		TimeSetting;
u8		TimeSelect;

void EEPROM_Init()
{
	u16		i;
	/**********EEPROM检测**********/
	for (i=0; i<512; i++)           //循环读取，直到FF，表示未写入
	{
		if (IAP_ReadByte(0+i) == 0xff)
		{
			EEPROM_site = i;
			break;
		}
	}
	if(EEPROM_site!=0)
	{
		if(EEPROM_site==509)//写满，读取，擦除重新写
		{
			Countdown_Hour	=	IAP_ReadByte(509-3);
			Countdown_Min		=	IAP_ReadByte(509-2);
			Countdown_Sec		=	IAP_ReadByte(509-1);
			IAP_EraseSector(0);//扇区擦除，一个扇区512字节
			EEPROM_site=5;
			IAP_ProgramByte(2,Countdown_Hour);
			IAP_ProgramByte(3,Countdown_Min);
			IAP_ProgramByte(4,Countdown_Sec);
		}else//未写满，正常读取
		{
			nLockNum_Set    = (IAP_ReadByte(0)<<8|IAP_ReadByte(1));
			Countdown_Hour	=	IAP_ReadByte(EEPROM_site-3);
			Countdown_Min		=	IAP_ReadByte(EEPROM_site-2);
			Countdown_Sec		=	IAP_ReadByte(EEPROM_site-1);
		}
	}
}

void main()
{	
	EEPROM_Init();
	//IAP_EraseSector(0);
	
	/* 开启单片机低压检测中断 */	
	ELVD = 1;
	PCON &= 0xdf;
	
	/* 设备初始化 */	
	OLED_Init();//OLED初始化
	OLED_Clear();//OLED清屏
	OLED_Background1(Menu_state);//显示初始菜单
	DS1302_Init();//DS1302初始化
	Timer0_Init();//定时器0初始化
	PCA0_Init();//PCA0初始化—做16位定时器
	Uart1_Init();//串口1初始化
	Uart2_Init();//串口2初始化
	
	EA=1;//打开总中断
	P4SW |= 0x30;//打开P4口
	
	
	/* LED初始化 */	
//	LED_W=0;
//	LED_B=0;
//	LED_G=0;
	LED_R=0;
	/* 继电器初始化 */	
	Relay1=1;//置1关继电器
	Relay2=1;
	UART2_SendHex(Volume_set, sizeof(Volume_set));//设置默认音量
	while(1)
	{
		if(bLock==0)
		{
			KeyNum=Key();							//读取按键键值
			Menu_Lock(KeyNum);
			//OLED_ShowNum(32,6,nLockNum_Set,4,8,1);
		}
		else if(bLock==1)
		{
			if(TimeSetting==0){DS1302_ReadTime();}//读取DS1302时间
			OLED_TimeShow(TimeSetting,TimeSelect);//检测是否修改DS1302
		
			KeyNum=Key();							//读取按键键值
		
			Menu_vaule=KeyNum+uart1_rx_data;//获取键值和蓝牙
			Menu(Menu_vaule);//进入菜单
			uart1_rx_data=0;
			OLED_ShowNum(0,7,Menu_state,2,8,1);
			OLED_ShowNum(32,7,EEPROM_site,4,8,1);
			OLED_ShowNum(32,6,nLockNum_Set,4,8,1);
			if(Menu_state==20)
			{
				OLED_StopwatchShow();//显示秒表时间
			}
			if(bMusic==1)//定时时间结束，播放音乐
			{
				UART2_SendHex(Volume_play8, sizeof(Volume_play8));//音乐播放
				bMusic=0;
			}
		}
		

	}
}



void Timer0_Routine() interrupt 1
{
	TL0 = 0x00;				//设置定时初始值10ms
	TH0 = 0xDC;	
	if(Stopwatchflag==1)//秒表计时
	{
		Msec++;
		if(Msec==100){Sec++;Msec=0;}
		if(Sec==60){Min++;Sec=0;}
	}
	if(Countdownflag==1)//倒计时
	{
		Countdowntimer++;
		Relay1=0;
		Relay2=0;
		LED_R=1;
		LED_G=0;
		if(Countdowntimer==100){Countdown_Sec--;Countdowntimer=0;}
		if(Countdown_Sec<0){Countdown_Min--;Countdown_Sec=59;}
		if(Countdown_Min<0){Countdown_Hour--;Countdown_Min=59;}
		if((Countdown_Hour==0)&&(Countdown_Min==0)&&(Countdown_Sec==0))
		{
			Countdownflag=0;
			Countdown_select=0;
			bMusic=1;
			Relay1=1;
			Relay2=1;
			LED_R=0;
			LED_G=1;
		}
	}

}	

void pcs_ds() interrupt 7
{//按键检测—长按单击双击
	static unsigned int KeyCount1;
	CCF0=0;		//中断标志位清0
	CCAP0L=PCA0_cnt;	  //比较寄存器程序赋值(比上次加1倍)
	CCAP0H=PCA0_cnt>>8;
	PCA0_cnt+=t100hz;//设置定时初始值10ms
	
	Loop_Key();

	if(OnceKey)
	{
		KeyCount1++;
		if(KeyCount1>=20)			//单击后200ms按键值判断时间
		{	KeyCount1=0;
			if(OnceKey==1)		    //按键按下1次后给按键赋值
			{OnceKey=0;KeyCount1=0;
			if(KeyNumber==11){Key_KeyNumber=11;}
			if(KeyNumber==21){Key_KeyNumber=21;}
			if(KeyNumber==31){Key_KeyNumber=31;}
			}
			else if(OnceKey==2)			//按键按下2次后给按键赋值
			{OnceKey=0;KeyCount1=0;
			if(KeyNumber==11){Key_KeyNumber=12;}
			if(KeyNumber==21){Key_KeyNumber=22;}
			if(KeyNumber==31){Key_KeyNumber=32;}
			}
		}	
	}
}
void Uart1_Isr(void) interrupt 4
{
	
	if (TI)				//检测串口1发送中断
	{
		TI = 0;			//清除串口1发送中断请求位
		busy1 =0;
	}
	if (RI)				//检测串口1接收中断
	{
		RI = 0;			//清除串口1接收中断请求位
		uart1_rx_data = SBUF-54;
	}
}

void Uart2_Isr(void) interrupt 8
{
	if (S2CON & 0x02)			//检测串口2发送中断
	{
		S2CON &= ~0x02;			//清除串口2发送中断请求位
		busy2 = 0;
	}
	if (S2CON & 0x01)			//检测串口2接收中断
	{
		S2CON &= ~0x01;			//清除串口2接收中断请求位
	}
}
void LVD_Routine(void) interrupt 6//低电压检测中断服务函数
{
		OLED_Display_Off();//关闭OLED显示，降低功耗
		
		/*将EEPROM分别写入数据*/
		IAP_ProgramByte(EEPROM_site,Countdown_Hour);
		IAP_ProgramByte(EEPROM_site+1,Countdown_Min);
		IAP_ProgramByte(EEPROM_site+2,Countdown_Sec);
		
		PCON &= 0xdf; /* 检测到低压时的标志位清零 */
}