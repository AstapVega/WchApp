/********************************** (C) COPYRIGHT *******************************
 * File Name          : peripheral.h
 * Author             : WCH
 * Version            : V1.0
 * Date               : 2018/12/11
 * Description        :
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
 *******************************************************************************/

#ifndef MY_TEST_H
#define MY_TEST_H


#ifdef __cplusplus
extern "C" {
#endif




/*********************************************************************
 * INCLUDES
 */

extern void    Bit_Test(void);
extern void COM1_COM4_Handler_Test1(void);
extern void COM1_COM4_Handler_Test2(void);
extern void COM1_COM4_Handler_Test3(void);
extern void COM1_COM4_Handler_Test4(void);
extern void COM1_COM4_Handler_Test8(void);


extern vu32  GPIO_test;
extern uint8  CR1 ;
extern uint8 RING_FASE ;
extern uint8 inverstest,invers_image,second_sep_invers,invers_clock_icon;
extern uint8 invers_blynk_image,invers_blynk_image_1S;
extern uint8 Virtual_timer,Virtual_timer2,Virtual_timer3;
extern uint16 Tik_1_sek;
extern int Count_Tik,long_mode_Tik,plus_minus_Tik;
extern int8_t Count_Plus,Count_Minus,Count_Mode;


/*********************************************************************
*********************************************************************/

#ifdef __cplusplus
}
#endif

#endif
