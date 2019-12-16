#ifndef __SYSTEM_CONFIG_H
#define __SYSTEM_CONFIG_H
#include "stm32f4xx.h"

#include "stdbool.h"

#include "delay.h"

#include "path.h"

#include "com_prop.h"

#define SYSTEM_SUPPORT_UCOS       1
#define _USE_LED
//#define _USE_BEEP
#define _USE_SWITCH
#define _USE_MYUSART1
#define _USE_MYUSART2
//#define _USE_DMA
//#define _USE_IMU
//#define _USE_ENCODER1
#define _USE_ENCODER2
#define _USE_ENCODER3
//#define _USE_BLUE
#define _USE_RED
#define _USE_MOTOR


#ifdef _USE_LED
#include "Led.h"
#endif


#if defined(_USE_MYUSART1) || defined(_USE_MYUSART2)
#include "Usart.h"
#endif

#ifdef _USE_IMU
#include "Imu.h"
#endif

#if defined(_USE_ENCODER1) || defined(_USE_ENCODER2) || defined(_USE_ENCODER3)
#include "Encoder.h"
#endif

#ifdef _USE_SWITCH
#include "Switch.h"
#endif

#ifdef _USE_BEEP
#include "Beep.h"
#endif

#ifdef _USE_MOTOR
#include "Motor.h"
#endif

#include "ZY_VisualScope.h"


void System_Init(void);

#endif
