#include "STD_TYPES.h"

#include "DMA.h"
#include "DMA_cfg.h"

#define DMA		(volatile const DMA_register_t *)0x40020000

typedef struct
{
	volatile u32 CCR;   /* DMA channel x configuration register */
	volatile u32 CNDTR; /* DMA channel x number of data register */
	volatile u32 CPAR;  /* DMA channel x peripheral address register */
	volatile u32 CMAR;  /* DMA channel x memory address register */
	volatile u32 RESERVED;
	
}DMAChannel_register_t;

typedef struct
{
	volatile u32 ISR;	/* DMA interrupt status register */
	volatile u32 IFCR;  /* DMA interrupt flag clear register */
	DMAChannel_register_t DMAChannel[DMA_NUMBER_OF_CHANNELS];

}DMA_register_t;

static callBackFn_t DMA_transferAppNotify[DMA_NUMBER_OF_CHANNELS] = {NULL, NULL, NULL, NULL, NULL. NULL, NULL};

const static DMAChannel_cfgStruct_t DMAChannel_InitCfgStruct[DMA_NUMBER_OF_CHANNELS] = 
{
	{
		.MEM2MEM_mode			= CHANNEL1_MEM2MEM,
		.priorityLevel          = CHANNEL1_PRIORITY,
		.memorySize             = CHANNEL1_MSIZE,
		.peripheralSize         = CHANNEL1_PSIZE,
		.memoryIncrement        = CHANNEL1_MINC,
		.peripheralIncrement    = CHANNEL1_PINC,
		.circularMode           = CHANNEL1_CIRC,
		.dataDirection          = CHANNEL1_DIR
	},
	
	{
		.MEM2MEM_mode			= CHANNEL2_MEM2MEM,
		.priorityLevel          = CHANNEL2_PRIORITY,
		.memorySize             = CHANNEL2_MSIZE,
		.peripheralSize         = CHANNEL2_PSIZE,
		.memoryIncrement        = CHANNEL2_MINC,
		.peripheralIncrement    = CHANNEL2_PINC,
		.circularMode           = CHANNEL2_CIRC,
		.dataDirection          = CHANNEL2_DIR
	},
	
	{
		.MEM2MEM_mode			= CHANNEL3_MEM2MEM,
		.priorityLevel          = CHANNEL3_PRIORITY,
		.memorySize             = CHANNEL3_MSIZE,
		.peripheralSize         = CHANNEL3_PSIZE,
		.memoryIncrement        = CHANNEL3_MINC,
		.peripheralIncrement    = CHANNEL3_PINC,
		.circularMode           = CHANNEL3_CIRC,
		.dataDirection          = CHANNEL3_DIR
	},
	
	{
		.MEM2MEM_mode			= CHANNEL4_MEM2MEM,
		.priorityLevel          = CHANNEL4_PRIORITY,
		.memorySize             = CHANNEL4_MSIZE,
		.peripheralSize         = CHANNEL4_PSIZE,
		.memoryIncrement        = CHANNEL4_MINC,
		.peripheralIncrement    = CHANNEL4_PINC,
		.circularMode           = CHANNEL4_CIRC,
		.dataDirection          = CHANNEL4_DIR
	},
	
	{
		.MEM2MEM_mode			= CHANNEL5_MEM2MEM,
		.priorityLevel          = CHANNEL5_PRIORITY,
		.memorySize             = CHANNEL5_MSIZE,
		.peripheralSize         = CHANNEL5_PSIZE,
		.memoryIncrement        = CHANNEL5_MINC,
		.peripheralIncrement    = CHANNEL5_PINC,
		.circularMode           = CHANNEL5_CIRC,
		.dataDirection          = CHANNEL5_DIR
	},
	
	{
		.MEM2MEM_mode			= CHANNEL6_MEM2MEM,
		.priorityLevel          = CHANNEL6_PRIORITY,
		.memorySize             = CHANNEL6_MSIZE,
		.peripheralSize         = CHANNEL6_PSIZE,
		.memoryIncrement        = CHANNEL6_MINC,
		.peripheralIncrement    = CHANNEL6_PINC,
		.circularMode           = CHANNEL6_CIRC,
		.dataDirection          = CHANNEL6_DIR
	},
	
	{
		.MEM2MEM_mode			= CHANNEL7_MEM2MEM,
		.priorityLevel          = CHANNEL7_PRIORITY,
		.memorySize             = CHANNEL7_MSIZE,
		.peripheralSize         = CHANNEL7_PSIZE,
		.memoryIncrement        = CHANNEL7_MINC,
		.peripheralIncrement    = CHANNEL7_PINC,
		.circularMode           = CHANNEL7_CIRC,
		.dataDirection          = CHANNEL7_DIR
	}	
};


STD_STATUS DMA_u8ChannelInit(u8 Channelx)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	if(IS_CHANNEL_VALID(Channelx))
	{
		local_u8ErrorStatus = DMA_u8ChannelConfigure(Channelx, &DMAChannel_InitCfgStruct[Channelx]);
	}
	else
	{
		local_u8ErrorStatus = STATUS_NOT_OK;		
	}
	return local_u8ErrorStatus;	
}

STD_STATUS DMA_u8ChannelConfigure(u8 Channelx, DMAChannel_cfgStruct_t *DMAChannel_cfgStruct)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	u32 local_u32RegisterCopy = 0;
	if(DMAChannel_cfgStruct)
	{
		if(IS_CHANNEL_VALID(Channelx))
		{		
			/* Disable channel interrupts */
			DMA->DMAChannel[Channelx].CCR &= ~DMA_CCR_U32_TEIE_MASK;
			DMA->DMAChannel[Channelx].CCR &= ~DMA_CCR_U32_HTIE_MASK;
			DMA->DMAChannel[Channelx].CCR &= ~DMA_CCR_U32_TCIE_MASK;
			
			/* Disable channel */
			DMA->DMAChannel[Channelx].CCR &= ~DMA_CCR_U32_EN_MASK;
			
			/* Clear pending interrupts */
			DMA->IFCR |= (DMA_ISR_U32_CGIFx_MASK << Channelx*4);

			/* Channel CCR register copy */
			local_u32RegisterCopy = DMA->DMAChannel[Channelx].CCR;

			local_u8ErrorStatus = STATUS_OK;
			/* Configure the channel */
			switch(DMAChannel_cfgStruct[Channelx].MEM2MEM_mode)
			{
				case MEM2MEM_DISABLED:	
					local_u32RegisterCopy &= ~DMA_CCR_U32_MEM2MEM_MASK;
					break;
				case MEM2MEM_ENABLED:
					local_u32RegisterCopy |= DMA_CCR_U32_MEM2MEM_MASK;
					break;
				default:
					local_u8ErrorStatus = STATUS_NOT_OK;
			}
			
			local_u32RegisterCopy &= DMA_CCR_U32_PL_CLR_MASK;
			switch(DMAChannel_cfgStruct[Channelx].priorityLevel)
			{
				case CH_PRI_LOW:	
					local_u32RegisterCopy |= DMA_CCR_U32_PL_LOW_MASK;
					break;
				case CH_PRI_MEDIUM:
					local_u32RegisterCopy |= DMA_CCR_U32_PL_MEDIUM_MASK;
					break;
				case CH_PRI_HIGH:
					local_u32RegisterCopy |= DMA_CCR_U32_PL_HIGH_MASK;
					break;
				case CH_PRI_VERY_HIGH:
					local_u32RegisterCopy |= DMA_CCR_U32_PL_VERY_HIGH_MASK;
					break;
				default:
					local_u8ErrorStatus = STATUS_NOT_OK;
			}
			
			local_u32RegisterCopy &= DMA_CCR_U32_M_SIZE_CLR_MASK;
			switch(DMAChannel_cfgStruct[Channelx].memorySize)
			{
				case MSIZE_BITS_8:	
					local_u32RegisterCopy |= DMA_CCR_U32_M_SIZE_8_MASK;
					break;
				case MSIZE_BITS_16:
					local_u32RegisterCopy |= DMA_CCR_U32_M_SIZE_16_MASK;
					break;
				case MSIZE_BITS_32:
					local_u32RegisterCopy |= DMA_CCR_U32_M_SIZE_32_MASK;
					break;
				default:
					local_u8ErrorStatus = STATUS_NOT_OK;
			}
			
			local_u32RegisterCopy &= DMA_CCR_U32_P_SIZE_CLR_MASK;
			switch(DMAChannel_cfgStruct[Channelx].peripheralSize)
			{
				case PSIZE_BITS_8:	
					local_u32RegisterCopy |= DMA_CCR_U32_P_SIZE_8_MASK;
					break;
				case PSIZE_BITS_16:
					local_u32RegisterCopy |= DMA_CCR_U32_P_SIZE_16_MASK;
					break;
				case PSIZE_BITS_32:
					local_u32RegisterCopy |= DMA_CCR_U32_P_SIZE_32_MASK;
					break;
				default:
					local_u8ErrorStatus = STATUS_NOT_OK;
			}
			switch(DMAChannel_cfgStruct[Channelx].memoryIncrement)
			{
				case MINC_DISABLED:	
					local_u32RegisterCopy &= ~DMA_CCR_U32_MINC_MASK;
					break;
				case MINC_ENABLED:
					local_u32RegisterCopy |= DMA_CCR_U32_MINC_MASK;
					break;
				default:
					local_u8ErrorStatus = STATUS_NOT_OK;
			}
			switch(DMAChannel_cfgStruct[Channelx].peripheralIncrement)
			{
				case PINC_DISABLED:	
					local_u32RegisterCopy &= ~DMA_CCR_U32_PINC_MASK;
					break;
				case PINC_ENABLED:
					local_u32RegisterCopy |= DMA_CCR_U32_PINC_MASK;
					break;
				default:
					local_u8ErrorStatus = STATUS_NOT_OK;
			}
			switch(DMAChannel_cfgStruct[Channelx].circularMode)
			{
				case CIRC_DISABLED:	
					local_u32RegisterCopy &= ~DMA_CCR_U32_CIRC_MASK;
					break;
				case CIRC_ENABLED:
					local_u32RegisterCopy |= DMA_CCR_U32_CIRC_MASK;
					break;
				default:
					local_u8ErrorStatus = STATUS_NOT_OK;
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

STD_STATUS DMA_u8StartTransfer(u8 Channelx, u32 Copy_u32SourceAddress, u32 Copy_u32DestinationAddress, u16 Copy_u32BlockSize)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	if(Copy_u32SourceAddress && Copy_u32DestinationAddress)
	{
		if(IS_CHANNEL_VALID(Channelx) && Copy_u32BlockSize)
		{
			DMA_u8StopTransfer(Channelx);
			DMA->DMAChannel[Channelx].CNDTR = Copy_u32BlockSize;
			
			/* Transfer data from a peripheral to memory */
			switch(DMAChannel_cfgStruct.dataDirection)
			{
				case READ_FROM_PERIPH:
					DMA->DMAChannel[Channelx].CPAR = Copy_u32SourceAddress; 
					DMA->DMAChannel[Channelx].CMAR = Copy_u32DestinationAddress; 
				
					/* Enable the channel */
					DMA->DMAChannel[Channelx].CCR |= DMA_CCR_U32_EN_MASK;
					local_u8ErrorStatus = STATUS_OK;
					break;
					
				case READ_FROM_MEM:
					DMA->DMAChannel[Channelx].CMAR = Copy_u32SourceAddress; 
					DMA->DMAChannel[Channelx].CPAR = Copy_u32DestinationAddress; 
				
					/* Enable the channel */
					DMA->DMAChannel[Channelx].CCR |= DMA_CCR_U32_EN_MASK;
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
	}
	else
	{
		local_u8ErrorStatus = STATUS_NULLPOINTER;
	}
	return local_u8ErrorStatus;
}

STD_STATUS DMA_u8StopTransfer(u8 Channelx)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	
	if(IS_CHANNEL_VALID(Channelx))
	{
		/* Disable the channel */
		DMA->DMAChannel[Channelx].CCR &= ~DMA_CCR_U32_EN_MASK;
	}
	else
	{
		local_u8ErrorStatus = STATUS_NOT_OK;
	}		
	return local_u8ErrorStatus;
}

STD_STATUS DMA_u8ClearChannelFlag(u8 Channelx, u8 Copy_u8Flag)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	
	if(IS_CHANNEL_VALID(Channelx))
	{
		switch(Copy_u8Flag)
		{
			case TRANSFER_INT_FLAG:	
				DMA->IFCR = (DMA_ISR_U32_CGIFx_MASK << Channelx*4);
				local_u8ErrorStatus = STATUS_NOT_OK;
				break;
			
			case HALF_TRANSFER_INT_FLAG:	
				DMA->IFCR = (DMA_ISR_U32_CTCIFx_MASK << Channelx*4);
				local_u8ErrorStatus = STATUS_NOT_OK;
				break;
				
			case TRANSFER_COMPLETE_FLAG:  
				DMA->IFCR = (DMA_ISR_U32_CHTIFx_MASK << Channelx*4);
				local_u8ErrorStatus = STATUS_NOT_OK;
				break;
				
			case GLOBAL_INT_FLAG:  
				DMA->IFCR = (DMA_ISR_U32_CTEIFx_MASK << Channelx*4);
				local_u8ErrorStatus = STATUS_NOT_OK;
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

STD_STATUS DMA_u8GetChannelFlag(u8 Channelx, u8 Copy_u8Flag, u8 *Copy_pu8FlagReturn)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	
	if(Copy_pu8FlagReturn)
	{
		if(IS_CHANNEL_VALID(Channelx))
		{
			switch(Copy_u8Flag)
			{
				case TRANSFER_INT_FLAG:	
					*Copy_pu8FlagReturn = DMA->ISR & (DMA_ISR_U32_CGIFx_MASK << Channelx*4);
					local_u8ErrorStatus = STATUS_NOT_OK;
					break;
				
				case HALF_TRANSFER_INT_FLAG:	
					*Copy_pu8FlagReturn = DMA->ISR & (DMA_ISR_U32_CTCIFx_MASK << Channelx*4);
					local_u8ErrorStatus = STATUS_NOT_OK;
					break;
					
				case TRANSFER_COMPLETE_FLAG:  
					*Copy_pu8FlagReturn = DMA->ISR & (DMA_ISR_U32_CHTIFx_MASK << Channelx*4);
					local_u8ErrorStatus = STATUS_NOT_OK;
					break;
					
				case GLOBAL_INT_FLAG:  
					*Copy_pu8FlagReturn = DMA->ISR & (DMA_ISR_U32_CTEIFx_MASK << Channelx*4);
					local_u8ErrorStatus = STATUS_NOT_OK;
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
	}
	else
	{
		local_u8ErrorStatus = STATUS_NULLPOINTER;
	}
	return local_u8ErrorStatus;
}

STD_STATUS DMA_u8SetChannelCallbackFn(u8 Channelx, callbackFn_t channelCbf)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	
	if(channelCbf)
	{
		if(IS_CHANNEL_VALID(Channelx))
		{		
			transferAppNotify[Channelx] = channelCbf;
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
}

extern void DMA1_Channel1_IRQHandler(void)
{
	/* clearing interrupt flag */
	DMA_u8ClearChannelFlag(DMA_CHANNEL_1, TRANSFER_COMPLETE_FLAG);
	
	/* calling the call back function */
	if (DMA_transferAppNotify[DMA_CHANNEL_1] != NULL)
	{
		DMA_transferAppNotify[DMA_CHANNEL_1]();
	}
}

extern void DMA1_Channel2_IRQHandler(void)
{
	/* clearing interrupt flag */
	DMA_u8ClearChannelFlag(DMA_CHANNEL_2, TRANSFER_COMPLETE_FLAG);
	
	/* calling the call back function */
	if (DMA_transferAppNotify[DMA_CHANNEL_2] != NULL)
	{
		DMA_transferAppNotify[DMA_CHANNEL_2]();
	}
}

extern void DMA1_Channel3_IRQHandler(void)
{
	/* clearing interrupt flag */
	DMA_u8ClearChannelFlag(DMA_CHANNEL_3, TRANSFER_COMPLETE_FLAG);
	
	/* calling the call back function */
	if (DMA_transferAppNotify[DMA_CHANNEL_3] != NULL)
	{
		DMA_transferAppNotify[DMA_CHANNEL_3]();
	}
}

extern void DMA1_Channel4_IRQHandler(void)
{
	/* clearing interrupt flag */
	DMA_u8ClearChannelFlag(DMA_CHANNEL_4, TRANSFER_COMPLETE_FLAG);
	
	/* calling the call back function */
	if (DMA_transferAppNotify[DMA_CHANNEL_4] != NULL)
	{
		DMA_transferAppNotify[DMA_CHANNEL_4]();
	}
}

extern void DMA1_Channel5_IRQHandler(void)
{
	/* clearing interrupt flag */
	DMA_u8ClearChannelFlag(DMA_CHANNEL_5, TRANSFER_COMPLETE_FLAG);
	
	/* calling the call back function */
	if (DMA_transferAppNotify[DMA_CHANNEL_5] != NULL)
	{
		DMA_transferAppNotify[DMA_CHANNEL_5]();
	}
}

extern void DMA1_Channel6_IRQHandler(void)
{
	/* clearing interrupt flag */
	DMA_u8ClearChannelFlag(DMA_CHANNEL_6, TRANSFER_COMPLETE_FLAG);
	
	/* calling the call back function */
	if (DMA_transferAppNotify[DMA_CHANNEL_6] != NULL)
	{
		DMA_transferAppNotify[DMA_CHANNEL_6]();
	}
}

extern void DMA1_Channel7_IRQHandler(void)
{
	/* clearing interrupt flag */
	DMA_u8ClearChannelFlag(DMA_CHANNEL_7, TRANSFER_COMPLETE_FLAG);
	
	/* calling the call back function */
	if (DMA_transferAppNotify[DMA_CHANNEL_7] != NULL)
	{
		DMA_transferAppNotify[DMA_CHANNEL_7]();
	}
}

