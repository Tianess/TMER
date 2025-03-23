#ifndef __PCA_H__ 
#define __PCA_H__

#define fosc 11059200L
#define t100hz (fosc/12/100)

void PCA0_Init(void);
extern u32 PCA0_cnt;


#endif