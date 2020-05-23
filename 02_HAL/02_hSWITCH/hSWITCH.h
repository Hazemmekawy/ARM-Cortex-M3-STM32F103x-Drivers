#ifndef HSWITCH_H
#define HSWITCH_H

#define 	SWITCH_OS_MODE			FALSE

#define 	SWITCH_NOT_PRESSED		0
#define 	SWITCH_PRESSED			1

#define 	SWITCH_ACTIVE_LOW		1
#define 	SWITCH_ACTIVE_HIGH		2

/* Configure in case of switch task */
#define 	SWITCH_COUNTER_VALUE	5

#define 	SWITCH_MAX_NUMBER		2

#define 	SWITCH_TACKTILE0	0
#define		SWITCH_TACKTILE1	1

#define IS_SWITCH_VALID(ID) (((ID) == SWITCH_TACKTILE0) || \
                                ((ID) == SWITCH_TACKTILE1))	

typedef struct
{
	u8 SWITCH_u8ID;
	void *SWITCH_pvGPIOx;
	u16 SWITCH_u16Pin;
	u8 SWITCH_u8ActiveState;
	
}SWITCH_cfgStruct_t;

#if SWITCH_OS_MODE == FALSE

/****************************************************************************************************************
*                                                                                                               *
*	Description:                                                                                                *
*				This function shall initialize a SWITCH.                                   						*
*				                                                                                                *
*	Input Parameters:                                                                                           *
*				void                         																	*
*                                                                                                               *
*	Return value:                                                                                               *
*				STD_STATUS: The function's execution status                                                     *
*					Options:                                                                                    *
*					STATUS_NOT_OK >> Function ended with faliure                                                *
*					STATUS_OK >> Function ended with success                                                    *
*                                                                                                               *
****************************************************************************************************************/
extern STD_STATUS hSWITCH_u8Init(void);

/****************************************************************************************************************
*                                                                                                               *
*	Description:                                                                                                *
*				This function shall set the status of a SWITCH.                               					*
*				                                                                                                *
*	Input Parameters:                                                                                           *
*				u8 Copy_u8_SWITCH_ID: Takes a SWITCH ID.                                                   		*
*					Options:                                                                                    *
*					A value from the specified IDs in SWITCH.h      											*
*                    	 	                                                                                    *
*				u8 *Copy_u8_SWITCH_Reading: Takes a pointer to a variable where the value is saved         		*
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
extern STD_STATUS hSWITCH_u8ReadState(u8 Copy_u8_SWITCH_ID, u8 *Copy_u8_SWITCH_Reading);



#elif SWITCH_OS_MODE == TRUE

extern STD_STATUS hSWITCH_OS_u8Init(void);
extern STD_STATUS hSWITCH_OS_u8ReadState(u8 Copy_u8ID, u8 *Copy_pu8Reading);
extern void hSWITCH_DebounceTask(void);

#else
	#error "HSWITCH_OS_ERROR"
#endif

#endif	/*HSWITCH_H*/