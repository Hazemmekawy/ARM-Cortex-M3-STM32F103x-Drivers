#include "STD_TYPES.h"

#include "RCC.h"
#include "STK.h"

#include "hSTK.h"


extern STD_STATUS hSTK_u8Init(void)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	
	local_u8ErrorStatus = STK_u8Init();
	return local_u8ErrorStatus;	
}

extern STD_STATUS hSTK_u8Start(void)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	
	local_u8ErrorStatus = STK_u8Start();
	return local_u8ErrorStatus;	
}

extern STD_STATUS hSTK_u8Stop(void)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	
	local_u8ErrorStatus = STK_u8Stop();
	return local_u8ErrorStatus;	
}

extern STD_STATUS hSTK_u8SetTimer_us(u32 Copy_u32Time_us)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	
	f32 local_f32AHB_MHZ = 0;
	RCC_u8Get_AHB_ClkFrequncyMHZ(&local_f32AHB_MHZ);
	
	local_u8ErrorStatus = STK_u8SetTimer(Copy_u32Time_us, local_f32AHB_MHZ);
	
	return local_u8ErrorStatus;
}

extern STD_STATUS hSTK_u8SetCallBack(callBackFn_t Copy_pfunc)
{
	STD_STATUS local_u8ErrorStatus = STATUS_NOT_OK;
	
	local_u8ErrorStatus = STK_u8SetCallBack(Copy_pfunc);
	return local_u8ErrorStatus;
}