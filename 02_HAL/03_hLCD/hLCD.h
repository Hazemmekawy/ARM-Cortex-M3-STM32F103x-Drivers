#ifndef HLCD_H
#define HLCD_H

/* LCD specific macros */
#define HLCD_DATA_LINES_NUMBER	8
#define HLCD_MAX_POSITION	15

/* Line selection macros */
#define HLCD_LINE_1_CMD		0x80
#define HLCD_LINE_2_CMD		0xC0

/* Configurations macros */
/* Data mode selection macros */
#define FOUR_BITS_MODE		0  
#define EIGHT_BITS_MODE		1

/* Number of lines selection macros*/
#define ONE_LINE			0
#define	TWO_LINE			1

/* Font selection macros */
#define FONT_5x7			0
#define FONT_5x10			1

/* Display state selection macros */
#define DISPLAY_OFF			0
#define DISPLAY_ON			1

/* Cursor state selection macros */
#define CURSOR_OFF			0
#define CURSOR_ON			1

/* Cursor blink selection macros */
#define CURSOR_BLINK_OFF	0
#define CURSOR_BLINK_ON		1

/* Display shift direction macros */
#define DECREASE			0
#define INCREASE			1

/* Display shift selection macros */
#define SHIFT_OFF			0
#define SHIFT_ON			1

/* LCD init configurations structure type */
typedef struct
{
	u8 cfgInitState1;
	u8 cfgInitState2;
	u8 cfgInitState3;
	u8 cfgInitState4;

}HLCD_cfgInitStateStruct_t;

/* LCD port configurations structure type */
typedef struct
{
	u8 mode;
	void *dataPorts[HLCD_DATA_LINES_NUMBER];
	u16 dataPins[HLCD_DATA_LINES_NUMBER];
	void *RS_Port;
	u16 RS_Pin;
	void *RW_Port;
	u16 RW_Pin;
	void *E_Port;
	u16 E_Pin;

}HLCD_cfgStruct_t;

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
extern STD_STATUS HLCD_u8Init(void);

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
extern STD_STATUS HLCD_u8WriteData(const u8 *Copy_pu8Buffer, u32 Copy_u32Length);

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
extern STD_STATUS HLCD_u8ClearScreen(void);

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
extern STD_STATUS HLCD_u8MoveCursor(u8 Copy_u8LineNum, u8 Copy_u8Position);

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
extern STD_STATUS HLCD_u8SetWriteCallbackFn(callBackFn_t writeNotifyCbf);

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
extern STD_STATUS HLCD_u8SetClearCallbackFn(callBackFn_t clearNotifyCbf);

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
extern STD_STATUS HLCD_u8SetMoveCallbackFn(callBackFn_t moveNotifyCbf);

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
extern void HLCD_Task(void);

#endif /* HLCD_H */
