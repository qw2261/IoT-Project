#ifndef __Beep_H
#define __Beep_H
#include "stm32f4xx.h"

#define  PassiveBeep              	//无源蜂鸣器，由端口PWM波驱动
//#define  PositiveBeep							//有源蜂鸣器

#define  Beep_PIN											GPIO_Pin_6
#define  Beep_GPIO_PORT								GPIOC
#define  Beep_GPIO_CLK								RCC_AHB1Periph_GPIOC

#ifdef   PassiveBeep
#define	 Beep_TIMER 							  	TIM8
#define  Beep_TIMER_CLK						 		RCC_APB2Periph_TIM8
#define  Beep_TIMER_PORT							RCC_AHB1Periph_GPIOC   
#define  Beep_TIMER_GPIO_PORT					GPIOC
#define  Beep_TIMER_PIN_SOURCE				GPIO_PinSource6
#define  Beep_TIMER_AF								GPIO_AF_TIM8
#define  Default_ARR             			42-1       
#define  Default_PSC		 							602-1        //变频改变音色  
#define  Beep_RCC_APBxPeriphClockCmd  RCC_APB2PeriphClockCmd
#define  Beep_TIM_OCXInit							TIM_OC1Init
#define  Beep_TIM_OCXPreloadConfig		TIM_OC1PreloadConfig
#define  Beep_TIM_SetCompareX					TIM_SetCompare1
#endif


typedef enum
{
	Do_L,Re_L,Mi_L,Fa_L,Sol_L,La_L,Si_L,
	Do,Re,Mi,Fa,Sol,La,Si,
	Do_H,Re_H,Mi_H,Fa_H,Sol_H,La_H,Si_H,
	Nop
} BeepTuneTypedef;

void Beep_Init();
void Beep_On(void);
void Beep_Off(void);
void Beep_Toggle(void);
void Beep_On_Tune(BeepTuneTypedef tune);
#endif
