#include <STC12C5A60S2.H>
#include "PCA.H"
#include "main.h"

void PCA0_Init(void)
{
	CCON=0;		   //cf cr ccf1 ccf0为0
	CL=0;		//pca计数值初始为0
	CH=0;
	CMOD=0X00;	 //CIDL=0、SYSclk/12、ECF = 0
	PCA0_cnt=t100hz;  //0.01s
	CCAP0L=PCA0_cnt;	//给比较寄存器赋值
	CCAP0H=PCA0_cnt>>8;
	PCA0_cnt+=t100hz;	 //value加一倍
	CCAPM0=0x49;	  //ecmo0 mat0 eccf0为1；ECOM0＝ 1时，允许比较器功能；匹配将置位CCON寄存；使能CCF0中
	CR=1;  //起动 PCA计数器阵列计数，CCON寄存器的一位
	
}

//模板
//void pcs_ds() interrupt 7
//{
//	CCF0=0;		//中断标志位清0
//	CCAP0L=value;	  //比较寄存器程序赋值(比上次加1倍)
//	CCAP0H=value>>8;
//}