/**
  ******************************************************************************
  * @file    app_pid.c
  * @author  HUST-Robocon-Team
  * @version V1.0
  * @date    2013-11-22
  * @brief   
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 HUST-Robocon-Team </center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "pid.h"
 /**
 * @brief PID调节函数
 * @param PID输出，float
 * @retval float 设定值，测量值，PID结构
 */
float PidRegulate(float Reference,float PresentFeedback,
		PID_StructTypedef *PID_Struct)
{
	float error;
	float error_inc;
	float pTerm;
	float iTerm;
	float dTerm;
	float dwAux;
	float output;
	/*error computation*/
	error = Reference - PresentFeedback;
	
	/*proportional term computation*/
	pTerm = error * PID_Struct->Kp;
	/*Integral term computation*/
	if (PID_Struct->Ki == 0)
	{
		PID_Struct->Integral = 0;           
  } 
	else
	{
		iTerm = error * PID_Struct->Ki;
		dwAux = PID_Struct->Integral + iTerm;
		/*limit integral*/
		if (dwAux > PID_Struct->LimitIntegral)
		{
			PID_Struct->Integral = PID_Struct->LimitIntegral;
		} else if (dwAux < -1*PID_Struct->LimitIntegral)
		{
			PID_Struct->Integral = -1*PID_Struct->LimitIntegral;
		} else
		{
			PID_Struct->Integral = dwAux;
		}
	}
	/*differential term computation*/
	
	error_inc = error - PID_Struct->PreError;
	dTerm = error_inc * PID_Struct->Kd;
	PID_Struct->PrePreError = PID_Struct->PreError;
	PID_Struct->PreError = error;

	output = pTerm + PID_Struct->Integral + dTerm;

	/*limit output*/
	if (output >= PID_Struct->LimitOutput)
	{
		return (PID_Struct->LimitOutput);
	} else if (output < -1*PID_Struct->LimitOutput)
	{
		return (-1*PID_Struct->LimitOutput);
	} else
	{
		return output;
	}
}


/******************* (C) COPYRIGHT 2013 HUST-Robocon-Team *****END OF FILE****/
