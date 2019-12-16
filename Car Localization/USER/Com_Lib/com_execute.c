#include "com_prop.h"
#include "RobotCAN_Proplist.h"
#include "Imu.h"
#include "led.h"

void MY_USART2ProcessData(COM_Frame* RecFrame)
{
//	switch(RecFrame->Prop)
//	{
//		case PC_XY:
//			PCCorrectChassisXYParaGet(&(RecFrame->Data));
//					break;
//		case PC_ALPHA:
//			PCChassisAlphaGet(&(RecFrame->Data));
//		     break;
//		default:
//					break;
//	}
}



void MY_USART1ProcessData(COM_Frame* RecFrame)
{
//	switch(RecFrame->Prop) 
//	{ 
//		case COM_CHASSIS_MODE:
//			ChassisMode_Get(&(RecFrame->Data));
//			break;
//		case COM_CHASSIS_POS:
//			ChassisPos_Get(&(RecFrame->Data));
//			break;
//		case CHASSIS_SPEED:
//			ChassisSpeedGet(&(RecFrame->Data));
//			break;
//		default :
//					break;
//	}

}


void ChassisSpeedGet(DataType* Data)
{

//	ChassisInstance.AimState.Vx = Data->floats_ts[0];
//	ChassisInstance.AimState.Vy = Data->floats_ts[1];
//	ChassisInstance.AimState.w = Data->floats_ts[2];
//	
//	wheelsVectorCal(&ChassisInstance);
}






/******************************************串口1接收函数****************************************/

u8 count1=0;
u8 Error_Count = 0;
float PreCorrectX=0.0f;

void PCCorrectChassisXYParaGet(DataType *Data)
{
	
}





u8 count2 = 0;  
void PCChassisAlphaGet(DataType *Data)                           //接收为角度制
{
	

}


/*********************************************************************************************/



/*****************************************串口2接收函数***************************************/




void ChassisMode_Get(DataType* Data)
{
	
	ChassisModeTypedef ChassisMode = Data->uint8_ts[0];
	if(ChassisMode == STALL  || ChassisMode == CHASSIS_DISABLE)
	{
		ChassisInstance.Mode = ChassisMode;
	}
	else if(ChassisMode == PARKING&&ChassisInstance.Mode != NAVIGATE)
	{
		ChassisInstance.Mode = PARKING;
	}
	else if(ChassisMode == NAVIGATE && ChassisInstance.Mode == PARKING)
	{
		ChassisInstance.NavigatePathNum = Data->uint8_ts[1];
		if(ChassisInstance.NavigatePathNum >= 6)
			ChassisInstance.NavigatePathNum = 6 - 1;
//		ChassisInstance.NavigatePathNum = 0;
		ChassisInstance.Mode = NAVIGATE;	
		
	}
	else if(ChassisMode == ON_LINE && ChassisInstance.Mode == PARKING)
	{
		ChassisInstance.Mode = ON_LINE;		
	}
	
	
}	








bool IsPosRecv = false;


void ChassisPos_Get(DataType* Data)
{
	if(ChassisInstance.Mode==ON_LINE)
	{
		IsPosRecv = true;
		
		ChassisInstance.AimState.X = Data->int16_ts[0];
		ChassisInstance.AimState.Y = Data->int16_ts[1];
		ChassisInstance.AimState.Alpha = Data->floats_ts[1];
	}
}


/*********************************************************************************************/
