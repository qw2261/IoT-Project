#include "CAN.h"
#include "RobotCAN_IDconf.h"
#include "RobotCAN_Basic.h"

void CAN1_Init(void)
{
	GPIO_InitTypeDef  		GPIO_InitStructure;
	CAN_InitTypeDef       CAN_InitStructure;
	CAN_FilterInitTypeDef CAN_FilterInitStructure;
	NVIC_InitTypeDef 			NVIC_InitStructure;
  
  /* CAN GPIOs configuration **************************************************/

  /* Enable GPIO clock */
  RCC_AHB1PeriphClockCmd(CAN1_GPIO_CLK, ENABLE);

  /* Connect CAN pins to AF9 */
  GPIO_PinAFConfig(CAN1_GPIO_PORT, CAN1_RX_SOURCE, CAN1_AF_PORT);
  GPIO_PinAFConfig(CAN1_GPIO_PORT, CAN1_TX_SOURCE, CAN1_AF_PORT); 
  
  /* Configure CAN RX and TX pins */
  GPIO_InitStructure.GPIO_Pin = CAN1_RX_PIN | CAN1_TX_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;
  GPIO_Init(CAN1_GPIO_PORT, &GPIO_InitStructure);

  /* CAN configuration ********************************************************/  
  /* Enable CAN clock */
  RCC_APB1PeriphClockCmd(CAN1_CLK, ENABLE);
  
  /* CAN register init */
  CAN_DeInit(CAN1);

  /* CAN cell init */
  CAN_InitStructure.CAN_TTCM = DISABLE;
  CAN_InitStructure.CAN_ABOM = ENABLE;
  CAN_InitStructure.CAN_AWUM = DISABLE;
  CAN_InitStructure.CAN_NART = DISABLE;
  CAN_InitStructure.CAN_RFLM = DISABLE;
  CAN_InitStructure.CAN_TXFP = DISABLE;
  CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;
  CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
    
  /* CAN Baudrate = 42M/(1+BS1+BS2)/Prescaler (CAN clocked at 42 MHz) */
  CAN_InitStructure.CAN_BS1 = CAN_BS1_8tq;       //(42/(1+8+5)/3=1M)
  CAN_InitStructure.CAN_BS2 = CAN_BS2_5tq;
   //CAN_InitStructure.CAN_Prescaler = 24; //500K
  CAN_InitStructure.CAN_Prescaler = 3;	   //1M
  CAN_Init(CAN1, &CAN_InitStructure);
	
  /* CAN filter init */
  CAN_FilterInitStructure.CAN_FilterNumber = CAN1_FILTER_NUMBER;
  CAN_FilterInitStructure.CAN_FilterMode =   CAN_FilterMode_IdMask;
  CAN_FilterInitStructure.CAN_FilterScale =  CAN_FilterScale_32bit;
  CAN_FilterInitStructure.CAN_FilterIdHigh = ((FILTER_ID <<3)&0xFFFF0000)>>16;
  CAN_FilterInitStructure.CAN_FilterIdLow =  (FILTER_ID <<3) &0x0000FFFF;
  CAN_FilterInitStructure.CAN_FilterMaskIdHigh = ((FILTER_MASK<<3)&0xFFFF0000)>>16;
  CAN_FilterInitStructure.CAN_FilterMaskIdLow =  (FILTER_MASK<<3) &0x0000FFFF;
  CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;
  CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
  CAN_FilterInit(&CAN_FilterInitStructure);
	
	#ifdef SLAVER_DEVICE
	CAN_FilterInitStructure.CAN_FilterNumber = CAN1_FILTER_NUMBER + 1;
  CAN_FilterInitStructure.CAN_FilterMode =   CAN_FilterMode_IdMask;
  CAN_FilterInitStructure.CAN_FilterScale =  CAN_FilterScale_32bit;
  CAN_FilterInitStructure.CAN_FilterIdHigh = ((FILTER_SECOND_ID <<3)&0xFFFF0000)>>16;
  CAN_FilterInitStructure.CAN_FilterIdLow =  (FILTER_SECOND_ID <<3) &0x0000FFFF;
  CAN_FilterInitStructure.CAN_FilterMaskIdHigh = ((FILTER_MASK<<3)&0xFFFF0000)>>16;
  CAN_FilterInitStructure.CAN_FilterMaskIdLow =  (FILTER_MASK<<3) &0x0000FFFF;
  CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;
	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
  CAN_FilterInit(&CAN_FilterInitStructure);
	#endif
	
	/* Configures the NVIC *****************************************************/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

  NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; 
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);  
  
  /* Enable FIFO 0 message pending Interrupt */
  CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);
}

void CAN2_Init(void)
{
	#ifndef SLAVER_DEVICE
	GPIO_InitTypeDef  		GPIO_InitStructure;
	CAN_InitTypeDef       CAN_InitStructure;
	CAN_FilterInitTypeDef CAN_FilterInitStructure;
	NVIC_InitTypeDef 			NVIC_InitStructure;
  
  /* CAN GPIOs configuration **************************************************/

  /* Enable GPIO clock */
  RCC_AHB1PeriphClockCmd(CAN2_GPIO_CLK, ENABLE);

  /* Connect CAN pins to AF9 */
  GPIO_PinAFConfig(CAN2_GPIO_PORT, CAN2_RX_SOURCE, CAN2_AF_PORT);
  GPIO_PinAFConfig(CAN2_GPIO_PORT, CAN2_TX_SOURCE, CAN2_AF_PORT); 
  
  /* Configure CAN RX and TX pins */
  GPIO_InitStructure.GPIO_Pin = CAN2_RX_PIN | CAN2_TX_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;
  GPIO_Init(CAN2_GPIO_PORT, &GPIO_InitStructure);

  /* CAN configuration ********************************************************/  
  /* Enable CAN clock */
  RCC_APB1PeriphClockCmd(CAN2_CLK, ENABLE);
  
  /* CAN register init */
  CAN_DeInit(CAN2);

  /* CAN cell init */
  CAN_InitStructure.CAN_TTCM = DISABLE;
  CAN_InitStructure.CAN_ABOM = ENABLE;
  CAN_InitStructure.CAN_AWUM = DISABLE;
  CAN_InitStructure.CAN_NART = DISABLE;
  CAN_InitStructure.CAN_RFLM = DISABLE;
  CAN_InitStructure.CAN_TXFP = DISABLE;
  CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;
  CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
    
  /* CAN Baudrate = 42M/(1+BS1+BS2)/Prescaler (CAN clocked at 42 MHz) */
  CAN_InitStructure.CAN_BS1 = CAN_BS1_8tq;       //(42/(1+8+5)/3=1M)
  CAN_InitStructure.CAN_BS2 = CAN_BS2_5tq;
   //CAN_InitStructure.CAN_Prescaler = 24; //500K
  CAN_InitStructure.CAN_Prescaler = 3;	   //1M
  CAN_Init(CAN2, &CAN_InitStructure);
	
	
  /* CAN filter init */
  CAN_FilterInitStructure.CAN_FilterNumber = CAN2_FILTER_NUMBER;
  CAN_FilterInitStructure.CAN_FilterMode =   CAN_FilterMode_IdMask;
  CAN_FilterInitStructure.CAN_FilterScale =  CAN_FilterScale_32bit;
  CAN_FilterInitStructure.CAN_FilterIdHigh = ((FILTER_SECOND_ID <<3)&0xFFFF0000)>>16;
  CAN_FilterInitStructure.CAN_FilterIdLow =  (FILTER_SECOND_ID <<3) &0x0000FFFF;
  CAN_FilterInitStructure.CAN_FilterMaskIdHigh = ((FILTER_MASK<<3)&0xFFFF0000)>>16;
  CAN_FilterInitStructure.CAN_FilterMaskIdLow =  (FILTER_MASK<<3) &0x0000FFFF;
  CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 1;
  CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
  CAN_FilterInit(&CAN_FilterInitStructure);
	
	/* Configures the NVIC *****************************************************/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

  NVIC_InitStructure.NVIC_IRQChannel = CAN2_RX_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);  
  
  /* Enable FIFO 1 message pending Interrupt */
  CAN_ITConfig(CAN2, CAN_IT_FMP1, ENABLE);
	#endif
}





