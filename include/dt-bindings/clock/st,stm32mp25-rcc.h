/* SPDX-License-Identifier: GPL-2.0-only OR BSD-2-Clause */
/*
 * Copyright (C) STMicroelectronics 2023 - All Rights Reserved
 * Author: Gabriel Fernandez <gabriel.fernandez@foss.st.com>
 */

#ifndef _DT_BINDINGS_STM32MP25_CLKS_H_
#define _DT_BINDINGS_STM32MP25_CLKS_H_

/* INTERNAL/EXTERNAL OSCILLATORS */
#define HSI_CK			0
#define HSE_CK			1
#define MSI_CK			2
#define LSI_CK			3
#define LSE_CK			4
#define I2S_CK			5
#define RTC_CK			6
#define SPDIF_CK_SYMB		7

/* PLL CLOCKS */
#define PLL1_CK			8
#define PLL2_CK			9
#define PLL3_CK			10
#define PLL4_CK			11
#define PLL5_CK			12
#define PLL6_CK			13
#define PLL7_CK			14
#define PLL8_CK			15

#define CK_CPU1			16

/* APB DIV CLOCKS */
#define CK_ICN_APB1		17
#define CK_ICN_APB2		18
#define CK_ICN_APB3		19
#define CK_ICN_APB4		20
#define CK_ICN_APBDBG		21

/* GLOBAL TIMER */
#define TIMG1_CK		22
#define TIMG2_CK		23

/* FLEXGEN CLOCKS */
#define CK_ICN_HS_MCU		24
#define CK_ICN_SDMMC		25
#define CK_ICN_DDR		26
#define CK_ICN_DISPLAY		27
#define CK_ICN_HSL		28
#define CK_ICN_NIC		29
#define CK_ICN_VID		30
#define CK_FLEXGEN_07		31
#define CK_FLEXGEN_08		32
#define CK_FLEXGEN_09		33
#define CK_FLEXGEN_10		34
#define CK_FLEXGEN_11		35
#define CK_FLEXGEN_12		36
#define CK_FLEXGEN_13		37
#define CK_FLEXGEN_14		38
#define CK_FLEXGEN_15		39
#define CK_FLEXGEN_16		40
#define CK_FLEXGEN_17		41
#define CK_FLEXGEN_18		42
#define CK_FLEXGEN_19		43
#define CK_FLEXGEN_20		44
#define CK_FLEXGEN_21		45
#define CK_FLEXGEN_22		46
#define CK_FLEXGEN_23		47
#define CK_FLEXGEN_24		48
#define CK_FLEXGEN_25		49
#define CK_FLEXGEN_26		50
#define CK_FLEXGEN_27		51
#define CK_FLEXGEN_28		52
#define CK_FLEXGEN_29		53
#define CK_FLEXGEN_30		54
#define CK_FLEXGEN_31		55
#define CK_FLEXGEN_32		56
#define CK_FLEXGEN_33		57
#define CK_FLEXGEN_34		58
#define CK_FLEXGEN_35		59
#define CK_FLEXGEN_36		60
#define CK_FLEXGEN_37		61
#define CK_FLEXGEN_38		62
#define CK_FLEXGEN_39		63
#define CK_FLEXGEN_40		64
#define CK_FLEXGEN_41		65
#define CK_FLEXGEN_42		66
#define CK_FLEXGEN_43		67
#define CK_FLEXGEN_44		68
#define CK_FLEXGEN_45		69
#define CK_FLEXGEN_46		70
#define CK_FLEXGEN_47		71
#define CK_FLEXGEN_48		72
#define CK_FLEXGEN_49		73
#define CK_FLEXGEN_50		74
#define CK_FLEXGEN_51		75
#define CK_FLEXGEN_52		76
#define CK_FLEXGEN_53		77
#define CK_FLEXGEN_54		78
#define CK_FLEXGEN_55		79
#define CK_FLEXGEN_56		80
#define CK_FLEXGEN_57		81
#define CK_FLEXGEN_58		82
#define CK_FLEXGEN_59		83
#define CK_FLEXGEN_60		84
#define CK_FLEXGEN_61		85
#define CK_FLEXGEN_62		86
#define CK_FLEXGEN_63		87

/* LOW SPEED MCU CLOCK */
#define CK_ICN_LS_MCU		88

#define CK_BUS_STM500		89
#define CK_BUS_FMC		90
#define CK_BUS_GPU		91
#define CK_BUS_ETH1		92
#define CK_BUS_ETH2		93
#define CK_BUS_PCIE		94
#define CK_BUS_DDRPHYC		95
#define CK_BUS_SYSCPU1		96
#define CK_BUS_ETHSW		97
#define CK_BUS_HPDMA1		98
#define CK_BUS_HPDMA2		99
#define CK_BUS_HPDMA3		100
#define CK_BUS_ADC12		101
#define CK_BUS_ADC3		102
#define CK_BUS_IPCC1		103
#define CK_BUS_CCI		104
#define CK_BUS_CRC		105
#define CK_BUS_MDF1		106
#define CK_BUS_OSPIIOM		107
#define CK_BUS_BKPSRAM		108
#define CK_BUS_HASH		109
#define CK_BUS_RNG		110
#define CK_BUS_CRYP1		111
#define CK_BUS_CRYP2		112
#define CK_BUS_SAES		113
#define CK_BUS_PKA		114
#define CK_BUS_GPIOA		115
#define CK_BUS_GPIOB		116
#define CK_BUS_GPIOC		117
#define CK_BUS_GPIOD		118
#define CK_BUS_GPIOE		119
#define CK_BUS_GPIOF		120
#define CK_BUS_GPIOG		121
#define CK_BUS_GPIOH		122
#define CK_BUS_GPIOI		123
#define CK_BUS_GPIOJ		124
#define CK_BUS_GPIOK		125
#define CK_BUS_LPSRAM1		126
#define CK_BUS_LPSRAM2		127
#define CK_BUS_LPSRAM3		128
#define CK_BUS_GPIOZ		129
#define CK_BUS_LPDMA		130
#define CK_BUS_HSEM		131
#define CK_BUS_IPCC2		132
#define CK_BUS_RTC		133
#define CK_BUS_SPI8		134
#define CK_BUS_LPUART1		135
#define CK_BUS_I2C8		136
#define CK_BUS_LPTIM3		137
#define CK_BUS_LPTIM4		138
#define CK_BUS_LPTIM5		139
#define CK_BUS_IWDG5		140
#define CK_BUS_WWDG2		141
#define CK_BUS_I3C4		142
#define CK_BUS_TIM2		143
#define CK_BUS_TIM3		144
#define CK_BUS_TIM4		145
#define CK_BUS_TIM5		146
#define CK_BUS_TIM6		147
#define CK_BUS_TIM7		148
#define CK_BUS_TIM10		149
#define CK_BUS_TIM11		150
#define CK_BUS_TIM12		151
#define CK_BUS_TIM13		152
#define CK_BUS_TIM14		153
#define CK_BUS_LPTIM1		154
#define CK_BUS_LPTIM2		155
#define CK_BUS_SPI2		156
#define CK_BUS_SPI3		157
#define CK_BUS_SPDIFRX		158
#define CK_BUS_USART2		159
#define CK_BUS_USART3		160
#define CK_BUS_UART4		161
#define CK_BUS_UART5		162
#define CK_BUS_I2C1		163
#define CK_BUS_I2C2		164
#define CK_BUS_I2C3		165
#define CK_BUS_I2C4		166
#define CK_BUS_I2C5		167
#define CK_BUS_I2C6		168
#define CK_BUS_I2C7		169
#define CK_BUS_I3C1		170
#define CK_BUS_I3C2		171
#define CK_BUS_I3C3		172
#define CK_BUS_TIM1		173
#define CK_BUS_TIM8		174
#define CK_BUS_TIM15		175
#define CK_BUS_TIM16		176
#define CK_BUS_TIM17		177
#define CK_BUS_TIM20		178
#define CK_BUS_SAI1		179
#define CK_BUS_SAI2		180
#define CK_BUS_SAI3		181
#define CK_BUS_SAI4		182
#define CK_BUS_USART1		183
#define CK_BUS_USART6		184
#define CK_BUS_UART7		185
#define CK_BUS_UART8		186
#define CK_BUS_UART9		187
#define CK_BUS_FDCAN		188
#define CK_BUS_SPI1		189
#define CK_BUS_SPI4		190
#define CK_BUS_SPI5		191
#define CK_BUS_SPI6		192
#define CK_BUS_SPI7		193
#define CK_BUS_BSEC		194
#define CK_BUS_IWDG1		195
#define CK_BUS_IWDG2		196
#define CK_BUS_IWDG3		197
#define CK_BUS_IWDG4		198
#define CK_BUS_WWDG1		199
#define CK_BUS_VREF		200
#define CK_BUS_DTS		201
#define CK_BUS_SERC		202
#define CK_BUS_HDP		203
#define CK_BUS_IS2M		204
#define CK_BUS_DSI		205
#define CK_BUS_LTDC		206
#define CK_BUS_CSI		207
#define CK_BUS_DCMIPP		208
#define CK_BUS_DDRC		209
#define CK_BUS_DDRCFG		210
#define CK_BUS_GICV2M		211
#define CK_BUS_USBTC		212
#define CK_BUS_USB3PCIEPHY	214
#define CK_BUS_STGEN		215
#define CK_BUS_VDEC		216
#define CK_BUS_VENC		217
#define CK_SYSDBG		218
#define CK_KER_TIM2		219
#define CK_KER_TIM3		220
#define CK_KER_TIM4		221
#define CK_KER_TIM5		222
#define CK_KER_TIM6		223
#define CK_KER_TIM7		224
#define CK_KER_TIM10		225
#define CK_KER_TIM11		226
#define CK_KER_TIM12		227
#define CK_KER_TIM13		228
#define CK_KER_TIM14		229
#define CK_KER_TIM1		230
#define CK_KER_TIM8		231
#define CK_KER_TIM15		232
#define CK_KER_TIM16		233
#define CK_KER_TIM17		234
#define CK_KER_TIM20		235
#define CK_BUS_SYSRAM		236
#define CK_BUS_VDERAM		237
#define CK_BUS_RETRAM		238
#define CK_BUS_OSPI1		239
#define CK_BUS_OSPI2		240
#define CK_BUS_OTFD1		241
#define CK_BUS_OTFD2		242
#define CK_BUS_SRAM1		243
#define CK_BUS_SRAM2		244
#define CK_BUS_SDMMC1		245
#define CK_BUS_SDMMC2		246
#define CK_BUS_SDMMC3		247
#define CK_BUS_DDR		248
#define CK_BUS_RISAF4		249
#define CK_BUS_USB2OHCI		250
#define CK_BUS_USB2EHCI		251
#define CK_BUS_USB3DR		252
#define CK_KER_LPTIM1		253
#define CK_KER_LPTIM2		254
#define CK_KER_USART2		255
#define CK_KER_UART4		256
#define CK_KER_USART3		257
#define CK_KER_UART5		258
#define CK_KER_SPI2		259
#define CK_KER_SPI3		260
#define CK_KER_SPDIFRX		261
#define CK_KER_I2C1		262
#define CK_KER_I2C2		263
#define CK_KER_I3C1		264
#define CK_KER_I3C2		265
#define CK_KER_I2C3		266
#define CK_KER_I2C5		267
#define CK_KER_I3C3		268
#define CK_KER_I2C4		269
#define CK_KER_I2C6		270
#define CK_KER_I2C7		271
#define CK_KER_SPI1		272
#define CK_KER_SPI4		273
#define CK_KER_SPI5		274
#define CK_KER_SPI6		275
#define CK_KER_SPI7		276
#define CK_KER_USART1		277
#define CK_KER_USART6		278
#define CK_KER_UART7		279
#define CK_KER_UART8		280
#define CK_KER_UART9		281
#define CK_KER_MDF1		282
#define CK_KER_SAI1		283
#define CK_KER_SAI2		284
#define CK_KER_SAI3		285
#define CK_KER_SAI4		286
#define CK_KER_FDCAN		287
#define CK_KER_DSIBLANE		288
#define CK_KER_DSIPHY		289
#define CK_KER_CSI		290
#define CK_KER_CSITXESC		291
#define CK_KER_CSIPHY		292
#define CK_KER_LVDSPHY		293
#define CK_KER_STGEN		294
#define CK_KER_USB3PCIEPHY	295
#define CK_KER_USB2PHY2EN	296
#define CK_KER_I3C4		297
#define CK_KER_SPI8		298
#define CK_KER_I2C8		299
#define CK_KER_LPUART1		300
#define CK_KER_LPTIM3		301
#define CK_KER_LPTIM4		302
#define CK_KER_LPTIM5		303
#define CK_KER_TSDBG		304
#define CK_KER_TPIU		305
#define CK_BUS_ETR		306
#define CK_BUS_SYSATB		307
#define CK_KER_ADC12		308
#define CK_KER_ADC3		309
#define CK_KER_OSPI1		310
#define CK_KER_OSPI2		311
#define CK_KER_FMC		312
#define CK_KER_SDMMC1		313
#define CK_KER_SDMMC2		314
#define CK_KER_SDMMC3		315
#define CK_KER_ETH1		316
#define CK_KER_ETH2		317
#define CK_KER_ETH1PTP		318
#define CK_KER_ETH2PTP		319
#define CK_KER_USB2PHY1		320
#define CK_KER_USB2PHY2		321
#define CK_KER_ETHSW		322
#define CK_KER_ETHSWREF		323
#define CK_MCO1			324
#define CK_MCO2			325
#define CK_KER_DTS		326
#define CK_ETH1_RX		327
#define CK_ETH1_TX		328
#define CK_ETH1_MAC		329
#define CK_ETH2_RX		330
#define CK_ETH2_TX		331
#define CK_ETH2_MAC		332
#define CK_ETH1_STP		333
#define CK_ETH2_STP		334
#define CK_KER_USBTC		335
#define CK_BUS_ADF1		336
#define CK_KER_ADF1		337
#define CK_BUS_LVDS		338
#define CK_KER_LTDC		339
#define CK_KER_GPU		340
#define CK_BUS_ETHSWACMCFG	341
#define CK_BUS_ETHSWACMMSG	342
#define HSE_DIV2_CK		343

#define STM32MP25_LAST_CLK	344

#define CK_SCMI_ICN_HS_MCU	0
#define CK_SCMI_ICN_SDMMC	1
#define CK_SCMI_ICN_DDR		2
#define CK_SCMI_ICN_DISPLAY	3
#define CK_SCMI_ICN_HSL		4
#define CK_SCMI_ICN_NIC		5
#define CK_SCMI_ICN_VID		6
#define CK_SCMI_FLEXGEN_07	7
#define CK_SCMI_FLEXGEN_08	8
#define CK_SCMI_FLEXGEN_09	9
#define CK_SCMI_FLEXGEN_10	10
#define CK_SCMI_FLEXGEN_11	11
#define CK_SCMI_FLEXGEN_12	12
#define CK_SCMI_FLEXGEN_13	13
#define CK_SCMI_FLEXGEN_14	14
#define CK_SCMI_FLEXGEN_15	15
#define CK_SCMI_FLEXGEN_16	16
#define CK_SCMI_FLEXGEN_17	17
#define CK_SCMI_FLEXGEN_18	18
#define CK_SCMI_FLEXGEN_19	19
#define CK_SCMI_FLEXGEN_20	20
#define CK_SCMI_FLEXGEN_21	21
#define CK_SCMI_FLEXGEN_22	22
#define CK_SCMI_FLEXGEN_23	23
#define CK_SCMI_FLEXGEN_24	24
#define CK_SCMI_FLEXGEN_25	25
#define CK_SCMI_FLEXGEN_26	26
#define CK_SCMI_FLEXGEN_27	27
#define CK_SCMI_FLEXGEN_28	28
#define CK_SCMI_FLEXGEN_29	29
#define CK_SCMI_FLEXGEN_30	30
#define CK_SCMI_FLEXGEN_31	31
#define CK_SCMI_FLEXGEN_32	32
#define CK_SCMI_FLEXGEN_33	33
#define CK_SCMI_FLEXGEN_34	34
#define CK_SCMI_FLEXGEN_35	35
#define CK_SCMI_FLEXGEN_36	36
#define CK_SCMI_FLEXGEN_37	37
#define CK_SCMI_FLEXGEN_38	38
#define CK_SCMI_FLEXGEN_39	39
#define CK_SCMI_FLEXGEN_40	40
#define CK_SCMI_FLEXGEN_41	41
#define CK_SCMI_FLEXGEN_42	42
#define CK_SCMI_FLEXGEN_43	43
#define CK_SCMI_FLEXGEN_44	44
#define CK_SCMI_FLEXGEN_45	45
#define CK_SCMI_FLEXGEN_46	46
#define CK_SCMI_FLEXGEN_47	47
#define CK_SCMI_FLEXGEN_48	48
#define CK_SCMI_FLEXGEN_49	49
#define CK_SCMI_FLEXGEN_50	50
#define CK_SCMI_FLEXGEN_51	51
#define CK_SCMI_FLEXGEN_52	52
#define CK_SCMI_FLEXGEN_53	53
#define CK_SCMI_FLEXGEN_54	54
#define CK_SCMI_FLEXGEN_55	55
#define CK_SCMI_FLEXGEN_56	56
#define CK_SCMI_FLEXGEN_57	57
#define CK_SCMI_FLEXGEN_58	58
#define CK_SCMI_FLEXGEN_59	59
#define CK_SCMI_FLEXGEN_60	60
#define CK_SCMI_FLEXGEN_61	61
#define CK_SCMI_FLEXGEN_62	62
#define CK_SCMI_FLEXGEN_63	63
#define CK_SCMI_ICN_LS_MCU	64
#define CK_SCMI_HSE		65
#define CK_SCMI_LSE		66
#define CK_SCMI_HSI		67
#define CK_SCMI_LSI		68
#define CK_SCMI_MSI		69
#define CK_SCMI_HSE_DIV2	70
#define CK_SCMI_CPU1		71
#define CK_SCMI_SYSCPU1		72
#define CK_SCMI_PLL2		73
#define CK_SCMI_PLL3		74
#define CK_SCMI_RTC		75
#define CK_SCMI_RTCCK		76
#define CK_SCMI_ICN_APB1	77
#define CK_SCMI_ICN_APB2	78
#define CK_SCMI_ICN_APB3	79
#define CK_SCMI_ICN_APB4	80
#define CK_SCMI_ICN_APBDBG	81
#define CK_SCMI_TIMG1		82
#define CK_SCMI_TIMG2		83
#define CK_SCMI_BKPSRAM		84
#define CK_SCMI_BSEC		85
#define CK_SCMI_ETR		87
#define CK_SCMI_FMC		88
#define CK_SCMI_GPIOA		89
#define CK_SCMI_GPIOB		90
#define CK_SCMI_GPIOC		91
#define CK_SCMI_GPIOD		92
#define CK_SCMI_GPIOE		93
#define CK_SCMI_GPIOF		94
#define CK_SCMI_GPIOG		95
#define CK_SCMI_GPIOH		96
#define CK_SCMI_GPIOI		97
#define CK_SCMI_GPIOJ		98
#define CK_SCMI_GPIOK		99
#define CK_SCMI_GPIOZ		100
#define CK_SCMI_HPDMA1		101
#define CK_SCMI_HPDMA2		102
#define CK_SCMI_HPDMA3		103
#define CK_SCMI_HSEM		104
#define CK_SCMI_IPCC1		105
#define CK_SCMI_IPCC2		106
#define CK_SCMI_LPDMA		107
#define CK_SCMI_RETRAM		108
#define CK_SCMI_SRAM1		109
#define CK_SCMI_SRAM2		110
#define CK_SCMI_LPSRAM1		111
#define CK_SCMI_LPSRAM2		112
#define CK_SCMI_LPSRAM3		113
#define CK_SCMI_VDERAM		114
#define CK_SCMI_SYSRAM		115
#define CK_SCMI_OSPI1		116
#define CK_SCMI_OSPI2		117
#define CK_SCMI_TPIU		118
#define CK_SCMI_SYSDBG		119
#define CK_SCMI_SYSATB		120
#define CK_SCMI_TSDBG		121
#define CK_SCMI_STM500		122

#endif /* _DT_BINDINGS_STM32MP25_CLKS_H_ */
