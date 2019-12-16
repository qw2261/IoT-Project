#ifndef _CHASSIS_H_
#define _CHASSIS_H_

#include "arm_math.h"
#include "includes.h"
#include "pid.h"

#define MECANNUM_WHEEL 

#define ENC_X   ENC2
#define ENC_Y   ENC3

#ifdef  MECANNUM_WHEEL
  #define WHEELS_NUM 4
#else  
  #define WHEELS_NUM 3
#endif

//#define WHEELS_NUM 4

#define WHEELS_RADIUS       (40.0f)

#define HalfPerimeter 300.0f // (320+260)/2
#define SQRT3 1.732050f
#define SQRT2 1.41421356f

#define W_LIMIT 1.2f   // (100.0f/RAD2DEG)  //limit the max w output


#define RAD2DEG   57.2957795f//(180.0f/PI)
#define DEG2RAD   0.0174532925f//(PI/180.0f)
#define RAD_PER_SECOND_2RPM    9.55f//(30.0f/PI)

typedef enum
{
	CHASSIS_TEST,
	STALL,
	PARKING,
	PARKING_ERR,
	NAVIGATE,
	NAVIGATE_ERR,
	CHASSIS_DISABLE,
	ON_LINE
}ChassisModeTypedef;


//All Informations are under global coordinate
typedef struct
{
	float X;
	float Y;
	float Alpha;
	float Vx;	
	float Vy;
	float w;
	//the vector of wheels Velocities
	short wheelsW[WHEELS_NUM];
}ChassisStateTypedef;

//All Informations are under global coordinate
typedef struct
{
	ChassisStateTypedef CurrentState;
	ChassisStateTypedef AimState;
	ChassisModeTypedef Mode;
	float X_Bias,Y_Bias,Alpha_Bias;
	float OriginX,OriginY,OriginAlpha;
	float X_Correct,Y_Correct,Alpha_Correct;
	uint8_t NavigatePathNum;
}ChassisInfoTypedef;


typedef struct
{
	float X; 			 
	float Y; 			 
	float Alpha;  	
	float V;
  float V_Theta; 	 	
	float w; 		
}NavagationTypedef;

typedef struct
{
	const NavagationTypedef* PathDotsInfoArray;//point to the inception of pathI[PathDotsNum]
	uint16_t PathDotsNum;	
}PathInfoTypedef;


extern ChassisInfoTypedef  ChassisInstance;




extern PID_StructTypedef TrajectCorrectPID;
extern PID_StructTypedef PosePID;
extern PID_StructTypedef PositionX_PID;
extern PID_StructTypedef PositionY_PID;
extern PID_StructTypedef PositionPID_InitTemp;

void wheelsVectorCal(ChassisInfoTypedef* ChasisInfo);

void chassisParking(ChassisInfoTypedef* ChassisInfo);
void chassisNavigate(ChassisInfoTypedef* ChasisInfo,PathInfoTypedef* PathInfo);
void chassisOnline(ChassisInfoTypedef* ChassisInfo);

void chassisOneCircle(void);
void chassisInit(void);

#endif







