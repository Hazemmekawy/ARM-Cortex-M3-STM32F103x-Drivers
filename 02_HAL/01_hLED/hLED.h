#ifndef LED_H
#define LED_H

#define 	LED_ACTIVE_LOW		1
#define 	LED_ACTIVE_HIGH		2

#define 	LED_MAX_NUMBER		3
#define 	LED_RED			0
#define 	LED_GREEN		1
#define 	LED_YELLOW		2

#define IS_LED_VALID(ID) (((ID) == LED_RED) || \
                                ((ID) == LED_GREEN) || \
                                ((ID) == LED_YELLOW))	
								
/* The LED Structure */
typedef struct
{
	uint8_t LED_u8ID;
	void *LED_pvGPIOx;
	uint16_t LED_u16Pin;
	uint8_t LED_u8Speed;
	uint8_t LED_u8ActiveState;
	
}LED_t;

/****************************************************************************************************************
*                                                                                                               *
*	Description:                                                                                                *
*				This function shall initialize the LEDs.                                     					*
*				                                                                                                *
*	Input Parameters:                                                                                           *
*				void                          																	*
*                                                                                                               *
*	Return value:                                                                                               *
*				STD_STATUS: The function's execution status                                                     *
*					Options:                                                                                    *
*					STATUS_NOT_OK >> Function ended with faliure                                                *
*					STATUS_OK >> Function ended with success                                                    *
*                                                                                                               *
****************************************************************************************************************/
extern STD_STATUS hLED_u8Init(void);

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
extern STD_STATUS hLED_u8SetState(uint8_t Copy_u8_LED_ID, STATE Copy_u8State);



#endif /*LED_H*/