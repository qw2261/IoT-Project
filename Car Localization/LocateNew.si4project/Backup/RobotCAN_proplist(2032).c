#include "RobotCAN_Basic.h"
#include "RobotCAN_Proplist.h"
//属性和方法的字典，用来查找

FunDict CAN1_PROP_Array[] = 
{
		{GET_SINGLE_MOTOR_SPEED, GetSingleMotorSpeed},
};

FunDict CAN2_PROP_Array[] = 
{
	{GET_SINGLE_MOTOR_SPEED,GetSingleMotorSpeed},
		{GET_LOCATE_INFO, GetLocateInfo},
};

const uint8_t CAN1_PROP_COUNT = sizeof(CAN1_PROP_Array)/sizeof(CAN1_PROP_Array[0]);
const uint8_t CAN2_PROP_COUNT = sizeof(CAN2_PROP_Array)/sizeof(CAN2_PROP_Array[0]);
