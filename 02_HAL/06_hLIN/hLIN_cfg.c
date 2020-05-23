#include "STD_TYPES.h"
#include "hUSART.h"
#include "hLIN.h"


/* Node ID */
#define NODE_A          0x0
#define NODE_B          0x1


/* To be read from the LDF file */
const Message_t CommMatrix [NumberOfMsgs]={{.Time_ms = 10 , .NodeStates = {{NODE_A,SENDER  },{NODE_B,RECEIVER}}, .messageID = 0x21 ,.messageSize = 5},
                                           {.Time_ms = 10 , .NodeStates = {{NODE_A,SENDER  },{NODE_B,RECEIVER}}, .messageID = 0x22 ,.messageSize = 3},
                                           {.Time_ms = 10 , .NodeStates = {{NODE_A,SENDER  },{NODE_B,RECEIVER}}, .messageID = 0x23 ,.messageSize = 2}};

/* Master Node Example*/
/* Configure the node with a node ID, the USART peripheral number and the node TYPE */
const Node_t  Node = { .NodeType = NODE_TYPE_MASTER, .USARTx = USART1, .Node_ID = NODE_A };

/* Slave Node Example*/
#if 0
 Node_t Nodes = { .NodeType = NODE_TYPE_SLAVE, .USARTx = USART1, .Node_ID = 0x02 };
#endif


