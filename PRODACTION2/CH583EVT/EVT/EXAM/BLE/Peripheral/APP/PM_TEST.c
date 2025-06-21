/********************************** (C) COPYRIGHT *******************************
 * File Name          : peripheral.C
 * Author             : zhangxiyi @WCH
 * Version            : v0.1
 * Date               : 2020/11/26
 * Description        :
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
 *******************************************************************************/

/*********************************************************************
 * INCLUDES
 */

// сюда можно писать различные тесты и процедуры для PM!! и вызывать их из основного цикла !!
// да бы не ломать основную прогу!!

#include <math.h>
#include <stdio.h>
#include <stdlib.h> // для перехода на русский язык

#include "CONFIG.h"
#include "my_assist32.h" // дополнительные битовые макросы и макросы типов заимственны из STM8 Raide
#include "my_test.h"
#include "my_large_LCD32.h"
#include "ext_my_directtest.h"
#include "lcd_test.h"
#include "PM_test.h"
#include "alex_board.h"




void PM_Test3(void);


//---------------------------------------PM секция

// unsigned int count;
 unsigned int it;// для Itoa
 char buffer [33];//для Itoa

 //****************начальная загрузка данных и инициализация работы c обновляемой flash памятью******************

 short int ConfigBufer[2]; // структурный буфер , для редко обновляемых очередей структур : расписание/ режим sfm итд
 #define   lengthConfig       2   // а также стартовой метки после: 1. обновления прошивки 2. сбросу к заводским настройкам

 short int SetTempereBufer[128];// часто обновляемый буфер устанавливаемой темпеартуры числа

 #define    lengthTestBuf            128
 unsigned char lengthTestBufPointer[256];// кольцевой указатель, работает в связке с данными SetTempereBufer[];

 short int  TestBuf[128] ;; // структурный буфер , для редко обновляемых очередей структур : расписание/ режим sfm итд
 #define    lengthTestBuf            128
 unsigned char lengthTestBufPointer[256];// кольцевой указатель, работает в связке с данными TestBufer[];

 short int TestBufShedul[64]; // структурный буфер , для редко обновляемых очередей структур : расписание/ режим sfm итд
 #define   lengthShedul      64
 unsigned char lengthTestBufPointer[256];// кольцевой указатель, работает в связке с данными TestBufShedul[];


 uint16_t   EEPROM_adress;
 short int counter;


//------------------------------------------------------------------------------------------------------




void DebugInit(void)
 {
     GPIOA_SetBits(GPIO_Pin_9);
     GPIOA_ModeCfg(GPIO_Pin_9, GPIO_ModeOut_PP_5mA);
   //   UART1_DefInit();
 }

 //-------------------------------------------------Конец определений для исходника РМ----------------//



void    PM_Test3(void)
 {


 }












