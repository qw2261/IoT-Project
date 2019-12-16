#include "RobotCAN_Basic.h"
#include "Locate.h"
#include "Laser.h"
/**************************************************
各属性对应的执行程序
**************************************************/




void GetSingleMotorSpeed(Frame* frm)
{	
		uint8_t Drivers_Num = frm->id.ExtID.SrcDeviceId - CHASSIS_MOTOR1;
	  if(Drivers_Num < WHEELS_NUM)
		{
			ChassisInstance.CurrentState.wheelsW[Drivers_Num] = frm->data.shorts[0];
			ChassisInstance.AimState.wheelsW[Drivers_Num] =  frm->data.shorts[1];
		}
}
#include "path.h"
extern uint16_t PathDot;
extern PathInfoTypedef PathInforms[PATH_NUM];
extern uint8_t PathChange;

/*
		-----------------
		|					 |4				|
		|2			   |				3|
		|					 |	 				|
		|					 |				  |
		|				   |1				|
		-----------------
*/
void GetLocateInfo(Frame* frm)
{	
	static int16_t M1, M2, M3, M4;
	float WorldX1, WorldY1, WorldX2, WorldY2, Theta, WorldY;
	static uint8_t sParkingCnt = 0;
//	if(abs(ChassisInstance.CurrentState.Vx) < 1000 && abs(ChassisInstance.CurrentState.w*(ChassisInstance.CurrentState.X + 7000)) < 1000 && abs(ChassisInstance.CurrentState.X - frm->data.shorts[0]) <50 && (abs(ChassisInstance.CurrentState.Vy) < 1000 && abs(ChassisInstance.CurrentState.w*(ChassisInstance.CurrentState.Y + 7000)) < 1000 && abs(ChassisInstance.CurrentState.Y - frm->data.shorts[1]) <50))
//	if( (abs(ChassisInstance.CurrentState.X - frm->data.shorts[0]) <50 &&  abs(ChassisInstance.CurrentState.Y - frm->data.shorts[1]) <50) || (abs(ChassisInstance.CurrentState.Vx) < 500 && abs(ChassisInstance.CurrentState.Vy) < 500))

		M1 = frm->data.shorts[0];
		M2 = frm->data.shorts[1];
		M3 = frm->data.shorts[2];
		M4 = frm->data.shorts[3];

	if(ChassisInstance.CurrentState.Y>0)
		WorldY = WorldY1;
	else
		WorldY = WorldY2;
	
	AcountAll(M1, M2, M3, M4, &WorldX1, &WorldY1, &WorldX2, &WorldY2, ChassisInstance.CurrentState.Alpha - ChassisInstance.Alpha_Bias);
	
	if(abs(ChassisInstance.OriginX) > 1)
	{
		if(abs(WorldX1 - ChassisInstance.CurrentState.X) < 200)
			ChassisInstance.X_Correct = (WorldX1 - ChassisInstance.OriginX);
		
	if(ChassisInstance.Mode != PARKING && PathDot < PathInforms[ChassisInstance.NavigatePathNum].PathDotsNum*0.6  && (ChassisInstance.NavigatePathNum != 2  || (ChassisInstance.NavigatePathNum == 2 && ChassisInstance.CurrentState.Y > 0)))
			sParkingCnt = 0;
	else	if(sParkingCnt < 30)
	{
		if(abs(ChassisInstance.CurrentState.Y - WorldY) < 300 || PathDot > PathInforms[ChassisInstance.NavigatePathNum].PathDotsNum * 0.8)
			ChassisInstance.Y_Correct =  WorldY - ChassisInstance.OriginY  ;
		if(ChassisInstance.Mode == PARKING)
		sParkingCnt++ ;
	}
	if(ChassisInstance.NavigatePathNum == 1 && abs(WorldX1 - WorldX2) < 100)
			ChassisInstance.X_Correct = (WorldX2 - ChassisInstance.OriginX);
		}
//		if(abs(ChassisInstance.OriginX) > 1 && fabs(ChassisInstance.CurrentState.Alpha - 3.141592653576f - Theta) < 0.05)
//	{
//		if( (ChassisInstance.CurrentState.Y ) >-2500 || (ChassisInstance.CurrentState.Y < -2500 && abs(ChassisInstance.CurrentState.X - WorldX) < 200))
//						ChassisInstance.X_Correct = ( (WorldX - ChassisInstance.OriginX));// + ChassisInstance.X_Correct*2)/3  ;
//	
//	if(ChassisInstance.Mode != PARKING && PathDot < PathInforms[ChassisInstance.NavigatePathNum].PathDotsNum*0.6  && (ChassisInstance.NavigatePathNum != 2  || (ChassisInstance.NavigatePathNum == 2 && ChassisInstance.CurrentState.Y > 0)))
//			sParkingCnt = 0;
//	else	if(sParkingCnt < 30)
//	{
//		if(abs(ChassisInstance.CurrentState.Y - WorldY) < 300 || PathDot > PathInforms[ChassisInstance.NavigatePathNum].PathDotsNum * 0.8)
//			ChassisInstance.Y_Correct =  WorldY - ChassisInstance.OriginY  ;
////		if(fabs(ChassisInstance.CurrentState.Alpha - 3.141592653576f - Theta) < 0.03)
////			ChassisInstance.Alpha_Correct = Theta  + 3.141592653576f - ChassisInstance.OriginAlpha;
//		if(ChassisInstance.Mode == PARKING)
//		sParkingCnt++ ;
//	}
//	
//	
//		if(ChassisInstance.Mode != PARKING && (ChassisInstance.NavigatePathNum != 2  || (ChassisInstance.NavigatePathNum == 2 && ChassisInstance.CurrentState.Y > 0)))
//		{
////			if( abs(ChassisInstance.CurrentState.Y - WorldY) <300 || 	PathDot > PathInforms[ChassisInstance.NavigatePathNum].PathDotsNum*0.8)
////							ChassisInstance.Y_Correct =  WorldY - ChassisInstance.OriginY  ;
//		}
//	}
	
//			if(PathDot > PathInforms[ChassisInstance.NavigatePathNum].PathDotsNum*0.5)//|| (abs(ChassisInstance.CurrentState.X - frm->data.shorts[0]) <20 &&  abs(ChassisInstance.CurrentState.Y - frm->data.shorts[1]) <20) )
//		{
//			if( (ChassisInstance.CurrentState.Y > 0 && abs(ChassisInstance.CurrentState.Y - WorldY) <200) || (ChassisInstance.CurrentState.Y < 0 && abs(ChassisInstance.CurrentState.Y - WorldY) < 400))// || 	PathDot > PathInforms[ChassisInstance.NavigatePathNum].PathDotsNum*0.8)
//			{
//										ChassisInstance.Y_Correct =  WorldY - ChassisInstance.OriginY  ;
//			}
//		}

	
//	if(abs(ChassisInstance.OriginX) > 1 && fabs(ChassisInstance.CurrentState.Alpha - 3.141592653576f - frm->data.floats[1]) < 0.1 )
//	{
//		if( abs(ChassisInstance.CurrentState.X - frm->data.shorts[0]) <120)
//						ChassisInstance.X_Correct = ( (frm->data.shorts[0] - ChassisInstance.OriginX));// + ChassisInstance.X_Correct*2)/3  ;

//			if(PathDot > PathInforms[ChassisInstance.NavigatePathNum].PathDotsNum*0.5)//|| (abs(ChassisInstance.CurrentState.X - frm->data.shorts[0]) <20 &&  abs(ChassisInstance.CurrentState.Y - frm->data.shorts[1]) <20) )
//		{
//			if( abs(ChassisInstance.CurrentState.Y - frm->data.shorts[1]) <400 || 	PathDot > PathInforms[ChassisInstance.NavigatePathNum].PathDotsNum*0.8)
//			{
//										ChassisInstance.Y_Correct =  frm->data.shorts[1] - ChassisInstance.OriginY  ;
//			}
//		}
//	}

//	if(abs(ChassisInstance.CurrentState.Vy) < 1000 && abs(ChassisInstance.CurrentState.w*(ChassisInstance.CurrentState.Y + 7000)) < 1000 && abs(ChassisInstance.CurrentState.Y - frm->data.shorts[1]) <30)
//		ChassisInstance.CurrentState.Y = frm->data.shorts[1];

//	if(abs(ChassisInstance.CurrentState.Vx)<1800 && abs(ChassisInstance.CurrentState.Vy)<1800)
//		ChassisInstance.CurrentState.Alpha = frm->data.floats[1];
	
}

void GetPathChange(Frame* frm)
{
	PathChange = 1;
}

/***************************************CAN1,CAN2函数分割******************************************/










