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
#define               SCHEDULE_RESERVE_6_BASE_ADR          2 +  BASE_EEPROM_ADR // �ߧѧ�ѧݧ�ߧ�� �ѧէ�֧�� �էݧ� �ާѧ��ڧӧ� TIME_RESERVE
#define               SHE_N                                126//7  // �ܧ�ݧڧ�ڧ�֧��ӧ� ��ݧ֧ާ֧ߧ��� �� �ާѧ��ڧӧ�
extern unsigned short SCHEDULE_RESERVE[SHE_N];
#define               SCHEDULE_Copy_N                      1 //18
#define               BASE_EEPROM_ADR                      0


#define               SYSTEM_RESERVE_6_BASE_ADR            2 +  SYSTEM_EEPROM_ADR// �ߧѧ�ѧݧ�ߧ�� �ѧէ�֧�� �էݧ� �ާѧ��ڧӧ� SYSTEM_RESERVE
#define               SR_N                                 7  // �ܧ�ݧڧ�ڧ�֧��ӧ� ��ݧ֧ާ֧ߧ��� �� �ާѧ��ڧӧ�
extern unsigned short SYSTEM_RESERVE[SR_N];
#define               SYSTEM_Copy_N                        18
#define               SYSTEM_EEPROM_ADR        BASE_EEPROM_ADR +256


#define               TEMPER_RESERVE_6_BASE_ADR            2 +  TEMPER_EEPROM_ADR// �ߧѧ�ѧݧ�ߧ�� �ѧէ�֧�� �էݧ� �ާѧ��ڧӧ� TEMPER_RESERVE
#define               TempR_N                              1// 7//1  // �ܧ�ݧڧ�ڧ�֧��ӧ� ��ݧ֧ާ֧ߧ��� �� �ާѧ��ڧӧ�
extern unsigned short TEMPER_RESERVE[TempR_N];
#define               TEMPER_Copy_N                        126// 18//18*7
#define               TEMPER_EEPROM_ADR        SYSTEM_EEPROM_ADR +256


#define               Repeat_N                             3

#define               SCHEDUL                 SCHEDULE_RESERVE // �է�ҧݧڧ��֧� �ܧ����ܧ�� �ߧѧ٧ӧѧߧڧ� �էݧ� SCHEDULE_RESERVE

#define               SCHED_3D                Shedull_Copy_Pointer // �է�ҧݧڧ��֧� �ܧ����ܧ�� �ߧѧ٧ӧѧߧڧ� �էݧ� Shedull_Copy_Pointer



//extern unsigned short SCH_RES[SHE_N];

//------------------------------------------FOR TIME DUBUG--------------------------------------
#define               BASE_EEPROM_ADR                      0
#define               TIME_RESERVE_6_BASE_ADR              2 +  BASE_EEPROM_ADR // ����짳��ۡ짳�짿�������ߡ짽 �짳�짷��ӡ째��ԡ�� �짷�짿��� ����짳��ԡ�ԡ짼�짵�짳 TIME_RESERVE
#define               TR_N                                 7  // �짾��ѡ짿�짼��ۡ짼��ۡ째��ԡ�ա짵��� ���짿�째����째�����ա�ѡ짵 �짵 ����짳��ԡ�ԡ짼�짵�째
extern unsigned short TIME_RESERVE[TR_N];
#define               Time_Copy_N                          18
#define               BASE_EEPROM_ADR                      0



//-------------------------------------�էݧ� �ԧݧѧӧߧ�ԧ� ��ܧ�ѧߧ�--------------------------------
#define SET_TEMPER                   0           // ��ܧѧ٧ѧ�֧ݧ� �ߧ� �֧ݧ֧ާ֧ߧ� �ާѧ�ڧӧ� " ��֧ާ�֧�ѧ���� �٧ѧէѧߧڧ�"

//-------------------------------------�էݧ� �ߧѧ����ۧܧ� ��ѧ��ڧ�ѧߧڧ�--------------------------------
//------------------------------------------��ҧ�ڧ� ��ܧѧ٧ѧ�֧ݧ�------------------------------------
#define   N_DAY                    7 // �ܧ�ݧڧ�֧��ӧ� �էߧ֧�




#define Shed_ph             0
#define Shed_pm             1
#define Shed_tp             2


//---------------------------------------------������������������ -------------------------------------------------
#define SET_ph_int1            0           // �֧ݧ֧ާ֧ߧ� �ާѧ�ڧӧ� " ��ѧ��"           / �ڧߧ�֧�ӧѧ� 1
#define SET_pm_int1            1           // e�ݧ֧ާ֧ߧ� �ާѧ�ڧӧ� " �ާڧߧ���"         / �ڧߧ�֧�ӧѧ� 1
#define SET_tp_int1            2           // �֧ݧ֧ާ֧ߧ� �ާѧ�ڧӧ� " ��֧ާ�֧�ѧ����"    / �ڧߧ�֧�ӧѧ� 1
//
#define SET_ph_int2            3           // �֧ݧ֧ާ֧ߧ� �ާѧ�ڧӧ� " ��ѧ��"           / �ڧߧ�֧�ӧѧ� 2
#define SET_pm_int2            4           // e�ݧ֧ާ֧ߧ� �ާѧ�ڧӧ� " �ާڧߧ���"         / �ڧߧ�֧�ӧѧ� 2
#define SET_tp_int2            5           // �֧ݧ֧ާ֧ߧ� �ާѧ�ڧӧ� " ��֧ާ�֧�ѧ����"    / �ڧߧ�֧�ӧѧ� 2
//
#define SET_ph_int3            6           // �֧ݧ֧ާ֧ߧ� �ާѧ�ڧӧ� " ��ѧ��"           / �ڧߧ�֧�ӧѧ� 3
#define SET_pm_int3            7           // e�ݧ֧ާ֧ߧ� �ާѧ�ڧӧ� " �ާڧߧ���"         / �ڧߧ�֧�ӧѧ� 3
#define SET_tp_int3            8           // �֧ݧ֧ާ֧ߧ� �ާѧ�ڧӧ� " ��֧ާ�֧�ѧ����"    / �ڧߧ�֧�ӧѧ� 3
//
#define SET_ph_int4            9           // �֧ݧ֧ާ֧ߧ� �ާѧ�ڧӧ� " ��ѧ��"           / �ڧߧ�֧�ӧѧ� 4
#define SET_pm_int4           10          // e�ݧ֧ާ֧ߧ� �ާѧ�ڧӧ� " �ާڧߧ���"          / �ڧߧ�֧�ӧѧ� 4
#define SET_tp_int4           11          // �֧ݧ֧ާ֧ߧ� �ާѧ�ڧӧ� " ��֧ާ�֧�ѧ����"     / �ڧߧ�֧�ӧѧ� 4
//
#define SET_ph_int5           12          // �֧ݧ֧ާ֧ߧ� �ާѧ�ڧӧ� " ��ѧ��"            / �ڧߧ�֧�ӧѧ� 5
#define SET_pm_int5           13          // e�ݧ֧ާ֧ߧ� �ާѧ�ڧӧ� " �ާڧߧ���"          / �ڧߧ�֧�ӧѧ� 5
#define SET_tp_int5           14          // �֧ݧ֧ާ֧ߧ� �ާѧ�ڧӧ� " ��֧ާ�֧�ѧ����"     / �ڧߧ�֧�ӧѧ� 5
//
#define SET_ph_int6           15          // �֧ݧ֧ާ֧ߧ� �ާѧ�ڧӧ� " ��ѧ��"            / �ڧߧ�֧�ӧѧ� 6
#define SET_pm_int6           16          // e�ݧ֧ާ֧ߧ� �ާѧ�ڧӧ� " �ާڧߧ���"          / �ڧߧ�֧�ӧѧ� 6
#define SET_tp_int6           17          // �֧ݧ֧ާ֧ߧ� �ާѧ�ڧӧ� " ��֧ާ�֧�ѧ����"     / �ڧߧ�֧�ӧѧ� 6



#define  DAY_SHUFT            18   // ������ߧ�� N ��ާ֧�֧ߧڧ� -  �ߧ� �ܧ�ݧڧ�֧��ӧ� ��ѧ�ѧާ֧���� �� ��էߧڧ� ����ܧѧ� �էݧ� ��ѧ��ڧ�ѧߧڧ�








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
