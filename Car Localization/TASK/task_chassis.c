#include "chassis.h"
#include "RobotCAN_Proplist.h"
#include "path.h"
#include "com_prop.h"
#include "Elmo.h"
extern uint8_t PathChange;
void chassisOneCircle(void);
uint8_t source=0;


void TaskChassis(void *p_arg)
{	
    OS_ERR err;
    while(1)
    {
			if(source == 0 && target == 1)
			{
				ChassisInstance.NavigatePathNum = 0;
				ChassisInstance.Mode = NAVIGATE;
				source = 1;
			}
			else if(source == 0 && target == 2)
			{
				ChassisInstance.NavigatePathNum = 1;
				ChassisInstance.Mode = NAVIGATE;
				source = 2;
			}
			else if(source == 1 && target == 0)
			{
				ChassisInstance.NavigatePathNum = 2;
				ChassisInstance.Mode = NAVIGATE;
				source = 0;
			}
			else if(source == 2 && target == 0)
			{
				ChassisInstance.NavigatePathNum = 3;
				ChassisInstance.Mode = NAVIGATE;
				source = 0;
			}
			else if(source == 1 && target == 2)
			{
				ChassisInstance.NavigatePathNum = 4;
				ChassisInstance.Mode = NAVIGATE;
				source = 2;
			}
			else if(source == 2 && target == 1)
			{
				ChassisInstance.NavigatePathNum = 5;
				ChassisInstance.Mode = NAVIGATE;
				source = 1;
			}
//			else
//			{
//				ChassisInstance.Mode = PARKING;
//			}

			
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
		//chassisNavigate(&ChassisInstance,&PathInforms[0]);
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
		//SendSetMotorsSpeed(0,0,0,0);
		#else
		//SendSetMotorsSpeed(0,0,0);
		#endif
	}
	else if(ChassisInstance.Mode == CHASSIS_DISABLE)
	{
		ChassisInstance.AimState.X = ChassisInstance.CurrentState.X;
		ChassisInstance.AimState.Y = ChassisInstance.CurrentState.Y;
		ChassisInstance.AimState.Alpha = ChassisInstance.CurrentState.Alpha;
//		SendSetMotorsCtrl(0x0);
		
	}
	else
	{
		ChassisInstance.AimState.X = ChassisInstance.CurrentState.X;
		ChassisInstance.AimState.Y = ChassisInstance.CurrentState.Y;
		ChassisInstance.AimState.Alpha = ChassisInstance.CurrentState.Alpha;
	}
}
