#include "RCC.h"


typedef struct
{
	volatile u32 CR;		/* Clock control register, offset = 0x00*/
	volatile u32 CFGR;		/* Clock configuration register, offset = 0x04 */
	volatile u32 CIR;		/* Clock interrupt register, offset = 0x08 */
	volatile u32 APB2RSTR;	/* APB2 peripheral reset register, offset = 0x0C */
	volatile u32 APB1RSTR;	/* APB1 peripheral reset register, offset = 0x10 */
	volatile u32 AHBENR;	/* AHB peripheral clock enable register, offset = 0x14 */
	volatile u32 APB2ENR;	/* APB2 peripheral clock enable register, offset = 0x18 */
	volatile u32 APB1ENR;	/* APB1 peripheral clock enable register, offset = 0x1C */
	volatile u32 BDCR;		/* Backup domain control register, offset = 0x20 */
	volatile u32 CSR;		/* Control/status register, offset = 0x24 */

}RCC_t;

/* This is a pointer to a block that corresponds to RCC memory map */
volatile RCC_t* const RCC = (RCC_t*)0x40021000;

/*note add the PLL multiplier*/

/****************************************************************************************************************
*                                                                                                               *
*	Description:                                                                                                *
*				This function shall control the state of the clock(OFF/ON).                                     *
*				                                                                                                *
*	Input Parameters:                                                                                           *
*				u32 Copy_u32ClkSelectionMask: Takes the mask of the selected Clk                                *
*					Options:                                                                                    *
*					RCC_CR_HSION_MASK >> HSI clk selection                                                      *
*					RCC_CR_HSEON_MASK >> HSE clk selection                                                      *
*					RCC_CR_PLLON_MASK >> PLL clk selection                                                      *
*                                                                                                               *
*				STATE Copy_u8Status: Takes the status of the selected Clk                                       *
*					Options:                                                                                    *
*					OFF >> Turn off the clock                                                                   *
*					ON >> Turn on the clock                                                                     *
*                                                                                                               *
*	Return value:                                                                                               *
*				STD_STATUS: The function's execution status                                                     *
*					Options:                                                                                    *
*					STATUS_NOT_OK >> Function ended with failure                                                *
*					STATUS_OK >> Function ended with success                                                    *
*                                                                                                               *
****************************************************************************************************************/
extern STD_STATUS RCC_u8ControlClks(u32 Copy_u32ClkSelectionMask, STATE Copy_u8Status)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	u32 Local_u32RegisterCopy = 0;
	
	if(IS_RCC_CLK_MASK_VALID(Copy_u32ClkSelectionMask))
	{
		switch(Copy_u8Status)
			{
				case OFF:
					
					Local_u32RegisterCopy = RCC->CR;
					Local_u32RegisterCopy &= ~Copy_u32ClkSelectionMask;
					RCC->CR = Local_u32RegisterCopy;
					local_u8ErrorStatus = STATUS_OK;
					break;
					
				case ON:
				
					Local_u32RegisterCopy = RCC->CR;
					Local_u32RegisterCopy |= Copy_u32ClkSelectionMask;
					RCC->CR = Local_u32RegisterCopy;
					local_u8ErrorStatus = STATUS_OK;
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

/****************************************************************************************************************
*                                                                                                               *
*	Description:                                                                                                *
*				This function shall select the system clock.                                                    *
*				                                                                                                *
*	Input Parameters:                                                                                           *
*				u32 Copy_u32ClkSelectionMask: Takes the mask of the selected Clk                                *
*					Options:                                                                                    *
*					RCC_CFGR_SW_HSI_MASK >> HSI clk selected as system clk.                                     *
*					RCC_CFGR_SW_HSE_MASK >> HSE clk selected as system clk.                                     *
*					RCC_CFGR_SW_PLL_MASK >> PLL clk selected as system clk.                                     *
*				                                                                                                *
*	Return value:                                                                                               *
*				STD_STATUS: The function's execution status                                                     *
*					Options:                                                                                    *
*					STATUS_NOT_OK >> Function ended with failure                                                *
*					STATUS_OK >> Function ended with success                                                    *
*                                                                                                               *
****************************************************************************************************************/
extern STD_STATUS RCC_u8SelectSysClk(u32 Copy_u32SysClkSelectionMask)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	u32 Local_u32RegisterCopy = 0;
	
	if(IS_RCC_SYS_CLK_MASK_VALID(Copy_u32SysClkSelectionMask))
	{
		Local_u32RegisterCopy = RCC->CFGR;
		Local_u32RegisterCopy &= RCC_CFGR_SW_CLR_MASK;
		Local_u32RegisterCopy |= Copy_u32SysClkSelectionMask;
		RCC->CFGR = Local_u32RegisterCopy;
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
*				This function shall configure the PLL source.                                                   *
*				(Make sure that the PLL is not selected as the sysclk)                                          *
*				                                                                                                *
*	Input Parameters:                                                                                           *
*				u32 Copy_u32PLLSourceMask: Takes the mask of the selected Clk                                   *
*					Options:                                                                                    *
*					RCC_CFGR_PLLSRC_HSI_BY_2_MASK >> HSI divided by 2 is selected as PLL source                 *
*					RCC_CFGR_PLLSRC_HSE_MASK >> HSE is selected as PLL source                                   *
*                                                                                                               *
*               u32 Copy_u32MultiplierValueMask                                                                 *
*					RCC_CFGR_PLLMUL_X2_MASK	                                                                    *
*					RCC_CFGR_PLLMUL_X3_MASK	                                                                    *
*					RCC_CFGR_PLLMUL_X4_MASK	                                                                    *
*					RCC_CFGR_PLLMUL_X5_MASK	                                                                    *
*					RCC_CFGR_PLLMUL_X6_MASK	                                                                    *
*					RCC_CFGR_PLLMUL_X7_MASK	                                                                    *
*					RCC_CFGR_PLLMUL_X8_MASK	                                                                    *
*					RCC_CFGR_PLLMUL_X9_MASK	                                                                    *
*					RCC_CFGR_PLLMUL_X10_MASK                                                                    *
*					RCC_CFGR_PLLMUL_X11_MASK                                                                    *
*					RCC_CFGR_PLLMUL_X12_MASK                                                                    *
*					RCC_CFGR_PLLMUL_X13_MASK                                                                    *
*					RCC_CFGR_PLLMUL_X14_MASK                                                                    *
*					RCC_CFGR_PLLMUL_X15_MASK                                                                    *
*					RCC_CFGR_PLLMUL_X16_MASK                                                                    *
*                                                                                     							*
*	Return value:                                                                                               *
*				STD_STATUS: The function's execution status                                                     *
*					Options:                                                                                    *
*					STATUS_NOT_OK >> Function ended with failure                                                *
*					STATUS_OK >> Function ended with success                                                    *
*                                                                                                               *
****************************************************************************************************************/
extern STD_STATUS RCC_u8ConfigurePLL(u32 Copy_u32PLLSourceMask, u32 Copy_u32MultiplierValueMask)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	u32 Local_u32RegisterCopy = 0;
	
	if(IS_RCC_PLL_SOURCE_VALID(Copy_u32PLLSourceMask) &&
		IS_RCC_PLL_MULTIPLIER_VALID(Copy_u32MultiplierValueMask))
	{
		/* Check that the CLK is not selected as SysClk */
		if(RCC->CFGR & RCC_CFGR_SW_PLL_MASK)
		{
			local_u8ErrorStatus =  STATUS_NOT_OK;
		}
		else
		{
			/* Select the PLL source */
			Local_u32RegisterCopy = RCC->CFGR;
			Local_u32RegisterCopy &= RCC_CFGR_PLLSRC_CLR_MASK;
			Local_u32RegisterCopy |= Copy_u32PLLSourceMask;	
			RCC->CFGR = Local_u32RegisterCopy;
			
			/* Select the PLL multiplier*/
			Local_u32RegisterCopy = RCC->CFGR;
			Local_u32RegisterCopy &= RCC_CFGR_PLLMUL_CLR_MASK;
			Local_u32RegisterCopy |= Copy_u32MultiplierValueMask;	
			RCC->CFGR = Local_u32RegisterCopy;
			
			local_u8ErrorStatus = STATUS_OK;
		}
	}
	else
	{
		local_u8ErrorStatus =  STATUS_NOT_OK;
	}
	
	return local_u8ErrorStatus;
}

/****************************************************************************************************************
*                                                                                                               *
*	Description:                                                                                                *
*				This function shall configure the MCO source.                                                   *
*				                                                                                                *
*	Input Parameters:                                                                                           *
*				u32 Copy_u32MCOSelectionMask: Takes the mask of the selected Clk                                *
*					Options:                                                                                    *
*					RCC_CFGR_PLLSRC_HSI_BY_2_MASK >> HSI divided by 2 is selected as PLL source                 *
*					RCC_CFGR_PLLSRC_HSE_MASK >> HSE is selected as PLL source                                   *
*                                                                                                               *
*	Return value:                                                                                               *
*				STD_STATUS: The function's execution status                                                     *
*					Options:                                                                                    *
*					STATUS_NOT_OK >> Function ended with failure                                                *
*					STATUS_OK >> Function ended with success                                                    *
*                                                                                                               *
****************************************************************************************************************/
extern STD_STATUS RCC_u8ConfigureMCO(u32 Copy_u32MCOSelectionMask)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	u32 Local_u32RegisterCopy = 0;
	
	if(IS_RCC_MCO_SOURCE_VALID(Copy_u32MCOSelectionMask))
	{
		Local_u32RegisterCopy = RCC->CFGR;
		Local_u32RegisterCopy &= RCC_CFGR_MCO_CLR_MASK;
		Local_u32RegisterCopy |= Copy_u32MCOSelectionMask;	
		RCC->CFGR = Local_u32RegisterCopy;
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
*				This function shall configure the prescaler of AHB bus.                                         *
*				                                                                                                *
*	Input Parameters:                                                                                           *
*				u32 Copy_u32AHBPrescalerSelectionMask: Takes the mask of the selected AHB prescaler.            *
*					Options:                                                                                    *
*					RCC_CFGR_HPRE_SYSCLK_NO_DIVISION_MASK	>> SYSCLK not divided is selected as AHB clk.       *
*                   RCC_CFGR_HPRE_SYSCLK_BY_2_MASK			>> SYSCLK divided by 2 is selected as AHB clk.      *
*                   RCC_CFGR_HPRE_SYSCLK_BY_4_MASK			>> SYSCLK divided by 4 is selected as AHB clk.      *
*                   RCC_CFGR_HPRE_SYSCLK_BY_8_MASK			>> SYSCLK divided by 8 is selected as AHB clk.      *
*                   RCC_CFGR_HPRE_SYSCLK_BY_16_MASK			>> SYSCLK divided by 16 is selected as AHB clk.     *
*                   RCC_CFGR_HPRE_SYSCLK_BY_64_MASK			>> SYSCLK divided by 64 is selected as AHB clk.     *
*                   RCC_CFGR_HPRE_SYSCLK_BY_128_MASK		>> SYSCLK divided by 128 is selected as AHB clk.    *
*                   RCC_CFGR_HPRE_SYSCLK_BY_256_MASK		>> SYSCLK divided by 256 is selected as AHB clk.    *
*					RCC_CFGR_HPRE_SYSCLK_BY_512_MASK		>> SYSCLK divided by 512 is selected as AHB clk.    *
*	                                                                                                            *
*	Return value:                                                                                               *
*				STD_STATUS: The function's execution status                                                     *
*					Options:                                                                                    *
*					STATUS_NOT_OK >> Function ended with failure                                                *
*					STATUS_OK >> Function ended with success                                                    *
*                                                                                                               *
****************************************************************************************************************/
extern STD_STATUS RCC_u8Configure_AHB_Prescaler(u32 Copy_u32AHBPrescalerSelectionMask)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	u32 Local_u32RegisterCopy = 0;
	
	if(IS_RCC_AHB_PRESCALER_VALID(Copy_u32AHBPrescalerSelectionMask))
	{
		Local_u32RegisterCopy = RCC->CFGR;
		Local_u32RegisterCopy &= RCC_CFGR_MCO_CLR_MASK;
		Local_u32RegisterCopy |= Copy_u32AHBPrescalerSelectionMask;	
		RCC->CFGR = Local_u32RegisterCopy;
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
*				This function shall configure the prescaler of APB1 bus.                                         *
*				                                                                                                *
*	Input Parameters:                                                                                           *
*				u32 Copy_u32APB1PrescalerSelectionMask: Takes the mask of the selected APB1 prescaler.          *
*					Options:                                                                                    *
*					RCC_CFGR_PPRE1_HCLK_NO_DIVISION_MASK	>> HCLK not divided is selected as APB1 clk.       	*
*                   RCC_CFGR_PPRE1_HCLK_BY_2_MASK			>> HCLK divided by 2 is selected as APB1 clk.      	*
*                   RCC_CFGR_PPRE1_HCLK_BY_4_MASK			>> HCLK divided by 4 is selected as APB1 clk.      	*
*                   RCC_CFGR_PPRE1_HCLK_BY_8_MASK			>> HCLK divided by 8 is selected as APB1 clk.      	*
*                   RCC_CFGR_PPRE1_HCLK_BY_16_MASK			>> HCLK divided by 16 is selected as APB1 clk.     	*        
*	                                                                                                            *
*	Return value:                                                                                               *
*				STD_STATUS: The function's execution status                                                     *
*					Options:                                                                                    *
*					STATUS_NOT_OK >> Function ended with failure                                                *
*					STATUS_OK >> Function ended with success                                                    *
*                                                                                                               *
****************************************************************************************************************/
extern STD_STATUS RCC_u8Configure_APB1_Prescaler(u32 Copy_u32APB1PrescalerSelectionMask)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	u32 Local_u32RegisterCopy = 0;
	
	if(IS_RCC_APB1_PRESCALER_VALID(Copy_u32APB1PrescalerSelectionMask))
	{
		Local_u32RegisterCopy = RCC->CFGR;
		Local_u32RegisterCopy &= RCC_CFGR_PPRE1_CLR_MASK;
		Local_u32RegisterCopy |= Copy_u32APB1PrescalerSelectionMask;	
		RCC->CFGR = Local_u32RegisterCopy;
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
*				This function shall configure the prescaler of APB2 bus.                                        *
*				                                                                                                *
*	Input Parameters:                                                                                           *
*				u32 Copy_u32APB2PrescalerSelectionMask: Takes the mask of the selected APB1 prescaler.          *
*					Options:                                                                                    *
*					RCC_CFGR_PPRE2_HCLK_NO_DIVISION_MASK	>> HCLK not divided is selected as APB2 clk.       	*
*                   RCC_CFGR_PPRE2_HCLK_BY_2_MASK			>> HCLK divided by 2 is selected as APB2 clk.      	*
*                   RCC_CFGR_PPRE2_HCLK_BY_4_MASK			>> HCLK divided by 4 is selected as APB2 clk.      	*
*                   RCC_CFGR_PPRE2_HCLK_BY_8_MASK			>> HCLK divided by 8 is selected as APB2 clk.      	*
*                   RCC_CFGR_PPRE2_HCLK_BY_16_MASK			>> HCLK divided by 16 is selected as APB2 clk.     	*       
*	                                                                                                            *
*	Return value:                                                                                               *
*				STD_STATUS: The function's execution status                                                     *
*					Options:                                                                                    *
*					STATUS_NOT_OK >> Function ended with failure                                                *
*					STATUS_OK >> Function ended with success                                                    *
*                                                                                                               *
****************************************************************************************************************/
extern STD_STATUS RCC_u8Configure_APB2_Prescaler(u32 Copy_u32APB2PrescalerSelectionMask)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	u32 Local_u32RegisterCopy = 0;
	
	
	if(IS_RCC_APB2_PRESCALER_VALID(Copy_u32APB2PrescalerSelectionMask))
	{
		Local_u32RegisterCopy = RCC->CFGR;
		Local_u32RegisterCopy &= RCC_CFGR_PPRE2_CLR_MASK;
		Local_u32RegisterCopy |= Copy_u32APB2PrescalerSelectionMask;	
		RCC->CFGR = Local_u32RegisterCopy;
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
*				This function shall configure the prescaler of ADC.                                        		*
*				                                                                                                *
*	Input Parameters:                                                                                           *
*				u32 Copy_u32ADCPrescalerSelectionMask: Takes the mask of the selected ADC prescaler.          	*
*					Options:                                                                                    *
*					RCC_CFGR_ADCPRE_PCLK2_BY_2_MASK	>> PCLK2 divided by 2 is selected as ADC clk.      			*
*                   RCC_CFGR_ADCPRE_PCLK2_BY_4_MASK	>> PCLK2 divided by 4 is selected as ADC clk.      			*
*                   RCC_CFGR_ADCPRE_PCLK2_BY_6_MASK	>> PCLK2 divided by 6 is selected as ADC clk.      			*
*                   RCC_CFGR_ADCPRE_PCLK2_BY_8_MASK	>> PCLK2 divided by 8 is selected as ADC clk.      			*   
*	                                                                                                            *
*	Return value:                                                                                               *
*				STD_STATUS: The function's execution status                                                     *
*					Options:                                                                                    *
*					STATUS_NOT_OK >> Function ended with failure                                                *
*					STATUS_OK >> Function ended with success                                                    *
*                                                                                                               *
****************************************************************************************************************/
extern STD_STATUS RCC_u8Configure_ADC_Prescaler(u32 Copy_u32ADCPrescalerSelectionMask)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	u32 Local_u32RegisterCopy = 0;
	
	if(IS_RCC_ADC_PRESCALER_VALID(Copy_u32ADCPrescalerSelectionMask))
	{
		Local_u32RegisterCopy = RCC->CFGR;
		Local_u32RegisterCopy &= RCC_CFGR_ADCPRE_CLR_MASK;
		Local_u32RegisterCopy |= Copy_u32ADCPrescalerSelectionMask;	
		RCC->CFGR = Local_u32RegisterCopy;
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
*				This function shall (Disable/Enable) the peripherals clk.                                 		*
*				                                                                                                *
*	Input Parameters:                                                                                           *
*				BUS Copy_u8Bus: Takes the mask of the selected ADC prescaler.          							*
*					Options:                                                                                    *
*				                                                                                                *
*				u32 Copy_u32PeripheralMask:                                                                     *
*					Options:                                                                                    *
*	                                                                                                            *
*				STATE Copy_u8Status: Takes the status of the selected Clk                                       *
*					Options:                                                                                    *
*					OFF >> Turn off the clock                                                                   *
*					ON >> Turn on the clock                                                                     *
*                                                                                                               *
*	Return value:                                                                                               *
*				STD_STATUS: The function's execution status                                                     *
*					Options:                                                                                    *
*					STATUS_NOT_OK >> Function ended with failure                                                *
*					STATUS_OK >> Function ended with success                                                    *
*                                                                                                               *
****************************************************************************************************************/
extern STD_STATUS RCC_u8ControlPeripherals(BUS Copy_u8Bus, u32 Copy_u32PeripheralMask, STATE Copy_u8Status)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	u32 Local_u32RegisterCopy = 0;
	
	switch(Copy_u8Bus)
	{
		case AHB:
			switch(Copy_u8Status)
			{
				case OFF:
					
					Local_u32RegisterCopy = RCC->AHBENR;
					Local_u32RegisterCopy &= ~Copy_u32PeripheralMask;
					RCC->AHBENR = Local_u32RegisterCopy;
					break;
					
				case ON:
			
					Local_u32RegisterCopy = RCC->AHBENR;
					Local_u32RegisterCopy |= Copy_u32PeripheralMask;
					RCC->AHBENR = Local_u32RegisterCopy;
					break;
			
				default:
					local_u8ErrorStatus = STATUS_NOT_OK;
					break;
			}
			break;

		case APB2:
			switch(Copy_u8Status)
			{
				case OFF:
					
					Local_u32RegisterCopy = RCC->APB2ENR;
					Local_u32RegisterCopy &= ~Copy_u32PeripheralMask;
					RCC->APB2ENR = Local_u32RegisterCopy;
					break;
				
				case ON:
				
					Local_u32RegisterCopy = RCC->APB2ENR;
					Local_u32RegisterCopy |= Copy_u32PeripheralMask;
					RCC->APB2ENR = Local_u32RegisterCopy;
					break;

				default:
				
					local_u8ErrorStatus = STATUS_NOT_OK;
					break;
			}
			break;

		case APB1:
			switch(Copy_u8Status)
			{
				case OFF:
				
					Local_u32RegisterCopy = RCC->APB1ENR;
					Local_u32RegisterCopy &= ~Copy_u32PeripheralMask;
					RCC->APB1ENR = Local_u32RegisterCopy;
					break;
				
				case ON:
				
					Local_u32RegisterCopy = RCC->APB1ENR;
					Local_u32RegisterCopy |= Copy_u32PeripheralMask;
					RCC->APB1ENR = Local_u32RegisterCopy;
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
	return local_u8ErrorStatus;
}

extern STD_STATUS RCC_u8GetSysClk(u32 *Copy_pu32SysClkMaskReturn)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	
	if(Copy_pu32SysClkMaskReturn)
	{
		*Copy_pu32SysClkMaskReturn = (RCC->CFGR) & RCC_CFGR_SWS_MASK;
		local_u8ErrorStatus = STATUS_OK;
	}
	else
	{
		local_u8ErrorStatus = STATUS_NULLPOINTER;
	}
	return local_u8ErrorStatus;	
	
}

extern STD_STATUS RCC_u8Get_AHB_Prescaler(u32 *Copy_pu32PrescalerMaskReturn)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	
	if(Copy_pu32PrescalerMaskReturn)
	{
		*Copy_pu32PrescalerMaskReturn = (RCC->CFGR) & (~RCC_CFGR_HPRE_CLR_MASK);
	}
	else
	{
		local_u8ErrorStatus = STATUS_NULLPOINTER;
	}
	return local_u8ErrorStatus;	
}

extern STD_STATUS RCC_u8Get_APB1_Prescaler(u32 *Copy_pu32PrescalerMaskReturn)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	
	if(Copy_pu32PrescalerMaskReturn)
	{
		*Copy_pu32PrescalerMaskReturn = (RCC->CFGR) & (~RCC_CFGR_PPRE1_CLR_MASK);
	}
	else
	{
		local_u8ErrorStatus = STATUS_NULLPOINTER;
	}
	return local_u8ErrorStatus;	
}

extern STD_STATUS RCC_u8Get_APB2_Prescaler(u32 *Copy_pu32PrescalerMaskReturn)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	
	if(Copy_pu32PrescalerMaskReturn)
	{
		*Copy_pu32PrescalerMaskReturn = (RCC->CFGR) & (~RCC_CFGR_PPRE2_CLR_MASK);
	}
	else
	{
		local_u8ErrorStatus = STATUS_NULLPOINTER;
	}
	return local_u8ErrorStatus;	
}

extern STD_STATUS RCC_u8Get_PLL_Multiplier(u32 *Copy_pu32MultiplierMaskReturn)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	
	if(Copy_pu32MultiplierMaskReturn)
	{
		*Copy_pu32MultiplierMaskReturn = (RCC->CFGR) & (~RCC_CFGR_PLLMUL_CLR_MASK);
	}
	else
	{
		local_u8ErrorStatus = STATUS_NULLPOINTER;
	}
	return local_u8ErrorStatus;	
}

extern STD_STATUS RCC_u8Get_PLL_Source(u32 *Copy_pu32SourceMaskReturn)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	
	if(Copy_pu32SourceMaskReturn)
	{
		*Copy_pu32SourceMaskReturn = (RCC->CFGR) & (~RCC_CFGR_PLLSRC_CLR_MASK);
	}
	else
	{
		local_u8ErrorStatus = STATUS_NULLPOINTER;
	}
	return local_u8ErrorStatus;	
}

extern STD_STATUS RCC_u8Get_AHB_ClkFrequncyMHZ(f32 *Copy_pf32Frequncy)
{
	STD_STATUS local_u8ErrorStatus = STATUS_OK;
	f32 local_f32TempFrequency = 0;
	u32 local_u32TempMask = 0;
	
	if(Copy_pf32Frequncy)
	{
		/* Get the SYSCLK */
		RCC_u8GetSysClk(&local_u32TempMask);
		switch(local_u32TempMask)
		{
			case RCC_CFGR_SWS_HSI_MASK:	local_f32TempFrequency = 8; 	break;
			case RCC_CFGR_SWS_HSE_MASK:	local_f32TempFrequency = 8;		break;
			case RCC_CFGR_SWS_PLL_MASK:		
				/* Get PLL source */
				RCC_u8Get_PLL_Source(&local_u32TempMask);
				switch(local_u32TempMask)
				{
					case RCC_CFGR_PLLSRC_HSI_BY_2_MASK:	local_f32TempFrequency = 4; 	break;
					case RCC_CFGR_PLLSRC_HSE_MASK:		local_f32TempFrequency = 8; 	break;
					default:	
						local_u8ErrorStatus = STATUS_NOT_OK; 
						break;
				}
				/* Get PLL Multiplier */
				RCC_u8Get_PLL_Multiplier(&local_u32TempMask);
				switch(local_u32TempMask)
				{
					case RCC_CFGR_PLLMUL_X2_MASK:		local_f32TempFrequency *= 2;	break;
					case RCC_CFGR_PLLMUL_X3_MASK:		local_f32TempFrequency *= 3;	break;
					case RCC_CFGR_PLLMUL_X4_MASK:		local_f32TempFrequency *= 4;	break;
					case RCC_CFGR_PLLMUL_X5_MASK:		local_f32TempFrequency *= 5;	break;
					case RCC_CFGR_PLLMUL_X6_MASK:		local_f32TempFrequency *= 6;	break;
					case RCC_CFGR_PLLMUL_X7_MASK:		local_f32TempFrequency *= 7;	break;
					case RCC_CFGR_PLLMUL_X8_MASK:		local_f32TempFrequency *= 8;	break;
					case RCC_CFGR_PLLMUL_X9_MASK:		local_f32TempFrequency *= 9;	break;
					case RCC_CFGR_PLLMUL_X10_MASK:		local_f32TempFrequency *= 10;	break;
					case RCC_CFGR_PLLMUL_X11_MASK:		local_f32TempFrequency *= 11;	break;
					case RCC_CFGR_PLLMUL_X12_MASK:		local_f32TempFrequency *= 12;	break;
					case RCC_CFGR_PLLMUL_X13_MASK:		local_f32TempFrequency *= 13;	break;
					case RCC_CFGR_PLLMUL_X14_MASK:		local_f32TempFrequency *= 14;	break;
					case RCC_CFGR_PLLMUL_X15_MASK:		local_f32TempFrequency *= 15;	break;
					case RCC_CFGR_PLLMUL_X16_MASK:		local_f32TempFrequency *= 16;	break;
					case RCC_CFGR_PLLMUL_X16_2_MASK:	local_f32TempFrequency *= 16;	break;
					default:
						local_u8ErrorStatus = STATUS_NOT_OK; 
						break;
				}
				break;
			default:	
				local_u8ErrorStatus = STATUS_NOT_OK; 
				break;
		}
		/* Get AHB prescaler */
		RCC_u8Get_AHB_Prescaler(&local_u32TempMask);
		switch(local_u32TempMask)
		{
			case RCC_CFGR_HPRE_SYSCLK_NO_DIVISION_MASK:	local_f32TempFrequency /= 1;	break;
			case RCC_CFGR_HPRE_SYSCLK_BY_2_MASK:        local_f32TempFrequency /= 2;	break;
			case RCC_CFGR_HPRE_SYSCLK_BY_4_MASK:        local_f32TempFrequency /= 4;	break;
			case RCC_CFGR_HPRE_SYSCLK_BY_8_MASK:        local_f32TempFrequency /= 8;	break;
			case RCC_CFGR_HPRE_SYSCLK_BY_16_MASK:       local_f32TempFrequency /= 16;	break;
			case RCC_CFGR_HPRE_SYSCLK_BY_64_MASK:       local_f32TempFrequency /= 64;	break;
			case RCC_CFGR_HPRE_SYSCLK_BY_128_MASK:      local_f32TempFrequency /= 128;	break;
			case RCC_CFGR_HPRE_SYSCLK_BY_256_MASK:      local_f32TempFrequency /= 256;	break;
			case RCC_CFGR_HPRE_SYSCLK_BY_512_MASK:      local_f32TempFrequency /= 512;	break;
			default:
				local_u8ErrorStatus = STATUS_NOT_OK; 
				break;
		}
		*Copy_pf32Frequncy = local_f32TempFrequency;
	}
	else
	{
		local_u8ErrorStatus = STATUS_NULLPOINTER;
	}
	
	return local_u8ErrorStatus;
}

extern STD_STATUS RCC_u8Get_APB1_ClkFrequncyMHZ(f32 *Copy_pf32Frequncy)
{
	STD_STATUS local_u8ErrorStatus = STATUS_OK;
	f32 local_f32TempFrequency = 0;
	u32 local_u32TempMask = 0;
	
	if(Copy_pf32Frequncy)
	{
		RCC_u8Get_AHB_ClkFrequncyMHZ(&local_f32TempFrequency);
		RCC_u8Get_APB1_Prescaler(&local_u32TempMask);
		
		switch(local_u32TempMask)
		{
			case RCC_CFGR_PPRE1_HCLK_NO_DIVISION_MASK:	local_f32TempFrequency /= 1;	break;
			case RCC_CFGR_PPRE1_HCLK_BY_2_MASK:	        local_f32TempFrequency /= 2;	break;
			case RCC_CFGR_PPRE1_HCLK_BY_4_MASK:         local_f32TempFrequency /= 4;	break;
			case RCC_CFGR_PPRE1_HCLK_BY_8_MASK:         local_f32TempFrequency /= 8;	break;
			case RCC_CFGR_PPRE1_HCLK_BY_16_MASK:        local_f32TempFrequency /= 16;	break;
			default:
				local_u8ErrorStatus = STATUS_NOT_OK; 
				break;
		}
		*Copy_pf32Frequncy = local_f32TempFrequency;
	}
	else
	{
		local_u8ErrorStatus = STATUS_NULLPOINTER;
	}
	
	return local_u8ErrorStatus;
}

extern STD_STATUS RCC_u8Get_APB2_ClkFrequncyMHZ(f32 *Copy_pf32Frequncy)
{
	STD_STATUS local_u8ErrorStatus = STATUS_OK;
	f32 local_f32TempFrequency = 0;
	u32 local_u32TempMask = 0;
	
	if(Copy_pf32Frequncy)
	{
		RCC_u8Get_AHB_ClkFrequncyMHZ(&local_f32TempFrequency);
		RCC_u8Get_APB2_Prescaler(&local_u32TempMask);
		
		switch(local_u32TempMask)
		{
			case RCC_CFGR_PPRE2_HCLK_NO_DIVISION_MASK:	local_f32TempFrequency /= 1;	break;
			case RCC_CFGR_PPRE2_HCLK_BY_2_MASK:	        local_f32TempFrequency /= 2;	break;
			case RCC_CFGR_PPRE2_HCLK_BY_4_MASK:         local_f32TempFrequency /= 4;	break;
			case RCC_CFGR_PPRE2_HCLK_BY_8_MASK:         local_f32TempFrequency /= 8;	break;
			case RCC_CFGR_PPRE2_HCLK_BY_16_MASK:        local_f32TempFrequency /= 16;	break;
			default:
				local_u8ErrorStatus = STATUS_NOT_OK; 
				break;
		}
		*Copy_pf32Frequncy = local_f32TempFrequency;
	}
	else
	{
		local_u8ErrorStatus = STATUS_NULLPOINTER;
	}
	
	return local_u8ErrorStatus;
}



