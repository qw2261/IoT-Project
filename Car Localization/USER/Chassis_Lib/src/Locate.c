/* Includes ------------------------------------------------------------------*/
#include "Encoder.h"
#include "Imu.h"
#include "arm_math.h"
#include "stdbool.h"
#include "globalTime.h"
#include "Locate.h"
#include "usart.h"

/*
*********************************************************************************************************
*                           所有角度制在此文件中转为弧度制
*********************************************************************************************************
*/


typedef struct
{
	float X;
	float Y;
	float Alpha;
	
	float Vx;	
	float Vy;
	float w;
	
	float Orientate;
	float InstallDis;
	float InstallTheta;

}IMU_MODULE_Typedef;



IMU_MODULE_Typedef ImuMoudle;


void ImuModuleInit()
{
	  
	  Imu.Angle = 0;
		Imu.dAngle = 0;
	  Imu.LastAngle = 0;
	  //Imu.ZeroDriftRate = ImuInitNormal();
	  Imu.Rate = 0.0f;	
}

void ImuModuleLocate(ChassisInfoTypedef *ChassisInfo)
{
	float ImuMoudleDeltaX;
	float ImuMoudleDeltaY;
	float ImuMoudleAlpha;
	
	float RoboticDeltaX,RoboticDeltaY,RoboticVx,RoboticVy;
	
	//ImuProcess();
	Imu.Angle = angle3;
	Imu.Rate = rate3;
	
	ENCx_Read(ENC3);
	ENCx_Read(ENC2);
	
	RoboticDeltaX = ENCODER_ARRAY[ENC_X].DeltaDistance;	
	RoboticDeltaY = ENCODER_ARRAY[ENC_Y].DeltaDistance;
	
	RoboticVx = ENCODER_ARRAY[ENC_X].Speed;	
	RoboticVy = ENCODER_ARRAY[ENC_Y].Speed;
	
	ImuMoudleAlpha = Imu.Angle * DEG2RAD + ChassisInfo->Alpha_Bias; //弧度
	
	//change into global coordinate
	ImuMoudleDeltaX = RoboticDeltaX * arm_cos_f32(ImuMoudleAlpha) - RoboticDeltaY * arm_sin_f32(ImuMoudleAlpha);
	ImuMoudleDeltaY = RoboticDeltaX * arm_sin_f32(ImuMoudleAlpha) + RoboticDeltaY * arm_cos_f32(ImuMoudleAlpha);

//		ImuMoudleDeltaX = RoboticDeltaX * arm_cos_f32(ImuMoudleAlpha) - (RoboticDeltaY-RoboticDeltaX*arm_cos_f32(Theta1+Theta2))/arm_sin_f32(Theta1+Theta2) * arm_sin_f32(ImuMoudleAlpha);
//		ImuMoudleDeltaY = RoboticDeltaX * arm_cos_f32(Theta1+Theta2-ImuMoudleAlpha) + (RoboticDeltaY-RoboticDeltaX*arm_cos_f32(Theta1+Theta2))/arm_sin_f32(Theta1+Theta2) * arm_sin_f32(Theta1+Theta2-ImuMoudleAlpha);

		
	//update Chassis Info
	ImuMoudle.Alpha = ImuMoudleAlpha;
	ImuMoudle.w  = Imu.Rate * DEG2RAD; 
	ImuMoudle.X += ImuMoudleDeltaX;
	ImuMoudle.Y += ImuMoudleDeltaY;
	
	ImuMoudle.Vx = RoboticVx * arm_cos_f32(ImuMoudleAlpha) - RoboticVy * arm_sin_f32(ImuMoudleAlpha);
	ImuMoudle.Vy = RoboticVx * arm_sin_f32(ImuMoudleAlpha) + RoboticVy * arm_cos_f32(ImuMoudleAlpha);	

//	ImuMoudle.Vx = RoboticVx * arm_cos_f32(ImuMoudleAlpha) - (RoboticVy-RoboticVx*arm_cos_f32(Theta1+Theta2))/arm_sin_f32(Theta1+Theta2) * arm_sin_f32(ImuMoudleAlpha);
//	ImuMoudle.Vy = RoboticVx * arm_cos_f32(Theta1+Theta2-ImuMoudleAlpha) + (RoboticVy-RoboticVx*arm_cos_f32(Theta1+Theta2))/arm_sin_f32(Theta1+Theta2) * arm_sin_f32(Theta1+Theta2-ImuMoudleAlpha);
	


	ImuMoudle.InstallDis = INSTALL_DISTANCE;
	ImuMoudle.Orientate = INSTALL_ORIENTATE;
	ImuMoudle.InstallTheta = INSTALL_THETA;

}


void UpdateChassisInfo(ChassisInfoTypedef *ChassisInfo)
{
	float ImuMoudleOrientate = ImuMoudle.Orientate;
	float ImuModuleDis = ImuMoudle.InstallDis;
	float ImuMoudleTheta = ImuMoudle.InstallTheta;
	ChassisStateTypedef *Chassis = &(ChassisInfo->CurrentState);
	
	ImuModuleLocate(&ChassisInstance);
	
	/****************码盘+陀螺仪初始定出来的位置信息************************/
	ChassisInfo->OriginAlpha = ImuMoudle.Alpha;
	
	ChassisInfo->OriginX = ImuMoudle.X*arm_cos_f32(ImuMoudleOrientate) - ImuMoudle.Y * arm_sin_f32(ImuMoudleOrientate)
	         + ImuModuleDis * arm_cos_f32(ImuMoudle.Alpha + ImuMoudleTheta)
	         - ImuModuleDis * arm_cos_f32(ImuMoudleTheta)
	         + ChassisInfo->X_Bias ;
	
	ChassisInfo->OriginY = ImuMoudle.X * arm_sin_f32(ImuMoudleOrientate)+ImuMoudle.Y * arm_cos_f32(ImuMoudleOrientate)
	         + ImuModuleDis * arm_sin_f32(ImuMoudle.Alpha + ImuMoudleTheta)
	         - ImuModuleDis * arm_sin_f32(ImuMoudleTheta)
	         + ChassisInfo->Y_Bias ;
		

//				ChassisInfo->OriginX =ImuMoudle.X* arm_sin_f32(Theta1) - (ImuMoudle.Y-ImuMoudle.X*arm_cos_f32(Theta1+Theta2))/arm_sin_f32(Theta1+Theta2) * arm_cos_f32(Theta1)
//	         + ImuModuleDis * arm_cos_f32(ImuMoudle.Alpha   - ChassisInfo->Alpha_Bias + ImuMoudleTheta)
//	         - ImuModuleDis * arm_cos_f32(ImuMoudleTheta)
//	         + ChassisInfo->X_Bias;
//				
//				ChassisInfo->OriginY =(ImuMoudle.X* arm_cos_f32(Theta1) + (ImuMoudle.Y-ImuMoudle.X*arm_cos_f32(Theta1+Theta2))/arm_sin_f32(Theta1+Theta2) * arm_sin_f32(Theta1)
//	         + ImuModuleDis * arm_sin_f32(ImuMoudle.Alpha  - ChassisInfo->Alpha_Bias + ImuMoudleTheta)
//	         - ImuModuleDis * arm_sin_f32(ImuMoudleTheta))
//	         + ChassisInfo->Y_Bias	;		
	ChassisInfo->CurrentState.Vx = ImuMoudle.Vx * arm_cos_f32(ImuMoudle.Orientate) - ImuMoudle.Vy * arm_sin_f32(ImuMoudle.Orientate);
	ChassisInfo->CurrentState.Vy = ImuMoudle.Vx * arm_sin_f32(ImuMoudle.Orientate) + ImuMoudle.Vy * arm_cos_f32(ImuMoudle.Orientate);	
	ChassisInfo->CurrentState.w = ImuMoudle.w;

	ChassisInfo->CurrentState.X = ChassisInfo->OriginX ;
	ChassisInfo->CurrentState.Y = ChassisInfo->OriginY ;
	ChassisInfo->CurrentState.Alpha = ChassisInfo->OriginAlpha;
}

void UpdateLaserLocate(void)
{
//	float ImuMoudleOrientate = ImuMoudle.Orientate;
//	float ImuModuleDis = ImuMoudle.InstallDis;
//	float ImuMoudleTheta = ImuMoudle.InstallTheta;
//	float c1,c2;
//	c1 = ChassisInstance.CurrentState.X - ChassisInstance.X_Bias + ImuModuleDis * arm_cos_f32(ImuMoudleTheta) - ImuModuleDis * arm_cos_f32(ImuMoudle.Alpha   - ChassisInstance.Alpha_Bias+ ImuMoudleTheta) ;
//	c2 = ChassisInstance.CurrentState.Y - ChassisInstance.Y_Bias + ImuModuleDis * arm_sin_f32(ImuMoudleTheta) - ImuModuleDis * arm_sin_f32(ImuMoudle.Alpha   - ChassisInstance.Alpha_Bias + ImuMoudleTheta);

//	ImuMoudle.X = 0.720933770831931*c1 + 0.693003966853042*c2;
//	ImuMoudle.Y = -0.685469165623185*c1 + 0.730915248791854*c2;
			ChassisInstance.X_Correct =  ChassisInstance.CurrentState.X - ChassisInstance.OriginX ;
			ChassisInstance.Y_Correct =  ChassisInstance.CurrentState.Y - ChassisInstance.OriginY ;

}
/******************* (C) COPYRIGHT 2017 HUST-Robocon-Team *****END OF FILE****/
