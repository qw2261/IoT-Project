#include "Switch.h"
#include "stm32f4xx.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
GPIO_TypeDef *SW_GPIO_PORT[SWn]	=	{SW0_GPIO_PORT,	SW1_GPIO_PORT,	SW2_GPIO_PORT};
const uint16_t SW_PIN[SWn]			=	{SW0_PIN,	SW1_PIN,	SW2_PIN};
const uint16_t SW_GPIO_CLK[SWn]	=	{SW0_GPIO_CLK,	SW1_GPIO_CLK,	SW2_GPIO_CLK};
/**
  * @brief  SW_Init
  * @param  SWx
  * @retval None
  */
void Sonnar_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);

	GPIO_InitStructure.GPIO_Pin 		= 	GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIO_ResetBits(GPIOB,GPIO_Pin_8);
	
	GPIO_InitStructure.GPIO_Pin 		= 	GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);

	GPIO_InitStructure.GPIO_Pin 		= 	GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOE,&GPIO_InitStructure);
	GPIO_ResetBits(GPIOE,GPIO_Pin_0);
	
}
 

void SW_Init(SW_TypeDef SWx)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(SW_GPIO_CLK[SWx],ENABLE);

	GPIO_InitStructure.GPIO_Pin 		= 	SW_PIN[SWx];
	GPIO_InitStructure.GPIO_Mode 		= 	GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType 	= 	GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed 	= 	GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd 		= 	GPIO_PuPd_UP;
	GPIO_Init(SW_GPIO_PORT[SWx],&GPIO_InitStructure);
}
/**
  * @brief  SW_InitAll
  * @param  None
  * @retval None
  */
void SW_InitAll(void)
{
	SW_Init(SW0);
  SW_Init(SW1);
  SW_Init(SW2);
}
/**
  * @brief  IsSW0Touched
  * @param  None
  * @retval true/false 
  */
bool IsSWTouched(SW_TypeDef SWx)
{
  if(GPIO_ReadInputDataBit(SW_GPIO_PORT[SWx],SW_PIN[SWx]))
	{
			return true;
	}
  return false;  			
}
/******************* (C) COPYRIGHT 2014 HUST-Robocon *****END OF FILE**********/
