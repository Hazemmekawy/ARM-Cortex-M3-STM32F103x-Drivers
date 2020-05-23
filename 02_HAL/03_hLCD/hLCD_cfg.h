#ifndef HLCD_CFG_H
#define HLCD_CFG_H

/*
	Options:
	FOUR_BITS_MODE
	EIGHT_BITS_MODE
*/
#define HLCD_DATA_MODE			EIGHT_BITS_MODE

/*
	Options:
	ONE_LINE
	TWO_LINE
*/
#define HLCD_NUMBER_OF_LINES	TWO_LINE

/*
	Options:
	FONT_5x7
	FONT_5x10
*/
#define HLCD_FONT				FONT_5x7

/*
	Options:
	DISPLAY_OFF
	DISPLAY_ON
*/
#define HLCD_DISPLAY			DISPLAY_ON

/*
	Options:
	CURSOR_OFF
	CURSOR_ON
*/
#define HLCD_CURSOR				CURSOR_OFF

/*
	Options:
	CURSOR_BLINK_OFF
	CURSOR_BLINK_ON
*/
#define HLCD_CURSOR_BLINK		CURSOR_BLINK_OFF

/*
	Options:
	DECREASE
	INCREASE
*/
#define HLCD_INC_DEC			DECREASE

/*
	Options:
	SHIFT_OFF	
	SHIFT_ON	
*/
#define HLCD_SHIFT				SHIFT_OFF


/* Control pins configuration */
#define HLCD_RS_PIN		GPIO_PIN_0
#define HLCD_RS_PORT	GPIOA

#define HLCD_RW_PIN		GPIO_PIN_0
#define HLCD_RW_PORT	GPIOA

#define HLCD_E_PIN		GPIO_PIN_0
#define HLCD_E_PORT     GPIOA

/* Data pins configuration */
#define HLCD_D0_PIN		GPIO_PIN_0
#define HLCD_D0_PORT	GPIOA

#define HLCD_D1_PIN		GPIO_PIN_0
#define HLCD_D1_PORT	GPIOA

#define HLCD_D2_PIN		GPIO_PIN_0
#define HLCD_D2_PORT	GPIOA

#define HLCD_D3_PIN		GPIO_PIN_0
#define HLCD_D3_PORT	GPIOA

#define HLCD_D4_PIN		GPIO_PIN_0
#define HLCD_D4_PORT	GPIOA

#define HLCD_D5_PIN		GPIO_PIN_0
#define HLCD_D5_PORT	GPIOA

#define HLCD_D6_PIN		GPIO_PIN_0
#define HLCD_D6_PORT	GPIOA

#define HLCD_D7_PIN		GPIO_PIN_0
#define HLCD_D7_PORT	GPIOA


#endif /* HLCD_CFG_H */