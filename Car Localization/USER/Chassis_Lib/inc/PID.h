// Author:    @HustRobocon 
// Date:       2014-12-01
/* File brief:  PID�ṹ�嶨�壬PID���ں�������
*/

#ifndef  __PID_H
#define  __PID_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

/***PID�����ṹ***/
typedef  struct 
{
		float Kp;
		float Ki;
		float Kd;
		float LimitOutput;  //Lower Limit for Output limitation
		float LimitIntegral;  //Upper Limit for Output limitation
		float Integral; //������,�洢��������KI
		float PreError;
	  float du;
		float PrePreError;
}PID_StructTypedef;



float PidRegulate(float Reference, float PresentFeedback,PID_StructTypedef *PID_Struct);

#endif
