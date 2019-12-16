#ifndef COMLIB_H
#define COMLIB_H
#include "stdint.h"
#include "com_userType.h"
#include "usart.h"


//最大长度224
typedef union
{
    int8_t	 int8_ts[64];
    int16_t	 int16_ts[32];
    int32_t	 int32_ts[16];
    uint8_t	 uint8_ts[64];
    uint16_t uint16_ts[32];
    uint32_t uint32_ts[16];
    float    floats_ts[16];
}DataType;


typedef struct
{
    uint8_t Length;
    uint8_t Prop;
    DataType Data;
}COM_Frame;


typedef struct
{
    uint8_t RecStatus;
    uint8_t RecCounts;
    uint8_t preData;
    uint8_t RecLength;
} FrameRecStatusTypedef;



void FRAME_Send(COM_Frame* SendFrame,uint8_t UsartMask);

void FRAME_ReceiveCall(uint8_t data,MY_USART_Typedef USARTx);

void MY_USART1ProcessData(COM_Frame* RecFrame);
void MY_USART2ProcessData(COM_Frame* RecFrame);

extern COM_Frame MY_USART1_Com_Receive;
extern FrameRecStatusTypedef MY_USART1_ComRecStatus;



extern COM_Frame MY_USART2_Com_Receive;
extern FrameRecStatusTypedef MY_USART2_ComRecStatus;

#endif // COMLIB_H
