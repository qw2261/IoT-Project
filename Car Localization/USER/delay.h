#ifndef _DELAY_H
#define _DELAY_H
#include "stdint.h"
void MyDelayms(uint32_t nCount);
void MyDelayus(uint32_t nCount);
void delay_init(void);
void delay_us(uint32_t nus);//nus²»ÄÜ³¬³ö1000
#endif
