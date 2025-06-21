/********************************** (C) COPYRIGHT *******************************
 * File Name          : peripheral.h
 * Author             : WCH
 * Version            : V1.0
 * Date               : 2018/12/11
 * Description        :
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
 *******************************************************************************/

#ifndef __my_FLASH_H
#define __my_FLASH_H

#ifdef __cplusplus
extern "C" {
#endif

extern unsigned short Test_a ,Test_b,pointerA,pointerB;

extern const unsigned short Shedull_Pointer[7][6][3] ;
extern unsigned short Shedull_Copy_Pointer[7][6][3] ;

extern unsigned short Shedull_Copy_Pointer_1D[6][3] ;

#define               BASE_EEPROM_ADR                      0
#define               SCHEDULE_RESERVE_6_BASE_ADR          2 +  BASE_EEPROM_ADR // §ß§Ñ§é§Ñ§Ý§î§ß§í§Û §Ñ§Õ§â§Ö§ã§ã §Õ§Ý§ñ §Þ§Ñ§ã§ã§Ú§Ó§Ñ TIME_RESERVE
#define               SHE_N                                126//7  // §Ü§à§Ý§Ú§é§Ú§é§Ö§ã§ä§Ó§à §ï§Ý§Ö§Þ§Ö§ß§ä§à§Ó §Ó §Þ§Ñ§ã§ã§Ú§Ó§Ö
extern unsigned short SCHEDULE_RESERVE[SHE_N];
#define               SCHEDULE_Copy_N                      1 //18
#define               BASE_EEPROM_ADR                      0


#define               SYSTEM_RESERVE_6_BASE_ADR            2 +  SYSTEM_EEPROM_ADR// §ß§Ñ§é§Ñ§Ý§î§ß§í§Û §Ñ§Õ§â§Ö§ã§ã §Õ§Ý§ñ §Þ§Ñ§ã§ã§Ú§Ó§Ñ SYSTEM_RESERVE
#define               SR_N                                 7  // §Ü§à§Ý§Ú§é§Ú§é§Ö§ã§ä§Ó§à §ï§Ý§Ö§Þ§Ö§ß§ä§à§Ó §Ó §Þ§Ñ§ã§ã§Ú§Ó§Ö
extern unsigned short SYSTEM_RESERVE[SR_N];
#define               SYSTEM_Copy_N                        18
#define               SYSTEM_EEPROM_ADR        BASE_EEPROM_ADR +256


#define               TEMPER_RESERVE_6_BASE_ADR            2 +  TEMPER_EEPROM_ADR// §ß§Ñ§é§Ñ§Ý§î§ß§í§Û §Ñ§Õ§â§Ö§ã§ã §Õ§Ý§ñ §Þ§Ñ§ã§ã§Ú§Ó§Ñ TEMPER_RESERVE
#define               TempR_N                              1// 7//1  // §Ü§à§Ý§Ú§é§Ú§é§Ö§ã§ä§Ó§à §ï§Ý§Ö§Þ§Ö§ß§ä§à§Ó §Ó §Þ§Ñ§ã§ã§Ú§Ó§Ö
extern unsigned short TEMPER_RESERVE[TempR_N];
#define               TEMPER_Copy_N                        126// 18//18*7
#define               TEMPER_EEPROM_ADR        SYSTEM_EEPROM_ADR +256


#define               Repeat_N                             3

#define               SCHEDUL                 SCHEDULE_RESERVE // §Õ§å§Ò§Ý§Ú§â§å§Ö§Þ §Ü§à§â§à§ä§Ü§à§Ö §ß§Ñ§Ù§Ó§Ñ§ß§Ú§Ö §Õ§Ý§ñ SCHEDULE_RESERVE

#define               SCHED_3D                Shedull_Copy_Pointer // §Õ§å§Ò§Ý§Ú§â§å§Ö§Þ §Ü§à§â§à§ä§Ü§à§Ö §ß§Ñ§Ù§Ó§Ñ§ß§Ú§Ö §Õ§Ý§ñ Shedull_Copy_Pointer



//extern unsigned short SCH_RES[SHE_N];

//------------------------------------------FOR TIME DUBUG--------------------------------------
#define               BASE_EEPROM_ADR                      0
#define               TIME_RESERVE_6_BASE_ADR              2 +  BASE_EEPROM_ADR // ¡ì§Á¡ì§³¡ì§Û¡ì§³¡ì§¿¡ì§à¡ì§Á¡ì§ß¡ì§½ ¡ì§³¡ì§·¡ì§Ó¡ì§¸¡ì§Ô¡ì§Ô ¡ì§·¡ì§¿¡ì§ã ¡ì§À¡ì§³¡ì§Ô¡ì§Ô¡ì§¼¡ì§µ¡ì§³ TIME_RESERVE
#define               TR_N                                 7  // ¡ì§¾¡ì§Ñ¡ì§¿¡ì§¼¡ì§Û¡ì§¼¡ì§Û¡ì§¸¡ì§Ô¡ì§Õ¡ì§µ¡ì§Ñ ¡ì§á¡ì§¿¡ì§¸¡ì§À¡ì§¸¡ì§Á¡ì§Õ¡ì§Ñ¡ì§µ ¡ì§µ ¡ì§À¡ì§³¡ì§Ô¡ì§Ô¡ì§¼¡ì§µ¡ì§¸
extern unsigned short TIME_RESERVE[TR_N];
#define               Time_Copy_N                          18
#define               BASE_EEPROM_ADR                      0



//-------------------------------------§Õ§Ý§ñ §Ô§Ý§Ñ§Ó§ß§à§Ô§à §ï§Ü§â§Ñ§ß§Ñ--------------------------------
#define SET_TEMPER                   0           // §å§Ü§Ñ§Ù§Ñ§ä§Ö§Ý§î §ß§Ñ §Ö§Ý§Ö§Þ§Ö§ß§ä §Þ§Ñ§ã§Ú§Ó§Ñ " §ä§Ö§Þ§á§Ö§â§Ñ§ä§å§â§Ñ §Ù§Ñ§Õ§Ñ§ß§Ú§ñ"

//-------------------------------------§Õ§Ý§ñ §ß§Ñ§ã§ä§â§à§Û§Ü§Ú §â§Ñ§ã§á§Ú§ã§Ñ§ß§Ú§ñ--------------------------------
//------------------------------------------§à§Ò§ë§Ú§Ö §å§Ü§Ñ§Ù§Ñ§ä§Ö§Ý§Ú------------------------------------
#define   N_DAY                    7 // §Ü§à§Ý§Ú§é§Ö§ã§ä§Ó§à §Õ§ß§Ö§Û




#define Shed_ph             0
#define Shed_pm             1
#define Shed_tp             2


//---------------------------------------------§ª§¯§´§¦§²§£§¡§­§½ -------------------------------------------------
#define SET_ph_int1            0           // §Ö§Ý§Ö§Þ§Ö§ß§ä §Þ§Ñ§ã§Ú§Ó§Ñ " §é§Ñ§ã§í"           / §Ú§ß§ä§Ö§â§Ó§Ñ§Ý 1
#define SET_pm_int1            1           // e§Ý§Ö§Þ§Ö§ß§ä §Þ§Ñ§ã§Ú§Ó§Ñ " §Þ§Ú§ß§å§ä§í"         / §Ú§ß§ä§Ö§â§Ó§Ñ§Ý 1
#define SET_tp_int1            2           // §Ö§Ý§Ö§Þ§Ö§ß§ä §Þ§Ñ§ã§Ú§Ó§Ñ " §ä§Ö§Þ§á§Ö§â§Ñ§ä§å§â§Ñ"    / §Ú§ß§ä§Ö§â§Ó§Ñ§Ý 1
//
#define SET_ph_int2            3           // §Ö§Ý§Ö§Þ§Ö§ß§ä §Þ§Ñ§ã§Ú§Ó§Ñ " §é§Ñ§ã§í"           / §Ú§ß§ä§Ö§â§Ó§Ñ§Ý 2
#define SET_pm_int2            4           // e§Ý§Ö§Þ§Ö§ß§ä §Þ§Ñ§ã§Ú§Ó§Ñ " §Þ§Ú§ß§å§ä§í"         / §Ú§ß§ä§Ö§â§Ó§Ñ§Ý 2
#define SET_tp_int2            5           // §Ö§Ý§Ö§Þ§Ö§ß§ä §Þ§Ñ§ã§Ú§Ó§Ñ " §ä§Ö§Þ§á§Ö§â§Ñ§ä§å§â§Ñ"    / §Ú§ß§ä§Ö§â§Ó§Ñ§Ý 2
//
#define SET_ph_int3            6           // §Ö§Ý§Ö§Þ§Ö§ß§ä §Þ§Ñ§ã§Ú§Ó§Ñ " §é§Ñ§ã§í"           / §Ú§ß§ä§Ö§â§Ó§Ñ§Ý 3
#define SET_pm_int3            7           // e§Ý§Ö§Þ§Ö§ß§ä §Þ§Ñ§ã§Ú§Ó§Ñ " §Þ§Ú§ß§å§ä§í"         / §Ú§ß§ä§Ö§â§Ó§Ñ§Ý 3
#define SET_tp_int3            8           // §Ö§Ý§Ö§Þ§Ö§ß§ä §Þ§Ñ§ã§Ú§Ó§Ñ " §ä§Ö§Þ§á§Ö§â§Ñ§ä§å§â§Ñ"    / §Ú§ß§ä§Ö§â§Ó§Ñ§Ý 3
//
#define SET_ph_int4            9           // §Ö§Ý§Ö§Þ§Ö§ß§ä §Þ§Ñ§ã§Ú§Ó§Ñ " §é§Ñ§ã§í"           / §Ú§ß§ä§Ö§â§Ó§Ñ§Ý 4
#define SET_pm_int4           10          // e§Ý§Ö§Þ§Ö§ß§ä §Þ§Ñ§ã§Ú§Ó§Ñ " §Þ§Ú§ß§å§ä§í"          / §Ú§ß§ä§Ö§â§Ó§Ñ§Ý 4
#define SET_tp_int4           11          // §Ö§Ý§Ö§Þ§Ö§ß§ä §Þ§Ñ§ã§Ú§Ó§Ñ " §ä§Ö§Þ§á§Ö§â§Ñ§ä§å§â§Ñ"     / §Ú§ß§ä§Ö§â§Ó§Ñ§Ý 4
//
#define SET_ph_int5           12          // §Ö§Ý§Ö§Þ§Ö§ß§ä §Þ§Ñ§ã§Ú§Ó§Ñ " §é§Ñ§ã§í"            / §Ú§ß§ä§Ö§â§Ó§Ñ§Ý 5
#define SET_pm_int5           13          // e§Ý§Ö§Þ§Ö§ß§ä §Þ§Ñ§ã§Ú§Ó§Ñ " §Þ§Ú§ß§å§ä§í"          / §Ú§ß§ä§Ö§â§Ó§Ñ§Ý 5
#define SET_tp_int5           14          // §Ö§Ý§Ö§Þ§Ö§ß§ä §Þ§Ñ§ã§Ú§Ó§Ñ " §ä§Ö§Þ§á§Ö§â§Ñ§ä§å§â§Ñ"     / §Ú§ß§ä§Ö§â§Ó§Ñ§Ý 5
//
#define SET_ph_int6           15          // §Ö§Ý§Ö§Þ§Ö§ß§ä §Þ§Ñ§ã§Ú§Ó§Ñ " §é§Ñ§ã§í"            / §Ú§ß§ä§Ö§â§Ó§Ñ§Ý 6
#define SET_pm_int6           16          // e§Ý§Ö§Þ§Ö§ß§ä §Þ§Ñ§ã§Ú§Ó§Ñ " §Þ§Ú§ß§å§ä§í"          / §Ú§ß§ä§Ö§â§Ó§Ñ§Ý 6
#define SET_tp_int6           17          // §Ö§Ý§Ö§Þ§Ö§ß§ä §Þ§Ñ§ã§Ú§Ó§Ñ " §ä§Ö§Þ§á§Ö§â§Ñ§ä§å§â§Ñ"     / §Ú§ß§ä§Ö§â§Ó§Ñ§Ý 6



#define  DAY_SHUFT            18   // §ã§å§ä§à§é§ß§à§Ö N §ã§Þ§Ö§ê§Ö§ß§Ú§Ö -  §ß§Ñ §Ü§à§Ý§Ú§é§Ö§ã§ä§Ó§à §á§Ñ§â§Ñ§Þ§Ö§ä§â§à§Ó §Ó §à§Õ§ß§Ú§ç §ã§å§ä§Ü§Ñ§ç §Õ§Ý§ñ §â§Ñ§ã§á§Ú§ã§Ñ§ß§Ú§ñ








extern void SCHEDULE_TO_FLASH(void);
extern void SYSTEM_TO_FLASH(void);
extern void SET_TEMPER_TO_FLASH(void);



//--prototypes for internal use
//void  init_LCD(void);             //use this function once at startup
//extern void  init_LCD(void);             //use this function once at startup



#ifdef __cplusplus
}
#endif

#endif
