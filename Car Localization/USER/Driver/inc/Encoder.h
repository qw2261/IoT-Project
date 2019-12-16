#ifndef _ENCODERA_H
#define _ENCODERA_H


#include "stm32f4xx.h"
#include "stdbool.h"

#define ENCn 3
typedef enum
{
  ENC1 = 0,
	ENC2 = 1,
	ENC3 = 2,
}ENC_Typedef;


/* Exported types ------------------------------------------------------------*/
typedef struct
{
	uint16_t last_encoder;
	int32_t count;
	uint16_t last_read_us;
	uint16_t last_d_t_us;
	float Distance;
	float Speed;
	float DeltaDistance;
	float ENC_Coeff;
	bool  If_Inverse;
} ENC_INSTANCE_TypeDef;
/* Exported constants --------------------------------------------------------*/

extern ENC_INSTANCE_TypeDef ENCODER_ARRAY[ENCn];

#define	ENC1_TIMER 							 					 TIM3
#define ENC1_TIMER_CLK						 				 RCC_APB1Periph_TIM3           
#define ENC1_GPIO_PORT						 				 GPIOB                          
#define ENC1_GPIO_CLK						 				   RCC_AHB1Periph_GPIOB
#define ENC1_GPIO_PIN_A					 					 GPIO_Pin_4                       //CH 1    
#define ENC1_GPIO_PIN_B					 					 GPIO_Pin_5 		                    //CH 2
#define ENC1_GPIO_AF_TIM          				 GPIO_AF_TIM3
#define ENC1_GPIO_Pinsource_A     				 GPIO_PinSource4          
#define ENC1_GPIO_Pinsource_B     				 GPIO_PinSource5
#define ENC1_TIMER_CLK_CMD					       RCC_APB1PeriphClockCmd


#define	ENC2_TIMER 							 					 TIM4
#define ENC2_TIMER_CLK						 				 RCC_APB1Periph_TIM4           
#define ENC2_GPIO_PORT						 				 GPIOB                          
#define ENC2_GPIO_CLK						 				   RCC_AHB1Periph_GPIOB
#define ENC2_GPIO_PIN_A					 					 GPIO_Pin_6                       //CH 1    
#define ENC2_GPIO_PIN_B					 					 GPIO_Pin_7 		                    //CH 2
#define ENC2_GPIO_AF_TIM          				 GPIO_AF_TIM4
#define ENC2_GPIO_Pinsource_A     				 GPIO_PinSource6          
#define ENC2_GPIO_Pinsource_B     				 GPIO_PinSource7
#define ENC2_TIMER_CLK_CMD					       RCC_APB1PeriphClockCmd


#define	ENC3_TIMER 							 					 TIM1
#define ENC3_TIMER_CLK						 				 RCC_APB2Periph_TIM1           
#define ENC3_GPIO_PORT						 				 GPIOA                          
#define ENC3_GPIO_CLK						 				   RCC_AHB1Periph_GPIOA
#define ENC3_GPIO_PIN_A					 					 GPIO_Pin_8                       //CH 1    
#define ENC3_GPIO_PIN_B					 					 GPIO_Pin_9 		                    //CH 2
#define ENC3_GPIO_AF_TIM          				 GPIO_AF_TIM1
#define ENC3_GPIO_Pinsource_A     				 GPIO_PinSource8          
#define ENC3_GPIO_Pinsource_B     				 GPIO_PinSource9
#define ENC3_TIMER_CLK_CMD					       RCC_APB2PeriphClockCmd


void ENCx_Reset(ENC_Typedef ENCx);
void ENCx_Read(ENC_Typedef ENCx);
void ENCx_Init(ENC_Typedef ENCx);



/* Exported 全局变量 --------------------------------------------------------*/


#endif 

/******************* (C) COPYRIGHT 2017 HUST-Robocon *****END OF FILE**********/
