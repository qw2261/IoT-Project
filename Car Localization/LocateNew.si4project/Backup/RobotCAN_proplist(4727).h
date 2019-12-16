#ifndef ROBOTCAN_PROPLIST_H_
#define ROBOTCAN_PROPLIST_H_

#include "RobotCAN_Basic.h"
#include "Locate.h"


/******************LOCATE-DRIVER,CAN1*****************************/


/*************prop����ֵ,8λ******************************/

//Locate-->drivers,����֡����
#define SET_MOTORS_SPEED	   	  		     0x00   //����֡,�趨�����ٶ�
#define SET_MOTORS_CTRL         			   0x01   //����֡,ʹ������
#define SEND_LOCATE_INFO         			   0x02  //����֡,ʹ������

//driver-->Locate,����֡����
#define GET_SINGLE_MOTOR_SPEED  			   0x02   //����֡,���յ����ٶ�
/********************************************************/


/************prio�������ȼ�,4λ*****************************/

//chassis-->drivers
#define SET_MOTORS_SPEED_PRIO 	         0x1    //�����ٶ����ȼ�   
#define SET_MOTORS_CTRL_PRIO             0x2    //ʹ���������ȼ� 
#define SEND_LOCATE_INFO_PRIO			0x1    //���Ͷ�λ���ȼ� 

/****************************************************************/







/*****************************************CAN1,CAN2�ָ�*******************************************/






/*********************LOCATE-MASTER,CAN2******************************/


///*****************prop,����ֵ8λ********************************/
////Locate-->Master,����֡����
//#define CHASSIS_CUR_MODE                 0x01   //����֡����, ���͵��̵�ǰģʽ 
//#define LOCATE_INFO             		     0x02   //����֡����, ���͵��̵�ǰλ����Ϣ
//#define AIM_LOCATE_INFO                  0X03   //����֡����, ���͵���Ŀ��λ����Ϣ
//#define FEED_MOTORS_SPEED       		     0x04   //����֡����, ���͵��̵���ٶ�
//#define MOTORS_AIM_SPEED                 0x05   //����֡����, ���͵��̵��Ŀ���ٶ�



////Master-->Locate,����֡����
#define GET_LOCATE_INFO  			   0x0A   //����֡,���յ��̶�λ��Ϣ
#define GET_PATH_CHANGE  			   0x0B   //����֡,���յ��̶�λ��Ϣ

//#define CHASSIS_MODE            		     0x06   //����֡����, ���յ���ģʽ��
//#define CHASSIS_POS                      0x07   //����֡����, ��������·��Ŀ��λ��
///**************************************************************/


///***************prio,���ȼ�4λ********************************/

////locate-->master
//#define LOCATE_INFO_PRIO 			  				 0x1  
//#define FEED_MOTORS_SPEED_PRIO       		 0x2
//#define AIM_LOCATE_INFO_PRIO             0x3
//#define MOTORS_AIM_SPEED_PRIO            0x4 
//#define CHASSIS_CUR_MODE_PRIO            0x5


/***************************************************************/








/**********************���պ���*********************************/

void GetSingleMotorSpeed(Frame* frm);                       //CAN1���ղ���


void GetLocateInfo(Frame* frm);

void GetPathChange(Frame* frm);


/*****************************************************************/



/***********************���ͺ���*******************************/

#ifdef MECANNUM_WHEEL
void SendSetMotorsSpeed(s16 v1,s16 v2,s16 v3,s16 v4);        //CAN1���Ͳ���
#else
void SendSetMotorsSpeed(s16 v1,s16 v2,s16 v3);        //CAN1���Ͳ���
#endif
void SendSetMotorsCtrl(uint8_t MotorEn);







/**************************************************************/

#endif
