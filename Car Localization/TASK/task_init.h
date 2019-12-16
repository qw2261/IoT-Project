#ifndef __TASK_INIT_H
#define __TASK_INIT_H
#include "includes.h"


/******************TASK PRIORITIES******************/
#define  TASK_START_PRIO                              2u
#define  TASK_LOCATE_PRIO                             3u
#define  TASK_CHASSIS_PRIO                            4u
#define  TASK_COM_PRIO                                6u
#define  TASK_MONITOR_PRIO                            13u
#define  TASK_INDICATE_PRIO                           22u
                               

/******TASK STACK SIZES Size of the task stacks (# of OS_STK entries)*******/
#define  TASK_START_STK_SIZE                 512u
#define  TASK_LOCATE_STK_SIZE                2048u
#define  TASK_CHASSIS_STK_SIZE               2048u
#define  TASK_COM_STK_SIZE                   2048u
#define  TASK_MONITOR_STK_SIZE               512u
#define  TASK_INDICATE_STK_SIZE              512u


void TaskStart(void *p_arg);
void TaskLocate(void *p_arg);
void TaskChassis(void *p_arg);
void TaskCom(void *p_arg);
void TaskMonitor(void *p_arg);
void TaskIndicate(void *p_arg);

#endif
 