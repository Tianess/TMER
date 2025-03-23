#include <STC12C5A60S2.H>


#ifndef __OLED_H
#define __OLED_H			  	 
 
#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据
#define OLED_MODE 0

#define SIZE 16
#define XLevelL		0x02
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	    						

extern u8	Msec,Sec,Min;
extern char	MenuSet_flag;
extern u8		MenuSet_state;
extern bit	TimeSetting;

extern	bit		bLock;
extern	bit		bLock_Set;
extern	u16		nLockNum;
extern	char		cLockSelect;

//OLED控制用函数
void OLED_WR_Byte(unsigned dat,unsigned cmd);//写数据 
void OLED_Display_On(void); //显示
void OLED_Display_Off(void);  //关闭显示 							   		    
void OLED_Init(void); //初始化
void OLED_Clear(void); //清屏;
void OLED_ColorTurn(u8 mode);//反色显示
void OLED_DisplayTurn(u8 mode);//屏幕旋转
void OLED_Refresh_Gram(void);
void OLED_DrawPoint(u8 x,u8 y,u8 t);//画点（x为x轴坐标,y为y坐标）
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);//x1,y1,x2,y2 区域的对角坐标
void OLED_Set_Pos(unsigned char x, unsigned char y); //设定坐标
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 sizey,u8 mode); //显示字符
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 sizey,u8 mode);//显示数字
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 sizey,u8 mode); //显示字符串
void OLED_ShowChinese(u8 x,u8 y,u8 no,u8 sizey,u8 mode); //显示中文字库
void fill_picture(unsigned char fill_Data); //显示图片
void OLED_Write_IIC_Command(unsigned char IIC_Command);//写指令
void OLED_Write_IIC_Date(unsigned char IIC_Data);//写数据
u32 oled_pow(u8 m,u8 n);
//用户定义
void OLED_Background1(u8 mode);//一级菜单
void OLED_Background20();//二级菜单功能1
void OLED_Background22();//二级菜单功能2
void OLED_Background24();//二级菜单功能3
void OLED_SetVolume();
void OLED_TimeShow(bit setting,u8 TimeSelect);//DS1302时间展示
void OLED_StopwatchShow();//秒表时间显示
void OLED_Lock();





#endif  