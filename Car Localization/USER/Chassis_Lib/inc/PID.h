// Author:    @HustRobocon 
// Date:       2014-12-01
/* File brief:  PID结构体定义，PID调节函数声明
*/

#ifndef  __PID_H
#define  __PID_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

/***PID参数结构***/
typedef  struct 
{
		float Kp;
		float Ki;
		float Kd;
		float LimitOutput;  //Lower Limit for Output limitation
		float LimitIntegral;  //Upper Limit for Output limitation
		float Integral; //积分项,存储积分误差×KI
		float PreError;
	  float du;
		float PrePreError;
}PID_StructTypedef;



float PidRegulate(float Reference, float PresentFeedback,PID_StructTypedef *PID_Struct);

#endif
