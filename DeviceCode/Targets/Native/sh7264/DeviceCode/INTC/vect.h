/***********************************************************************/
/*                                                                     */
/*  FILE        :vect.h                                                */
/*  DATE        :Wed, Apr 22, 2009                                     */
/*  DESCRIPTION :Definition of Vector                                  */
/*  CPU TYPE    :SH7264                                               */
/*                                                                     */
/*  This file is generated by Renesas Project Generator (Ver.4.9).     */
/*                                                                     */
/***********************************************************************/
                  




//;<<VECTOR DATA START (POWER ON RESET)>>
//;0 Power On Reset PC
extern void PowerON_Reset_PC(void);                                                                                                                

//;<<VECTOR DATA END (POWER ON RESET)>>
// 1 Power On Reset SP

// 2 Reserved

// 3 Reserved

// 4 Illegal code
#pragma interrupt INT_Illegal_code
extern void INT_Illegal_code(void);

// 5 Reserved

// 6 Illegal slot
#pragma interrupt INT_Illegal_slot
extern void INT_Illegal_slot(void);

// 7 Reserved

// 8 Reserved

// 9 CPU Address error
#pragma interrupt INT_CPU_Address
extern void INT_CPU_Address(void);

// 10 BUS error
#pragma interrupt INT_DMAC_Address
extern void INT_DMAC_Address(void);

// 11 NMI
#pragma interrupt INT_NMI
extern void INT_NMI(void);

// 12 Reserved

// 13 INT_FPU
#pragma interrupt INT_FPU
extern void INT_FPU(void);

// 14 H-UDI
#pragma interrupt INT_HUDI
extern void INT_HUDI(void);

// 15 Bank Overflow
#pragma interrupt INT_Bank_Overflow
extern void INT_Bank_Overflow(void);

// 16 Bank Underflow
#pragma interrupt INT_Bank_Underflow
extern void INT_Bank_Underflow(void);

// 17 Divide by zero
#pragma interrupt INT_Divide_by_Zero
extern void INT_Divide_by_Zero(void);

// 18 Divide Overflow
#pragma interrupt INT_Divide_Overflow
extern void INT_Divide_Overflow(void);

// 19 Reserved

// 20 Reserved

// 21 Reserved

// 22 Reserved

// 23 Reserved

// 24 Reserved

// 25 Reserved

// 26 Reserved

// 27 Reserved

// 28 Reserved

// 29 Reserved

// 30 Reserved

// 31 Reserved

// 32 TRAPA (User Vecter)
#pragma interrupt INT_TRAPA32
extern void INT_TRAPA32(void);

// 33 TRAPA (User Vecter)
#pragma interrupt INT_TRAPA33
extern void INT_TRAPA33(void);

// 34 TRAPA (User Vecter)
#pragma interrupt INT_TRAPA34
extern void INT_TRAPA34(void);

// 35 TRAPA (User Vecter)
#pragma interrupt INT_TRAPA35
extern void INT_TRAPA35(void);

// 36 TRAPA (User Vecter)
#pragma interrupt INT_TRAPA36
extern void INT_TRAPA36(void);

// 37 TRAPA (User Vecter)
#pragma interrupt INT_TRAPA37
extern void INT_TRAPA37(void);

// 38 TRAPA (User Vecter)
#pragma interrupt INT_TRAPA38
extern void INT_TRAPA38(void);

// 39 TRAPA (User Vecter)
#pragma interrupt INT_TRAPA39
extern void INT_TRAPA39(void);

// 40 TRAPA (User Vecter)
#pragma interrupt INT_TRAPA40
extern void INT_TRAPA40(void);

// 41 TRAPA (User Vecter)
#pragma interrupt INT_TRAPA41
extern void INT_TRAPA41(void);

// 42 TRAPA (User Vecter)
#pragma interrupt INT_TRAPA42
extern void INT_TRAPA42(void);

// 43 TRAPA (User Vecter)
#pragma interrupt INT_TRAPA43
extern void INT_TRAPA43(void);

// 44 TRAPA (User Vecter)
#pragma interrupt INT_TRAPA44
extern void INT_TRAPA44(void);

// 45 TRAPA (User Vecter)
#pragma interrupt INT_TRAPA45
extern void INT_TRAPA45(void);

// 46 TRAPA (User Vecter)
#pragma interrupt INT_TRAPA46
extern void INT_TRAPA46(void);

// 47 TRAPA (User Vecter)
#pragma interrupt INT_TRAPA47
extern void INT_TRAPA47(void);

// 48 TRAPA (User Vecter)
#pragma interrupt INT_TRAPA48
extern void INT_TRAPA48(void);

// 49 TRAPA (User Vecter)
#pragma interrupt INT_TRAPA49
extern void INT_TRAPA49(void);

// 50 TRAPA (User Vecter)
#pragma interrupt INT_TRAPA50
extern void INT_TRAPA50(void);

// 51 TRAPA (User Vecter)
#pragma interrupt INT_TRAPA51
extern void INT_TRAPA51(void);

// 52 TRAPA (User Vecter)
#pragma interrupt INT_TRAPA52
extern void INT_TRAPA52(void);

// 53 TRAPA (User Vecter)
#pragma interrupt INT_TRAPA53
extern void INT_TRAPA53(void);

// 54 TRAPA (User Vecter)
#pragma interrupt INT_TRAPA54
extern void INT_TRAPA54(void);

// 55 TRAPA (User Vecter)
#pragma interrupt INT_TRAPA55
extern void INT_TRAPA55(void);

// 56 TRAPA (User Vecter)
#pragma interrupt INT_TRAPA56
extern void INT_TRAPA56(void);

// 57 TRAPA (User Vecter)
#pragma interrupt INT_TRAPA57
extern void INT_TRAPA57(void);

// 58 TRAPA (User Vecter)
#pragma interrupt INT_TRAPA58
extern void INT_TRAPA58(void);

// 59 TRAPA (User Vecter)
#pragma interrupt INT_TRAPA59
extern void INT_TRAPA59(void);

// 60 TRAPA (User Vecter)
#pragma interrupt INT_TRAPA60
extern void INT_TRAPA60(void);

// 61 TRAPA (User Vecter)
#pragma interrupt INT_TRAPA61
extern void INT_TRAPA61(void);

// 62 TRAPA (User Vecter)
#pragma interrupt INT_TRAPA62
extern void INT_TRAPA62(void);

// 63 TRAPA (User Vecter)
#pragma interrupt INT_TRAPA63
extern void INT_TRAPA63(void);

// 64 Interrupt IRQ0
#ifdef THREADX
#pragma interrupt _tx_touch_interrupt_entry
extern void _tx_touch_interrupt_entry(void);
#else
#pragma interrupt INT_IRQ0
extern void INT_IRQ0(void);
#endif

// 65 Interrupt IRQ1
#pragma interrupt INT_IRQ1
extern void INT_IRQ1(void);

// 66 Interrupt IRQ2
#pragma interrupt INT_IRQ2
extern void INT_IRQ2(void);

// 67 Interrupt IRQ3
#pragma interrupt INT_IRQ3
extern void INT_IRQ3(void);

// 68 Interrupt IRQ4
#pragma interrupt INT_IRQ4
extern void INT_IRQ4(void);

// 69 Interrupt IRQ5
#pragma interrupt INT_IRQ5
extern void INT_IRQ5(void);

// 70 Interrupt IRQ6
#pragma interrupt INT_IRQ6
extern void INT_IRQ6(void);

// 71 Interrupt IRQ7
#pragma interrupt INT_IRQ7
extern void INT_IRQ7(void);

// 72 Reserved

// 73 Reserved

// 74 Reserved

// 75 Reserved

// 76 Reserved

// 77 Reserved

// 78 Reserved

// 79 Reserved

// 80 Interrupt PINT0
#pragma interrupt INT_PINT0
extern void INT_PINT0(void);

// 81 Interrupt PINT1
#pragma interrupt INT_PINT1
extern void INT_PINT1(void);

// 82 Interrupt PINT2
#pragma interrupt INT_PINT2
extern void INT_PINT2(void);

// 83 Interrupt PINT3
#pragma interrupt INT_PINT3
extern void INT_PINT3(void);

// 84 Interrupt PINT4
#pragma interrupt INT_PINT4
extern void INT_PINT4(void);

// 85 Interrupt PINT5
#pragma interrupt INT_PINT5
extern void INT_PINT5(void);

// 86 Interrupt PINT6
#pragma interrupt INT_PINT6
extern void INT_PINT6(void);

// 87 Interrupt PINT7
#pragma interrupt INT_PINT7
extern void INT_PINT7(void);

// 88 Reserved

// 89 Reserved

// 90 Reserved

// 91 Reserved

// 92 Reserved

// 93 Reserved

// 94 Reserved

// 95 Reserved

// 96 Reserved

// 97 Reserved

// 98 Reserved

// 99 Reserved

// 100 Reserved

// 101 Reserved

// 102 Reserved

// 103 Reserved

// 104 Reserved

// 105 Reserved

// 106 Reserved

// 107 Reserved

// 108 DMAC0 TEI0
#pragma interrupt INT_DMAC0_TEI0
extern void INT_DMAC0_TEI0(void);

// 109 DMAC0 HEI0
#pragma interrupt INT_DMAC0_HEI0
extern void INT_DMAC0_HEI0(void);

// 110 Reserved

// 111 Reserved

// 112 DMAC1 TEI1
//#pragma interrupt INT_DMAC1_TEI1
//extern void INT_DMAC1_TEI1(void);
#pragma interrupt _tx_DMAO_CH1_ISR
extern void _tx_DMAO_CH1_ISR(void);

// 113 DMAC1 HEI1
#pragma interrupt INT_DMAC1_HEI1
extern void INT_DMAC1_HEI1(void);

// 114 Reserved

// 115 Reserved

// 116 DMAC2 TEI2
//#pragma interrupt INT_DMAC2_TEI2
//extern void INT_DMAC2_TEI2(void);
#pragma interrupt _tx_DMAO_CH2_ISR
extern void _tx_DMAO_CH2_ISR(void);

// 117 DMAC2 HEI2
#pragma interrupt INT_DMAC2_HEI2
extern void INT_DMAC2_HEI2(void);

// 118 Reserved

// 119 Reserved

// 120 DMAC3 TEI3
#pragma interrupt INT_DMAC3_TEI3
extern void INT_DMAC3_TEI3(void);
//#pragma interrupt _tx_DMAO_CH3_ISR
//extern void _tx_DMAO_CH3_ISR(void);


// 121 DMAC3 HEI3
#pragma interrupt INT_DMAC3_HEI3
extern void INT_DMAC3_HEI3(void);

// 122 Reserved

// 123 Reserved

// 124 DMAC4 TEI4
#pragma interrupt INT_DMAC4_TEI4
extern void INT_DMAC4_TEI4(void);

// 125 DMAC4 HEI4
#pragma interrupt INT_DMAC4_HEI4
extern void INT_DMAC4_HEI4(void);

// 126 Reserved

// 127 Reserved

// 128 DMAC5 TEI5
#pragma interrupt INT_DMAC5_TEI5
extern void INT_DMAC5_TEI5(void);

// 129 DMAC5 HEI5
#pragma interrupt INT_DMAC5_HEI5
extern void INT_DMAC5_HEI5(void);

// 130 Reserved

// 131 Reserved

// 132 DMAC6 TEI6
#pragma interrupt INT_DMAC6_TEI6
extern void INT_DMAC6_TEI6(void);

// 133 DMAC6 HEI6
#pragma interrupt INT_DMAC6_HEI6
extern void INT_DMAC6_HEI6(void);

// 134 Reserved

// 135 Reserved

// 136 DMAC7 TEI7
#pragma interrupt INT_DMAC7_TEI7
extern void INT_DMAC7_TEI7(void);

// 137 DMAC7 HEI7
#pragma interrupt INT_DMAC7_HEI7
extern void INT_DMAC7_HEI7(void);

// 138 Reserved

// 139 Reserved

// 140 DMAC8 TEI8
#pragma interrupt INT_DMAC8_TEI8
extern void INT_DMAC8_TEI8(void);

// 141 DMAC8 HEI8
#pragma interrupt INT_DMAC8_HEI8
extern void INT_DMAC8_HEI8(void);

// 142 Reserved

// 143 Reserved

// 144 DMAC9 TEI9
#pragma interrupt INT_DMAC9_TEI9
extern void INT_DMAC9_TEI9(void);

// 145 DMAC9 HEI9
#pragma interrupt INT_DMAC9_HEI9
extern void INT_DMAC9_HEI9(void);

// 146 Reserved

// 147 Reserved

// 148 DMAC10 TEI10
#pragma interrupt INT_DMAC10_TEI10
extern void INT_DMAC10_TEI10(void);

// 149 DMAC10 HEI10
#pragma interrupt INT_DMAC10_HEI10
extern void INT_DMAC10_HEI10(void);

// 150 Reserved

// 151 Reserved

// 152 DMAC11 TEI11
#pragma interrupt INT_DMAC11_TEI11
extern void INT_DMAC11_TEI11(void);

// 153 DMAC11 HEI11
#pragma interrupt INT_DMAC11_HEI11
extern void INT_DMAC11_HEI11(void);

// 154 Reserved

// 155 Reserved

// 156 DMAC12 TEI12
#pragma interrupt INT_DMAC12_TEI12
extern void INT_DMAC12_TEI12(void);

// 157 DMAC12 HEI12
#pragma interrupt INT_DMAC12_HEI12
extern void INT_DMAC12_HEI12(void);

// 158 Reserved

// 159 Reserved

// 160 DMAC13 TEI13
#pragma interrupt INT_DMAC13_TEI13
extern void INT_DMAC13_TEI13(void);

// 161 DMAC13 HEI13
#pragma interrupt INT_DMAC13_HEI13
extern void INT_DMAC13_HEI13(void);

// 162 Reserved

// 163 Reserved

// 164 DMAC14 TEI14
#pragma interrupt INT_DMAC14_TEI14
extern void INT_DMAC14_TEI14(void);

// 165 DMAC14 HEI14
#pragma interrupt INT_DMAC14_HEI14
extern void INT_DMAC14_HEI14(void);

// 166 Reserved

// 167 Reserved

// 168 DMAC15 TEI15
#pragma interrupt INT_DMAC15_TEI15
extern void INT_DMAC15_TEI15(void);

// 169 DMAC15 HEI15
#pragma interrupt INT_DMAC15_HEI15
extern void INT_DMAC15_HEI15(void);

// 170 USB USBI
#pragma interrupt INT_USB_USBI
extern void INT_USB_USBI(void);
    
// 171 VDC3 VIVSYNCJ
#pragma interrupt INT_VDC3_VIVSYNCJ
extern void INT_VDC3_VIVSYNCJ(void);

// 172 VDC3 VBUFERRJ
#pragma interrupt INT_VDC3_VBUFERR
extern void INT_VDC3_VBUFERR(void);

// 173 VDC3 VIFIELDE
#pragma interrupt INT_VDC3_VIFIELDE
extern void INT_VDC3_VIFIELDE(void);

// 174 VDC3 VOLINE
#pragma interrupt INT_VDC3_VOLINE
extern void INT_VDC3_VOLINE(void);

// 175 CMT CMT0 CMI0
#pragma interrupt INT_CMT0_CMI0
extern void INT_CMT0_CMI0(void);

// 176 CMT CMT1 CMI1
#pragma interrupt INT_CMT1_CMI1
extern void INT_CMT1_CMI1(void);

// 177 BSC CMI
#pragma interrupt INT_BSC_CMI
extern void INT_BSC_CMI(void);

// 178 WDT
#pragma interrupt INT_WDT_ITI
extern void INT_WDT_ITI(void);

// 179 MTU2 MTU0 TGI0A
#pragma interrupt INT_MTU2_TGI0A
extern void INT_MTU2_TGI0A(void);

// 180 MTU2 MTU0 TGI0B
#pragma interrupt INT_MTU2_TGI0B
extern void INT_MTU2_TGI0B(void);

// 181 MTU2 MTU0 TGI0C
#pragma interrupt INT_MTU2_TGI0C
extern void INT_MTU2_TGI0C(void);

// 182 MTU2 MTU0 TGI0D
#pragma interrupt INT_MTU2_TGI0D
extern void INT_MTU2_TGI0D(void);

// 183 MTU2 MTU0 TCI0V
#pragma interrupt INT_MTU2_TCI0V
extern void INT_MTU2_TCI0V(void);

// 184 MTU2 MTU0 TGI0E
#pragma interrupt INT_MTU2_TGI0E
extern void INT_MTU2_TGI0E(void);

// 185 MTU2 MTU0 TGI0F
#pragma interrupt INT_MTU2_TGI0F
extern void INT_MTU2_TGI0F(void);

// 186 MTU2 MTU1 TGI1A
#pragma interrupt INT_MTU2_TGI1A
extern void INT_MTU2_TGI1A(void);

// 187 MTU2 MTU1 TGI1B
#pragma interrupt INT_MTU2_TGI1B
extern void INT_MTU2_TGI1B(void);

// 188 MTU2 MTU1 TCI1V
#pragma interrupt INT_MTU2_TCI1V
extern void INT_MTU2_TCI1V(void);

// 189 MTU2 MTU1 TCI1U
#pragma interrupt INT_MTU2_TCI1U
extern void INT_MTU2_TCI1U(void);

// 190 MTU2 MTU2 TGI2A
#pragma interrupt INT_MTU2_TGI2A
extern void INT_MTU2_TGI2A(void);

// 191 MTU2 MTU2 TGI2B
#pragma interrupt INT_MTU2_TGI2B
extern void INT_MTU2_TGI2B(void);

// 192 MTU2 MTU2 TCI2V
#pragma interrupt INT_MTU2_TCI2V
extern void INT_MTU2_TCI2V(void);

// 193 MTU2 MTU2 TCI2U
#pragma interrupt INT_MTU2_TCI2U
extern void INT_MTU2_TCI2U(void);

// 194 MTU2 MTU3 TGI3A
#pragma interrupt INT_MTU2_TGI3A
extern void INT_MTU2_TGI3A(void);

// 195 MTU2 MTU3 TGI3B
#pragma interrupt INT_MTU2_TGI3B
extern void INT_MTU2_TGI3B(void);

// 196 MTU2 MTU3 TGI3C
#pragma interrupt INT_MTU2_TGI3C
extern void INT_MTU2_TGI3C(void);

// 197 MTU2 MTU3 TGI3D
#pragma interrupt INT_MTU2_TGI3D
extern void INT_MTU2_TGI3D(void);

// 198 MTU2 MTU3 TCI3V
#pragma interrupt INT_MTU2_TCI3V
extern void INT_MTU2_TCI3V(void);

// 199 MTU2 MTU4 TGI4A
#pragma interrupt INT_MTU2_TGI4A
extern void INT_MTU2_TGI4A(void);

// 200 MTU2 MTU4 TGI4B
#pragma interrupt INT_MTU2_TGI4B
extern void INT_MTU2_TGI4B(void);

// 201 MTU2 MTU4 TGI4C
#pragma interrupt INT_MTU2_TGI4C
extern void INT_MTU2_TGI4C(void);

// 202 MTU2 MTU4 TGI4D
#pragma interrupt INT_MTU2_TGI4D
extern void INT_MTU2_TGI4D(void);

// 203 MTU2 MTU4 TCI4V
#pragma interrupt INT_MTU2_TCI4V
extern void INT_MTU2_TCI4V(void);

// 204 PWM PWM1 
#pragma interrupt INT_PWM1
extern void INT_PWM1(void);

// 205 PWM PWM2
#pragma interrupt INT_PWM2
extern void INT_PWM2(void);

// 206 A/D ADI
#pragma interrupt INT_AD_ADI
extern void INT_AD_ADI(void);

// 207 SSI0 SSIF0
#pragma interrupt INT_SSI0_SSIF0
extern void INT_SSI0_SSIF0(void);

// 208 SSI0 SSIRXI0
#pragma interrupt INT_SSI0_SSIRXI0
extern void INT_SSI0_SSIRXI0(void);

// 209 SSI0 SSITXI0
#pragma interrupt INT_SSI0_SSITXI0
extern void INT_SSI0_SSITXI0(void);

// 210 SSI1 SSII1
#pragma interrupt INT_SSI1_SSII1
extern void INT_SSI1_SSII1(void);

// 211 SSI1 SSIRTI1
#pragma interrupt INT_SSI1_SSIRTI1
extern void INT_SSI1_SSIRTI1(void);

// 212 SSI2 SSII2
#pragma interrupt INT_SSI2_SSII2
extern void INT_SSI2_SSII2(void);

// 213 SSI2 SSIRTI2
#pragma interrupt INT_SSI2_SSIRTI2
extern void INT_SSI2_SSIRTI2(void);

// 214 SSI3 SSII3
#pragma interrupt INT_SSI3_SSII3
extern void INT_SSI3_SSII3(void);

// 215 SSI3 SSIRTI3
#pragma interrupt INT_SSI3_SSIRTI3
extern void INT_SSI3_SSIRTI3(void);

// 216 SPDIF SPDIFI
#pragma interrupt INT_SPDIF_SPDIFI
extern void INT_SPDIF_SPDIFI(void);

// 217 IIC3 IIC0 STPI0
#pragma interrupt INT_IIC3_STPI0
extern void INT_IIC3_STPI0(void);

// 218 IIC3 IIC0 NAKI0
#pragma interrupt INT_IIC3_NAKI0
extern void INT_IIC3_NAKI0(void);

// 219 IIC3 IIC0 RXI0
#pragma interrupt INT_IIC3_RXI0
extern void INT_IIC3_RXI0(void);

// 220 IIC3 IIC0 TXI0
#pragma interrupt INT_IIC3_TXI0
extern void INT_IIC3_TXI0(void);

// 221 IIC3 IIC0 TEI0
#pragma interrupt INT_IIC3_TEI0
extern void INT_IIC3_TEI0(void);

// 222 IIC3 IIC1 STPI1
#pragma interrupt INT_IIC3_STPI1
extern void INT_IIC3_STPI1(void);

// 223 IIC3 IIC1 NAKI1
#pragma interrupt INT_IIC3_NAKI1
extern void INT_IIC3_NAKI1(void);

// 224 IIC3 IIC1 RXI1
#pragma interrupt INT_IIC3_RXI1
extern void INT_IIC3_RXI1(void);

// 225 IIC3 IIC1 TXI1
#pragma interrupt INT_IIC3_TXI1
extern void INT_IIC3_TXI1(void);

// 226 IIC3 IIC1 TEI1
#pragma interrupt INT_IIC3_TEI1
extern void INT_IIC3_TEI1(void);

// 227 IIC3 IIC2 STPI2
#pragma interrupt INT_IIC3_STPI2
extern void INT_IIC3_STPI2(void);

// 228 IIC3 IIC2 NAKI2
#pragma interrupt INT_IIC3_NAKI2
extern void INT_IIC3_NAKI2(void);

// 229 IIC3 IIC2 RXI2
#pragma interrupt INT_IIC3_RXI2
extern void INT_IIC3_RXI2(void);

// 230 IIC3 IIC2 TXI2
#pragma interrupt INT_IIC3_TXI2
extern void INT_IIC3_TXI2(void);

// 231 IIC3 IIC2 TEI2
#pragma interrupt INT_IIC3_TEI2
extern void INT_IIC3_TEI2(void);

// 232 SCIF SCIF0 BRI0
#pragma interrupt INT_SCIF0_BRI0
extern void INT_SCIF0_BRI0(void);

// 233 SCIF SCIF0 ERI0
#pragma interrupt INT_SCIF0_ERI0
extern void INT_SCIF0_ERI0(void);

// 234 SCIF SCIF0 RXI0
#pragma interrupt INT_SCIF0_RXI0
extern void INT_SCIF0_RXI0(void);

// 235 SCIF SCIF0 TXI0
#pragma interrupt INT_SCIF0_TXI0
extern void INT_SCIF0_TXI0(void);

// 236 SCIF SCIF1 BRI1
#pragma interrupt INT_SCIF1_BRI1
extern void INT_SCIF1_BRI1(void);

// 237 SCIF SCIF1 ERI1
#pragma interrupt INT_SCIF1_ERI1
extern void INT_SCIF1_ERI1(void);

// 238 SCIF SCIF1 RXI1
#pragma interrupt INT_SCIF1_RXI1
extern void INT_SCIF1_RXI1(void);

// 239 SCIF SCIF1 TXI1
#pragma interrupt INT_SCIF1_TXI1
extern void INT_SCIF1_TXI1(void);

// 240 SCIF SCIF2 BRI2
#pragma interrupt INT_SCIF2_BRI2
extern void INT_SCIF2_BRI2(void);

// 241 SCIF SCIF2 ERI2
#pragma interrupt INT_SCIF2_ERI2
extern void INT_SCIF2_ERI2(void);

// 242 SCIF SCIF2 RXI2
#pragma interrupt INT_SCIF2_RXI2
extern void INT_SCIF2_RXI2(void);

// 243 SCIF SCIF2 TXI2
#pragma interrupt INT_SCIF2_TXI2
extern void INT_SCIF2_TXI2(void);

// 244 SCIF SCIF3 BRI3
#pragma interrupt INT_SCIF3_BRI3
extern void INT_SCIF3_BRI3(void);

// 245 SCIF SCIF3 ERI3
#pragma interrupt INT_SCIF3_ERI3
extern void INT_SCIF3_ERI3(void);

// 246 SCIF SCIF3 RXI3
#pragma interrupt INT_SCIF3_RXI3
extern void INT_SCIF3_RXI3(void);

// 247 SCIF SCIF3 TXI3
#pragma interrupt INT_SCIF3_TXI3
extern void INT_SCIF3_TXI3(void);

// 248 SCIF SCIF4 BRI4
#pragma interrupt INT_SCIF4_BRI4
extern void INT_SCIF4_BRI4(void);

// 249 SCIF SCIF4 ERI4
#pragma interrupt INT_SCIF4_ERI4
extern void INT_SCIF4_ERI4(void);

// 250 SCIF SCIF4 RXI4
#pragma interrupt INT_SCIF4_RXI4
extern void INT_SCIF4_RXI4(void);

// 251 SCIF SCIF4 TXI4
#pragma interrupt INT_SCIF4_TXI4
extern void INT_SCIF4_TXI4(void);

// 252 SCIF SCIF5 BRI5
#pragma interrupt INT_SCIF5_BRI5
extern void INT_SCIF5_BRI5(void);

// 253 SCIF SCIF5 ERI5
#pragma interrupt INT_SCIF5_ERI5
extern void INT_SCIF5_ERI5(void);

// 254 SCIF SCIF5 RXI5
#pragma interrupt INT_SCIF5_RXI5
extern void INT_SCIF5_RXI5(void);

// 255 SCIF SCIF5 TXI5
#pragma interrupt INT_SCIF5_TXI5
extern void INT_SCIF5_TXI5(void);

// 256 SCIF SCIF6 BRI6
#pragma interrupt INT_SCIF6_BRI6
extern void INT_SCIF6_BRI6(void);

// 257 SCIF SCIF6 ERI6
#pragma interrupt INT_SCIF6_ERI6
extern void INT_SCIF6_ERI6(void);

// 258 SCIF SCIF6 RXI6
#pragma interrupt INT_SCIF6_RXI6
extern void INT_SCIF6_RXI6(void);

// 259 SCIF SCIF6 TXI6
#pragma interrupt INT_SCIF6_TXI6
extern void INT_SCIF6_TXI6(void);

// 260 SCIF SCIF7 BRI7
#pragma interrupt INT_SCIF7_BRI7
extern void INT_SCIF7_BRI7(void);

// 261 SCIF SCIF7 ERI7
#pragma interrupt INT_SCIF7_ERI7
extern void INT_SCIF7_ERI7(void);

// 262 SCIF SCIF7 RXI7
#pragma interrupt INT_SCIF7_RXI7
extern void INT_SCIF7_RXI7(void);

// 263 SCIF SCIF7 TXI7
#pragma interrupt INT_SCIF7_TXI7
extern void INT_SCIF7_TXI7(void);

// 264 SIOF SIOFI
#pragma interrupt INT_SIOF_SIOFI
extern void INT_SIOF_SIOFI(void);

// 265 RSPI RSPI0 SPEI0
#pragma interrupt INT_RSPI0_SPEI0
extern void INT_RSPI0_SPEI0(void);

// 266 RSPI RSPI0 SPRI0
#pragma interrupt INT_RSPI0_SPRI0
extern void INT_RSPI0_SPRI0(void);

// 267 RSPI RSPI0 SPTI0
#pragma interrupt INT_RSPI0_SPTI0
extern void INT_RSPI0_SPTI0(void);

// 268 RSPI RSPI1 SPEI1
#pragma interrupt INT_RSPI1_SPEI1
extern void INT_RSPI1_SPEI1(void);

// 269 RSPI RSPI1 SPRI1
#pragma interrupt INT_RSPI1_SPRI1
extern void INT_RSPI1_SPRI1(void);

// 270 RSPI RSPI1 SPTI1
#pragma interrupt INT_RSPI1_SPTI1
extern void INT_RSPI1_SPTI1(void);

// 271 RCAN RCAN0 ERS0 
#pragma interrupt INT_RCAN0_ERS0
extern void INT_RCAN0_ERS0(void);

// 272 RCAN RCAN0 OVR0 
#pragma interrupt INT_RCAN0_OVR0
extern void INT_RCAN0_OVR0(void);

// 273 RCAN RCAN0 RM00 
#pragma interrupt INT_RCAN0_RM00
extern void INT_RCAN0_RM00(void);

// 274 RCAN RCAN0 RM10 
#pragma interrupt INT_RCAN0_RM10
extern void INT_RCAN0_RM10(void);

// 275 RCAN RCAN0 SLE0 
#pragma interrupt INT_RCAN0_SLE0
extern void INT_RCAN0_SLE0(void);

// 276 RCAN RCAN1 ERS1 
#pragma interrupt INT_RCAN1_ERS1
extern void INT_RCAN1_ERS1(void);

// 277 RCAN RCAN1 OVR1 
#pragma interrupt INT_RCAN1_OVR1
extern void INT_RCAN1_OVR1(void);

// 278 RCAN RCAN1 RM01 
#pragma interrupt INT_RCAN1_RM01
extern void INT_RCAN1_RM01(void);

// 279 RCAN RCAN1 RM11 
#pragma interrupt INT_RCAN1_RM11
extern void INT_RCAN1_RM11(void);

// 280 RCAN RCAN1 SLE1 
#pragma interrupt INT_RCAN1_SLE1
extern void INT_RCAN1_SLE1(void);

// 281 IEB IEB 
#pragma interrupt INT_IEB_IEB
extern void INT_IEB_IEB(void);

// 282 ROMDEC ISY 
#pragma interrupt INT_ROMDEC_ISY
extern void INT_ROMDEC_ISY(void);

// 283 ROMDEC IERR 
#pragma interrupt INT_ROMDEC_IERR
extern void INT_ROMDEC_IERR(void);

// 284 ROMDEC ITARG 
#pragma interrupt INT_ROMDEC_ITARG
extern void INT_ROMDEC_ITARG(void);

// 285 ROMDEC ISEC 
#pragma interrupt INT_ROMDEC_ISEC
extern void INT_ROMDEC_ISEC(void);

// 286 ROMDEC IBUF 
#pragma interrupt INT_ROMDEC_IBUF
extern void INT_ROMDEC_IBUF(void);

// 287 ROMDEC IREADY 
#pragma interrupt INT_ROMDEC_IREADY
extern void INT_ROMDEC_IREADY(void);

// 288 FLCTL FLSTEI 
#pragma interrupt INT_FLCTL_FLSTEI
extern void INT_FLCTL_FLSTEI(void);

// 289 FLCTL FLTENDI 
#pragma interrupt INT_FLCTL_FLTENDI
extern void INT_FLCTL_FLTENDI(void);

// 290 FLCTL FLTREQ0I 
#pragma interrupt INT_FLCTL_FLTREQ0I
extern void INT_FLCTL_FLTREQ0I(void);

// 291 FLCTL FLTREQ1I 
#pragma interrupt INT_FLCTL_FLTREQ1I
extern void INT_FLCTL_FLTREQ1I(void);

// 292 SDHI SDHI3 
#pragma interrupt INT_SDHI_SDHI3
extern void INT_SDHI_SDHI3(void);

// 293 SDHI SDHI0 
#pragma interrupt INT_SDHI_SDHI0
extern void INT_SDHI_SDHI0(void);

// 294 SDHI SDHI1 
#pragma interrupt INT_SDHI_SDHI1
extern void INT_SDHI_SDHI1(void);

// 295 Reserved

// 296 RTC ARM 
#pragma interrupt INT_RTC_ARM
extern void INT_RTC_ARM(void);

// 297 RTC PRD 
#pragma interrupt INT_RTC_PRD
extern void INT_RTC_PRD(void);

// 298 RTC CUP 
#pragma interrupt INT_RTC_CUP
extern void INT_RTC_CUP(void);

// 299 SRC SRC0 OVF0 
#pragma interrupt INT_SRC0_OVF0
extern void INT_SRC0_OVF0(void);

// 300 SRC SRC0 UDF0 
#pragma interrupt INT_SRC0_UDF0
extern void INT_SRC0_UDF0(void);

// 301 SRC SRC0 CEF0 
#pragma interrupt INT_SRC0_CEF0
extern void INT_SRC0_CEF0(void);

// 302 SRC SRC0 ODFI0 
#pragma interrupt INT_SRC0_ODFI0
extern void INT_SRC0_ODFI0(void);

// 303 SRC SRC0 IDEI0 
#pragma interrupt INT_SRC0_IDEI0
extern void INT_SRC0_IDEI0(void);

// 304 SRC SRC1 OVF1 
#pragma interrupt INT_SRC1_OVF1
extern void INT_SRC1_OVF1(void);

// 305 SRC SRC1 UDF1 
#pragma interrupt INT_SRC1_UDF1
extern void INT_SRC1_UDF1(void);

// 306 SRC SRC1 CEF1 
#pragma interrupt INT_SRC1_CEF1
extern void INT_SRC1_CEF1(void);

// 307 SRC SRC1 ODFI1 
#pragma interrupt INT_SRC1_ODFI1
extern void INT_SRC1_ODFI1(void);

// 308 SRC SRC1 IDEI1 
#pragma interrupt INT_SRC1_IDEI1
extern void INT_SRC1_IDEI1(void);

// 309 Reserved

// 310 DCU DCUEI 
#pragma interrupt INT_DCU_DCUEI
extern void INT_DCU_DCUEI(void);

// 311 DCU OFFI 
#pragma interrupt INT_DCU_OFFI
extern void INT_DCU_OFFI(void);

// 312 DCU IFEI 
#pragma interrupt INT_DCU_IFEI
extern void INT_DCU_IFEI(void);


#pragma interrupt Dummy
extern void Dummy(void);