#include "system_config.h"
#include "globalTime.h"

bool sw1 = true,sw2 = true;

void System_Init(void)
{	
	globalTimInit();
	
	#ifdef _USE_LED
	LED_InitAll();
	#endif
	
	#ifdef _USE_SWITCH
	//SW_InitAll();
	Sonnar_Init();
	#endif
				
	#ifdef _USE_MYUSART1
	MyUART_Init(MYUSART1);
//	USART_DMA_CONFIG();

	
	
	#endif
	
	#ifdef _USE_MYUSART2
	MyUART_Init(MYUSART2);

	#endif
	
	#ifdef _USE_BEEP
	Beep_Init();
	#endif
	
	#ifdef _USE_ENCODER1
	ENCx_Init(ENC1);
	#endif
		
	#ifdef _USE_ENCODER2
	ENCx_Init(ENC2);
	#endif
		
	#ifdef _USE_ENCODER3
	ENCx_Init(ENC3);
	#endif

	#ifdef _USE_IMU
	ImuHardInit() ;
	#endif
	
	#ifdef _USE_MOTOR
	Motor1_Init(1000-1,42-1);
	Motor2_Init(1000-1,42-1);
	#endif
	
	PathInit();
	
	

}
