#include <STC12C5A60S2.H>
#include "OLED.H"
#include "OLEDFONT.H"
#include "OLEDBMP.H"
#include "IIC.H"
#include "DS1302.H"
#include <stdio.h>
#include <intrins.h>
#include <stdarg.h>

u8 (*Ezk_1)[6]  = F6x8;
u8 (*Ezk_2)[16] = F8x16;
u8 (*Czk_1)[32]  = Hzk16x16;
u8 (*Czk_2)[24]  = Hzk12x12;

void OLED_Init(void)
{
	OLED_WR_Byte(0xAE,OLED_CMD);//--display off
	OLED_WR_Byte(0x00,OLED_CMD);//---设置显示位置—列低地址
	OLED_WR_Byte(0x10,OLED_CMD);//---设置显示位置—列高地址 
	OLED_WR_Byte(0x40,OLED_CMD);//--set start line address  
	OLED_WR_Byte(0xB0,OLED_CMD);//--set page address
	OLED_WR_Byte(0x81,OLED_CMD); // contract control
	OLED_WR_Byte(0xFF,OLED_CMD);//--128   
	OLED_WR_Byte(0xA1,OLED_CMD);//set segment remap 
	OLED_WR_Byte(0xA6,OLED_CMD);//--normal / reverse
	OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
	OLED_WR_Byte(0x3F,OLED_CMD);//--1/32 duty
	OLED_WR_Byte(0xC8,OLED_CMD);//Com scan direction
	OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset
	OLED_WR_Byte(0x00,OLED_CMD);//	
	OLED_WR_Byte(0xD5,OLED_CMD);//set osc division
	OLED_WR_Byte(0x80,OLED_CMD);//	
	OLED_WR_Byte(0xD8,OLED_CMD);//set area color mode off
	OLED_WR_Byte(0x05,OLED_CMD);//	
	OLED_WR_Byte(0xD9,OLED_CMD);//Set Pre-Charge Period
	OLED_WR_Byte(0xF1,OLED_CMD);//	
	OLED_WR_Byte(0xDA,OLED_CMD);//set com pin configuartion
	OLED_WR_Byte(0x12,OLED_CMD);//
	OLED_WR_Byte(0xDB,OLED_CMD);//set Vcomh
	OLED_WR_Byte(0x30,OLED_CMD);//	
	OLED_WR_Byte(0x8D,OLED_CMD);//set charge pump enable
	OLED_WR_Byte(0x14,OLED_CMD);//	
	OLED_WR_Byte(0xAF,OLED_CMD);//--turn on oled panel
	
	OLED_Clear();
}
/**********************************************
// IIC Write Command
**********************************************/
void OLED_Write_IIC_Command(unsigned char IIC_Command)
{
	IIC_Start();
  Write_IIC_Byte(0x78);            //Slave address,SA0=0
	IIC_Wait_Ack();	
  Write_IIC_Byte(0x00);			//write command
	IIC_Wait_Ack();	
  Write_IIC_Byte(IIC_Command); 
	IIC_Wait_Ack();	
  IIC_Stop();
}
/**********************************************
// IIC Write Data
**********************************************/
void OLED_Write_IIC_Date(unsigned char IIC_Data)
{
	IIC_Start();
  Write_IIC_Byte(0x78);			//D/C#=0; R/W#=0
	IIC_Wait_Ack();	
  Write_IIC_Byte(0x40);			//write data
	IIC_Wait_Ack();	
  Write_IIC_Byte(IIC_Data);
	IIC_Wait_Ack();	
  IIC_Stop();
}
void OLED_WR_Byte(unsigned dat,unsigned cmd)
{
	if(cmd)
	{
		OLED_Write_IIC_Date(dat); 
	}
	else 
	{
		OLED_Write_IIC_Command(dat);
	}
}

//反显函数
void OLED_ColorTurn(u8 mode)
{
	if(mode==0)
	{
		OLED_WR_Byte(0xA6,OLED_CMD);//正常显示
  }
  if(mode==1)
  {
    OLED_WR_Byte(0xA7,OLED_CMD);//反色显示
  }
}
//屏幕旋转180度
void OLED_DisplayTurn(u8 mode)
{
    if(mode==0)
        {
            OLED_WR_Byte(0xC8,OLED_CMD);//正常显示
            OLED_WR_Byte(0xA1,OLED_CMD);
        }
    if(mode==1)
        {
            OLED_WR_Byte(0xC0,OLED_CMD);//反转显示
            OLED_WR_Byte(0xA0,OLED_CMD);
        }
}
//坐标设置
void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 
	OLED_WR_Byte(0xb0+y,OLED_CMD);
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
	OLED_WR_Byte((x&0x0f),OLED_CMD); 
}   	  
//开启OLED显示    
void OLED_Display_On(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
	OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
	OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}
//关闭OLED显示     
void OLED_Display_Off(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
	OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
	OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}		   			 
//清屏函数,清完屏,整个屏幕是黑色的!和没点亮一样!!!	  
void OLED_Clear(void)  
{  
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //设置页地址（0~7）
		OLED_WR_Byte (0x00,OLED_CMD);      //设置显示位置—列低地址
		OLED_WR_Byte (0x10,OLED_CMD);      //设置显示位置—列高地址   
		for(n=0;n<128;n++)OLED_WR_Byte(0,OLED_DATA); 
	} //更新显示
}
void OLED_On(void)  
{  
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //设置页地址（0~7）
		OLED_WR_Byte (0x00,OLED_CMD);      //设置显示位置—列低地址
		OLED_WR_Byte (0x10,OLED_CMD);      //设置显示位置—列高地址   
		for(n=0;n<128;n++)OLED_WR_Byte(1,OLED_DATA); 
	} //更新显示
}

//在指定位置显示一个字符,包括部分字符
//x:0~127
//y:0~63			 
//sizey:选择字体 8 
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 sizey,u8 mode)
{
	u8 c=0,sizex=sizey/2;
	u16 i=0,size1;
	if(sizey==8)size1=6;
	else size1=(sizey/8+((sizey%8)?1:0))*(sizey/2);
	c=chr-' ';//得到偏移后的值
	OLED_Set_Pos(x,y);
	if(mode==1)
	{
		for(i=0;i<size1;i++)
    {
        if(i%sizex==0&&sizey!=8) OLED_Set_Pos(x,y++);
        if(sizey==8) OLED_WR_Byte(Ezk_1[c][i],OLED_DATA);//6X8字号
        else if(sizey==16) OLED_WR_Byte(Ezk_2[c][i],OLED_DATA);//8x16字号
//        else if(sizey==xx) OLED_WR_Byte(asc2_xxxx[c][i],OLED_DATA);//用户添加字号
        else return;
    }
	}
	else if(mode==0)
	{
		for(i=0;i<size1;i++)
    {
        if(i%sizex==0&&sizey!=8) OLED_Set_Pos(x,y++);
        if(sizey==8) OLED_WR_Byte(~Ezk_1[c][i],OLED_DATA);//6X8字号
        else if(sizey==16) OLED_WR_Byte(~Ezk_2[c][i],OLED_DATA);//8x16字号
//        else if(sizey==xx) OLED_WR_Byte(asc2_xxxx[c][i],OLED_DATA);//用户添加字号
        else return;
    }
	}
    
}
//m^n函数
u32 oled_pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;//计算    
	return result;//有返回值的子函数
}	

//显示数字
//x,y :起点坐标	 
//len :数字的位数
//sizey:字体大小
//num:数值(0~4294967295);	 		  
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 sizey,u8 mode)
{
	u8 t,temp,m=0;
	u8 enshow=0;
	if(sizey==8)m=2;
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_ShowChar(x+(sizey/2+m)*t,y,' ',sizey,mode);
				continue;
			}else enshow=1;
		}OLED_ShowChar(x+(sizey/2+m)*t,y,temp+'0',sizey,mode);
	}
} 

//显示一个字符号串
//显示的横坐标、纵坐标、字符串、字体大小
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 sizey,u8 mode)
{
	u8 j=0;
	while (chr[j]!='\0')
	{
		OLED_ShowChar(x,y,chr[j++],sizey,mode);
		if(sizey==8)x+=6;
		else x+=sizey/2;
	}
}
//显示汉字，可显示取模后的任意点阵
//参数：显示的横坐标、纵坐标、汉字库中文字的序号、汉字尺寸（默认16x16）mode：0反色 1正常
//显示汉字，可显示取模后的任意点阵
//参数：显示的横坐标、纵坐标、汉字库中文字的序号、汉字尺寸（默认16x16）
void OLED_ShowChinese(u8 x,u8 y,u8 no,u8 sizey,u8 mode)
{
    u16 i,size1=(sizey/8+((sizey%8)?1:0))*sizey;
		if(mode==1)
		{
			for(i=0;i<size1;i++)
			{
        if(i%sizey==0) OLED_Set_Pos(x,y++);
        if(sizey==16) OLED_WR_Byte(Czk_1[no][i],OLED_DATA);//16x16字号
				else if(sizey==12) OLED_WR_Byte(Czk_2[no][i],OLED_DATA);//用户添加字号
//        else if(sizey==xx) OLED_WR_Byte(xxx[no][i],OLED_DATA);//用户添加字号
        else return;
			}  
		}
    else if(mode==0)
		{
			for(i=0;i<size1;i++)
			{
        if(i%sizey==0) OLED_Set_Pos(x,y++);
        if(sizey==16) OLED_WR_Byte(~Czk_1[no][i],OLED_DATA);//16x16字号
				else if(sizey==12) OLED_WR_Byte(~Czk_2[no][i],OLED_DATA);//用户添加字号
//        else if(sizey==xx) OLED_WR_Byte(xxx[no][i],OLED_DATA);//用户添加字号
        else return;
			}  
		}
}

//显示图片
//x,y显示坐标
//sizex,sizey,图片长宽
//BMP：要显示的图片
void OLED_DrawBMP(u8 x,u8 y,u8 sizex,u8 sizey,u8 BMP[])
{
	u16 j=0;
	u8 i,m;
	sizey=sizey/8+((sizey%8)?1:0);
	for(i=0;i<sizey;i++)
	{
		OLED_Set_Pos(x,i+y);
		for(m=0;m<sizex;m++)
		{
			OLED_WR_Byte(BMP[j++],OLED_DATA);
		}
	}
}
//DS1302时间显示
void OLED_TimeShow(bit setting,u8 TimeSelect)
{
	u8 i,x,y;
	bit flag;
	
	if(setting==0)
	{
		OLED_ShowChar( 80,6,'-',8,1);
		OLED_ShowChar(104,6,'-',8,1);
		OLED_ShowChar( 80,7,':',8,1);
		OLED_ShowChar(104,7,':',8,1);
	
		for(i=0;i<6;i++)
		{
			x=64+24*(i%3);//确定x坐标
			y=6+((i/3)>=1);//确定是在第6行还是第7行显示
			if(DS1302_Time[i]>=10){OLED_ShowNum(x,y,DS1302_Time[i],2,8,1);}
			else
			{//小于10补零
				OLED_ShowNum(x,y,0,1,8,1);
				OLED_ShowNum(x+6,y,DS1302_Time[i],1,8,1);
			}
		}
	}
	else if(setting==1)
	{
		OLED_ShowChinese(80,6,21,16,1);
		OLED_ShowChar(40,2,'-',16,1);
		OLED_ShowChar(80,2,'-',16,1);
		OLED_ShowChar(40,4,':',16,1);
		OLED_ShowChar(80,4,':',16,1);
	
		for(i=0;i<6;i++)
		{
			if(i==TimeSelect){flag=0;}
			else{flag=1;}
			x=16+40*(i%3);//确定x坐标
			y=2+2*((i/3)>=1);//确定是在第6行还是第7行显示
			if(DS1302_Time[i]>=10){OLED_ShowNum(x,y,DS1302_Time[i],2,16,flag);}
			else
			{//小于10补零
				OLED_ShowNum(x,y,0,1,16,flag);
				OLED_ShowNum(x+8,y,DS1302_Time[i],1,16,flag);
			}
		}
	}
	
}

//秒表计时显示
void OLED_StopwatchShow()
{
	
	if(Min<10){OLED_ShowString(32,4,"0",8,1);OLED_ShowNum(38,4,Min,1,8,1);}//分
	else{OLED_ShowNum(32,4,Min,2,8,1);}
	OLED_ShowChar(46,4,':',8,1);
	
	if(Sec<10){OLED_ShowString(54,4,"0",8,1);OLED_ShowNum(60,4,Sec,1,8,1);}//秒
	else{OLED_ShowNum(54,4,Sec,2,8,1);}
	OLED_ShowChar(68,4,'.',8,1);
	
	if(Msec<10){OLED_ShowString(76,4,"0",8,1);OLED_ShowNum(82,4,Msec,1,8,1);}//毫秒
	else{OLED_ShowNum(76,4,Msec,2,8,1);}
	
}

void OLED_Background1(u8 mode)//背景显示1-----功能：主菜单
{
	if(mode==10)
	{
		OLED_ShowChinese(00,00,00,16,0);//秒
		OLED_ShowChinese(16,00,01,16,0);//表
		OLED_ShowChinese(00,02,02,16,1);//时
		OLED_ShowChinese(16,02,03,16,1);//控
		OLED_ShowChinese(00,04,10,16,1);//设
		OLED_ShowChinese(16,04,11,16,1);//置
	}
	if(mode==12)
	{
		OLED_ShowChinese(00,00,00,16,1);//秒
		OLED_ShowChinese(16,00,01,16,1);//表
		OLED_ShowChinese(00,02,02,16,0);//时
		OLED_ShowChinese(16,02,03,16,0);//控
		OLED_ShowChinese(00,04,10,16,1);//设
		OLED_ShowChinese(16,04,11,16,1);//置
	}
	if(mode==14)
	{
		OLED_ShowChinese(00,00,00,16,1);//秒
		OLED_ShowChinese(16,00,01,16,1);//表
		OLED_ShowChinese(00,02,02,16,1);//时
		OLED_ShowChinese(16,02,03,16,1);//控
		OLED_ShowChinese(00,04,10,16,0);//设
		OLED_ShowChinese(16,04,11,16,0);//置
	}
}               



void OLED_Background20()//背景显示2_1--------功能：秒表
{
	OLED_ShowChinese(00,00,12,16,1);//按
	OLED_ShowChinese(16,00,13,16,1);//下
	OLED_ShowString( 32,0,"key1",16,1);
	OLED_ShowChinese(64,00,14,16,1);//以
	OLED_ShowChinese(80,00,04,16,1);//开
	OLED_ShowChinese(96,00,05,16,1);//始
}							
void OLED_Background22()//背景显示2_2--------功能：设置时间控制
{
	OLED_ShowChinese(00,00,15,16,1);//请
	OLED_ShowChinese(16,00,10,16,1);//设
	OLED_ShowChinese(32,00,11,16,1);//置
	OLED_ShowChinese(48,00,02,16,1);//时
	OLED_ShowChinese(64,00,16,16,1);//间
	OLED_ShowChinese(32,02,02,16,1);//时
	OLED_ShowChinese(64,02, 9,16,1);//分
	OLED_ShowChinese(96,02,00,16,1);//秒
}
void OLED_Background24()//背景显示2_3--------功能：外设设置
{	
	bit bSelect0;
	bit	bSelect1;
	bit	bSelect2;
	if(MenuSet_flag==0){bSelect0=0;bSelect1=1;bSelect2=1;}
	if(MenuSet_flag==1){bSelect0=1;bSelect1=0;bSelect2=1;}
	if(MenuSet_flag==2){bSelect0=1;bSelect1=1;bSelect2=0;}
	
	OLED_ShowChinese(00,00,02,16,bSelect0);//时
	OLED_ShowChinese(16,00,16,16,bSelect0);//
	OLED_ShowChinese(32,00,10,16,bSelect0);//设
	OLED_ShowChinese(48,00,11,16,bSelect0);//置
	
	
	OLED_ShowChinese(00,02,17,16,bSelect1);//音
	OLED_ShowChinese(16,02,18,16,bSelect1);//量
	OLED_ShowChinese(32,02,10,16,bSelect1);//设
	OLED_ShowChinese(48,02,11,16,bSelect1);//置
	
	OLED_ShowChinese(00,04,24,16,bSelect2);//音
	OLED_ShowChinese(16,04,25,16,bSelect2);//量
	OLED_ShowChinese(32,04,10,16,bSelect2);//设
	OLED_ShowChinese(48,04,11,16,bSelect2);//置
	
}	

void OLED_SetVolume()
{
	OLED_ShowChinese(00,00,17,16,1);//音
	OLED_ShowChinese(16,00,18,16,1);//量
	OLED_ShowChinese(32,00,19,16,1);//等
	OLED_ShowChinese(48,00,20,16,1);//级
	OLED_ShowChar( 64,00,':',16,1);
}

void OLED_Lock()
{
	u8	i;
	u8	uSelect[4];
	OLED_ShowChinese(00,00,15,16,1);//请
	OLED_ShowChinese(48,00,24,16,1);//密
	OLED_ShowChinese(64,00,25,16,1);//码
	if(bLock_Set==0)
	{
		OLED_ShowChinese(16,00,22,16,1);//输
		OLED_ShowChinese(32,00,23,16,1);//入
	}
	else if(bLock_Set==1)
	{
		OLED_ShowChinese(16,00,26,16,1);//修
		OLED_ShowChinese(32,00,27,16,1);//改
	}
	
	
	
	for(i=0;i<4;i++)
	{
		if(i==cLockSelect){uSelect[i]=0;}
		else{uSelect[i]=1;}
		
	}
	OLED_ShowNum(00,2,nLockNum/1000,2,16,uSelect[0]);
	OLED_ShowNum(16,2,nLockNum/100%10,2,16,uSelect[1]);
	OLED_ShowNum(32,2,nLockNum/10%10,2,16,uSelect[2]);
	OLED_ShowNum(48,2,nLockNum%10,2,16,uSelect[3]);
	
}