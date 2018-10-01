
#ifndef __APP_CFG_H__
#define __APP_CFG_H__

/*********************设置任务优先级************************/
//#define	STARTUP_TASK_PRIO	4
#define	MODBUS_TASK_PRIO	3
#define	ETHERNET_TASK_PRIO	2


/*********************设置栈大小（单位为 OS_STK）************************/
//#define STARTUP_TASK_STK_SIZE	512
#define MODBUS_TASK_STK_SIZE	512
#define ETHERNET_TASK_STK_SIZE 10240 //10K缓存区

#endif

