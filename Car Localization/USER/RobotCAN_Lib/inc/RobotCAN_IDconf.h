#ifndef ROBOTCAN_IDCONF_H_
#define ROBOTCAN_IDCONF_H_

#include "stm32f4xx_can.h"
#include "RobotCAN_device.h"


#define DEVICE_ID     LOCATE_ID
#define BROADCAST_ID  CHASSIS_BROADCAST_ID


#if     (DEVICE_ID == LOCATE_ID)
#define DEVICE_SECOND_ID   LOCATE_SECOND_ID

#elif  (DEVICE_ID == MASTER_ID)
#define DEVICE_SECOND_ID   MASTER_SECOND_BOARD_ID
           
#else
#define SLAVER_DEVICE
#define DEVICE_SECOND_ID  BROADCAST_ID 
#endif

#define	FILTER_ID														DEVICE_ID
#define FILTER_SECOND_ID                    DEVICE_SECOND_ID
#define FILTER_MASK      0x000000ff
#endif /*ROBOT_CAN_CONF_H_*/

