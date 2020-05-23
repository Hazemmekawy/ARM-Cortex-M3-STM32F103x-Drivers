/************************************************************/
/*                                                          */
/*        Author	:	AHMED ZOHER	& WALEED ADEL & Hazem   */
/*        Version	: 	V01				                    */
/*        Date		:	14 Mar 2020		                    */
/*                                                          */
/************************************************************/

/************************************************************/
/****************** HEADER-FILES INCLUSION ******************/
/************************************************************/
#include <STD_TYPES.h>
#include <dFLASH.h>





/************************************************************/
/******************** TYPES DEFINITIONS *********************/
/************************************************************/

typedef struct
{
  u32 ACR;
  u32 KEYR;
  u32 OPTKEYR;
  u32 SR;
  u32 CR;
  u32 AR;
  u32 RESERVED;
  u32 OBR;
  u32 WRPR;
} FLASH_t;

/************************************************************/
/************************** MACROS **************************/
/************************************************************/

#define FLASH_BASE_ADDRESS       ((u32)0x40022000)
#define FLASH                ((volatile FLASH_t *) (FLASH_BASE_ADDRESS))

#define FLASH_KEY1           ((u32)0x45670123)
#define FLASH_KEY2           ((u32)0xCDEF89AB)


#define CR_PG_MASK           ((u32)0x00000001)
#define CR_PER_MASK          ((u32)0x00000002)
#define CR_MER_MASK          ((u32)0x00000004)
#define CR_STRT_MASK         ((u32)0x00000040)
#define CR_LOCK_MASK         ((u32)0x00000080)

#define SR_BSY_MASK          ((u32)0x00000001)
#define SR_EOP_MASK          ((u32)0x00000020)

/************************************************************/
/************************* VARIABLES ************************/
/************************************************************/



/************************************************************/
/****************** FUNCTION DECLARATIONS *******************/
/************************************************************/


/* Description: This API shall wite a word in the flash     */
/* Input  => u32 data => data to be written                 */
/*           void * Address => address to write             */
/* Output => void                                           */
void dFLASH_writeWord(void * Address, u32 data){
	while((FLASH->SR & SR_BSY_MASK)) ;
	/* Setting Page write trigger bit */
	FLASH->CR          |= CR_PG_MASK ;
	/* Writing first halfworld in the user-defined address */
	*((u16 *)Address)   = *(((u16 *)&data)) ;
	while((FLASH->SR & SR_BSY_MASK)) ;
	/* Writing Second halfworld in the user-defined address */
	FLASH->SR          &= (~SR_EOP_MASK) ;
	*((u16 *)Address+1) = *(((u16 *)&data)+1) ;
	while((FLASH->SR & SR_BSY_MASK)) ;
	/* Clearing the Page program flag */
	FLASH->CR          &= (~CR_PG_MASK) ;
}


/* Description: This API shall wite a word in the flash     */
/* Input  => u32 data => address data to be written         */
/*           void * Address => address to write             */
/*           u16 NumberOfBytes => number of bytes           */
/* Output => void                                           */
void dFLASH_programWrite(void* startAddress, void* dataAddress, u16 NumberOfBytes){
	while((FLASH->SR & SR_BSY_MASK)) ;
	/* Setting Page write trigger bit */
	FLASH->CR          |= CR_PG_MASK ;
	for (u16 loopCounter = 0 ; loopCounter < (NumberOfBytes/2) ; loopCounter++){
		/* Writing halfworld by half world in the user-defined address */
		*(((u16 *)startAddress)+loopCounter)   = *(((u16 *)dataAddress)+loopCounter) ;
		while((FLASH->SR & SR_BSY_MASK)) ;
		/* Clearing the End operation flag */
		FLASH->SR          &= (~SR_EOP_MASK) ;
	}
	while((FLASH->SR & SR_BSY_MASK)) ;
	/* Clearing the Page program flag */
	FLASH->CR          &= (~CR_PG_MASK) ;
}


/* Description: This API shall erase a page in the flash    */
/* Input  => u32 pageAddress => any adress in the required  */
/*                              page                        */
/* Output => void                                           */
void dFLASH_erasePage(u32 pageAddress){
	while((FLASH->SR & SR_BSY_MASK)) ;
	/* Setting Page erase trigger bit */
	FLASH->CR |= CR_PER_MASK ;
	FLASH->AR  = pageAddress ;
	/* Setting the start operation trigger bit */
	FLASH->CR |= CR_STRT_MASK ;
	while((FLASH->SR & SR_BSY_MASK));
	/* Clearing the Page erase flag */
	FLASH->CR          &= (~CR_PER_MASK) ;
}


/* Description: This API shall Erase the whole FLASH        */
/* Input  => void                                           */
/* Output => void                                           */
void dFLASH_eraseMass(void){
	while((FLASH->SR & SR_BSY_MASK)) ;
	/* Setting Mass erase trigger bit */
	FLASH->CR |= CR_MER_MASK ;
	/* Setting the start operation trigger bit */
	FLASH->CR |= CR_STRT_MASK ;
	while((FLASH->SR & SR_BSY_MASK)) ;
	/* Clearing the Mass erase flag */
	FLASH->CR &= (~CR_MER_MASK) ;
}


/* Description: This API shall unlock the FLASH             */
/* Input  => void                                           */
/* Output => void                                           */
void dFLASH_unlock(void){
	while((FLASH->SR & SR_BSY_MASK)) ;
	/* Applying Key 1 to the KEY register */
	FLASH->KEYR = FLASH_KEY1 ;
	/* Applying Key 2 to the KEY register */
	FLASH->KEYR = FLASH_KEY2 ;
}


/* Description: This API shall Lock the FLASH               */
/* Input  => void                                           */
/* Output => void                                           */
void dFLASH_lock(void){
	while((FLASH->SR & SR_BSY_MASK)) ;
	/* Setting the lock bit */
	FLASH->CR |= CR_LOCK_MASK ;
}
