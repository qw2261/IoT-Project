#include "ELMO.h"
#include "delay.h"

MotorTypeDef Motor1, Motor2, Motor3, Motor4;
MotorTypeDef* MotorAll[4] = { &Motor1, &Motor2, &Motor3, &Motor4};

void ProcessElmoFrame(Frame* Frame_Process)
{
  STD_ID_Typedef	StdId;
  StdId.all = Frame_Process->id.StdID;
  if(StdId.ID.COB_ID == COB_TPDO3)
	{
		if(StdId.ID.DeviceId < 5)
		{
		MotorAll[StdId.ID.DeviceId - 1]->SpeedMeasure = (float)(Frame_Process->data.ints[0])/SPEED_PARA;
		MotorAll[StdId.ID.DeviceId - 1]->PositionMeasure = Frame_Process->data.ints[1];
		ChassisInstance.CurrentState.wheelsW[StdId.ID.DeviceId - 1] =  MotorAll[StdId.ID.DeviceId - 1]->SpeedMeasure ;
		}
//		else
//		{
//		MotorAll[2]->SpeedMeasure = Frame_Process->data.ints[0];
//		MotorAll[2]->PositionMeasure = Frame_Process->data.ints[1];
//		}
	}
  
}
void StopTPDO(uint8_t TPDONum, uint8_t DevId)
{
	CanTxMsg TxMessage;
	uint16_t i = 0;
	uint8_t TransmitMailbox = CAN_TxStatus_NoMailBox;	
	uint16_t  time_out_count = 0;
	TxMessage.StdId = BUILD_COB(COB_RSDO, DevId);
	TxMessage.IDE = CAN_ID_STD;
	TxMessage.RTR = CAN_RTR_DATA;
	TxMessage.DLC = 3;

	TxMessage.Data[0] = 0x2f;			//DSP 301  4-2  P22
	TxMessage.Data[1] = TPDONum/2 - 1;
	TxMessage.Data[2] = 0x1a;
	TxMessage.Data[3] = 0;
	TxMessage.Data[4] = 0;
	TxMessage.Data[5] = 0;
	TxMessage.Data[6] = 0;
	TxMessage.Data[7] = 0;
	while((TransmitMailbox == CAN_TxStatus_NoMailBox) && (time_out_count++ != 0xFF))
	{
		TransmitMailbox = CAN_Transmit(CAN1, &TxMessage);
	}

}
void SetPVFeedBack(uint8_t TPDONum, uint8_t DevId)
{
	CanTxMsg TxMessage;
	uint16_t i = 0;
	uint8_t TransmitMailbox = CAN_TxStatus_NoMailBox;	
	uint16_t  time_out_count = 0;
	TxMessage.StdId = BUILD_COB(COB_RSDO, DevId);
	TxMessage.IDE = CAN_ID_STD;
	TxMessage.RTR = CAN_RTR_DATA;
	TxMessage.DLC = 8;
	/*Position*/
	TxMessage.Data[0] = 0x23;			//DSP 301  4-2  P22
	TxMessage.Data[1] = TPDONum/2 - 1;
	TxMessage.Data[2] = 0x1a;
	TxMessage.Data[3] = 0x01;
	TxMessage.Data[4] = 0x20;
	TxMessage.Data[5] = 0;
	TxMessage.Data[6] = 0x69;
	TxMessage.Data[7] = 0x60;


	while((TransmitMailbox == CAN_TxStatus_NoMailBox) && (time_out_count++ != 0xFF))
	{
		TransmitMailbox = CAN_Transmit(CAN1, &TxMessage);
	}

	TransmitMailbox = CAN_TxStatus_NoMailBox;
	time_out_count = 0;
	TxMessage.StdId = BUILD_COB(COB_RSDO, DevId);
	TxMessage.IDE = CAN_ID_STD;
	TxMessage.RTR = CAN_RTR_DATA;
	TxMessage.DLC = 8;
	/*velocity*/
	TxMessage.Data[0] = 0x23;			//DSP 301  4-2  P22
	TxMessage.Data[1] = TPDONum/2 - 1;
	TxMessage.Data[2] = 0x1a;
	TxMessage.Data[3] = 0x02;
	TxMessage.Data[4] = 0x20;
	TxMessage.Data[5] = 0;
	TxMessage.Data[6] = 0x64;
	TxMessage.Data[7] = 0x60;


	while((TransmitMailbox == CAN_TxStatus_NoMailBox) && (time_out_count++ != 0xFF))
	{
		TransmitMailbox = CAN_Transmit(CAN1, &TxMessage);
	}
}
void SetEventTimer(uint8_t TPDONum, uint8_t DevId, uint8_t Time)
{
	CanTxMsg TxMessage;
	uint16_t i = 0;
	uint8_t TransmitMailbox = CAN_TxStatus_NoMailBox;	
	uint16_t  time_out_count = 0;

	TxMessage.StdId = BUILD_COB(COB_RSDO, DevId);
	TxMessage.IDE = CAN_ID_STD;
	TxMessage.RTR = CAN_RTR_DATA;
	TxMessage.DLC =8;

	/*Event Timer*/
	TxMessage.Data[0] = 0x2f;			//DSP 301  4-2  P22
	TxMessage.Data[1] = TPDONum/2 - 1;
	TxMessage.Data[2] = 0x18;
	TxMessage.Data[3] = 0x05;
	TxMessage.Data[4] = Time;
	TxMessage.Data[5] = 0;
	TxMessage.Data[6] = 0;
	TxMessage.Data[7] = 0;
	while((TransmitMailbox == CAN_TxStatus_NoMailBox) && (time_out_count++ != 0xFF))
	{
		TransmitMailbox = CAN_Transmit(CAN1, &TxMessage);
	}

	
	TransmitMailbox = CAN_TxStatus_NoMailBox;
	time_out_count = 0;
	TxMessage.StdId = BUILD_COB(COB_RSDO, DevId);
	TxMessage.IDE = CAN_ID_STD;
	TxMessage.RTR = CAN_RTR_DATA;
	TxMessage.DLC = 8;


	
		/*Transmit PDO communication parameter 0xfe*/
	TxMessage.Data[0] = 0x2f;			//DSP 301  4-2  P22
	TxMessage.Data[1] = TPDONum/2 - 1;
	TxMessage.Data[2] = 0x18;
	TxMessage.Data[3] = 0x02;
	TxMessage.Data[4] = 0xfe;
	TxMessage.Data[5] = 0;
	TxMessage.Data[6] = 0;
	TxMessage.Data[7] = 0;
	while((TransmitMailbox == CAN_TxStatus_NoMailBox) && (time_out_count++ != 0xFF))
	{
		TransmitMailbox = CAN_Transmit(CAN1, &TxMessage);
	}

}
void ActivateTPDO(uint8_t TPDONum, uint8_t DevId)
{
	CanTxMsg TxMessage;
	uint16_t i = 0;
	uint8_t TransmitMailbox = CAN_TxStatus_NoMailBox;	
	uint16_t  time_out_count = 0;
	TxMessage.StdId = BUILD_COB(COB_RSDO, DevId);
	TxMessage.IDE = CAN_ID_STD;
	TxMessage.RTR = CAN_RTR_DATA;
	TxMessage.DLC = 5;

	TxMessage.Data[0] = 0x2f;			//DSP 301  4-2  P22
	TxMessage.Data[1] = TPDONum/2 - 1;
	TxMessage.Data[2] = 0x1a;
	TxMessage.Data[3] = 0;
	TxMessage.Data[4] = 2;				//active 2 mapped objects
	TxMessage.Data[5] = 0;
	TxMessage.Data[6] = 0;
	TxMessage.Data[7] = 0;
	while((TransmitMailbox == CAN_TxStatus_NoMailBox) && (time_out_count++ != 0xFF))
	{
		TransmitMailbox = CAN_Transmit(CAN1, &TxMessage);
	}

}
void NMT_StartNode(void)
{
	CanTxMsg TxMessage;
	uint16_t i = 0;
	uint8_t TransmitMailbox = CAN_TxStatus_NoMailBox;	
	uint16_t  time_out_count = 0;
	TxMessage.StdId = 0;
	TxMessage.IDE = CAN_ID_STD;
	TxMessage.RTR = CAN_RTR_DATA;
	TxMessage.DLC = 2;

	TxMessage.Data[0] = 1;			//DSP 301  4-2  P22
	TxMessage.Data[1] = 0;
	TxMessage.Data[2] = 0;
	TxMessage.Data[3] = 0;
	TxMessage.Data[4] = 0;
	TxMessage.Data[5] = 0;
	TxMessage.Data[6] = 0;
	TxMessage.Data[7] = 0;
	while((TransmitMailbox == CAN_TxStatus_NoMailBox) && (time_out_count++ != 0xFF))
	{
		TransmitMailbox = CAN_Transmit(CAN1, &TxMessage);
	}

}
void MotorOn(void)
{
	CanTxMsg TxMessage;
	uint8_t i = 0;
	uint8_t TransmitMailbox = CAN_TxStatus_NoMailBox;	
	uint16_t  time_out_count = 0;
	TxMessage.StdId = 0;
	TxMessage.IDE = CAN_ID_STD;
	TxMessage.RTR = CAN_RTR_DATA;
	TxMessage.DLC = 8;

		TxMessage.Data[0] = 'J';
	TxMessage.Data[1] = 'V';
	TxMessage.Data[2] = 0;
	TxMessage.Data[3] = 0;
	TxMessage.Data[4] = 0;
	TxMessage.Data[5] = 0;
	TxMessage.Data[6] = 0;
	TxMessage.Data[7] = 0;
			for(i = 1; i < 5; i++)
		{
			TxMessage.StdId = BUILD_COB(COB_RPDO2, i);
			time_out_count = 0;
			TransmitMailbox = CAN_TxStatus_NoMailBox;	
			while((TransmitMailbox == CAN_TxStatus_NoMailBox) && (time_out_count++ != 0xFF))
			{
				TransmitMailbox = CAN_Transmit(CAN1, &TxMessage);
			}
			MyDelayus(10);
		}

	TxMessage.Data[0] = 'M';
	TxMessage.Data[1] = 'O';
	TxMessage.Data[2] = 0;
	TxMessage.Data[3] = 0;
	TxMessage.Data[4] = 1;
	TxMessage.Data[5] = 0;
	TxMessage.Data[6] = 0;
	TxMessage.Data[7] = 0;

	for(i = 1; i < 5; i++)
		{
			TxMessage.StdId = BUILD_COB(COB_RPDO2, i);
			time_out_count = 0;
			TransmitMailbox = CAN_TxStatus_NoMailBox;	
			while((TransmitMailbox == CAN_TxStatus_NoMailBox) && (time_out_count++ != 0xFF))
			{
				TransmitMailbox = CAN_Transmit(CAN1, &TxMessage);
			}
			MyDelayus(10);
		}
		


}
void MotorOff(void)
{
	CanTxMsg TxMessage;
	uint8_t i = 0;
	uint8_t TransmitMailbox = CAN_TxStatus_NoMailBox;	
	uint16_t  time_out_count = 0;
	TxMessage.StdId = 0;
	TxMessage.IDE = CAN_ID_STD;
	TxMessage.RTR = CAN_RTR_DATA;
	TxMessage.DLC = 8;

	TxMessage.Data[0] = 'M';
	TxMessage.Data[1] = 'O';
	TxMessage.Data[2] = 0;
	TxMessage.Data[3] = 0;
	TxMessage.Data[4] = 0;
	TxMessage.Data[5] = 0;
	TxMessage.Data[6] = 0;
	TxMessage.Data[7] = 0;

	for(i = 1; i < 5; i++)
		{
			TxMessage.StdId = BUILD_COB(COB_RPDO2, i);
			time_out_count = 0;
			TransmitMailbox = CAN_TxStatus_NoMailBox;	
			while((TransmitMailbox == CAN_TxStatus_NoMailBox) && (time_out_count++ != 0xFF))
			{
				TransmitMailbox = CAN_Transmit(CAN1, &TxMessage);
			}
			MyDelayus(10);
		}
		
	TxMessage.Data[0] = 'J';
	TxMessage.Data[1] = 'V';
	TxMessage.Data[2] = 0;
	TxMessage.Data[3] = 0;
	TxMessage.Data[4] = 0;
	TxMessage.Data[5] = 0;
	TxMessage.Data[6] = 0;
	TxMessage.Data[7] = 0;
			for(i = 1; i < 5; i++)
		{
			TxMessage.StdId = BUILD_COB(COB_RPDO2, i);
			time_out_count = 0;
			TransmitMailbox = CAN_TxStatus_NoMailBox;	
			while((TransmitMailbox == CAN_TxStatus_NoMailBox) && (time_out_count++ != 0xFF))
			{
				TransmitMailbox = CAN_Transmit(CAN1, &TxMessage);
			}
			MyDelayus(10);
		}
}
void SetSingleMotorSpeed(int32_t Speed, int32_t DevId)
{
	CanTxMsg TxMessage;
	uint16_t i = 0;
	uint8_t TransmitMailbox = CAN_TxStatus_NoMailBox;	
	uint16_t  time_out_count = 0;

	MotorAll[DevId - 1]->SpeedExpected = (float)Speed/SPEED_PARA;
	ChassisInstance.AimState.wheelsW[DevId - 1] = MotorAll[DevId - 1]->SpeedExpected;
	
	TxMessage.IDE = CAN_ID_STD;
	TxMessage.RTR = CAN_RTR_DATA;
	TxMessage.DLC = 8;

	TxMessage.Data[0] = 'J';			//DSP 301  4-2  P22
	TxMessage.Data[1] = 'V';
	TxMessage.Data[2] = 0;
	TxMessage.Data[3] = 0;

	TxMessage.StdId = BUILD_COB(COB_RPDO2, DevId);
	TxMessage.Data[4] = Speed & 0xff;
	TxMessage.Data[5] = (Speed >> 8) & 0xff;
	TxMessage.Data[6] = (Speed >> 16) & 0xff;
	TxMessage.Data[7] = (Speed >> 24) & 0xff;
	while((TransmitMailbox == CAN_TxStatus_NoMailBox) && (time_out_count++ != 0xFF))
	{
		TransmitMailbox = CAN_Transmit(CAN1, &TxMessage);
	}
//	MyDelayus(10);

	TxMessage.StdId = BUILD_COB(COB_RPDO2, DevId);
	TxMessage.DLC = 4;
	TxMessage.Data[0] = 'B';
	TxMessage.Data[1] = 'G';
	TxMessage.Data[2] = 0;
	TxMessage.Data[3] = 0;
	TxMessage.Data[4] = 0;
	TxMessage.Data[5] = 0;
	TxMessage.Data[6] = 0;
	TxMessage.Data[7] = 0;
	time_out_count = 0;
	TransmitMailbox = CAN_TxStatus_NoMailBox;	
	while((TransmitMailbox == CAN_TxStatus_NoMailBox) && (time_out_count++ != 0xFF))
	{
		TransmitMailbox = CAN_Transmit(CAN1, &TxMessage);
	}
}
void SpeedUpdate(int32_t Speed1, int32_t Speed2,int32_t Speed3,int32_t Speed4)
{
	SetSingleMotorSpeed(MOTOR1_DIR*Speed1, 1);
	SetSingleMotorSpeed(MOTOR2_DIR*Speed2, 2);
	SetSingleMotorSpeed(MOTOR3_DIR*Speed3, 3);
	SetSingleMotorSpeed(MOTOR4_DIR*Speed4, 4);
}

void ElmoInit(void)
{
		StopTPDO(COB_TPDO3,1);
	MyDelayms(1);
	SetPVFeedBack(COB_TPDO3,1);
		MyDelayms(1);
	SetEventTimer(COB_TPDO3, 1, 10);
		MyDelayms(1);
	ActivateTPDO(COB_TPDO3, 1);
		MyDelayms(1);
	
	StopTPDO(COB_TPDO3,2);
	MyDelayms(1);
	SetPVFeedBack(COB_TPDO3,2);
		MyDelayms(1);
	SetEventTimer(COB_TPDO3, 2, 10);
		MyDelayms(1);
	ActivateTPDO(COB_TPDO3, 2);
		MyDelayms(1);
		
			StopTPDO(COB_TPDO3,3);
	MyDelayms(1);
	SetPVFeedBack(COB_TPDO3,3);
		MyDelayms(1);
	SetEventTimer(COB_TPDO3, 3, 10);
		MyDelayms(1);
	ActivateTPDO(COB_TPDO3, 3);
		MyDelayms(1);
		
			StopTPDO(COB_TPDO3,4);
	MyDelayms(1);
	SetPVFeedBack(COB_TPDO3,4);
		MyDelayms(1);
	SetEventTimer(COB_TPDO3,4, 10);
		MyDelayms(1);
	ActivateTPDO(COB_TPDO3,4 );
		MyDelayms(1);
		
		
	NMT_StartNode();
			MyDelayms(1);
	MotorOn();}

