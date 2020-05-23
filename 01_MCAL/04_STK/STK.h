#ifndef STK_H
#define STK_H

/* SysTick control and status register masks */
#define		STK_CTRL_ENABLE_MASK		0x00000001
#define		STK_CTRL_TICKINT_MASK		0x00000002
#define		STK_CTRL_CLKSOURCE_MASK		0x00000004
#define 	STK_CTRL_COUNTFLAG_MASK		0x00010000

/* Configuration options of AHB_CLK */
#define		STK_AHB_CLK			0x1
#define		STK_AHB_CLK_BY_8	0x2

#define 	IS_STK_SOURCE_VALID(CLK_SORUCE) 	(((CLK_SORUCE) == STK_AHB_CLK) || \
												((CLK_SORUCE) == STK_AHB_CLK_BY_8))

/* SysTick control and status register */
#define 	STK_CALIB_TENMS_MASK		0x00FFFFFF
#define		STK_CALIB_SKEW_MASK			0x40000000
#define		STK_CALIB_NOREF_MASK		0x80000000

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
*					STATUS_NOT_OK >> Function ended with faliure                                                *
*					STATUS_OK >> Function ended with success                                                    *
*                                                                                                               *
****************************************************************************************************************/
extern STD_STATUS STK_u8Init(void);

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
*					STATUS_NOT_OK >> Function ended with faliure                                                *
*					STATUS_OK >> Function ended with success                                                    *
*                                                                                                               *
****************************************************************************************************************/
extern STD_STATUS STK_u8Start(void);

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
*					STATUS_NOT_OK >> Function ended with faliure                                                *
*					STATUS_OK >> Function ended with success                                                    *
*                                                                                                               *
****************************************************************************************************************/
extern STD_STATUS STK_u8Stop(void);

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
extern STD_STATUS STK_u8SetTimer(u32 Copy_u32Time_us, f32 Copy_f32_AHB_Clock_MHZ);

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
extern STD_STATUS STK_u8SetCallBack(callBackFn_t Copy_pfunc);

#endif /* SYSTICK_H */