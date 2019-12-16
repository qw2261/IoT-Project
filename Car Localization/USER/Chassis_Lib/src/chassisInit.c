#include "system_config.h"
#include "path.h"
#include "chassis.h"
#include "Locate.h"


PID_StructTypedef TrajectCorrectPID;
PID_StructTypedef PosePID;
PID_StructTypedef PositionX_PID;
PID_StructTypedef PositionY_PID;
PID_StructTypedef PositionPID_InitTemp;

void PositionInit(ChassisInfoTypedef* ChassisInfo);

void PositionPidInit(PID_StructTypedef * pPID)
{
	pPID->Kp = PositionPID_InitTemp.Kp;
	pPID->Ki = PositionPID_InitTemp.Ki;
	pPID->Kd = PositionPID_InitTemp.Kd;
	pPID->LimitOutput = PositionPID_InitTemp.LimitOutput;
	pPID->LimitIntegral = PositionPID_InitTemp.LimitIntegral;
	pPID->PreError = 0;
	pPID->Integral = 0;
}


void chassisInit()
{  
    PositionPID_InitTemp.Kp =3;//15;//1.0f;
    PositionPID_InitTemp.Ki = 0;//0.004;
    PositionPID_InitTemp.Kd =0;//50;// 5.0f;
    PositionPID_InitTemp.LimitOutput = 800; 
    PositionPID_InitTemp.LimitIntegral = 20;
    PositionPID_InitTemp.PreError = 0;
    PositionPID_InitTemp.Integral = 0;
		
		PositionPidInit(&PositionX_PID);
	
	  PositionPID_InitTemp.Kp = 1.8;//0.004;
		PositionPidInit(&PositionY_PID);	

   TrajectCorrectPID.Kp=5.0f;
		PositionPidInit(&TrajectCorrectPID);

//    /*½Ç¶È*/
    PosePID.Kp =4.0f;
    PosePID.Ki = 0.0; 
    PosePID.Kd =0;
    PosePID.LimitOutput = 450 ; 
    PosePID.LimitIntegral = 5;
    PosePID.Integral = 0;
    PosePID.PreError = 0;
		
		
	  PositionInit(&ChassisInstance);	
		
    ImuModuleInit();
}



void PositionInit(ChassisInfoTypedef* ChassisInfo)
{
	ChassisInfo->X_Bias = 0.0f;//(PathInforms[0].PathDotsInfoArray)->X;
	ChassisInfo->Y_Bias = 0.0f;//(PathInforms[0].PathDotsInfoArray)->Y;
	ChassisInfo->Alpha_Bias = 0.0f;// (PathInforms[0].PathDotsInfoArray)->Alpha;	
	
	ChassisInfo->X_Correct = 0.0f;
	ChassisInfo->Y_Correct = 0.0f;
	ChassisInfo->Alpha_Correct = 0.0f;
	
	ChassisInfo->OriginX = 0.0f;
	ChassisInfo->OriginY = 0.0f;
	ChassisInfo->OriginAlpha = 0.0f;
	
	

	ChassisInfo->AimState.X = 0.0f;//(PathInforms[0].PathDotsInfoArray)->X;
	ChassisInfo->AimState.Y = 0.0f;//(PathInforms[0].PathDotsInfoArray)->Y;
	ChassisInfo->AimState.Alpha =0.0f;//(PathInforms[0].PathDotsInfoArray)->Alpha;
	
	ChassisInfo->CurrentState.X= 0.0f;//(PathInforms[0].PathDotsInfoArray)->X;
	ChassisInfo->CurrentState.Y=0.0f;//(PathInforms[0].PathDotsInfoArray)->Y;
	ChassisInfo->CurrentState.Alpha=0.0f;//(PathInforms[0].PathDotsInfoArray)->Alpha;
	
	
	ChassisInfo->AimState.Vx = 0;
	ChassisInfo->AimState.Vy = 0;
	ChassisInfo->AimState.w = 0;
	
	
	ChassisInstance.Mode = PARKING;
	ChassisInstance.NavigatePathNum = 0;
}

