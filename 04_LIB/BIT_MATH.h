/******************************************************/
/*                                                    */
/*				Author: Hazem Mekawy                  */
/*				File Name: BIT_MATH.h          	      */
/*				Component: BIT_MATH                   */
/*				Layer: LIB                            */
/*				Version: 2.0                          */
/*                                                    */
/******************************************************/

#ifndef BIT_MATH_H
#define BIT_MATH_H

#define SET_BIT(VAR, BIT_NO)			(VAR |= (1<<BIT_NO))
#define CLR_BIT(VAR, BIT_NO)			(VAR &= ~(1<<BIT_NO))
#define TOGGLE_BIT(VAR, BIT_NO)			(VAR ^= (1<<BIT_NO))
#define GET_BIT(VAR, BIT_NO)			((VAR>>BIT_NO)&1)
#define ASSIGN_BIT(VAR, BIT_NO, VAL)	(VAR=(VAR&~(1<<BIT_NO)) | (VAL<<BIT_NO))

#endif /* BIT_MATH_H */