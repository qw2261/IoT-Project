#include "includes.h"
#include "system_config.h"
#include "com_prop.h"
#include "chassis.h"
#include "RobotCAN_Proplist.h"
#include "globalTime.h"

void TaskIndicate(void *p_arg)
{
    OS_ERR err;
    while(1)
    {
			LED_Toggle(GREEN_LED);
			
			OSTimeDlyHMSM(0, 0, 1, 0, OS_OPT_TIME_HMSM_STRICT, &err);
			
		}

}
uint32_t tt = 0,nn = 0;
bool sendflag = true;
uint16_t tmp = 0,tmp1 = 0;
bool take_photo = false;
bool goback = false;
void TaskMonitor(void *p_arg)
{
   OS_ERR err;
	 uint16_t now_t_us,d_t_us;
    while(1)
    {
			if(take_photo == true )
			{
				SEND_SINGAL = 1;
				tt ++;
			}
			if(tt > 500 && take_photo == true)
			{
				 SEND_SINGAL = 0;
				tt =0;
				take_photo = false;
				goback = true;
			}
			if (goback == true)
			{
				nn++;
			}
			if(nn > 100)
			{
				nn =0 ;
			  goback = false;
				target = 0;
			}
			
			
		
     OSTimeDlyHMSM(0, 0, 0,10, OS_OPT_TIME_HMSM_STRICT, &err);
    }

}

/***********communicate**********/
u8 status=0;
void TaskCom(void *p_arg)
{
	OS_ERR err;
	  u8 count = 0;
	  
		while(1)
		{
			count++;
			
			if(count%10 == 0)
			{
//				CurrentSend(&ChassisInstance);
//				CurrentSend2(&ChassisInstance);
  		}
			
			
			
			OSTimeDlyHMSM(0, 0, 0, 10, OS_OPT_TIME_HMSM_STRICT, &err);
					
		} 
}


void TaskLocate(void *p_arg)
{
    OS_ERR err;
	static uint32_t i=0;
    while(1)
    {			
      UpdateChassisInfo(&ChassisInstance);
		
//	  i++;
//	  if(i%2 == 0)
//    	ZY_VisualScope_Send(ChassisInstance.CurrentState.Vx*10,ChassisInstance.CurrentState.Vy*10,ENCODER_ARRAY[0].Speed*10,ENCODER_ARRAY[1].Speed*10);
			OSTimeDlyHMSM(0, 0, 0, 5, OS_OPT_TIME_HMSM_STRICT, &err);			
		}

}