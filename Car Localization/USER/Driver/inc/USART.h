#ifndef __USART_H
#define __USART_H


#include "stm32f4xx.h"
#include "stdio.h"
#include "stdbool.h"


typedef enum
{
  MYUSART1 = 0,
	MYUSART2 = 1,
}MY_USART_Typedef;



#define BUFFERSIZE                          255

#define MY_USART1_MASK 0x01  //001b
#define MY_USART2_MASK 0x02  //010b

#define MY_USART1_BAUDRATE   115200 //460800
#define MY_USART2_BAUDRATE   115200


extern u8 ReceiveBuffer1[BUFFERSIZE];   //DMA中断接收使用
extern u8 ReceiveBuffer2[BUFFERSIZE];

extern u16  LENTH_USART_RX1;
extern bool FLAG_USART_RX1;

extern u16  LENTH_USART_RX2;
extern bool FLAG_USART_RX2;

extern float angle1,angle2,angle3,T,rate1,rate2,rate3;
extern uint8_t target;

/* Exported constants --------------------------------------------------------*/

#define USARTn															2

/* Definition for USARTx resources ******************************************/

#define MY_USART1                           UART4                            
#define MY_USART1_CLK                       RCC_APB1Periph_UART4
#define MY_USART1_CLK_INIT                  RCC_APB1PeriphClockCmd
#define MY_USART1_IRQn                      UART4_IRQn
#define MY_USART1_IRQHandler                UART4_IRQHandler

#define MY_USART1_GPIO_PORT              		GPIOC      
#define MY_USART1_TX_PIN                    GPIO_Pin_10                
#define MY_USART1_RX_PIN                    GPIO_Pin_11                 
#define MY_USART1_TX_SOURCE                 GPIO_PinSource10
#define MY_USART1_RX_SOURCE                 GPIO_PinSource11
#define MY_USART1_GPIO_CLK               		RCC_AHB1Periph_GPIOC
#define MY_USART1_AF                     		GPIO_AF_UART4
																						
/* Definition for USARTx resources ******************************************/

#define MY_USART2                           USART3                            
#define MY_USART2_CLK                       RCC_APB1Periph_USART3
#define MY_USART2_CLK_INIT                  RCC_APB1PeriphClockCmd
#define MY_USART2_IRQn                      USART3_IRQn
#define MY_USART2_IRQHandler                USART3_IRQHandler

#define MY_USART2_GPIO_PORT              		GPIOB      
#define MY_USART2_TX_PIN                    GPIO_Pin_10                
#define MY_USART2_RX_PIN                    GPIO_Pin_11                 
#define MY_USART2_TX_SOURCE                 GPIO_PinSource10
#define MY_USART2_RX_SOURCE                 GPIO_PinSource11
#define MY_USART2_GPIO_CLK               		RCC_AHB1Periph_GPIOB
#define MY_USART2_AF                     		GPIO_AF_USART3




/* Exported functions --------------------------------------------------------*/
void MyUART_Init(MY_USART_Typedef USARTx);
void ComWrite(uint8_t* SendBuf,uint8_t lengthTemp,MY_USART_Typedef USARTx);
#endif 

/******************* (C) COPYRIGHT 2017 HUST-Robocon *****END OF FILE**********/


