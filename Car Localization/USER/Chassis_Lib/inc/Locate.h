#ifndef  _LOCATE_H
#define  _LOCATE_H

#include "chassis.h"

//install correct parameter,码盘安装误差修正系数
#define INSTALL_DISTANCE       		 124.0f 	//码盘中心与机器人中心连线长度
#define INSTALL_ORIENTATE_DEG     (0.0f)//码盘坐标系与机器人坐标系夹角,偏大往正了调，偏小往负了调
#define INSTALL_THETA          		 3.1415926f/4   //码盘中心与机器人的中心连线与机器人坐标系夹角,弧度制

#define INSTALL_ORIENTATE 		(INSTALL_ORIENTATE_DEG * DEG2RAD)

#define Theta2 0.76354016419966700000 

#define Theta1 0.78607926247162700000  
 
 
 

 




void UpdateChassisInfo(ChassisInfoTypedef* ChassisInfo);
void ImuModuleInit();
void UpdateLaserLocate(void);

#endif 
/******************* (C) COPYRIGHT 2017 HUST-Robocon-Team *****END OF FILE****/
