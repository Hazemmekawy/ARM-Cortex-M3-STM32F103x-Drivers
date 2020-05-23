#ifndef HUSART_CFG_H
#define HUSART_CFG_H


/* USART1 DMA configurations */
/* USART1 DMA channel enable */
#define USART1_TX_DMA_CHANNEL_EN			DMA_CHANNEL_DISABLED
#define USART1_RX_DMA_CHANNEL_EN			DMA_CHANNEL_DISABLED

/* USART1 DMA Tx channel configurations */
#define USART1_TX_DMA_CHANNEL_MEM2MEM					MEM2MEM_DISABLED
#define USART1_TX_DMA_CHANNEL_PRI_LEVEL		            CH_PRI_LOW
#define USART1_TX_DMA_CHANNEL_MEM_SIZE			        MSIZE_BITS_8
#define USART1_TX_DMA_CHANNEL_PERIPH_SIZE		        PSIZE_BITS_8
#define USART1_TX_DMA_CHANNEL_MEM_INC	                MINC_DISABLED
#define USART1_TX_DMA_CHANNEL_PERIPH_INC                PINC_DISABLED
#define USART1_TX_DMA_CHANNEL_CIRC		                CIRC_DISABLED
#define USART1_TX_DMA_CHANNEL_DATA_DIRECTION		    READ_FROM_PERIPH
#define USART1_TX_DMA_CHANNEL_HALF_TRANSFER_MODE	    HALF_TRANSFER_DISABLED

/* USART1 DMA Rx channel configurations */
#define USART1_RX_DMA_CHANNEL_MEM2MEM					MEM2MEM_DISABLED
#define USART1_RX_DMA_CHANNEL_PRI_LEVEL		            CH_PRI_LOW
#define USART1_RX_DMA_CHANNEL_MEM_SIZE			        MSIZE_BITS_8
#define USART1_RX_DMA_CHANNEL_PERIPH_SIZE		        PSIZE_BITS_8
#define USART1_RX_DMA_CHANNEL_MEM_INC	                MINC_DISABLED
#define USART1_RX_DMA_CHANNEL_PERIPH_INC                PINC_DISABLED
#define USART1_RX_DMA_CHANNEL_CIRC		                CIRC_DISABLED
#define USART1_RX_DMA_CHANNEL_DATA_DIRECTION		    READ_FROM_PERIPH
#define USART1_RX_DMA_CHANNEL_HALF_TRANSFER_MODE	    HALF_TRANSFER_DISABLED


/* USART2 DMA configurations */
/* USART2 DMA channel enable */
#define USART2_TX_DMA_CHANNEL_EN			DMA_CHANNEL_DISABLED
#define USART2_RX_DMA_CHANNEL_EN			DMA_CHANNEL_DISABLED

/* USART2 DMA Tx channel configurations */
#define USART2_TX_DMA_CHANNEL_MEM2MEM					MEM2MEM_DISABLED
#define USART2_TX_DMA_CHANNEL_PRI_LEVEL		            CH_PRI_LOW
#define USART2_TX_DMA_CHANNEL_MEM_SIZE			        MSIZE_BITS_8
#define USART2_TX_DMA_CHANNEL_PERIPH_SIZE		        PSIZE_BITS_8
#define USART2_TX_DMA_CHANNEL_MEM_INC	                MINC_DISABLED
#define USART2_TX_DMA_CHANNEL_PERIPH_INC                PINC_DISABLED
#define USART2_TX_DMA_CHANNEL_CIRC		                CIRC_DISABLED
#define USART2_TX_DMA_CHANNEL_DATA_DIRECTION		    READ_FROM_MEM
#define USART2_TX_DMA_CHANNEL_HALF_TRANSFER_MODE	    HALF_TRANSFER_DISABLED

/* USART2 DMA Rx channel configurations */
#define USART2_RX_DMA_CHANNEL_MEM2MEM					MEM2MEM_DISABLED
#define USART2_RX_DMA_CHANNEL_PRI_LEVEL		            CH_PRI_LOW
#define USART2_RX_DMA_CHANNEL_MEM_SIZE			        MSIZE_BITS_8
#define USART2_RX_DMA_CHANNEL_PERIPH_SIZE		        PSIZE_BITS_8
#define USART2_RX_DMA_CHANNEL_MEM_INC	                MINC_DISABLED
#define USART2_RX_DMA_CHANNEL_PERIPH_INC                PINC_DISABLED
#define USART2_RX_DMA_CHANNEL_CIRC		                CIRC_DISABLED
#define USART2_RX_DMA_CHANNEL_DATA_DIRECTION		    READ_FROM_PERIPH
#define USART2_RX_DMA_CHANNEL_HALF_TRANSFER_MODE	    HALF_TRANSFER_DISABLED


/* USART3 DMA configurations */
/* USART3 DMA channel enable */
#define USART3_TX_DMA_CHANNEL_EN			DMA_CHANNEL_DISABLED
#define USART3_RX_DMA_CHANNEL_EN			DMA_CHANNEL_DISABLED

/* USART3 DMA Tx channel configurations */
#define USART3_TX_DMA_CHANNEL_MEM2MEM					MEM2MEM_DISABLED
#define USART3_TX_DMA_CHANNEL_PRI_LEVEL		            CH_PRI_LOW
#define USART3_TX_DMA_CHANNEL_MEM_SIZE			        MSIZE_BITS_8
#define USART3_TX_DMA_CHANNEL_PERIPH_SIZE		        PSIZE_BITS_8
#define USART3_TX_DMA_CHANNEL_MEM_INC	                MINC_DISABLED
#define USART3_TX_DMA_CHANNEL_PERIPH_INC                PINC_DISABLED
#define USART3_TX_DMA_CHANNEL_CIRC		                CIRC_DISABLED
#define USART3_TX_DMA_CHANNEL_DATA_DIRECTION		    READ_FROM_PERIPH
#define USART3_TX_DMA_CHANNEL_HALF_TRANSFER_MODE	    HALF_TRANSFER_DISABLED

/* USART3 DMA Rx channel configurations */
#define USART3_RX_DMA_CHANNEL_MEM2MEM					MEM2MEM_DISABLED
#define USART3_RX_DMA_CHANNEL_PRI_LEVEL		            CH_PRI_LOW
#define USART3_RX_DMA_CHANNEL_MEM_SIZE			        MSIZE_BITS_8
#define USART3_RX_DMA_CHANNEL_PERIPH_SIZE		        PSIZE_BITS_8
#define USART3_RX_DMA_CHANNEL_MEM_INC	                MINC_DISABLED
#define USART3_RX_DMA_CHANNEL_PERIPH_INC                PINC_DISABLED
#define USART3_RX_DMA_CHANNEL_CIRC		                CIRC_DISABLED
#define USART3_RX_DMA_CHANNEL_DATA_DIRECTION		    READ_FROM_PERIPH
#define USART3_RX_DMA_CHANNEL_HALF_TRANSFER_MODE	    HALF_TRANSFER_DISABLED

#endif /* HUSART_CFG_H */