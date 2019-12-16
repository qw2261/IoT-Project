#ifndef __IMU_H
#define __IMU_H

#include "stm32f4xx.h"
#include "stdbool.h"

#define INSTALL_ANGLE          180
#define IMU_IF_DIR_INVERSE    1


#define IMU_INVALIDE_TIME 			1000
#define IMU_INTEGRAL_TIME 			5000
#define IMU_RATE_DEAD  					0.1f//0.04f


#define ADC_CORRECT_COEFF      1.0025601802059043499785469501209f   // 1.002575577f

#define ADC_FULL_SCALE_MV 			8192.0f
#define ANALOG_GAIN    					0.2f
#define ADC_FULL_DIGITAL				0XFFFFFF
#define IMU_DEG_PER_SECOND_2MV   46.7f




#define ADC_COEFF               (ADC_FULL_SCALE_MV/ADC_FULL_DIGITAL / ANALOG_GAIN /IMU_DEG_PER_SECOND_2MV * ADC_CORRECT_COEFF)

#define IMU_SPI              		SPI1       
#define IMU_GPIO_AF_SPI      		GPIO_AF_SPI1
#define RCC_IMU_SPI_CLK         RCC_APB2Periph_SPI1
#define RCC_IMU_SPI_CLK_CMD    	RCC_APB2PeriphClockCmd 

#define IMU_SCK_PIN        			GPIO_Pin_5
#define IMU_SCK_PORT        		GPIOA	     
#define IMU_SCK_CLK							RCC_AHB1Periph_GPIOA
#define IMU_SCK_PINSOURCE    		GPIO_PinSource5

#define IMU_SDI_PIN        			GPIO_Pin_7
#define IMU_SDI_PORT        		GPIOA     
#define IMU_SDI_CLK							RCC_AHB1Periph_GPIOA
#define IMU_SDI_PINSOURCE    		GPIO_PinSource7 

#define IMU_SDO_PIN        			GPIO_Pin_6
#define IMU_SDO_PORT        		GPIOA	     
#define IMU_SDO_CLK							RCC_AHB1Periph_GPIOA
#define IMU_SDO_PINSOURCE    		GPIO_PinSource6

#define IMU_CS_PIN         			GPIO_Pin_15	
#define IMU_CS_PORT        			GPIOA	     
#define IMU_CS_CLK					  	RCC_AHB1Periph_GPIOA

#define IMU_RESET_PIN         	GPIO_Pin_1
#define IMU_RESET_PORT        	GPIOB	     
#define IMU_RESET_CLK						RCC_AHB1Periph_GPIOB

#define IMU_SYNC_PIN         		GPIO_Pin_0
#define IMU_SYNC_PORT        		GPIOB	     
#define IMU_SYNC_CLK						RCC_AHB1Periph_GPIOB

#define IMU_RDY_PIN          		GPIO_Pin_4  
#define IMU_RDY_PORT        		GPIOC	     
#define IMU_RDY_CLK							RCC_AHB1Periph_GPIOC


#define	ADC_CS_NC      	 				GPIO_SetBits(IMU_CS_PORT,IMU_CS_PIN )
#define	ADC_CS_CHOOSE     			GPIO_ResetBits(IMU_CS_PORT,IMU_CS_PIN )

#define	IS_ADC_RDY   						GPIO_ReadInputDataBit(IMU_RDY_PORT, IMU_RDY_PIN) 




extern float Fusing_Data;
extern float Fusing_K ;
extern bool IsImageRec ;
extern float Image_angle;




/*ÍÓÂÝÒÇ½á¹¹Ìå*/
typedef struct 
{
	float Angle;     
	float Rate;     
	float dAngle;  
	float LastAngle;
	float ZeroDriftRate;	
}ImuTypedef;


extern volatile ImuTypedef Imu ;

void  ImuHardInit(void) ;
float ImuInitNormal(void);

void ImuProcess(void);
#endif 

/******************* (C) COPYRIGHT 2017 HUST-Robocon *****END OF FILE**********/
