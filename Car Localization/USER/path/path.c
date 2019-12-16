#include "path.h"

bool USE_RED = true,USE_BLUE = false;

	
PathInfoTypedef PathInforms[PATH_NUM];


void PathInit()
{
	if(USE_RED)
	{
				PathInforms[0].PathDotsInfoArray = Path0;
		PathInforms[0].PathDotsNum = 2;
		
		PathInforms[1].PathDotsInfoArray = Path1;
		PathInforms[1].PathDotsNum = 3;
		
				PathInforms[2].PathDotsInfoArray = Path2;
		PathInforms[2].PathDotsNum = 2;
		
				PathInforms[3].PathDotsInfoArray = Path3;
		PathInforms[3].PathDotsNum = 3;
		
				PathInforms[4].PathDotsInfoArray = Path4;
		PathInforms[4].PathDotsNum = 4;
		

				PathInforms[5].PathDotsInfoArray = Path5;
		PathInforms[5].PathDotsNum = 4;
		

	}
	else if(USE_RED)
	{
//		PathInforms[0].PathDotsInfoArray = Path5;
//		PathInforms[0].PathDotsNum = 286;
//		
//		PathInforms[1].PathDotsInfoArray = Path6;
//		PathInforms[1].PathDotsNum = 201;
//		
//		PathInforms[2].PathDotsInfoArray = Path7;
//		PathInforms[2].PathDotsNum = 452;
//		
//		PathInforms[3].PathDotsInfoArray = Path8;
//		PathInforms[3].PathDotsNum = 452;
		

	}
}