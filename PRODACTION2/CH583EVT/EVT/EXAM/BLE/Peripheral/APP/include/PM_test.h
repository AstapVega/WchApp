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


//---------------------------------------PM ��֧ܧ�ڧ�

 //extern unsigned int count;
 extern unsigned int it;// �էݧ� Itoa
 extern char buffer [33];//�էݧ� Itoa

 //****************�ߧѧ�ѧݧ�ߧѧ� �٧ѧԧ��٧ܧ� �էѧߧߧ�� �� �ڧߧڧ�ڧѧݧڧ٧ѧ�ڧ� ��ѧҧ��� c ��ҧߧ�ӧݧ�֧ާ�� flash ��ѧާ����******************

 extern short int ConfigBufer[2]; // �����ܧ���ߧ�� �ҧ��֧� , �էݧ� ��֧էܧ� ��ҧߧ�ӧݧ�֧ާ�� ���֧�֧է֧� �����ܧ��� : ��ѧ��ڧ�ѧߧڧ�/ ��֧اڧ� sfm �ڧ��
 #define   lengthConfig       2   // �� ��ѧܧا� ���ѧ���ӧ�� �ާ֧�ܧ� ����ݧ�: 1. ��ҧߧ�ӧݧ֧ߧڧ� �����ڧӧܧ� 2. ��ҧ���� �� �٧ѧӧ�է�ܧڧ� �ߧѧ����ۧܧѧ�

 extern short int SetTempereBufer[128];// ��ѧ��� ��ҧߧ�ӧݧ�֧ާ�� �ҧ��֧� ����ѧߧѧӧݧڧӧѧ֧ާ�� ��֧ާ�֧ѧ����� ��ڧ�ݧ�

 #define    lengthTestBuf            128
 extern unsigned char lengthTestBufPointer[256];// �ܧ�ݧ��֧ӧ�� ��ܧѧ٧ѧ�֧ݧ�, ��ѧҧ��ѧ֧� �� ��ӧ�٧ܧ� �� �էѧߧߧ�ާ� SetTempereBufer[];

 extern short int  TestBuf[128]; // �����ܧ���ߧ�� �ҧ��֧� , �էݧ� ��֧էܧ� ��ҧߧ�ӧݧ�֧ާ�� ���֧�֧է֧� �����ܧ��� : ��ѧ��ڧ�ѧߧڧ�/ ��֧اڧ� sfm �ڧ��
 #define    lengthTestBuf            128
 extern unsigned char lengthTestBufPointer[256];// �ܧ�ݧ��֧ӧ�� ��ܧѧ٧ѧ�֧ݧ�, ��ѧҧ��ѧ֧� �� ��ӧ�٧ܧ� �� �էѧߧߧ�ާ� TestBufer[];

 extern short int TestBufShedul[64]; // �����ܧ���ߧ�� �ҧ��֧� , �էݧ� ��֧էܧ� ��ҧߧ�ӧݧ�֧ާ�� ���֧�֧է֧� �����ܧ��� : ��ѧ��ڧ�ѧߧڧ�/ ��֧اڧ� sfm �ڧ��
 #define   lengthShedul      64
 extern unsigned char lengthTestBufPointer[256];// �ܧ�ݧ��֧ӧ�� ��ܧѧ٧ѧ�֧ݧ�, ��ѧҧ��ѧ֧� �� ��ӧ�٧ܧ� �� �էѧߧߧ�ާ� TestBufShedul[];



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
