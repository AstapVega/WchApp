/********************************** (C) COPYRIGHT *******************************
 * File Name          : peripheral.h
 * Author             : WCH
 * Version            : V1.0
 * Date               : 2018/12/11
 * Description        :
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
 *******************************************************************************/

#ifndef __MY_LARGE_LCD32_H
#define __MY_LARGE_LCD32_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************************************************************
 * INCLUDES
 */
#include "my_assist32.h"

//  CUSTOM MADE LCD FROM LANGFANG YAAN ELECTRONICS CO.
//--------------------------------lcd_flags

// ТИП LCD : если  define  SK3_LCD иначе  SK7_LCD

#define  SK3_LCD


#define     ANT               10

#define     ENABLE_LCD      0x00000001      //for users
#define     ENABLE_LCD_SYNC     0x00000002          //for synchronization
#define     BYPASS_ON_REQ       0x00000004          //
#define     BYPASS_ON       0x00000008          //
#define     BYPASS_OFF_REQ      0x00000010


#define     LCD_ACTIVE_TIME     250L // не использую для WCH
#define     LCD_DEAD_TIME       30L    // не использую для WCH

#define     LCD_DEAD_TIME_ARR   (LCD_DEAD_TIME-1)    // не использую для WCH
#define     LCD_ACTIVE_TIME_ARR (LCD_ACTIVE_TIME-1)  // не использую для WCH
//--------------------------------------

//#define  DEAD_TIME          FREQ_SYS / 350// рекомендуется при 3,5 в
//#define  ACTIVE_TIME        FREQ_SYS /170//

 //#define  DEAD_TIME          FREQ_SYS / 450 //хорошая контрасность и низкое послесвечение
// #define  ACTIVE_TIME        FREQ_SYS /170  //в диапазоне 3,0 -3,3 в
// #define  ACTIVE_TIME        FREQ_SYS /200  //в диапазоне 3,0 -3,3 в


//для нового клга китайского ЖКИ от Лавелько

#define  DEAD_TIME          FREQ_SYS / 650// рекомендуется при 3,5 в
#define  ACTIVE_TIME        FREQ_SYS /150//





//------------------------------fsm states (sequence in one com)
#define     CHARGE_ACT_COMX     ((s16)0) // не использую для WCH
#define     CHARGE_DEAD_COMX    ((s16)1) // не использую для WCH
#define     DISCHARGE_ACT_COMX  ((s16)2) // не использую для WCH
#define     DISCHARGE_DEAD_COMX ((s16)3) // не использую для WCH
#define     FSM_MASK        ((s16)3)
//------------------------------fsm2 states (sequence of coms)
#define     COM1_WORK       ((s16)0) // не использую для WCH
#define     COM2_WORK       ((s16)1) // не использую для WCH
#define     COM3_WORK       ((s16)2) // не использую для WCH
#define     COM4_WORK       ((s16)3) // не использую для WCH
#define     FSM2_MASK       ((s16)3) // не использую для WCH




 #ifdef SK3_LCD

//-------------------description of COM1 buffer for SK3 LCD

#define   TMPR1D_1A      0x00000400/*LCD15-4COM=bit11*/    //  1A  (LCD15) com1 // сегмент "A", 1 -й  восьмерки
#define   HOUSEIN_2H     0x00000080/*LCD12-4COM=bit8*/     //  T16 (LCD12) com1 // сегмент "приход"
#define   TMPR2D_2A      0x00002000/*LCD18-4COM=bit14*/    //  2A  (LCD18) com1 // сегмент "A", 2 -й  восьмерки
#define   CLOCK_9H       0x00010000/*LCD21-4COM=bit17*/    //  T21 (LCD21) com4 // сегмент "часы"
#define   TMPR3D_3A      0x00008000/*LCD20-4COM=bit16*/    //  3A  (LCD20) com1 // сегмент "A", 3 -й  восьмерки
#define   CELSIUM_3H     0x00004000/*LCD19-4COM=bit15*/    //  T1  (LCD19) com1 // сегмент "T" + знак "цельсий!
#define   PERCENT_2I     0x00000100/*LCD13-4COM=bit9*/     //  T14 (LCD13) com1 // сегмент "процент"
#define   HEAP_5D        0x00000000/*LCDxx-4COM=bitxx*/    //- знакоместо  не используется
#define   HEAP_4D        0x00000000/*LCDxx-4COM=bitxx*/    //- знакоместо  не используется
#define   HEAP_4I        0x00000000/*LCDxx-4COM=bitxx*/    //- знакоместо  не используется
#define   HAND_6H        0x00010000/*LCD21-4COM=bit17*/    //  T19 (LCD21) com3 // сегмент "рука"
#define   TIME6D_6D      0x00000001/*LCD5-4COM=bit1*/      //  4D  (LCD 5) com1 // сегмент "D", 4 -й восьмерки "часы"
#define   TIMEDOT_7H     0x00000002/*LCD6-4COM=bit2*/      //  Е2  (LCD 6) com1 // сегмент "цельсий" + "точка", в "часах"
#define   TIME7D_7D      0x00000004/*LCD7-4COM=bit3*/      //  5D  (LCD 7) com1 // сегмент "D", 5 -й восьмерки "часы"
#define   TIMESEP_8H     0x00000008/*LCD8-4COM=bit4*/      //  T4  (LCD 8) com1 // сегмент "двоеточие" в "часах"
#define   TIME8D_8D      0x00000010/*LCD9-4COM=bit5*/      //  6D  (LCD 9) com1 // сегмент "D", 6 -й восьмерки "часы"
#define   HEAT_9I        0x00010000/*LCD21-4COM=bit17*/    //  T20 (LCD21) com1 // сегмент "нагрев"
#define   TIME9D_9D      0x00000040/*LCD11-4COM=bit7*/     //  7D  (LCD11) com1 // сегмент "D", 7 -й восьмерки "часы"
#define   ANT_T22        0x00010000/*LCD21-4COM=bit17*/    //  T22 (LCD21) com2 // сегмент "ANT
#define   BAROUT_10H     0x00000100/*LCD13-4COM=bit9*/     //  T17 (LCD13) com2 // сегмент "уйти с обеда"

//-------------------description of COM2 buffer
#define   TMPR1D_1F      0x00000200/*LCD14-4COM=bit10*/    //  1F  (LCD14) com2 // сегмент "F", 1 -й  восьмерки
#define   TMPR1D_1B      0x00000400/*LCD15-4COM=bit11*/    //  1B  (LCD15) com2 // сегмент "B", 1 -й  восьмерки
#define   TMPR2D_2F      0x00001000/*LCD17-4COM=bit13*/    //  2F  (LCD17) com2 // сегмент "F", 2 -й  восьмерки
#define   TMPR2D_2B      0x00002000/*LCD18-4COM=bit14*/    //  2B  (LCD18) com2 // сегмент "B", 2 -й  восьмерки
#define   TMPR3D_3F      0x00004000/*LCD19-4COM=bit15*/    //  3F  (LCD19) com2 // сегмент "F", 3 -й  восьмерки
#define   TMPR3D_3B      0x00008000/*LCD20-4COM=bit16*/    //  3B  (LCD20) com2 // сегмент "B", 3 -й  восьмерки
#define   HEAP_4E        0x00000000/*LCDxx-4COM=bitxx*/    //- знакоместо  не используется
#define   HEAP_5E        0x00000000/*LCDxx-4COM=bitxx*/    //- знакоместо  не используется
#define   HEAP_4H        0x00000000/*LCDxx-4COM=bitxx*/    //- знакоместо  не используется
#define   HEAP_4G        0x00000000/*LCDxx-4COM=bitxx*/    //- знакоместо  не используется
#define   TIME6D_6C      0x00000001/*LCD5-4COM=bit1*/      //  4C  (LCD 5) com2 // сегмент "C", 4 -й восьмерки "часы"
#define   TIME6D_6E      0x00000002/*LCD6-4COM=bit2*/      //  4E  (LCD 6) com2 // сегмент "E", 4 -й восьмерки "часы"
#define   TIME7D_7C      0x00000004/*LCD7-4COM=bit3*/      //  5C  (LCD 7) com2 // сегмент "C", 5 -й восьмерки "часы"
#define   TIME7D_7E      0x00000008/*LCD8-4COM=bit4*/      //  5E  (LCD 8) com2 // сегмент "E", 5 -й восьмерки "часы"
#define   TIME8D_8C      0x00000010/*LCD9-4COM=bit5*/      //  6C  (LCD 9) com2 // сегмент "C", 6 -й восьмерки "часы"
#define   TIME8D_8E      0x00000020/*LCD10-4COM=bit6*/     //  6E  (LCD10) com2 // сегмент "E", 6 -й восьмерки "часы"
#define   TIME9D_9C      0x00000040/*LCD11-4COM=bit7*/     //  7C  (LCD11) com2 // сегмент "C", 7 -й восьмерки "часы"
#define   TIME9D_9E      0x00000080/*LCD12-4COM=bit8*/     //  7E  (LCD12) com2 // сегмент "E", 7 -й восьмерки "часы"
#define   UPMINUS_TEMP   0x00000080/*LCD12-4COM=bit8*/     //  7G  (LCD12) com3 // сегмент "G", "-" температуры задания
#define   BARIN_10B      0x00000800/*LCD16-4COM=bit12*/    //  T18 (LCD16) com1 // сегмент "прийти пообедать"

//-------------------description of COM3 buffer
#define   TMPR1D_1E      0x00000200/*LCD14-4COM=bit10*/    //  1E  (LCD14) com4 // сегмент "E", 1 -й  восьмерки
#define   TMPR1D_1G      0x00000200/*LCD14-4COM=bit10*/    //  1G  (LCD14) com3 // сегмент "G", 1 -й  восьмерки
#define   TMPR2D_2E      0x00001000/*LCD17-4COM=bit13*/    //  2E  (LCD17) com4 // сегмент "E", 2 -й  восьмерки
#define   TMPR2D_2G      0x00001000/*LCD17-4COM=bit13*/    //  2G  (LCD17) com3 // сегмент "G", 2 -й  восьмерки
#define   TMPR3D_3E      0x00004000/*LCD19-4COM=bit15*/    //  3E  (LCD19) com4 // сегмент "E", 3 -й  восьмерки
#define   TMPR3D_3G      0x00004000/*LCD19-4COM=bit15*/    //  3G  (LCD19) com3 // сегмент "G", 3 -й  восьмерки
#define   HEAP_5G        0x00000000/*LCDxx-4COM=bitxx*/    //- знакоместо  не используется
#define   HEAP_5I        0x00000000/*LCDxx-4COM=bitxx*/    //- знакоместо  не используется
#define   HEAP_4C        0x00000000/*LCDxx-4COM=bitxx*/    //- знакоместо  не используется
#define   HEAP_4F        0x00000000/*LCDxx-4COM=bitxx*/    //- знакоместо  не используется
#define   TIME6D_6G      0x00000002/*LCD6-4COM=bit2*/      //  4G  (LCD 6) com3 // сегмент "G", 4 -й восьмерки "часы"
#define   TIME6D_6F      0x00000002/*LCD6-4COM=bit2*/      //  4F  (LCD 6) com4 // сегмент "F", 4 -й восьмерки "часы"
#define   TIME7D_7G      0x00000008/*LCD8-4COM=bit4*/      //  5G  (LCD 8) com3 // сегмент "G", 5 -й восьмерки "часы"
#define   TIME7D_7F      0x00000008/*LCD8-4COM=bit4*/      //  5F  (LCD 8) com4 // сегмент "F", 5 -й восьмерки "часы"
#define   TIME8D_8G      0x00000020/*LCD10-4COM=bit6*/     //  6G  (LCD10) com3 // сегмент "D", 6 -й восьмерки "часы"
#define   TIME8D_8F      0x00000020/*LCD10-4COM=bit6*/     //  6F  (LCD10) com4 // сегмент "F", 6 -й восьмерки "часы"
#define   TIME9D_9G      0x00000080/*LCD12-4COM=bit8*/     //  7G  (LCD12) com3 // сегмент "G", 7 -й восьмерки "часы"
#define   TIME9D_9F      0x00000080/*LCD12-4COM=bit8*/     //  7F  (LCD12) com4 // сегмент "F", 7 -й восьмерки "часы"
#define   COM3_NA        0x00040000/*LCD23-4COM=bit19*/    //  NA  (LCD23) com3 // не определено
#define   HOUSEOUT_10C   0x00000020/*LCD10-4COM=bit6*/     //  T13 (LCD10) com1 // сегмент "уход из дома"

//-------------------description of COM4 buffer
#define   TMPR1D_1D      0x00000400/*LCD15-4COM=bit11*/    //  1D  (LCD15) com4 // сегмент "D", 1 -й  восьмерки
#define   TMPR1D_1C      0x00000400/*LCD15-4COM=bit11*/    //  1C  (LCD15) com3 // сегмент "C", 1 -й  восьмерки
#define   TMPR2D_2D      0x00002000/*LCD18-4COM=bit14*/    //  2D  (LCD18) com4 // сегмент "D", 2 -й  восьмерки
#define   TMPR2D_2C      0x00002000/*LCD18-4COM=bit14*/    //  2C  (LCD18) com3 // сегмент "C", 2 -й  восьмерки
#define   TMPR3D_3D      0x00008000/*LCD20-4COM=bit16*/    //  3D  (LCD20) com4 // сегмент "D", 3 -й  восьмерки
#define   TMPR3D_3C      0x00008000/*LCD20-4COM=bit16*/    //  3C  (LCD20) com3 // сегмент "C", 3 -й  восьмерки
#define   MOON_1H        0x00000100/*LCD13-4COM=bit9*/     //  T15 (LCD13) com3 // сегмент "луна"
#define   HEAP_5F        0x00000000/*LCDxx-4COM=bitxx*/    //- знакоместо  не используется
#define   HEAP_4B        0x00000000/*LCDxx-4COM=bitxx*/    //- знакоместо  не используется
#define   HEAP_4A        0x00000000/*LCDxx-4COM=bitxx*/    //- знакоместо  не используется
#define   TIME6D_6B      0x00000001/*LCD5-4COM=bit1*/      //  4B  (LCD 5) com3 // сегмент "B", 4 -й восьмерки "часы"
#define   TIME6D_6A      0x00000001/*LCD5-4COM=bit1*/      //  4A  (LCD 5) com4 // сегмент "A", 4 -й восьмерки "часы"
#define   TIME7D_7B      0x00000004/*LCD7-4COM=bit3*/      //  5B  (LCD 7) com3 // сегмент "B", 5 -й восьмерки "часы"
#define   TIME7D_7A      0x00000004/*LCD7-4COM=bit3*/      //  5A  (LCD 7) com4 // сегмент "A", 5 -й восьмерки "часы"
#define   TIME8D_8B      0x00000010/*LCD9-4COM=bit5*/      //  6B  (LCD 9) com3 // сегмент "B", 6 -й восьмерки "часы"
#define   TIME8D_8A      0x00000010/*LCD9-4COM=bit5*/      //  6A  (LCD 9) com4 // сегмент "A", 6 -й восьмерки "часы"
#define   TIME9D_9B      0x00000040/*LCD11-4COM=bit7*/     //  7B  (LCD11) com3 // сегмент "B", 6 -й восьмерки "часы"
#define   TIME9D_9A      0x00000040/*LCD11-4COM=bit7*/     //  7A  (LCD11) com4 // сегмент "A", 6 -й восьмерки "часы"
#define   LWMINUS_T      0x00000200/*LCD14-4COM=bit10*/    //  T3  (LCD14) com1 // сегмент "-", 1 -й большой восьмерки
#define   SUN_1I         0x00000100/*LCD13-4COM=bit9*/     //  Е12 (LCD13) com4 // сегмент "солнце",


//------------------------------- 7DAY BAR SEGMENTS ----------------------------------------------//

#define  SEG_1  0x00000800/*LCD13-4COM=bit12*/     //  T5  (LCD16) com4 // сегмент "понедельник"
#define  SEG_2  0x00000800/*LCD13-4COM=bit12*/     //  T6  (LCD16) com3 // сегмент "вторник"
#define  SEG_3  0x00000800/*LCD13-4COM=bit12*/     //  T7  (LCD16) com2 // сегмент "среда"
#define  SEG_4  0x00020000/*LCD22-4COM=bit18*/     //  T8  (LCD22) com2 // сегмент "четверг"
#define  SEG_5  0x00020000/*LCD22-4COM=bit18*/     //  T9  (LCD13) com3 // сегмент "пятница"
#define  SEG_6  0x00020000/*LCD22-4COM=bit18*/     //  T10 (LCD22) com4 // сегмент "субота"
#define  SEG_7  0x00020000/*LCD22-4COM=bit18*/     //  T11 (LCD13) com1 // сегмент "воскресение"



//-----------------------------------------REDEFINE FOR SK3 LCD--------------------------------------------------//

//----------------------- COM1---------------- for SK3 LCD-----------------------------------------------------//

#define /*1*/   NEW_TIME4D_4D       TIME6D_6D    //  4D  (LCD 5) com1 // сегмент "D", 4 -й восьмерки "часы"
#define /*2*/   NEW_TIME5D_5D       TIME7D_7D    //  5D  (LCD 7) com1 // сегмент "D", 5 -й восьмерки "часы"
#define /*3*/   TIMESEP_T4          TIMESEP_8H   //  T4  (LCD 8) com1 // сегмент "двоеточие" в "часах"
#define /*4*/   NEW_TIME6D_6D       TIME8D_8D    //  6D  (LCD 9) com1 // сегмент "D", 6 -й восьмерки "часы"
#define /*5*/   NEW_TIME6D_6G       TIME8D_8G    //  6D  (LCD 9) com1 // сегмент "D", 6 -й восьмерки "часы"
#define /*6*/   NEW_TIME7D_7D       TIME9D_9D    //  7D  (LCD11) com1 // сегмент "D", 7 -й восьмерки "часы"
#define /*7*/   HOUSEIN_T16         HOUSEIN_2H   //  T16 (LCD12) com1 // сегмент "приход"
#define /*8*/   PERCENT_T14         PERCENT_2I   //  T14 (LCD13) com1 // сегмент "процент"
#define /*9*/   NEW_LWMINUS_T3      LWMINUS_T    //  T3  (LCD14) com1 // сегмент "-", 1 -й большой восьмерки
#define /*10*/  NEW_BARIN_T18       BARIN_10B    //  T18 (LCD16) com1 // сегмент "прийти пообедать"
#define /*11*/  HEAT_T20            HEAT_9I      //  T20 (LCD21) com1 // сегмент "нагрев"
#define /*12*/  NEW_TMPR1D_1A       TMPR1D_1A    //  1A  (LCD15) com1 // сегмент "A", 1 -й  восьмерки
#define /*13*/  NEW_TMPR2D_2A       TMPR2D_2A    //  2A  (LCD18) com1 // сегмент "A", 2 -й  восьмерки
#define /*14*/  NEW_TMPR3D_3A       TMPR3D_3A    //  3A  (LCD20) com1 // сегмент "A", 3 -й  восьмерки



//----------------------- COM2-------------- for SK3 LCD-------------------------------------------------------//
#define /*1*/   NEW_TMPR1D_1F       TMPR1D_1F    //  1F  (LCD14) com2 // сегмент "F", 1 -й  восьмерки
#define /*2*/   NEW_TMPR1D_1B       TMPR1D_1B    //  1B  (LCD15) com2 // сегмент "B", 1 -й  восьмерки
#define /*3*/   NEW_TMPR2D_2F       TMPR2D_2F    //  2F  (LCD17) com2 // сегмент "F", 2 -й  восьмерки
#define /*4*/   NEW_TMPR2D_2B       TMPR2D_2B    //  2B  (LCD18) com2 // сегмент "B", 2 -й  восьмерки
#define /*5*/   NEW_TMPR3D_3F       TMPR3D_3F    //  3F  (LCD19) com2 // сегмент "F", 3 -й  восьмерки
#define /*6*/   NEW_TMPR3D_3B       TMPR3D_3B    //  3B  (LCD20) com2 // сегмент "B", 3 -й  восьмерки
#define /*7*/   NEW_TIME4D_4C       TIME6D_6C    //  4C  (LCD 5) com2 // сегмент "C", 4 -й восьмерки "часы"
#define /*8*/   NEW_TIME4D_4E       TIME6D_6E    //  4E  (LCD 6) com2 // сегмент "E", 4 -й восьмерки "часы"
#define /*9*/   NEW_TIME5D_5C       TIME7D_7C    //  5C  (LCD 7) com2 // сегмент "C", 5 -й восьмерки "часы"
#define /*10*/  NEW_TIME5D_5E       TIME7D_7E    //  5E  (LCD 8) com2 // сегмент "E", 5 -й восьмерки "часы"
#define /*11*/  NEW_TIME6D_6C       TIME8D_8C    //  6C  (LCD 9) com2 // сегмент "C", 6 -й восьмерки "часы"
#define /*12*/  NEW_TIME6D_6E       TIME8D_8E    //  6E  (LCD10) com2 // сегмент "E", 6 -й восьмерки "часы"
#define /*13*/  NEW_TIME7D_7C       TIME9D_9C    //  7C  (LCD11) com2 // сегмент "C", 7 -й восьмерки "часы"
#define /*14*/  NEW_TIME7D_7E       TIME9D_9E    //  7E  (LCD12) com2 // сегмент "E", 7 -й восьмерки "часы"
#define /*15*/  NEW_BAROUT_T17      BAROUT_10H   //  T17 (LCD13) com2 // сегмент "уйти с обеда"



//----------------------- COM3--------------for SK3 LCD--------------------------------------------------------//

#define /*1*/   NEW_TMPR2D_2G       TMPR2D_2G    //  2G  (LCD17) com3 // сегмент "G", 2 -й  восьмерки
#define /*2*/   NEW_TIME4D_4B       TIME6D_6B    //  4B  (LCD 5) com3 // сегмент "B", 4 -й восьмерки "часы"
#define /*3*/   NEW_TIME4D_4G       TIME6D_6G    //  4G  (LCD 6) com3 // сегмент "G", 4 -й восьмерки "часы"
#define /*4*/   NEW_TIME5D_5B       TIME7D_7B    //  5B  (LCD 7) com3 // сегмент "B", 5 -й восьмерки "часы"
#define /*5*/   NEW_TIME5D_5G       TIME7D_7G    //  5G  (LCD 8) com3 // сегмент "G", 5 -й восьмерки "часы"
#define /*6*/   NEW_TIME6D_6B       TIME8D_8B    //  6B  (LCD 9) com3 // сегмент "B", 6 -й восьмерки "часы"
#define /*7*/   NEW_TIME4D_4G       TIME6D_6G    // 4G   (LCD 6) com3 // сегмент "G", 4 -й восьмерки "часы"
#define /*8*/   NEW_TIME7D_7B       TIME9D_9B    //  7B  (LCD11) com3 // сегмент "B", 6 -й восьмерки "часы"
#define /*9*/   NEW_TIME7D_7G       TIME9D_9G    //  7G  (LCD12) com3 // сегмент "G", 7 -й восьмерки "часы"
#define /*10*/  NEW_MOON_T15        MOON_1H      //  T15 (LCD13) com3 // сегмент "луна"
#define /*11*/  NEW_TMPR1D_1C       TMPR1D_1C    //  1C  (LCD15) com3 // сегмент "C", 1 -й  восьмерки
#define /*12*/  NEW_TMPR1D_1G       TMPR1D_1G    //  1G  (LCD14) com3 // сегмент "G", 1 -й  восьмерки
#define /*13*/  NEW_TMPR2D_2C       TMPR2D_2C    //  2C  (LCD18) com3 // сегмент "C", 2 -й  восьмерки
#define /*14*/  NEW_TMPR3D_3C       TMPR3D_3C    //  3C  (LCD20) com3 // сегмент "C", 3 -й  восьмерки
#define /*15*/  NEW_TMPR3D_3G       TMPR3D_3G    //  3G  (LCD19) com3 // сегмент "G", 3 -й  восьмерки
#define /*16*/  NEW_HAND_T19        HAND_6H      //  T19 (LCD21) com3 // сегмент "рука"


//------------------------COM4-------------- for SK3 LCD-------------------------------------------------------//

#define /*1*/   NEW_TIME4D_4A       TIME6D_6A    //  4A  (LCD 5) com4 // сегмент "A", 4 -й восьмерки "часы"
#define /*2*/   NEW_TIME4D_4F       TIME6D_6F    //  4F  (LCD 6) com4 // сегмент "F", 4 -й восьмерки "часы"
#define /*3*/   NEW_TIME5D_5A       TIME7D_7A    //  5A  (LCD 7) com4 // сегмент "A", 5 -й восьмерки "часы"
#define /*4*/   NEW_TIME5D_5F       TIME7D_7F    //  5F  (LCD 8) com4 // сегмент "F", 5 -й восьмерки "часы"
#define /*5*/   NEW_TIME6D_6A       TIME8D_8A    //  6A  (LCD 9) com4 // сегмент "A", 6 -й восьмерки "часы"
#define /*6*/   NEW_TIME6D_6F       TIME8D_8F    //  6F  (LCD10) com4 // сегмент "F", 6 -й восьмерки "часы"
#define /*7*/   NEW_TIME7D_7A       TIME9D_9A    //  7A  (LCD11) com4 // сегмент "A", 6 -й восьмерки "часы"
#define /*8*/   NEW_TIME7D_7F       TIME9D_9F    //  7F  (LCD12) com4 // сегмент "F", 7 -й восьмерки "часы"
#define /*9*/   NEW_TMPR1D_1E       TMPR1D_1E    //  1E  (LCD14) com4 // сегмент "E", 1 -й  восьмерки
#define /*10*/  NEW_TMPR1D_1D       TMPR1D_1D    //  1D  (LCD15) com4 // сегмент "D", 1 -й  восьмерки
#define /*11*/  NEW_TMPR2D_2E       TMPR2D_2E    //  2E  (LCD17) com4 // сегмент "E", 2 -й  восьмерки
#define /*12*/  NEW_TMPR2D_2D       TMPR2D_2D    //  2D  (LCD18) com4 // сегмент "D", 2 -й  восьмерки
#define /*13*/  NEW_TMPR3D_3E       TMPR3D_3E    //  3E  (LCD19) com4 // сегмент "E", 3 -й  восьмерки
#define /*14*/  NEW_TMPR3D_3D       TMPR3D_3D    //  3D  (LCD20) com4 // сегмент "D", 3 -й  восьмерки
#define /*15*/  NEW_CLOCK_T21       CLOCK_9H     //  T21 (LCD21) com4 // сегмент "часы"

#else

// по умолчанию для большого LCD
//---------------------------------------DEFINE FOR SK7 LCD--------------------------------//

//-------------------description of COM1 buffer

#define     TMPR1D_1A   0x00000001
#define     HOUSEIN_2H  0x00000002
#define     TMPR2D_2A   0x00000004
#define     CLOCK_9H    0x00000008
#define     TMPR3D_3A   0x00000010
#define     CELSIUM_3H  0x00000020
#define     PERCENT_2I  0x00000040
#define     HEAP_5D     0x00000080
#define     HEAP_4D     0x00000100
#define     HEAP_4I     0x00000200
#define     HAND_6H     0x00000400
#define     TIME6D_6D   0x00000800
#define     TIMEDOT_7H  0x00001000
#define     TIME7D_7D   0x00002000
#define     TIMESEP_8H  0x00004000
#define     TIME8D_8D   0x00008000
#define     HEAT_9I     0x00010000
#define     TIME9D_9D   0x00020000
#define     LOCK_T2     0x00040000
#define     BAROUT_10H  0x00080000

//-------------------description of COM2 buffer
#define     TMPR1D_1F   0x00000001
#define     TMPR1D_1B   0x00000002
#define     TMPR2D_2F   0x00000004
#define     TMPR2D_2B   0x00000008
#define     TMPR3D_3F   0x00000010
#define     TMPR3D_3B   0x00000020
#define     HEAP_4E     0x00000040
#define     HEAP_5E     0x00000080
#define     HEAP_4H     0x00000100
#define     HEAP_4G     0x00000200
#define     TIME6D_6C   0x00000400
#define     TIME6D_6E   0x00000800
#define     TIME7D_7C   0x00001000
#define     TIME7D_7E   0x00002000
#define     TIME8D_8C   0x00004000
#define     TIME8D_8E   0x00008000
#define     TIME9D_9C   0x00010000
#define     TIME9D_9E   0x00020000
#define     UPMINUS_T1 0x00040000
#define     BARIN_10B   0x00080000

//-------------------description of COM3 buffer
#define     TMPR1D_1E   0x00000001
#define     TMPR1D_1G   0x00000002
#define     TMPR2D_2E   0x00000004
#define     TMPR2D_2G   0x00000008
#define     TMPR3D_3E   0x00000010
#define     TMPR3D_3G   0x00000020
#define     HEAP_5G     0x00000040
#define     HEAP_5I     0x00000080
#define     HEAP_4C     0x00000100
#define     HEAP_4F     0x00000200
#define     TIME6D_6G   0x00000400
#define     TIME6D_6F   0x00000800
#define     TIME7D_7G   0x00001000
#define     TIME7D_7F   0x00002000
#define     TIME8D_8G   0x00004000
#define     TIME8D_8F   0x00008000
#define     TIME9D_9G   0x00010000
#define     TIME9D_9F   0x00020000
#define     COM3_NA     0x00040000
#define     HOUSEOUT_10C    0x00080000

//-------------------description of COM4 buffer
#define     TMPR1D_1D   0x00000001
#define     TMPR1D_1C   0x00000002
#define     TMPR2D_2D   0x00000004
#define     TMPR2D_2C   0x00000008
#define     TMPR3D_3D   0x00000010
#define     TMPR3D_3C   0x00000020
#define     MOON_1H     0x00000040
#define     HEAP_5F     0x00000080
#define     HEAP_4B     0x00000100
#define     HEAP_4A     0x00000200
#define     TIME6D_6B   0x00000400
#define     TIME6D_6A   0x00000800
#define     TIME7D_7B   0x00001000
#define     TIME7D_7A   0x00002000
#define     TIME8D_8B   0x00004000
#define     TIME8D_8A   0x00008000
#define     TIME9D_9B   0x00010000
#define     TIME9D_9A   0x00020000
#define     LWMINUS_T   0x00040000
#define     SUN_1I      0x00080000

#endif



#define   ALLGEG        0x000fffff
//-----------------------------------вкл/выкл-- перебить под WCH что бы не тянуло энергию с делителя ??
//#define LCD_BIAS_ON     GPIOB->ODR|=p9
//#define LCD_BIAS_OFF  GPIOB->ODR&=~p9
//#define CHECK_BIAS      GPIOB->ODR&p9


//------------------------ПОД WCH !!!!!!!!!!!!!!

#define COM1_HIGH     GPIOB_SetBits(PIN1_LCD_COM1);    GPIOB_ModeCfg( PIN1_LCD_COM1, GPIO_ModeOut_PP_20mA )
#define COM2_HIGH     GPIOB_SetBits(PIN2_LCD_COM2);    GPIOB_ModeCfg( PIN2_LCD_COM2, GPIO_ModeOut_PP_20mA )
#define COM3_HIGH     GPIOB_SetBits(PIN3_LCD_COM3);    GPIOB_ModeCfg( PIN3_LCD_COM3, GPIO_ModeOut_PP_20mA )
#define COM4_HIGH     GPIOB_SetBits(PIN4_LCD_COM4);    GPIOB_ModeCfg( PIN4_LCD_COM4, GPIO_ModeOut_PP_20mA )


#define COM1_LOW      GPIOB_ResetBits(PIN1_LCD_COM1);  GPIOB_ModeCfg( PIN1_LCD_COM1, GPIO_ModeOut_PP_20mA )
#define COM2_LOW      GPIOB_ResetBits(PIN2_LCD_COM2);  GPIOB_ModeCfg( PIN2_LCD_COM2, GPIO_ModeOut_PP_20mA )
#define COM3_LOW      GPIOB_ResetBits(PIN3_LCD_COM3);  GPIOB_ModeCfg( PIN3_LCD_COM3, GPIO_ModeOut_PP_20mA )
#define COM4_LOW      GPIOB_ResetBits(PIN4_LCD_COM4);  GPIOB_ModeCfg( PIN4_LCD_COM4, GPIO_ModeOut_PP_20mA )


#define COM1_OUT      GPIOB_ModeCfg( PIN1_LCD_COM1, GPIO_ModeOut_PP_20mA )
#define COM2_OUT      GPIOB_ModeCfg( PIN2_LCD_COM2, GPIO_ModeOut_PP_20mA )
#define COM3_OUT      GPIOB_ModeCfg( PIN3_LCD_COM3, GPIO_ModeOut_PP_20mA )
#define COM4_OUT      GPIOB_ModeCfg( PIN4_LCD_COM4, GPIO_ModeOut_PP_20mA )



//----------------------определение виртуальных портов PORTA и PORTB для работы с сегментами
#define PORTA       0x00000000
// вариант маски для программного LCD порта PORTA, для возможности "раделить" виртуальные порты PORTA и PORTB,и последовательной   выгрузки
// подготовленных битовых значений  для состояний COM1,COM2,COM3,COM4  в GPIOB и GPIOА через функции charge_SEG и discharge_SEG
//  с учетом того что макросы определения пинов от p0-p24 у них  физически дублируются
//значение маски выбирается больше чем крайнее значение при установке крайнего рабочего бита  т.е для p15 //#define PORTB       0x00100000

#define   PORTB       0x10000000 //+  для макимального pin > p24

//#define PORTB       0x01000000 //+  для макимального pin = p24

//#define   PORTB       0x00100000//+   для макимального pin < p20
//#define   PORTB       0x00010000//+   для макимального pin = p15

//#define   PORTB       0x00000800//+   для макимального pin = p15
//0x00000800


#define SHIFT_OUT_SEG     0x00100000 // 4*5 =20 пин крутить ,т.е 20 сдвигов от значения SHIFT_OUT_SEG = 0x00100000
//( т.е B.100000000000000000000) на каждый LCD Pin через функции charge_SEG и discharge_SEG



//------------------- Модифицированное подключение с перенаправленными физически ногами

//------------------------ COM1 - COM4---------------------

  #define PIN1_LCD_COM1        p8         //   пин PB8  порта PORTB   // можно перенаправить
  #define PIN2_LCD_COM2        p7         //   пин PB7  порта PORTB   // можно перенаправить
  #define PIN3_LCD_COM3        p6         //   пин PB6  порта PORTB   // можно перенаправить
  #define PIN4_LCD_COM4        p5         //   пин PB5  порта PORTB   // можно перенаправить


//--------------------- LCD PINS +  порядковые пины  микроконтроллера под соответсвующий PORT_Х (PORTA и PORTB)

#define LCDPIN5       (PORTB|p20)    // pb20+
#define LCDPIN6       (PORTB|p19)    // pb19+
#define LCDPIN7       (PORTA|p15)    // pa15+
#define LCDPIN8       (PORTA|p14)    // pa14+
#define LCDPIN9       (PORTA|p13)    // pa13+
#define LCDPIN10      (PORTA|p12)    // pa12+

//#define LCDPIN11      (PORTA|p11)    // pa11+
//#define LCDPIN12      (PORTA|p10)    // pa10+

//#define LCDPIN11      (PORTA|p9)    // pa11+
//#define LCDPIN12      (PORTA|p8)    // pa10+


#define LCDPIN11      (PORTA|p9)    // pa11+
#define LCDPIN12      (PORTA|p8)    // pa10+


#define LCDPIN13      (PORTB|p18)    // pb18+
#define LCDPIN14      (PORTB|p17)    // pb17+
#define LCDPIN15      (PORTB|p16)    // pb16+
#define LCDPIN16      (PORTB|p9)     // pb9+
#define LCDPIN17      (PORTB|p4)     // pb4+
#define LCDPIN18      (PORTB|p3)     // pb3+
#define LCDPIN19      (PORTB|p2)     // pb2+
#define LCDPIN20      (PORTB|p1)     // pb1+
#define LCDPIN21      (PORTB|p0)     // pb0+
#define LCDPIN22      (PORTA|p6)     // pa6+
#define LCDPIN23      (PORTA|p3)     // pa3+
#define LCDPIN24      (PORTA|p2)     // pa2+


#define MASK_SEG_PORTB      (u32)(p20|p19|p18|p17|p16|p9|p4|p3|p2|p1|p0)//все активны кроме используемых для COM1-COM4 т.е в данном случае кроме:p5,p6,p7,p8

#ifndef  SK3_LCD       // Если большой экран
#define MASK_SEG_PORTA      (u32)(p15|p14|p13|p12|p11|p10|p6|p3|p2)//
#else
#define MASK_SEG_PORTA      (u32)(p15|p14|p13|p12|p11|p10|p6)//
#endif

#define MASK_COM_PORTB      (p5|p6|p7|p8) // можно потом перебить порты и маски!!

//#define SEGB_DEAD       GPIOB->ODR&=~MASK_SEG_PORTB // переделать для WCH  ??  макром маски на сегменты
//#define SEGA_DEAD       GPIOA->ODR&=~MASK_SEG_PORTA  //

#define SEGB_DEAD       GPIOB_ResetBits(MASK_SEG_PORTB);
#define SEGA_DEAD       GPIOA_ResetBits(MASK_SEG_PORTA);



//--------------------seven segment symbol generator
#define SEGA    0x01        //    __-A
#define SEGB    0x02        //  |   |- B
#define SEGC    0x04        //F-|   |
#define SEGD    0x08        //   __-G
#define SEGE    0x10        //  |   | -C
#define SEGF    0x20        //E-|   |
#define SEGG    0x40        //   __-D

#define SIGN_DEFIS      (char)SEGG              // special symbols
#define SIGN_C          (char)(SEGA|SEGD|SEGE|SEGF)
#define SIGN_o          (char)(SEGG|SEGD|SEGE|SEGC)
#define SIGN_u          (char)(SEGD|SEGE|SEGC)
#define SIGN_t          (char)(SEGD|SEGE|SEGG|SEGF)
#define SIGN_E          (char)(SEGA|SEGD|SEGE|SEGG|SEGF)
#define SIGN_c          (char)(SEGG|SEGD|SEGE)
#define SIGN_d          (char)(SEGB|SEGC|SEGG|SEGD|SEGE)
#define SIGN_A          (char)(SEGA|SEGB|SEGC|SEGE|SEGF|SEGG)
#define SIGN_Y          (char)(SEGB|SEGC|SEGD|SEGF|SEGG)
#define SIGN_M1         (char)(SEGA|SEGB|SEGE|SEGF)
#define SIGN_M2         (char)(SEGA|SEGB|SEGC|SEGF)
#define SIGN_n          (char)(SEGG|SEGE|SEGC)
#define SIGN_O          (char)(SEGA|SEGB|SEGC|SEGD|SEGE|SEGF)
#define SIGN_r          (char)(SEGG|SEGE)
#define SIGN_KT         (char)(SEGG|SEGB)
#define SIGN_P          (char)(SEGG|SEGB|SEGE|SEGA|SEGF)
#define SIGN_S          (char)(SEGG|SEGC|SEGD|SEGA|SEGF)
#define SIGN_H          (char)(SEGG|SEGC|SEGE|SEGB|SEGF)
#define SIGN_I          (char)(SEGF|SEGE)
#define SIGN_i          (char)(SEGC)
#define SIGN_L          (char)(SEGF|SEGE|SEGD)
#define SIGN_W1         (char)(SEGF|SEGE|SEGD|SEGC)
#define SIGN_W2         (char)(SEGB|SEGC|SEGD|SEGE)
#define SIGN_F          (char)(SEGA|SEGF|SEGG|SEGE)




//--------------------seven segment symbol generator for heap
//---each tetrad contains bit set for digit: tetrads located as com4:com3:com2:com1
//--bit set will be located at coms at bit 6,7,8,9.
#define     COM1_CL_MASK    0x000f
#define     COM2_CL_MASK    0x00f0
#define     COM3_CL_MASK    0x0f00
#define     COM4_CL_MASK    0xf000
//---------com4
#define     HSYM_5F     0x2000      //----------com4 description start
#define     HSYM_4B     0x4000
#define     HSYM_4A     0x8000
//---------com3
//      HEAP_5G             //frame has convient function
#define     HSYM_5I     0x0200
#define     HSYM_4C     0x0400
#define     HSYM_4F     0x0800
//---------com2
#define     HSYM_4E     0x0010
#define     HSYM_5E     0x0020
#define     HSYM_4H     0x0040
#define     HSYM_4G     0x0080
//---------com1
#define     HSYM_5D     0x0002
#define     HSYM_4D     0x0004
#define     HSYM_4I     0x0008


#define     ALL_SHUT_OFF    10      //position in array or incoming digit
//------------------------some functions definations
//----------------------interval control
#define     MOON        0L
#define     HOUSE_IN    1L
#define     BAR_OUT     2L
#define     BAR_IN      3L
#define     HOUSE_OUT   4L
#define     SUN     5L
//-----------------------------

//--prototypes for internal use
void  init_LCD(void);             //use this function once at startup
void  pack_temperature123D(int);  //use this function to update temperature
void  pack_temperature9876D(int); //use this function to update temperature for SK7 LCD
void  pack_temperature7654D(int); //use this function to update temperature for SK3 LCD
void  pack_temperature_TIME(int);//функция с общим вызовом для SK3 LCD и SK7 LCD, выводит температуру в знакоместо часов
void  pack_minutes(int);         //use this function to update minutes
void  pack_hours(int);           //use this function to update hours
void  pack_year(int16_t);
void  pack_heap(int);            //use this function to update number in frame
void  pack123D_custom(int);      //use this function to generate custom symbols
void  pack9876D_custom(int);     //use this function to generate custom symbols
void  enable_LCD(void);          //enable lcd
void  dissable_LCD(void);        //dissable lcd and remain discharge
void  houses_control(int);       //controls intervals
void  frame_5G_on(void);
void  frame_5G_off(void);
void  set_bypass_on(void);
void  set_bypass_off(void);
int   is_bypass_on(void);
int   cut_lcd_sync(void);
void  clear_screen(void);
void  pack1d(char);
void  pack2d(char);
void  pack3d(char);
void  pack4d(char);
void  pack5d(char);
void  pack6d(char);
void  pack7d(char);
void  pack8d(char);
void  pack9d(char);
char  get_symbol(char);
void  minusdw_on(void);
void  minusdw_off(void);
void  minusup_on(void);
void  minusup_off(void);
void  ANT_on(void);
void  ANT_off(void);
void  lock_on(void);
void  lock_off(void);
void  allseg(void);


#ifdef SK3_LCD

void    pack_day(int digit);
//------------------------------------7 DAYS PROTOTYPES ---------------------------//
void    SEG_1_on(void);
void    SEG_1_off(void);
void    SEG_2_on(void);
void    SEG_2_off(void);
void    SEG_3_on(void);
void    SEG_3_off(void);
void    SEG_4_on(void);
void    SEG_4_off(void);
void    SEG_5_on(void);
void    SEG_5_off(void);
void    SEG_6_on(void);
void    SEG_6_off(void);
void    SEG_7_on(void);
void    SEG_7_off(void);

#endif

//-----------------------------------------

//-- prototypes for external use
extern void    My_drive_ALL(void);
extern void  drive_ALL(void);
extern void  drive_COM1(void);
extern void  drive_COM2(void);
extern void  drive_COM3(void);
extern void  drive_COM4(void);
extern void  drive_COM_dead(void);
extern void  dead_time_phase(void);
extern void  charge_SEG(u32,u8);
extern void  discharge_SEG(u32,u8);
extern void  VideoToPort_SEG(void);
extern void  SEG_PortToLCD_OUT(u32,u8);
extern void COM1_COM4_Handler(void);
extern u16   bindec_decoder(int);
//-------------------------------------
extern void  init_LCD(void);             //use this function once at startup
extern void  pack_temperature123D(int);  //use this function to update temperature
extern void  pack_temperature9876D(int); //use this function to update temperature SK7 LCD
extern void  pack_temperature7654D(int); //use this function to update temperature SK3 LCD
extern void  pack_temperature_TIME(int);// функция с общим вызовом для SK3 LCD и SK7 LCD, выводит температуру в знакоместо часов
extern void  pack_minutes(int);         //use this function to update minutes
extern void  pack_hours(int);           //use this function to update hours
extern void  pack_year(int16_t);
extern void  pack_heap(int);            //use this function to update number in frame
extern void  pack123D_custom(int);      //use this function to generate custom symbols
extern void  pack9876D_custom(int);     //use this function to generate custom symbols
extern void  enable_LCD(void);          //enable lcd
extern void  dissable_LCD(void);        //dissable lcd and remain discharge
extern void  houses_control(int);       //controls intervals
extern void  sun_on(void);              // --start-- there and below is control of special signs/symbols
extern void  sun_off(void);
extern void  moon_on(void);
extern void  moon_off(void);
extern void  house_out_on(void);
extern void  house_out_off(void);
extern void  house_in_on(void);
extern void  house_in_off(void);
extern void  percent_on(void);
extern void  percent_off(void);
extern void  bar_out_on(void);
extern void  bar_out_off(void);
extern void  bar_in_on(void);
extern void  bar_in_off(void);
extern void  heat_on(void);
extern void  heat_off(void);
extern void  celsium_on(void);
extern void  celsium_off(void);
extern void  clock_on(void);
extern void  clock_off(void);
extern void  second_sep_on(void);
extern void  second_sep_off(void);
extern void  time_dots_on(void);
extern void  time_dots_off(void);
extern void  hand_on(void);
extern void  hand_off(void);
extern void  frame_5G_on(void);// только  SK7 (см LCD datasheet)
extern void  frame_5G_off(void);// только  SK7 (см LCD datasheet)
extern void  set_bypass_on(void);
extern void  set_bypass_off(void);
extern int   is_bypass_on(void);
extern int   cut_lcd_sync(void);
extern void  clear_screen(void);
extern void  pack1d(char);// SK3+SK7
extern void  pack2d(char);// SK3+SK7
extern void  pack3d(char);// SK3+SK7
extern void  pack4d(char);// только  SK3 (см LCD datasheet)
extern void  pack5d(char);// SK3+SK7 (см LCD datasheet)
extern void  pack6d(char);// SK3+SK7 (см LCD datasheet)
extern void  pack7d(char);// SK3+SK7 (см LCD datasheet)
extern void  pack8d(char);// только  SK7 (см LCD datasheet)
extern void  pack9d(char);// только  SK7 (см LCD datasheet)
extern char  get_symbol(char);
extern void  minusdw_on(void);
extern void  minusdw_off(void);
extern void  minusup_on(void);
extern void  minusup_off(void);
extern void  ANT_on(void);
extern void  ANT_off(void);
extern void  lock_on(void);
extern void  lock_off(void);
extern void  allseg(void);

#ifdef SK3_LCD

extern void    pack_day(int digit);
//------------------------------------7 DAYS EXT PROTOTYPES ---------------------------//

extern void    SEG_1_on(void);
extern void    SEG_1_off(void);
extern void    SEG_2_on(void);
extern void    SEG_2_off(void);
extern void    SEG_3_on(void);
extern void    SEG_3_off(void);
extern void    SEG_4_on(void);
extern void    SEG_4_off(void);
extern void    SEG_5_on(void);
extern void    SEG_5_off(void);
extern void    SEG_6_on(void);
extern void    SEG_6_off(void);
extern void    SEG_7_on(void);
extern void    SEG_7_off(void);

#endif

//------------------------------------МАКРОСЫ ДЛЯ МЕНЮ------------------------------------------//

#define   HandIcon                 hand_on();
#define   ProgIcon                 sun_on(); moon_on(); house_out_on();house_in_on();bar_out_on();bar_in_on();
#define   ClockIcon                clock_on();
#define   PowModeIcon              pack9876D_custom((SIGN_P << 24) | (SIGN_O << 16) | (SIGN_W1 << 8) | SIGN_W2);
#define   LockIcon                 lock_on();
#define   Celsium_Icon             celsium_on();

//--------------------------------------- TEMPERE & CLOCK OUT VIDEO MASK

#define  defis_heap             11
#define  non_heap               12

#define  non_min               100
#define  non_hour              101

#define  defise_time           104

#define  non_temp_small        1001
#define  non_temp_large        1002
#define  defise_temp           1003


//-------------------для Charge/ Disharge-------------------

extern  u32 tempB;
extern  u32 tempA;
extern  u32 mask;
extern  int cnt;
extern  u32 tmp ;


//-------------------------------------
extern u32 com1;   //buffer for com1
extern u32 com2;   //buffer for com2
extern u32 com3;   //buffer for com3
extern u32 com4;   //buffer for com4
extern s16 fsm;    //автомат // не испольую в WCH
extern s16 fsm2;   //автомат // не испольую в WCH

extern u32 outportA,outportB;

extern u32 COM1_charghe_PA,COM2_charghe_PA,COM3_charghe_PA,COM4_charghe_PA;
extern u32 COM1_charghe_PB,COM2_charghe_PB,COM3_charghe_PB,COM4_charghe_PB;

extern u32 COM1_discharghe_PA,COM2_discharghe_PA,COM3_dishcarghe_PA,COM4_dishcarghe_PA;
extern u32 COM1_discharghe_PB,COM2_discharghe_PB,COM3_dishcarghe_PB,COM4_dishcarghe_PB;



#define    out_LCD_ON       0x01
#define    out_LCD_OFF      0x00

#define    discharghe       0x01
#define    charghe          0x02

#define    com1_charge      0x01
#define    com1_discharge   0x02
#define    com2_charge      0x03
#define    com2_discharge   0x04
#define    com3_charge      0x05
#define    com3_discharge   0x06
#define    com4_charge      0x07
#define    com4_discharge   0x08
/*********************************************************************
*********************************************************************/

#ifdef __cplusplus
}
#endif

#endif
