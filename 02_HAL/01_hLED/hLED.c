#include "STD_TYPES.h"
#include "GPIO.h"
#include "hLED.h"

extern const LED_t LED_arrMap[LED_MAX_NUMBER];

/****************************************************************************************************************
*                                                                                                               *
*	Description:                                                                                                *
*				This function shall initialize a LED.                                     						*
*				                                                                                                *
*	Input Parameters:                                                                                           *
*				uint8_t Copy_u8_LED_ID: Takes a LED ID.                                                         *
*					Options:                                                                                    *
*					A value from the specified IDs in LED.h                           							*
*                                                                                                               *
*	Return value:                                                                                               *
*				STD_STATUS: The function's execution status                                                     *
*					Options:                                                                                    *
*					STATUS_NOT_OK >> Function ended with faliure                                                *
*					STATUS_OK >> Function ended with success                                                    *
*                                                                                                               *
****************************************************************************************************************/
extern STD_STATUS hLED_u8Init(void)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	GPIO_Init_t local_PinStructure;
	u8 local_u8Index = 0;
	
	for(local_u8Index = 0; local_u8Index < LED_MAX_NUMBER; local_u8Index++)
	{
		if(IS_LED_VALID(local_u8Index))
		{
			local_PinStructure.GPIO_Pin = LED_arrMap[local_u8Index].LED_u16Pin;
			local_PinStructure.GPIO_Speed = LED_arrMap[local_u8Index].LED_u8Speed;
			local_PinStructure.GPIO_Mode = GPIO_MODE_OUT_PP_MASK;
	
			GPIO_u8ConfigurePin(LED_arrMap[local_u8Index].LED_pvGPIOx, &local_PinStructure);
			local_u8ErrorStatus = STATUS_OK;
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
*				This function shall set the status of a LED.                               						*
*				                                                                                                *
*	Input Parameters:                                                                                           *
*				uint8_t Copy_u8_LED_ID: Takes a LED ID.                                                         *
*					Options:                                                                                    *
*					A value from the specified IDs in LED.h      												*
*                    	 	                                                                                    *
*				STATE Copy_u8State: Takes the state of the LED	                                                *
*					Options:                                                                                    *
*					OFF >> Turn on the LED                                                                      *
*					ON >> Turn off the LED   																	*
*                                                                                                               *
*	Return value:                                                                                               *
*				STD_STATUS: The function's execution status                                                     *
*					Options:                                                                                    *
*					STATUS_NOT_OK >> Function ended with faliure                                                *
*					STATUS_OK >> Function ended with success                                                    *
*                                                                                                               *
****************************************************************************************************************/
extern STD_STATUS hLED_u8SetState(uint8_t Copy_u8_LED_ID, STATE Copy_u8State)
{
	STD_STATUS local_u8ErrorStatus = STATUS_OK;
	
	if(IS_LED_VALID(Copy_u8_LED_ID))
	{
		switch(LED_arrMap[Copy_u8_LED_ID].LED_u8ActiveState)
		{
			case LED_ACTIVE_LOW:
				switch(Copy_u8State)
				{
					case OFF:
						GPIO_u8SetPin(LED_arrMap[Copy_u8_LED_ID].LED_pvGPIOx, LED_arrMap[Copy_u8_LED_ID].LED_u16Pin);
						break;
					case ON:
						GPIO_u8ResetPin(LED_arrMap[Copy_u8_LED_ID].LED_pvGPIOx, LED_arrMap[Copy_u8_LED_ID].LED_u16Pin);
						break;
					default:
						local_u8ErrorStatus = STATUS_NOT_OK;
						break;
				}
				break;
			
			case LED_ACTIVE_HIGH:
				switch(Copy_u8State)
				{
					case OFF:
						GPIO_u8ResetPin(LED_arrMap[Copy_u8_LED_ID].LED_pvGPIOx, LED_arrMap[Copy_u8_LED_ID].LED_u16Pin);
						break;
					case ON:
						GPIO_u8SetPin(LED_arrMap[Copy_u8_LED_ID].LED_pvGPIOx, LED_arrMap[Copy_u8_LED_ID].LED_u16Pin);
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
