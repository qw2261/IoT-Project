#include "chassis.h"
#include "com_prop.h"
uint16_t PathDot = 0;
uint8_t PathChange = 0;
extern uint8_t source,target;
void chassisPoseCtrl(ChassisInfoTypedef* ChassisInfo)
{
	float angle;
  float AimW;
  int32_t n;
	//all angles subtract ChassisInfo->AimState.Alpha
  angle = ChassisInfo->CurrentState.Alpha - ChassisInfo->AimState.Alpha;
	//float AimW;
	//scale the angle to 0-2*PI
	//int32_t n;
	n = (int32_t)(angle/(2.0f * PI));
	if(angle < 0.0f)
	{
		n--;
	}
	angle -= 2.0f * n * PI;
	//scale the angle  to -PI - +PI
	if(angle  > PI)
	{
		angle -= 2.0f * PI;
	}
	AimW = PidRegulate(0.0f, angle, &PosePID); 	
	if(fabs(angle)<0.004f)
	{
		AimW=0.0f;
	}

	if(AimW > W_LIMIT)   //The GYRO Resolution is limited to 150 degree/second
	{
		AimW = W_LIMIT;    
	}		
	else if(AimW < -W_LIMIT) 
	{
		AimW = -W_LIMIT;
	}
	ChassisInfo->AimState.w = AimW;
}

void chassisParking(ChassisInfoTypedef* ChassisInfo)
{
	float dx,dy;
	
	dx = ChassisInfo->CurrentState.X - ChassisInfo->AimState.X;
	dy = ChassisInfo->CurrentState.Y - ChassisInfo->AimState.Y;
	if(((fabs(dx)+fabs(dy))>2000)||((dx)*(dx)+(dy)*(dy)<50.0f))
	{
		ChassisInfo->AimState.Vx=0.0f;
		ChassisInfo->AimState.Vy=0.0f;
	}
	else if(fabs(dx)+fabs(dy)>500)
	{
//		PositionX_PID.Kp=10.0f;
//		PositionY_PID.Kp=10.0f;
	  ChassisInfo->AimState.Vx = PidRegulate(0.0f, dx, &PositionX_PID); 
	  ChassisInfo->AimState.Vy = PidRegulate(0.0f, dy, &PositionY_PID); 
	}
	else if(fabs(dx)+fabs(dy)>350)
	{
//		PositionX_PID.Kp=7.0f;
//		PositionY_PID.Kp=7.0f;
		ChassisInfo->AimState.Vx = PidRegulate(0.0f, dx, &PositionX_PID); 
	  ChassisInfo->AimState.Vy = PidRegulate(0.0f, dy, &PositionY_PID); 
	}
	else
	{
//		PositionX_PID.Kp=5.0f;
//		PositionY_PID.Kp=5.0f;
		ChassisInfo->AimState.Vx = PidRegulate(0.0f, dx, &PositionX_PID); 
	  ChassisInfo->AimState.Vy = PidRegulate(0.0f, dy, &PositionY_PID); 
	}

	chassisPoseCtrl(ChassisInfo);
	
	wheelsVectorCal(ChassisInfo);
}
void chassisNavigate(ChassisInfoTypedef* ChassisInfo,PathInfoTypedef* PathInfo)
{
	static uint16_t PathDotIndex = 1;
	float dx,dy;
	uint16_t PathDotIndexMAX = PathInfo->PathDotsNum -1;
	const NavagationTypedef* PathDotsInfo = PathInfo-> PathDotsInfoArray;
	volatile ChassisStateTypedef *pCurrentState = &(ChassisInfo->CurrentState);
	volatile ChassisStateTypedef *pAimState = &(ChassisInfo->AimState);
	pAimState->X  = PathDotsInfo[PathDotIndex].X;
	pAimState->Y  = PathDotsInfo[PathDotIndex].Y; 
	pAimState->Alpha = PathDotsInfo[PathDotIndex].Alpha;
	pAimState->w = PathDotsInfo[PathDotIndex].w;
	dx = -PathDotsInfo[PathDotIndex].X + pCurrentState->X;
	dy = -PathDotsInfo[PathDotIndex].Y + pCurrentState->Y;
	
	if((dx)*(dx)+(dy)*(dy)<1000.0f)
	{
		if(PathDotIndex < PathDotIndexMAX)
			PathDotIndex++;
		else
		{
			source = target;
			ChassisInfo->Mode = PARKING;
  		PathDotIndex = 1;
			chassisParking(ChassisInfo);
		}
	}
	else
	{
		pAimState->Vx = PidRegulate(0.0f, dx, &PositionX_PID); 
		pAimState->Vy = PidRegulate(0.0f, dy, &PositionY_PID); 
	}
	chassisPoseCtrl(ChassisInfo);
	wheelsVectorCal(ChassisInfo);
	
}

//brief:chassis Navigate func,when locus is finished,the chassis mode will be changed to parking mode
void chassisOnline(ChassisInfoTypedef* ChassisInfo) //不稳定，需修改
{

		static volatile bool IsFirst=true;
	  float Vstart=400.0f;
	  static float Vconst=0.0f,a=0.0f;                      //匀速段速度，加速度
	  float dispos=0.0f;	                         //当前点距离目标点距离
    float Vvertical=0.0f,Vparallel=0.0f;           //垂直目标直线速度，平行目标直线速度
	  float PositionError=0.0f;                  //当前点距目标直线的垂直距离
	  float vmax=3000.0f;               //最大速度，最大加速度，mm为单位
    static volatile float LA=0.0f,LB=0.0f,LC=0.0f,LD=0.0f;
    static volatile float StartPointX=0.0f;
    static volatile float StartPointY=0.0f;            //目标直线起点（x1,y1）
    static volatile float StopPointX=0.0f;
    static volatile float StopPointY=0.0f;             //目标直线终点(x2,y2),目标直线方程：(y2-y1)*x-(x2-x1)*y+x2*y1-x1*y2=0
	  static volatile float AlphaInit=0.0f;
	  static volatile float DeltaAlpha=0.0f;
	  static float k=0.0f;
	  float angle=0.0f;

		
	
		if(IsFirst&&(ChassisInfo->Mode== ON_LINE))  //距离大于200mm进行路径规划，否则直接parking,默认会进一次
		{
			StartPointX=ChassisInfo->CurrentState.X;
			StartPointY=ChassisInfo->CurrentState.Y;
			StopPointX=ChassisInfo->AimState.X;
			StopPointY=ChassisInfo->AimState.Y;
			
		  LA=StopPointY-StartPointY; //(y2-y1)
		  LB=StopPointX-StartPointX; //(x2-x1)
		  LC=StopPointX*StartPointY-StartPointX*StopPointY;//x2*y1-x1*y2 
		  LD=sqrt(LA * LA + LB * LB);
			
			DeltaAlpha=ChassisInfo->AimState.Alpha-ChassisInfo->CurrentState.Alpha;
			AlphaInit=ChassisInfo->CurrentState.Alpha;
			k = DeltaAlpha/LD;
			
			Vconst=0.35f*LD;                      //最高速度与路径长度成正比，路径越长，速度越快
			if(Vconst>vmax)
			{
				Vconst=vmax;
			}
			
		  IsFirst=false;
		}
		
		dispos=sqrt((StopPointX-ChassisInfo->CurrentState.X)*(StopPointX-ChassisInfo->CurrentState.X)+
			 (StopPointY-ChassisInfo->CurrentState.Y)*(StopPointY-ChassisInfo->CurrentState.Y));
		
		if(dispos>100.0f)
			{
				 PositionError = (LA *(ChassisInfo->CurrentState.X) - LB *(ChassisInfo->CurrentState.Y) + LC)/LD;
				 Vvertical = PidRegulate(0.0f,PositionError,&TrajectCorrectPID);
				if(fabs(dispos-LD)<LD*0.25f)          //前4分之一匀加速，中间二分之一匀速,总长为LD,当前位移近似为LD-dispos
				{
					a=2.0f*(Vconst*Vconst-Vstart*Vstart)/(LD);
					Vparallel=sqrt(Vstart*Vstart+2*a*(LD-dispos));  
					angle=AlphaInit+(LD-dispos)*k;
				}
				else if(fabs(dispos-LD)>LD*0.75f)
				{
					a=2.0f*(Vconst*Vconst)/(LD);
					Vparallel=sqrt(2*a*dispos);
					angle=AlphaInit+(LD-dispos)*k;
				}
				else
				{
					Vparallel=Vconst;
					angle=AlphaInit+(LD-dispos)*k;
				}
				
				
				if(Vparallel>vmax)
				{
					Vparallel=vmax;
				} 

				ChassisInfo->AimState.Alpha = angle;
        ChassisInfo->AimState.Vx = Vparallel*LB/LD+Vvertical*LA/LD;
				ChassisInfo->AimState.Vy = Vparallel*LA/LD-Vvertical*LB/LD;
				
				
				chassisPoseCtrl(ChassisInfo);
				wheelsVectorCal(ChassisInfo);
			 }
		 else
		{
			IsFirst=true;
			IsPosRecv = false;
			ChassisInfo->Mode = PARKING;
			chassisParking(ChassisInfo);
		}	
		 
}



