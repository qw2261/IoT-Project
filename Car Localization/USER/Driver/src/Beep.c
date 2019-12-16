#include "Beep.h"

u16 Beep_Tune_Parameters[]=
{
	4545,4048,3610,3401,3030,2703,2410,   //Do_L,Re_L,Mi_L,Fa_L,Sol_L,La_L,Si_L,
	2273,2024,1805,1704,1517,1353,1203,		//Do,Re,Mi,Fa,Sol,La,Si,
	1136,1012,901,851,758,677,602,				//Do_H,Re_H,Mi_H,Fa_H,Sol_H,La_H,Si_H,
	0                                  		//Nop
};


void Beep_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	#ifdef PassiveBeep
	/* TIMx≥ı ºªØ */
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	Beep_RCC_APBxPeriphClockCmd(Beep_TIMER_CLK,ENABLE);  	  
	RCC_AHB1PeriphClockCmd(Beep_TIMER_PORT, ENABLE); 	
	
	GPIO_PinAFConfig(Beep_TIMER_GPIO_PORT,Beep_TIMER_PIN_SOURCE,Beep_TIMER_AF);

	GPIO_InitStructure.GPIO_Pin = Beep_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(Beep_GPIO_PORT,&GPIO_InitStructure);
	GPIO_ResetBits(Beep_GPIO_PORT,Beep_PIN);
	 
	/*Beep TimerInit*/
	TIM_TimeBaseInitStructure.TIM_Period = Default_ARR; 	
	TIM_TimeBaseInitStructure.TIM_Prescaler= Default_PSC;  
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; 
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	TIM_TimeBaseInit(Beep_TIMER,&TIM_TimeBaseInitStructure);

  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	
	Beep_TIM_OCXInit(Beep_TIMER, &TIM_OCInitStructure);
	
  TIM_CtrlPWMOutputs(Beep_TIMER,ENABLE);
	 
	Beep_TIM_OCXPreloadConfig(Beep_TIMER, TIM_OCPreload_Enable);
  TIM_ARRPreloadConfig(Beep_TIMER,ENABLE);
	
	TIM_Cmd(Beep_TIMER, ENABLE);  
	
  Beep_TIM_SetCompareX(Beep_TIMER,0);									
  #endif	
	
	#ifdef PositiveBeep
	RCC_AHB1PeriphClockCmd(Beep_GPIO_CLK,ENABLE);

	GPIO_InitStructure.GPIO_Pin = Beep_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(Beep_GPIO_PORT,&GPIO_InitStructure);
	GPIO_SetBits(Beep_GPIO_PORT,Beep_PIN);
	
	#endif

}
void Beep_On(void)
{
	#ifdef PositiveBeep
	  GPIO_ResetBits(Beep_GPIO_PORT,Beep_PIN);
	#endif 
	#ifdef PassiveBeep
	  Beep_TIM_SetCompareX(Beep_TIMER,10);
	#endif
}
void Beep_Off(void)
{
	#ifdef PositiveBeep
		GPIO_SetBits(Beep_GPIO_PORT,Beep_PIN);
	#endif 
	#ifdef PassiveBeep
	  Beep_TIM_SetCompareX(Beep_TIMER,0);
	#endif

}

#ifdef PositiveBeep
void Beep_Toggle(void)
{
	GPIO_ToggleBits(Beep_GPIO_PORT,Beep_PIN);
}
#endif 

#ifdef PassiveBeep

void Beep_On_Tune(BeepTuneTypedef tune)
{
	TIM_PrescalerConfig(Beep_TIMER,Beep_Tune_Parameters[tune],TIM_PSCReloadMode_Update);
	Beep_TIM_SetCompareX(Beep_TIMER,10);
}
#endif

