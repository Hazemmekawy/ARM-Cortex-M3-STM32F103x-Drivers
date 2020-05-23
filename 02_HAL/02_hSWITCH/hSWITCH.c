#include "STD_TYPES.h"
#include "GPIO.h"
#include "SCHEDULER.h"
#include "hSWITCH.h"


extern const SWITCH_cfgStruct_t SWITCH_cfgStruct[SWITCH_MAX_NUMBER];

#if SWITCH_OS_MODE == FALSE

/****************************************************************************************************************
*                                                                                                               *
*	Description:                                                                                                *
*				This function shall initialize a SWITCH.                                   						*
*				                                                                                                *
*	Input Parameters:                                                                                           *
*				void                           																	*
*                                                                                                               *
*	Return value:                                                                                               *
*				STD_STATUS: The function's execution status                                                     *
*					Options:                                                                                    *
*					STATUS_NOT_OK >> Function ended with faliure                                                *
*					STATUS_OK >> Function ended with success                                                    *
*                                                                                                               *
****************************************************************************************************************/
extern STD_STATUS hSWITCH_u8Init(void)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	u8 local_u8Index = 0;
	
	for(local_u8Index = 0; local_u8Index < SWITCH_MAX_NUMBER; local_u8Index++)
	{
		if(IS_SWITCH_VALID(local_u8Index))
		{
			GPIO_Init_t Local_PinStructure;
		
			Local_PinStructure.GPIO_Pin = SWITCH_cfgStruct[local_u8Index].SWITCH_u16Pin;
			Local_PinStructure.GPIO_Speed = GPIO_SPEED_INPUT_MASK;
			
			switch(SWITCH_cfgStruct[local_u8Index].SWITCH_u8ActiveState)
			{
				case SWITCH_ACTIVE_LOW: //pull up
					Local_PinStructure.GPIO_Mode = GPIO_MODE_IN_PU_MASK;
					GPIO_u8ConfigurePin(SWITCH_cfgStruct[local_u8Index].SWITCH_pvGPIOx, &Local_PinStructure);
					local_u8ErrorStatus = STATUS_OK;
					break;
					
				case SWITCH_ACTIVE_HIGH: //pull down
					Local_PinStructure.GPIO_Mode = GPIO_MODE_IN_PD_MASK;
					GPIO_u8ConfigurePin(SWITCH_cfgStruct[local_u8Index].SWITCH_pvGPIOx, &Local_PinStructure);
					local_u8ErrorStatus = STATUS_OK;
					break;
					
				default:
				
					local_u8ErrorStatus = STATUS_NOT_OK;
					break;
			}
			if(local_u8ErrorStatus == STATUS_NOT_OK) break;
		}
		else
		{
			local_u8ErrorStatus = STATUS_NOT_OK;
			break;
		}
	}
	
	return local_u8ErrorStatus;
}
/****************************************************************************************************************
*                                                                                                               *
*	Description:                                                                                                *
*				This function shall set the status of a SWITCH.                               					*
*				                                                                                                *
*	Input Parameters:                                                                                           *
*				u8 Copy_u8ID: Takes a SWITCH ID.                                                   				*
*					Options:                                                                                    *
*					A value from the specified IDs in SWITCH.h      											*
*                    	 	                                                                                    *
*				u8 *Copy_pu8Reading: Takes a pointer to a variable where the value is saved         			*
*					Options:                                                                                    *
*					OFF >> Turn on the SWITCH                                                                   *
*					ON >> Turn off the SWITCH  																	*
*                                                                                                               *
*	Return value:                                                                                               *
*				STD_STATUS: The function's execution status                                                     *
*					Options:                                                                                    *
*					STATUS_NOT_OK >> Function ended with faliure                                                *
*					STATUS_OK >> Function ended with success                                                    *
*                                                                                                               *
****************************************************************************************************************/
extern STD_STATUS hSWITCH_u8ReadState(u8 Copy_u8ID, u8 *Copy_pu8Reading)
{
	STD_STATUS local_u8ErrorStatus = STATUS_OK;
	LEVEL local_u8Level;
	
	if(IS_SWITCH_VALID(Copy_u8ID))
	{
		GPIO_u8GetPinValue(SWITCH_cfgStruct[Copy_u8ID].SWITCH_pvGPIOx, 
										SWITCH_cfgStruct[Copy_u8ID].SWITCH_u16Pin, 
										&local_u8Level);
										
		switch(SWITCH_cfgStruct[Copy_u8ID].SWITCH_u8ActiveState)
		{
			case SWITCH_ACTIVE_LOW:
			
				switch(local_u8Level)
				{
					case LOW:
						*Copy_pu8Reading = SWITCH_PRESSED;
						break;
						
					case HIGH:
						*Copy_pu8Reading = SWITCH_NOT_PRESSED;
						break;
					
					default:
						local_u8ErrorStatus = STATUS_NOT_OK;
						break;
				}
				break;
				
			case SWITCH_ACTIVE_HIGH:
			
				switch(local_u8Level)
				{
					case LOW:
						*Copy_pu8Reading = SWITCH_NOT_PRESSED;
						break;
						
					case HIGH:
						*Copy_pu8Reading = SWITCH_PRESSED;
						break;
					
					default:
						local_u8ErrorStatus = STATUS_NOT_OK;
						break;
				}
				break;
				
			default:
				local_u8ErrorStatus = STATUS_NOT_OK;
				break;
		}
	}
	else
	{
		local_u8ErrorStatus = STATUS_NOT_OK;
	}
	
	return local_u8ErrorStatus;
}

#elif SWITCH_OS_MODE == TRUE

typedef struct
{
	u8 switchID;
	u8 debounceCounter;
	u8 previousSate;
	u8 state;
	
}SWITCH_taskStates_t;

extern const Task_t hSWITCH_task = 
{
	.runnable = hSWITCH_DebounceTask,
	.periodicity_us = 20000 /* Every 20ms */
};

SWITCH_taskStates_t SWITCH_taskStates[SWITCH_MAX_NUMBER];

extern STD_STATUS hSWITCH_OS_u8Init(void)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	u8 local_u8Index = 0;
	
	for(local_u8Index = 0; local_u8Index < SWITCH_MAX_NUMBER; local_u8Index++)
	{
		if(IS_SWITCH_VALID(local_u8Index))
		{
			GPIO_Init_t Local_PinStructure;
		
			Local_PinStructure.GPIO_Pin = SWITCH_cfgStruct[local_u8Index].SWITCH_u16Pin;
			Local_PinStructure.GPIO_Speed = GPIO_SPEED_INPUT_MASK;
			
			/* This line is in case of OS */
			
			SWITCH_taskStates[local_u8Index].switchID = SWITCH_cfgStruct[local_u8Index].SWITCH_u8ID;
			SWITCH_taskStates[local_u8Index].debounceCounter = 0;
			SWITCH_taskStates[local_u8Index].previousSate = 0;
			SWITCH_taskStates[local_u8Index].state = 0;
			
			switch(SWITCH_cfgStruct[local_u8Index].SWITCH_u8ActiveState)
			{
				case SWITCH_ACTIVE_LOW: //pull up
					Local_PinStructure.GPIO_Mode = GPIO_MODE_IN_PU_MASK;
					GPIO_u8ConfigurePin(SWITCH_cfgStruct[local_u8Index].SWITCH_pvGPIOx, &Local_PinStructure);
					local_u8ErrorStatus = STATUS_OK;
					break;
					
				case SWITCH_ACTIVE_HIGH: //pull down
					Local_PinStructure.GPIO_Mode = GPIO_MODE_IN_PD_MASK;
					GPIO_u8ConfigurePin(SWITCH_cfgStruct[local_u8Index].SWITCH_pvGPIOx, &Local_PinStructure);
					local_u8ErrorStatus = STATUS_OK;
					break;
					
				default:
				
					local_u8ErrorStatus = STATUS_NOT_OK;
					break;
			}
			if(local_u8ErrorStatus == STATUS_NOT_OK) break;
		}
		else
		{
			local_u8ErrorStatus = STATUS_NOT_OK;
			break;
		}
	}
	
	return local_u8ErrorStatus;
}

extern STD_STATUS hSWITCH_OS_u8ReadState(u8 Copy_u8ID, u8 *Copy_pu8Reading)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	
	if(Copy_pu8Reading)
	{
		*Copy_pu8Reading = SWITCH_taskStates[Copy_u8ID].state;
	}
	else
	{
		local_u8ErrorStatus = STATUS_NULLPOINTER;		
	}
	
	return local_u8ErrorStatus;	
}

extern void hSWITCH_DebounceTask(void)
{
	u8 local_u8Index = 0;
	u8 local_u8CurrentState = 0;
	
	for(local_u8Index = 0; local_u8Index < SWITCH_MAX_NUMBER; local_u8Index++)
	{
		GPIO_u8GetPinValue(SWITCH_cfgStruct[local_u8Index].SWITCH_pvGPIOx, 
										SWITCH_cfgStruct[local_u8Index].SWITCH_u16Pin, 
										&local_u8CurrentState);
										
		if(local_u8CurrentState == SWITCH_taskStates[local_u8Index].previousSate)
		{
			SWITCH_taskStates[local_u8Index].debounceCounter++;		
		}
		else
		{
			SWITCH_taskStates[local_u8Index].debounceCounter = 0;
		}	
	}

	if(SWITCH_taskStates[local_u8Index].debounceCounter == SWITCH_COUNTER_VALUE)
	{
		SWITCH_taskStates[local_u8Index].state = local_u8CurrentState;
		SWITCH_taskStates[local_u8Index].debounceCounter = 0;
	}	
	SWITCH_taskStates[local_u8Index].previousSate = local_u8CurrentState;
}

#else
	#error "HSWITCH_OS_ERROR"
#endif