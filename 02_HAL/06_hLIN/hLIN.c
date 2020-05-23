#include "STD_TYPES.h"
#include "SCHEDULER.h"
#include "USART.h"

#include "hLIN.h"

/************************************************************/
/************************** MACROS **************************/
/************************************************************/

#define DATA_SIZE               (8)
#define HEADER_SIZE             (2)
#define CHECKSUM_SIZE           (1)
#define SYNC_BYTE               (0x55)

#define GET_BIT(VAR, BIT_NO)	((VAR>>BIT_NO)&1)
#define CALC_PID_P0(Data)       (((GET_BIT(Data, 0)^GET_BIT(Data, 1))^(GET_BIT(Data, 2)^GET_BIT(Data, 4)))^0)
#define CALC_PID_P1(Data)       (((GET_BIT(Data, 1)^GET_BIT(Data, 3))^(GET_BIT(Data, 4)^GET_BIT(Data, 5)))^1)

/************************************************************/
/******************** TYPES DEFINITIONS *********************/
/************************************************************/

typedef struct 
{
	u8 SyncByte;
	u8 PID;
}HeaderFrame_t;

typedef struct 
{
	u8 Data[DATA_SIZE];
	u8 Checksum;
}ResponseFrame_t;

typedef struct 
{
	HeaderFrame_t   HeaderFrame;
	ResponseFrame_t ResponseFrame;
}LIN_Frame_t;

/************************************************************/
/************************** Externs *************************/
/************************************************************/

extern const Message_t CommMatrix[3];
extern const Node_t Node;

/************************************************************/
/******************** FUNCTION DECLARATION ******************/
/************************************************************/

void hLIN_MainTask(void);
static u8 LIN_u8CalculateChecksum(u8* pu8Array, u8 Copy_u8ArraySize)
static u8 LIN_u8CalculatePID(u8 Copy_u8MsgID);

/************************************************************/
/****************** VARIABLES DEFINITION ********************/
/************************************************************/

/* State machine flags to be updated by the call-back functions*/
static u8 HeaderTransmitted = 0;
static u8 HeaderReceived = 0;
static u8 BreakDetected = 0;
/* Static counter to keep track of the current message in the Comm Matrix to be transmitted */
static u8 CommMatrixMsgCounter = 0;

static LIN_Frame_t TransmittedFrames [NumberOfMsgs];
static LIN_Frame_t ReceivedFrames [NumberOfMsgs];

const Task_t LIN_Task = {.Runnable = &hLIN_vMainTask, .PeriodicityUS = 5000};


/************************************************************/
/****************** FUNCTION DEFINITION *********************/
/************************************************************/

/* 
/* Description: This API shall Set each MSG with the desied 
/* 			    Data to be transmitted                      
/* Input  => u8 Copy_u8MsgID => Desired msg ID from comm matrix    
/* 		  => u8 * Copy_pu8MsgBuffer => Desired msg Data             
/* Output => void     
*/                                      
void hLIN_vSetTxData(u8 Copy_u8MsgID , u8* Copy_pu8MsgBuffer)
{
	/* Searching for the intended Copy_u8MsgID in the comm matrix */
	for (u8 local_u8Iterator = 0; local_u8Iterator < NumberOfMsgs; local_u8Iterator++)
	{
		/* Once the msg ID is found the data are copied in the response frame related to the Copy_u8MsgID */
		if ( Copy_u8MsgID == CommMatrix[local_u8Iterator].messageID )
		{
			for ( u8 local_u8DataIndex = 0 ; local_u8DataIndex < CommMatrix[local_u8Iterator].messageSize ; local_u8DataIndex++ )
				TransmittedFrames[local_u8Iterator].ResponseFrame.Data[data_index] = Copy_pu8MsgBuffer[data_index];
			break;
		}
	}
}

/* Description: USARTx Receive Data callback
/* Input  => void                           
/* Output => void       
*/                    
static void LIN_vRxCallBack(void)
{
	u8 local_u8Iterator = 0;
	u8 local_u8CS = 0;
	u8 local_u8CPID = 0;

	/* Printing the Header Frame that has been received */
	if (0 == HeaderReceived)
	{
		for (local_u8Iterator = 0; local_u8Iterator < HEADER_SIZE; local_u8Iterator++)
		{
			trace_printf("HeaderFrame   [%x] = %x \n",local_u8Iterator,((u8*)&ReceivedFrames[CommMatrixMsgCounter].HeaderFrame)[local_u8Iterator]);
		}
		/* Setting the header received flag with value one to be used by the state machine */
		HeaderReceived = 1 ;

		/* Checking the SyncByte */
		if( SYNC_BYTE == ReceivedFrames[CommMatrixMsgCounter].HeaderFrame.SyncByte )
		{
			trace_printf("Sync Byte VERIFIED\n");
		}
		else
		{
			trace_printf("Sync Byte ERROR!!!\n");
		}

		/* Checking the PID and compare the parity */
		local_u8CPID = LIN_u8CalculatePID(CommMatrix[CommMatrixMsgCounter].messageID);
		if( local_u8CPID == ReceivedFrames[CommMatrixMsgCounter].HeaderFrame.PID  )
		{
			trace_printf("PID VERIFIED\n");
		}
		else
		{
			trace_printf("PID ERROR!!!\n");
		}
	}
	else
	{
		/* Printing the Data Frame that has been received */
		ReceivedFrames[CommMatrixMsgCounter].ResponseFrame.Checksum = ReceivedFrames[CommMatrixMsgCounter].ResponseFrame.Data[CommMatrix[CommMatrixMsgCounter].messageSize];
		for (local_u8Iterator = 0; local_u8Iterator < CommMatrix[CommMatrixMsgCounter].messageSize; local_u8Iterator++)
		{
			trace_printf("RecievedFrame [%x] = %x \n",local_u8Iterator,ReceivedFrames[CommMatrixMsgCounter].ResponseFrame.Data[local_u8Iterator]);
		}
		trace_printf("RecievedFrame_CS  = %x \n",ReceivedFrames[CommMatrixMsgCounter].ResponseFrame.Checksum);

		/* Calculate the check sum and compare it with the received one and checking if it is classic or enhanced Checksum */
		#if   CHECKSUM_MODE == CHECKSUM_MODE_CLASSIC
			local_u8CS = LIN_u8CalculateChecksum(ReceivedFrames[CommMatrixMsgCounter].ResponseFrame.Data, CommMatrix[CommMatrixMsgCounter].messageSize) ;
		#elif CHECKSUM_MODE == CHECKSUM_MODE_ENHANCED
			local_u8CS = LIN_u8CalculateChecksum(ReceivedFrames[CommMatrixMsgCounter].HeaderFrame.PID, CommMatrix[CommMatrixMsgCounter].messageSize + CHECKSUM_SIZE) ;
		#endif
		local_u8CS = LIN_u8CalculateChecksum(ReceivedFrames[CommMatrixMsgCounter].ResponseFrame.Data, CommMatrix[CommMatrixMsgCounter].messageSize) ;

		if( local_u8CS == ReceivedFrames[CommMatrixMsgCounter].ResponseFrame.Checksum )
		{
			trace_printf("CheckSum VERIFIED\n");
		}
		else
		{
			trace_printf("CheckSum ERROR!!!\n");
		}
		/* Printing the end of the frame */
		trace_printf("---------------------------------------------------------------------------------- \n");

		/* Incrementing the message counter to take the next msg in the comm matrix*/
		CommMatrixMsgCounter++;
		if ( NumberOfMsgs == CommMatrixMsgCounter ){
			CommMatrixMsgCounter = 0;
		}

		/* clearing the header received flag to start another reception of the next frame */
		HeaderReceived = 0 ;
		if( 1 == HeaderTransmitted )
		{
			HeaderTransmitted = 0 ;
		}
	}
}

/* Description: USARTx Transmit Data callback               */
/* Input  => void                                           */
/* Output => void                                           */
static void LIN_vTxCallBack(void)
{

}

/* Description: USARTx Receive Break callback               */
/* Input  => void                                           */
/* Output => void                                           */
static void LIN_vLINCallBack(void)
{
	BreakDetected = 1;
}

/* Description: This API shall Initialize LIN Module        */
/* Input  => void                                           */
/* Output => void                                           */
void hLIN_vInit(void)
{
	/* setting the call back functions fo the USART transmission and reception of data or break */
	hUSART_SetRxCallBackFn(Node.USARTx, RxCallBack);
	hUSART_SetTxCallBackFn(Node.USARTx, TxCallBack);
	hUART_SetLIN_BreakCallBackFn(Node.USARTx, LINCallBack);
}

/* Description: This API Contains the state machine to be   */
/* 				called by the scheduler                     */
/* Input  => void                                           */
/* Output => void                                           */
void hLIN_vMainTask(void)
{
	/************************************************************************************************************************************/
	/******************************************************** Slave Routine *************************************************************/
	/************************************************************************************************************************************/

	/* State Machine: 3rd state ---> the Header frame has been trasmitted and the response is going to be transmitted */
	if ( 1 == HeaderReceived )
	{
		/* Checking if the node is the receiver or the sender of the current message */
		if ( RECEIVER == CommMatrix[CommMatrixMsgCounter].NodeStates[Node.Node_ID].NodeStatus )
		{
			hUSART_Receive(Node.USARTx , (u8 *) (&ReceivedFrames[CommMatrixMsgCounter].ResponseFrame), CommMatrix[CommMatrixMsgCounter].messageSize + CHECKSUM_SIZE);
		}
		else if ( SENDER == CommMatrix[CommMatrixMsgCounter].NodeStates[Node.Node_ID].NodeStatus )
		{
			/******* The next line is for testing on the same USART (connecting TX with RX on same peripheral) otherwise, it should be removed ******/
			hUSART_Receive(Node.USARTx , (u8 *) (&ReceivedFrames[CommMatrixMsgCounter].ResponseFrame), CommMatrix[CommMatrixMsgCounter].messageSize + CHECKSUM_SIZE); ///////////////////// TO BE REMOVED
			/* Calculating the checksum */
			#if   CHECKSUM_MODE == CHECKSUM_MODE_CLASSIC
				TransmittedFrames[CommMatrixMsgCounter].ResponseFrame.Data[CommMatrix[CommMatrixMsgCounter].messageSize] = LIN_u8CalculateChecksum((u8*)TransmittedFrames[CommMatrixMsgCounter].ResponseFrame.Data,CommMatrix[CommMatrixMsgCounter].messageSize) ;
			#elif CHECKSUM_MODE == CHECKSUM_MODE_ENHANCED
				TransmittedFrames[CommMatrixMsgCounter].ResponseFrame.Data[CommMatrix[CommMatrixMsgCounter].messageSize]  = LIN_u8CalculateChecksum((u8*)TransmittedFrames[CommMatrixMsgCounter].HeaderFrame.PID,CommMatrix[CommMatrixMsgCounter].messageSize + CHECKSUM_SIZE)
			#endif
			/* trasnmitting the message with the related checksum */
			hUSART_Send( Node.USARTx , (u8*) (&TransmittedFrames[CommMatrixMsgCounter].ResponseFrame) , CommMatrix[CommMatrixMsgCounter].messageSize + CHECKSUM_SIZE);
		}
	}

	/************************************************************************************************************************************/
	/******************************************************** Master Routine ************************************************************/
	/************************************************************************************************************************************/

	/* State Machine: 1st state ---> the break is going to be transmitted if the node is a master node*/
	if ( 0 == HeaderTransmitted )
	{
		if ( NODE_TYPE_MASTER == Node.NodeType) {
			/* calling the USART handler API to send a break signal */
			hUSART_SendLIN_Break(Node.USARTx);
			HeaderTransmitted = 1;
		}
	}

	/* State Machine: 2st state ---> the break has been transmitted and the Header frame is going to be transmitted */
	if ( 1 == BreakDetected )
	{
		/* The node has to receive the header even if it is a master node */
		hUSART_Receive(Node.USARTx ,(u8 *) (&ReceivedFrames[CommMatrixMsgCounter].HeaderFrame) , HEADER_SIZE);
		if (NODE_TYPE_MASTER == Node.NodeType)
		{
			/* if the node is master then the header frame is transmitted */
			TransmittedFrames[CommMatrixMsgCounter].HeaderFrame.SyncByte = SYNC_BYTE;
			TransmittedFrames[CommMatrixMsgCounter].HeaderFrame.PID = LIN_u8CalculatePID(CommMatrix[CommMatrixMsgCounter].messageID);
			hUSART_Send( Node.USARTx ,(u8 *)(&TransmittedFrames[CommMatrixMsgCounter].HeaderFrame),HEADER_SIZE);
		}
		BreakDetected = 0;
	}
}

static u8 LIN_u8CalculateChecksum(u8* pu8Array, u8 Copy_u8ArraySize)
{
	u8 local_u8Result = 0;
	
	/* Adding all the elements using 256-bit addition */
	for (u8 local_u8Iterator = 0; local_u8Iterator < Copy_u8ArraySize; local_u8Iterator++)
	{
		local_u8Result += pu8Array[local_u8Iterator];
	}
	/* Inverting the local_u8Result to get the CheckSum value */
	return (~local_u8Result);
}

static u8 LIN_u8CalculatePID(u8 Copy_u8MsgID)
{
	/* calculating the parity using predefined macros and inserting P0 and P1 in 6th and 7th bit position respectively */
	return ((CALC_PID_P1(Copy_u8MsgID)<<7)|(CALC_PID_P0(Copy_u8MsgID)<<6)|(Copy_u8MsgID));
}


