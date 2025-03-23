#include <STC12C5A60S2.H>
#include "KEY.H"
#include "main.h"

unsigned char Key(void)
{
	unsigned char Temp;						//中间变量Temp，便于赋值一次消零
	Temp=Key_KeyNumber;
	Key_KeyNumber=0;
	return Temp;
}

unsigned char KeyData(void)						//读取动态按键变化
{
	unsigned char KeyNumber=0;
	
	if(KEY1==0){KeyNumber=11;}
	if(KEY2==0){KeyNumber=21;}
	if(KEY3==0){KeyNumber=31;}
	
	return KeyNumber;				//返回按键的值
}

void Loop_Key(void)
{
	LastKey=NowKey;							//LastKey：上一次的按键值
	NowKey=KeyData();						//NowKey：当前的按键值

	if(LastKey)								//当按键按下时开始计时
	{	KeyNumber=LastKey;
		KeyTime++;
		if(KeyTime<25 && NowKey==0)			//如果按键的时间小于250ms
		{	
			KeyTime=0;
			OnceKey++;						//OnceKey每松手一次加1
		}
		else if(KeyTime>=25 && NowKey)		//如果按键时间大于250ms且现按键还在按下
		{
			
			if(LastKey==11){Key_KeyNumber=13;}	//给按键赋值
			if(LastKey==21){Key_KeyNumber=23;}
			if(LastKey==31){Key_KeyNumber=33;}
			
		}
		if(NowKey==0 && LastKey && KeyTime>=25)//防止长按后立即被当成短按再次赋值
		{
			Key_KeyNumber=0;KeyTime=0;
		}

	}
}
