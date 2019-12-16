#include "Encoder.h"
#include "globalTime.h"
#include "EncoderPara.h"

#define ENCODER_TIM_PERIOD               (0xffff)      //兼容16位,不可修改

GPIO_TypeDef * const ENC_GPIO_PORT[ENCn]={
								ENC1_GPIO_PORT,
								ENC2_GPIO_PORT,
								ENC3_GPIO_PORT,
								};

TIM_TypeDef  * const ENC_TIMER[ENCn] ={
								ENC1_TIMER,
								ENC2_TIMER,
								ENC3_TIMER,
								};
const uint32_t ENC_TIMER_CLK[ENCn] ={
								ENC1_TIMER_CLK,
								ENC2_TIMER_CLK,
								ENC3_TIMER_CLK,
								};
								

const uint32_t ENC_GPIO_CLK[ENCn] ={
								ENC1_GPIO_CLK,
								ENC2_GPIO_CLK,
								ENC3_GPIO_CLK,
								};

const uint16_t ENC_APIN[ENCn]={	
								ENC1_GPIO_PIN_A,
								ENC2_GPIO_PIN_A,
								ENC3_GPIO_PIN_A,
								};

const uint16_t ENC_BPIN[ENCn]={
								ENC1_GPIO_PIN_B,
								ENC2_GPIO_PIN_B,
								ENC3_GPIO_PIN_B,
								};

const uint8_t  ENC_APIN_SOURCE[ENCn]={	
								ENC1_GPIO_Pinsource_A,
								ENC2_GPIO_Pinsource_A,
								ENC3_GPIO_Pinsource_A,
								};
const uint8_t  ENC_BPIN_SOURCE[ENCn]={
								ENC1_GPIO_Pinsource_B,
								ENC2_GPIO_Pinsource_B,
								ENC3_GPIO_Pinsource_B,
								};
const uint8_t  ENC_GPIO_AF[ENCn]={
								ENC1_GPIO_AF_TIM,
								ENC2_GPIO_AF_TIM,
								ENC3_GPIO_AF_TIM,
								};
void(* ENC_TIMER_CLK_CMD[ENCn])(uint32_t,FunctionalState)={
								ENC1_TIMER_CLK_CMD,
								ENC2_TIMER_CLK_CMD,
								ENC3_TIMER_CLK_CMD,
};


const float ENC_COEFF[ENCn]={
								ENC1_COEFF,
								ENC2_COEFF,
								ENC3_COEFF
};

const bool ENC_DIR_IF_INVERSE[ENCn]={
								ENC1_DIR_IF_INVERSE,
								ENC2_DIR_IF_INVERSE,
								ENC3_DIR_IF_INVERSE,
};

ENC_INSTANCE_TypeDef ENCODER_ARRAY[ENCn];


/**
  * @brief  码盘初始化
  * @param
  * @retval
*/
void ENCx_HARD_Init(ENC_Typedef ENCx)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(ENC_GPIO_CLK[ENCx], ENABLE);	
	
	GPIO_InitStructure.GPIO_Pin 	= ENC_APIN[ENCx];
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_UP ;
	GPIO_Init(ENC_GPIO_PORT[ENCx], &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin 	= ENC_BPIN[ENCx];
	GPIO_Init(ENC_GPIO_PORT[ENCx], &GPIO_InitStructure);
	
	GPIO_PinAFConfig(ENC_GPIO_PORT[ENCx], ENC_APIN_SOURCE[ENCx], ENC_GPIO_AF[ENCx]);
	GPIO_PinAFConfig(ENC_GPIO_PORT[ENCx], ENC_BPIN_SOURCE[ENCx], ENC_GPIO_AF[ENCx]);

	ENC_TIMER_CLK_CMD[ENCx](ENC_TIMER_CLK[ENCx],ENABLE);
	
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Prescaler = 0x0;  // No prescaling 
	TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_PERIOD;  
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	
	TIM_TimeBaseInit(ENC_TIMER[ENCx], &TIM_TimeBaseStructure);
		// set them up as encoder inputs
	// set both inputs to rising polarity to let it use both edges
	TIM_EncoderInterfaceConfig(ENC_TIMER[ENCx],TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);

	TIM_Cmd(ENC_TIMER[ENCx], ENABLE);
}





void ENCx_Instance_Init(ENC_Typedef ENCx)
{
	ENC_INSTANCE_TypeDef *Encoderx = &ENCODER_ARRAY[ENCx];
	Encoderx->ENC_Coeff = ENC_COEFF[ENCx];
	Encoderx->If_Inverse = ENC_DIR_IF_INVERSE[ENCx];
}

void ENCx_Reset(ENC_Typedef ENCx)
{
	ENC_INSTANCE_TypeDef *Encoderx = &ENCODER_ARRAY[ENCx];
	Encoderx->count = 0;
	TIM_SetCounter(ENC_TIMER[ENCx], 0);	
}

void ENCx_Init(ENC_Typedef ENCx)
{
	ENCx_HARD_Init(ENCx);
	ENCx_Instance_Init(ENCx);
	ENCx_Reset(ENCx);	
}


void ENCx_Read(ENC_Typedef ENCx)
{
	ENC_INSTANCE_TypeDef *Encoderx = &ENCODER_ARRAY[ENCx];
	uint16_t now_t_us,d_t_us,now_encoder;
	int16_t delata_count;
	float DistanceResult,SpeedResult,DeltaDistanceResult;

	now_t_us = DT_US_COUNT;
	now_encoder = TIM_GetCounter(ENC_TIMER[ENCx]);
			
	d_t_us = now_t_us - Encoderx->last_read_us;
	Encoderx->last_d_t_us = d_t_us;
	delata_count = (int16_t)(now_encoder - Encoderx->last_encoder);
	
	Encoderx->last_read_us = now_t_us;
	Encoderx->last_encoder = now_encoder;
	Encoderx->count += delata_count;
	
	if(d_t_us == 0)//protect
	{
		d_t_us = 0xffff;
	}

	DistanceResult = Encoderx->count * Encoderx->ENC_Coeff;
	DeltaDistanceResult = delata_count * Encoderx->ENC_Coeff;
	SpeedResult =  1000 * DeltaDistanceResult * 1000/(float)d_t_us; 
	
	if(Encoderx->If_Inverse)
	{
		Encoderx->Distance = -DistanceResult;
		Encoderx->DeltaDistance = -DeltaDistanceResult;
		Encoderx->Speed = -SpeedResult;
	}		
	else
	{
		Encoderx->Distance = DistanceResult;
		Encoderx->DeltaDistance = DeltaDistanceResult;
		Encoderx->Speed = SpeedResult;
	}
}


/******************* (C) COPYRIGHT 2017 HUST-Robocon *****END OF FILE**********/
