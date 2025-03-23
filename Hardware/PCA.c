#include <STC12C5A60S2.H>
#include "PCA.H"
#include "main.h"

void PCA0_Init(void)
{
	CCON=0;		   //cf cr ccf1 ccf0Ϊ0
	CL=0;		//pca����ֵ��ʼΪ0
	CH=0;
	CMOD=0X00;	 //CIDL=0��SYSclk/12��ECF = 0
	PCA0_cnt=t100hz;  //0.01s
	CCAP0L=PCA0_cnt;	//���ȽϼĴ�����ֵ
	CCAP0H=PCA0_cnt>>8;
	PCA0_cnt+=t100hz;	 //value��һ��
	CCAPM0=0x49;	  //ecmo0 mat0 eccf0Ϊ1��ECOM0�� 1ʱ������Ƚ������ܣ�ƥ�佫��λCCON�Ĵ棻ʹ��CCF0��
	CR=1;  //�� PCA���������м�����CCON�Ĵ�����һλ
	
}

//ģ��
//void pcs_ds() interrupt 7
//{
//	CCF0=0;		//�жϱ�־λ��0
//	CCAP0L=value;	  //�ȽϼĴ�������ֵ(���ϴμ�1��)
//	CCAP0H=value>>8;
//}