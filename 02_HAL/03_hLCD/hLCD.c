#include "STD_TYPES.h"

#include "GPIO.h"
#include "hLCD.h"
#include "hLCD_cfg.h"
#include "SCHEDULER.h"

/* LCD Data types macros */
#define HLCD_CMD_TYPE	0
#define HLCD_DATA_TYPE	1

/* LCD commands macros */
#define HLCD_CLEAR_CMD		0x01

#define Conc(b7, b6, b5, b4, b3, b2, b1, b0)		Conc_Help(b7, b6, b5, b4, b3, b2, b1, b0)
#define Conc_Help(b7, b6, b5, b4, b3, b2, b1, b0)	0b##b7##b6##b5##b4##b3##b2##b1##b0

#define INIT_STATE_1	Conc(0, 0, 1, 1, HLCD_NUMBER_OF_LINES, HLCD_FONT, 0, 0)
#define INIT_STATE_2	Conc(0, 0, 0, 0, 1, HLCD_DISPLAY, HLCD_CURSOR, HLCD_CURSOR_BLINK)
#define INIT_STATE_3	Conc(0, 0, 0, 0, 0, 0, 0, 1)
#define INIT_STATE_4	Conc(0, 0, 0, 0, 0, 1, HLCD_INC_DEC, HLCD_SHIFT)

/* LCD init states */
typedef enum
{
	initS1,
	initS2,
	initS3,
	initS4
}initStates_t;

/* LCD scheduler processes */
typedef enum
{
	idleProcess,
	clearProcess,
	writeProcess,
	moveProcess
}process_t;

/* LCD private functions declarations */
static STD_STATUS hLCD_u8Write(u8 Copy_u8Value, u8 Copy_u8WriteType);
static STD_STATUS hLCD_u8InitProcess(void);
static STD_STATUS hLCD_u8WriteProcess(void);
static STD_STATUS hLCD_u8ClearProcess(void);
static STD_STATUS hLCD_u8MoveProcess(void);
static STD_STATUS hLCD_u8SetDataPort(u8 Copy_u8Data);
static STD_STATUS hLCD_u8SetHalfDataPort(u8 Copy_u8Data);

/* LCD Task declaraion */
extern Task_t hLCD_task =
{
	.runnable = hLCD_Task,
	.periodicity_us = 20000 /* 20ms */
};

static const HLCD_cfgInitStateStruct_t HLCD_cfgInitStateStruct =
{
	.cfgInitState1 = INIT_STATE_1,
	.cfgInitState2 = INIT_STATE_2,
	.cfgInitState3 = INIT_STATE_3,
	.cfgInitState4 = INIT_STATE_4
};

static const HLCD_cfgStruct_t HLCD_cfgStruct =
{
	.mode = HLCD_DATA_MODE,
	
    .dataPorts 	= {HLCD_D0_PORT, HLCD_D1_PORT, HLCD_D2_PORT, HLCD_D3_PORT,
					HLCD_D4_PORT, HLCD_D5_PORT, HLCD_D6_PORT, HLCD_D7_PORT},
    
	.dataPins 	= {HLCD_D0_PIN, HLCD_D1_PIN, HLCD_D2_PIN, HLCD_D3_PIN,
					HLCD_D4_PIN, HLCD_D5_PIN, HLCD_D6_PIN, HLCD_D7_PIN},
    
    .RS_Port 	= HLCD_RS_PORT,
    .RS_Pin 	= HLCD_RS_PIN,
    
    .RW_Port 	= HLCD_RW_PORT,
    .RW_Pin 	= HLCD_RW_PIN,
    
	.E_Port 	= HLCD_E_PORT,
	.E_Pin 		= HLCD_E_PIN
};

/* LCD configurations structures */
extern const hLCD_cfgStruct_t hLCD_cfgStruct;
extern const hLCD_cfgInitStateStruct_t hLCD_cfgInitStateStruct;

static u8 initComplete;
static process_t currentProcess;

/* LCD cursorn position */
static u8 hLCD_u8CursorLine;
static u8 hLCD_u8CursorPosition;

/* LCD application notifications callback functions */
static callBackFn_t hLCD_writeAppNotify;
static callBackFn_t hLCD_clearAppNotify;
static callBackFn_t hLCD_moveAppNotify;

/* LCD copy buffer variables */
static u8 *hLCD_pu8CopyBuffer;
static u8 hLCD_u32CopyBufferLength;

/****************************************************************************************************************
*                                                                                                               *
*	Description:                                                                                                *
*				This function shall initialize the LCD pins.                                     				*
*				                                                                                                *
*	Input Parameters:                                                                                           *
*				void                                                   											*
*                                                                                                               *
*	Return value:                                                                                               *
*				STD_STATUS: The function's execution status                                                     *
*					Options:                                                                                    *
*					STATUS_NOT_OK >> Function ended with faliure                                                *
*					STATUS_OK >> Function ended with success                                                    *
*                                                                                                               *
****************************************************************************************************************/
extern STD_STATUS hLCD_u8Init(void)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	u8 local_u8Index = 0;
	GPIO_Init_t local_gpioConfigStruct;
	local_gpioConfigStruct.GPIO_Speed = GPIO_SPEED_2MHZ_MASK;
	local_gpioConfigStruct.GPIO_Mode = GPIO_MODE_OUT_PP_MASK;
	
	/* Configure the GPIO Pins for LCD as outputs */
	for(local_u8Index = 0; local_u8Index < HLCD_DATA_LINES_NUMBER; local_u8Index++)
	{
		local_gpioConfigStruct.GPIO_Pin = hLCD_cfgStruct.dataPins[local_u8Index];		
		GPIO_u8ConfigurePin(hLCD_cfgStruct.dataPorts[local_u8Index], &local_gpioConfigStruct);
	}
	local_gpioConfigStruct.GPIO_Pin = hLCD_cfgStruct.RS_Pin;
	GPIO_u8ConfigurePin(hLCD_cfgStruct.RS_Port, &local_gpioConfigStruct);
	
	local_gpioConfigStruct.GPIO_Pin = hLCD_cfgStruct.RW_Pin;		
	GPIO_u8ConfigurePin(hLCD_cfgStruct.RW_Port, &local_gpioConfigStruct);
	
	local_gpioConfigStruct.GPIO_Pin = hLCD_cfgStruct.E_Pin;		
	GPIO_u8ConfigurePin(hLCD_cfgStruct.E_Port, &local_gpioConfigStruct);
	
	/* Resetting the values to 0 */
	hLCD_u8SetDataPort(0x00);
	GPIO_u8ResetPin(hLCD_cfgStruct.RS_Port, hLCD_cfgStruct.RS_Pin);
	GPIO_u8ResetPin(hLCD_cfgStruct.RW_Port, hLCD_cfgStruct.RW_Pin);
	GPIO_u8ResetPin(hLCD_cfgStruct.E_Port, hLCD_cfgStruct.E_Pin);
	
	local_u8ErrorStatus = STATUS_OK;
	
	return local_u8ErrorStatus;	
}

static STD_STATUS hLCD_u8Write(u8 Copy_u8Value, u8 Copy_u8WriteType)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;

	switch(Copy_u8WriteType)
	{
		case HLCD_CMD_TYPE:
			GPIO_u8ResetPin(hLCD_cfgStruct.RS_Port, hLCD_cfgStruct.RS_Pin);
			GPIO_u8ResetPin(hLCD_cfgStruct.RW_Port, hLCD_cfgStruct.RW_Pin);
			local_u8ErrorStatus = STATUS_OK;
			break;
			
		case HLCD_DATA_TYPE:
			GPIO_u8SetPin(hLCD_cfgStruct.RS_Port, hLCD_cfgStruct.RS_Pin);
		    GPIO_u8ResetPin(hLCD_cfgStruct.RW_Port, hLCD_cfgStruct.RW_Pin);
			local_u8ErrorStatus = STATUS_OK;
			break;
		
		
		default:
			local_u8ErrorStatus = STATUS_NOT_OK;
			break;		
	}
	switch(hLCD_cfgStruct.mode)
	{
		case EIGHT_BITS_MODE:
			/* Set Data on Data Port */
			hLCD_u8SetDataPort(Copy_u8Value);
			local_u8ErrorStatus = STATUS_OK;
			break;
			
		case FOUR_BITS_MODE:
			hLCD_u8SetHalfDataPort(Copy_u8Value >> 4);
			
			//pulsate here
			
			hLCD_u8SetHalfDataPort(Copy_u8Value);
			
			//pulsate here
		
			local_u8ErrorStatus = STATUS_OK;
			break;
		
		
		default:
			local_u8ErrorStatus = STATUS_NOT_OK;
			break;		
	}
	return local_u8ErrorStatus;
}

/****************************************************************************************************************
*                                                                                                               *
*	Description:                                                                                                *
*				This function shall write a string on LCD.                                     					*
*				                                                                                                *
*	Input Parameters:                                                                                           *
*				const u8 *Copy_pu8Buffer: Takes a pointer to the string                                			*
*                                                                                                               *
*				u32 Copy_u32Length: Takes length of the string                       							*
*                                                                                                               *
*	Return value:                                                                                               *
*				STD_STATUS: The function's execution status                                                     *
*					Options:                                                                                    *
*					STATUS_NOT_OK >> Function ended with faliure                                                *
*					STATUS_OK >> Function ended with success                                                    *
*					STATUS_NULLPOINTER >> Function ended with nullpointer error                                 *
*					STATUS_BUSY >> Function was busy                                                    		*
*                                                                                                               *
****************************************************************************************************************/
extern STD_STATUS hLCD_u8WriteData(const u8 *Copy_pu8Buffer, u32 Copy_u32Length)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	u8 local_u8Index = 0;
	
	if(Copy_pu8Buffer)
	{
		if(Copy_u32Length)
		{
			if(currentProcess == idleProcess)
			{
				currentProcess = writeProcess;
				/*for(local_u8Index = 0; local_u8Index < Copy_u32Length; local_u8Index++)
				{
					hLCD_pu8CopyBuffer[local_u8Index] = Copy_pu8Buffer[local_u8Index];
				}*/
				hLCD_pu8CopyBuffer = hLCD_pu8CopyBuffer;
				hLCD_u32CopyBufferLength = Copy_u32Length;
				local_u8ErrorStatus = STATUS_OK;
			}
			else
			{
				/* Returning that the buffer is busy */
				local_u8ErrorStatus = STATUS_BUSY;
			}
		}
		else
		{
			local_u8ErrorStatus = STATUS_NOT_OK;
		}
	}
	else
	{
		local_u8ErrorStatus = STATUS_NULLPOINTER;
	}
	return local_u8ErrorStatus;
}

/****************************************************************************************************************
*                                                                                                               *
*	Description:                                                                                                *
*				This function shall clear the LCD screen                                     					*
*				                                                                                                *
*	Input Parameters:                                                                                           *
*				void                                															*
*                                                                                                               *
*	Return value:                                                                                               *
*				STD_STATUS: The function's execution status                                                     *
*					Options:                                                                                    *
*					STATUS_NOT_OK >> Function ended with faliure                                                *
*					STATUS_OK >> Function ended with success                                                    *
*					STATUS_BUSY >> Function was busy                                                    		*
*                                                                                                               *
****************************************************************************************************************/
extern STD_STATUS hLCD_u8ClearScreen(void)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	
	if(currentProcess == idleProcess)
	{
		currentProcess = clearProcess;	
		local_u8ErrorStatus = STATUS_OK;
	}
	else
	{
		local_u8ErrorStatus = STATUS_BUSY;
	}
	return local_u8ErrorStatus;
}

/****************************************************************************************************************
*                                                                                                               *
*	Description:                                                                                                *
*				This function shall write a string on LCD.                                     					*
*				                                                                                                *
*	Input Parameters:                                                                                           *
*				u8 Copy_u8LineNum: Takes a cursor line                                							*
*                                                                                                               *
*				u8 Copy_u8Position: Takes a crusor position on that line                      					*
*                                                                                                               *
*	Return value:                                                                                               *
*				STD_STATUS: The function's execution status                                                     *
*					Options:                                                                                    *
*					STATUS_NOT_OK >> Function ended with faliure                                                *
*					STATUS_OK >> Function ended with success                                                    *
*					STATUS_BUSY >> Function was busy                                                    		*
*                                                                                                               *
****************************************************************************************************************/
extern STD_STATUS hLCD_u8MoveCursor(u8 Copy_u8LineNum, u8 Copy_u8Position)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	if(((Copy_u8LineNum == HLCD_LINE_1_CMD)||(Copy_u8LineNum == HLCD_LINE_2_CMD)) && 
		(Copy_u8Position <= HLCD_MAX_POSITION))
	{
		if(currentProcess == idleProcess)
		{
			currentProcess = moveProcess;
			hLCD_u8CursorLine = Copy_u8LineNum;
			hLCD_u8CursorPosition = Copy_u8Position;
		}
		else
		{
			local_u8ErrorStatus = STATUS_BUSY;
		}
	}
	else
	{
		local_u8ErrorStatus = STATUS_NOT_OK;
	}
	return local_u8ErrorStatus;
}

static STD_STATUS hLCD_u8InitProcess(void)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	
	static initStates_t currentState = initS1;
	u8 local_u8EnableValue = 0;
	
	GPIO_u8GetPinValue(hLCD_cfgStruct.E_Port, hLCD_cfgStruct.E_Pin, &local_u8EnableValue);
	
	switch(currentState)
	{
		case initS1:
			if(local_u8EnableValue)
			{
				/* Clear enable pin */
				GPIO_u8ResetPin(hLCD_cfgStruct.E_Port, hLCD_cfgStruct.E_Pin);
				currentState = initS2;
			}
			else
			{
				/* Send state1 init command */
				hLCD_u8Write(hLCD_cfgInitStateStruct.cfgInitState1, HLCD_CMD_TYPE);
				
				/* Set enable pin */
				GPIO_u8SetPin(hLCD_cfgStruct.E_Port, hLCD_cfgStruct.E_Pin);
			}
			break;
			
		case initS2:
			if(local_u8EnableValue)
			{
				/* Clear enable pin */
				GPIO_u8ResetPin(hLCD_cfgStruct.E_Port, hLCD_cfgStruct.E_Pin);
				currentState = initS3;
			}
			else
			{
				/* Send state2 init command */
				hLCD_u8Write(hLCD_cfgInitStateStruct.cfgInitState2, HLCD_CMD_TYPE);
				
				/* Set enable pin */
				GPIO_u8SetPin(hLCD_cfgStruct.E_Port, hLCD_cfgStruct.E_Pin);
			}
			break;
		case initS3:
			if(local_u8EnableValue)
			{
				/* Clear enable pin */
				GPIO_u8ResetPin(hLCD_cfgStruct.E_Port, hLCD_cfgStruct.E_Pin);
				currentState = initS4;
			}
			else
			{
				/* Send state3 init command */
				hLCD_u8Write(hLCD_cfgInitStateStruct.cfgInitState3, HLCD_CMD_TYPE);
				
				/* Set enable pin */
				GPIO_u8SetPin(hLCD_cfgStruct.E_Port, hLCD_cfgStruct.E_Pin);
			}
			break;
		case initS4:
			if(local_u8EnableValue)
			{
				/* Clear enable pin */
				GPIO_u8ResetPin(hLCD_cfgStruct.E_Port, hLCD_cfgStruct.E_Pin);
				initComplete = 1;
			}
			else
			{
				/* Send state4 init command */
				hLCD_u8Write(hLCD_cfgInitStateStruct.cfgInitState4, HLCD_CMD_TYPE);
				
				/* Set enable pin */
				GPIO_u8SetPin(hLCD_cfgStruct.E_Port, hLCD_cfgStruct.E_Pin);
			}
			break;
	}
	local_u8ErrorStatus = STATUS_OK;
	return local_u8ErrorStatus;
}

static STD_STATUS hLCD_u8WriteProcess(void)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	static u8 local_u8CurrentChar = 0;
	u8 local_u8EnableValue = 0;
	
	GPIO_u8GetPinValue(hLCD_cfgStruct.E_Port, hLCD_cfgStruct.E_Pin, &local_u8EnableValue);
	
	if(local_u8EnableValue)
	{
		/* Clear enable pin */
		GPIO_u8ResetPin(hLCD_cfgStruct.E_Port, hLCD_cfgStruct.E_Pin);
	}
	else
	{
		/* Check if all chars has been written */
		if(local_u8CurrentChar == hLCD_u32CopyBufferLength)
		{
			currentProcess = idleProcess;
			local_u8CurrentChar = 0;
			if(hLCD_writeAppNotify)
			{
				hLCD_writeAppNotify();	
			}
		}
		else
		{
			hLCD_u8Write(hLCD_pu8CopyBuffer[local_u8CurrentChar], HLCD_DATA_TYPE);
			local_u8CurrentChar++;
			/* Set enable pin */
			GPIO_u8SetPin(hLCD_cfgStruct.E_Port, hLCD_cfgStruct.E_Pin);
		}
	}
	local_u8ErrorStatus = STATUS_OK;
	return local_u8ErrorStatus;
}

static STD_STATUS hLCD_u8ClearProcess(void)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	
	u8 local_u8EnableValue = 0;
	
	GPIO_u8GetPinValue(hLCD_cfgStruct.E_Port, hLCD_cfgStruct.E_Pin, &local_u8EnableValue);
	
	if(local_u8EnableValue)
	{
		/* Clear enable pin */
		GPIO_u8ResetPin(hLCD_cfgStruct.E_Port, hLCD_cfgStruct.E_Pin);
		currentProcess = idleProcess;
		if(hLCD_clearAppNotify)
		{
			hLCD_clearAppNotify();
		}
	}
	else
	{
		hLCD_u8Write(HLCD_CLEAR_CMD, HLCD_CMD_TYPE);
		/* Set enable pin */
		GPIO_u8SetPin(hLCD_cfgStruct.E_Port, hLCD_cfgStruct.E_Pin);
	}
	local_u8ErrorStatus = STATUS_OK;
	return local_u8ErrorStatus;
}

static STD_STATUS hLCD_u8MoveProcess(void)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	
	u8 local_u8EnableValue = 0;
	
	GPIO_u8GetPinValue(hLCD_cfgStruct.E_Port, hLCD_cfgStruct.E_Pin, &local_u8EnableValue);
	
	if(local_u8EnableValue)
	{
		/* Clear enable pin */
		GPIO_u8ResetPin(hLCD_cfgStruct.E_Port, hLCD_cfgStruct.E_Pin);
		currentProcess = idleProcess;
		hLCD_u8CursorLine = 0;
		hLCD_u8CursorPosition = 0;
		if(hLCD_moveAppNotify)
		{
			hLCD_moveAppNotify();
		}
	}
	else
	{
		hLCD_u8Write(hLCD_u8CursorLine + hLCD_u8CursorPosition, HLCD_CMD_TYPE);
		/* Set enable pin */
		GPIO_u8SetPin(hLCD_cfgStruct.E_Port, hLCD_cfgStruct.E_Pin);
	}
	local_u8ErrorStatus = STATUS_OK;
	return local_u8ErrorStatus;
}

/****************************************************************************************************************
*                                                                                                               *
*	Description:                                                                                                *
*				This function shall call the write complete notification function                               *
*				                                                                                                *
*	Input Parameters:                                                                                           *
*				callBackFn_t writeNotifyCbf: Takes a call back function pointer                                	*
*                                                                                                               *
*	Return value:                                                                                               *
*				STD_STATUS: The function's execution status                                                     *
*					Options:                                                                                    *
*					STATUS_NOT_OK >> Function ended with faliure                                                *
*					STATUS_OK >> Function ended with success                                                    *
*					STATUS_NULLPOINTER >> Function ended with nullpointer error                                 *
*                                                                                                               *
****************************************************************************************************************/
extern STD_STATUS hLCD_u8SetWriteCallbackFn(callBackFn_t writeNotifyCbf)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	
	if(writeNotifyCbf)
	{
		hLCD_writeAppNotify = writeNotifyCbf;
		local_u8ErrorStatus = STATUS_OK;
	}
	else
	{
		local_u8ErrorStatus = STATUS_NULLPOINTER;
	}
	
	return local_u8ErrorStatus;
}

/****************************************************************************************************************
*                                                                                                               *
*	Description:                                                                                                *
*				This function shall call the clear complete notification function                               *
*				                                                                                                *
*	Input Parameters:                                                                                           *
*				callBackFn_t clearNotifyCbf: Takes a call back function pointer                                	*
*                                                                                                               *
*	Return value:                                                                                               *
*				STD_STATUS: The function's execution status                                                     *
*					Options:                                                                                    *
*					STATUS_NOT_OK >> Function ended with faliure                                                *
*					STATUS_OK >> Function ended with success                                                    *
*					STATUS_NULLPOINTER >> Function ended with nullpointer error                                 *
*                                                                                                               *
****************************************************************************************************************/
extern STD_STATUS hLCD_u8SetClearCallbackFn(callBackFn_t clearNotifyCbf)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	
	if(clearNotifyCbf)
	{
		hLCD_clearAppNotify = clearNotifyCbf;
		local_u8ErrorStatus = STATUS_OK;
	}
	else
	{
		local_u8ErrorStatus = STATUS_NULLPOINTER;
	}
	
	return local_u8ErrorStatus;
}

/****************************************************************************************************************
*                                                                                                               *
*	Description:                                                                                                *
*				This function shall call the move cursor complete notification function                         *
*				                                                                                                *
*	Input Parameters:                                                                                           *
*				callBackFn_t moveNotifyCbf: Takes a call back function pointer                                	*
*                                                                                                               *
*	Return value:                                                                                               *
*				STD_STATUS: The function's execution status                                                     *
*					Options:                                                                                    *
*					STATUS_NOT_OK >> Function ended with faliure                                                *
*					STATUS_OK >> Function ended with success                                                    *
*					STATUS_NULLPOINTER >> Function ended with nullpointer error                                 *
*                                                                                                               *
****************************************************************************************************************/
extern STD_STATUS hLCD_u8SetMoveCallbackFn(callBackFn_t moveNotifyCbf)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	
	if(moveNotifyCbf)
	{
		hLCD_moveAppNotify = moveNotifyCbf;
		local_u8ErrorStatus = STATUS_OK;
	}
	else
	{
		local_u8ErrorStatus = STATUS_NULLPOINTER;
	}
	
	return local_u8ErrorStatus;
}

/****************************************************************************************************************
*                                                                                                               *
*	Description:                                                                                                *
*				This function shall execute the LCD Task                              							*
*				                                                                                                *
*	Input Parameters:                                                                                           *
*				void                                															*
*                                                                                                               *
*	Return value:                                                                                               *
*				STD_STATUS: The function's execution status                                                     *
*					Options:                                                                                    *
*					STATUS_NOT_OK >> Function ended with faliure                                                *
*					STATUS_OK >> Function ended with success                                                    *
*					STATUS_NULLPOINTER >> Function ended with nullpointer error                                 *
*                                                                                                               *
****************************************************************************************************************/
extern void hLCD_Task(void)
{
	if(initComplete)
	{
		switch(currentProcess)
		{
			case idleProcess:	
				break;
				
			case writeProcess:	
				hLCD_u8WriteProcess();
				break;
				
			case clearProcess:	
				hLCD_u8ClearProcess();
				break;
				
			case moveProcess:	
				hLCD_u8MoveProcess();
				break;		
				
			default:
				break;
		}
	}
	else
	{
		hLCD_u8InitProcess();	
	}
}

static STD_STATUS hLCD_u8SetDataPort(u8 Copy_u8Data)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	u8 local_u8Index;
	
	for(local_u8Index = 0; local_u8Index < HLCD_DATA_LINES_NUMBER; local_u8Index++)
	{
		GPIO_u8WritePinValue(
								hLCD_cfgStruct.dataPorts[local_u8Index], 
								hLCD_cfgStruct.dataPins[local_u8Index], 
								(Copy_u8Data >> local_u8Index) & 0x1
							);
	}
	local_u8ErrorStatus = STATUS_OK;
	return local_u8ErrorStatus;
}

static STD_STATUS hLCD_u8SetHalfDataPort(u8 Copy_u8Data)
{	
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	u8 local_u8Index;
	
	for(local_u8Index = HLCD_DATA_LINES_NUMBER/2; local_u8Index < HLCD_DATA_LINES_NUMBER; local_u8Index++)
	{
		GPIO_u8WritePinValue(
								hLCD_cfgStruct.dataPorts[local_u8Index], 
								hLCD_cfgStruct.dataPins[local_u8Index], 
								(Copy_u8Data >> local_u8Index) & 0x1
							);
	}
	local_u8ErrorStatus = STATUS_OK;
	return local_u8ErrorStatus;
}

//FUTURE ENHANCEMENT:
// COMPLETE THE 4BIT MODE
// ADD FUNCTIONS TO ACCEPT SPECIAL CHARACHTERS >> adding an extra intit stage and new function for special write
