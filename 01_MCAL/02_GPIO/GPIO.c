#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO.h"

typedef struct
{
	volatile u32 CRL; 
	volatile u32 CRH;
	volatile u32 IDR;
	volatile u32 ODR;
	volatile u32 BSRR;
	volatile u32 BRR;
	volatile u32 LCK;
}GPIO_t;

/****************************************************************************************************************
*                                                                                                               *
*	Description:                                                                                                *
*				This function shall configure a variable number of pins.                                     	*
*				                                                                                                *
*	Input Parameters:                                                                                           *
*				void *Copy_pvGPIO: Takes a macro of GPIO pointer                                				*
*					Options:                                                                                    *
*					GPIOA >> GPIOA selection                                                      				*
*					GPIOB >> GPIOB selection                                                      				*
*					GPIOC >> GPIOC selection                                                      				*
*                                                                                                               *
*				GPIO_Init_t* GPIO_InitStruct: Takes a structure of the pin configurations                       *
*                                                                                                               *
*	Return value:                                                                                               *
*				STD_STATUS: The function's execution status                                                     *
*					Options:                                                                                    *
*					STATUS_NOT_OK >> Function ended with faliure                                                *
*					STATUS_OK >> Function ended with success                                                    *
*                                                                                                               *
****************************************************************************************************************/
extern STD_STATUS GPIO_u8ConfigurePin(void *Copy_pvGPIO, GPIO_Init_t* GPIO_InitStruct)
{
	u8 Local_u8PinIndex = 0;
	u32 Local_u32RegisterCopy = 0;
	u8 Local_u8PinConfig = 0;
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	GPIO_t *GPIOx = (GPIO_t *)Copy_pvGPIO;
	
	if(IS_GPIO(Copy_pvGPIO) && 
		IS_GPIO_PIN(GPIO_InitStruct->GPIO_Pin) && 
		IS_GPIO_SPEED(GPIO_InitStruct->GPIO_Speed) && 
		IS_GPIO_MODE(GPIO_InitStruct->GPIO_Mode))
	{
		Local_u8PinConfig = (GPIO_InitStruct->GPIO_Speed | GPIO_InitStruct->GPIO_Mode);
		
		Local_u32RegisterCopy = GPIOx->CRL;
		for(Local_u8PinIndex = 0; Local_u8PinIndex < (REGISTER_SIZE/2); Local_u8PinIndex++)
		{
			if((GPIO_InitStruct->GPIO_Pin) & (1<<Local_u8PinIndex))
			{
				/* Configurations of CRL */
				
				/* Clear the old configurations for that pin */
				Local_u32RegisterCopy &= ~(((GPIO_SPEED_CLR_MASK | GPIO_MODE_CLR_MASK)) << (4 * Local_u8PinIndex));       //(GPIO_SPEED_CLR_MASK & GPIO_MODE_CLR_MASK) << (4 * Local_u8PinIndex);
				
				/* Assign the new pin configuration */
				Local_u32RegisterCopy |= (Local_u8PinConfig) << (4 * Local_u8PinIndex);
				
				/* The case of Input pull-up */
				if(GPIO_InitStruct->GPIO_Mode & GPIO_MODE_IN_PU_MASK)
				{
					GPIOx->BSRR = (1 << Local_u8PinIndex);
				}
			}
		}
		/* Write the new pin configurations to CRL */
		GPIOx->CRL = Local_u32RegisterCopy;
		
		Local_u32RegisterCopy = GPIOx->CRH;
		for(Local_u8PinIndex = (REGISTER_SIZE/2); Local_u8PinIndex < REGISTER_SIZE; Local_u8PinIndex++)
		{
			if((GPIO_InitStruct->GPIO_Pin) & (1<<Local_u8PinIndex))
			{
				/* Configurations of CRH */
				
				/* Clear the old configurations for that pin */
				Local_u32RegisterCopy &= ~(((GPIO_SPEED_CLR_MASK | GPIO_MODE_CLR_MASK)) << (4 * (Local_u8PinIndex - 8)));
				
				/* Assign the new pin configuration */
				Local_u32RegisterCopy |= (Local_u8PinConfig) << (4 * (Local_u8PinIndex - 8));
				
				/* The case of Input pull-up */
				if(GPIO_InitStruct->GPIO_Mode & GPIO_MODE_IN_PU_MASK)
				{
					GPIOx->BSRR = (1 << Local_u8PinIndex);
				}
			}
		}
		/* Write the new configurations to CRH */
		GPIOx->CRH = Local_u32RegisterCopy;
		
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
*				This function shall set variable number of pins.                                     			*
*				                                                                                                *
*	Input Parameters:                                                                                           *
*				void *Copy_pvGPIO: Takes a macro of GPIO pointer                                				*
*					Options:                                                                                    *
*					GPIOA >> GPIOA selection                                                      				*
*					GPIOB >> GPIOB selection                                                      				*
*					GPIOC >> GPIOC selection                                                      				*
*                                                                                                               *
*				uint16_t Copy_u16PinMask: Takes a mask of the selected pins to be set                    		*
*                                                                                                               *
*	Return value:                                                                                               *
*				STD_STATUS: The function's execution status                                                     *
*					Options:                                                                                    *
*					STATUS_NOT_OK >> Function ended with faliure                                                *
*					STATUS_OK >> Function ended with success                                                    *
*                                                                                                               *
****************************************************************************************************************/
extern STD_STATUS GPIO_u8SetPin(void *Copy_pvGPIO, uint16_t Copy_u16PinMask)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	GPIO_t *GPIOx = (GPIO_t *)Copy_pvGPIO;
	
	if(IS_GPIO_PIN(Copy_u16PinMask))
	{
		GPIOx -> BSRR = Copy_u16PinMask;
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
*				This function shall reset variable number of pins.                                     			*
*				                                                                                                *
*	Input Parameters:                                                                                           *
*				void *Copy_pvGPIO: Takes a macro of GPIO pointer                                				*
*					Options:                                                                                    *
*					GPIOA >> GPIOA selection                                                      				*
*					GPIOB >> GPIOB selection                                                      				*
*					GPIOC >> GPIOC selection                                                      				*
*                                                                                                               *
*				uint16_t Copy_u16PinMask: Takes a mask of the selected pins to be reset                    		*
*                                                                                                               *
*	Return value:                                                                                               *
*				STD_STATUS: The function's execution status                                                     *
*					Options:                                                                                    *
*					STATUS_NOT_OK >> Function ended with faliure                                                *
*					STATUS_OK >> Function ended with success                                                    *
*                                                                                                               *
****************************************************************************************************************/
extern STD_STATUS GPIO_u8ResetPin(void *Copy_pvGPIO, uint16_t Copy_u16PinMask)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	GPIO_t *GPIOx = (GPIO_t *)Copy_pvGPIO;
	
	if(IS_GPIO_PIN(Copy_u16PinMask))
	{
		GPIOx -> BRR = Copy_u16PinMask;
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
*				This function shall get the value of a pin                                						*
*				                                                                                                *
*	Input Parameters:                                                                                           *
*				void *Copy_pvGPIO: Takes a macro of GPIO pointer                                				*
*					Options:                                                                                    *
*					GPIOA >> GPIOA selection                                                      				*
*					GPIOB >> GPIOB selection                                                      				*
*					GPIOC >> GPIOC selection                                                      				*
*                                                                                                               *
*				uint16_t Copy_u16PinMask: Takes a mask of the selected pins to be reset                         *
*                                                                                                               *
*				uint8_t* Copy_pu8Value: Takes the pointer to a variable where the return is saved				*														*
*                                                                                                               *
*	Return value:                                                                                               *
*				STD_STATUS: The function's execution status                                                     *
*					Options:                                                                                    *
*					STATUS_NOT_OK >> Function ended with faliure                                                *
*					STATUS_OK >> Function ended with success                                                    *
*                                                                                                               *
****************************************************************************************************************/
extern STD_STATUS GPIO_u8GetPinValue(void *Copy_pvGPIO, uint16_t Copy_u16PinMask, uint8_t* Copy_pu8Value)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	GPIO_t *GPIOx = (GPIO_t *)Copy_pvGPIO;
	
	if(IS_GPIO_PIN(Copy_u16PinMask))
	{
		if(((GPIOx->IDR) & Copy_u16PinMask) == 0)
		{
			*Copy_pu8Value = 0;
		}
		else
		{
			*Copy_pu8Value = 1;
		}
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
*				This function shall set variable number of pins(LOW/HIGH).                             			*
*				                                                                                                *
*	Input Parameters:                                                                                           *
*				void *Copy_pvGPIO: Takes a macro of GPIO pointer                                				*
*					Options:                                                                                    *
*					GPIOA >> GPIOA selection                                                      				*
*					GPIOB >> GPIOB selection                                                      				*
*					GPIOC >> GPIOC selection                                                      				*
*                                                                                                               *
*				u16 Copy_u16PinMask: Takes a mask of the selected pins to be set                    			*
*                                                                       	                                    *
*				LEVEL Copy_u8Level: Takes a mask of the selected pins to be set                                 *
*					Options:                                                                                    *
*					LOW  >> 0                                                                                   *
*					HIGH >> 1																					*
*                                                                                                               *
*	Return value:                                                                                               *
*				STD_STATUS: The function's execution status                                                     *
*					Options:                                                                                    *
*					STATUS_NOT_OK >> Function ended with faliure                                                *
*					STATUS_OK >> Function ended with success                                                    *
*                                                                                                               *
****************************************************************************************************************/
extern STD_STATUS GPIO_u8WritePinValue(void *Copy_pvGPIO, uint16_t Copy_u16PinMask, LEVEL Copy_u8Level)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	GPIO_t *GPIOx = (GPIO_t *)Copy_pvGPIO;
	
	if(IS_GPIO_PIN(Copy_u16PinMask))
	{
		if(Copy_u8Level)
		{
			GPIOx -> BSRR = Copy_u16PinMask;
		}
		else
		{
			GPIOx -> BRR = Copy_u16PinMask;
		}
		local_u8ErrorStatus = STATUS_OK;
	}
	else
	{
		local_u8ErrorStatus = STATUS_NOT_OK;
	}
	return local_u8ErrorStatus;
}

