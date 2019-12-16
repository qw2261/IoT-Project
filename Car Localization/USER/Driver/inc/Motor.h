#ifndef _SERVO_H
#define _SERVO_H
#include "stm32f4xx.h" 
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_rcc.h"

void Motor1_Init(uint32_t arr,uint32_t psc);
void Motor2_Init(uint32_t arr,uint32_t psc);
void SetMotor1(int16_t pwm);  
void SetMotor2(int16_t pwm); 
void SetMotor3(int16_t pwm);  
void SetMotor4(int16_t pwm); 

#endif
