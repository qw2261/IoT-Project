#include "includes.h"
#include "system_config.h"
#include "com_prop.h"
#include "chassis.h"
#include "RobotCAN_Proplist.h"

void TaskIndicate(void *p_arg)
{
    OS_ERR err;
    while(1)
    {
			LED_Toggle(GREEN_LED);
			
			OSTimeDlyHMSM(0, 0, 1, 0, OS_OPT_TIME_HMSM_STRICT, &err);
			
		}

}

void TaskMonitor(void *p_arg)
{
   OS_ERR err;
    while(1)
    {
//			if(fabs(ChassisInstance.AimState.X-ChassisInstance.CurrentState.X)>300.0f)  
//			{
//				ChassisInstance.Mode = CHASSIS_DISABLE;
//				SendSetMotorsCtrl(0x0);
//			}
		
     OSTimeDlyHMSM(0, 0, 0, 20, OS_OPT_TIME_HMSM_STRICT, &err);
    }

}

/***********communicate**********/
u8 status=0;
void TaskCom(void *p_arg)
{
	OS_ERR err;
	
	while(1)
		{
			switch(status)
			{
				case 0:
				  LocateInfo_Send(&ChassisInstance);
				  AimLocateInfo_Send(&ChassisInstance);
				  status++;
					break;
				case 1:
					MotorsSpeed_Send(&ChassisInstance);
					MotorsAimSpeed_Send(&ChassisInstance);
				  status++;
					break;
				case 2:
					ChassisMode_Send(&ChassisInstance);
				  status = 0;
					break;
			}
			Chassis_Pos_Send(&ChassisInstance);
						
			OSTimeDlyHMSM(0, 0, 0, 5,OS_OPT_TIME_HMSM_STRICT, &err);
		
		}    
}


void TaskLocate(void *p_arg)
{
    OS_ERR err;
	static uint32_t i=0;
    while(1)
    {			
      UpdateChassisInfo(&ChassisInstance);
	  i++;
	  if(i%2 == 0)
//	  	ZY_VisualScope_Send(ChassisInstance.CurrentState.Vx*10,ChassisInstance.CurrentState.Vy*10,ENCODER_ARRAY[0].Speed*10,ENCODER_ARRAY[1].Speed*10);
			OSTimeDlyHMSM(0, 0, 0, 1, OS_OPT_TIME_HMSM_STRICT, &err);			
		}

}