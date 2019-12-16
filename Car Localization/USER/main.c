#include "system_config.h" 
#include "includes.h"
#include "task_init.h"
#include "chassis.h"


static  OS_TCB   TaskStartTCB;
static  CPU_STK  TaskStartStk[TASK_START_STK_SIZE];

static  OS_TCB   TaskMonitorTCB;
static  CPU_STK  TaskMonitorStk[TASK_MONITOR_STK_SIZE];

static  OS_TCB   TaskComTCB;
static  CPU_STK  TaskComStk[TASK_COM_STK_SIZE];

static  OS_TCB   TaskChassisTCB;
static  CPU_STK  TaskChassisStk[TASK_CHASSIS_STK_SIZE];

static  OS_TCB   TaskLocateTCB;
static  CPU_STK  TaskLocateStk[TASK_LOCATE_STK_SIZE];

static  OS_TCB   TaskIndicateTCB;
static  CPU_STK  TaskIndicateStk[TASK_INDICATE_STK_SIZE];




int main(void)
{
    OS_ERR err;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);    //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
    System_Init();
    delay_init();
    OSInit(&err);

    /*创建起始任务*/ 
    OSTaskCreate ((OS_TCB       *)&TaskStartTCB,
                  (CPU_CHAR     *)"Task Start",
                  (OS_TASK_PTR   )TaskStart,
                  (void         *)0,
                  (OS_PRIO       )TASK_START_PRIO,
                  (CPU_STK      *)&TaskStartStk[0],
                  (CPU_STK_SIZE  )TASK_START_STK_SIZE / 10,
                  (CPU_STK_SIZE  )TASK_START_STK_SIZE,
                  (OS_MSG_QTY    )0,
                  (OS_TICK       )0,
                  (void         *)0,
                  (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                  (OS_ERR       *)&err);
    OSStart(&err);
    (void)&err;
}
void TaskStart(void *p_arg)
{
    OS_ERR err;
    CPU_SR cpu_sr = 0;
    p_arg = p_arg;
    CPU_Init();    // Initialize the uC/CPU services
    Mem_Init();    // Initialize Memory Management Module
    Math_Init();
    

	
    LED_On(RED_LED);
    LED_On(GREEN_LED);

    MyDelayms(500);
    LED_Off(RED_LED);
    LED_Off(GREEN_LED);

	  
		chassisInit();

	
    LED_On(RED_LED);
    LED_On(GREEN_LED);

		
	  OS_CRITICAL_ENTER();
    OSTaskCreate  ((OS_TCB       *)&TaskMonitorTCB,
                   (CPU_CHAR     *)"Monitor Task",
                   (OS_TASK_PTR   )TaskMonitor,
                   (void         *)0,
                   (OS_PRIO       )TASK_MONITOR_PRIO,
                   (CPU_STK      *)&TaskMonitorStk[0],
                   (CPU_STK_SIZE  )TASK_MONITOR_STK_SIZE / 10,
                   (CPU_STK_SIZE  )TASK_MONITOR_STK_SIZE,
                   (OS_MSG_QTY    )0,
                   (OS_TICK       )0,
                   (void         *)0,
                   (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                   (OS_ERR       *)&err);
    
    OSTaskCreate  ((OS_TCB       *)&TaskIndicateTCB,
                   (CPU_CHAR     *)"Indicate Task",
                   (OS_TASK_PTR   )TaskIndicate,
                   (void         *)0,
                   (OS_PRIO       )TASK_INDICATE_PRIO,
                   (CPU_STK      *)&TaskIndicateStk[0],
                   (CPU_STK_SIZE  )TASK_INDICATE_STK_SIZE / 10,
                   (CPU_STK_SIZE  )TASK_INDICATE_STK_SIZE,
                   (OS_MSG_QTY    )0,
                   (OS_TICK       )0,
                   (void         *)0,
                   (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                   (OS_ERR       *)&err);
									 


    OSTaskCreate  ((OS_TCB       *)&TaskComTCB,
                   (CPU_CHAR     *)"Com Task",
                   (OS_TASK_PTR   )TaskCom,
                   (void         *)0,
                   (OS_PRIO       )TASK_COM_PRIO,
                   (CPU_STK      *)&TaskComStk[0],
                   (CPU_STK_SIZE  )TASK_COM_STK_SIZE / 10,
                   (CPU_STK_SIZE  )TASK_COM_STK_SIZE,
                   (OS_MSG_QTY    )0,
                   (OS_TICK       )0,
                   (void         *)0,
                   (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                   (OS_ERR       *)&err);
									 
    OSTaskCreate  ((OS_TCB       *)&TaskChassisTCB,
                   (CPU_CHAR     *)"Chassis Task",
                   (OS_TASK_PTR   )TaskChassis,
                   (void         *)0,
                   (OS_PRIO       )TASK_CHASSIS_PRIO,
                   (CPU_STK      *)&TaskChassisStk[0],
                   (CPU_STK_SIZE  )TASK_CHASSIS_STK_SIZE / 10,
                   (CPU_STK_SIZE  )TASK_CHASSIS_STK_SIZE,
                   (OS_MSG_QTY    )0,
                   (OS_TICK       )0,
                   (void         *)0,
                   (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                   (OS_ERR       *)&err);
									 
	  OSTaskCreate  ((OS_TCB       *)&TaskLocateTCB,
                   (CPU_CHAR     *)"Locate Task",
                   (OS_TASK_PTR   )TaskLocate,
                   (void         *)0,
                   (OS_PRIO       )TASK_LOCATE_PRIO,
                   (CPU_STK      *)&TaskLocateStk[0],
                   (CPU_STK_SIZE  )TASK_LOCATE_STK_SIZE / 10,
                   (CPU_STK_SIZE  )TASK_LOCATE_STK_SIZE,
                   (OS_MSG_QTY    )0,
                   (OS_TICK       )0,
                   (void         *)0,
                   (OS_OPT        )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                   (OS_ERR       *)&err);
								 
		
    OSTaskSuspend((OS_TCB *)&TaskStartTCB, (OS_ERR *) &err); 
    
		OS_CRITICAL_EXIT();							 
	 
}



void assert_failed(uint8_t* file, uint32_t line)
{
	
}
