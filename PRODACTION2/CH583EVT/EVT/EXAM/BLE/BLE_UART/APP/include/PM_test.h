/********************************** (C) COPYRIGHT *******************************
 * File Name          : peripheral.h
 * Author             : WCH
 * Version            : V1.0
 * Date               : 2018/12/11
 * Description        :
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
 *******************************************************************************/

#ifndef PM_TEST_H
#define PM_TEST_H

#ifdef __cplusplus
extern "C" {
#endif


extern void PM_Test3(void);
extern void PM_Test2(void);
extern void PM_Test4(void);
extern void ADC_setup1(void);
extern void get_char_test1(void);
extern void DebugInit(void);

extern  float get_resist(float VrefBUF,float VntcBUF,float R_upper);
extern double get_tempere(double ResistNTC);
extern  int8_t tempere_sensor_error(double VrefBUF,double VntcBUF,double ResistNTCBUF );
extern void ADC_BUF_ON_OFF(int8 buf_ON);


//---------------------------------------PM §ã§Ö§Ü§è§Ú§ñ

 //extern unsigned int count;
 extern unsigned int it;// §Õ§Ý§ñ Itoa
 extern char buffer [33];//§Õ§Ý§ñ Itoa

 //****************§ß§Ñ§é§Ñ§Ý§î§ß§Ñ§ñ §Ù§Ñ§Ô§â§å§Ù§Ü§Ñ §Õ§Ñ§ß§ß§í§ç §Ú §Ú§ß§Ú§è§Ú§Ñ§Ý§Ú§Ù§Ñ§è§Ú§ñ §â§Ñ§Ò§à§ä§í c §à§Ò§ß§à§Ó§Ý§ñ§Ö§Þ§à§Û flash §á§Ñ§Þ§ñ§ä§î§ð******************

 extern short int ConfigBufer[2]; // §ã§ä§â§å§Ü§ä§å§â§ß§í§Û §Ò§å§æ§Ö§â , §Õ§Ý§ñ §â§Ö§Õ§Ü§à §à§Ò§ß§à§Ó§Ý§ñ§Ö§Þ§í§ç §à§é§Ö§â§Ö§Õ§Ö§Û §ã§ä§â§å§Ü§ä§å§â : §â§Ñ§ã§á§Ú§ã§Ñ§ß§Ú§Ö/ §â§Ö§Ø§Ú§Þ sfm §Ú§ä§Õ
 #define   lengthConfig       2   // §Ñ §ä§Ñ§Ü§Ø§Ö §ã§ä§Ñ§â§ä§à§Ó§à§Û §Þ§Ö§ä§Ü§Ú §á§à§ã§Ý§Ö: 1. §à§Ò§ß§à§Ó§Ý§Ö§ß§Ú§ñ §á§â§à§ê§Ú§Ó§Ü§Ú 2. §ã§Ò§â§à§ã§å §Ü §Ù§Ñ§Ó§à§Õ§ã§Ü§Ú§Þ §ß§Ñ§ã§ä§â§à§Û§Ü§Ñ§Þ

 extern short int SetTempereBufer[128];// §é§Ñ§ã§ä§à §à§Ò§ß§à§Ó§Ý§ñ§Ö§Þ§í§Û §Ò§å§æ§Ö§â §å§ã§ä§Ñ§ß§Ñ§Ó§Ý§Ú§Ó§Ñ§Ö§Þ§à§Û §ä§Ö§Þ§á§Ö§Ñ§â§ä§å§â§í §é§Ú§ã§Ý§Ñ

 #define    lengthTestBuf            128
 extern unsigned char lengthTestBufPointer[256];// §Ü§à§Ý§î§è§Ö§Ó§à§Û §å§Ü§Ñ§Ù§Ñ§ä§Ö§Ý§î, §â§Ñ§Ò§à§ä§Ñ§Ö§ä §Ó §ã§Ó§ñ§Ù§Ü§Ö §ã §Õ§Ñ§ß§ß§í§Þ§Ú SetTempereBufer[];

 extern short int  TestBuf[128]; // §ã§ä§â§å§Ü§ä§å§â§ß§í§Û §Ò§å§æ§Ö§â , §Õ§Ý§ñ §â§Ö§Õ§Ü§à §à§Ò§ß§à§Ó§Ý§ñ§Ö§Þ§í§ç §à§é§Ö§â§Ö§Õ§Ö§Û §ã§ä§â§å§Ü§ä§å§â : §â§Ñ§ã§á§Ú§ã§Ñ§ß§Ú§Ö/ §â§Ö§Ø§Ú§Þ sfm §Ú§ä§Õ
 #define    lengthTestBuf            128
 extern unsigned char lengthTestBufPointer[256];// §Ü§à§Ý§î§è§Ö§Ó§à§Û §å§Ü§Ñ§Ù§Ñ§ä§Ö§Ý§î, §â§Ñ§Ò§à§ä§Ñ§Ö§ä §Ó §ã§Ó§ñ§Ù§Ü§Ö §ã §Õ§Ñ§ß§ß§í§Þ§Ú TestBufer[];

 extern short int TestBufShedul[64]; // §ã§ä§â§å§Ü§ä§å§â§ß§í§Û §Ò§å§æ§Ö§â , §Õ§Ý§ñ §â§Ö§Õ§Ü§à §à§Ò§ß§à§Ó§Ý§ñ§Ö§Þ§í§ç §à§é§Ö§â§Ö§Õ§Ö§Û §ã§ä§â§å§Ü§ä§å§â : §â§Ñ§ã§á§Ú§ã§Ñ§ß§Ú§Ö/ §â§Ö§Ø§Ú§Þ sfm §Ú§ä§Õ
 #define   lengthShedul      64
 extern unsigned char lengthTestBufPointer[256];// §Ü§à§Ý§î§è§Ö§Ó§à§Û §å§Ü§Ñ§Ù§Ñ§ä§Ö§Ý§î, §â§Ñ§Ò§à§ä§Ñ§Ö§ä §Ó §ã§Ó§ñ§Ù§Ü§Ö §ã §Õ§Ñ§ß§ß§í§Þ§Ú TestBufShedul[];



 extern uint16_t   EEPROM_adress;
 extern short int counter;


 #define count1 25500
 #define RUN_RING_COUNT_BASE 25500
 #define BASE_EEPROM_ADR        0

//#define BASE_EEPROM_ADR        20



#ifdef __cplusplus
}
#endif

#endif
