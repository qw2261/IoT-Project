#ifndef __ELMO
#define __ELMO
#include "stm32f4xx.h"
#include "RobotCAN_Proplist.h"
#include "RobotCAN_Basic.h"
#include "RobotCAN_IDconf.h"

#define	COB_NMT				0
#define	COB_SYNC			1
#define	COB_TIME_STAMP		2
#define	COB_EMERGENCY		1
#define	COB_TPDO1			3
#define	COB_RPDO1			4
#define	COB_TPDO2			5
#define	COB_RPDO2			6
#define	COB_TPDO3			7
#define	COB_RPDO3			8
#define	COB_TPDO4			9
#define	COB_RPDO4			10
#define	COB_TSDO			11
#define	COB_RSDO			12
#define	COB_ERROR_CONTROL	14

#define SPEED_PARA		(1000*4*23/60)

#define	MOTOR1_DIR		(-1)
#define	MOTOR2_DIR		(-1)
#define	MOTOR3_DIR		(-1)
#define	MOTOR4_DIR		(-1)

#define	BUILD_COB(COB_ID,DEV_ID)	(COB_ID<<7 | DEV_ID)

typedef union
{
	uint32_t	all;
	struct
	{
		uint32_t DeviceId		:7;
		uint32_t COB_ID		:4;
	}ID;
}STD_ID_Typedef;

typedef struct 
{
	float PositionExpected;
	float PositionMeasure;
	float SpeedExpected;
	float SpeedMeasure;
}MotorTypeDef;
void ProcessElmoFrame(Frame* Frame_Process);
void StopTPDO(uint8_t TPDONum, uint8_t DevId);
void SetPVFeedBack(uint8_t TPDONum, uint8_t DevId);
void SetEventTimer(uint8_t TPDONum, uint8_t DevId, uint8_t Time);
void ActivateTPDO(uint8_t TPDONum, uint8_t DevId);
void NMT_StartNode(void);
void MotorOn(void);
void MotorOff(void);
void SpeedUpdate(int32_t Speed1, int32_t Speed2,int32_t Speed3, int32_t Speed4);
void SetSingleMotorSpeed(int32_t Speed, int32_t DevId);
void ElmoInit(void);

#endif