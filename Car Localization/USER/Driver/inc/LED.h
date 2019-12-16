#ifndef __LED_H
#define __LED_H
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

/* Exported types ------------------------------------------------------------*/
typedef enum
{
	LED1 ,
	LED2   
}LED_TypeDef;

/* Exported constants --------------------------------------------------------*/
#define LEDn														3
//                                                         
#define LED1_PIN												GPIO_Pin_6                 
#define LED1_GPIO_PORT									GPIOA
#define LED1_GPIO_CLK										RCC_AHB1Periph_GPIOA

#define LED2_PIN												GPIO_Pin_7                 
#define LED2_GPIO_PORT									GPIOA
#define LED2_GPIO_CLK										RCC_AHB1Periph_GPIOA


#define RED_LED      LED1 
#define GREEN_LED    LED2 



/* Exported functions --------------------------------------------------------*/
void LED_Init(LED_TypeDef LED);
void LED_On(LED_TypeDef LED);
void LED_Off(LED_TypeDef LED);
void LED_Toggle(LED_TypeDef LED);
void LED_InitAll(void);


#endif 

/******************* (C) COPYRIGHT 2014 HUST-Robocon *****END OF FILE**********/

