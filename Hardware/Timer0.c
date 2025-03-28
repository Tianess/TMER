#include <STC12C5A60S2.H>
#include <Timer0.h>

void Timer0_Init(void)
{
	//AUXR |= 0x80;		//定时器时钟1T模式
	AUXR &= 0x7F;			//定时器时钟12T模式
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
//	TL0 = 0xCD;		//设置定时初值
//	TH0 = 0xD4;		//设置定时初值
	TL0 = 0x00;				//设置定时初始值
	TH0 = 0xDC;				//设置定时初始值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
	ET0 = 1;
	EA = 1;
	PT0 = 0;
}


/*定时器中断函数模板
void Timer0_Routine() interrupt 1
{
	static unsigned int T0Count;
	TL0 = 0x18;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	T0Count++;
	if(T0Count>=1000)
	{
		T0Count=0;

	}
}
*/
