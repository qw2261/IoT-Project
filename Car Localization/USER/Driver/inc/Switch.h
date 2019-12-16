#ifndef  _SWITCH_H
#define  _SWITCH_H

#include "stm32f4xx.h"
#include "atomIO.h"
#include "stdbool.h"
typedef  enum
{
	SW0 = 0,
	SW1 = 1,
	SW2 = 2	
}SW_TypeDef;

/* Exported constants --------------------------------------------------------*/
#define SWn    										3

#define SW0_PIN   								GPIO_Pin_0
#define SW0_GPIO_PORT 						GPIOC
#define SW0_GPIO_CLK  						RCC_AHB1Periph_GPIOC

#define SW1_PIN   								GPIO_Pin_1
#define SW1_GPIO_PORT 						GPIOC
#define SW1_GPIO_CLK  						RCC_AHB1Periph_GPIOC

#define SW2_PIN   								GPIO_Pin_2
#define SW2_GPIO_PORT 						GPIOC
#define SW2_GPIO_CLK  						RCC_AHB1Periph_GPIOC


/* Exported functions --------------------------------------------------------*/
void  SW_InitAll(void);
void Sonnar_Init();
void SW_Init(SW_TypeDef  SW);
bool IsSWTouched(SW_TypeDef SW_N);

#define SW0_IN  PCin(0)
#define SW1_IN  PCin(1)
#define SW2_IN  PCin(2)

#define SN_IN PBin(9)
#define SN_OUT PBout(8)
#define SEND_SINGAL PEout(0)
#endif 
