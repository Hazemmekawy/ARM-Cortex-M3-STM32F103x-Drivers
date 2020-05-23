/**
 *  @file FLASH.h
 *  @author Hazem Mekawy
 *  @brief STM32F103x Flash Driver header file
 *  @module Flash Driver
 *  @layer MCAL
 */
 
#ifndef FLASH_H
#define FLASH_H


/* 
	Description: This API shall wite a word in the flash 
	Input  => u32 data => data to be written             
			void * Address => address to write         
	Output => void  
*/

extern void FLASH_writeWord(void * Address, u32 data);

/* 
	Description: This API shall wite a word in the flash 
	Input  => u32 data => address data to be written     
			void * Address => address to write         
			u16 NumberOfBytes => number of bytes       
	Output => void 
*/
extern void FLASH_programWrite(void* startAddress, void* dataAddress, u16 NumberOfBytes);

/* 
	Description: This API shall erase a page in the flash   
	Input  => u32 pageAddress => any adress in the required page                       
	Output => void       
*/ 
extern void FLASH_erasePage(u32 pageAddress);

/* 
	Description: This API shall Erase the whole FLASH
	Input  => void                                   
	Output => void     
*/           
extern void FLASH_eraseMass(void);

/* 
	Description: This API shall unlock the FLASH
	Input  => void                              
	Output => void       
*/         
extern void FLASH_unlock(void);

/* 
	Description: This API shall Lock the FLASH
	Input  => void                            
	Output => void         
*/                   
extern void FLASH_lock(void);

#endif /* FLASH_H */
