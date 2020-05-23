#ifndef SCHEDULER_H
#define	SCHEDULER_H

typedef void(*TaskRunnable_t)(void);

typedef struct 
{
	TaskRunnable_t runnable;
	u32 periodicity_us;
}Task_t;

typedef struct
{
	const Task_t* const appTask;
	u32 delayTicks;	
}sysTaskInfo_t;

extern STD_STATUS SCHEDULER_u8Init(void);
extern STD_STATUS SCHEDULER_u8Start(void);
//extern STD_STATUS SCHEDULER_u8CreateTask(Task_t *Copy_appTask);
extern STD_STATUS SCHEDULER_u8SupsendTask(Task_t *Copy_appTask);

#endif /* SCHEDULER_H */