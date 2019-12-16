#include "hpfilter.h"

float testin[1024]=
{0.0f};
float testout[1024]={0.0f};   //采样频率1KHZ,截至频率15HZ




float32_t  Scalevalue1 = 0.9892959049403619f;
float32_t  Scalevalue2 = 0.97132449733676085f;
float32_t  Scalevalue3 = 0.95654322555687676f;
float32_t  Scalevalue4 = 0.94608307884220311f;
float32_t  Scalevalue5 = 0.94067508119380239f;

arm_biquad_cascade_df2T_instance_f32 SFilter;

float32_t  IIRState[2*NUMSTAGES];

float32_t IIRCoeffsHP[5*NUMSTAGES] = {
1.0f , -2.0f , 1.0f , 1.9766377324327391f , -0.98054588732870851f,        
1.0f , -2.0f , 1.0f , 1.94073041471636f   , -0.94456757463068353f,        
1.0f , -2.0f , 1.0f , 1.9111970674260732f , -0.91497583480143385f,        
1.0f , -2.0f , 1.0f , 1.8902974350918498f , -0.89403488027696243f,        
1.0f , -2.0f , 1.0f , 1.8794921217822989f , -0.8832082029929107f 
};





void arm_iir_f32_hp_Init()
{
	u32 i=1024;
	
	for(i=0;i<1024;i++)
	{
		testin[i]=1.2f*arm_sin_f32(2*PI*5*i/1000)+arm_sin_f32(2*PI*100*i/1000);
	}
		/*初始化*/
	arm_biquad_cascade_df2T_init_f32(&SFilter, NUMSTAGES, (float32_t *)&IIRCoeffsHP[0], (float32_t*)&IIRState[0]);
}



/*********************************************************************************************************
*        函数名  : arm_iir_f32_hp
*        功能说明:调用arm_iir_f32_hp实现高通滤波
*        形    参:输入,输出信号,信号采样点数
*        返回值  :无 
*********************************************************************************************************/
void arm_iir_f32_hp(float32_t *SignalIn,float32_t *SignalOut,u32 Sample_Lenth)
{
	uint32_t i;
	
	float32_t  ScaleValue = Scalevalue1 * Scalevalue2 * Scalevalue3 * Scalevalue4 * Scalevalue5;
	
	/*IIR滤波*/
	
	arm_biquad_cascade_df2T_f32(&SFilter, SignalIn, SignalOut, Sample_Lenth);
	
	/*放缩系数*/
	
	for(i=0;i<Sample_Lenth;i++)
	{
		SignalOut[i] = SignalOut[i]*ScaleValue;
	}
	
}