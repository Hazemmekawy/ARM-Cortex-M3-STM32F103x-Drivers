#include "STD_TYPES.h"

#include "STK.h"
#include "STK_cfg.h"

typedef struct 
{
	volatile u32 STK_CTRL;
	volatile u32 STK_LOAD;
	volatile u32 STK_VAL;
	volatile u32 STK_CALIB;	
}STK_t;

volatile STK_t* const STK = (STK_t*)0xE000E010;
void (*STK_pfuncCallBack)(void);

/****************************************************************************************************************
*                                                                                                               *
*	Description:                                                                                                *
*				This function shall initialize the systick timer.                                     			*
*				                                                                                                *
*	Input Parameters:                                                                                           *
*				void                                                                                            *
*                                                                                                               *
*	Return value:                                                                                               *
*				STD_STATUS: The function's execution status                                                     *
*					Options:                                                                                    *
*					STATUS_NOT_OK >> Function ended with failure                                                *
*					STATUS_OK >> Function ended with success                                                    *
*                                                                                                               *
****************************************************************************************************************/
extern STD_STATUS STK_u8Init(void)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	
	/* Enable the interrupt */
	STK->STK_CTRL |= STK_CTRL_TICKINT_MASK;
	
	/* Set the prescaler */	
	#if STK_CLKSOURCE == STK_AHB_CLK
		STK->STK_CTRL |= STK_CTRL_CLKSOURCE_MASK;
		local_u8ErrorStatus = STATUS_OK;
	
	#elif STK_CLKSOURCE == STK_AHB_CLK_BY_8
		STK->STK_CTRL &= ~STK_CTRL_CLKSOURCE_MASK;
		local_u8ErrorStatus = STATUS_OK;
	
	#else
		local_u8ErrorStatus = STATUS_NOT_OK;
	
	#endif
	
	return local_u8ErrorStatus;
}

/****************************************************************************************************************
*                                                                                                               *
*	Description:                                                                                                *
*				This function shall start the systick timer.                                     				*
*				                                                                                                *
*	Input Parameters:                                                                                           *
*				void                                                                                            *
*                                                                                                               *
*	Return value:                                                                                               *
*				STD_STATUS: The function's execution status                                                     *
*					Options:                                                                                    *
*					STATUS_NOT_OK >> Function ended with failure                                                *
*					STATUS_OK >> Function ended with success                                                    *
*                                                                                                               *
****************************************************************************************************************/
extern STD_STATUS STK_u8Start(void)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	STK->STK_CTRL |= STK_CTRL_ENABLE_MASK;
	local_u8ErrorStatus = STATUS_OK;
	return local_u8ErrorStatus;
}

/****************************************************************************************************************
*                                                                                                               *
*	Description:                                                                                                *
*				This function shall stop the systick timer.                                     				*
*				                                                                                                *
*	Input Parameters:                                                                                           *
*				void                                                                                            *
*                                                                                                               *
*	Return value:                                                                                               *
*				STD_STATUS: The function's execution status                                                     *
*					Options:                                                                                    *
*					STATUS_NOT_OK >> Function ended with failure                                                *
*					STATUS_OK >> Function ended with success                                                    *
*                                                                                                               *
****************************************************************************************************************/
extern STD_STATUS STK_u8Stop(void)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	STK->STK_CTRL &= ~STK_CTRL_ENABLE_MASK;
	local_u8ErrorStatus = STATUS_OK;
	return local_u8ErrorStatus;
}

/****************************************************************************************************************
*                                                                                                               *
*	Description:                                                                                                *
*				This function shall set the systick timer value.                                     			*
*				                                                                                                *
*	Input Parameters:                                                                                           *
*				u32 Copy_u32Time_us: The time in microseconds.                                                  *
*                                                                                                               *
*				u32 Copy_f32_AHB_Clock_MHZ: The AHB clock source of systick timer in MHZ						*                                                                           *
*					                                                                                            *
*	Return value:                                                                                               *
*				STD_STATUS: The function's execution status                                                     *
*					Options:                                                                                    *
*					STATUS_NOT_OK >> Function ended with faliure                                                *
*					STATUS_OK >> Function ended with success                                                    *
*                                                                                                               *
****************************************************************************************************************/
extern STD_STATUS STK_u8SetTimer(u32 Copy_u32Time_us, f32 Copy_f32_AHB_Clock_MHZ)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	f32 local_f32TickTime = 0;
	u32 local_u32Ticks = 0;
	
	#if STK_CLKSOURCE == STK_AHB_CLK
		local_f32TickTime = ((f32)1/Copy_f32_AHB_Clock_MHZ);
		local_u32Ticks = Copy_u32Time_us/local_f32TickTime;
		
		/* Load the value into the load register */
		STK->STK_LOAD = local_u32Ticks;
	
		/* Clear the value register */
		STK->STK_VAL = 0;
		
		local_u8ErrorStatus = STATUS_OK;
	
	#elif STK_CLKSOURCE == STK_AHB_CLK_BY_8
		local_f32TickTime = ((f32)8/Copy_f32_AHB_Clock_MHZ);
		local_u32Ticks = Copy_u32Time_us/local_f32TickTime;
		
		/* Load the value into the load register */
		STK->STK_LOAD = local_u32Ticks;
		
		/* Clear the value register */
		STK->STK_VAL = 0;
		
		local_u8ErrorStatus = STATUS_OK;
	
	#else
		local_u8ErrorStatus = STATUS_NOT_OK;
	
	#endif
	return local_u8ErrorStatus;
}

/****************************************************************************************************************
*                                                                                                               *
*	Description:                                                                                                *
*				This function shall set the callback function of systick timer value.                           *
*				                                                                                                *
*	Input Parameters:                                                                                           *
*				callBackFn_t Copy_pfunc: Pointer to the callback function                                       *                                                                         *
*					                                                                                            *
*	Return value:                                                                                               *
*				STD_STATUS: The function's execution status                                                     *
*					Options:                                                                                    *
*					STATUS_NOT_OK >> Function ended with faliure                                                *
*					STATUS_OK >> Function ended with success                                                    *
*                                                                                                               *
****************************************************************************************************************/
extern STD_STATUS STK_u8SetCallBack(callBackFn_t Copy_pfunc)
{
	STD_STATUS local_u8ErrorStatus = STATUS_OK;
	if(Copy_pfunc)
	{
		STK_pfuncCallBack = Copy_pfunc;
	}
	else
	{
		local_u8ErrorStatus = STATUS_NULLPOINTER;
	}
	return local_u8ErrorStatus;
}

void SysTick_Handler(void)
{
	if(STK_pfuncCallBack)
	{
		STK_pfuncCallBack();
	}
}

