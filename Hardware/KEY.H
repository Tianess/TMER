#ifndef __KEY_H__ 
#define __KEY_H__

unsigned char Key(void);
unsigned char KeyData(void);
void Loop_Key(void);

extern u8 Key_KeyNumber,LastKey,NowKey,KeyNum,OnceKey,KeyNumber,Count;
extern u8 KeyTime;
#endif