/************************************************************/
/*                                                          */
/*        Author	:	AHMED ZOHER	& WALEED ADEL & Hazem   */
/*        Version	: 	V01				                    */
/*        Date		:	14 Mar 2020		                    */
/*                                                          */
/************************************************************/


/************************************************************/
/*********************** HEADER GUARD ***********************/
/************************************************************/
#ifndef dFLASH_H
#define dFLASH_H

/************************************************************/
/************************** MACROS **************************/
/************************************************************/


/************************************************************/
/******************** TYPES DEFINITIONS *********************/
/************************************************************/




/************************************************************/
/****************** VARIABLES DECLARATIONS ******************/
/************************************************************/



/************************************************************/
/****************** FUNCTION DECLARATIONS *******************/
/************************************************************/

/* Description: This API shall wite a word in the flash     */
/* Input  => u32 data => data to be written                 */
/*           void * Address => address to write             */
/* Output => void                                           */
extern void dFLASH_writeWord(void * Address, u32 data);

/* Description: This API shall wite a word in the flash     */
/* Input  => u32 data => address data to be written         */
/*           void * Address => address to write             */
/*           u16 NumberOfBytes => number of bytes           */
/* Output => void                                           */
extern void dFLASH_programWrite(void* startAddress, void* dataAddress, u16 NumberOfBytes);

/* Description: This API shall erase a page in the flash    */
/* Input  => u32 pageAddress => any adress in the required  */
/*                              page                        */
/* Output => void                                           */
extern void dFLASH_erasePage(u32 pageAddress);

/* Description: This API shall Erase the whole FLASH        */
/* Input  => void                                           */
/* Output => void                                           */
extern void dFLASH_eraseMass(void);

/* Description: This API shall unlock the FLASH             */
/* Input  => void                                           */
/* Output => void                                           */
extern void dFLASH_unlock(void);

/* Description: This API shall Lock the FLASH               */
/* Input  => void                                           */
/* Output => void                                           */
extern void dFLASH_lock(void);

#endif

