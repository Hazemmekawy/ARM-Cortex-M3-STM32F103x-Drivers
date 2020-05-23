#ifndef HUSART_H
#define HUSART_H

#include "USART.h"

#define 	CFG_DEFAULT		0
#define		CFG_DEFINED		1


#define 	IS_CFG_OPTION_VALID(OPTION)	(((OPTION) == CFG_DEFAULT) 	|| \
										((OPTION) == CFG_DEFINED))


extern STD_STATUS hUSART_u8Init(u8 USARTx, u8 Copy_u8CfgOption);
extern STD_STATUS hUSART_u8EnableTxDMA(u8 USARTx);
extern STD_STATUS hUSART_u8DisableTxDMA(u8 USARTx);
extern STD_STATUS hUSART_u8EnableRxDMA(u8 USARTx);
extern STD_STATUS hUSART_u8DisableRxDMA(u8 USARTx);
extern STD_STATUS hUSART_u8ConfigureTxDMA(u8 USARTx, DMAChannel_cfgStruct_t *DMAChannel_cfgStruct);
extern STD_STATUS hUSART_u8ConfigureRxDMA(u8 USARTx, DMAChannel_cfgStruct_t *DMAChannel_cfgStruct);
extern STD_STATUS hUSART_u8Configure(u8 USARTx, USART_cfgStruct_t *USART_cfgStruct);
extern STD_STATUS hUSART_u8SendData(u8 USARTx, u8 *Copy_pu8Buffer, u16 Copy_u16BytesCount);
extern STD_STATUS hUSART_u8ReceiveData(u8 USARTx, u8 *Copy_u8Buffer, u16 Copy_u16Length);
extern STD_STATUS hUSART_u8SetTxCallbackFn(u8 USARTx, callBackFn_t txCbf);
extern STD_STATUS hUSART_u8SetRxCallbackFn(u8 USARTx, callBackFn_t rxCbf);
extern STD_STATUS hUSART_u8GenerateBreak(u8 USARTx);

#endif /* HUSART_H */
