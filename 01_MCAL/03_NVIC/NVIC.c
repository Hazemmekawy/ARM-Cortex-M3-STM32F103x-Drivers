#include "STD_TYPES.h"
#include "NVIC.h"

#define 	REGISTER_SIZE		32
//System Block Control registers

#define 	SCB_AIRCR		*((u32*)0xE000ED0C)	//Application interrupt and reset control register
#define 	SCB_SHCSR		*((u32*)0xE000ED24)	//System Handler Control and State register

#define 	IS_EXCEPTION_VALID(EXCEPTION)	(((EXCEPTION) == SCB_SHCSR_MEMFAULTENA_MASK) || \
											((EXCEPTION) == SCB_SHCSR_BUSFAULTENA_MASK)	|| \
											((EXCEPTION) == SCB_SHCSR_USGFAULTENA_MASK)	|| \
											((EXCEPTION) == SCB_SHCSR_CLRFAULTENA_MASK))

#define 	IS_PRIGROUP_VALID(PRIGROUP)		(((PRIGROUP) == SCB_AIRCR_PRIGROUP_3_MASK) 	|| \
											((PRIGROUP) == SCB_AIRCR_PRIGROUP_4_MASK)	|| \
											((PRIGROUP) == SCB_AIRCR_PRIGROUP_5_MASK)	|| \
											((PRIGROUP) == SCB_AIRCR_PRIGROUP_6_MASK) 	|| \
											((PRIGROUP) == SCB_AIRCR_PRIGROUP_7_MASK))

//NVIC Registers
//Interrupt Enable registers

#define 	SETENA_PTR		((u32*)0xE000E100)
#define 	SETENA0			*((u32*)0xE000E100)		//Exceptions: 16(#0) ~ 47(#31)
#define 	SETENA1			*((u32*)0xE000E104) 	//Exceptions: 48(#32) ~ 79(#63)
#define 	SETENA2			*((u32*)0xE000E108) 	//Exceptions: 80(#64) ~ 111(#95)
#define 	SETENA3			*((u32*)0xE000E10C) 	//Exceptions: 112(#96) ~ 143(#127)
#define 	SETENA4			*((u32*)0xE000E110) 	//Exceptions: 144(#128) ~ 175(#159)
#define 	SETENA5			*((u32*)0xE000E114) 	//Exceptions: 176(#160) ~ 207(#191)
#define 	SETENA6			*((u32*)0xE000E118)		//Exceptions: 208(#192) ~ 239(#223)
#define 	SETENA7			*((u32*)0xE000E11C)		//Exceptions: 240(#224) ~ 271(#255)

//Interrupt Clear registers

#define 	CLRENA_PTR		((u32*)0xE000E180)
#define 	CLRENA0			*((u32*)0xE000E180)		//Exceptions: 16(#0) ~ 47(#31)
#define 	CLRENA1			*((u32*)0xE000E184)  	//Exceptions: 48(#32) ~ 79(#63)
#define 	CLRENA2			*((u32*)0xE000E188)  	//Exceptions: 80(#64) ~ 111(#95)
#define 	CLRENA3			*((u32*)0xE000E18C)  	//Exceptions: 112(#96) ~ 143(#127)
#define 	CLRENA4			*((u32*)0xE000E190)  	//Exceptions: 144(#128) ~ 175(#159)
#define 	CLRENA5			*((u32*)0xE000E194)  	//Exceptions: 176(#160) ~ 207(#191)
#define 	CLRENA6			*((u32*)0xE000E198)		//Exceptions: 208(#192) ~ 239(#223)
#define 	CLRENA7			*((u32*)0xE000E19C)		//Exceptions: 240(#224) ~ 271(#255)

//Interrupt Set Pending registers

#define 	SETPEND_PTR		((u32*)0xE000E200)
#define 	SETPEND0		*((u32*)0xE000E200)		//Exceptions: 16(#0) ~ 47(#31)
#define 	SETPEND1		*((u32*)0xE000E204)  	//Exceptions: 48(#32) ~ 79(#63)
#define 	SETPEND2		*((u32*)0xE000E208)  	//Exceptions: 80(#64) ~ 111(#95)
#define 	SETPEND3		*((u32*)0xE000E20C)  	//Exceptions: 112(#96) ~ 143(#127)
#define 	SETPEND4		*((u32*)0xE000E210)  	//Exceptions: 144(#128) ~ 175(#159)
#define 	SETPEND5		*((u32*)0xE000E214)  	//Exceptions: 176(#160) ~ 207(#191)
#define 	SETPEND6		*((u32*)0xE000E218)		//Exceptions: 208(#192) ~ 239(#223)
#define 	SETPEND7		*((u32*)0xE000E21C)		//Exceptions: 240(#224) ~ 271(#255)

//Interrupt Clear Pending registers

#define 	CLRPEND_PTR		((u32*)0xE000E280)
#define 	CLRPEND0		*((u32*)0xE000E280)		//Exceptions: 16(#0) ~ 47(#31)
#define 	CLRPEND1		*((u32*)0xE000E284)  	//Exceptions: 48(#32) ~ 79(#63)
#define 	CLRPEND2		*((u32*)0xE000E288)  	//Exceptions: 80(#64) ~ 111(#95)
#define 	CLRPEND3		*((u32*)0xE000E28C)  	//Exceptions: 112(#96) ~ 143(#127)
#define 	CLRPEND4		*((u32*)0xE000E290)  	//Exceptions: 144(#128) ~ 175(#159)
#define 	CLRPEND5		*((u32*)0xE000E294)  	//Exceptions: 176(#160) ~ 207(#191)
#define 	CLRPEND6		*((u32*)0xE000E298)		//Exceptions: 208(#192) ~ 239(#223)
#define 	CLRPEND7		*((u32*)0xE000E29C)		//Exceptions: 240(#224) ~ 271(#255)

//Interrupt Clear Pending registers

#define 	ACTIVE_PTR		((u32*)0xE000E300)
#define 	ACTIVE0			*((u32*)0xE000E300)		//Exceptions: 16(#0) ~ 47(#31)
#define 	ACTIVE1			*((u32*)0xE000E304)  	//Exceptions: 48(#32) ~ 79(#63)
#define 	ACTIVE2			*((u32*)0xE000E308)  	//Exceptions: 80(#64) ~ 111(#95)
#define 	ACTIVE3			*((u32*)0xE000E30C)  	//Exceptions: 112(#96) ~ 143(#127)
#define 	ACTIVE4			*((u32*)0xE000E310)  	//Exceptions: 144(#128) ~ 175(#159)
#define 	ACTIVE5			*((u32*)0xE000E314)  	//Exceptions: 176(#160) ~ 207(#191)
#define 	ACTIVE6			*((u32*)0xE000E318)		//Exceptions: 208(#192) ~ 239(#223)
#define 	ACTIVE7			*((u32*)0xE000E31C)		//Exceptions: 240(#224) ~ 271(#255)

//Interrupt Priority-Level Registers

#define 	NVIC_PRI_PTR	((u8*)0xE000E400)

//Interrupt numbers validation
#define 	IS_EXTINT_NUMBER_VALID(EXTINT_NUMBER)	((EXTINT_NUMBER <= NVIC_EXTINT_239))


/****************************************************************************************************************
*                                                                                                               *
*	Description:                                                                                                *
*				This function shall enable an external interrupt.                                     			*
*				                                                                                                *
*	Input Parameters:                                                                                           *
*				u8 Copy_u8InterruptNumber: Takes the external interrupt number.                                	*
*					Options:                                                                                    *
*					NVIC_EXTINT_0 ~ NVIC_EXTINT_239                                     						*
*                                                                                                               *
*	Return value:                                                                                               *
*				STD_STATUS: The function's execution status                                                     *
*					Options:                                                                                    *
*					STATUS_NOT_OK >> Function ended with faliure                                                *
*					STATUS_OK >> Function ended with success                                                    *
*                                                                                                               *
****************************************************************************************************************/
extern STD_STATUS NVIC_u8InterruptEnable(u8 Copy_u8InterruptNumber)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	u8 local_u8RegisterIndex = 0;
	u8 local_u8IntIndex = 0;
	
	if(IS_EXTINT_NUMBER_VALID(Copy_u8InterruptNumber))
	{
		local_u8RegisterIndex = (Copy_u8InterruptNumber / REGISTER_SIZE); //to get the register index 
		local_u8IntIndex = (Copy_u8InterruptNumber % REGISTER_SIZE); //to get the interrupt index
		SETENA_PTR[local_u8RegisterIndex] |= (1<<local_u8IntIndex);
		local_u8ErrorStatus = STATUS_OK;
	}
	else
	{
		local_u8ErrorStatus = STATUS_NOT_OK;
	}
	
	return local_u8ErrorStatus;
}

/****************************************************************************************************************
*                                                                                                               *
*	Description:                                                                                                *
*				This function shall disable an external interrupt.                                     			*
*				                                                                                                *
*	Input Parameters:                                                                                           *
*				u8 Copy_u8InterruptNumber: Takes the external interrupt number.                                	*
*					Options:                                                                                    *
*					NVIC_EXTINT_0 ~ NVIC_EXTINT_239                                     						*
*                                                                                                               *
*	Return value:                                                                                               *
*				STD_STATUS: The function's execution status                                                     *
*					Options:                                                                                    *
*					STATUS_NOT_OK >> Function ended with faliure                                                *
*					STATUS_OK >> Function ended with success                                                    *
*                                                                                                               *
****************************************************************************************************************/
extern STD_STATUS NVIC_u8InterruptDisable(u8 Copy_u8InterruptNumber)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	u8 local_u8RegisterIndex = 0;
	u8 local_u8IntIndex = 0;
	
	if(IS_EXTINT_NUMBER_VALID(Copy_u8InterruptNumber))
	{
		local_u8RegisterIndex = (Copy_u8InterruptNumber / REGISTER_SIZE); //to get the register index 
		local_u8IntIndex = (Copy_u8InterruptNumber % REGISTER_SIZE); //to get the interrupt index		
		CLRENA_PTR[local_u8RegisterIndex] |= (1<<local_u8IntIndex);
		local_u8ErrorStatus = STATUS_OK;
	}
	else
	{
		local_u8ErrorStatus = STATUS_NOT_OK;
	}
	
	return local_u8ErrorStatus;
}

/****************************************************************************************************************
*                                                                                                               *
*	Description:                                                                                                *
*				This function shall set pending status for an external interrupt.                               *
*				                                                                                                *
*	Input Parameters:                                                                                           *
*				u8 Copy_u8InterruptNumber: Takes the external interrupt number.                                	*
*					Options:                                                                                    *
*					NVIC_EXTINT_0 ~ NVIC_EXTINT_239                                     						*
*                                                                                                               *
*	Return value:                                                                                               *
*				STD_STATUS: The function's execution status                                                     *
*					Options:                                                                                    *
*					STATUS_NOT_OK >> Function ended with faliure                                                *
*					STATUS_OK >> Function ended with success                                                    *
*                                                                                                               *
****************************************************************************************************************/
extern STD_STATUS NVIC_u8SetPendingStatus(u8 Copy_u8InterruptNumber)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	u8 local_u8RegisterIndex = 0;
	u8 local_u8IntIndex = 0;
	
	if(IS_EXTINT_NUMBER_VALID(Copy_u8InterruptNumber))
	{
		local_u8RegisterIndex = (Copy_u8InterruptNumber / REGISTER_SIZE); //to get the register index 
		local_u8IntIndex = (Copy_u8InterruptNumber % REGISTER_SIZE); //to get the interrupt index
		SETPEND_PTR[local_u8RegisterIndex] |= (1<<local_u8IntIndex);
		local_u8ErrorStatus = STATUS_OK;
	}
	else
	{
		local_u8ErrorStatus = STATUS_NOT_OK;
	}
	
	return local_u8ErrorStatus;
}

/****************************************************************************************************************
*                                                                                                               *
*	Description:                                                                                                *
*				This function shall clear pending status for an external interrupt.                             *
*				                                                                                                *
*	Input Parameters:                                                                                           *
*				u8 Copy_u8InterruptNumber: Takes the external interrupt number.                                	*
*					Options:                                                                                    *
*					NVIC_EXTINT_0 ~ NVIC_EXTINT_239                                     						*
*                                                                                                               *
*	Return value:                                                                                               *
*				STD_STATUS: The function's execution status                                                     *
*					Options:                                                                                    *
*					STATUS_NOT_OK >> Function ended with faliure                                                *
*					STATUS_OK >> Function ended with success                                                    *
*                                                                                                               *
****************************************************************************************************************/
extern STD_STATUS NVIC_u8ClearPendingStatus(u8 Copy_u8InterruptNumber)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	u8 local_u8RegisterIndex = 0;
	u8 local_u8IntIndex = 0;
	
	if(IS_EXTINT_NUMBER_VALID(Copy_u8InterruptNumber))
	{
		local_u8RegisterIndex = (Copy_u8InterruptNumber / REGISTER_SIZE); //to get the register index 
		local_u8IntIndex = (Copy_u8InterruptNumber % REGISTER_SIZE); //to get the interrupt index
		CLRPEND_PTR[local_u8RegisterIndex] |= (1<<local_u8IntIndex);
		local_u8ErrorStatus = STATUS_OK;
	}
	else
	{
		local_u8ErrorStatus = STATUS_NOT_OK;
	}
	
	return local_u8ErrorStatus;
}

/****************************************************************************************************************
*                                                                                                               *
*	Description:                                                                                                *
*				This function shall get the active status for an external interrupt.                            *
*				                                                                                                *
*	Input Parameters:                                                                                           *
*				u8 Copy_u8InterruptNumber: Takes the external interrupt number.                                	*
*					Options:                                                                                    *
*					NVIC_EXTINT_0 ~ NVIC_EXTINT_239                                                             *
*				                                                                                                *
*				u8 *Copy_pu8Status: Takes the pointer to a variable where the status is saved                   *
*                                                                                                               *
*	Return value:                                                                                               *
*				STD_STATUS: The function's execution status                                                     *
*					Options:                                                                                    *
*					STATUS_NOT_OK >> Function ended with faliure                                                *
*					STATUS_OK >> Function ended with success                                                    *
*                                                                                                               *
****************************************************************************************************************/
extern STD_STATUS NVIC_u8GetActiveStatus(u8 Copy_u8InterruptNumber, u8 *Copy_pu8Status)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	u8 local_u8RegisterIndex = 0;
	u8 local_u8IntIndex = 0;
	
	if(IS_EXTINT_NUMBER_VALID(Copy_u8InterruptNumber))
	{
		local_u8RegisterIndex = (Copy_u8InterruptNumber / REGISTER_SIZE); //to get the register index 
		local_u8IntIndex = (Copy_u8InterruptNumber % REGISTER_SIZE); //to get the interrupt index
		*Copy_pu8Status = ((ACTIVE_PTR[local_u8RegisterIndex] >> local_u8IntIndex) & 0x01);
		local_u8ErrorStatus = STATUS_OK;
	}
	else
	{
		local_u8ErrorStatus = STATUS_NOT_OK;
	}
	
	return local_u8ErrorStatus;
}

/****************************************************************************************************************
*                                                                                                               *
*	Description:                                                                                                *
*				This function shall set the priority for an interrupt.                            				*
*				                                                                                                *
*	Input Parameters:                                                                                           *
*				u8 Copy_u8InterruptNumber: Takes the external interrupt number.                                	*
*					Options:                                                                                    *
*					NVIC_EXTINT_0 ~ NVIC_EXTINT_239                                                             *
*				                                                                                                *
*				u8 Copy_u8Priority: Takes priority of the interrupt.                   							*
*                                                                                                               *
*	Return value:                                                                                               *
*				STD_STATUS: The function's execution status                                                     *
*					Options:                                                                                    *
*					STATUS_NOT_OK >> Function ended with faliure                                                *
*					STATUS_OK >> Function ended with success                                                    *
*                                                                                                               *
****************************************************************************************************************/
extern STD_STATUS NVIC_u8SetPriority(u8 Copy_u8InterruptNumber, u8 Copy_u8Priority)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	
	if(IS_EXTINT_NUMBER_VALID(Copy_u8InterruptNumber))
	{	
		NVIC_PRI_PTR[Copy_u8InterruptNumber] = Copy_u8Priority;
		local_u8ErrorStatus = STATUS_OK;
	}
	else
	{
		local_u8ErrorStatus = STATUS_NOT_OK;
	}
	return local_u8ErrorStatus;
}

/****************************************************************************************************************
*                                                                                                               *
*	Description:                                                                                                *
*				This function shall get the active status for an external interrupt.                            *
*				                                                                                                *
*	Input Parameters:                                                                                           *
*				u8 Copy_u8InterruptNumber: Takes the external interrupt number.                                	*
*					Options:                                                                                    *
*					NVIC_EXTINT_0 ~ NVIC_EXTINT_239                                                             *
*				                                                                                                *
*				u8 *Copy_pu8PriorityValue: Takes the pointer to a variable where the priority value is saved.   *
*                                                                                                               *
*	Return value:                                                                                               *
*				STD_STATUS: The function's execution status                                                     *
*					Options:                                                                                    *
*					STATUS_NOT_OK >> Function ended with faliure                                                *
*					STATUS_OK >> Function ended with success                                                    *
*                                                                                                               *
****************************************************************************************************************/
extern STD_STATUS NVIC_u8GetPriority(u8 Copy_u8InterruptNumber, u8 *Copy_pu8PriorityValue)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;;
	
	if(IS_EXTINT_NUMBER_VALID(Copy_u8InterruptNumber))
	{	
		*Copy_pu8PriorityValue = NVIC_PRI_PTR[Copy_u8InterruptNumber];
		local_u8ErrorStatus = STATUS_OK;
	}
	else
	{
		local_u8ErrorStatus = STATUS_NOT_OK;
	}
	
	return local_u8ErrorStatus;
}

/****************************************************************************************************************
*                                                                                                               *
*	Description:                                                                                                *
*				This function shall configure the priority group bits.                            				*
*				                                                                                                *
*	Input Parameters:                                                                                           *
*				u32 Copy_u32PriorityGroupMask: Takes a mask of the priority group bits.                        	*
*					Options:                                                                                    *
*					SCB_AIRCR_PRIGROUP_3_MASK    																*
*                   SCB_AIRCR_PRIGROUP_4_MASK                                                                   *
*                   SCB_AIRCR_PRIGROUP_5_MASK                                                                   *
*                   SCB_AIRCR_PRIGROUP_6_MASK                                                                   *
*                   SCB_AIRCR_PRIGROUP_7_MASK                                                                   *
*                                                                                                               *
*	Return value:                                                                                               *
*				STD_STATUS: The function's execution status                                                     *
*					Options:                                                                                    *
*					STATUS_NOT_OK >> Function ended with faliure                                                *
*					STATUS_OK >> Function ended with success                                                    *
*                                                                                                               *
****************************************************************************************************************/
extern STD_STATUS NVIC_u8ConfigureGroupBits(u32 Copy_u32PriorityGroupMask)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	
	if(IS_PRIGROUP_VALID(Copy_u32PriorityGroupMask))
	{	
		/* Clear the Priority Group bits */
		SCB_AIRCR &= SCB_AIRCR_PRIGROUP_CLR_MASK;
		SCB_AIRCR |= Copy_u32PriorityGroupMask;
		local_u8ErrorStatus = STATUS_OK;
	}
	else
	{
		local_u8ErrorStatus = STATUS_NOT_OK;
	}
	
	return local_u8ErrorStatus;
}

/****************************************************************************************************************
*                                                                                                               *
*	Description:                                                                                                *
*				This function shall enable all peripheral interrupts                            				*
*				                                                                                                *
*	Input Parameters:                                                                                           *
*				void  																							*
*                                                                                                               *
*	Return value:                                                                                               *
*				STD_STATUS: The function's execution status                                                     *
*					Options:                                                                                    *
*					STATUS_NOT_OK >> Function ended with faliure                                                *
*					STATUS_OK >> Function ended with success                                                    *
*                                                                                                               *
****************************************************************************************************************/
extern STD_STATUS NVIC_u8EnableAllPeripheralsInterrupts(void)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	
	/* Clear the PRIMASK */
	__asm__("MOV R4, #0");
	__asm__("MSR PRIMASK, R4");
	local_u8ErrorStatus = STATUS_OK;
	return local_u8ErrorStatus;
}

/****************************************************************************************************************
*                                                                                                               *
*	Description:                                                                                                *
*				This function shall disable all peripheral interrupts                            				*
*				                                                                                                *
*	Input Parameters:                                                                                           *
*				void  																							*
*                                                                                                               *
*	Return value:                                                                                               *
*				STD_STATUS: The function's execution status                                                     *
*					Options:                                                                                    *
*					STATUS_NOT_OK >> Function ended with faliure                                                *
*					STATUS_OK >> Function ended with success                                                    *
*                                                                                                               *
****************************************************************************************************************/
extern STD_STATUS NVIC_u8DisableAllPeripheralsInterrupts(void)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	
	/* Set the PRIMASK */
	__asm__("MOV R4, #1");
	__asm__("MSR PRIMASK, R4");
	local_u8ErrorStatus = STATUS_OK;
	return local_u8ErrorStatus;
}

/****************************************************************************************************************
*                                                                                                               *
*	Description:                                                                                                *
*				This function shall enable all internal interrupts                            					*
*				                                                                                                *
*	Input Parameters:                                                                                           *
*				void  																							*
*                                                                                                               *
*	Return value:                                                                                               *
*				STD_STATUS: The function's execution status                                                     *
*					Options:                                                                                    *
*					STATUS_NOT_OK >> Function ended with faliure                                                *
*					STATUS_OK >> Function ended with success                                                    *
*                                                                                                               *
****************************************************************************************************************/
extern STD_STATUS NVIC_u8EnableAllFaultExceptions(void)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	
	__asm__("MOV R4, #0");
	__asm__("MSR FAULTMASK, R4");
	local_u8ErrorStatus = STATUS_OK;
	return local_u8ErrorStatus;
}

/****************************************************************************************************************
*                                                                                                               *
*	Description:                                                                                                *
*				This function shall disable all internal interrupts                            					*
*				                                                                                                *
*	Input Parameters:                                                                                           *
*				void  																							*
*                                                                                                               *
*	Return value:                                                                                               *
*				STD_STATUS: The function's execution status                                                     *
*					Options:                                                                                    *
*					STATUS_NOT_OK >> Function ended with faliure                                                *
*					STATUS_OK >> Function ended with success                                                    *
*                                                                                                               *
****************************************************************************************************************/
extern STD_STATUS NVIC_u8DisableAllFaultExceptions(void)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	
	__asm__("MOV R4, #1");
	__asm__("MSR FAULTMASK, R4");
	local_u8ErrorStatus = STATUS_OK;
	return local_u8ErrorStatus;
}

/****************************************************************************************************************
*                                                                                                               *
*	Description:                                                                                                *
*				This function shall enable an internal exception.                            					*
*				                                                                                                *
*	Input Parameters:                                                                                           *
*				u32 Copy_u32FaultExceptionMask: 																*
*					Options:	                                                                                *
*					SCB_SHCSR_MEMFAULTENA_MASK                                                                  *
*					SCB_SHCSR_BUSFAULTENA_MASK                                                                  *
*					SCB_SHCSR_USGFAULTENA_MASK                                                                  *
*                                                                                                               *
*	Return value:                                                                                               *
*				STD_STATUS: The function's execution status                                                     *
*					Options:                                                                                    *
*					STATUS_NOT_OK >> Function ended with faliure                                                *
*					STATUS_OK >> Function ended with success                                                    *
*                                                                                                               *
****************************************************************************************************************/
extern STD_STATUS NVIC_u8EnableFaultException(u32 Copy_u32FaultExceptionMask) 
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	
	if(IS_EXCEPTION_VALID(Copy_u32FaultExceptionMask))
	{
		SCB_SHCSR |= Copy_u32FaultExceptionMask;
		local_u8ErrorStatus = STATUS_OK;
	}
	else
	{
		local_u8ErrorStatus = STATUS_NOT_OK;
	}
	return local_u8ErrorStatus;
}

/****************************************************************************************************************
*                                                                                                               *
*	Description:                                                                                                *
*				This function shall disable an internal exception.                            					*
*				                                                                                                *
*	Input Parameters:                                                                                           *
*				u32 Copy_u32FaultExceptionMask: 																*
*					Options:	                                                                                *
*					SCB_SHCSR_MEMFAULTENA_MASK                                                                  *
*					SCB_SHCSR_BUSFAULTENA_MASK                                                                  *
*					SCB_SHCSR_USGFAULTENA_MASK                                                                  *
*                                                                                                               *
*	Return value:                                                                                               *
*				STD_STATUS: The function's execution status                                                     *
*					Options:                                                                                    *
*					STATUS_NOT_OK >> Function ended with faliure                                                *
*					STATUS_OK >> Function ended with success                                                    *
*                                                                                                               *
****************************************************************************************************************/
extern STD_STATUS NVIC_u8DisableFaultException(u32 Copy_u32FaultExceptionMask) 
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	
	if(IS_EXCEPTION_VALID(Copy_u32FaultExceptionMask))
	{
		SCB_SHCSR &= ~Copy_u32FaultExceptionMask;
		local_u8ErrorStatus = STATUS_OK;
	}
	else
	{
		local_u8ErrorStatus = STATUS_NOT_OK;
	}
	return local_u8ErrorStatus;
}

/****************************************************************************************************************
*                                                                                                               *
*	Description:                                                                                                *
*				This function shall set an interrupt filter level.                            					*
*				                                                                                                *
*	Input Parameters:                                                                                           *
*				u8 Copy_u8Priority: Takes the priority at which the filteration is set.                        	*
*					Options:                                                                                    *
*					u8 Copy_u8Priority:  	0 >> clears the filter.                                             *
*											1~127 >> sets the filter at the specified value 					*									*
*                                                                                                               *
*	Return value:                                                                                               *
*				STD_STATUS: The function's execution status                                                     *
*					Options:                                                                                    *
*					STATUS_NOT_OK >> Function ended with faliure                                                *
*					STATUS_OK >> Function ended with success                                                    *
*                                                                                                               *
****************************************************************************************************************/
extern STD_STATUS NVIC_u8SetPriorityFilter(u8 Copy_u8Priority)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	
	/* 
		- The funtion argument is stored in R0 0.
		- We need to shift the value 4 bits to the left as implemented in ST.	
	*/
	__asm__("LSLS R0, R0, #4");
	__asm__("MSR BASEPRI, R0");
	local_u8ErrorStatus = STATUS_OK;
	
	return local_u8ErrorStatus;
}
