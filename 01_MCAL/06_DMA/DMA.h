#ifndef DMA_H
#define DMA_H

#define DMA_NUMBER_OF_CHANNELS		7

/* Channel number macros */
#define DMA_CHANNEL_1		0
#define DMA_CHANNEL_2		1
#define DMA_CHANNEL_3		2
#define DMA_CHANNEL_4		3
#define DMA_CHANNEL_5		4
#define DMA_CHANNEL_6		5
#define DMA_CHANNEL_7		6

/* Channel 1 */
#define DMA_ADC1			DMA_CHANNEL_1
#define DMA_TIM2_CH3    	DMA_CHANNEL_1
#define DMA_TIM4_CH1    	DMA_CHANNEL_1

/* Channel 2 */
#define DMA_USART3_TX		DMA_CHANNEL_2
#define DMA_TIM1_CH1    	DMA_CHANNEL_2
#define DMA_TIM2_UP     	DMA_CHANNEL_2
#define DMA_TIM3_CH3    	DMA_CHANNEL_2
#define DMA_SPI1_RX     	DMA_CHANNEL_2

/* Channel 3 */
#define DMA_USART3_RX		DMA_CHANNEL_3
#define DMA_TIM1_CH2    	DMA_CHANNEL_3
#define DMA_TIM3_CH4    	DMA_CHANNEL_3
#define DMA_TIM3_UP     	DMA_CHANNEL_3
#define DMA_SPI1_TX     	DMA_CHANNEL_3

/* Channel 4 */
#define DMA_USART1_TX		DMA_CHANNEL_4
#define DMA_TIM1_CH4        DMA_CHANNEL_4
#define DMA_TIM1_TRIG       DMA_CHANNEL_4
#define DMA_TIM1_COM        DMA_CHANNEL_4
#define DMA_TIM4_CH2        DMA_CHANNEL_4
#define DMA_SPI_I2S2_RX     DMA_CHANNEL_4
#define DMA_I2C2_TX         DMA_CHANNEL_4

/* Channel 5 */
#define DMA_USART1_RX		DMA_CHANNEL_5
#define DMA_TIM1_UP         DMA_CHANNEL_5
#define DMA_SPI_I2S2_TX     DMA_CHANNEL_5
#define DMA_TIM2_CH1        DMA_CHANNEL_5
#define DMA_TIM4_CH3        DMA_CHANNEL_5
#define DMA_I2C2_RX         DMA_CHANNEL_5

/* Channel 6 */
#define DMA_USART2_RX		DMA_CHANNEL_6
#define DMA_TIM1_CH3        DMA_CHANNEL_6
#define DMA_TIM3_CH1        DMA_CHANNEL_6
#define DMA_TIM3_TRIG       DMA_CHANNEL_6
#define DMA_I2C1_TX         DMA_CHANNEL_6

/* Channel 7 */
#define DMA_USART2_TX		DMA_CHANNEL_7	
#define DMA_TIM2_CH2        DMA_CHANNEL_7
#define DMA_TIM2_CH4        DMA_CHANNEL_7
#define DMA_TIM4_UP         DMA_CHANNEL_7
#define DMA_I2C1_RX         DMA_CHANNEL_7


#define 	DMA_CHANNEL_DISABLED	0
#define 	DMA_CHANNEL_ENABLED		1

#define IS_CHANNEL_VALID(CHANNEL)	((CHANNEL == DMA_CHANNEL_1) || \
									(CHANNEL == DMA_CHANNEL_2) || \
									(CHANNEL == DMA_CHANNEL_3) || \
									(CHANNEL == DMA_CHANNEL_4) || \
									(CHANNEL == DMA_CHANNEL_5) || \
									(CHANNEL == DMA_CHANNEL_6) || \
									(CHANNEL == DMA_CHANNEL_7))
									
/* Type of flag macros */
#define TRANSFER_INT_FLAG			0
#define HALF_TRANSFER_INT_FLAG		1
#define TRANSFER_COMPLETE_FLAG		2
#define GLOBAL_INT_FLAG				3

/* Channel configurations macros */
/* Channel memory to memory mode */
#define MEM2MEM_DISABLED	0
#define MEM2MEM_ENABLED		1

/* Channel half transfer mode */
#define HALF_TRANSFER_DISABLED		0
#define HALF_TRANSFER_ENABLED		1

/* Channel memory increment mode  */
#define MINC_DISABLED		0
#define MINC_ENABLED		1

/* Channel peripheral increment mode */
#define PINC_DISABLED		0
#define PINC_ENABLED		1

/* Channel circular mode */
#define CIRC_DISABLED		0
#define CIRC_ENABLED		1

/* Channel priority */
#define CH_PRI_LOW			0
#define CH_PRI_MEDIUM      	1
#define CH_PRI_HIGH        	2
#define CH_PRI_VERY_HIGH   	3

/* Channel memory size */
#define MSIZE_BITS_8		0
#define MSIZE_BITS_16		1
#define MSIZE_BITS_32		2

/* Channel peripheral size  */
#define PSIZE_BITS_8		0
#define PSIZE_BITS_16		1
#define PSIZE_BITS_32		2

/* Channel data transfer direction */
#define READ_FROM_PERIPH	0
#define READ_FROM_MEM		1


/* DMA registers macros */
/* DMA_ISR register macros */
#define DMA_ISR_U32_GIFx_MASK			0x00000001	/* Channel x transfer error flag */
#define DMA_ISR_U32_TCIFx_MASK    		0x00000002  /* Channel x half transfer flag */
#define DMA_ISR_U32_HTIFx_MASK    		0x00000004  /* Channel x transfer complete flag */
#define DMA_ISR_U32_TEIFx_MASK   		0x00000008  /* Channel x global interrupt flag */

/* DMA_IFCR register macros */
#define DMA_ISR_U32_CGIFx_MASK			0x00000001	/* Channel x transfer error flag clear */
#define DMA_ISR_U32_CTCIFx_MASK    		0x00000002  /* Channel x half transfer flag clear */
#define DMA_ISR_U32_CHTIFx_MASK    		0x00000004  /* Channel x transfer complete flag clear */
#define DMA_ISR_U32_CTEIFx_MASK   		0x00000008  /* Channel x global interrupt flag clear */

/* DMA_CCR register masks */
#define DMA_CCR_U32_MEM2MEM_MASK		0x00000000	/* Memory to memory mode */

#define DMA_CCR_U32_PL_LOW_MASK			0x00000000  /* Channel priority level - Low */
#define DMA_CCR_U32_PL_MEDIUM_MASK		0x00000000  /* Channel priority level - Medium */
#define DMA_CCR_U32_PL_HIGH_MASK		0x00000000  /* Channel priority level - High */
#define DMA_CCR_U32_PL_VERY_HIGH_MASK	0x00000000  /* Channel priority level - Very High */
#define DMA_CCR_U32_PL_CLR_MASK			0x00000000  /* Channel priority level - Clear */

#define DMA_CCR_U32_M_SIZE_8_MASK		0x00000000	/* Memory size - 8 */
#define DMA_CCR_U32_M_SIZE_16_MASK		0x00000000  /* Memory size - 16 */
#define DMA_CCR_U32_M_SIZE_32_MASK		0x00000000  /* Memory size - 32 */
#define DMA_CCR_U32_M_SIZE_CLR_MASK		0x00000000  /* Memory size - Clear */

#define DMA_CCR_U32_P_SIZE_8_MASK		0x00000000  /* Peripheral size - 8 */
#define DMA_CCR_U32_P_SIZE_16_MASK		0x00000000  /* Peripheral size - 16 */
#define DMA_CCR_U32_P_SIZE_32_MASK		0x00000000  /* Peripheral size - 32 */
#define DMA_CCR_U32_P_SIZE_CLR_MASK		0x00000000	/* Peripheral size - Clear */

#define DMA_CCR_U32_MINC_MASK			0x00000000	/* Memory increment mode */
#define DMA_CCR_U32_PINC_MASK			0x00000000  /* Peripheral increment mode */
#define DMA_CCR_U32_CIRC_MASK			0x00000000  /* Circular mode */
#define DMA_CCR_U32_DIR_MASK			0x00000000  /* Data transfer direction */
#define DMA_CCR_U32_TEIE_MASK			0x00000000  /* Transfer error interrupt enable */
#define DMA_CCR_U32_HTIE_MASK			0x00000000  /* Half transfer interrupt enable */
#define DMA_CCR_U32_TCIE_MASK			0x00000000  /* Transfer complete interrupt enable */
#define DMA_CCR_U32_EN_MASK				0x00000000  /* Channel enable */


typedef struct
{
	u8 MEM2MEM_mode;
	u8 priorityLevel;
	u8 memorySize;
	u8 peripheralSize;
	u8 memoryIncrement;
	u8 peripheralIncrement;
	u8 circularMode;
	u8 dataDirection;
	u8 halfTransferMode;
	
}DMAChannel_cfgStruct_t;



STD_STATUS DMA_u8ChannelInit(u8 Channelx);
STD_STATUS DMA_u8ChannelConfigure(u8 Channelx, DMAChannel_cfgStruct_t *DMAChannel_cfgStruct);
STD_STATUS DMA_u8StartTransfer(u8 Channelx, u32 Copy_u32SourceAddress, u32 Copy_u32DestinationAddress, u16 Copy_u32BlockSize);
STD_STATUS DMA_u8StopTransfer(u8 Channelx);
STD_STATUS DMA_u8ClearChannelFlag(u8 Channelx, u8 Copy_u8Flag);
STD_STATUS DMA_u8GetChannelFlag(u8 Channelx, u8 Copy_u8Flag, u8 *Copy_pu8FlagReturn);
STD_STATUS DMA_u8SetChannelCallbackFn(u8 Channelx, callbackFn_t channelCbf);

#endif /* DMA_H */
