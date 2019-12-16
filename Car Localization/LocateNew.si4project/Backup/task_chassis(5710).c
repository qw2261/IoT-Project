#include "chassis.h"
#include "RobotCAN_Proplist.h"
#include "path.h"
#include "com_prop.h"
void chassisOneCircle(void);

void TaskChassis(void *p_arg)
{	
    OS_ERR err;
    while(1)
    {
			chassisOneCircle();
			OSTimeDlyHMSM(0, 0, 0, 5, OS_OPT_TIME_HMSM_STRICT, &err);
    }
}




ChassisInfoTypedef  ChassisInstance;

void chassisOneCircle(void)
{
	
	//only when the former value is parking or test can the mode be transfered to NAVIGATE
	if(ChassisInstance.Mode == NAVIGATE)
	{
		chassisNavigate(&ChassisInstance,&PathInforms[ChassisInstance.NavigatePathNum]);
	}
	else if(ChassisInstance.Mode == PARKING)
	{
		chassisParking(&ChassisInstance);
	}
	else if(ChassisInstance.Mode == ON_LINE&&IsPosRecv)
	{
	  chassisOnline(&ChassisInstance);
	}
	else if(ChassisInstance.Mode == STALL)
	{
		ChassisInstance.AimState.X = ChassisInstance.CurrentState.X;
		ChassisInstance.AimState.Y = ChassisInstance.CurrentState.Y;
		ChassisInstance.AimState.Alpha = ChassisInstance.CurrentState.Alpha;
		#ifdef MECANNUM_WHEEL
		SendSetMotorsSpeed(0,0,0,0);
		#else
		SendSetMotorsSpeed(0,0,0);
		#endif
	}
	else if(ChassisInstance.Mode == CHASSIS_DISABLE)
	{
		ChassisInstance.AimState.X = ChassisInstance.CurrentState.X;
		ChassisInstance.AimState.Y = ChassisInstance.CurrentState.Y;
		ChassisInstance.AimState.Alpha = ChassisInstance.CurrentState.Alpha;
		SendSetMotorsCtrl(0x0);
	}
	else
	{
		ChassisInstance.AimState.X = ChassisInstance.CurrentState.X;
		ChassisInstance.AimState.Y = ChassisInstance.CurrentState.Y;
		ChassisInstance.AimState.Alpha = ChassisInstance.CurrentState.Alpha;
	}
}
