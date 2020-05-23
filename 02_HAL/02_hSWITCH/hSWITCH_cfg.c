#include "STD_TYPES.h"
#include "GPIO.h"
#include "hSWITCH.h"
#include "hSWITCH_cfg.h"


/* Switches configuration array */
extern const SWITCH_cfgStruct_t SWITCH_cfgStruct[SWITCH_MAX_NUMBER] = {
	
	/*
		{SWITCH_NAME, SWITCH_PORT, SWITCH_PIN_MASK, SWITCH_ACTIVE_STATE}
	*/
	
	{SWITCH0, SWITCH0_PORT, SWITCH0_PIN, SWITCH0_ACTIVE_STATE},
	{SWITCH1, SWITCH1_PORT, SWITCH1_PIN, SWITCH1_ACTIVE_STATE}		
};

