#include "system_config.h"
#include "Laser.h"

/*
				-----------------
				|					 |4				|
				|2				 |				3|
				|					 |	 				|
				|					 |				  |
				|				   |1				|
				-----------------
*/
/*µ½³µÐÄ¾àÀë*/
#define	L1_X		261.5f
#define	L1_Y		255.0f
#define	L2_X		46.0f
#define	L2_Y		442.8f
#define	L3_X		236.0f
#define	L3_Y		255.0f
#define	L4_X		25.0f
#define	L4_Y		443.5f

#define LazY1_FixErrY   311.4f
#define LazY1_FixErrX   125.0f

#define LazY2_FixErrY   384.0f
#define LazY2_FixErrX   110.0f

#define LazX1_FixErrY  213.0f
#define LazX2_FixErrY  227.0f
#define LazX_FixErrX   273.7f



//void AccoutTheta(void)
//{
//	float LazX_FixErrY = LazX1_FixErrY + LazX2_FixErrY ;
//	float tantheta = (DisX2 - DisX1)/LazX_FixErrY; 
//	Theta = atan(tantheta);
//}

//void AccoutX(void)
//{ 
//	DisX = (DisX1* LazX2_FixErrY + DisX2 *LazX1_FixErrY )/ (LazX1_FixErrY + LazX2_FixErrY);
//	WorldX = -7000 + arm_cos_f32(Theta)*(LazX_FixErrX + DisX) ; 
//}

//void AccoutY(void)
//{
//	float tempy = LazY_FixErrX * arm_sin_f32(Theta)/arm_cos_f32(Theta);
//	WorldY = -7000 + arm_cos_f32(Theta) *(DisY + LazY_FixErrY - tempy);
//}
/*
				-----------------
				|					 |4				|
				|1			 |				3|
				|					 |	 				|
				|					 |				  |
				|				   |2				|
				-----------------
*/
  float WorldY1, WorldY2 ;
float XX1,XX3,YY2,YY4;
void AcountAll(int16_t M1, int16_t M2, int16_t M3, int16_t M4, float *WorldX1, float *WorldY1,float *WorldX2, float *WorldY2,  float Theta)
{

	float X3 = (M3 + L3_X)*arm_cos_f32(Theta) - L3_Y*arm_sin_f32(Theta);
	float X1 = (M1 + L1_X)*arm_cos_f32(Theta) + L1_Y*arm_sin_f32(Theta);
	float Y4 = (M4 + L4_Y)*arm_cos_f32(Theta) + L4_X*arm_sin_f32(Theta);
	float Y2 = (M2 + L2_Y)*arm_cos_f32(Theta) - L2_X*arm_sin_f32(Theta);
	XX1= -7000 + 2130 - X1;
	XX3= -7000 + X3;
	YY2=7000 - Y2;
	YY4= -7000 + Y4;
	*WorldX1 = XX3;
	*WorldX2 = XX1;
	*WorldY1 = YY2;
	*WorldY2 = YY4;
//	float DisX  ,DisY1, DisY2;
//	float DisX2 = (float)M1 - 0.9f;
//  float DisX1 = (float)M2 + 0.9f;

//	float LazX_FixErrY = LazX1_FixErrY + LazX2_FixErrY ;
//	float tantheta = (DisX2 - DisX1)/LazX_FixErrY; 
//	float tempy1, tempy2 ;

//		int error1, error2, error3;

//	DisY1 = M3;
//	DisY2 = M4;
////	*Theta = atan(tantheta);
////	DisX = (DisX1* LazX2_FixErrY + DisX2 *LazX1_FixErrY )/ (LazX1_FixErrY + LazX2_FixErrY);
////	*WorldX = -7000 + arm_cos_f32(*Theta)*(LazX_FixErrX + DisX) ; 
////	
////	
////	tempy1 = LazY1_FixErrX * arm_sin_f32(*Theta)/arm_cos_f32(*Theta);
////	tempy2 = LazY2_FixErrX * arm_sin_f32(*Theta)/arm_cos_f32(*Theta);

////	
////	WorldY1 = -7000 + arm_cos_f32(*Theta) *(DisY1 + LazY1_FixErrY - tempy1);
////	WorldY2 = 7000 - arm_cos_f32(*Theta) *(DisY2 + LazY2_FixErrY + tempy2);
//	
//	error1 = abs(ChassisInstance.CurrentState.Y - WorldY1);
//	error2 = abs(ChassisInstance.CurrentState.Y - WorldY2);
////	error3 = abs(WorldY1 - WorldY2);
//	if(ChassisInstance.CurrentState.Y > 0)// && error2 < 800)
//	 *WorldY = WorldY2;
//	else if(ChassisInstance.CurrentState.Y < 0)// && error1 < 800)
//		*WorldY = WorldY1;
//	else
//		*WorldY = ChassisInstance.CurrentState.Y;
	// AccoutTheta();
	// AccoutX();
	// AccoutY();
}