/*
#define 	u8  	unsigned char
#define 	u16		unsigned short int
#define 	u32 	unsigned long int

#define 	s8 		signed char
#define 	s16		signed short int
#define 	s32 	signed long int

#define 	f32 	float
#define 	f64 	double
#define		f96 	long double 
*/


#ifndef STD_TYPES_H
#define STD_TYPES_H

#define 	NULL			((void *)0)

#define 	STD_STATUS 			u8
#define 	STATUS_NOT_OK		0
#define 	STATUS_OK			1
#define 	STATUS_NULLPOINTER	2
#define 	STATUS_IDLE			3
#define 	STATUS_BUSY			4

#define 	LEVEL 		u8
#define 	LOW			0
#define 	HIGH		1

#define 	STATE		u8
#define 	OFF			0
#define 	ON			1


#define 	FALSE		0
#define 	TRUE		1

typedef 	unsigned char		u8, uint8_t;
typedef 	unsigned short int	u16, uint16_t;
typedef 	unsigned long int	u32, uint32_t;

typedef 	signed char			s8, sint8_t;
typedef 	signed short int	s16, sint16_t;
typedef 	signed long int		s32, sint32_t;

typedef 	float				f32, float16_t;
typedef 	double				f64, float64_t;
typedef 	long double 		f96, float96_t;

/* Pointer to callback function */
typedef void(*callBackFn_t)(void);

#endif /*STD_TYPES_H*/
