#include "RobotCAN_Basic.h"
#include "Locate.h"
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
void GetLocateInfo(Frame* frm)
{	
//	if(abs(ChassisInstance.CurrentState.Vx) < 1000 && abs(ChassisInstance.CurrentState.w*(ChassisInstance.CurrentState.X + 7000)) < 1000 && abs(ChassisInstance.CurrentState.X - frm->data.shorts[0]) <50 && (abs(ChassisInstance.CurrentState.Vy) < 1000 && abs(ChassisInstance.CurrentState.w*(ChassisInstance.CurrentState.Y + 7000)) < 1000 && abs(ChassisInstance.CurrentState.Y - frm->data.shorts[1]) <50))
//	if( (abs(ChassisInstance.CurrentState.X - frm->data.shorts[0]) <50 &&  abs(ChassisInstance.CurrentState.Y - frm->data.shorts[1]) <50) || (abs(ChassisInstance.CurrentState.Vx) < 500 && abs(ChassisInstance.CurrentState.Vy) < 500))
	
	if(abs(ChassisInstance.OriginX) > 1 && fabs(ChassisInstance.CurrentState.Alpha - 3.141592653576f - frm->data.floats[1]) < 0.1 )
	{
		if( abs(ChassisInstance.CurrentState.X - frm->data.shorts[0]) <120)
						ChassisInstance.X_Correct =  frm->data.shorts[0] - ChassisInstance.OriginX  ;

//				ChassisInstance.CurrentState.X = frm->data.shorts[0];
			if(PathDot > PathInforms[ChassisInstance.NavigatePathNum].PathDotsNum*0.5)//|| (abs(ChassisInstance.CurrentState.X - frm->data.shorts[0]) <20 &&  abs(ChassisInstance.CurrentState.Y - frm->data.shorts[1]) <20) )
		{
			if( abs(ChassisInstance.CurrentState.Y - frm->data.shorts[1]) <400 || 	PathDot > PathInforms[ChassisInstance.NavigatePathNum].PathDotsNum*0.8)
			{
										ChassisInstance.Y_Correct =  frm->data.shorts[1] - ChassisInstance.OriginY  ;

//			ChassisInstance.CurrentState.Y = frm->data.shorts[1];
			}
		}
//			UpdateLaserLocate();
	}

//	if(abs(ChassisInstance.CurrentState.Vy) < 1000 && abs(ChassisInstance.CurrentState.w*(ChassisInstance.CurrentState.Y + 7000)) < 1000 && abs(ChassisInstance.CurrentState.Y - frm->data.shorts[1]) <30)
//		ChassisInstance.CurrentState.Y = frm->data.shorts[1];

//	if(abs(ChassisInstance.CurrentState.Vx)<1800 && abs(ChassisInstance.CurrentState.Vy)<1800)
//		ChassisInstance.CurrentState.Alpha = frm->data.floats[1];
	
}

/***************************************CAN1,CAN2函数分割******************************************/










