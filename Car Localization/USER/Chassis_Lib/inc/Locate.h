#ifndef  _LOCATE_H
#define  _LOCATE_H

#include "chassis.h"

//install correct parameter,���̰�װ�������ϵ��
#define INSTALL_DISTANCE       		 124.0f 	//����������������������߳���
#define INSTALL_ORIENTATE_DEG     (0.0f)//��������ϵ�����������ϵ�н�,ƫ�������˵���ƫС�����˵�
#define INSTALL_THETA          		 3.1415926f/4   //��������������˵��������������������ϵ�н�,������

#define INSTALL_ORIENTATE 		(INSTALL_ORIENTATE_DEG * DEG2RAD)

#define Theta2 0.76354016419966700000 

#define Theta1 0.78607926247162700000  
 
 
 

 




void UpdateChassisInfo(ChassisInfoTypedef* ChassisInfo);
void ImuModuleInit();
void UpdateLaserLocate(void);

#endif 
/******************* (C) COPYRIGHT 2017 HUST-Robocon-Team *****END OF FILE****/
