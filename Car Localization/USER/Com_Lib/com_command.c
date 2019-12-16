#include "com_prop.h"
#include "path.h"
#include "encoder.h"
void TestSend(float t1,float t2,float t3)
{ 
	  COM_Frame SendFrame;
    SendFrame.Length = 12;
    SendFrame.Prop = CURRENT_PID_SEND;
    SendFrame.Data.floats_ts[0] = t1;
	  SendFrame.Data.floats_ts[1] = t2;
		SendFrame.Data.floats_ts[2] = t3;
		FRAME_Send(&SendFrame,  MY_USART1_MASK);
}

void CurrentSend2(ChassisInfoTypedef *ChassisInfo)
{
		COM_Frame SendFrame;
		SendFrame.Length = 20;
		SendFrame.Prop = MOTOR_PARA_SEND;
		SendFrame.Data.floats_ts[0] = (float)(ChassisInfo->CurrentState.Vx);
		SendFrame.Data.floats_ts[1] = (float)(ChassisInfo->CurrentState.Vx);
		SendFrame.Data.floats_ts[2] = 0;
		SendFrame.Data.floats_ts[3] = 0;
		SendFrame.Data.floats_ts[4]  = 0;
		FRAME_Send(&SendFrame,  MY_USART1_MASK);	
}

void CurrentSend(ChassisInfoTypedef *ChassisInfo)
{ 
	  COM_Frame SendFrame;
    SendFrame.Length = 12;
    SendFrame.Prop = POS_PID_SEND;
    SendFrame.Data.floats_ts[0] = (float)(ChassisInfo->CurrentState.X);
		SendFrame.Data.floats_ts[1] = (float)(ChassisInfo->CurrentState.Y);
		SendFrame.Data.floats_ts[2] = (ChassisInfo->CurrentState.Alpha);
		FRAME_Send(&SendFrame,  MY_USART1_MASK);
}
void AimSend(ChassisInfoTypedef *ChassisInfo)
{ 
	  COM_Frame SendFrame;
    SendFrame.Length = 12;
    SendFrame.Prop = SPEED_PID_SEND;
    SendFrame.Data.floats_ts[0] = 111;
	  SendFrame.Data.floats_ts[1] = 222;
		SendFrame.Data.floats_ts[2] = 333;
		FRAME_Send(&SendFrame,  MY_USART1_MASK);
}




/*******************************串口2发送函数************************************/

void Chassis_Pos_Send(ChassisInfoTypedef *ChassisInfo)
{

}

/********************************************************************************/








/*****************************串口1发送函数************************************/


void LocateInfo_Send(ChassisInfoTypedef *ChassisInfo)
{
	
	COM_Frame SendFrame;
	SendFrame.Length = 20;//17;//20;
 	SendFrame.Prop = COM_LOCATE_INFO;// COM_LOCATE_INFO;//6
	SendFrame.Data.int16_ts[0] = (s16)(ChassisInfo->CurrentState.X);
	SendFrame.Data.int16_ts[1] = (s16)(ChassisInfo->CurrentState.Y);
	SendFrame.Data.floats_ts[1] = (ChassisInfo->CurrentState.Alpha);

//	SendFrame.Data.int16_ts[0] = (s16)(ChassisInfo->CurrentState.X);
//	SendFrame.Data.int16_ts[1] = (s16)((ChassisInfo->CurrentState.w));
//	SendFrame.Data.floats_ts[1] = (ChassisInfo->CurrentState.Alpha*100);
	
//	SendFrame.Data.int16_ts[0] = ENCODER_ARRAY[0].count/32767;
//	SendFrame.Data.int16_ts[1] = ENCODER_ARRAY[0].count%32767;
//	SendFrame.Data.floats_ts[1] = (ChassisInfo->CurrentState.Alpha);
//		SendFrame.Data.int16_ts[4] = ENCODER_ARRAY[1].count/32767;
//	SendFrame.Data.int16_ts[5] = ENCODER_ARRAY[1].count%32767;
//	SendFrame.Data.floats_ts[3] = (ChassisInfo->CurrentState.Alpha);
//	SendFrame.Data.uint8_ts[16] =1;// (ChassisInfo->CurrentState.Alpha);

	
	SendFrame.Data.int16_ts[4] = (ChassisInfo->CurrentState.Vx);
	SendFrame.Data.int16_ts[5] = (ChassisInfo->CurrentState.Vy);
	SendFrame.Data.floats_ts[3] = (ChassisInfo->CurrentState.w);
	SendFrame.Data.int16_ts[8] = ChassisInfo->X_Correct;
	SendFrame.Data.int16_ts[9] = ChassisInfo->Y_Correct;
	FRAME_Send(&SendFrame,MY_USART1_MASK);
}


void AimLocateInfo_Send(ChassisInfoTypedef* ChassisInfo)
{
	COM_Frame SendFrame;
	
	SendFrame.Length = 16;
  SendFrame.Prop = COM_AIM_LOCATE_INFO;
	SendFrame.Data.int16_ts[0] = (s16)(ChassisInfo->AimState.X);
	SendFrame.Data.int16_ts[1] = (s16)(ChassisInfo->AimState.Y);
	SendFrame.Data.floats_ts[1] = (ChassisInfo->AimState.Alpha);
	SendFrame.Data.int16_ts[4]  = (s16)(ChassisInfo->AimState.Vx);
	SendFrame.Data.int16_ts[5]  = (s16)(ChassisInfo->AimState.Vy);
	SendFrame.Data.floats_ts[3]  = (s16)(ChassisInfo->AimState.w);
//	SendFrame.Data.floats_ts[1] = (float)ENCODER_ARRAY[1].count;
	FRAME_Send(&SendFrame,MY_USART1_MASK);
}

void MotorsSpeed_Send(ChassisInfoTypedef* ChassisInfo)
{
	COM_Frame SendFrame;
	
	SendFrame.Length = 8;
	SendFrame.Prop = COM_FEED_MOTORS_SPEED;
	SendFrame.Data.int16_ts[0] = ChassisInfo->CurrentState.wheelsW[0]; 
	SendFrame.Data.int16_ts[1] = ChassisInfo->CurrentState.wheelsW[1]; 
	SendFrame.Data.int16_ts[2] = ChassisInfo->CurrentState.wheelsW[2]; 
	SendFrame.Data.int16_ts[3] = ChassisInfo->CurrentState.wheelsW[3]; 
	
	FRAME_Send(&SendFrame,MY_USART1_MASK);
}


void MotorsAimSpeed_Send(ChassisInfoTypedef* ChassisInfo)
{
	COM_Frame SendFrame;
	
	SendFrame.Length = 8;
	SendFrame.Prop = COM_MOTORS_AIM_SPEED;
	SendFrame.Data.int16_ts[0] = ChassisInfo->AimState.wheelsW[0]; 
	SendFrame.Data.int16_ts[1] = ChassisInfo->AimState.wheelsW[1]; 
	SendFrame.Data.int16_ts[2] = ChassisInfo->AimState.wheelsW[2]; 
	SendFrame.Data.int16_ts[3] = ChassisInfo->AimState.wheelsW[3]; 
	FRAME_Send(&SendFrame,MY_USART1_MASK);
}


void ChassisMode_Send(ChassisInfoTypedef* ChassisInfo)
{
	COM_Frame SendFrame;
	
	SendFrame.Length = 2;
	SendFrame.Prop = COM_CHASSIS_CUR_MODE;
	SendFrame.Data.uint8_ts[0] = ChassisInfo->Mode;
	SendFrame.Data.uint8_ts[1] = ChassisInfo->NavigatePathNum;
	
	FRAME_Send(&SendFrame,MY_USART1_MASK);
}


void RegionInfoSend()
{
	COM_Frame SendFrame;
	
	
	SendFrame.Length = 1;
	SendFrame.Prop = REGION_INFO;
	
	if(USE_BLUE)
	{
	 SendFrame.Data.uint8_ts[0] = 1; 
	}
	else if(USE_RED)
	{
	 SendFrame.Data.uint8_ts[0] = 2; 
	}
	
  FRAME_Send(&SendFrame,MY_USART1_MASK);
}
/******************************************************************************/




