#include "Imu.h"
#include "delay.h"
#include "arm_math.h"
#include "globalTime.h"
#include "includes.h"
#include "chassis.h"

volatile ImuTypedef Imu ;


float Fusing_Data = 0.0f;
float Fusing_K = 0.05f;
bool IsImageRec = false;
float Image_angle = 0.0f;



float Complementary_Filter(float Gyro_Rate,float Image_angle,float integraltime)
{
	if(IsImageRec)
	{
		Fusing_Data=Fusing_K*Image_angle+(1-Fusing_K)*(Fusing_Data+Gyro_Rate*integraltime*0.000001f);
		IsImageRec=false;
	}
	else
	{
		Fusing_Data=Fusing_Data+Gyro_Rate*integraltime*0.000001f;
	}
	return Fusing_Data;
}

//硬件SPI配置
void IMU_SPI_Init(void)	
{
	SPI_InitTypeDef  SPI_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	 
	RCC_AHB1PeriphClockCmd(IMU_SCK_CLK|IMU_SDI_CLK|IMU_SDO_CLK, ENABLE);   
	/*SPI GPIO Configuration
	*/
	GPIO_PinAFConfig(IMU_SCK_PORT,IMU_SCK_PINSOURCE,IMU_GPIO_AF_SPI);  
	GPIO_PinAFConfig(IMU_SDI_PORT,IMU_SDI_PINSOURCE,IMU_GPIO_AF_SPI);  
	GPIO_PinAFConfig(IMU_SDO_PORT,IMU_SDO_PINSOURCE,IMU_GPIO_AF_SPI);  
	/*SPI GPIO Configuration
	*/	
	GPIO_InitStructure.GPIO_Pin = IMU_SCK_PIN ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(IMU_SCK_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin =  IMU_SDI_PIN;    
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(IMU_SDI_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin =  IMU_SDO_PIN ;    
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(IMU_SDO_PORT, &GPIO_InitStructure);  
	
	RCC_IMU_SPI_CLK_CMD(RCC_IMU_SPI_CLK,ENABLE);
	
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256; 
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Init(IMU_SPI, &SPI_InitStructure);

	SPI_Cmd(IMU_SPI, ENABLE);   
}


void IMU_GPIO_Init(void)	
{
  GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(IMU_CS_CLK, ENABLE);   
	GPIO_InitStructure.GPIO_Pin = IMU_CS_PIN;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(IMU_CS_PORT, &GPIO_InitStructure);	
	GPIO_SetBits(IMU_CS_PORT, IMU_CS_PIN);
	
 
	RCC_AHB1PeriphClockCmd(IMU_RDY_CLK, ENABLE);   
	GPIO_InitStructure.GPIO_Pin =  IMU_RDY_PIN ;    
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(IMU_RDY_PORT, &GPIO_InitStructure); 

  RCC_AHB1PeriphClockCmd(IMU_RESET_CLK, ENABLE);   
	GPIO_InitStructure.GPIO_Pin = IMU_RESET_PIN;   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(IMU_RESET_PORT, &GPIO_InitStructure);	
	
  RCC_AHB1PeriphClockCmd(IMU_SYNC_CLK, ENABLE);   
	GPIO_InitStructure.GPIO_Pin = IMU_SYNC_PIN;  
  GPIO_Init(IMU_SYNC_PORT, &GPIO_InitStructure);		
	
	GPIO_ResetBits(IMU_RESET_PORT, IMU_RESET_PIN);	
	delay_us(10);
	GPIO_SetBits(IMU_SYNC_PORT, IMU_SYNC_PIN);
	GPIO_SetBits(IMU_RESET_PORT, IMU_RESET_PIN);	
	
}	


uint8_t SPI_WriteByte(SPI_TypeDef* SPIx,uint8_t Byte)
{
	while((SPIx->SR&SPI_I2S_FLAG_TXE) == RESET);		//等待发送区空	  
	SPIx->DR = Byte;	 	                            //发送一个byte   
	while((SPIx->SR&SPI_I2S_FLAG_RXNE) == RESET);   //等待接收完一个byte  
	return SPIx->DR;          	                    //返回收到的数据			
} 
/**
  * @brief  MCU向陀螺仪外设中写入一个字节数据，同时读取一个数据
  * @param  
  * @retval 
*/
uint8_t ADC_SPI_WriteDat(uint8_t Data)
{
	 uint8_t DatRec;
   ADC_CS_CHOOSE ;  //片选有效（低电平）
	 DatRec =  SPI_WriteByte(IMU_SPI,Data);
	 ADC_CS_NC;      //片选无效（高电平）x
	 return  DatRec;
}



/**
  * @brief  写寄存器
  * @param  
  * @retval 
*/
void ADC_SPI_WriteReg(unsigned char command,unsigned char data)
{
	ADC_CS_CHOOSE ;
  SPI_WriteByte(IMU_SPI,command);
  SPI_WriteByte(IMU_SPI,0x00);
  SPI_WriteByte(IMU_SPI,data);
	delay_us(1);
	ADC_CS_NC ; 
}

/**
  * @brief  陀螺仪硬件初始化
  * @param  
  * @retval 
*/

void ImuHardInit(void) 
{
		IMU_GPIO_Init();
		IMU_SPI_Init();


		while(IS_ADC_RDY){};
		ADC_SPI_WriteDat(0xf0);//Offset and Gain Self-Calibration
    delay_us(2);
			
		while(IS_ADC_RDY){};
		ADC_SPI_WriteDat(0xfe);//Reset to Power-Up Values
		delay_us(1);
					
		while(IS_ADC_RDY){};
		ADC_SPI_WriteReg(0x50,0x04);//STATUS REGISTER Bit 2 ACAL: Auto-Calibration
		delay_us(1);
			
		while(IS_ADC_RDY){};
		ADC_SPI_WriteReg(0x51,0x01);//Input Multiplexer Control Register  default
		delay_us(1);
			
		while(IS_ADC_RDY){};
		ADC_SPI_WriteReg(0x52,0x00);// A/D Control Register 
														//clock Clock Out Frequency = f CLKIN (default) ;
														//Sensor Detect OFF (default)
														//PGA = 1(default)
		delay_us(1);
			
		while(IS_ADC_RDY){};
		ADC_SPI_WriteReg(0x53,0xF0);// A/D Data Rate 30,000SPS (default)  Data rates scale linearly with fCLKIN.
		delay_us(1);
		
		while(IS_ADC_RDY){};
		ADC_SPI_WriteReg(0x54,0xE0);// GPIO Control Register   Reset Value = E0h
		delay_us(1);
		
		while(IS_ADC_RDY){};
		ADC_SPI_WriteDat(0xf0);			//Offset and Gain Self-Calibration
		delay_us(1);
}

//************角速度处理函数**************//
/**
  * @brief 返回原始的角速度寄存器值,用于陀螺仪标定
  * @param  
  * @retval 32位无符号整型(寄存器数据为24位无符号数据）
*/



int32_t ReadImuRateReg(void)
{
	uint8_t Reg_H,Reg_HH,Reg_HHH;
  int32_t RateRegTemp;
	
	
	while(IS_ADC_RDY);
	ADC_CS_CHOOSE ;
	SPI_WriteByte(IMU_SPI,0x01);
	delay_us(7);
	Reg_HHH = SPI_WriteByte(IMU_SPI,0x22);//ImuWriteDat(0x22);//发送无意义，在于接收
	Reg_HH = SPI_WriteByte(IMU_SPI,0x22);
	Reg_H = SPI_WriteByte(IMU_SPI,0x22);
	delay_us(1);
	ADC_CS_NC;
	RateRegTemp = (Reg_HHH<<16) + (Reg_HH<<8) + Reg_H;
	if(Reg_HHH & 0x80)
	{
		RateRegTemp -= 0x1000000; 
	}
//	if(RateRegTemp > 0x800008)
//	{
//		RateRegTemp -= 0x1000008; 
//	}

	if(IMU_IF_DIR_INVERSE)
	{
		RateRegTemp = -RateRegTemp;
	}
	return RateRegTemp;
}

/**
  * @brief  translate ADS reg value to tate
	* @param  void
	* @retval uint:deg/s
*/



float ReadImuRate(void)
{
	//	double a=1.406e-6,b=-4.462e-6,c=0.9982;
//	double a0=1.762142731716297,a1=-0.765497532041101,b1=-0.007490856568432,w=0.002098277621420;
//	 int32_t ImuReg = ReadImuRateReg();
//   float ImuTemp = ImuReg * ADC_COEFF;
////   double Correct = a*ImuTemp*ImuTemp + b*ImuTemp + c;
//	double wx=fabs(w*ImuTemp);
//	double Correct = a0+a1*arm_cos_f32(wx)+b1*arm_sin_f32(wx);
//	 float ImuRate =Correct*(ImuTemp - Imu.ZeroDriftRate);	
//	 return  ImuRate ;
	
	double a0=1.762142731716297,a1=-0.765497532041101,b1=-0.007490856568432,w=0.002098277621420;
	int32_t ImuReg = ReadImuRateReg();
	float ImuTemp = ImuReg * ADC_COEFF;
	float ImuRate = ImuTemp - Imu.ZeroDriftRate;
	double wx=fabs(ImuRate)*w;
	ImuRate = (a0+a1*arm_cos_f32(wx)+b1*arm_sin_f32(wx))*ImuRate;
	return ImuRate;
	
	
//	double a0=1.043014077148380,a1=-0.050971246528513,a2=0.004532776654977,b1=-0.005777232713031,b2=0.002238001533952,w=0.010354580027207;
//	int32_t ImuReg = ReadImuRateReg();
//	float ImuTemp = ImuReg * ADC_COEFF;
//	float ImuRate = ImuTemp - Imu.ZeroDriftRate;
//	double wx=ImuRate*w;
//	ImuRate = (a0+a1*arm_cos_f32(wx)+b1*arm_sin_f32(wx)+a2*arm_cos_f32(2*wx)+b2*arm_sin_f32(2*wx))*ImuRate;
//	return ImuRate;
	
	
//		 int32_t ImuReg = ReadImuRateReg();
//   float ImuTemp = ImuReg * ADC_COEFF;
//	 float ImuRate = ImuTemp - Imu.ZeroDriftRate;
//	 return  ImuRate ;
}
/**
  * @brief  读取陀螺仪角度值，对原始角速度值进行积分，角度数据写入陀螺仪结构体
  * @param  
  * @retval 
*/

void ImuProcess(void)
{
//	static bool IsFirstCalAngle;
//	static float ImuPreRate;
//	uint16_t now_time;
//	static uint16_t pre_time = 0;
//  uint16_t d_t;
//	float Imu_mid_rate;
//	
//	

//  Imu.Rate = ReadImuRate();
//	
//	now_time = DT_US_COUNT;	
//	
//	d_t = now_time - pre_time;
//	pre_time = now_time;
//	
//	if(IsFirstCalAngle == true)
//	{
//		ImuPreRate = Imu.Rate ; //全局变量
//		IsFirstCalAngle = false;
//	}
//	else
//	{
//		Imu_mid_rate = (Imu.Rate + ImuPreRate)*0.5f;
//		ImuPreRate   =  Imu.Rate; 
//		
//		if(fabs(Imu_mid_rate) <=  IMU_RATE_DEAD)
//		{
//			Imu_mid_rate = 0.0f;
//		}	
//		
//		Imu.LastAngle = Imu.Angle;
//		Imu.dAngle = Imu_mid_rate* d_t *0.000001f;
//		Imu.Angle += Imu.dAngle;
//		ChassisInstance.CurrentState.Alpha=Complementary_Filter(Imu_mid_rate,Image_angle,d_t) * DEG2RAD + ChassisInstance.Alpha_Bias;
//		//ChassisInstance.CurrentState.Alpha=imuaver* DEG2RAD;

//	}    	
}



/**
  * @brief  陀螺仪正常积分启动，需要时间较长
  * @param  
  * @retval 
*/	 
float ImuInitNormal(void)
{
	OS_ERR      err;
	float ImuRateTemp = 0;
	float ImuZeroDriftRate = 0;
	int i = 0;
	
	for(i = 0 ;i < IMU_INVALIDE_TIME ;i++)
	{
		ImuRateTemp = ReadImuRate();
		OSTimeDlyHMSM(0, 0,0, 1, OS_OPT_TIME_HMSM_STRICT, &err);
	}

	/*接下来5秒积分求均值计算零漂*/
	for(i = 0; i < IMU_INTEGRAL_TIME; i++)
	{
		ImuRateTemp = ReadImuRate();
		ImuZeroDriftRate += ImuRateTemp;
		OSTimeDlyHMSM(0, 0,0, 1, OS_OPT_TIME_HMSM_STRICT, &err);
	}
  //计算零偏和此刻的温度，用于矫正温漂
	ImuZeroDriftRate /= IMU_INTEGRAL_TIME;	
  
	return ImuZeroDriftRate;
}
