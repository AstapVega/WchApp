/********************************** (C) COPYRIGHT *******************************
 * File Name          : peripheral.h
 * Author             : WCH
 * Version            : V1.0
 * Date               : 2018/12/11
 * Description        :
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
 *******************************************************************************/

#ifndef MY_SMALL_LCD8_H
#define MY_SMALL_LCD8_H

#ifdef __cplusplus
extern "C" {
#endif




/*********************************************************************
 * INCLUDES
 */
#include "my_assist8.h"


//-------------------types
typedef struct{ //§à§Õ§Ú§ß §Ü§à§Þ §Ú§Þ§Ö§Ö§ä §ä§â§Ú §á§à§â§ä§Ñ
    char a;
    char c;
    char d;
}cmpack;

//define   segments from 1 to 19
//------------------COM1
#define   C1_FR2_A            p2    //pa2 seg1
#define   C1_7D_A             p1    //pa1 seg2
#define   C1_T6_D             p6    //pd6 seg3
#define   C1_6D_D               p5  //pd5 seg4
#define   C1_T1_D               p4  //pd4 seg5
#define   C1_5D_D               p3  //pd3 seg6
#define   C1_T2_D               p2  //pd2 seg7
#define   C1_4D_D               p0  //pd0 seg8
#define   C1_T5_C               p7  //pc7 seg9
#define   C1_1D_C               p6  //pc6 seg10
//#define   C1_5F_C             p5  //pc5 seg11
#define   C1_2D_C               p4  //pc4 seg12
#define   C1_T4_C               p3  //pc3 seg13
#define   C1_3D_C               p2  //pc2 seg14
#define   C1_A_C                p1  //pc1 seg15
//------------------COM2
#define   C2_7E_A             p2    //pa2 seg1
#define   C2_7C_A             p1    //pa1 seg2
#define   C2_6E_D             p6    //pd6 seg3
#define   C2_6C_D               p5  //pd5 seg4
#define   C2_5E_D               p4  //pd4 seg5
#define   C2_5C_D               p3  //pd3 seg6
#define   C2_4E_D               p2  //pd2 seg7
#define   C2_4C_D               p0  //pd0 seg8
#define   C2_1E_C               p7  //pc7 seg9
#define   C2_1C_C               p6  //pc6 seg10
#define   C2_2E_C               p5  //pc5 seg11
#define   C2_2C_C               p4  //pc4 seg12
#define   C2_3E_C               p3  //pc3 seg13
#define   C2_3C_C               p2  //pc2 seg14
#define   C2_V_C                p1  //pc1 seg15
//------------------COM3
#define   C3_7G_A             p2    //pa2 seg1
#define   C3_7B_A             p1    //pa1 seg2
#define   C3_6G_D             p6    //pd6 seg3
#define   C3_6B_D               p5  //pd5 seg4
#define   C3_5G_D               p4  //pd4 seg5
#define   C3_5B_D               p3  //pd3 seg6
#define   C3_4G_D               p2  //pd2 seg7
#define   C3_4B_D               p0  //pd0 seg8
#define   C3_1G_C               p7  //pc7 seg9
#define   C3_1B_C               p6  //pc6 seg10
#define   C3_2G_C               p5  //pc5 seg11
#define   C3_2B_C               p4  //pc4 seg12
#define   C3_3G_C               p3  //pc3 seg13
#define   C3_3B_C               p2  //pc2 seg14
#define   C3_T7_C               p1  //pc1 seg15
//------------------COM4
#define   C4_7F_A             p2    //pa2 seg1
#define   C4_7A_A             p1    //pa1 seg2
#define   C4_6F_D             p6    //pd6 seg3
#define   C4_6A_D               p5  //pd5 seg4
#define   C4_5F_D               p4  //pd4 seg5
#define   C4_5A_D               p3  //pd3 seg6
#define   C4_4F_D               p2  //pd2 seg7
#define   C4_4A_D               p0  //pd0 seg8
#define   C4_1F_C               p7  //pc7 seg9
#define   C4_1A_C               p6  //pc6 seg10
#define   C4_2F_C               p5  //pc5 seg11
#define   C4_2A_C               p4  //pc4 seg12
#define   C4_3F_C               p3  //pc3 seg13
#define   C4_3A_C               p2  //pc2 seg14
#define   C4_T3_C               p1  //pc1 seg15

//------define §Þ§Ñ§ã§Ü§Ú §ß§Ñ §á§à§â§ä§í
#define  SM_PORTA       (u8)(p1|p2)
#define  SM_PORTC       (u8)~p0
#define  SM_PORTD       (u8)~(p1|p7)
//------------§Þ§Ñ§Ü§â§à§ã§í §á§à §ã§Ö§Ô§Þ§Ö§ß§ä§Ñ§Þ

#define FRAME2_ON           cm[0].a|=C1_FR2_A
#define FRAME2_OFF      cm[0].a&=~C1_FR2_A
#define PERCENT_ON      cm[0].d|=C1_T1_D
#define PERCENT_OFF     cm[0].d&=~C1_T1_D
#define MINUSUP_ON    cm[0].d|=C1_T6_D
#define MINUSUP_OFF   cm[0].d&=~C1_T6_D
#define MINUSDN_ON    cm[0].c|=C1_T5_C
#define MINUSDN_OFF   cm[0].c&=~C1_T5_C
#define DOT_UP_ON           cm[0].d|=C1_T2_D
#define DOT_UP_OFF      cm[0].d&=~C1_T2_D
#define DOT_DN_ON           cm[0].c|=C1_T4_C
#define DOT_DN_OFF      cm[0].c&=~C1_T4_C
#define A_ON                cm[0].c|=C1_A_C
#define A_OFF             cm[0].c&=~C1_A_C
#define V_ON                cm[1].c|=C2_V_C
#define V_OFF             cm[1].c&=~C2_V_C
#define LOCK_ON         cm[2].c|=C3_T7_C
#define LOCK_OFF        cm[2].c&=~C3_T7_C
#define CEL_C_ON            cm[3].c|=C4_T3_C
#define CEL_C_OFF           cm[3].c&=~C4_T3_C

//-------------§Þ§Ñ§Ü§â§à§ã§í §ß§Ñ §Ü§à§Þ§í

#define COM1_ON    GPIOA_SetBits(PIN1_LCD_COM1)
#define COM2_ON    GPIOA_SetBits(PIN2_LCD_COM2)
#define COM3_ON    GPIOA_SetBits(PIN3_LCD_COM3)
#define COM4_ON    GPIOA_SetBits(PIN4_LCD_COM4)

#define COM1_OFF   GPIOA_ResetBits(PIN1_LCD_COM1)
#define COM2_OFF   GPIOA_ResetBits(PIN2_LCD_COM2)
#define COM3_OFF   GPIOA_ResetBits(PIN3_LCD_COM3)
#define COM4_OFF   GPIOA_ResetBits(PIN4_LCD_COM4)

//---------------OLD EXAMLE STM8S--------------//
//#define COM1_ON     GPIOB->ODR|=p6;    //PB6
//#define COM2_ON     GPIOB->ODR|=p7;    //PB7
//#define COM3_ON     GPIOF->ODR|=p4;    //PF4
//#define COM4_ON     GPIOA->ODR|=p3;    //PA3

//#define COM1_OFF    GPIOB->ODR&=~p6;    //PB6
//#define COM2_OFF    GPIOB->ODR&=~p7;    //PB7
//#define COM3_OFF    GPIOF->ODR&=~p4;    //PF4
//#define COM4_OFF    GPIOA->ODR&=~p3;    //PA3

//---------------seven segment definitions
#define SEGA    0x01        //   __-A
#define SEGB    0x02        //  |   |- B
#define SEGC    0x04        //F-|   |
#define SEGD    0x08        //   __-G
#define SEGE    0x10        //  |   | -C
#define SEGF    0x20        //E-|   |
#define SEGG    0x40        //   __-D
//---------------

#define SIGN_DEFIS  (char)SEGG              // special symbols
#define SIGN_C          (char)(SEGA|SEGD|SEGE|SEGF)             // C
#define SIGN_o          (char)(SEGG|SEGD|SEGE|SEGC)             // o
#define SIGN_u          (char)(SEGD|SEGE|SEGC)                  // u
#define SIGN_t          (char)(SEGD|SEGE|SEGG|SEGF)             // t
#define SIGN_E          (char)(SEGA|SEGD|SEGE|SEGG|SEGF)        // E
#define SIGN_c          (char)(SEGG|SEGD|SEGE)                  // c
#define SIGN_d          (char)(SEGB|SEGC|SEGG|SEGD|SEGE)
#define SIGN_A          (char)(SEGA|SEGB|SEGC|SEGE|SEGF|SEGG)
#define SIGN_Y          (char)(SEGB|SEGC|SEGD|SEGF|SEGG)
#define SIGN_M1         (char)(SEGA|SEGB|SEGE|SEGF)
#define SIGN_M2         (char)(SEGA|SEGB|SEGC|SEGF)
#define SIGN_n          (char)(SEGG|SEGE|SEGC)
#define SIGN_O          (char)(SEGA|SEGB|SEGC|SEGD|SEGE|SEGF)
#define SIGN_r          (char)(SEGG|SEGE)
#define SIGN_KT         (char)(SEGG|SEGB)
#define SIGN_P          (char)(SEGA|SEGG|SEGB|SEGF|SEGE)
#define SIGN_H          (char)(SEGC|SEGG|SEGB|SEGF|SEGE)
#define SIGN_S          (char)(SEGA|SEGF|SEGG|SEGC|SEGD)
#define SIGN_L          (char)(SEGF|SEGE|SEGD)
#define SIGN_I          (char)(SEGF|SEGE)
#define SIGN_F          (char)(SEGA|SEGF|SEGE|SEGG)

//--------------§à§á§â§Ö§Õ§Ö§Ý§Ö§ß§Ú§ñ §æ§à§â§Þ§Ñ§ä§Ñ format
#define  MINUS    0x80      //1- §á§à§Ü§Ñ§Ù§Ñ§ä§î §Þ§Ú§ß§å§ã
#define  DECIMAL  0x40      //1- §á§à§Ü§Ñ§Ù§Ñ§ä§î §Õ§Ö§ã§ñ§ä§Ú§é§ß§å§ð §ä§à§é§Ü§å
#define  HIDE           0x20    //1- §ã§Ü§â§í§ä§î §Ý§Ú§Õ§Ú§â§å§ð§ë§Ú§Ö §ß§å§Ý§Ú


#define  DIGIT3   0x02    //§Þ§Ñ§â§Ü§Ö§â
#define  DIGIT2   0x01    //§Þ§Ñ§â§Ü§Ö§â
//-------------- minor definations
#define STATES 8
#define LASTSTATE  (STATES-1)
//--------------exported stuff
extern cmpack cm[];
extern void tick_on(void);

//--------------functions
void bindec_decoder(s16);
void pack123_value(s16,char);
void pack654_value(s16,char);
void pack123_custom(char,char,char);
void pack654_custom(char,char,char);
void pack_7d(char);
char get_symbol(char);
void setLCDon(void);
void setLCDoff(void);
void init_lcd(void);
void allseg(void);
void pack_1d(char);
void pack_2d(char);
void pack_3d(char);
void pack_4d(char);
void pack_5d(char);
void pack_6d(char);
void clearLCD(void);






/*********************************************************************
 * CONSTANTS
 */



/*********************************************************************
 * MACROS
 */

/*********************************************************************
 * FUNCTIONS
 */



/*********************************************************************
*********************************************************************/

#ifdef __cplusplus
}
#endif

#endif
