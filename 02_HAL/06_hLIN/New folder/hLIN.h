/************************************************************/
/*                                                          */
/*        Author	:	AHMED ZOHER	& WALEED ADEL           */
/*        Version	: 	V01				                    */
/*        Date		:	14 Mar 2020		                    */
/*                                                          */
/************************************************************/


/************************************************************/
/*********************** HEADER GUARD ***********************/
/************************************************************/
#ifndef hLIN_H
#define hLIN_H

/************************************************************/
/************************** MACROS **************************/
/************************************************************/
#include "hLIN_Config.h"

/************************************************************/
/************************** MACROS **************************/
/************************************************************/

#define NODE_TYPE_MASTER        0
#define NODE_TYPE_SLAVE         1

#define CHECKSUM_MODE_CLASSIC   0
#define CHECKSUM_MODE_ENHANCED  1

#define SENDER                 (0)
#define RECEIVER               (1)
#define IGNORE                 (2)


/************************************************************/
/******************** TYPES DEFINITIONS *********************/
/************************************************************/

typedef struct	{
	u8 Node_ID ;
	u8 NodeStatus;
}NodeState_t;

typedef struct {
	u8 Time_ms;
	NodeState_t NodeStates[NumberOfNodes];
	u8 messageID;
	u8 messageSize;
}Message_t;

typedef struct {
	u8 NodeType;
	u8 USARTx;
	u8 Node_ID;
}Node_t;


/************************************************************/
/****************** VARIABLES DECLARATIONS ******************/
/************************************************************/




/************************************************************/
/****************** FUNCTION DECLARATIONS *******************/
/************************************************************/


/* Description: This API shall Initialize LIN Module        */
/* Input  => void                                           */
/* Output => void                                           */
extern void hLIN_Init(void);

/* Description: This API shall Set each MSG with the desied */
/* 			    Data to be transmitted                      */
/* Input  => u8 MsgID => Desired msg ID from comm matrix    */
/* 		  => u8 * MsgBuffer => Desired msg Data             */
/* Output => void                                           */
extern void hLIN_SetTxData(u8 MsgID , u8 * MsgBuffer);

#endif

