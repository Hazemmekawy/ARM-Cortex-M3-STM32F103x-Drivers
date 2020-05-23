#ifndef RCC_H
#define RCC_H
	
#include "STD_TYPES.h"

/*Type definitions*/

#define 	BUS		u8
#define 	AHB		0
#define 	APB1	1
#define		APB2	2

/*RCC_CR_MASKS*/
#define 	RCC_CR_HSION_MASK						0x00000001
#define 	RCC_CR_HSIRDY_MASK						0x00000002

#define		RCC_CR_HSITRIM_0_VALUE_MASK 	 		0x00000000
#define		RCC_CR_HSITRIM_1_VALUE_MASK 	 		0x00000008
#define		RCC_CR_HSITRIM_2_VALUE_MASK 	 		0x00000010
#define		RCC_CR_HSITRIM_3_VALUE_MASK 	 		0x00000018
#define		RCC_CR_HSITRIM_4_VALUE_MASK 	 		0x00000020
#define		RCC_CR_HSITRIM_5_VALUE_MASK 	 		0x00000028
#define		RCC_CR_HSITRIM_6_VALUE_MASK 	 		0x00000030
#define		RCC_CR_HSITRIM_7_VALUE_MASK 	 		0x00000038
#define		RCC_CR_HSITRIM_8_VALUE_MASK 	 		0x00000040
#define		RCC_CR_HSITRIM_9_VALUE_MASK 	 		0x00000048
#define		RCC_CR_HSITRIM_10_VALUE_MASK 	 		0x00000050
#define		RCC_CR_HSITRIM_11_VALUE_MASK 	 		0x00000058
#define		RCC_CR_HSITRIM_12_VALUE_MASK 	 		0x00000060
#define		RCC_CR_HSITRIM_13_VALUE_MASK 	 		0x00000068
#define		RCC_CR_HSITRIM_14_VALUE_MASK 	 		0x00000070
#define		RCC_CR_HSITRIM_15_VALUE_MASK 	 		0x00000078
#define 	RCC_CR_HSITRIM_DEFAULT_VALUE_MASK 		0x00000080
#define		RCC_CR_HSITRIM_16_VALUE_MASK 	 		0x00000080
#define		RCC_CR_HSITRIM_17_VALUE_MASK 	 		0x00000088
#define		RCC_CR_HSITRIM_18_VALUE_MASK 	 		0x00000090
#define		RCC_CR_HSITRIM_19_VALUE_MASK 	 		0x00000098
#define		RCC_CR_HSITRIM_20_VALUE_MASK 	 		0x000000A0
#define		RCC_CR_HSITRIM_21_VALUE_MASK 	 		0x000000A8
#define		RCC_CR_HSITRIM_22_VALUE_MASK 	 		0x000000B0
#define		RCC_CR_HSITRIM_23_VALUE_MASK 	 		0x000000B8
#define		RCC_CR_HSITRIM_24_VALUE_MASK 	 		0x000000C0
#define		RCC_CR_HSITRIM_25_VALUE_MASK 	 		0x000000C8
#define		RCC_CR_HSITRIM_26_VALUE_MASK 	 		0x000000D0
#define		RCC_CR_HSITRIM_27_VALUE_MASK 	 		0x000000D8
#define		RCC_CR_HSITRIM_28_VALUE_MASK 	 		0x000000E0
#define		RCC_CR_HSITRIM_29_VALUE_MASK 	 		0x000000E8
#define		RCC_CR_HSITRIM_30_VALUE_MASK 	 		0x000000F0
#define		RCC_CR_HSITRIM_31_VALUE_MASK 	 		0x000000F8
#define 	RCC_CR_HSITRIM_CLR_MASK					0xFFFFFF07

#define 	RCC_CR_HSICAL_MASK						0x0000FF00
	
#define 	RCC_CR_HSEON_MASK						0x00010000	
#define 	RCC_CR_HSERDY_MASK						0x00020000			
#define 	RCC_CR_HSEBYP_MASK						0x00040000			
#define 	RCC_CR_CSSON_MASK						0x00080000			
#define 	RCC_CR_PLLON_MASK						0x01000000		
#define 	RCC_CR_PLLRDY_MASK						0x02000000		


/*RCC_CFGR_MASKS*/
#define 	RCC_CFGR_SW_HSI_MASK					0x00000000
#define 	RCC_CFGR_SW_HSE_MASK					0x00000001	
#define 	RCC_CFGR_SW_PLL_MASK					0x00000002					
#define 	RCC_CFGR_SW_CLR_MASK					0xFFFFFFFC

#define		RCC_CFGR_SWS_HSI_MASK					0x00000000
#define		RCC_CFGR_SWS_HSE_MASK                   0x00000004
#define		RCC_CFGR_SWS_PLL_MASK                   0x00000008
#define 	RCC_CFGR_SWS_MASK						0x0000000C		

#define 	RCC_CFGR_HPRE_SYSCLK_NO_DIVISION_MASK	0x00000000
#define 	RCC_CFGR_HPRE_SYSCLK_BY_2_MASK			0x00000080
#define 	RCC_CFGR_HPRE_SYSCLK_BY_4_MASK			0x00000090
#define 	RCC_CFGR_HPRE_SYSCLK_BY_8_MASK			0x000000A0
#define 	RCC_CFGR_HPRE_SYSCLK_BY_16_MASK			0x000000B0
#define 	RCC_CFGR_HPRE_SYSCLK_BY_64_MASK			0x000000C0
#define 	RCC_CFGR_HPRE_SYSCLK_BY_128_MASK		0x000000D0
#define 	RCC_CFGR_HPRE_SYSCLK_BY_256_MASK		0x000000E0	
#define 	RCC_CFGR_HPRE_SYSCLK_BY_512_MASK		0x000000F0	
#define 	RCC_CFGR_HPRE_CLR_MASK					0xFFFFFF0F
	
#define 	RCC_CFGR_PPRE1_HCLK_NO_DIVISION_MASK	0x00000000
#define 	RCC_CFGR_PPRE1_HCLK_BY_2_MASK			0x00000400
#define 	RCC_CFGR_PPRE1_HCLK_BY_4_MASK			0x00000500
#define 	RCC_CFGR_PPRE1_HCLK_BY_8_MASK			0x00000600
#define 	RCC_CFGR_PPRE1_HCLK_BY_16_MASK			0x00000700
#define 	RCC_CFGR_PPRE1_CLR_MASK					0xFFFFF8FF		
	
#define 	RCC_CFGR_PPRE2_HCLK_NO_DIVISION_MASK	0x00000000
#define 	RCC_CFGR_PPRE2_HCLK_BY_2_MASK			0x00002000
#define 	RCC_CFGR_PPRE2_HCLK_BY_4_MASK			0x00002800
#define 	RCC_CFGR_PPRE2_HCLK_BY_8_MASK			0x00003000
#define 	RCC_CFGR_PPRE2_HCLK_BY_16_MASK			0x00003800
#define 	RCC_CFGR_PPRE2_CLR_MASK					0xFFFFC7FF

#define 	RCC_CFGR_ADCPRE_PCLK2_BY_2_MASK			0x00000000
#define 	RCC_CFGR_ADCPRE_PCLK2_BY_4_MASK			0x00004000
#define 	RCC_CFGR_ADCPRE_PCLK2_BY_6_MASK			0x00008000
#define 	RCC_CFGR_ADCPRE_PCLK2_BY_8_MASK			0x0000C000
#define 	RCC_CFGR_ADCPRE_CLR_MASK				0xFFFF3FFF
	
#define 	RCC_CFGR_PLLSRC_HSI_BY_2_MASK			0x00000000
#define 	RCC_CFGR_PLLSRC_HSE_MASK				0x00010000
#define 	RCC_CFGR_PLLSRC_CLR_MASK				0xFFFEFFFF

#define 	RCC_CFGR_PLLXTPRE_MASK					0x00020000

#define 	RCC_CFGR_PLLMUL_X2_MASK					0x00000000
#define 	RCC_CFGR_PLLMUL_X3_MASK					0x00040000
#define 	RCC_CFGR_PLLMUL_X4_MASK					0x00080000
#define 	RCC_CFGR_PLLMUL_X5_MASK					0x000C0000
#define 	RCC_CFGR_PLLMUL_X6_MASK					0x00100000
#define 	RCC_CFGR_PLLMUL_X7_MASK					0x00140000
#define 	RCC_CFGR_PLLMUL_X8_MASK					0x00180000
#define 	RCC_CFGR_PLLMUL_X9_MASK					0x001C0000
#define 	RCC_CFGR_PLLMUL_X10_MASK				0x00200000
#define 	RCC_CFGR_PLLMUL_X11_MASK				0x00240000
#define 	RCC_CFGR_PLLMUL_X12_MASK				0x00280000
#define 	RCC_CFGR_PLLMUL_X13_MASK				0x002C0000
#define 	RCC_CFGR_PLLMUL_X14_MASK				0x00300000
#define 	RCC_CFGR_PLLMUL_X15_MASK				0x00340000
#define 	RCC_CFGR_PLLMUL_X16_MASK				0x00380000
#define 	RCC_CFGR_PLLMUL_X16_2_MASK				0x003C0000				
#define 	RCC_CFGR_PLLMUL_CLR_MASK				0xFFC3FFFF

#define 	RCC_CFGR_USBPRE_MASK					0x00400000

#define 	RCC_CFGR_MCO_NO_CLK_MASK				0x00000000
#define 	RCC_CFGR_MCO_SYSCLK_MASK				0x04000000
#define 	RCC_CFGR_MCO_HSI_MASK					0x05000000
#define 	RCC_CFGR_MCO_HSE_MASK					0x06000000
#define 	RCC_CFGR_MCO_PLL_BY_2_MASK				0x07000000
#define 	RCC_CFGR_MCO_CLR_MASK					0xF8FFFFFF

/*RCC_AHBENR*/
#define 	RCC_AHBENR_DMA1EN_MASK					0x00000001
#define 	RCC_AHBENR_DMA2EN_MASK					0x00000002
#define 	RCC_AHBENR_SRAMEN_MASK					0x00000004
#define 	RCC_AHBENR_FLITFEN_MASK					0x00000010
#define 	RCC_AHBENR_CRCEN_MASK					0x00000040
#define 	RCC_AHBENR_FSMCEN_MASK					0x00000100
#define 	RCC_AHBENR_SDIOEN_MASK					0x00000400


/*RCC_APB2ENR*/
#define 	RCC_APB2ENR_AFIOEN_MASK					0x00000001
#define 	RCC_APB2ENR_IOPAEN_MASK					0x00000004
#define 	RCC_APB2ENR_IOPBEN_MASK					0x00000008
#define 	RCC_APB2ENR_IOPCEN_MASK					0x00000010
#define 	RCC_APB2ENR_IOPDEN_MASK					0x00000020
#define 	RCC_APB2ENR_IOPEEN_MASK					0x00000040
#define 	RCC_APB2ENR_IOPFEN_MASK					0x00000080
#define 	RCC_APB2ENR_IOPGEN_MASK					0x00000100
#define 	RCC_APB2ENR_ADC1EN_MASK					0x00000200
#define 	RCC_APB2ENR_ADC2EN_MASK					0x00000400
#define 	RCC_APB2ENR_TIM1EN_MASK					0x00000800
#define 	RCC_APB2ENR_SPI1EN_MASK					0x00001000
#define 	RCC_APB2ENR_TIM8EN_MASK					0x00002000
#define 	RCC_APB2ENR_USART1EN_MASK				0x00004000
#define 	RCC_APB2ENR_ADC3EN_MASK					0x00008000

/*RCC_APB1ENR*/
#define 	RCC_APB1ENR_TIM2EN_MASK					0x00000001			
#define 	RCC_APB1ENR_TIM3EN_MASK					0x00000002
#define 	RCC_APB1ENR_TIM4EN_MASK					0x00000004
#define 	RCC_APB1ENR_TIM5EN_MASK					0x00000008
#define 	RCC_APB1ENR_TIM6EN_MASK					0x00000010
#define 	RCC_APB1ENR_TIM7EN_MASK					0x00000020
#define 	RCC_APB1ENR_TIM12EN_MASK				0x00000040
#define 	RCC_APB1ENR_TIM13EN_MASK				0x00000080
#define 	RCC_APB1ENR_TIM14EN_MASK				0x00000100
#define 	RCC_APB1ENR_WWDGEN_MASK					0x00000800
#define 	RCC_APB1ENR_SPI2EN_MASK					0x00004000
#define 	RCC_APB1ENR_SPI3EN_MASK					0x00008000
#define 	RCC_APB1ENR_USART2EN_MASK				0x00020000
#define 	RCC_APB1ENR_USART3EN_MASK				0x00040000
#define 	RCC_APB1ENR_USART4EN_MASK				0x00080000
#define 	RCC_APB1ENR_USART5EN_MASK				0x00100000
#define 	RCC_APB1ENR_I2C1EN_MASK					0x00200000
#define 	RCC_APB1ENR_I2C2EN_MASK					0x00400000
#define 	RCC_APB1ENR_USBEN_MASK					0x00800000
#define 	RCC_APB1ENR_CANEN_MASK					0x02000000
#define 	RCC_APB1ENR_BKPEN_MASK					0x08000000
#define 	RCC_APB1ENR_PWREN_MASK					0x10000000
#define 	RCC_APB1ENR_DACEN_MASK					0x20000000



/* RCC validation macros */
#define 	IS_RCC_CLK_MASK_VALID(CLK) 					(((CLK) == RCC_CR_HSION_MASK) || \
														((CLK) == RCC_CR_HSEON_MASK)  || \
														((CLK) == RCC_CR_PLLON_MASK))

#define 	IS_RCC_SYS_CLK_MASK_VALID(SYS_CLK) 			(((SYS_CLK) == RCC_CFGR_SW_HSI_MASK) || \
														((SYS_CLK) == RCC_CFGR_SW_HSE_MASK)  || \
														((SYS_CLK) == RCC_CFGR_SW_PLL_MASK))

#define 	IS_RCC_PLL_SOURCE_VALID(PLL_SOURCE)			(((PLL_SOURCE) == RCC_CFGR_PLLSRC_HSI_BY_2_MASK) || \
														((PLL_SOURCE) == RCC_CFGR_PLLSRC_HSE_MASK))

#define 	IS_RCC_PLL_MULTIPLIER_VALID(PLL_MULTIPLIER) ((PLL_MULTIPLIER == RCC_CFGR_PLLMUL_X2_MASK)  || \
														(PLL_MULTIPLIER == RCC_CFGR_PLLMUL_X3_MASK)  || \
														(PLL_MULTIPLIER == RCC_CFGR_PLLMUL_X4_MASK)  || \
														(PLL_MULTIPLIER == RCC_CFGR_PLLMUL_X5_MASK)  || \
														(PLL_MULTIPLIER == RCC_CFGR_PLLMUL_X6_MASK)  || \
														(PLL_MULTIPLIER == RCC_CFGR_PLLMUL_X7_MASK)  || \
														(PLL_MULTIPLIER == RCC_CFGR_PLLMUL_X8_MASK)  || \
														(PLL_MULTIPLIER == RCC_CFGR_PLLMUL_X9_MASK)  || \
														(PLL_MULTIPLIER == RCC_CFGR_PLLMUL_X10_MASK) || \
														(PLL_MULTIPLIER == RCC_CFGR_PLLMUL_X11_MASK) || \
														(PLL_MULTIPLIER == RCC_CFGR_PLLMUL_X12_MASK) || \
														(PLL_MULTIPLIER == RCC_CFGR_PLLMUL_X13_MASK) || \
														(PLL_MULTIPLIER == RCC_CFGR_PLLMUL_X14_MASK) || \
														(PLL_MULTIPLIER == RCC_CFGR_PLLMUL_X15_MASK) || \
														(PLL_MULTIPLIER == RCC_CFGR_PLLMUL_X16_MASK)) 

#define 	IS_RCC_MCO_SOURCE_VALID(MCO_SOURCE)			(((MCO_SOURCE) == RCC_CFGR_MCO_NO_CLK_MASK) || \
														((MCO_SOURCE) == RCC_CFGR_MCO_SYSCLK_MASK)  || \
														((MCO_SOURCE) == RCC_CFGR_MCO_HSI_MASK)  	|| \
														((MCO_SOURCE) == RCC_CFGR_MCO_HSE_MASK)  	|| \
														((MCO_SOURCE) == RCC_CFGR_MCO_PLL_BY_2_MASK))

#define 	IS_RCC_AHB_PRESCALER_VALID(AHB_PRESCALER)	(((AHB_PRESCALER) == RCC_CFGR_HPRE_SYSCLK_NO_DIVISION_MASK) || \
                                                        ((AHB_PRESCALER) == RCC_CFGR_HPRE_SYSCLK_BY_2_MASK)  	|| \
                                                        ((AHB_PRESCALER) == RCC_CFGR_HPRE_SYSCLK_BY_4_MASK)  	|| \
                                                        ((AHB_PRESCALER) == RCC_CFGR_HPRE_SYSCLK_BY_8_MASK)  	|| \
														((AHB_PRESCALER) == RCC_CFGR_HPRE_SYSCLK_BY_16_MASK) 	|| \
                                                        ((AHB_PRESCALER) == RCC_CFGR_HPRE_SYSCLK_BY_64_MASK)  	|| \
                                                        ((AHB_PRESCALER) == RCC_CFGR_HPRE_SYSCLK_BY_128_MASK)  	|| \
														((AHB_PRESCALER) == RCC_CFGR_HPRE_SYSCLK_BY_256_MASK)  	|| \
                                                        ((AHB_PRESCALER) == RCC_CFGR_HPRE_SYSCLK_BY_512_MASK))

#define 	IS_RCC_APB1_PRESCALER_VALID(APB1_PRESCALER)	(((APB1_PRESCALER) == RCC_CFGR_PPRE1_HCLK_NO_DIVISION_MASK) || \
                                                        ((APB1_PRESCALER) == RCC_CFGR_PPRE1_HCLK_BY_2_MASK)  	|| \
                                                        ((APB1_PRESCALER) == RCC_CFGR_PPRE1_HCLK_BY_4_MASK)  	|| \
                                                        ((APB1_PRESCALER) == RCC_CFGR_PPRE1_HCLK_BY_8_MASK)  	|| \
														((APB1_PRESCALER) == RCC_CFGR_PPRE1_HCLK_BY_16_MASK))

#define 	IS_RCC_APB2_PRESCALER_VALID(APB2_PRESCALER)	(((APB2_PRESCALER) == RCC_CFGR_PPRE2_HCLK_NO_DIVISION_MASK) || \
                                                        ((APB2_PRESCALER) == RCC_CFGR_PPRE2_HCLK_BY_2_MASK)  	|| \
                                                        ((APB2_PRESCALER) == RCC_CFGR_PPRE2_HCLK_BY_4_MASK)  	|| \
                                                        ((APB2_PRESCALER) == RCC_CFGR_PPRE2_HCLK_BY_8_MASK)  	|| \
														((APB2_PRESCALER) == RCC_CFGR_PPRE2_HCLK_BY_16_MASK))

#define 	IS_RCC_ADC_PRESCALER_VALID(ADC_PRESCALER)	(((ADC_PRESCALER) == RCC_CFGR_ADCPRE_PCLK2_BY_2_MASK) 	|| \
                                                        ((ADC_PRESCALER) == RCC_CFGR_ADCPRE_PCLK2_BY_4_MASK)  	|| \
                                                        ((ADC_PRESCALER) == RCC_CFGR_ADCPRE_PCLK2_BY_6_MASK)  	|| \
														((ADC_PRESCALER) == RCC_CFGR_ADCPRE_PCLK2_BY_8_MASK))
														
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
extern STD_STATUS RCC_u8ControlClks(u32 Copy_u32ClkSelectionMask, STATE Copy_u8Status);


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
extern STD_STATUS RCC_u8SelectSysClk(u32 Copy_u32SysClkSelectionMask);


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
extern STD_STATUS RCC_u8ConfigurePLL(u32 Copy_u32PLLSourceMask, u32 Copy_u32MultiplierValueMask);


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
extern STD_STATUS RCC_u8ConfigureMCO(u32 Copy_u32MCOSelectionMask);


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
extern STD_STATUS RCC_u8Configure_AHB_Prescaler(u32 Copy_u32AHBPrescalerSelectionMask);


/****************************************************************************************************************
*                                                                                                               *
*	Description:                                                                                                *
*				This function shall configure the prescaler of APB1 bus.                                        *
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
extern STD_STATUS RCC_u8Configure_APB1_Prescaler(u32 Copy_u32APB1PrescalerSelectionMask);


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
extern STD_STATUS RCC_u8Configure_APB2_Prescaler(u32 Copy_u32APB2PrescalerSelectionMask);


/****************************************************************************************************************
*                                                                                                               *
*	Description:                                                                                                *
*				This function shall configure the prescaler of ADC.                                        		*
*				                                                                                                *
*	Input Parameters:                                                                                           *
*				u32 RCC_u8Configure_ADC_Prescaler: Takes the mask of the selected ADC prescaler.          		*
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
extern STD_STATUS RCC_u8Configure_ADC_Prescaler(u32 Copy_u32ADCPrescalerSelectionMask);



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
extern STD_STATUS RCC_u8ControlPeripherals(BUS Copy_u8Bus, u32 Copy_u32PeripheralMask, STATE Copy_u8Status);


extern STD_STATUS RCC_u8GetSysClk(u32 *Copy_pu32SysClkMaskReturn);
extern STD_STATUS RCC_u8Get_AHB_Prescaler(u32 *Copy_pu32PrescalerMaskReturn);
extern STD_STATUS RCC_u8Get_APB1_Prescaler(u32 *Copy_pu32PrescalerMaskReturn);
extern STD_STATUS RCC_u8Get_APB2_Prescaler(u32 *Copy_pu32PrescalerMaskReturn);
extern STD_STATUS RCC_u8Get_PLL_Multiplier(u32 *Copy_pu32MultiplierMaskReturn);
extern STD_STATUS RCC_u8Get_PLL_Source(u32 *Copy_pu32SourceMaskReturn);

extern STD_STATUS RCC_u8Get_AHB_ClkFrequncyMHZ(f32 *Copy_pf32Frequncy);
extern STD_STATUS RCC_u8Get_APB1_ClkFrequncyMHZ(f32 *Copy_pf32Frequncy);
extern STD_STATUS RCC_u8Get_APB2_ClkFrequncyMHZ(f32 *Copy_pf32Frequncy);


#endif /* RCC_H */

