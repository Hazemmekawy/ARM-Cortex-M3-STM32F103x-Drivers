#ifndef USART_H
#define USART_H

/* Creating the pointers for each USART */
#define USART1_BASE_REG		(void*)0x40013800
#define USART2_BASE_REG		(void*)0x40004400
#define USART3_BASE_REG		(void*)0x40004800

#define 	IS_USART_BASE_VALID(USART) 	(((USART) == USART1_BASE_REG) 	|| \
										((USART) == USART2_BASE_REG) 	|| \
										((USART) == USART3_BASE_REG))
										
#define 	NUMBER_OF_USARTs	3
		
#define 	USART1			0
#define 	USART2			1
#define 	USART3			2

#define 	IS_USART_VALID(USART) 		(((USART) == USART1) 	|| \
										((USART) == USART2) 	|| \
										((USART) == USART3))
									
/* Synchronization configuration macros */
#define ASYNCHRONOUS	0x0
#define SYNCHRONOUS		0x1

/* Baudrate configuration macros */
#define	BAUD_2400       (f32)937.5
#define	BAUD_9600       (f32)234.375
#define	BAUD_19200      (f32)117.1875
#define	BAUD_57600      (f32)39.0625
#define	BAUD_115200     (f32)19.5

/* Parity bits configuration macros */
#define STOP_BITS_1 	0x0
#define STOP_BITS_0_5   0x1
#define STOP_BITS_2     0x2
#define STOP_BITS_1_5	0x3

/* Parity bits configuration macros */
#define NO_PARITY		0x0
#define EVEN_PARITY     0x1
#define ODD_PARITY		0x2

/* Channel direction configuration macros */
#define FULL_DUPLEX		0x0
#define HALF_DUPLEX		0x1
#define SIMPLEX_T		0x2
#define SIMPLEX_R		0x3

/* DMA enable configuration macros */
#define DMA_DISABLED	0x0
#define DMA_ENABLED		0x1

/* LIN enable configuration macros */
#define LIN_DISABLED	0x0
#define LIN_ENABLED		0x1
	
/* Status register (USART_SR) masks */
#define USART_SR_U32_PE_MASK			(u32)0x00000001	 /* Parity error */
#define USART_SR_U32_FE_MASK    		(u32)0x00000002  /* Framing error */
#define USART_SR_U32_NE_MASK    		(u32)0x00000004  /* Noise error flag */
#define USART_SR_U32_ORE_MASK   		(u32)0x00000008  /* Overrun error */
#define USART_SR_U32_IDLE_MASK  		(u32)0x00000010  /* IDLE line detected */
#define USART_SR_U32_RXNE_MASK  		(u32)0x00000020  /* Read data register not empty */
#define USART_SR_U32_TC_MASK    		(u32)0x00000040  /* Transmission complete */
#define USART_SR_U32_TXE_MASK   		(u32)0x00000080  /* Transmit data register empty */
#define USART_SR_U32_LBD_MASK   		(u32)0x00000100  /* LIN break detection flag */
#define USART_SR_U32_CTS_MASK   		(u32)0x00000200  /* CTS flag */

/* Control register 1 (USART_CR1) masks */
#define USART_CR1_U32_SBK_MASK			(u32)0x00000001	 /* Send break */
#define USART_CR1_U32_RWU_MASK      	(u32)0x00000002  /* Receiver wakeup */
#define USART_CR1_U32_RE_MASK       	(u32)0x00000004  /* Receiver enable */
#define USART_CR1_U32_TE_MASK       	(u32)0x00000008  /* Transmitter enable */
#define USART_CR1_U32_IDLEIE_MASK   	(u32)0x00000010  /* IDLE interrupt enable */
#define USART_CR1_U32_RXNEIE_MASK   	(u32)0x00000020  /* RXNE interrupt enable */
#define USART_CR1_U32_TCIE_MASK     	(u32)0x00000040  /* Transmission complete interrupt enable */
#define USART_CR1_U32_TXEIE_MASK    	(u32)0x00000080  /* TXE interrupt enable */
#define USART_CR1_U32_PEIE_MASK     	(u32)0x00000100  /* PE interrupt enable */
#define USART_CR1_U32_PS_MASK       	(u32)0x00000200  /* Parity selection */
#define USART_CR1_U32_PCE_MASK      	(u32)0x00000400  /* Parity control enable */
#define USART_CR1_U32_WAKE_MASK     	(u32)0x00000800  /* Wakeup method */
#define USART_CR1_U32_M_MASK        	(u32)0x00001000  /* Word length */
#define USART_CR1_U32_UE_MASK       	(u32)0x00002000  /* USART enable */

/* Control register 2 (USART_CR2) masks */
//#define USART_CR2_U32_ADD_MASK
#define USART_CR2_U32_ADD_CLR_MASK		(u32)0xFFFFFFF0	 /* Address of the USART node */

#define USART_CR2_U32_LBDL_MASK     	(u32)0x00000020  /* LIN break detetion length */
#define USART_CR2_U32_LBDIE_MASK    	(u32)0x00000040  /* LIN break detection interrupt enable */
#define USART_CR2_U32_LBCL_MASK     	(u32)0x00000100  /* Last bit clock pulse */
#define USART_CR2_U32_CPHA_MASK     	(u32)0x00000200  /* Clock phase */
#define USART_CR2_U32_CPOL_MASK     	(u32)0x00000400  /* Clock polarity */
#define USART_CR2_U32_CLKEN_MASK    	(u32)0x00000800  /* Clock enable */
  
#define USART_CR2_U32_STOP_1_MASK     	(u32)0x00000000  /* 1 STOP bits */
#define USART_CR2_U32_STOP_0_5_MASK     (u32)0x00001000  /* 0.5 STOP bits */
#define USART_CR2_U32_STOP_2_MASK     	(u32)0x00002000  /* 2 STOP bits */
#define USART_CR2_U32_STOP_1_5_MASK    	(u32)0x00003000  /* 1.5 STOP bits */
#define USART_CR2_U32_STOP_CLR_MASK		(u32)0xFFFF3FFF  /* clear STOP bits */

#define USART_CR2_U32_LINEN_MASK		(u32)0x00004000  /* LIN enable mode */

/* Control register 1 (USART_CR3) masks */
#define USART_CR3_U32_EIE_MASK			(u32)0x00000001	 /* Error interrupt enable */
#define USART_CR3_U32_IREN_MASK			(u32)0x00000002  /* IrDA mode enable */
#define USART_CR3_U32_IRLP_MASK			(u32)0x00000004  /* IrDA low-power */
#define USART_CR3_U32_HDSEL_MASK		(u32)0x00000008	 /* Half-duplex selection */
#define USART_CR3_U32_NACK_MASK			(u32)0x00000010  /* Smartcard NACK enable */
#define USART_CR3_U32_SCEN_MASK			(u32)0x00000020  /* Smartcard mode enable */
#define USART_CR3_U32_DMAR_MASK			(u32)0x00000040  /* DMA enable receiver */
#define USART_CR3_U32_DMAT_MASK			(u32)0x00000080  /* DMA enable transmitter */
#define USART_CR3_U32_RTSE_MASK			(u32)0x00000100  /* RTS enable */
#define USART_CR3_U32_CTSE_MASK			(u32)0x00000200  /* CTS enable */
#define USART_CR3_U32_CTSIE_MASK		(u32)0x00000400	 /* CTS interrupt enable */

typedef struct
{
	f32 baudRate;
	u8 mode;
	u8 stopBits;
	u8 parityBits;
	u8 channelDirection;
	u8 enableRxDMA;
	u8 enableTxDMA;
	u8 enableLIN;
	
}USART_cfgStruct_t;


extern STD_STATUS USART_u8Init(u8 USARTx, f32 Copy_f32BUS_Clk_MHZ);
extern STD_STATUS USART_u8DefaultInit(u8 USARTx, f32 Copy_f32BUS_Clk_MHZ);
extern STD_STATUS USART_u8Configure(u8 USARTx, USART_cfgStruct_t *USART_cfgStruct, f32 Copy_f32BUS_Clk_MHZ);
extern STD_STATUS USART_u8SendData(u8 USARTx, u8 *Copy_pu8Buffer, u16 Copy_u16BytesCount);
extern STD_STATUS USART_u8ReceiveData(u8 USARTx, u8 *Copy_u8Buffer, u16 Copy_u16Length)
extern STD_STATUS USART_u8SetTxCallbackFn(u8 USARTx, callBackFn_t txCbf);
extern STD_STATUS USART_u8SetRxCallbackFn(u8 USARTx, callBackFn_t rxCbf);
extern STD_STATUS USART_u8GetFlagStatus(u8 USARTx, u32 Copy_u32FlagMask, u32 *Copy_pu32StatusReturn);
extern STD_STATUS USART_u8ClearFlagStatus(u8 USARTx, u32 Copy_u32FlagMask);
extern STD_STATUS USART_u8SendByte(u8 USARTx, u8 Copy_u8Byte);
extern STD_STATUS USART_u8ReceiveByte(u8 USARTx, u8 *Copy_pu8ByteReturn);
extern STD_STATUS USART_u8GenerateBreak(u8 USARTx);
extern STD_STATUS USART_u8EnableTxDMA(u8 USARTx);
extern STD_STATUS USART_u8DisableTxDMA(u8 USARTx);
extern STD_STATUS USART_u8EnableRxDMA(u8 USARTx);
extern STD_STATUS USART_u8DisableRxDMA(u8 USARTx);

#endif /* USART_H */
