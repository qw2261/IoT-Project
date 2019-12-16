/* Includes ------------------------------------------------------------------*/
#include "chassis.h"
#include "RobotCAN_Proplist.h"
#include "Motor.h"

#ifdef MECANNUM_WHEEL
float WheelsSignX[WHEELS_NUM]={1,1,-1,-1};
float WheelsSignY[WHEELS_NUM]={1,-1,-1,1};
#endif

float WheelsThetaSinTab[WHEELS_NUM]={0.0f,-0.4330127019f,0.4330127019f};
float WheelsThetaCosTab[WHEELS_NUM]={1.0f,-0.25f,-0.25f};
float DIS_WHEELS2CENTER[WHEELS_NUM]={541.6142157f,541.6142157f,541.6142157f};
	
	
//brief:Calculate the wheels angle velocity in accord with target global velocity and alpha
//Note:the Velocities of the wheels under Right-hand rule 
//para: ChasisInfo: a pointer to the an instant of ChasisInfoTypedef
//func : update the wheels velocities of ChasisInfo->AimState
void wheelsVectorCal(ChassisInfoTypedef* ChasisInfo)
{
	int WheelsIndex;
	//chage Chassis State into robotic coordinate
	//a contentious issue here
	float RobotChassisAimVx = 
		+ ChasisInfo->AimState.Vx * arm_cos_f32(ChasisInfo->CurrentState.Alpha)
		+ ChasisInfo->AimState.Vy * arm_sin_f32(ChasisInfo->CurrentState.Alpha);
	float RobotChassisAimVy = 
		- ChasisInfo->AimState.Vx * arm_sin_f32(ChasisInfo->CurrentState.Alpha)
		+ ChasisInfo->AimState.Vy * arm_cos_f32(ChasisInfo->CurrentState.Alpha);

	float RobotChassisAimW = ChasisInfo->AimState.w;
	
	float WheelsW[WHEELS_NUM] = {0.0f};
	
	
	for(WheelsIndex = 0;WheelsIndex < WHEELS_NUM;WheelsIndex++)
	{
//  	WheelsW[WheelsIndex] = 
//		 ( ( RobotChassisAimVx * WheelsThetaSinTab[WheelsIndex]
//		    + RobotChassisAimVy * WheelsThetaCosTab[WheelsIndex]
//			  + RobotChassisAimW * DIS_WHEELS2CENTER[WheelsIndex])/WHEELS_RADIUS )* RAD_PER_SECOND_2RPM;
	#ifdef MECANNUM_WHEEL
		 WheelsW[WheelsIndex] = 
		  ( (RobotChassisAimVx * WheelsSignX[WheelsIndex]
			   + RobotChassisAimVy * WheelsSignY[WheelsIndex]
		     - RobotChassisAimW  * HalfPerimeter/2)/WHEELS_RADIUS)* RAD_PER_SECOND_2RPM;
	#else
  	 WheelsW[WheelsIndex] = 
		  ( ( RobotChassisAimVx * WheelsThetaSinTab[WheelsIndex]
		    + RobotChassisAimVy * WheelsThetaCosTab[WheelsIndex]
			  + RobotChassisAimW * DIS_WHEELS2CENTER[WheelsIndex])/WHEELS_RADIUS )* RAD_PER_SECOND_2RPM;

	#endif
	}
	
	#ifdef MECANNUM_WHEEL
  //SendSetMotorsSpeed(WheelsW[0],WheelsW[1],WheelsW[2],WheelsW[3]);
	SetMotor1(WheelsW[0]*1.5);
	SetMotor2(WheelsW[1]*1.5);
	SetMotor3(WheelsW[2]*1.5);
	SetMotor4(WheelsW[3]*1.5);
	
	#else
	
	#endif
}




