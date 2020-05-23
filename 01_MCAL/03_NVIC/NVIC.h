#ifndef NVIC_H
#define NVIC_H


//System Block Control registers masks
//Application interrupt and reset control register masks
#define		SCB_AIRCR_VECTKEY_MASK		0x05FA0000

//System Handler Control and State register masks
#define 	SCB_SHCSR_MEMFAULTENA_MASK		0x00010000
#define 	SCB_SHCSR_BUSFAULTENA_MASK		0x00020000
#define 	SCB_SHCSR_USGFAULTENA_MASK		0x00040000
#define		SCB_SHCSR_CLRFAULTENA_MASK		0xFFF8FFFF


//Interrupt priority grouping field

#define 	SCB_AIRCR_PRIGROUP_3_MASK		(u32)0x00000300
#define 	SCB_AIRCR_PRIGROUP_4_MASK       (u32)0x00000400
#define 	SCB_AIRCR_PRIGROUP_5_MASK       (u32)0x00000500
#define 	SCB_AIRCR_PRIGROUP_6_MASK       (u32)0x00000600
#define 	SCB_AIRCR_PRIGROUP_7_MASK       (u32)0x00000700
#define 	SCB_AIRCR_PRIGROUP_CLR_MASK     (u32)0xFFFFF8FF

//Interrupt numbers
#define 	NVIC_EXTINT_0  			0  
#define 	NVIC_EXTINT_1          	1  
#define 	NVIC_EXTINT_2          	2  
#define 	NVIC_EXTINT_3          	3  
#define 	NVIC_EXTINT_4          	4  
#define 	NVIC_EXTINT_5          	5  
#define 	NVIC_EXTINT_6          	6  
#define 	NVIC_EXTINT_7          	7  
#define 	NVIC_EXTINT_8          	8  
#define 	NVIC_EXTINT_9          	9  
#define 	NVIC_EXTINT_10         	10 
#define 	NVIC_EXTINT_11         	11 
#define 	NVIC_EXTINT_12         	12 
#define 	NVIC_EXTINT_13         	13 
#define 	NVIC_EXTINT_14         	14 
#define 	NVIC_EXTINT_15         	15 
#define 	NVIC_EXTINT_16         	16 
#define 	NVIC_EXTINT_17         	17 
#define 	NVIC_EXTINT_18         	18 
#define 	NVIC_EXTINT_19         	19 
#define 	NVIC_EXTINT_20         	20 
#define 	NVIC_EXTINT_21         	21 
#define 	NVIC_EXTINT_22         	22 
#define 	NVIC_EXTINT_23         	23 
#define 	NVIC_EXTINT_24         	24 
#define 	NVIC_EXTINT_25         	25 
#define 	NVIC_EXTINT_26         	26 
#define 	NVIC_EXTINT_27         	27 
#define 	NVIC_EXTINT_28         	28 
#define 	NVIC_EXTINT_29         	29 
#define 	NVIC_EXTINT_30         	30 
#define 	NVIC_EXTINT_31         	31 
#define 	NVIC_EXTINT_32         	32 
#define 	NVIC_EXTINT_33         	33 
#define 	NVIC_EXTINT_34         	34 
#define 	NVIC_EXTINT_35         	35 
#define 	NVIC_EXTINT_36         	36 
#define 	NVIC_EXTINT_37         	37 
#define 	NVIC_EXTINT_38	       	38	
#define 	NVIC_EXTINT_39         	39 
#define 	NVIC_EXTINT_40         	40 
#define 	NVIC_EXTINT_41         	41 
#define 	NVIC_EXTINT_42         	42 
#define 	NVIC_EXTINT_43         	43 
#define 	NVIC_EXTINT_44         	44 
#define 	NVIC_EXTINT_45         	45 
#define 	NVIC_EXTINT_46         	46 
#define 	NVIC_EXTINT_47         	47 
#define 	NVIC_EXTINT_48         	48 
#define 	NVIC_EXTINT_49         	49 
#define 	NVIC_EXTINT_50         	50 
#define 	NVIC_EXTINT_51         	51 
#define 	NVIC_EXTINT_52         	52 
#define 	NVIC_EXTINT_53         	53 
#define 	NVIC_EXTINT_54         	54 
#define 	NVIC_EXTINT_55         	55 
#define 	NVIC_EXTINT_56         	56 
#define 	NVIC_EXTINT_57         	57 
#define 	NVIC_EXTINT_58         	58 
#define 	NVIC_EXTINT_59         	59 
#define 	NVIC_EXTINT_60         	60 
#define 	NVIC_EXTINT_61         	61 
#define 	NVIC_EXTINT_62         	62 
#define 	NVIC_EXTINT_63         	63 
#define 	NVIC_EXTINT_64         	64 
#define 	NVIC_EXTINT_65         	65 
#define 	NVIC_EXTINT_66         	66 
#define 	NVIC_EXTINT_67         	67 
#define 	NVIC_EXTINT_68         	68 
#define 	NVIC_EXTINT_69         	69 
#define 	NVIC_EXTINT_70         	70 
#define 	NVIC_EXTINT_71         	71 
#define 	NVIC_EXTINT_72         	72 
#define 	NVIC_EXTINT_73         	73 
#define 	NVIC_EXTINT_74         	74 
#define 	NVIC_EXTINT_75         	75 
#define 	NVIC_EXTINT_76         	76 
#define 	NVIC_EXTINT_77         	77 
#define 	NVIC_EXTINT_78         	78 
#define 	NVIC_EXTINT_79         	79 
#define 	NVIC_EXTINT_80         	80 
#define 	NVIC_EXTINT_81         	81 
#define 	NVIC_EXTINT_82         	82 
#define 	NVIC_EXTINT_83         	83 
#define 	NVIC_EXTINT_84         	84 
#define 	NVIC_EXTINT_85         	85 
#define 	NVIC_EXTINT_86         	86 
#define 	NVIC_EXTINT_87         	87 
#define 	NVIC_EXTINT_88         	88 
#define 	NVIC_EXTINT_89         	89 
#define 	NVIC_EXTINT_90         	90 
#define 	NVIC_EXTINT_91         	91 
#define 	NVIC_EXTINT_92         	92 
#define 	NVIC_EXTINT_93         	93 
#define 	NVIC_EXTINT_94         	94 
#define 	NVIC_EXTINT_95         	95 
#define 	NVIC_EXTINT_96         	96 
#define 	NVIC_EXTINT_97         	97 
#define 	NVIC_EXTINT_98         	98 
#define 	NVIC_EXTINT_99         	99 
#define 	NVIC_EXTINT_100        	100
#define 	NVIC_EXTINT_101        	101
#define 	NVIC_EXTINT_102        	102
#define 	NVIC_EXTINT_103        	103
#define 	NVIC_EXTINT_104        	104
#define 	NVIC_EXTINT_105        	105
#define 	NVIC_EXTINT_106        	106
#define 	NVIC_EXTINT_107        	107
#define 	NVIC_EXTINT_108        	108
#define 	NVIC_EXTINT_109        	109
#define 	NVIC_EXTINT_110        	110
#define 	NVIC_EXTINT_111        	111
#define 	NVIC_EXTINT_112        	112
#define 	NVIC_EXTINT_113        	113
#define 	NVIC_EXTINT_114        	114
#define 	NVIC_EXTINT_115        	115
#define 	NVIC_EXTINT_116        	116
#define 	NVIC_EXTINT_117        	117
#define 	NVIC_EXTINT_118        	118
#define 	NVIC_EXTINT_119        	119
#define 	NVIC_EXTINT_120        	120
#define 	NVIC_EXTINT_121        	121
#define 	NVIC_EXTINT_122        	122
#define 	NVIC_EXTINT_123        	123
#define 	NVIC_EXTINT_124        	124
#define 	NVIC_EXTINT_125        	125
#define 	NVIC_EXTINT_126        	126
#define 	NVIC_EXTINT_127        	127
#define 	NVIC_EXTINT_128        	128
#define 	NVIC_EXTINT_129        	129
#define 	NVIC_EXTINT_130        	130
#define 	NVIC_EXTINT_131        	131
#define 	NVIC_EXTINT_132        	132
#define 	NVIC_EXTINT_133        	133
#define 	NVIC_EXTINT_134        	134
#define 	NVIC_EXTINT_135        	135
#define 	NVIC_EXTINT_136        	136
#define 	NVIC_EXTINT_137        	137
#define 	NVIC_EXTINT_138        	138
#define 	NVIC_EXTINT_139        	139
#define 	NVIC_EXTINT_140        	140
#define 	NVIC_EXTINT_141        	141
#define 	NVIC_EXTINT_142        	142
#define 	NVIC_EXTINT_143        	143
#define 	NVIC_EXTINT_144        	144
#define 	NVIC_EXTINT_145        	145
#define 	NVIC_EXTINT_146        	146
#define 	NVIC_EXTINT_147        	147
#define 	NVIC_EXTINT_148        	148
#define 	NVIC_EXTINT_149        	149
#define 	NVIC_EXTINT_150        	150
#define 	NVIC_EXTINT_151        	151
#define 	NVIC_EXTINT_152        	152
#define 	NVIC_EXTINT_153        	153
#define 	NVIC_EXTINT_154        	154
#define 	NVIC_EXTINT_155        	155
#define 	NVIC_EXTINT_156        	156
#define 	NVIC_EXTINT_157        	157
#define 	NVIC_EXTINT_158        	158
#define 	NVIC_EXTINT_159        	159
#define 	NVIC_EXTINT_160        	160
#define 	NVIC_EXTINT_161        	161
#define 	NVIC_EXTINT_162        	162
#define 	NVIC_EXTINT_163        	163
#define 	NVIC_EXTINT_164        	164
#define 	NVIC_EXTINT_165        	165
#define 	NVIC_EXTINT_166        	166
#define 	NVIC_EXTINT_167        	167
#define 	NVIC_EXTINT_168        	168
#define 	NVIC_EXTINT_169        	169
#define 	NVIC_EXTINT_170        	170
#define 	NVIC_EXTINT_171        	171
#define 	NVIC_EXTINT_172        	172
#define 	NVIC_EXTINT_173        	173
#define 	NVIC_EXTINT_174        	174
#define 	NVIC_EXTINT_175        	175
#define 	NVIC_EXTINT_176        	176
#define 	NVIC_EXTINT_177        	177
#define 	NVIC_EXTINT_178        	178
#define 	NVIC_EXTINT_179        	179
#define 	NVIC_EXTINT_180        	180
#define 	NVIC_EXTINT_181        	181
#define 	NVIC_EXTINT_182        	182
#define 	NVIC_EXTINT_183        	183
#define 	NVIC_EXTINT_184        	184
#define 	NVIC_EXTINT_185        	185
#define 	NVIC_EXTINT_186        	186
#define 	NVIC_EXTINT_187        	187
#define 	NVIC_EXTINT_188        	188
#define 	NVIC_EXTINT_189        	189
#define 	NVIC_EXTINT_190        	190
#define 	NVIC_EXTINT_191        	191
#define 	NVIC_EXTINT_192        	192
#define 	NVIC_EXTINT_193        	193
#define 	NVIC_EXTINT_194        	194
#define 	NVIC_EXTINT_195        	195
#define 	NVIC_EXTINT_196        	196
#define 	NVIC_EXTINT_197        	197
#define 	NVIC_EXTINT_198        	198
#define 	NVIC_EXTINT_199        	199
#define 	NVIC_EXTINT_200        	200
#define 	NVIC_EXTINT_201        	201
#define 	NVIC_EXTINT_202        	202
#define 	NVIC_EXTINT_203        	203
#define 	NVIC_EXTINT_204        	204
#define 	NVIC_EXTINT_205        	205
#define 	NVIC_EXTINT_206        	206
#define 	NVIC_EXTINT_207        	207
#define 	NVIC_EXTINT_208        	208
#define 	NVIC_EXTINT_209        	209
#define 	NVIC_EXTINT_210        	210
#define 	NVIC_EXTINT_211        	211
#define 	NVIC_EXTINT_212        	212
#define 	NVIC_EXTINT_213        	213
#define 	NVIC_EXTINT_214        	214
#define 	NVIC_EXTINT_215        	215
#define 	NVIC_EXTINT_216        	216
#define 	NVIC_EXTINT_217        	217
#define 	NVIC_EXTINT_218        	218
#define 	NVIC_EXTINT_219        	219
#define 	NVIC_EXTINT_220        	220
#define 	NVIC_EXTINT_221        	221
#define 	NVIC_EXTINT_222        	222
#define 	NVIC_EXTINT_223        	223
#define 	NVIC_EXTINT_224        	224
#define 	NVIC_EXTINT_225        	225
#define 	NVIC_EXTINT_226        	226
#define 	NVIC_EXTINT_227        	227
#define 	NVIC_EXTINT_228        	228
#define 	NVIC_EXTINT_229        	229
#define 	NVIC_EXTINT_230        	230
#define 	NVIC_EXTINT_231        	231
#define 	NVIC_EXTINT_232        	232
#define 	NVIC_EXTINT_233        	233
#define 	NVIC_EXTINT_234        	234
#define 	NVIC_EXTINT_235        	235
#define 	NVIC_EXTINT_236        	236
#define 	NVIC_EXTINT_237        	237
#define 	NVIC_EXTINT_238        	238
#define 	NVIC_EXTINT_239        	239

/****************************************************************************************************************
*                                                                                                               *
*	Description:                                                                                                *
*				This function shall enable an external interrupt.                                     			*
*				                                                                                                *
*	Input Parameters:                                                                                           *
*				u8 Copy_u8InterruptNumber: Takes the external interrupt number.                                	*
*					Options:                                                                                    *
*					NVIC_EXTINT_0 ~ NVIC_EXTINT_239                                     						*
*                                                                                                               *
*	Return value:                                                                                               *
*				STD_STATUS: The function's execution status                                                     *
*					Options:                                                                                    *
*					STATUS_NOT_OK >> Function ended with faliure                                                *
*					STATUS_OK >> Function ended with success                                                    *
*                                                                                                               *
****************************************************************************************************************/
extern STD_STATUS NVIC_u8InterruptEnable(u8 Copy_u8InterruptNumber);

/****************************************************************************************************************
*                                                                                                               *
*	Description:                                                                                                *
*				This function shall disable an external interrupt.                                     			*
*				                                                                                                *
*	Input Parameters:                                                                                           *
*				u8 Copy_u8InterruptNumber: Takes the external interrupt number.                                	*
*					Options:                                                                                    *
*					NVIC_EXTINT_0 ~ NVIC_EXTINT_239                                     						*
*                                                                                                               *
*	Return value:                                                                                               *
*				STD_STATUS: The function's execution status                                                     *
*					Options:                                                                                    *
*					STATUS_NOT_OK >> Function ended with faliure                                                *
*					STATUS_OK >> Function ended with success                                                    *
*                                                                                                               *
****************************************************************************************************************/
extern STD_STATUS NVIC_u8InterruptDisable(u8 Copy_u8InterruptNumber);

/****************************************************************************************************************
*                                                                                                               *
*	Description:                                                                                                *
*				This function shall set pending status for an external interrupt.                               *
*				                                                                                                *
*	Input Parameters:                                                                                           *
*				u8 Copy_u8InterruptNumber: Takes the external interrupt number.                                	*
*					Options:                                                                                    *
*					NVIC_EXTINT_0 ~ NVIC_EXTINT_239                                     						*
*                                                                                                               *
*	Return value:                                                                                               *
*				STD_STATUS: The function's execution status                                                     *
*					Options:                                                                                    *
*					STATUS_NOT_OK >> Function ended with faliure                                                *
*					STATUS_OK >> Function ended with success                                                    *
*                                                                                                               *
****************************************************************************************************************/
extern STD_STATUS NVIC_u8SetPendingStatus(u8 Copy_u8InterruptNumber);


/****************************************************************************************************************
*                                                                                                               *
*	Description:                                                                                                *
*				This function shall clear pending status for an external interrupt.                             *
*				                                                                                                *
*	Input Parameters:                                                                                           *
*				u8 Copy_u8InterruptNumber: Takes the external interrupt number.                                	*
*					Options:                                                                                    *
*					NVIC_EXTINT_0 ~ NVIC_EXTINT_239                                     						*
*                                                                                                               *
*	Return value:                                                                                               *
*				STD_STATUS: The function's execution status                                                     *
*					Options:                                                                                    *
*					STATUS_NOT_OK >> Function ended with faliure                                                *
*					STATUS_OK >> Function ended with success                                                    *
*                                                                                                               *
****************************************************************************************************************/
extern STD_STATUS NVIC_u8ClearPendingStatus(u8 Copy_u8InterruptNumber);

/****************************************************************************************************************
*                                                                                                               *
*	Description:                                                                                                *
*				This function shall get the active status for an external interrupt.                            *
*				                                                                                                *
*	Input Parameters:                                                                                           *
*				u8 Copy_u8InterruptNumber: Takes the external interrupt number.                                	*
*					Options:                                                                                    *
*					NVIC_EXTINT_0 ~ NVIC_EXTINT_239                                                             *
*				                                                                                                *
*				u8 *Copy_pu8Status: Takes the pointer to a variable where the status is saved                   *
*                                                                                                               *
*	Return value:                                                                                               *
*				STD_STATUS: The function's execution status                                                     *
*					Options:                                                                                    *
*					STATUS_NOT_OK >> Function ended with faliure                                                *
*					STATUS_OK >> Function ended with success                                                    *
*                                                                                                               *
****************************************************************************************************************/
extern STD_STATUS NVIC_u8GetActiveStatus(u8 Copy_u8InterruptNumber, u8 *Copy_pu8Status);

/****************************************************************************************************************
*                                                                                                               *
*	Description:                                                                                                *
*				This function shall set the priority for an interrupt.                            				*
*				                                                                                                *
*	Input Parameters:                                                                                           *
*				u8 Copy_u8InterruptNumber: Takes the external interrupt number.                                	*
*					Options:                                                                                    *
*					NVIC_EXTINT_0 ~ NVIC_EXTINT_239                                                             *
*				                                                                                                *
*				u8 Copy_u8Priority: Takes priority of the interrupt.                   							*
*                                                                                                               *
*	Return value:                                                                                               *
*				STD_STATUS: The function's execution status                                                     *
*					Options:                                                                                    *
*					STATUS_NOT_OK >> Function ended with faliure                                                *
*					STATUS_OK >> Function ended with success                                                    *
*                                                                                                               *
****************************************************************************************************************/
extern STD_STATUS NVIC_u8SetPriority(u8 Copy_u8InterruptNumber, u8 Copy_u8Priority);

/****************************************************************************************************************
*                                                                                                               *
*	Description:                                                                                                *
*				This function shall get the active status for an external interrupt.                            *
*				                                                                                                *
*	Input Parameters:                                                                                           *
*				u8 Copy_u8InterruptNumber: Takes the external interrupt number.                                	*
*					Options:                                                                                    *
*					NVIC_EXTINT_0 ~ NVIC_EXTINT_239                                                             *
*				                                                                                                *
*				u8 *Copy_pu8PriorityValue: Takes the pointer to a variable where the priority value is saved.   *
*                                                                                                               *
*	Return value:                                                                                               *
*				STD_STATUS: The function's execution status                                                     *
*					Options:                                                                                    *
*					STATUS_NOT_OK >> Function ended with faliure                                                *
*					STATUS_OK >> Function ended with success                                                    *
*                                                                                                               *
****************************************************************************************************************/
extern STD_STATUS NVIC_u8GetPriority(u8 Copy_u8InterruptNumber, u8 *Copy_pu8PriorityValue);

/****************************************************************************************************************
*                                                                                                               *
*	Description:                                                                                                *
*				This function shall configure the priority group bits.                            				*
*				                                                                                                *
*	Input Parameters:                                                                                           *
*				u32 Copy_u32PriorityGroupMask: Takes a mask of the priority group bits.                        	*
*					Options:                                                                                    *
*					SCB_AIRCR_PRIGROUP_3_MASK    																*
*                   SCB_AIRCR_PRIGROUP_4_MASK                                                                   *
*                   SCB_AIRCR_PRIGROUP_5_MASK                                                                   *
*                   SCB_AIRCR_PRIGROUP_6_MASK                                                                   *
*                   SCB_AIRCR_PRIGROUP_7_MASK                                                                   *
*                                                                                                               *
*	Return value:                                                                                               *
*				STD_STATUS: The function's execution status                                                     *
*					Options:                                                                                    *
*					STATUS_NOT_OK >> Function ended with faliure                                                *
*					STATUS_OK >> Function ended with success                                                    *
*                                                                                                               *
****************************************************************************************************************/
extern STD_STATUS NVIC_u8ConfigureGroupBits(u32 Copy_u32PriorityGroupMask);

/****************************************************************************************************************
*                                                                                                               *
*	Description:                                                                                                *
*				This function shall enable all peripheral interrupts                            				*
*				                                                                                                *
*	Input Parameters:                                                                                           *
*				void  																							*
*                                                                                                               *
*	Return value:                                                                                               *
*				STD_STATUS: The function's execution status                                                     *
*					Options:                                                                                    *
*					STATUS_NOT_OK >> Function ended with faliure                                                *
*					STATUS_OK >> Function ended with success                                                    *
*                                                                                                               *
****************************************************************************************************************/
extern STD_STATUS NVIC_u8EnableAllPeripheralsInterrupts(void);

/****************************************************************************************************************
*                                                                                                               *
*	Description:                                                                                                *
*				This function shall disable all peripheral interrupts                            				*
*				                                                                                                *
*	Input Parameters:                                                                                           *
*				void  																							*
*                                                                                                               *
*	Return value:                                                                                               *
*				STD_STATUS: The function's execution status                                                     *
*					Options:                                                                                    *
*					STATUS_NOT_OK >> Function ended with faliure                                                *
*					STATUS_OK >> Function ended with success                                                    *
*                                                                                                               *
****************************************************************************************************************/
extern STD_STATUS NVIC_u8DisableAllPeripheralsInterrupts(void);

/****************************************************************************************************************
*                                                                                                               *
*	Description:                                                                                                *
*				This function shall enable an internal exception.                            					*
*				                                                                                                *
*	Input Parameters:                                                                                           *
*				u32 Copy_u32FaultExceptionMask: 																*
*					Options:	                                                                                *
*					SCB_SHCSR_MEMFAULTENA_MASK                                                                  *
*					SCB_SHCSR_BUSFAULTENA_MASK                                                                  *
*					SCB_SHCSR_USGFAULTENA_MASK                                                                  *
*                                                                                                               *
*	Return value:                                                                                               *
*				STD_STATUS: The function's execution status                                                     *
*					Options:                                                                                    *
*					STATUS_NOT_OK >> Function ended with faliure                                                *
*					STATUS_OK >> Function ended with success                                                    *
*                                                                                                               *
****************************************************************************************************************/
extern STD_STATUS NVIC_u8EnableFaultException(u32 Copy_u32FaultExceptionMask); 

/****************************************************************************************************************
*                                                                                                               *
*	Description:                                                                                                *
*				This function shall disable an internal exception.                            					*
*				                                                                                                *
*	Input Parameters:                                                                                           *
*				u32 Copy_u32FaultExceptionMask: 																*
*					Options:	                                                                                *
*					SCB_SHCSR_MEMFAULTENA_MASK                                                                  *
*					SCB_SHCSR_BUSFAULTENA_MASK                                                                  *
*					SCB_SHCSR_USGFAULTENA_MASK                                                                  *
*                                                                                                               *
*	Return value:                                                                                               *
*				STD_STATUS: The function's execution status                                                     *
*					Options:                                                                                    *
*					STATUS_NOT_OK >> Function ended with faliure                                                *
*					STATUS_OK >> Function ended with success                                                    *
*                                                                                                               *
****************************************************************************************************************/
extern STD_STATUS NVIC_u8DisableFaultException(u32 Copy_u32FaultExceptionMask); 

/****************************************************************************************************************
*                                                                                                               *
*	Description:                                                                                                *
*				This function shall set an interrupt filter level.                            					*
*				                                                                                                *
*	Input Parameters:                                                                                           *
*				u8 Copy_u8Priority: Takes the priority at which the filteration is set.                        	*
*					Options:                                                                                    *
*					u8 Copy_u8Priority:  	0 >> clears the filter.                                             *
*											1~127 >> sets the filter at the specified value 					*									*
*                                                                                                               *
*	Return value:                                                                                               *
*				STD_STATUS: The function's execution status                                                     *
*					Options:                                                                                    *
*					STATUS_NOT_OK >> Function ended with faliure                                                *
*					STATUS_OK >> Function ended with success                                                    *
*                                                                                                               *
****************************************************************************************************************/
extern STD_STATUS NVIC_u8SetPriorityFilter(u8 Copy_u8Priority);


#endif