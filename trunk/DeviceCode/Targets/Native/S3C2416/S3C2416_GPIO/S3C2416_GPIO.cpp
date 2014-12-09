////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) Microsoft Corporation.  All rights reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <tinyhal.h>
#include "S3C2416_GPIO.h"
#include "../s3c2416.h"
//--//

#undef  TRACE_ALWAYS

#define TRACE_ALWAYS               0x00000001

#undef  DEBUG_TRACE
#define DEBUG_TRACE (TRACE_ALWAYS)

//--//

#if defined(ADS_LINKER_BUG__NOT_ALL_UNUSED_VARIABLES_ARE_REMOVED)
#pragma arm section rodata = "c_Gpio_Attributes_S3C2416"
#endif

const UINT8 __section(rodata) S3C2416_GPIO_Driver::c_Gpio_Attributes[S3C2416_GPIO_Driver::c_MaxPins] =
{
    GPIO_ATTRIBUTE_OUTPUT                        , //   0 GPA0  (register 0)
    GPIO_ATTRIBUTE_OUTPUT                        , //   1 GPA1
    GPIO_ATTRIBUTE_OUTPUT                        , //   2 GPA2
    GPIO_ATTRIBUTE_OUTPUT                        , //   3 GPA3
    GPIO_ATTRIBUTE_OUTPUT                        , //   4 GPA4
    GPIO_ATTRIBUTE_OUTPUT                        , //   5 GPA5
    GPIO_ATTRIBUTE_OUTPUT                        , //   6 GPA6
    GPIO_ATTRIBUTE_OUTPUT                        , //   7 GPA7
    GPIO_ATTRIBUTE_OUTPUT                        , //   8 GPA8
    GPIO_ATTRIBUTE_OUTPUT                        , //   9 GPA9
    GPIO_ATTRIBUTE_OUTPUT                        , //  10 GPA10
    GPIO_ATTRIBUTE_OUTPUT                        , //  11 GPA12
    GPIO_ATTRIBUTE_OUTPUT                        , //  12 GPA13
    GPIO_ATTRIBUTE_OUTPUT                        , //  13 GPA14
    GPIO_ATTRIBUTE_OUTPUT                        , //  14 GPA15
    GPIO_ATTRIBUTE_OUTPUT                        , //  15 GPA16
    GPIO_ATTRIBUTE_OUTPUT                        , //  16 GPA17
    GPIO_ATTRIBUTE_OUTPUT                        , //  17 GPA18
    GPIO_ATTRIBUTE_OUTPUT                        , //  18 GPA19
    GPIO_ATTRIBUTE_OUTPUT                        , //  19 GPA20
    GPIO_ATTRIBUTE_OUTPUT                        , //  20 GPA21
    GPIO_ATTRIBUTE_OUTPUT                        , //  21 GPA22
    GPIO_ATTRIBUTE_OUTPUT                        , //  22 GPA23
    GPIO_ATTRIBUTE_OUTPUT                        , //  23 GPA24
    GPIO_ATTRIBUTE_OUTPUT                        , //  24 GPA25
    GPIO_ATTRIBUTE_OUTPUT                        , //  25 GPA26  
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  26  GPB0 
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  27  GPB1
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  28  GPB2
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  29  GPB3
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  30  GPB4
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  31  GPB5
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  32  GPB6 (register 1)
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  33  GPB9
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  34  GPB10   
	GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  35  GPC0
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  36  GPC1
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  37  GPC2
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  38  GPC3
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  39  GPC4
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  40  GPC5
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  41  GPC6
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  42  GPC7
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  43  GPC8
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  44  GPC9
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  45  GPC10
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  46  GPC11
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  47  GPC12
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  48  GPC13
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  49  GPC14
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  50  GPC15  
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  51  GPD0
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  52  GPD1
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  53  GPD2
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  54  GPD3
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  55  GPD4
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  56  GPD5
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  57  GPD6
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  58  GPD7
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  59  GPD8
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  60  GPD9
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  61  GPD10
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  62  GPD11
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  63  GPD12
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  64  GPD13 (register 2)
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  65  GPD14
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  66  GPD15   
	GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  67  GPE0
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  68  GPE1
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  69  GPE2
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  70  GPE3
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  71  GPE4
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  72  GPE5
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  73  GPE6
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  74  GPE7
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  75  GPE8
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  76  GPE9
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  77  GPE10
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  78  GPE11
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  79  GPE12
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  80  GPE13
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  81  GPE14
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  82  GPE15   
	GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  83  GPF0
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  84  GPF1
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  85  GPF2
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  86  GPF3
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  87  GPF4
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  88  GPF5
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  89  GPF6
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  90  GPF7	
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  91  GPG0
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  92  GPG1
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  93  GPG2
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  94  GPG3
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  95  GPG4
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  96  GPG5 (register 3)
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  97  GPG6
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  98  GPG7
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  99  GPH0
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //  100 GPH1

    GPIO_ATTRIBUTE_OUTPUT                        , // 101 GPA1
    GPIO_ATTRIBUTE_OUTPUT                        , //102 GPA2
    GPIO_ATTRIBUTE_OUTPUT                        , //103 GPA3
    GPIO_ATTRIBUTE_OUTPUT                        , //104 GPA4
    GPIO_ATTRIBUTE_OUTPUT                        , //105 GPA5
    GPIO_ATTRIBUTE_OUTPUT                        , //106 GPA6
    GPIO_ATTRIBUTE_OUTPUT                        , //107 GPA7
    GPIO_ATTRIBUTE_OUTPUT                        , //108 GPA8
    GPIO_ATTRIBUTE_OUTPUT                        , //109 GPA9
    GPIO_ATTRIBUTE_OUTPUT                        , //110 GPA10
    GPIO_ATTRIBUTE_OUTPUT                        , //111 GPA12
    GPIO_ATTRIBUTE_OUTPUT                        , //112 GPA13
    GPIO_ATTRIBUTE_OUTPUT                        , //113 GPA14
    GPIO_ATTRIBUTE_OUTPUT                        , //114 GPA15
    GPIO_ATTRIBUTE_OUTPUT                        , //115 GPA16
    GPIO_ATTRIBUTE_OUTPUT                        , //116 GPA17
    GPIO_ATTRIBUTE_OUTPUT                        , //117 GPA18
    GPIO_ATTRIBUTE_OUTPUT                        , //118 GPA19
    GPIO_ATTRIBUTE_OUTPUT                        , //119 GPA20
    GPIO_ATTRIBUTE_OUTPUT                        , //120 GPA21
    GPIO_ATTRIBUTE_OUTPUT                        , //121 GPA22
    GPIO_ATTRIBUTE_OUTPUT                        , //122 GPA23
    GPIO_ATTRIBUTE_OUTPUT                        , //123 GPA24
    GPIO_ATTRIBUTE_OUTPUT                        , //124 GPA25
    GPIO_ATTRIBUTE_OUTPUT                        , //125 GPA26  
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //126  GPB0 
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //127  GPB1
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //128  GPB2
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //129  GPB3
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //130  GPB4
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //131  GPB5
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //132  GPB6 (register 1)
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //133  GPB9
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //134  GPB10   
	GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //135  GPC0
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //136  GPC1
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //137  GPC2
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //138  GPC3
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //139  GPC4
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //140  GPC5
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //141  GPC6
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //142  GPC7
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //143  GPC8
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //144  GPC9
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //145  GPC10
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //146  GPC11
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //147  GPC12
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //148  GPC13
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //149  GPC14
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //150  GPC15  
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //151  GPD0
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //152  GPD1
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //153  GPD2
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //154  GPD3
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //155  GPD4
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //156  GPD5
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //157  GPD6
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //158  GPD7
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //159  GPD8
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //160  GPD9
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //161  GPD10
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //162  GPD11
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //163  GPD12
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //164  GPD13 (register 2)
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //165  GPD14
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //166  GPD15   
	GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //167  GPE0
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //168  GPE1
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //169  GPE2
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //170  GPE3
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //171  GPE4
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //172  GPE5
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //173  GPE6
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //174  GPE7
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //175  GPE8
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //176  GPE9
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //177  GPE10
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //178  GPE11
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //179  GPE12
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //180  GPE13
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //181  GPE14
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //182  GPE15   
	GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //183  GPF0
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //184  GPF1
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //185  GPF2
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //186  GPF3
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //187  GPF4
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //188  GPF5
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //189  GPF6
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //190  GPF7	
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //191  GPG0
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //192  GPG1
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //193  GPG2
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //194  GPG3
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //195  GPG4
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //196  GPG5 (register 3)
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //197  GPG6
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //198  GPG7
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //199  GPH0
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //200 GPH1
	
    GPIO_ATTRIBUTE_OUTPUT                        , //201 GPA1
    GPIO_ATTRIBUTE_OUTPUT                        , //202 GPA2
    GPIO_ATTRIBUTE_OUTPUT                        , //203 GPA3
    GPIO_ATTRIBUTE_OUTPUT                        , //204 GPA4
    GPIO_ATTRIBUTE_OUTPUT                        , //205 GPA5
    GPIO_ATTRIBUTE_OUTPUT                        , //206 GPA6
    GPIO_ATTRIBUTE_OUTPUT                        , //207 GPA7
    GPIO_ATTRIBUTE_OUTPUT                        , //208 GPA8
    GPIO_ATTRIBUTE_OUTPUT                        , //209 GPA9
    GPIO_ATTRIBUTE_OUTPUT                        , //210 GPA10
    GPIO_ATTRIBUTE_OUTPUT                        , //211 GPA12
    GPIO_ATTRIBUTE_OUTPUT                        , //212 GPA13
    GPIO_ATTRIBUTE_OUTPUT                        , //213 GPA14
    GPIO_ATTRIBUTE_OUTPUT                        , //214 GPA15
    GPIO_ATTRIBUTE_OUTPUT                        , //215 GPA16
    GPIO_ATTRIBUTE_OUTPUT                        , //216 GPA17
    GPIO_ATTRIBUTE_OUTPUT                        , //217 GPA18
    GPIO_ATTRIBUTE_OUTPUT                        , //218 GPA19
    GPIO_ATTRIBUTE_OUTPUT                        , //219 GPA20
    GPIO_ATTRIBUTE_OUTPUT                        , //220 GPA21
    GPIO_ATTRIBUTE_OUTPUT                        , //221 GPA22
    GPIO_ATTRIBUTE_OUTPUT                        , //222 GPA23
    GPIO_ATTRIBUTE_OUTPUT                        , //223 GPA24
    GPIO_ATTRIBUTE_OUTPUT                        , //224 GPA25
    GPIO_ATTRIBUTE_OUTPUT                        , //225 GPA26  
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //226  GPB0 
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //227  GPB1
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //228  GPB2
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //229  GPB3
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //230  GPB4
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //231  GPB5
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //232  GPB6 (register 1)
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //233  GPB9
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //234  GPB10   
	GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //235  GPC0
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //236  GPC1
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //237  GPC2
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //238  GPC3
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //239  GPC4
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //240  GPC5
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //241  GPC6
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //242  GPC7
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //243  GPC8
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //244  GPC9
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //245  GPC10
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //246  GPC11
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //247  GPC12
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //248  GPC13
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //249  GPC14
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //250  GPC15  
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //251  GPD0
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //252  GPD1
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //253  GPD2
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //254  GPD3
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //255  GPD4
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //256  GPD5
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //257  GPD6
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //258  GPD7
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //259  GPD8
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //260  GPD9
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //261  GPD10
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //262  GPD11
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //263  GPD12
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //264  GPD13 (register 2)
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //265  GPD14
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //266  GPD15   
	GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //267  GPE0
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //268  GPE1
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //269  GPE2
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //270  GPE3
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //271  GPE4
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //272  GPE5
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //273  GPE6
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //274  GPE7
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //275  GPE8
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //276  GPE9
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //277  GPE10
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //278  GPE11
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //279  GPE12
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //280  GPE13
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //281  GPE14
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //282  GPE15   
	GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //283  GPF0
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //284  GPF1
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //285  GPF2
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //286  GPF3
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //287  GPF4
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //288  GPF5
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //289  GPF6
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //290  GPF7	
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //291  GPG0
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //292  GPG1
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //293  GPG2
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //294  GPG3
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //295  GPG4
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //296  GPG5 (register 3)
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //297  GPG6
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //298  GPG7
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //299  GPH0
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //300 GPH1
	
	GPIO_ATTRIBUTE_OUTPUT                        , //301 GPA1
    GPIO_ATTRIBUTE_OUTPUT                        , //302 GPA2
    GPIO_ATTRIBUTE_OUTPUT                        , //303 GPA3
    GPIO_ATTRIBUTE_OUTPUT                        , //304 GPA4
    GPIO_ATTRIBUTE_OUTPUT                        , //305 GPA5
    GPIO_ATTRIBUTE_OUTPUT                        , //306 GPA6
    GPIO_ATTRIBUTE_OUTPUT                        , //307 GPA7
    GPIO_ATTRIBUTE_OUTPUT                        , //308 GPA8
    GPIO_ATTRIBUTE_OUTPUT                        , //309 GPA9
    GPIO_ATTRIBUTE_OUTPUT                        , //310 GPA10
    GPIO_ATTRIBUTE_OUTPUT                        , //311 GPA12
    GPIO_ATTRIBUTE_OUTPUT                        , //312 GPA13
    GPIO_ATTRIBUTE_OUTPUT                        , //313 GPA14
    GPIO_ATTRIBUTE_OUTPUT                        , //314 GPA15
    GPIO_ATTRIBUTE_OUTPUT                        , //315 GPA16
    GPIO_ATTRIBUTE_OUTPUT                        , //316 GPA17
    GPIO_ATTRIBUTE_OUTPUT                        , //317 GPA18
    GPIO_ATTRIBUTE_OUTPUT                        , //318 GPA19
    GPIO_ATTRIBUTE_OUTPUT                        , //319 GPA20
    GPIO_ATTRIBUTE_OUTPUT                        , //320 GPA21
    GPIO_ATTRIBUTE_OUTPUT                        , //321 GPA22
    GPIO_ATTRIBUTE_OUTPUT                        , //322 GPA23
    GPIO_ATTRIBUTE_OUTPUT                        , //323 GPA24
    GPIO_ATTRIBUTE_OUTPUT                        , //324 GPA25
    GPIO_ATTRIBUTE_OUTPUT                        , //325 GPA26  
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //326  GPB0 
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //327  GPB1
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //328  GPB2
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //329  GPB3
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //330  GPB4
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //331  GPB5
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //332  GPB6 (register 1)
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //333  GPB9
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //334  GPB10   
	GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //335  GPC0
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //336  GPC1
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //337  GPC2
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //338  GPC3
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //339  GPC4
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //340  GPC5
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //341  GPC6
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //342  GPC7
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //343  GPC8
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //344  GPC9
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //345  GPC10
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //346  GPC11
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //347  GPC12
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //348  GPC13
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //349  GPC14
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //350  GPC15  
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //351  GPD0
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //352  GPD1
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //353  GPD2
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //354  GPD3
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //355  GPD4
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //356  GPD5
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //357  GPD6
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //358  GPD7
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //359  GPD8
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //360  GPD9
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //361  GPD10
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //362  GPD11
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //363  GPD12
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //364  GPD13 (register 2)
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //365  GPD14
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //366  GPD15   
	GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //367  GPE0
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //368  GPE1
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //369  GPE2
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //370  GPE3
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //371  GPE4
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //372  GPE5
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //373  GPE6
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //374  GPE7
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //375  GPE8
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //376  GPE9
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //377  GPE10
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //378  GPE11
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //379  GPE12
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //380  GPE13
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //381  GPE14
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //382  GPE15   
	GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //383  GPF0
    GPIO_ATTRIBUTE_INPUT | GPIO_ATTRIBUTE_OUTPUT, //384  GPF1

};

#if defined(ADS_LINKER_BUG__NOT_ALL_UNUSED_VARIABLES_ARE_REMOVED)
#pragma arm section rodata
#endif

//--//

#if defined(ADS_LINKER_BUG__NOT_ALL_UNUSED_VARIABLES_ARE_REMOVED)
#pragma arm section zidata = "g_S3C2416_GPIO_Driver"
#endif

S3C2416_GPIO_Driver g_S3C2416_GPIO_Driver;

#if defined(ADS_LINKER_BUG__NOT_ALL_UNUSED_VARIABLES_ARE_REMOVED)
#pragma arm section zidata
#endif

//--//

BOOL S3C2416_GPIO_Driver::Initialize()
{
    int i;

    // initialize the interrupt information
   // S3C2416  只有GPF和GPG才有中断
    {
        PIN_ISR_DESCRIPTOR* pinIsr = g_S3C2416_GPIO_Driver.m_PinIsr;

         for(i = 160; i < 224; i++)
        {
            pinIsr->m_pin     = i;
            pinIsr->m_intEdge = GPIO_INT_NONE;
            pinIsr->m_isr     = STUB_GPIOISRVector;
            pinIsr->m_param   = NULL;
            pinIsr->m_flags   = 0;
            pinIsr->m_completion.Initialize( );
            pinIsr->m_completion.InitializeForISR( &PIN_ISR_DESCRIPTOR::Fire, pinIsr );
            pinIsr++;
        }
    }

    SetDebounce( 20 );

    for(i = 0; i < c_MaxPorts; i++)
    {
        // initialize pins as free
       // S3C2416_PIO &pioX = S3C2416::PIO(i);

        g_S3C2416_GPIO_Driver.m_PinReservationInfo[i] = 0;
        
        //pioX.PIO_IDR = 0xffffffff;                // Disable all interrupts
      //  pioX.PIO_ISR ^= 0xffffffff;
    }
	EINTMASK = 0x00fffff0; //关闭所有中断
    // set unsed pins as specified in platform selector
#if defined(S3C2416_UNUSED_GPIOS)
    {
        struct UnusedGPIO
        {
            UINT8 Pin;
            UINT8 State;
        };

        static const UnusedGPIO c_Unused[] = { S3C2416_UNUSED_GPIOS };

        const UnusedGPIO* ptr = c_Unused;

        for(size_t i = 0; i < ARRAYSIZE(c_Unused); i++, ptr++)
        {
            if(ptr->State == RESISTOR_DISABLED)
            {
                EnableInputPin( (GPIO_PIN)ptr->Pin, FALSE, NULL, 0, GPIO_INT_NONE, RESISTOR_DISABLED );
            }
            else
            {
                EnableOutputPin( (GPIO_PIN)ptr->Pin, (BOOL)(ptr->State == RESISTOR_PULLUP) );
            }
        }
    }
#endif

    // register interrupt handler for all ports
    if(!CPU_INTC_ActivateInterrupt( S3C2416C_ID_PIOA, ISR, (void*)(size_t)0 )) return FALSE;
#if (S3C2416_MAX_GPIO > 32)
    if(!CPU_INTC_ActivateInterrupt( S3C2416C_ID_PIOB, ISR, (void*)(size_t)1 )) return FALSE;
#endif 

#if (S3C2416_MAX_GPIO > 64)
    if(!CPU_INTC_ActivateInterrupt( S3C2416C_ID_PIOC, ISR, (void*)(size_t)2 )) return FALSE;
#endif

#if (S3C2416_MAX_GPIO > 96)
    if(!CPU_INTC_ActivateInterrupt( S3C2416C_ID_PIOD, ISR, (void*)(size_t)3 )) return FALSE;
#endif

    //S3C2416的GPIO时钟默认已经打开，无需再操作
    // TODO: will be replaced by PMC API
/*
    S3C2416_PMC &pmc = S3C2416::PMC();
    pmc.EnablePeriphClock(S3C2416C_ID_PIOA);

#if  (S3C2416_MAX_GPIO > 32)
    pmc.EnablePeriphClock(S3C2416C_ID_PIOB);
#endif

#if  (S3C2416_MAX_GPIO > 64)
    pmc.EnablePeriphClock(S3C2416C_ID_PIOC);
#endif

#if  (S3C2416_MAX_GPIO > 96)
    pmc.EnablePeriphClock(S3C2416C_ID_PIOD);
#endif
*/
    return TRUE;
}

//--//

BOOL S3C2416_GPIO_Driver::Uninitialize()
{
    GLOBAL_LOCK(irq);

    // uninitialize the interrupt information
    {
        UINT32 volatile trash;
        int i;


        PIN_ISR_DESCRIPTOR* pinIsr = g_S3C2416_GPIO_Driver.m_PinIsr;
        for(i = 0; i < c_MaxPins; i++)
        {
            pinIsr->m_completion.Abort();

            pinIsr++;
        }
       /*
        for(i = 0; i < c_MaxPorts; i++)
        {
            S3C2416_PIO& pPioX = S3C2416::PIO(i);
            pPioX.PIO_IDR   = 0xffffffff;           // Disable all interrupts
            trash           = pPioX.PIO_ISR;        // flush pending
        }
		*/
			EINTMASK = 0x00fffff0; //关闭所有中断
			EINTPEND = 0x0; //清除所有中断标志位
    }

    if(!CPU_INTC_DeactivateInterrupt( S3C2416C_ID_PIOA )) return FALSE;
#if (S3C2416_MAX_GPIO > 32)
    if(!CPU_INTC_DeactivateInterrupt( S3C2416C_ID_PIOB )) return FALSE;
#endif 

#if (S3C2416_MAX_GPIO > 64)
    if(!CPU_INTC_DeactivateInterrupt( S3C2416C_ID_PIOC )) return FALSE;
#endif
    //S3C2416的GPIO时钟不关闭
    // TODO: will be replaced by PMC API
/*
    S3C2416_PMC &PMC = S3C2416::PMC();
    PMC.DisablePeriphClock(S3C2416C_ID_PIOA);
#if  (S3C2416_MAX_GPIO > 32)
    PMC.DisablePeriphClock(S3C2416C_ID_PIOB);
#endif

#if (S3C2416_MAX_GPIO > 64)
    PMC.DisablePeriphClock(S3C2416C_ID_PIOC);
#endif
  */
    return TRUE;
}

//--//

UINT32 S3C2416_GPIO_Driver::Attributes( GPIO_PIN Pin )
{
    if(Pin < c_MaxPins)
    {
        return c_Gpio_Attributes[Pin];
    }

    return GPIO_ATTRIBUTE_NONE;
}

//--//

void S3C2416_GPIO_Driver::DisablePin( GPIO_PIN pin, GPIO_RESISTOR resistorState, UINT32 dir_out, GPIO_ALT_MODE function )
{
    ASSERT(pin < c_MaxPins);

    UINT32  bitmask_pullup = 0x02 << (PinToBit ( pin ) * 2); //GPIOUDP用两个Bit来控制下拉
	UINT32  bitmask_pulldown = 0x01 << (PinToBit ( pin ) * 2); //GPIOUDP用两个Bit来控制上拉
	UINT32  bitmask_pulldisable = 0 << (PinToBit ( pin ) * 2); //GPIOUDP用两个Bit来控制关闭
	UINT32  bitmask  = 0xFF << (PinToBit ( pin ) * 2); //GPIOUDP用两个Bit来控制关闭
    UINT32  port = PinToPort( pin );
    UINT32  GPIOX  = GetPort(port);
	
    GLOBAL_LOCK(irq);
    if(resistorState == RESISTOR_DISABLED) 
	    GPIOX->GPIOUDP &= ~bitmask;  
        GPIOX->GPIOUDP |= bitmask_pulldisable;         // 禁止上下拉
    else if(resistorState == RESISTOR_PULLUP)
        GPIOX->GPIOUDP &= ~bitmask;  	
        GPIOX->GPIOUDP =  bitmask_pullup;            // 使能上拉
	else if(resistorState == RESISTOR_PULLDOWN)
	    GPIOX->GPIOUDP &= ~bitmask;  
	    GPIOX->GPIOUDP =  bitmask_pulldown;          //使能下拉
    }
	
	UINT32  bitmask_ = 1 << PinToBit ( pin ) ; //GPIOSEL用1Bit来Selects the function of port
    switch (function)
    {
        case GPIO_ALT_MODE_1:               // Enable Peripheral A function
            GPIOX->GPIOSEL &= ~bitmask;   
           // pioX.PIO_ASR = bitmask;
            break;

            
        case GPIO_ALT_MODE_2:               // Enable Peripheral B function
           GPIOX->GPIOSEL |= bitmask;  
          //  pioX.PIO_BSR = bitmask;
            break;
            
        default:        
            break;              
    }

    pioX.PIO_IDR = bitmask;                   // Disable the Input Change Interrupt       

    PIN_ISR_DESCRIPTOR& pinIsr = g_S3C2416_GPIO_Driver.m_PinIsr[ pin ];

    pinIsr.m_intEdge = GPIO_INT_NONE;
    pinIsr.m_isr     = STUB_GPIOISRVector;
    pinIsr.m_param   = NULL;
}

//--//

void S3C2416_GPIO_Driver::EnableOutputPin( GPIO_PIN pin, BOOL initialState )
{

    
    UINT32   bitmask  = 1 << PinToBit( pin );
    UINT32  port = PinToPort( pin );


    S3C2416_PIO &pioX = S3C2416::PIO (port);

    GLOBAL_LOCK(irq);

    pioX.PIO_PER = bitmask;                   // Enable PIO function
    
        if(initialState)
        pioX.PIO_SODR = bitmask;
    else
        pioX.PIO_CODR = bitmask;

    pioX.PIO_OER = bitmask;                   // Enable Output

    PIN_ISR_DESCRIPTOR& pinIsr = g_S3C2416_GPIO_Driver.m_PinIsr[ pin ];

    pinIsr.m_intEdge = GPIO_INT_NONE;
    pinIsr.m_isr     = STUB_GPIOISRVector;
    pinIsr.m_param   = NULL;

}

//--//

BOOL S3C2416_GPIO_Driver::EnableInputPin( GPIO_PIN pin, BOOL GlitchFilterEnable, GPIO_INTERRUPT_SERVICE_ROUTINE ISR, void* pinIsrParam, GPIO_INT_EDGE intEdge, GPIO_RESISTOR resistorState )
{
    ASSERT(pin < c_MaxPins);


    UINT32   bitmask  = 1 << PinToBit( pin );
    UINT32  port = PinToPort( pin );

    S3C2416_PIO &pioX = S3C2416::PIO (port);

    GLOBAL_LOCK(irq);   

    switch (resistorState)
    {
        case RESISTOR_DISABLED:
            pioX.PIO_PPUDR = bitmask;     // Disable the pull up resistor
            break;
        case RESISTOR_PULLUP:
            pioX.PIO_PPUER =  bitmask;        // Enable the pull up resistor
            break;
        case RESISTOR_PULLDOWN:
            return FALSE;                       // There are no pulldown resistors on the SAM9
    }

    PIN_ISR_DESCRIPTOR& pinIsr = g_S3C2416_GPIO_Driver.m_PinIsr[ pin ];

    pioX.PIO_PER = bitmask;                   // Enable PIO function
    pioX.PIO_ODR = bitmask;               // Disable Output

    pinIsr.m_intEdge = intEdge;
    pinIsr.m_isr     = (ISR != NULL) ? ISR : STUB_GPIOISRVector;
    pinIsr.m_param   = pinIsrParam;
    pinIsr.m_flags   = (GlitchFilterEnable == TRUE) ? PIN_ISR_DESCRIPTOR::c_Flags_Debounce : 0;
    pinIsr.m_status  = 0;      
    
#if !defined(PLATFORM_ARM_SAM7_ANY)
    pinIsr.m_completion.Abort();
    pinIsr.m_completion.Initialize();
#endif
    
    if(ISR)
    {
        // since there is no HW debounce, we always have to listen to both edges and 
        // filter the interrupt based on the desired edge and the debounce time 
        switch(intEdge)
        {
            case GPIO_INT_NONE:
                return FALSE;
            
            case GPIO_INT_EDGE_LOW :
            case GPIO_INT_LEVEL_LOW:
                pinIsr.m_status |= PIN_ISR_DESCRIPTOR::c_Status_AllowLowEdge;
                break;

            case GPIO_INT_EDGE_HIGH:
            case GPIO_INT_LEVEL_HIGH:
                pinIsr.m_status |= PIN_ISR_DESCRIPTOR::c_Status_AllowHighEdge;
                break;

            case GPIO_INT_EDGE_BOTH:
            {                 
                pinIsr.m_flags |= PIN_ISR_DESCRIPTOR::c_Flags_RequireHighEdge | PIN_ISR_DESCRIPTOR::c_Flags_RequireLowEdge;
                
                // check pin state before setting interrupt
                while(true)
                {
                    BOOL state = pioX.PIO_PDSR & bitmask;

                    if(state)
                    {
                        pinIsr.m_status &= ~PIN_ISR_DESCRIPTOR::c_Status_AllowHighEdge;
                        pinIsr.m_status |=  PIN_ISR_DESCRIPTOR::c_Status_AllowLowEdge;                      

                        // make sure we didn't miss an edge interrupt (and leave it deadlocked!)
                        if( !(pioX.PIO_PDSR & bitmask) )
                        {
                            continue;
                        }
                    }
                    else
                    {
                        pinIsr.m_status &= ~PIN_ISR_DESCRIPTOR::c_Status_AllowLowEdge;
                        pinIsr.m_status |=  PIN_ISR_DESCRIPTOR::c_Status_AllowHighEdge;

                        // make sure we didn't miss an edge interrupt (and leave it deadlocked!)
                        if( pioX.PIO_PDSR & bitmask )
                        {
                            continue;
                        }
                    }
                    break;
                }
            }
            break;

        default:
            ASSERT(0);
            return FALSE;
        }

        pioX.PIO_IER = bitmask;               // Enable interrupt
    }
    else
    {
        pioX.PIO_IDR = bitmask;               // Disable interrupt
    }
        
    return TRUE;
}


BOOL S3C2416_GPIO_Driver::GetPinState( GPIO_PIN pin )
{

    ASSERT(pin < c_MaxPins);

    UINT32  bit  = PinToBit( pin );
    UINT32  port = PinToPort( pin );

    S3C2416_PIO &pioX = S3C2416::PIO (port);

        return (((pioX.PIO_PDSR) >> bit) & 1);
}

//--//

void S3C2416_GPIO_Driver::SetPinState( GPIO_PIN pin, BOOL pinState )
{
    ASSERT(pin < c_MaxPins);

    UINT32  port = PinToPort( pin );
    UINT32  bit  = PinToBit ( pin );

    S3C2416_PIO &pioX = S3C2416::PIO (port);

    GLOBAL_LOCK(irq);

    if(pinState)
        pioX.PIO_SODR =  1 << bit;
    else
        pioX.PIO_CODR  = 1 << bit;
}

//--//

void S3C2416_GPIO_Driver::ISR( void* Param )
{
    
    UINT32  port = (UINT32)Param;
    
    S3C2416_PIO &pioX = S3C2416::PIO (port);    
    
    // fire off each change, one at a time
    UINT32 bitMask  = 0x00000001;
    UINT32 bitIndex = 0;

    UINT32 interruptsActive = pioX.PIO_ISR;
    
    while(interruptsActive)
    {
        while((interruptsActive & bitMask) == 0)
        {
            bitMask  <<= 1;
            ++bitIndex;
        }

        //--//

        GPIO_PIN pin = BitToPin( bitIndex, port);

        PIN_ISR_DESCRIPTOR& pinIsr = g_S3C2416_GPIO_Driver.m_PinIsr[ pin ];

        if(pinIsr.m_intEdge != GPIO_INT_NONE)
        {
            BOOL negativeEdge = TRUE;
            
            if(pinIsr.m_intEdge == GPIO_INT_EDGE_BOTH)
            {
                // which edge are we interrupting on?
                if(pinIsr.m_status & PIN_ISR_DESCRIPTOR::c_Status_AllowLowEdge)
                {
                    if( !(pioX.PIO_PDSR & bitMask) )
                        negativeEdge = TRUE;
                    else 
                        return;             // A pair of falling edge and rising edge may have been lost, exit without any handling
                }
                else if(pinIsr.m_status & PIN_ISR_DESCRIPTOR::c_Status_AllowHighEdge)
                {
                    if( pioX.PIO_PDSR & bitMask )
                        negativeEdge = FALSE;
                    else 
                        return;             // A pair of rising edge and falling edge may have been lost, exit without any handling 
                }                           
            }
            else
            {
                if(pinIsr.m_status & PIN_ISR_DESCRIPTOR::c_Status_AllowLowEdge)
                {
                    if( !(pioX.PIO_PDSR & bitMask) )
                    {
                        negativeEdge = TRUE;
                    }
                    else
                    {
                        return;             // throw out the unexpected falling edge
                    }
                }
                else if(pinIsr.m_status & PIN_ISR_DESCRIPTOR::c_Status_AllowHighEdge)
                {
                    if( pioX.PIO_PDSR & bitMask )
                    {
                        negativeEdge = FALSE;
                    }
                    else
                    {       
                        return;             // throw out the unexpected rising edge
                    }
                }
            }

            // send the interrupted state to the higher level
            if(pinIsr.m_flags & PIN_ISR_DESCRIPTOR::c_Flags_Debounce)
            {
                pinIsr.HandleDebounce( !negativeEdge );
            }
            else
            {
                pinIsr.Fire( (void*)&pinIsr );
            }
        }

        // remove the pin from the local check
        interruptsActive ^= bitMask;
    } 
}

//--//

void S3C2416_GPIO_Driver::SetResistor( GPIO_PIN pin, GPIO_RESISTOR resistorState )
{
    ASSERT(pin < c_MaxPins);

    UINT32  bitmask  = 1 << PinToBit( pin );
    UINT32  port = PinToPort( pin );

    S3C2416_PIO &pioX = S3C2416::PIO (port);

    GLOBAL_LOCK(irq);   

    switch (resistorState)
    {
        case RESISTOR_DISABLED:
            pioX.PIO_PPUDR = bitmask;     // Disable the pull up resistor
            break;
        case RESISTOR_PULLUP:
            pioX.PIO_PPUER =  bitmask;        // Enable the pull up resistor
            break;
        default:
            ASSERT(0);                          // There are no pulldown resistors on the SAM9
    }
    return;
}

//--//

BOOL S3C2416_GPIO_Driver::PinIsBusy( GPIO_PIN pin )
{
    UINT32  port     = pin / c_PinsPerPort;
    UINT32  bitMask  = 1 << PinToBit( pin );
    UINT32& res      = g_S3C2416_GPIO_Driver.m_PinReservationInfo[port];

    return (res & bitMask) != 0 ? TRUE : FALSE;
}

//--//

BOOL S3C2416_GPIO_Driver::ReservePin( GPIO_PIN pin, BOOL fReserve )
{
    GLOBAL_LOCK(irq);

    UINT32  port = pin / c_PinsPerPort;
    UINT32  bit  = PinToBit( pin );
    UINT32& res  = g_S3C2416_GPIO_Driver.m_PinReservationInfo[port];
    UINT32  mask = (fReserve ? 1u : 0u) << bit;

    if((res & (1u << bit)) == mask) return FALSE;

    if(fReserve)
    {
        res |= (1u << bit);
    }
    else
    {
        res &= ~(1u << bit);
    }

    return TRUE;
}

//--//

UINT32 S3C2416_GPIO_Driver::GetDebounce()
{
#if !defined(PLATFORM_ARM_SAM7_ANY)
    return CPU_TicksToTime( g_S3C2416_GPIO_Driver.m_DebounceTicks ) / TIME_CONVERSION__TO_MILLISECONDS;
#else
    // assume that it takes 16 ticks for each ms the user wants
    // this of course needs calibration and it boils down to assessing 
    // what the loop in HandleDebounce takes
    return (S3C2416_GPIO_Driver::PIN_ISR_DESCRIPTOR::c_DebounceCount >> 4);
#endif
}

BOOL S3C2416_GPIO_Driver::SetDebounce( INT64 debounceTimeMilliseconds )
{   
#if !defined(PLATFORM_ARM_SAM7_ANY)
    if(debounceTimeMilliseconds < c_MinDebounceTimeMs || c_MaxDebounceTimeMs < debounceTimeMilliseconds )
    {
        return FALSE;
    }

    g_S3C2416_GPIO_Driver.m_DebounceTicks = CPU_MillisecondsToTicks( (UINT32)debounceTimeMilliseconds );

    return TRUE;
#else
    // cannot specify the debounce time
    return FALSE;
#endif
}

//--//

void S3C2416_GPIO_Driver::GetPinsMap( UINT8* pins, size_t size )
{
    const UINT8*    src = c_Gpio_Attributes;
    UINT8* dst = pins;   
    UINT32 maxpin = c_MaxPins;

    if ( size ==0 ) return;
    while ((size--) && (maxpin --))
    {
        *dst = *src;  
        ++dst; ++src;
    }
}

    
//--//

void S3C2416_GPIO_Driver::STUB_GPIOISRVector( GPIO_PIN Pin, BOOL PinState, void* Param )
{
    lcd_printf( "\fSTUB_GPI %04x\r\n", (size_t)Param );

    DEBUG_HARD_BREAKPOINT();
}

//--//

void S3C2416_GPIO_Driver::PIN_ISR_DESCRIPTOR::Fire( void* arg )
{
    PIN_ISR_DESCRIPTOR* desc = (PIN_ISR_DESCRIPTOR*)arg;
        
    desc->m_isr( desc->m_pin, (desc->m_status & c_Status_AllowHighEdge) != 0, desc->m_param );

    if(desc->m_intEdge == GPIO_INT_EDGE_BOTH)
    {
        desc->m_status ^= PIN_ISR_DESCRIPTOR::c_Status_AllowLowEdge | PIN_ISR_DESCRIPTOR::c_Status_AllowHighEdge;
    }
}

//--//

//
// extern declarations are required by GCC compiler as it cannot resolve the constant values.
//
#if defined(__GNUC__)
extern const UINT8 S3C2416_GPIO_Driver::PIN_ISR_DESCRIPTOR::c_Status_AllowHighEdge;
extern const UINT8 S3C2416_GPIO_Driver::PIN_ISR_DESCRIPTOR::c_Status_AllowLowEdge;
#endif


#if !defined(PLATFORM_ARM_SAM7_ANY)
void S3C2416_GPIO_Driver::PIN_ISR_DESCRIPTOR::HandleDebounce( BOOL edge )
{
    ASSERT_IRQ_MUST_BE_OFF();

    m_completion.Abort();

    UINT8 statusMask = edge ? c_Status_AllowHighEdge  : c_Status_AllowLowEdge ;

    if(m_status & statusMask)
    {
        m_completion.EnqueueTicks( HAL_Time_CurrentTicks() + g_S3C2416_GPIO_Driver.m_DebounceTicks );
    }
}
#else
void S3C2416_GPIO_Driver::PIN_ISR_DESCRIPTOR::HandleDebounce( BOOL edge )
{
    ASSERT_IRQ_MUST_BE_OFF();

    UINT32 count = c_DebounceCount;

    // we implement debouce by reading the pin a finite number of times
    while(--count > 0)
    {
        if(GetPinState( m_pin ) != edge)
        {
            // it was a glitch
            return;
        }
    }

    // debounce test passed
    Fire( this );
}
#endif

