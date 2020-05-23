#include "STD_TYPES.h"

#include "USART.h"
#include "USART_cfg.h"

/* Structure of USART register map */
typedef struct
{
	volatile u32 SR;
	volatile u32 DR;
	volatile u32 BRR;
	volatile u32 CR1;
	volatile u32 CR2;
	volatile u32 CR3;
	volatile u32 GPTR;

}USARTx_register_t;

/* Structure of the data buffer */
typedef struct
{
	u8 *ptr;
	u32 position;
	u32 size;
	u8 state;	
}dataBuffer_t;

typedef struct
{
	const USARTx_register_t *USART_BaseRegister;
	callBackFn_t appTxNotify;
	callBackFn_t appRxNotify;
	dataBuffer_t txBuffer;
	dataBuffer_t rxBuffer;
	u8 DMA_TxState;
	u8 DMA_RxState;
	u8 LIN_State;

}USART_Info_t;

static u16 USART_u16CalculateBaudRate(f32 Copy_f32Baudrate, f32 Copy_f32BUS_Clk_MHZ);

const static USART_cfgStruct_t USART_InitCfgStruct[NUMBER_OF_USARTs] = 
{
	{
		.mode 				= USART1_SYNC,
		.baudRate 			= USART1_BAUDRATE1,
		.stopBits 			= USART1_STOP_BITS,
		.parityBits 		= USART1_PARITY_BIT,
		.channelDirection 	= USART1_CHANNEL_DIRECTION,
		.enableRxDMA		= USART1_Rx_DMA_STATE,
		.enableTxDMA 		= USART1_Tx_DMA_STATE,
		.enableLIN			= USART1_LIN_STATE
	},
	
	{
		.mode 				= USART2_SYNC,
		.baudRate 			= USART2_BAUDRATE1,
		.stopBits 			= USART2_STOP_BITS,
		.parityBits 		= USART2_PARITY_BIT,
		.channelDirection 	= USART2_CHANNEL_DIRECTION,
		.enableRxDMA		= USART2_Rx_DMA_STATE,
		.enableTxDMA 		= USART2_Tx_DMA_STATE,
		.enableLIN			= USART2_LIN_STATE
	},
	
	{
		.mode 				= USART3_SYNC,
		.baudRate 			= USART3_BAUDRATE1,
		.stopBits 			= USART3_STOP_BITS,
		.parityBits 		= USART3_PARITY_BIT,
		.channelDirection 	= USART3_CHANNEL_DIRECTION,
		.enableRxDMA		= USART3_Rx_DMA_STATE,
		.enableTxDMA 		= USART3_Tx_DMA_STATE,
		.enableLIN			= USART3_LIN_STATE
	}
};

static USART_Info_t USART_Info[NUMBER_OF_USARTs] =
{
	{
		.USART_BaseRegister			=	(USARTx_register_t *)USART1_BASE_REG,
		.txBuffer.ptr				=	NULL,
		.txBuffer.position			=	0,
		.txBuffer.size				=	0,
		.txBuffer.state				=	STATUS_IDLE,
		.rxBuffer.ptr				=	NULL,			
		.rxBuffer.position			=	0,
		.rxBuffer.size				=	0,
		.rxBuffer.state				=	STATUS_IDLE,
	    .appTxNotify  				=	NULL,
	    .appRxNotify  				=	NULL,
		.DMA_TxState				=	DMA_DISABLED,
		.DMA_RxState				=	DMA_DISABLED,
		.LIN_State					=	LIN_DISABLED
	},
	{
		.USART_BaseRegister			=	(USARTx_register_t *)USART2_BASE_REG,
	    .txBuffer.ptr				=	NULL,
		.txBuffer.position			=	0,
		.txBuffer.size				=	0,
		.txBuffer.state				=	STATUS_IDLE,
		.rxBuffer.ptr				=	NULL,			
		.rxBuffer.position			=	0,
		.rxBuffer.size				=	0,
		.rxBuffer.state				=	STATUS_IDLE,
	    .appTxNotify  				=	NULL,
	    .appRxNotify  				=	NULL,
		.DMA_TxState				=	DMA_DISABLED,
		.DMA_RxState				=	DMA_DISABLED,
		.LIN_State					=	LIN_DISABLED
	},
	{
		.USART_BaseRegister			=	(USARTx_register_t *)USART3_BASE_REG,
	    .txBuffer.ptr				=	NULL,
		.txBuffer.position			=	0,
		.txBuffer.size				=	0,
		.txBuffer.state				=	STATUS_IDLE,
		.rxBuffer.ptr				=	NULL,			
		.rxBuffer.position			=	0,
		.rxBuffer.size				=	0,
		.rxBuffer.state				=	STATUS_IDLE,
	    .appTxNotify  				=	NULL,
	    .appRxNotify  				=	NULL,
		.DMA_TxState				=	DMA_DISABLED,
		.DMA_RxState				=	DMA_DISABLED,
		.LIN_State					=	LIN_DISABLED
	}
};

extern STD_STATUS USART_u8Init(u8 USARTx, f32 Copy_f32BUS_Clk_MHZ)
{
	STD_STATUS local_u8ErrorStatus = STATUS_OK;
	local_u8ErrorStatus = USART_u8Configure(USARTx, &(USART_InitCfgStruct[USARTx]), Copy_f32BUS_Clk_MHZ);
	return local_u8ErrorStatus;	
}

extern STD_STATUS USART_u8DefaultInit(u8 USARTx, f32 Copy_f32BUS_Clk_MHZ)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	if(IS_USART_VALID(USARTx))
	{
		/* Configure BRR for 9600 baudrate */
		(USART_Info[USARTx].USART_BaseRegister)->BRR = (u16)USART_u16CalculateBaudRate(BAUD_9600, Copy_f32BUS_Clk_MHZ);

		/* Configure the parity bits */
		/* No parity */
		(USART_Info[USARTx].USART_BaseRegister)->CR1 &= ~(USART_CR1_U32_PCE_MASK|USART_CR1_U32_PS_MASK);

		/* Configure the stop bits */
		/* 1 stop bit */
		(USART_Info[USARTx].USART_BaseRegister)->CR2 &= USART_CR2_U32_STOP_CLR_MASK;
		(USART_Info[USARTx].USART_BaseRegister)->CR2 |= USART_CR2_U32_STOP_1_MASK;

		/* Configure Rx_DMA usage */
		/* No Rx_DMA */
		USART_u8DisableRxDMA(USARTx);

		/* Configure Tx_DMA usage */
		/* No Tx_DMA */
		USART_u8DisableTxDMA(USARTx);
		
		/* Configure LIN usage */
		/* No LIN */
		USART_u8DisableLIN(USARTx);

		/* Configure the channel direction */
		(USART_Info[USARTx].USART_BaseRegister)->CR1 &= ~(USART_CR1_U32_TCIE_MASK|USART_CR1_U32_RXNEIE_MASK|USART_CR1_U32_RE_MASK|USART_CR1_U32_TE_MASK);
		/* Enable transmitter and receiver interrupts */
		(USART_Info[USARTx].USART_BaseRegister)->CR1 |= (USART_CR1_U32_TCIE_MASK|USART_CR1_U32_RXNEIE_MASK);
		/* Enable transmitter and receiver */
		(USART_Info[USARTx].USART_BaseRegister)->CR1 |= (USART_CR1_U32_RE_MASK|USART_CR1_U32_TE_MASK);

		/* Enable the USARTx */
		(USART_Info[USARTx].USART_BaseRegister)->CR1 |= USART_CR1_U32_UE_MASK;
		local_u8ErrorStatus = STATUS_OK;
	}
	else
	{	
		local_u8ErrorStatus = STATUS_NOT_OK;
	}
	return local_u8ErrorStatus;	
}

extern STD_STATUS USART_u8Configure(u8 USARTx, USART_cfgStruct_t *USART_cfgStruct, f32 Copy_f32BUS_Clk_MHZ)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;

	if(USART_cfgStruct)
	{
		/* Configure BRR */
		(USART_Info[USARTx].USART_BaseRegister)->BRR = (u16)USART_u16CalculateBaudRate(USART_cfgStruct[USARTx].baudRate, Copy_f32BUS_Clk_MHZ);

		/* Configure the parity bits */
		(USART_Info[USARTx].USART_BaseRegister)->CR1 &= ~(USART_CR1_U32_PCE_MASK|USART_CR1_U32_PS_MASK);
		switch(USART_cfgStruct[USARTx].parityBits)
		{
		case NO_PARITY:
			break;

		case EVEN_PARITY:
			(USART_Info[USARTx].USART_BaseRegister)->CR1 |= USART_CR1_U32_PCE_MASK;
			break;

		case ODD_PARITY:
			(USART_Info[USARTx].USART_BaseRegister)->CR1 |= (USART_CR1_U32_PCE_MASK|USART_CR1_U32_PS_MASK);
			break;

		default:
			local_u8ErrorStatus = STATUS_NOT_OK;
			break;
		}

		/* Configure the stop bits */
		(USART_Info[USARTx].USART_BaseRegister)->CR2 &= USART_CR2_U32_STOP_CLR_MASK;
		switch(USART_cfgStruct[USARTx].parityBits)
		{
		case STOP_BITS_1:
			(USART_Info[USARTx].USART_BaseRegister)->CR2 |= USART_CR2_U32_STOP_1_MASK;
			break;

		case STOP_BITS_0_5:
			(USART_Info[USARTx].USART_BaseRegister)->CR2 |= USART_CR2_U32_STOP_0_5_MASK;
			break;

		case STOP_BITS_2:
			(USART_Info[USARTx].USART_BaseRegister)->CR2 |= USART_CR2_U32_STOP_2_MASK;
			break;

		case STOP_BITS_1_5:
			(USART_Info[USARTx].USART_BaseRegister)->CR2 |= USART_CR2_U32_STOP_1_5_MASK;
			break;

		default:
			local_u8ErrorStatus = STATUS_NOT_OK;
			break;
		}

		/* Configure Rx_DMA usage */
		switch(USART_cfgStruct[USARTx].enableRxDMA)
		{
		case DMA_DISABLED:
			USART_u8DisableRxDMA(USARTx);
			break;

		case DMA_ENABLED:
			USART_u8EnableRxDMA(USARTx);
			break;

		default:
			local_u8ErrorStatus = STATUS_NOT_OK;
			break;

		}

		/* Configure Tx_DMA usage */
		switch(USART_cfgStruct[USARTx].enableTxDMA)
		{
		case DMA_DISABLED:
			USART_u8DisableTxDMA(USARTx);
			break;

		case DMA_ENABLED:
			USART_u8EnableTxDMA(USARTx);
			break;

		default:
			local_u8ErrorStatus = STATUS_NOT_OK;
			break;

		}
		
		/* Configure LIN usage */
		switch(USART_cfgStruct[USARTx].enableLIN)
		{
		case LIN_DISABLED:
			USART_u8DisableLIN(USARTx);
			break;

		case LIN_ENABLED:
			USART_u8EnableLIN(USARTx);
			break;

		default:
			local_u8ErrorStatus = STATUS_NOT_OK;
			break;
		}

		/* Configure the channel direction */
		(USART_Info[USARTx].USART_BaseRegister)->CR1 &= ~(USART_CR1_U32_TXEIE_MASK|USART_CR1_U32_RXNEIE_MASK|USART_CR1_U32_RE_MASK|USART_CR1_U32_TE_MASK);
		switch(USART_cfgStruct[USARTx].channelDirection)
		{
		case FULL_DUPLEX:
			/* Enable transmitter and receiver interrupts */
			(USART_Info[USARTx].USART_BaseRegister)->CR1 |= (USART_CR1_U32_TXEIE_MASK|USART_CR1_U32_RXNEIE_MASK);
			/* Enable transmitter and receiver */
			(USART_Info[USARTx].USART_BaseRegister)->CR1 |= (USART_CR1_U32_RE_MASK|USART_CR1_U32_TE_MASK);
			break;

		case HALF_DUPLEX:
			/* Enable the HALF-DUPLEX mode*/
			(USART_Info[USARTx].USART_BaseRegister)->CR3 |= USART_CR3_U32_HDSEL_MASK;
			/* Enable transmitter and receiver interrupts */
			(USART_Info[USARTx].USART_BaseRegister)->CR1 |= (USART_CR1_U32_TXEIE_MASK|USART_CR1_U32_RXNEIE_MASK);
			/* Enable transmitter and receiver */
			(USART_Info[USARTx].USART_BaseRegister)->CR1 |= (USART_CR1_U32_RE_MASK|USART_CR1_U32_TE_MASK);
			break;

		case SIMPLEX_T:
			/* Enable transmitter interrupt */
			(USART_Info[USARTx].USART_BaseRegister)->CR1 |= USART_CR1_U32_TXEIE_MASK;
			/* Enable transmitter */
			(USART_Info[USARTx].USART_BaseRegister)->CR1 |= USART_CR1_U32_TE_MASK;
			break;

		case SIMPLEX_R:
			/* Enable receiver interrupt */
			(USART_Info[USARTx].USART_BaseRegister)->CR1 |= USART_CR1_U32_RXNEIE_MASK;
			/* Enable receiver */
			(USART_Info[USARTx].USART_BaseRegister)->CR1 |= USART_CR1_U32_RE_MASK;
			break;

		default:
			local_u8ErrorStatus = STATUS_NOT_OK;
			break;
		}

		/* Clear the TC flag */
		USART_u8ClearFlagStatus(USARTx, USART_SR_U32_TC_MASK);

		/* Enable the USARTx */
		(USART_Info[USARTx].USART_BaseRegister)->CR1 |= USART_CR1_U32_UE_MASK;
	}
	else
	{
		local_u8ErrorStatus = STATUS_NULLPOINTER;
	}
	return local_u8ErrorStatus;	
}

extern STD_STATUS USART_u8SendData(u8 USARTx, u8 *Copy_pu8Buffer, u16 Copy_u16BytesCount)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	
	if(Copy_pu8Buffer)
	{
		if((IS_USART_VALID(USARTx)) && (Copy_u16BytesCount))
		{
			if(USART_Info[USARTx].txBuffer.state == STATUS_IDLE)
			{
				USART_Info[USARTx].txBuffer.ptr = Copy_pu8Buffer;
				USART_Info[USARTx].txBuffer.position = 0;
				USART_Info[USARTx].txBuffer.size = Copy_u16BytesCount;
				trace_printf("START SENDING DATA\n");
				USART_u8SendByte(USART_Info[USARTx].USART_BaseRegister, USART_Info[USARTx].txBuffer.ptr[USART_Info[USART1].txBuffer.position]);
				
				USART_Info[USARTx].txBuffer.position++;
				USART_Info[USARTx].txBuffer.state = STATUS_BUSY;
				local_u8ErrorStatus = STATUS_OK;				
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
	}
	else
	{
		local_u8ErrorStatus = STATUS_NULLPOINTER;
	}
	return local_u8ErrorStatus;
}

extern STD_STATUS USART_u8ReceiveData(u8 USARTx, u8 *Copy_u8Buffer, u16 Copy_u16Length)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	
	if(Copy_u8Buffer)
	{
		if((IS_USART_VALID(USARTx)) && (Copy_u16Length))
		{
			/* Checking whether if there is a current receiving process from the buffer or not*/
			if(USART_Info[USARTx].rxBuffer.state == STATUS_IDLE)
			{
				trace_printf("START RECEIVING DATA\n");
				USART_Info[USARTx].rxBuffer.ptr = Copy_u8Buffer;
				USART_Info[USARTx].rxBuffer.size = Copy_u16Length;
				USART_Info[USARTx].rxBuffer.position = 0;
				USART_Info[USARTx].rxBuffer.state = STATUS_BUSY;
				local_u8ErrorStatus = STATUS_OK;
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
	}
	else
	{
		local_u8ErrorStatus = STATUS_NULLPOINTER;
	}
	return local_u8ErrorStatus;	
}

extern STD_STATUS USART_u8GetFlagStatus(u8 USARTx, u32 Copy_u32FlagMask, u32 *Copy_pu32StatusReturn)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;

	if((IS_USART_VALID(USARTx)) && (Copy_pu32StatusReturn))
	{
		switch(Copy_u32FlagMask)
		{
		case USART_SR_U32_RXNE_MASK:
			*Copy_pu32StatusReturn = (USART_Info[USARTx].USART_BaseRegister)->SR & (USART_SR_U32_RXNE_MASK);
			break;

		case USART_SR_U32_TC_MASK:
			*Copy_pu32StatusReturn = (USART_Info[USARTx].USART_BaseRegister)->SR & (USART_SR_U32_TC_MASK);
			break;

		default:
			local_u8ErrorStatus = STATUS_NOT_OK;
			break;
		}
	}
	else
	{
		local_u8ErrorStatus = STATUS_NULLPOINTER;
	}
	return local_u8ErrorStatus;
}

extern STD_STATUS USART_u8ClearFlagStatus(u8 USARTx, u32 Copy_u32FlagMask)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;

	if(IS_USART_VALID(USARTx))
	{
		switch(Copy_u32FlagMask)
		{
		case USART_SR_U32_RXNE_MASK:
			(USART_Info[USARTx].USART_BaseRegister)->SR &= ~USART_SR_U32_RXNE_MASK;
			break;

		case USART_SR_U32_TC_MASK:
			(USART_Info[USARTx].USART_BaseRegister)->SR &= ~USART_SR_U32_TC_MASK;
			break;

		default:
			local_u8ErrorStatus = STATUS_NOT_OK;
			break;
		}
	}
	else
	{
		local_u8ErrorStatus = STATUS_NULLPOINTER;
	}
	return local_u8ErrorStatus;
}

static u16 USART_u16CalculateBaudRate(f32 Copy_f32Baudrate, f32 Copy_f32BUS_Clk_MHZ)
{
	f32 local_f32DIVTotal = (f32)(Copy_f32BUS_Clk_MHZ * 1000000) / (16 * Copy_f32Baudrate);
	u32 local_f32DIVdecimal = (u32)local_f32DIVTotal;
	f32 local_f32DIVfraction = local_f32DIVTotal - (f32)local_f32DIVdecimal;
	f32 local_f32DIVfraction_16 = local_f32DIVfraction * 16;
	f32 local_f32DIVfractionRounded=0;

	if (local_f32DIVfraction_16 > ((u32)local_f32DIVfraction_16)+0.49)
	{
		local_f32DIVfractionRounded = ((u32)local_f32DIVfraction_16)+1;
	}
	else
	{
		local_f32DIVfractionRounded = ((u32)local_f32DIVfraction_16);
	}

	return ((local_f32DIVdecimal<<4) + local_f32DIVfractionRounded);
}

extern STD_STATUS USART_u8SendByte(u8 USARTx, u8 Copy_u8Byte)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;

	if(IS_USART_VALID(USARTx))
	{
		(USART_Info[USARTx].USART_BaseRegister)->DR = Copy_u8Byte;
		trace_printf("SENDING: %c\n", Copy_u8Byte);
	}
	else
	{
		local_u8ErrorStatus = STATUS_NULLPOINTER;
	}
	return local_u8ErrorStatus;
}

extern STD_STATUS USART_u8ReceiveByte(u8 USARTx, u8 *Copy_pu8ByteReturn)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;

	if((IS_USART_VALID(USARTx)) && (Copy_pu8ByteReturn))
	{
		*Copy_pu8ByteReturn = (USART_Info[USARTx].USART_BaseRegister)->DR;
		trace_printf("RECEIVING: %c\n", *Copy_pu8ByteReturn);
	}
	else
	{
		local_u8ErrorStatus = STATUS_NULLPOINTER;
	}
	return local_u8ErrorStatus;
}

extern STD_STATUS USART_u8GenerateBreak(u8 USARTx)
{
	(USART_Info[USARTx].USART_BaseRegister)->CR1 |= USART_CR1_U32_SBK_MASK;
	return STATUS_OK;
}

extern STD_STATUS USART_u8EnableTxDMA(u8 USARTx)
{
	(USART_Info[USARTx].USART_BaseRegister)->CR3 |= USART_CR3_U32_DMAT_MASK;
	USART_Info[USARTx].DMA_TxState = DMA_ENABLED;
	return STATUS_OK;
}

extern STD_STATUS USART_u8DisableTxDMA(u8 USARTx)
{
	(USART_Info[USARTx].USART_BaseRegister)->CR3 &= ~USART_CR3_U32_DMAT_MASK;
	USART_Info[USARTx].DMA_TxState = DMA_DISABLED;
	return STATUS_OK;
}

extern STD_STATUS USART_u8EnableRxDMA(u8 USARTx)
{
	(USART_Info[USARTx].USART_BaseRegister)->CR3 |= USART_CR3_U32_DMAR_MASK;
	USART_Info[USARTx].DMA_RxState = DMA_ENABLED;
	return STATUS_OK;
}

extern STD_STATUS USART_u8DisableRxDMA(u8 USARTx)
{
	(USART_Info[USARTx].USART_BaseRegister)->CR3 &= ~USART_CR3_U32_DMAR_MASK;
	USART_Info[USARTx].DMA_RxState = DMA_DISABLED;
	return STATUS_OK;
}

extern STD_STATUS USART_u8SetTxCallbackFn(u8 USARTx, callBackFn_t txCbf)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	
	/* Checking whether to pointer to the callback function is valid */
	if(txCbf)
	{
		USART_Info[USARTx].appTxNotify = txCbf;
	}
	else
	{
		local_u8ErrorStatus = STATUS_NULLPOINTER;
	}
	return local_u8ErrorStatus;	
}

extern STD_STATUS USART_u8SetRxCallbackFn(u8 USARTx, callBackFn_t rxCbf)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	
	/* Checking whether to pointer to the callback function is valid */
	if(rxCbf)
	{
		USART_Info[USARTx].appRxNotify = rxCbf;
	}
	else
	{
		local_u8ErrorStatus = STATUS_NULLPOINTER;
	}
	return local_u8ErrorStatus;	
}

////TO BE IMPLEMENTED
extern STD_STATUS USART_u8EnableLIN(u8 USARTx)
{
	
	USART_Info[USARTx].LIN_State = LIN_ENABLED;
	return STATUS_OK;
}

extern STD_STATUS USART_u8DisableLIN(u8 USARTx)
{
	
	USART_Info[USARTx].LIN_State = LIN_DISABLED;
	return STATUS_OK;
}

extern void USART1_IRQHandler(void)
{	
	u32 local_u32FlagStatus = 0;
	/* Clearing the TC flag at the first interrupt */
	if(USART_Info[USART1].txBuffer.position == 0 && USART_Info[USART1].txBuffer.size == 0)
	{
		trace_printf("CLEARING TC FOR FIRST BYTE\n");
        USART_u8ClearFlagStatus(USART1_BASE_REG, USART_SR_U32_TC_MASK);
	}

	USART_u8GetFlagStatus(USART_Info[USART1].USART_BaseRegister, USART_SR_U32_RXNE_MASK, &local_u32FlagStatus);
	/* Checking whether the interrupt was generated from a receiving */
	if(local_u32FlagStatus)
	{
		/* Clear RXNE */
		USART_u8ClearFlagStatus(USART_Info[USART1].USART_BaseRegister, USART_SR_U32_RXNE_MASK);
		
		if(USART_Info[USART1].DMA_RxState == DMA_DISABLED)
		{
			/* If busy this means that buffer is ready to save the data */
			if(USART_Info[USART1].rxBuffer.state == STATUS_BUSY)
			{
				USART_u8ReceiveByte(USART_Info[USART1].USART_BaseRegister, &(USART_Info[USART1].rxBuffer.ptr[USART_Info[USART1].rxBuffer.position]));
				USART_Info[USART1].rxBuffer.position++;	
				if(USART_Info[USART1].rxBuffer.position == USART_Info[USART1].rxBuffer.size)
				{
					USART_Info[USART1].rxBuffer.ptr = NULL;
					USART_Info[USART1].rxBuffer.size = 0;
					USART_Info[USART1].rxBuffer.position = 0;
					USART_Info[USART1].rxBuffer.state = STATUS_IDLE;
					if(USART_Info[USART1].appRxNotify)
						USART_Info[USART1].appRxNotify();
				}
			}
		}
	}

	USART_u8GetFlagStatus(USART1_BASE_REG, USART_SR_U32_TC_MASK, &local_u32FlagStatus);
	/* Checking whether the interrupt was generated from a transmission */
	if(local_u32FlagStatus)
	{
		/* Clear the TC flag */
		USART_u8ClearFlagStatus(USART1_BASE_REG, USART_SR_U32_TC_MASK);
		
		if(USART_Info[USART1].DMA_TxState == DMA_DISABLED)
		{
			/* Transmission is still on-going */
			if(USART_Info[USART1].txBuffer.position != USART_Info[USART1].txBuffer.size)
			{
				USART_u8SendByte(USART_Info[USART1].USART_BaseRegister, USART_Info[USART1].txBuffer.ptr[USART_Info[USART1].txBuffer.position]);
				USART_Info[USART1].txBuffer.position++;			
			}
			/* Transmission is done */
			else
			{
				USART_Info[USART1].txBuffer.ptr = NULL;
				USART_Info[USART1].txBuffer.position = 0;
				USART_Info[USART1].txBuffer.size = 0;
				USART_Info[USART1].txBuffer.state = STATUS_IDLE;
				if(USART_Info[USART1].appTxNotify)
					USART_Info[USART1].appTxNotify();
			}
		}
	}
}

extern void USART2_IRQHandler(void)
{	
	u32 local_u32FlagStatus = 0;
	/* Clearing the TC flag at the first interrupt */
	if(USART_Info[USART2].txBuffer.position == 0 && USART_Info[USART2].txBuffer.size == 0)
	{
		trace_printf("CLEARING TC FOR FIRST BYTE\n");
        USART_u8ClearFlagStatus(USART2_BASE_REG, USART_SR_U32_TC_MASK);
	}

	USART_u8GetFlagStatus(USART_Info[USART2].USART_BaseRegister, USART_SR_U32_RXNE_MASK, &local_u32FlagStatus);
	/* Checking whether the interrupt was generated from a receiving */
	if(local_u32FlagStatus)
	{
		/* Clear RXNE */
		USART_u8ClearFlagStatus(USART_Info[USART2].USART_BaseRegister, USART_SR_U32_RXNE_MASK);
		
		if(USART_Info[USART2].DMA_RxState == DMA_DISABLED)
		{
			/* If busy this means that buffer is ready to save the data */
			if(USART_Info[USART2].rxBuffer.state == STATUS_BUSY)
			{
				USART_u8ReceiveByte(USART_Info[USART2].USART_BaseRegister, &(USART_Info[USART2].rxBuffer.ptr[USART_Info[USART2].rxBuffer.position]));
				USART_Info[USART2].rxBuffer.position++;	
				if(USART_Info[USART2].rxBuffer.position == USART_Info[USART2].rxBuffer.size)
				{
					USART_Info[USART2].rxBuffer.ptr = NULL;
					USART_Info[USART2].rxBuffer.size = 0;
					USART_Info[USART2].rxBuffer.position = 0;
					USART_Info[USART2].rxBuffer.state = STATUS_IDLE;
					if(USART_Info[USART2].appRxNotify)
						USART_Info[USART2].appRxNotify();
				}
			}
		}
	}
	
	USART_u8GetFlagStatus(USART2_BASE_REG, USART_SR_U32_TC_MASK, &local_u32FlagStatus);
	/* Checking whether the interrupt was generated from a transmission */
	if(local_u32FlagStatus)
	{
		/* Clear the TC flag */
		USART_u8ClearFlagStatus(USART2_BASE_REG, USART_SR_U32_TC_MASK);
		
		if(USART_Info[USART2].DMA_TxState == DMA_DISABLED)
		{
			/* Transmission is still on-going */
			if(USART_Info[USART2].txBuffer.position != USART_Info[USART2].txBuffer.size)
			{
				
				USART_u8SendByte(USART_Info[USART2].USART_BaseRegister, USART_Info[USART2].txBuffer.ptr[USART_Info[USART2].txBuffer.position]);
				USART_Info[USART2].txBuffer.position++;			
			}
			/* Transmission is done */
			else
			{
				USART_Info[USART2].txBuffer.ptr = NULL;
				USART_Info[USART2].txBuffer.position = 0;
				USART_Info[USART2].txBuffer.size = 0;
				USART_Info[USART2].txBuffer.state = STATUS_IDLE;
				if(USART_Info[USART2].appTxNotify)
					USART_Info[USART2].appTxNotify();
			}
		}
	}
}

extern void USART3_IRQHandler(void)
{	
	u32 local_u32FlagStatus = 0;
	/* Clearing the TC flag at the first interrupt */
	if(USART_Info[USART3].txBuffer.position == 0 && USART_Info[USART3].txBuffer.size == 0)
	{
		trace_printf("CLEARING TC FOR FIRST BYTE\n");
        USART_u8ClearFlagStatus(USART3_BASE_REG, USART_SR_U32_TC_MASK);
	}

	USART_u8GetFlagStatus(USART_Info[USART3].USART_BaseRegister, USART_SR_U32_RXNE_MASK, &local_u32FlagStatus);
	/* Checking whether the interrupt was generated from a receiving */
	if(local_u32FlagStatus)
	{
		/* Clear RXNE */
		USART_u8ClearFlagStatus(USART_Info[USART3].USART_BaseRegister, USART_SR_U32_RXNE_MASK);
		
		if(USART_Info[USART3].DMA_RxState == DMA_DISABLED)
		{
			/* If busy this means that buffer is ready to save the data */
			if(USART_Info[USART3].rxBuffer.state == STATUS_BUSY)
			{
				USART_u8ReceiveByte(USART_Info[USART3].USART_BaseRegister, &(USART_Info[USART3].rxBuffer.ptr[USART_Info[USART3].rxBuffer.position]));
				USART_Info[USART3].rxBuffer.position++;	
				if(USART_Info[USART3].rxBuffer.position == USART_Info[USART3].rxBuffer.size)
				{
					USART_Info[USART3].rxBuffer.ptr = NULL;
					USART_Info[USART3].rxBuffer.size = 0;
					USART_Info[USART3].rxBuffer.position = 0;
					USART_Info[USART3].rxBuffer.state = STATUS_IDLE;
					if(USART_Info[USART3].appRxNotify)
						USART_Info[USART3].appRxNotify();
				}
			}
		}
	}
	
	USART_u8GetFlagStatus(USART3_BASE_REG, USART_SR_U32_TC_MASK, &local_u32FlagStatus);
	/* Checking whether the interrupt was generated from a transmission */
	if(local_u32FlagStatus)
	{
		/* Clear the TC flag */
		USART_u8ClearFlagStatus(USART3_BASE_REG, USART_SR_U32_TC_MASK);
		
		if(USART_Info[USART3].DMA_TxState == DMA_DISABLED)
		{
			/* Transmission is still on-going */
			if(USART_Info[USART3].txBuffer.position != USART_Info[USART3].txBuffer.size)
			{
				
				USART_u8SendByte(USART_Info[USART3].USART_BaseRegister, USART_Info[USART3].txBuffer.ptr[USART_Info[USART3].txBuffer.position]);
				USART_Info[USART3].txBuffer.position++;			
			}
			/* Transmission is done */
			else
			{
				USART_Info[USART3].txBuffer.ptr = NULL;
				USART_Info[USART3].txBuffer.position = 0;
				USART_Info[USART3].txBuffer.size = 0;
				USART_Info[USART3].txBuffer.state = STATUS_IDLE;
				if(USART_Info[USART3].appTxNotify)
					USART_Info[USART3].appTxNotify();
			}
		}
	}
}

