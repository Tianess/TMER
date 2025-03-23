#ifndef __MENU_H
#define __MENU_H

extern	u32		Menu_state;
extern	char	MenuSet_flag;
extern	u8		MenuSet_state;

extern	u8		Msec,Sec,Min;
extern 	bit		Stopwatchflag;
extern	char	Countdown_Hour,Countdown_Min,Countdown_Sec;
extern	char	Countdown_select;
extern	bit		Countdownflag;
extern	u8		Countdowntimer;

extern	char	DS1302_Time[];
extern	u8		TimeSelect;

extern	char	Volume;
extern	u8 code	Volume_plus[];
extern	u8 code	Volume_down[];
extern	u8 code	Volume_play1[];

extern	bit		bLock;
extern	u16		nLockNum;
extern	u16   nLockNum_Set;
extern	char	cLockSelect;

extern	u16		EEPROM_site;
void 		Secondary_Menu(u8 mode,u8 KeyNum);//¶þ¼¶²Ëµ¥
void 		Menu(u8 KeyNum);
void		Menu_Lock(u8 KeyNum);
void		Code_Input(u8 KeyNum);


#endif