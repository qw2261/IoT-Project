#ifndef ROBOTCAN_PROPLIST_H_
#define ROBOTCAN_PROPLIST_H_

#include "RobotCAN_Basic.h"
#include "Locate.h"


/******************LOCATE-DRIVER,CAN1*****************************/


/*************prop属性值,8位******************************/

//Locate-->drivers,发送帧属性
#define SET_MOTORS_SPEED	   	  		     0x00   //发送帧,设定驱动速度
#define SET_MOTORS_CTRL         			   0x01   //发送帧,使能驱动
#define SEND_LOCATE_INFO         			   0x02  //发送帧,使能驱动

//driver-->Locate,接收帧属性
#define GET_SINGLE_MOTOR_SPEED  			   0x02   //接收帧,接收底盘速度
/********************************************************/


/************prio发送优先级,4位*****************************/

//chassis-->drivers
#define SET_MOTORS_SPEED_PRIO 	         0x1    //发送速度优先级   
#define SET_MOTORS_CTRL_PRIO             0x2    //使能驱动优先级 
#define SEND_LOCATE_INFO_PRIO			0x1    //发送定位优先级 

/****************************************************************/







/*****************************************CAN1,CAN2分隔*******************************************/






/*********************LOCATE-MASTER,CAN2******************************/


///*****************prop,属性值8位********************************/
////Locate-->Master,发送帧属性
//#define CHASSIS_CUR_MODE                 0x01   //发送帧属性, 发送底盘当前模式 
//#define LOCATE_INFO             		     0x02   //发送帧属性, 发送底盘当前位置信息
//#define AIM_LOCATE_INFO                  0X03   //发送帧属性, 发送底盘目标位置信息
//#define FEED_MOTORS_SPEED       		     0x04   //发送帧属性, 发送底盘电机速度
//#define MOTORS_AIM_SPEED                 0x05   //发送帧属性, 发送底盘电机目标速度



////Master-->Locate,接收帧属性
#define GET_LOCATE_INFO  			   0x0A   //接收帧,接收底盘定位信息
#define GET_PATH_CHANGE  			   0x0B   //接收帧,接收底盘定位信息

//#define CHASSIS_MODE            		     0x06   //接收帧属性, 接收底盘模式、
//#define CHASSIS_POS                      0x07   //接收帧属性, 接收在线路径目标位置
///**************************************************************/


///***************prio,优先级4位********************************/

////locate-->master
//#define LOCATE_INFO_PRIO 			  				 0x1  
//#define FEED_MOTORS_SPEED_PRIO       		 0x2
//#define AIM_LOCATE_INFO_PRIO             0x3
//#define MOTORS_AIM_SPEED_PRIO            0x4 
//#define CHASSIS_CUR_MODE_PRIO            0x5


/***************************************************************/








/**********************接收函数*********************************/

void GetSingleMotorSpeed(Frame* frm);                       //CAN1接收部分


void GetLocateInfo(Frame* frm);

void GetPathChange(Frame* frm);


/*****************************************************************/



/***********************发送函数*******************************/

#ifdef MECANNUM_WHEEL
void SendSetMotorsSpeed(s16 v1,s16 v2,s16 v3,s16 v4);        //CAN1发送部分
#else
void SendSetMotorsSpeed(s16 v1,s16 v2,s16 v3);        //CAN1发送部分
#endif
void SendSetMotorsCtrl(uint8_t MotorEn);







/**************************************************************/

#endif
