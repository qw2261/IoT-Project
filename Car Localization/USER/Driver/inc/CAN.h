#ifndef __CAN_H
#define __CAN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"


/* Exported constants --------------------------------------------------------*/
#define CAN1_CLK                    					RCC_APB1Periph_CAN1
#define CAN1_RX_PIN                 					GPIO_Pin_8
#define CAN1_TX_PIN                 					GPIO_Pin_9
#define CAN1_GPIO_PORT              					GPIOB
#define CAN1_GPIO_CLK               					RCC_AHB1Periph_GPIOB
#define CAN1_AF_PORT                					GPIO_AF_CAN1
#define CAN1_RX_SOURCE              					GPIO_PinSource8
#define CAN1_TX_SOURCE              					GPIO_PinSource9

#define CAN1_FILTER_NUMBER										0        //CAN2 用 14，CAN1 用的是0
#define CAN1_RX_IRQn													CAN1_RX0_IRQn
#define CAN1_RX_IRQHandler										CAN1_RX0_IRQHandler

#define CAN2_CLK                    					RCC_APB1Periph_CAN2 | RCC_APB1Periph_CAN1
#define CAN2_RX_PIN                 					GPIO_Pin_12
#define CAN2_TX_PIN                 					GPIO_Pin_13
#define CAN2_GPIO_PORT              					GPIOB
#define CAN2_GPIO_CLK               					RCC_AHB1Periph_GPIOB 
#define CAN2_AF_PORT                					GPIO_AF_CAN2
#define CAN2_RX_SOURCE              					GPIO_PinSource12
#define CAN2_TX_SOURCE              					GPIO_PinSource13

#define CAN2_FILTER_NUMBER										14        //CAN2 用 14，CAN1 用的是0
#define CAN2_RX_IRQn													CAN2_RX1_IRQn
#define CAN2_RX_IRQHandler										CAN2_RX1_IRQHandler



void CAN1_Init(void);
void CAN2_Init(void);

#endif
