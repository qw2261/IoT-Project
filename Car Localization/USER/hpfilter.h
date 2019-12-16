#ifndef _HP_FILTER
#define _HP_FILTER
#include "stm32f4xx.h"
#include "arm_math.h"

#define NUMSTAGES             5  //¶þ½×ÂË²¨Æ÷¸öÊý

extern float testin[1024];
extern float testout[1024];


extern  arm_biquad_cascade_df2T_instance_f32 SFilter;

extern float32_t  IIRState[2*NUMSTAGES];


extern  float32_t IIRCoeffsHP[5*NUMSTAGES];



void arm_iir_f32_hp_Init();

void arm_iir_f32_hp(float32_t *SignalIn,float32_t *SignalOut,u32 Sample_Lenth);


#endif
