#ifndef COM_PROP_H
#define COM_PROP_H
#include "comLib.h"
#include "chassis.h"

extern bool IsPosRecv;

/*******************************************************************************
//帧属性 //限制大小64位
*******************************************************************************/
 
 
 /****************************串口1的发送帧属性**********************/
 #define MOTOR_PARA_SEND      5
 #define AIM_STATE_SEND       6

 #define SPEED_PID_SEND       7
 #define POS_PID_SEND         8
 #define CURRENT_PID_SEND     9

 #define EXT_IO_SEND          17
 #define SENSOR_SEND          18
 #define EXT_PARA_SEND        19

 #define SAMPLE_VALUE_STORAGE 20 
 /*******************************************************************/
 
 
 /***************************串口2的发送帧属性**********************/
 #define COM_CHASSIS_CUR_MODE           21      //发送底盘模式
 #define COM_LOCATE_INFO                22      //发送底盘当前位置
 #define COM_AIM_LOCATE_INFO            23      //发送底盘目标位置
 #define COM_FEED_MOTORS_SPEED          24      //发送底盘电机当前速度 
 #define COM_MOTORS_AIM_SPEED           25      //发送底盘电机目标速度
 /***************************串口2的发送帧属性**********************/
 #define COM_CHASSIS_MODE               26      //接收底盘目标模式
 #define COM_CHASSIS_POS                27      //接收在线路径目标 
 #define REGION_INFO                    28
 #define CHASSIS_SPEED            		30
 /*******************************************************************/


/*******************************************************************************
															  指令函数
*******************************************************************************/
void TestSend(float t1,float t2,float t3);
void CurrentSend(ChassisInfoTypedef *ChassisInfo);
void AimSend(ChassisInfoTypedef *ChassisInfo);
void CurrentSend2(ChassisInfoTypedef *ChassisInfo);



/**************************串口1发送函数***************************************/
void Chassis_Pos_Send(ChassisInfoTypedef *ChassisInfo);

/******************************************************************************/

/**************************串口1接收函数***************************************/
void PCCorrectChassisXYParaGet(DataType *Data);
void PCChassisAlphaGet(DataType *Data);
/******************************************************************************/



/***************************串口2发送函数**************************************/
void LocateInfo_Send(ChassisInfoTypedef* ChassisInfo);        
void MotorsSpeed_Send(ChassisInfoTypedef* ChassisInfo);
void AimLocateInfo_Send(ChassisInfoTypedef* ChassisInfo); 
void MotorsAimSpeed_Send(ChassisInfoTypedef* ChassisInfo);
void ChassisMode_Send(ChassisInfoTypedef* ChassisInfo);
void RegionInfoSend();
/******************************************************************************/



/***************************串口2接收函数*************************************/
void ChassisMode_Get(DataType* Data);                           
void ChassisPos_Get(DataType* Data);
void ChassisSpeedGet(DataType* Data);

/*****************************************************************************/





#endif // COM_PROP_H
