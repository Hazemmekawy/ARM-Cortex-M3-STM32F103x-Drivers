#include "STD_TYPES.h"

#include "RCC.h"
#include "GPIO.h"
#include "NVIC.h"
#include "DMA.h"

//#include "USART.h"

#include "hUSART.h"

typedef struct
{
	GPIO_Init_t GPIO_TxMap;
	GPIO_Init_t GPIO_RxMap;
	void *USART_BaseRegister;
	void *GPIO_BaseRegister_Tx;
	void *GPIO_BaseRegister_Rx;
	u32 RCC_PeripheralEnable;
	u8 interruptID;
	u8 DMA_TxChannel;
	u8 DMA_RxChannel;
	BUS Bus;
	
}hUSART_t;

const static hUSART_t hUSART[NUMBER_OF_USARTs] =
{
	{
		.USART_BaseRegister			=	USART1_BASE_REG,
		.GPIO_BaseRegister_Tx 		= 	GPIOA,
		.GPIO_TxMap.GPIO_Pin		=	GPIO_PIN_9,
	    .GPIO_TxMap.GPIO_Speed		=	GPIO_SPEED_10MHZ_MASK,
		.GPIO_TxMap.GPIO_Mode		=	GPIO_MODE_AF_PP_MASK,
		.GPIO_BaseRegister_Rx		= 	GPIOA,
		.GPIO_RxMap.GPIO_Pin	    =	GPIO_PIN_10,
		.GPIO_RxMap.GPIO_Speed	    =	GPIO_SPEED_INPUT_MASK,
		.GPIO_RxMap.GPIO_Mode	    =	GPIO_MODE_IN_PU_MASK,
		.RCC_PeripheralEnable		=	RCC_APB2ENR_USART1EN_MASK,
		.DMA_TxChannel				=	DMA_USART1_TX,
		.DMA_RxChannel				=	DMA_USART1_RX,
		.interruptID   				=	NVIC_EXTINT_37,
		.Bus						= 	APB2
	},
	{
		.USART_BaseRegister			=	USART2_BASE_REG,
		.GPIO_BaseRegister_Tx 		= 	GPIOA,
		.GPIO_TxMap.GPIO_Pin		=	GPIO_PIN_2,
	    .GPIO_TxMap.GPIO_Speed		=	GPIO_SPEED_10MHZ_MASK,
		.GPIO_TxMap.GPIO_Mode		=	GPIO_MODE_AF_PP_MASK,
		.GPIO_BaseRegister_Rx		= 	GPIOA,
		.GPIO_RxMap.GPIO_Pin	    =	GPIO_PIN_3,
		.GPIO_RxMap.GPIO_Speed	    =	GPIO_SPEED_INPUT_MASK,
		.GPIO_RxMap.GPIO_Mode	    =	GPIO_MODE_IN_PU_MASK,
		.RCC_PeripheralEnable		=	RCC_APB1ENR_USART2EN_MASK,
		.DMA_TxChannel				=	DMA_USART2_TX,
		.DMA_RxChannel				=	DMA_USART2_RX,
		.interruptID   				=	NVIC_EXTINT_38,
		.Bus						= 	APB1
	},
	{
		.USART_BaseRegister			=	USART3_BASE_REG,
		.GPIO_BaseRegister_Tx 		= 	GPIOB,
		.GPIO_TxMap.GPIO_Pin		=	GPIO_PIN_10,
	    .GPIO_TxMap.GPIO_Speed		=	GPIO_SPEED_10MHZ_MASK,
		.GPIO_TxMap.GPIO_Mode		=	GPIO_MODE_AF_PP_MASK,
		.GPIO_BaseRegister_Rx		= 	GPIOB,
		.GPIO_RxMap.GPIO_Pin	    =	GPIO_PIN_11,
		.GPIO_RxMap.GPIO_Speed	    =	GPIO_SPEED_INPUT_MASK,
		.GPIO_RxMap.GPIO_Mode	    =	GPIO_MODE_IN_PU_MASK,
		.RCC_PeripheralEnable		=	RCC_APB1ENR_USART3EN_MASK,
		.DMA_TxChannel				=	DMA_USART3_TX,
		.DMA_RxChannel				=	DMA_USART3_RX,
		.interruptID   				=	NVIC_EXTINT_39,
		.Bus						= 	APB1
	}
};

const static DMAChannel_cfgStruct_t	USART_Tx_DMAChannel_cfgStruct[NUMBER_OF_USARTs] = 
{
	{
		.MEM2MEM_mode			=	USART1_TX_DMA_CHANNEL_MEM2MEM,			
		.priorityLevel			= 	USART1_TX_DMA_CHANNEL_PRI_LEVEL,	    
		.memorySize				=	USART1_TX_DMA_CHANNEL_MEM_SIZE,			
	    .peripheralSize			=	USART1_TX_DMA_CHANNEL_PERIPH_SIZE,		
		.memoryIncrement		=	USART1_TX_DMA_CHANNEL_MEM_INC,	        
		.peripheralIncrement	= 	USART1_TX_DMA_CHANNEL_PERIPH_INC,         
		.circularMode			=	USART1_TX_DMA_CHANNEL_CIRC,		        
		.dataDirection			=	USART1_TX_DMA_CHANNEL_DATA_DIRECTION,	
		.halfTransferMode		=	USART1_TX_DMA_CHANNEL_HALF_TRANSFER_MODE
	},
	{
		.MEM2MEM_mode			=	USART2_TX_DMA_CHANNEL_MEM2MEM,			
		.priorityLevel			= 	USART2_TX_DMA_CHANNEL_PRI_LEVEL,	    
		.memorySize				=	USART2_TX_DMA_CHANNEL_MEM_SIZE,			
	    .peripheralSize			=	USART2_TX_DMA_CHANNEL_PERIPH_SIZE,		
		.memoryIncrement		=	USART2_TX_DMA_CHANNEL_MEM_INC,	        
		.peripheralIncrement	= 	USART2_TX_DMA_CHANNEL_PERIPH_INC,         
		.circularMode			=	USART2_TX_DMA_CHANNEL_CIRC,		        
		.dataDirection			=	USART2_TX_DMA_CHANNEL_DATA_DIRECTION,	
		.halfTransferMode		=	USART2_TX_DMA_CHANNEL_HALF_TRANSFER_MODE
	},
	{
		.MEM2MEM_mode			=	USART3_TX_DMA_CHANNEL_MEM2MEM,			
		.priorityLevel			= 	USART3_TX_DMA_CHANNEL_PRI_LEVEL,	    
		.memorySize				=	USART3_TX_DMA_CHANNEL_MEM_SIZE,			
	    .peripheralSize			=	USART3_TX_DMA_CHANNEL_PERIPH_SIZE,		
		.memoryIncrement		=	USART3_TX_DMA_CHANNEL_MEM_INC,	        
		.peripheralIncrement	= 	USART3_TX_DMA_CHANNEL_PERIPH_INC,         
		.circularMode			=	USART3_TX_DMA_CHANNEL_CIRC,		        
		.dataDirection			=	USART3_TX_DMA_CHANNEL_DATA_DIRECTION,	
		.halfTransferMode		=	USART3_TX_DMA_CHANNEL_HALF_TRANSFER_MODE
	}
};

const static DMAChannel_cfgStruct_t	USART_Rx_DMAChannel_cfgStruct[NUMBER_OF_USARTs] = 
{
	{
		.MEM2MEM_mode			=	USART1_RX_DMA_CHANNEL_MEM2MEM,			
		.priorityLevel			= 	USART1_RX_DMA_CHANNEL_PRI_LEVEL,	    
		.memorySize				=	USART1_RX_DMA_CHANNEL_MEM_SIZE,			
	    .peripheralSize			=	USART1_RX_DMA_CHANNEL_PERIPH_SIZE,		
		.memoryIncrement		=	USART1_RX_DMA_CHANNEL_MEM_INC,	        
		.peripheralIncrement	= 	USART1_RX_DMA_CHANNEL_PERIPH_INC,         
		.circularMode			=	USART1_RX_DMA_CHANNEL_CIRC,		        
		.dataDirection			=	USART1_RX_DMA_CHANNEL_DATA_DIRECTION,	
		.halfTransferMode		=	USART1_RX_DMA_CHANNEL_HALF_TRANSFER_MODE
	},
	{
		.MEM2MEM_mode			=	USART2_RX_DMA_CHANNEL_MEM2MEM,			
		.priorityLevel			= 	USART2_RX_DMA_CHANNEL_PRI_LEVEL,	    
		.memorySize				=	USART2_RX_DMA_CHANNEL_MEM_SIZE,			
	    .peripheralSize			=	USART2_RX_DMA_CHANNEL_PERIPH_SIZE,		
		.memoryIncrement		=	USART2_RX_DMA_CHANNEL_MEM_INC,	        
		.peripheralIncrement	= 	USART2_RX_DMA_CHANNEL_PERIPH_INC,         
		.circularMode			=	USART2_RX_DMA_CHANNEL_CIRC,		        
		.dataDirection			=	USART2_RX_DMA_CHANNEL_DATA_DIRECTION,	
		.halfTransferMode		=	USART2_RX_DMA_CHANNEL_HALF_TRANSFER_MODE
	},
	{
		.MEM2MEM_mode			=	USART3_RX_DMA_CHANNEL_MEM2MEM,			
		.priorityLevel			= 	USART3_RX_DMA_CHANNEL_PRI_LEVEL,	    
		.memorySize				=	USART3_RX_DMA_CHANNEL_MEM_SIZE,			
	    .peripheralSize			=	USART3_RX_DMA_CHANNEL_PERIPH_SIZE,		
		.memoryIncrement		=	USART3_RX_DMA_CHANNEL_MEM_INC,	        
		.peripheralIncrement	= 	USART3_RX_DMA_CHANNEL_PERIPH_INC,         
		.circularMode			=	USART3_RX_DMA_CHANNEL_CIRC,		        
		.dataDirection			=	USART3_RX_DMA_CHANNEL_DATA_DIRECTION,	
		.halfTransferMode		=	USART3_RX_DMA_CHANNEL_HALF_TRANSFER_MODE
	}
};

static u8 USART_Tx_DMAChannelEnable[NUMBER_OF_USARTs] = {USART1_TX_DMA_CHANNEL_ENABLE, USART2_TX_DMA_CHANNEL_ENABLE, USART3_TX_DMA_CHANNEL_ENABLE};
static u8 USART_Rx_DMAChannelEnable[NUMBER_OF_USARTs] = {USART1_RX_DMA_CHANNEL_ENABLE, USART2_RX_DMA_CHANNEL_ENABLE, USART3_RX_DMA_CHANNEL_ENABLE};

extern STD_STATUS hUSART_u8Init(u8 USARTx, u8 Copy_u8CfgOption)
{
	STD_STATUS local_u8ErrorStatus = STATUS_OK;
	f32 local_u32Clk_MHZ = 0;
	
	if(IS_USART_VALID(USARTx) && IS_CFG_OPTION_VALID(Copy_u8CfgOption))
	{
		switch(hUSART[USARTx].Bus)
		{
			case APB1:
				local_u8ErrorStatus = RCC_u8Get_APB1_ClkFrequncyMHZ(&local_u32Clk_MHZ);
				break;
				
			case APB2:
				local_u8ErrorStatus = RCC_u8Get_APB2_ClkFrequncyMHZ(&local_u32Clk_MHZ);
				break;
			
			default:
				local_u8ErrorStatus = STATUS_NOT_OK;
				break;
		}
		
		local_u8ErrorStatus = RCC_u8ControlPeripherals(hUSART[USARTx].Bus, hUSART[USARTx].RCC_PeripheralEnable, ON);
		local_u8ErrorStatus = GPIO_u8ConfigurePin(hUSART[USARTx].GPIO_BaseRegister_Tx, &hUSART[USARTx].GPIO_TxMap);
		local_u8ErrorStatus = GPIO_u8ConfigurePin(hUSART[USARTx].GPIO_BaseRegister_Rx, &hUSART[USARTx].GPIO_RxMap);
		
		if(Copy_u8CfgOption == CFG_DEFAULT)
		{
			local_u8ErrorStatus = USART_u8DefaultInit(USARTx, local_u32Clk_MHZ);
		}
		else if(Copy_u8CfgOption == CFG_DEFINED)
		{
			local_u8ErrorStatus = USART_u8Init(USARTx, local_u32Clk_MHZ);
		}
		
		
		local_u8ErrorStatus = NVIC_u8ClearPendingStatus(hUSART[USARTx].interruptID);
		local_u8ErrorStatus = NVIC_u8InterruptEnable(hUSART[USARTx].interruptID);
		
		
		/* if the DMA was enabled */
		if(USART_Tx_DMAChannelEnable[USARTx] == DMA_CHANNEL_ENABLED)
		{
			DMA_u8ChannelConfigure(hUSART[USARTx].DMA_TxChannel, &USART_Tx_DMAChannel_cfgStruct[USARTx]);
		}
		
		if(USART_Rx_DMAChannelEnable[USARTx] == DMA_CHANNEL_ENABLED)
		{
			DMA_u8ChannelConfigure(hUSART[USARTx].DMA_RxChannel, &USART_Rx_DMAChannel_cfgStruct[USARTx]);
		}
	}
	else
	{
		local_u8ErrorStatus = STATUS_NOT_OK;
	}

	return local_u8ErrorStatus;
}

extern STD_STATUS hUSART_u8EnableTxDMA(u8 USARTx)
{
	USART_Tx_DMAChannelEnable[USARTx] = DMA_CHANNEL_ENABLED;
	USART_u8EnableTxDMA(USARTx);
	return STATUS_OK;
}

extern STD_STATUS hUSART_u8DisableTxDMA(u8 USARTx)
{
	USART_Tx_DMAChannelEnable[USARTx] = DMA_CHANNEL_DISABLED;
	USART_u8DisableTxDMA(USARTx);
	return STATUS_OK;
}

extern STD_STATUS hUSART_u8EnableRxDMA(u8 USARTx)
{
	USART_Rx_DMAChannelEnable[USARTx] = DMA_CHANNEL_ENABLED;
	USART_u8EnableRxDMA(USARTx);
	return STATUS_OK;
}

extern STD_STATUS hUSART_u8DisableRxDMA(u8 USARTx)
{
	USART_Rx_DMAChannelEnable[USARTx] = DMA_CHANNEL_DISABLED;
	USART_u8DisableRxDMA(USARTx);
	return STATUS_OK;
}

extern STD_STATUS hUSART_u8ConfigureTxDMA(u8 USARTx, DMAChannel_cfgStruct_t *DMAChannel_cfgStruct)
{
	STD_STATUS local_u8ErrorStatus = STATUS_OK;
	if(DMAChannel_cfgStruct)
	{
		local_u8ErrorStatus = DMA_u8ChannelConfigure(hUSART[USARTx].DMA_TxChannel, DMAChannel_cfgStruct);
	}
	else
	{
		local_u8ErrorStatus = STATUS_NULLPOINTER;
	}
	return local_u8ErrorStatus;
}

extern STD_STATUS hUSART_u8ConfigureRxDMA(u8 USARTx, DMAChannel_cfgStruct_t *DMAChannel_cfgStruct)
{
	STD_STATUS local_u8ErrorStatus = STATUS_OK;
	if(DMAChannel_cfgStruct)
	{
		local_u8ErrorStatus = DMA_u8ChannelConfigure(hUSART[USARTx].DMA_RxChannel, DMAChannel_cfgStruct);
	}
	else
	{
		local_u8ErrorStatus = STATUS_NULLPOINTER;
	}
	return local_u8ErrorStatus;
}

extern STD_STATUS hUSART_u8Configure(u8 USARTx, USART_cfgStruct_t *USART_cfgStruct)
{
	STD_STATUS local_u8ErrorStatus = STATUS_OK;
	f32 local_u32Clk_MHZ = 0;
	
	if(USART_cfgStruct)
	{
		switch(hUSART[USARTx].Bus)
		{
			case APB1:
				local_u8ErrorStatus = RCC_u8Get_APB1_ClkFrequncyMHZ(&local_u32Clk_MHZ);
				break;
				
			case APB2:
				local_u8ErrorStatus = RCC_u8Get_APB2_ClkFrequncyMHZ(&local_u32Clk_MHZ);
				break;
			
			default:
				local_u8ErrorStatus = STATUS_NOT_OK;
				break;
		}
		local_u8ErrorStatus = USART_u8Configure(USARTx, USART_cfgStruct, local_u32Clk_MHZ);
		
		local_u8ErrorStatus = NVIC_u8ClearPendingStatus(hUSART[USARTx].interruptID);
		local_u8ErrorStatus = NVIC_u8InterruptEnable(hUSART[USARTx].interruptID);
	}
	else
	{
		local_u8ErrorStatus = STATUS_NULLPOINTER;
	}
	return local_u8ErrorStatus;
}

extern STD_STATUS hUSART_u8SendData(u8 USARTx, u8 *Copy_pu8Buffer, u16 Copy_u16BytesCount)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	
	if(Copy_pu8Buffer)
	{
		if((IS_USART_VALID(USARTx)) && (Copy_u16BytesCount))
		{
			if(USART_Tx_DMAChannelEnable[USARTx] == DMA_CHANNEL_ENABLED)
			{
				
				local_u8ErrorStatus = DMA_u8StartTransfer(hUSART[USARTx].DMA_TxChannel,
															Copy_pu8Buffer,
															&(hUSART[USARTx].USART_BaseRegister->DR), 
															Copy_u16BytesCount);
				
			}
			else
			{
				local_u8ErrorStatus = USART_u8SendData(USARTx, Copy_pu8Buffer, Copy_u16BytesCount);
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

extern STD_STATUS hUSART_u8ReceiveData(u8 USARTx, u8 *Copy_u8Buffer, u16 Copy_u16Length)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	
	if(Copy_u8Buffer)
	{
		if((IS_USART_VALID(USARTx)) && (Copy_u16Length))
		{
			if(USART_Rx_DMAChannelEnable[USARTx] == DMA_CHANNEL_ENABLED)
			{
				local_u8ErrorStatus = DMA_u8StartTransfer(hUSART[USARTx].DMA_RxChannel,
															&(hUSART[USARTx].USART_BaseRegister->DR), 
															Copy_pu8Buffer,
															Copy_u16BytesCount);
			}
			else
			{
				local_u8ErrorStatus = USART_u8ReceiveData(USARTx, Copy_u8Buffer, Copy_u16Length);
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

extern STD_STATUS hUSART_u8SetTxCallbackFn(u8 USARTx, callBackFn_t txCbf)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	
	/* Checking whether to pointer to the callback function is valid */
	if(txCbf)
	{
		if(USART_Tx_DMAChannelEnable[USARTx] == DMA_CHANNEL_ENABLED)
		{
			local_u8ErrorStatus = DMA_u8SetChannelCallbackFn(hUSART[USARTx].DMA_TxChannel, txCbf);
		}
		else
		{
			local_u8ErrorStatus = USART_u8SetTxCallbackFn(USARTx, txCbf);
		}
	}
	else
	{
		local_u8ErrorStatus = STATUS_NULLPOINTER;
	}
	return local_u8ErrorStatus;	
}

extern STD_STATUS hUSART_u8SetRxCallbackFn(u8 USARTx, callBackFn_t rxCbf)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	
	/* Checking whether to pointer to the callback function is valid */
	if(rxCbf)
	{
		if(USART_Rx_DMAChannelEnable[USARTx] == DMA_CHANNEL_ENABLED)
		{
			local_u8ErrorStatus = DMA_u8SetChannelCallbackFn(hUSART[USARTx].DMA_RxChannel, rxCbf);
		}
		else
		{
			local_u8ErrorStatus = USART_u8SetRxCallbackFn(USARTx, rxCbf);
		}
	}
	else
	{
		local_u8ErrorStatus = STATUS_NULLPOINTER;
	}
	return local_u8ErrorStatus;	
}

extern STD_STATUS hUSART_u8GenerateBreak(u8 USARTx)
{
	USART_u8GenerateBreak(USARTx);
	return STATUS_OK;
}


