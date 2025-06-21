/********************************** (C) COPYRIGHT *******************************
 * File Name          : peripheral.h
 * Author             : WCH
 * Version            : V1.0
 * Date               : 2018/12/11
 * Description        :
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
 *******************************************************************************/

#ifndef ALEX_MENU_H
#define ALEX_MENU_H

#ifdef __cplusplus
extern "C" {
#endif


/*********************************************************************
 * INCLUDES
 */

extern uint8_t menu_item, EE_save_time;
extern uint8_t day_period, week_index, week_index_dest, _index;


extern void keys(void);

extern FlagStatus K1_adc(void);
extern FlagStatus K2_adc(void);
extern FlagStatus K3_adc(void);
extern FlagStatus K4_adc(void);
extern void message(void);
//extern void menu(void);

extern void print_hex1(uint8_t d);
extern void print_hex4(uint16_t d);
extern void print_dec2(signed int a, BOOL m);
extern void print_dec3(signed int a);
extern void print_dec4(signed int a);

extern void print_dec4a(signed int a);
extern void print_time(uint8_t data1, uint8_t data2);
extern void print_day_period(uint8_t index);
extern void clear_minutes(void);
extern void clear_hours(void);
extern void print_week(uint8_t day);




/*********************************************************************
*********************************************************************/

#ifdef __cplusplus
}
#endif

#endif
