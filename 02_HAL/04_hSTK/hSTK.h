#ifndef HSTK_H
#define HSTK_H


extern STD_STATUS hSTK_u8Init(void);
extern STD_STATUS hSTK_u8Start(void);
extern STD_STATUS hSTK_u8Stop(void);
extern STD_STATUS hSTK_u8SetTimer_us(u32 Copy_u32Time_us);
extern STD_STATUS hSTK_u8SetCallBack(callBackFn_t Copy_pfunc);

#endif /* HSTK_H */