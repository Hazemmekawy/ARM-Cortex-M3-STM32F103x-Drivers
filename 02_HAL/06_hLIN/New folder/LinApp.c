
#include "STD_TYPES.h"
#include "lString.h"
#include "dRCC.h"
#include "dGPIO.h"
#include "dNVIC.h"
#include "dDMA.h"
#include "hUSART.h"
#include "hLIN.h"
#include "Scheduler.h"


USART_InitTypeDef init_struct = {.USART_BaudRate = 9600,
								 .USART_StopBits = USART_StopBits_1,
								 .USART_Parity = USART_Parity_No,
								 .USART_TxRxMode = USART_TxRxMode_Rx | USART_TxRxMode_Tx,
								 .USART_DMA_TxRxMode = USART_DMA_TxRxMode_Disable,
								 .USART_Mode = USART_Mode_Async,
								 .USART_LIN_Mode = USART_LIN_Mode_Enable_10_Bit,
								 .USART_LIN_Interrupt = USART_LIN_Interrupt_Enable};


u8 data1[] = {1,2,3,4,5};
u8 data2[] = {5,6,7};
u8 data3[] = {8,9};

// ----- main() ---------------------------------------------------------------


int
main(void)
{
	RCC_SetClockState(HSION_MASK,ON);
	RCC_SetSystemClock(HSI);
	RCC_SetPrephiralClockState(APB2,IOPAEN,ON);
	RCC_SetPrephiralClockState(APB2,IOPBEN,ON);
	RCC_SetPrephiralClockState(APB2,IOPCEN,ON);

	hUSART_Init(USART1,&init_struct);
	hLIN_Init();


	hLIN_SetTxData(0x21 , data1);
	hLIN_SetTxData(0x22 , data2);
	hLIN_SetTxData(0x23 , data3);

	Scheduler_Init();
	Scheduler_Start();
  while (1)
    {
       // Add your code here.
    }
  return 0;
}


// ----------------------------------------------------------------------------
