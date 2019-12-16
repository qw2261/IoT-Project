#include "usart.h"
#include "system_config.h"



u8 ReceiveBuffer1[BUFFERSIZE];
u8 SendBuffer1[BUFFERSIZE];

u8 ReceiveBuffer2[BUFFERSIZE];
u8 SendBuffer2[BUFFERSIZE];

u16  LENTH_USART_RX1=0;
bool FLAG_USART_RX1=false;

u16  LENTH_USART_RX2=0;
bool FLAG_USART_RX2=false;


USART_TypeDef * const USART_SOURCE[USARTn] ={
								MY_USART1,
								MY_USART2,
								};

GPIO_TypeDef * const USART_GPIO_PORT[USARTn]={
								MY_USART1_GPIO_PORT,
								MY_USART2_GPIO_PORT,
								};

const uint32_t USART_GPIO_CLK[USARTn] ={
								MY_USART1_GPIO_CLK,
								MY_USART2_GPIO_CLK,
								};
const uint16_t USART_TX_PIN[USARTn]={	
								MY_USART1_TX_PIN,
								MY_USART2_TX_PIN,
								};
const uint16_t USART_TX_PIN_SOURCE[USARTn]={
								MY_USART1_TX_SOURCE,
								MY_USART2_TX_SOURCE,
								};
const uint16_t USART_RX_PIN[USARTn]={	
								MY_USART1_RX_PIN,
								MY_USART2_RX_PIN,
								};

const uint16_t USART_RX_PIN_SOURCE[USARTn]={
								MY_USART1_RX_SOURCE,
								MY_USART2_RX_SOURCE,
								};
const uint8_t USART_IRQn[USARTn] ={
								MY_USART1_IRQn,
								MY_USART2_IRQn,
								};	

const uint8_t  USART_AF[USARTn]={
								MY_USART1_AF,
								MY_USART2_AF,
								};

const uint32_t USART_BAUDRATE[USARTn] ={
								MY_USART1_BAUDRATE,
								MY_USART2_BAUDRATE,
								};	

void (*UART_PERIPH_CLOCK_CMD[USARTn])(uint32_t , FunctionalState)={
								MY_USART1_CLK_INIT,
								MY_USART2_CLK_INIT,
								};

const uint32_t USART_PERIPH_CLK[USARTn]={
								MY_USART1_CLK,
								MY_USART2_CLK
                };

uint8_t* const USART_SENDBUFFER[USARTn] ={
	              SendBuffer1,
	              SendBuffer2,
                };



uint8_t* const USART_RECVBUFFER[USARTn] ={
	              ReceiveBuffer1,
	              ReceiveBuffer2,
                };



void USARTx_Init(MY_USART_Typedef USARTx)
{
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef  NVIC_InitStructure;
    GPIO_InitTypeDef  GPIO_InitStructure;

    /* Enable GPIO(AHB1) clock */
    RCC_AHB1PeriphClockCmd(USART_GPIO_CLK[USARTx], ENABLE);

    /* Enable USART clock */
    UART_PERIPH_CLOCK_CMD[USARTx](USART_PERIPH_CLK[USARTx],ENABLE);
	

    /* Connect USART pins to AF */
    GPIO_PinAFConfig(USART_GPIO_PORT[USARTx], USART_TX_PIN_SOURCE[USARTx], USART_AF[USARTx]);
    GPIO_PinAFConfig(USART_GPIO_PORT[USARTx], USART_RX_PIN_SOURCE[USARTx], USART_AF[USARTx]);

    /* Configure USART Tx and Rx as alternate function push-pull */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Pin =  USART_TX_PIN[USARTx];
    GPIO_Init(USART_GPIO_PORT[USARTx], &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin =  USART_RX_PIN[USARTx];
    GPIO_Init(USART_GPIO_PORT[USARTx], &GPIO_InitStructure);

    USART_OverSampling8Cmd(USART_SOURCE[USARTx], ENABLE);

    USART_InitStructure.USART_BaudRate = USART_BAUDRATE[USARTx];
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART_SOURCE[USARTx], &USART_InitStructure);

    #ifdef _USE_DMA
	  USART_ITConfig(USART_SOURCE[USARTx], USART_IT_IDLE, ENABLE);
		#else
	  USART_ITConfig(USART_SOURCE[USARTx], USART_IT_RXNE, ENABLE);
		#endif
    /* Configure the Priority Group to 2 bits */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    /* Enable the USARTx Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = USART_IRQn[USARTx];
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* Enable USART */
    USART_Cmd(USART_SOURCE[USARTx], ENABLE);
		
		#ifdef _USE_DMA
		USART_DMACmd(USART_SOURCE[USARTx], USART_DMAReq_Tx, ENABLE);
	  USART_DMACmd(USART_SOURCE[USARTx], USART_DMAReq_Rx, ENABLE);
		#endif
		
		USART_ClearFlag(USART_SOURCE[USARTx], USART_FLAG_TC);
}


void MyUART_Init(MY_USART_Typedef USARTx)
{
	USARTx_Init(USARTx);
	

}

void ComWrite(uint8_t* SendBuf,uint8_t lengthTemp,MY_USART_Typedef USARTx)
{
	uint8_t i = 0;
	USART_TypeDef *USART_INSTANCE = USART_SOURCE[USARTx];
	for(i = 0;i < lengthTemp;i++)
	{
		while(USART_GetFlagStatus(USART_INSTANCE,USART_FLAG_TXE)!= SET);
		USART_SendData(USART_INSTANCE,*SendBuf++);
	}
}

u8 ORDER_RX_BUF[256] = {0};   
uint8_t target = 0;
extern bool take_photo;
static void get_order(uint8_t data_t)
{
	static uint8_t num = 0;
	ORDER_RX_BUF[num] = data_t;
	if(num == 0)
	{
		if(ORDER_RX_BUF[num] == 0x75)
		{
			num++;
		}
	}
	else if(num > 1)
  {
		switch(ORDER_RX_BUF[1])
		{
			case 0x61:
				target = 1;
			break;
			case 0x62:
				target = 2;
			break;
			case 0x73:
				target = 0;
			break;
			case 0x70:
				take_photo = true;
			break;
		}
		num = 0;
	}
	else
	{
		num ++;
	}
	
}

void (MY_USART1_IRQHandler)(void)
{
	u8 Res;

	if(USART_GetITStatus(MY_USART1, USART_IT_RXNE) == SET)
  {
		Res = USART_ReceiveData(MY_USART1);	//读取接收到的数据
		get_order(Res);    //解析数据帧	 
   USART_ClearITPendingBit(MY_USART1, USART_IT_RXNE);
	}
	else
		USART_ClearITPendingBit(MY_USART1, USART_IT_ERR|USART_IT_ORE|USART_IT_FE|USART_IT_NE);	
}



float angle1=0, angle2=0, angle3=0,T=0;
float rate1=0, rate2=0,rate3=0;

u8 USART_RX_BUF[256] = {0};     //接收缓冲,最大USART_REC_LEN个字节.

	
static void analyse_data2(uint8_t data_t)
{ 
	static uint8_t state = 0;

	USART_RX_BUF[state] = data_t;

	// 帧头
  if(state == 0)
	{
		if(USART_RX_BUF[state] == 0x55)
			state ++ ;
	}
	else
	{
		if(state >= 10)
		{
			switch(USART_RX_BUF[1])
			{
				case 0x52:
					rate1 = (USART_RX_BUF[3]<<8 | USART_RX_BUF[2])/32768.0 * 2000;
				  rate2 = (USART_RX_BUF[5]<<8 | USART_RX_BUF[4])/32768.0 * 2000;
				  rate3 = (USART_RX_BUF[7]<<8 | USART_RX_BUF[6])/32768.0 * 2000;
					break;
				case 0x53:
					angle1 = (USART_RX_BUF[3]<<8 | USART_RX_BUF[2])/32768.0 * 180;
				  angle2 = (USART_RX_BUF[5]<<8 | USART_RX_BUF[4])/32768.0 * 180;
				  angle3 = (USART_RX_BUF[7]<<8 | USART_RX_BUF[6])/32768.0 * 180;
					T = (USART_RX_BUF [9]<<8| USART_RX_BUF [8])/340.0+36.25;
				break;
			
			}
			state = 0;
		}
		else
		{
			state++;
		}
	}
	
	
}

void (MY_USART2_IRQHandler)(void)
{
	u8 Res;

	if(USART_GetITStatus(MY_USART2, USART_IT_RXNE) == SET)
  {
   // temp = USART_ReceiveData(PC_USART);
	//	FRAME_ReceiveCall(temp,&MY_USART1_ComRecStatus,&MY_USART1_Com_Receive);
		Res = USART_ReceiveData(MY_USART2);	//读取接收到的数据
		analyse_data2(Res);    //解析数据帧	 
   USART_ClearITPendingBit(MY_USART2, USART_IT_RXNE);
	}
	else
		USART_ClearITPendingBit(MY_USART2, USART_IT_ERR|USART_IT_ORE|USART_IT_FE|USART_IT_NE);	
}

/******************* (C) COPYRIGHT 2017 HUST-Robocon *****END OF FILE**********/


