#include "STD_TYPES.h"

#include "HSTK.h"
#include "STK_cfg.h"

#include "SCHEDULER.h"
#include "SCHEDULER_cfg.h"

typedef enum
{
	taskSuspended,
	taskRunning
}taskState_t;

typedef struct
{
	sysTaskInfo_t *sysTaskInfo;
	u32 remainTicksToExecute;
	u32 periodicTicks;
	taskState_t state;
}SysTask_t;

static void SCHEDULER_u8ClearFlag(void);
static void SCHEDULER_u8SetFlag(void);
static STD_STATUS SCHEDULER_u8RunScheduler(void);

extern const sysTaskInfo_t sysTaskInfo[SCHEDULER_TASKS_MAX_NUMBER];
static SysTask_t SysTasks[SCHEDULER_TASKS_MAX_NUMBER];

static u8 SCHEDULER_u8RunningFlag = 0;
//static u8 SCHEDULER_u8NumberOfRunningTasks = SCHEDULER_TASKS_MAX_NUMBER;

extern STD_STATUS SCHEDULER_u8Init(void)
{
	STD_STATUS local_u8ErrorStatus = STATUS_OK;
	u8 local_u8Index = 0;

	//set the tasks
	for(local_u8Index = 0; local_u8Index <SCHEDULER_TASKS_MAX_NUMBER; local_u8Index ++)
	{
		SysTasks[local_u8Index].sysTaskInfo = &sysTaskInfo[local_u8Index];
		SysTasks[local_u8Index].periodicTicks = (sysTaskInfo[local_u8Index].appTask->periodicity_us) / TICK_TIME_US;
		SysTasks[local_u8Index].remainTicksToExecute = sysTaskInfo[local_u8Index].delayTicks;
		SysTasks[local_u8Index].state = taskRunning;
	}
	
	/* Configure the systick timer */
	HSTK_u8SetTimer_us(TICK_TIME_US);
	
	/* Set the callback for systick */
	HSTK_u8SetCallBack(SCHEDULER_u8SetFlag);
	
	return local_u8ErrorStatus;
}

extern STD_STATUS SCHEDULER_u8Start(void)
{
	STD_STATUS local_u8ErrorStatus = STATUS_OK;
	
	//start the SYTICK
	HSTK_u8Start();
	
	while(1)
	{
		if(SCHEDULER_u8RunningFlag)
		{
			SCHEDULER_u8ClearFlag();
			SCHEDULER_u8RunScheduler();
		}
	}
	
	return local_u8ErrorStatus;
}

static STD_STATUS SCHEDULER_u8RunScheduler(void)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	u8 local_u8Index = 0;
	
	for(local_u8Index = 0; local_u8Index <SCHEDULER_TASKS_MAX_NUMBER; local_u8Index ++)
	{
		if((SysTasks[local_u8Index].remainTicksToExecute == 0) && (SysTasks[local_u8Index].state == taskRunning))
		{
			SysTasks[local_u8Index].sysTaskInfo->appTask->runnable();
			SysTasks[local_u8Index].remainTicksToExecute = SysTasks[local_u8Index].periodicTicks;
		}
		else
		{
			SysTasks[local_u8Index].remainTicksToExecute--;
		}
	}
	
	local_u8ErrorStatus = STATUS_OK;
	return local_u8ErrorStatus;
}

extern STD_STATUS SCHEDULER_u8SupsendTask(Task_t *Copy_appTask)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	u8 local_u8Index = 0;
	
	if(Copy_appTask)
	{
		for(local_u8Index = 0; local_u8Index < SCHEDULER_TASKS_MAX_NUMBER; local_u8Index++)
		{
			if((SysTasks[local_u8Index].sysTaskInfo->appTask) == Copy_appTask)
			{
				SysTasks[local_u8Index].state = taskSuspended;
			}
			{
				local_u8ErrorStatus = STATUS_NOT_OK;
			}
		}
	}
	else
	{
		local_u8ErrorStatus = STATUS_NULLPOINTER;
	}
	return local_u8ErrorStatus;
}

static void SCHEDULER_u8ClearFlag(void)
{
	SCHEDULER_u8RunningFlag = 0;
}
static void SCHEDULER_u8SetFlag(void)
{
	SCHEDULER_u8RunningFlag = 1;
}

