/*
 * ZY_VisualScope.c
 *
 *  Created on: 2014-10-27
 *      Author: Yue
 */
#include "ZY_VisualScope.h"
//#include "USART.h"
u8 ZY_VisualScope[10] = {0x00, 0x01, 0x00, 0x2, 0x00, 0x03, 0x0, 0x4, 0x00, 0x00};
extern uint8_t TxData[30];
// -30000~30000;
void ZY_VisualScope_Send(float Channel1, float Channel2, float Channel3,
                         float Channel4)
{
	static int t=0;

	if(t ==0)
		t++;
	else
	{
//		while(DMA_GetFlagStatus(DMA1_Stream4,DMA_FLAG_TCIF4)==0);
		DMA_ClearFlag(DMA1_Stream4, DMA_FLAG_TCIF4 | DMA_FLAG_HTIF4);
	}

    ZY_VisualScope[0] = ((s16)(Channel1)) & 0x00ff;
    ZY_VisualScope[1] = ((s16)(Channel1) & 0xff00) >> 8;
    ZY_VisualScope[2] = ((s16)(Channel2)) & 0x00ff;
    ZY_VisualScope[3] = ((s16)(Channel2) & 0xff00) >> 8;
    ZY_VisualScope[4] = ((s16)(Channel3)) & 0x00ff;
    ZY_VisualScope[5] = ((s16)(Channel3) & 0xff00) >> 8;
    ZY_VisualScope[6] = ((s16)(Channel4)) & 0x00ff;
    ZY_VisualScope[7] = ((s16)(Channel4) & 0xff00) >> 8;
    CRC_CHECK(ZY_VisualScope, 8);
}

void CRC_CHECK(unsigned char *Buf, unsigned char Len)
{
    u16 CRC_Temp;
    u8 i, j, k;
    CRC_Temp = 0xffff;     //CRC初始化
    for (i = 0; i < Len; i++)   //要循环的次数，就是Buf的字节数
    {
        CRC_Temp ^= ZY_VisualScope[i];  //逐字节异或
        for (j = 0; j < 8; j++)
        {
            if (CRC_Temp & 0x01)  //如果低位为1
            {
                CRC_Temp = (CRC_Temp >> 1 ) ^ 0xa001; //将CRC右移一位后与0xA001异或
            }
            else   //如果低位为0
            {
                CRC_Temp = CRC_Temp >> 1;  //将CRC右移一位
            }
        }
    }
    ZY_VisualScope[8] = CRC_Temp & 0x00ff ;                   //第9个数据上是CRC的低字节
    ZY_VisualScope[9] = (CRC_Temp & 0xff00) >> 8;            //将第10个数据赋上CRC的高字节
    for(k = 0; k < 10; k++)
    {
        USART_SendData(UART4 , Buf[k]);            // USART1 可以换成 USART2 等
        while (!(UART4->SR & USART_FLAG_TXE));
    }

//	 DMA1_Stream4->CR &= ~(uint32_t)DMA_SxCR_EN;																								 //    DMA_Cmd(DMA2, DISABLE);	   //1?±?DMA′?ê? 
//	 while((DMA1_Stream4->CR & (uint32_t)DMA_SxCR_EN) != 0){}				   //	 while (DMA_GetCmdStatus(DMA2_Stream7) != DISABLE){} //è·±￡DMA?éò?±?éè??	
//	 DMA1_Stream4->CR |= (uint32_t)DMA_SxCR_EN;

//	 DMA_Cmd(DMA_Channel_4, DISABLE);
//		DMA_Channel_4->CNDTR = 10;
//    DMA_Channel_4->CCR |= DMA_CCR1_EN;
}




