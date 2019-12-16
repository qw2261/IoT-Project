#include "RobotCAN_Proplist.h"
#include "RobotCAN_Basic.h"
#include "RobotCAN_IDconf.h"
#include "Elmo.h"
#include "delay.h"
#define CHASSIS_CAN    CAN1
#ifdef MECANNUM_WHEEL
void SendSetMotorsSpeed(s16 v1,s16 v2,s16 v3,s16 v4)
{
	
//	Frame   Frame_tsm;
//	EXT_ID_Typedef* ExtID = &(Frame_tsm.id.ExtID);

//	ExtID->Priority    =  SET_MOTORS_SPEED_PRIO;
//	ExtID->DesDeviceId =  CHASSIS_BROADCAST_ID;
//	ExtID->SrcDeviceId =  DEVICE_ID;
//	ExtID->Property    =  SET_MOTORS_SPEED;

//	Frame_tsm.isRemote = 0;
//	Frame_tsm.length = 8;

//	Frame_tsm.data.shorts[0] = v1;
//	Frame_tsm.data.shorts[1] = v2;
//	Frame_tsm.data.shorts[2] = v3;
//	Frame_tsm.data.shorts[3] = v4;

//    SendFrame(&Frame_tsm,CHASSIS_CAN);
}
#else
void SendSetMotorsSpeed(s16 v1,s16 v2,s16 v3)
{
//	Frame   Frame_tsm;
//	EXT_ID_Typedef* ExtID = &(Frame_tsm.id.ExtID);

//	ExtID->Priority    =  SET_MOTORS_SPEED_PRIO;
//	ExtID->DesDeviceId =  CHASSIS_MOTOR1_ID;
//	ExtID->SrcDeviceId =  DEVICE_ID;
//	ExtID->Property    =  SET_MOTORS_SPEED;

//	Frame_tsm.isRemote = 0;
//	Frame_tsm.length = 6;

//	Frame_tsm.data.shorts[0] = v1;
//	Frame_tsm.data.shorts[1] = v2;
//	Frame_tsm.data.shorts[2] = v3;

//    SendFrame(&Frame_tsm,CHASSIS_CAN);
}

#endif



void SendSetMotorsCtrl(uint8_t MotorEn)
{
    /* Transmit */
//    Frame  Frame_tsm;
//    EXT_ID_Typedef* ExtID = &(Frame_tsm.id.ExtID);
//    
//	ExtID->Priority    =  SET_MOTORS_CTRL_PRIO ;
//	ExtID->DesDeviceId =  CHASSIS_MOTOR1_ID;
//	ExtID->SrcDeviceId =  DEVICE_ID;
//	ExtID->Property    =  SET_MOTORS_CTRL;

//    Frame_tsm.isRemote = 0;
//    Frame_tsm.length = 1;

//    Frame_tsm.data.uchars[0] = MotorEn;

//    SendFrame(&Frame_tsm,CHASSIS_CAN);
}


void SendLocateInfo(short X, short Y, short OriginX, char PathNum, char Mode)
{
    /* Transmit */
//    Frame  Frame_tsm;
//    EXT_ID_Typedef* ExtID = &(Frame_tsm.id.ExtID);
//    
//	ExtID->Priority    =  SEND_LOCATE_INFO_PRIO ;
//	ExtID->DesDeviceId =  UP_MACHINE_BROADCAST_ID;
//	ExtID->SrcDeviceId =  DEVICE_ID;
//	ExtID->Property    =  SEND_LOCATE_INFO;

//    Frame_tsm.isRemote = 0;
//    Frame_tsm.length = 8;

//    Frame_tsm.data.shorts[0] = X;
//    Frame_tsm.data.shorts[1] = Y;
//	Frame_tsm.data.shorts[2] = OriginX;
//	Frame_tsm.data.chars[6] = PathNum;
//	Frame_tsm.data.chars[7] = Mode;
//    SendFrame(&Frame_tsm,CAN2);
}



/***************************************CAN1,CAN2º¯Êý·Ö¸î******************************************/








