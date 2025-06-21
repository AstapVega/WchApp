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


#include "CONFIG.h"

#include "my_FLASH.h"

#include "ext_my_directtest.h"

#include "PM_test.h"
#include "alex_board.h"
#include "menu_vlad.h"


// файл кольцевой записи основных параметров :

// 1. Первый параметр при считывании любой страницы  - буфера памяти минимальным размером 256 байт
// это заголовок - 0x55AA по адресу BASE ADD OFF CURENT ARRAY, если заголовка нет ил он поврежден -
//старница перезатирается и обновляется  полностью

//2.идентификатор  - флаг удачного обвновления  процесса последней записи  данного массива :
// 0x5555 - последння запись произведена по событию, если 0xAAAA -обновления не было по событию ли SLEEP

//3. колочиство последовательных обновляемых структуо завист от общего размера локально массива:
// для времени: N -  слов, где 6 - параметры самого времени
//


unsigned short  SCHEDULE_RESERVE[SHE_N];

#define    SCHEDUL        SCHEDULE_RESERVE // дублируем короткое название для SCHEDULE_RESERVE

unsigned short Shedull_Copy_Pointer[7][6][3] ;

unsigned short Shedull_Copy_Pointer_1D[6][3] ;

unsigned short  SYSTEM_RESERVE[SR_N];
unsigned short  TEMPER_RESERVE[TempR_N ];
unsigned short TIME_RESERVE[TR_N];

unsigned short Test_a = 22,Test_b = 33,pointerA,pointerB;

/*
const unsigned short Shedull_Pointer[7][6][3] = {
       // {{6,0,280},{8,0,290},{11,30,230},{12,30,240},{17,0,250},{22,30,270},},

        {{1,15,280},{7,25,290},{11,35,230},{15,45,240},{20,0,250},{23,0,270},},// минимальный интервал между периодами 30 мин
                                                                             // жестко 6 интервалов суточных
        {{6,0,280} ,{8,0,230}, {11,30,230},{12,30,230},{17,0,280},{22,0,230},},// все последовательные , но может быть что
        {{6,0,375} ,{8,0,230}, {11,30,230},{12,30,230},{17,0,280},{22,0,230},},// один интевал ==12 часов , а остальные 5 по
        {{6,0,385} ,{8,0,230}, {11,30,230},{12,30,230},{17,0,280},{22,0,230},},// 2 часа 40 минут...главное сумароное время
        {{6,0,280} ,{8,0,240}, {11,30,250},{12,30,260},{17,0,290},{22,0,300},},// и минимальное расстояние между границами
        {{8,0,280} ,{12,0,280},{14,0,280}, {17,0, 280},{20,0,280},{23,0,230},},// интервалов
        {{8,0,280} ,{12,0,280},{14,0,280}, {17,0, 280},{20,0,280},{22,0,230},}, // также нужно внести dead time +- 30 минут
        // возле полуночи, т.е крайняя точка интервала 6 = 23,30 а первая точка первого интервала
        // 00,30 , таким образом при копировании дней, не будет коализий, и будут соблюдатся
        // граничніе интервалы!!

};
*/

const unsigned short Shedull_Pointer[7][6][3] = {

        {{1,15,280},{7,25,290},{11,35,230},{15,45,240},{20,0,250},{23,0,270}},

        {{6,0,290} ,{8,0,230}, {11,30,240},{12,30,250},{17,0,260},{22,0,220}},

        {{1,15,280},{7,25,290},{11,35,230},{15,45,240},{20,0,250},{23,0,270}},

        {{6,0,290} ,{8,0,230}, {11,30,240},{12,30,250},{17,0,260},{22,0,220}},

        {{1,15,280},{7,25,290},{11,35,310},{15,45,320},{20,0,330},{23,0,270}},

        {{6,0,290} ,{8,0,230}, {11,30,240},{12,30,250},{17,0,260},{22,0,220}},

        {{1,15,280},{7,25,290},{11,35,230},{15,45,240},{20,0,250},{23,0,270}}



};

// когда выставлеям последовательно  интервалы с  1 по 6, то вначале задаем максимальное  время в 1 м интервале
// с учетом правила остатка времени, т.е  мах Time  для первого интервала, равен
// 24 - 30мин*5 (4.5 часа, т.е) т.е 21,30 маскимально отдаленная  точка для первого  интервала, и 30 мин - минимально
// приблеженная, итд для следующих остатков, но что бы они были не пустые, последовательны и с минимальным расстояние
//в 30 минут
// таким образом когда после установки времени интервала №1 = 21,30, следующий интервал предлагается начиная со времени
// 22.00 итд, т.е вычисляем динамически остаток


//2) если мы коректируем текущую программу, то меняем границы с учетом правила крайних 30 минут ,

// при нажатии кнопок "+" или "-" мы анализируем левую и правую границы соседних интервалов и даем вариант ограничения
//выставляемых значений времени, это ВАЖНО, что бы было коректный и посдеовательный ход времени по заданному расписанию





void SET_TEMPER_TO_FLASH(void);

void SET_TEMPER_TO_FLASH(void)
{
static unsigned short a,b,c,d,i,s,ERROR,rewrite,BUSY_MEMORY_ADR, FREE_MEMORY_ADR;
static unsigned short BUFF_TEMPER_RESERVE[TempR_N];// буфер для контрольной копии массива времени TEMPER_RESERVE
static unsigned short TEMPER_Copy_Pointer[TEMPER_Copy_N]; //указатель свободного EEPROM для страницы в 128 элементов(256 байт)
// для пересохранения параметров текущего времени, с учетом состояния кольцевого буфера

a=0,b=0,c=0,d=0,i=0,s=0,ERROR=0,rewrite=0,BUSY_MEMORY_ADR=0, FREE_MEMORY_ADR=0;
// хоть переменные мы обьявили как static..их надо очищать перед использованием


//#define   SET_TEMPER_TO_FLASH

#ifndef  SET_TEMPER_TO_FLASH
      GPIOB_SetBits(bTXD1);
      GPIOB_ModeCfg(bTXD1, GPIO_ModeOut_PP_5mA);
#endif


TEMPER_RESERVE[0]= setup_temp;
//TEMPER_RESERVE[1]= pmon;
//TEMPER_RESERVE[2]= pd;
//TEMPER_RESERVE[3]= ph;
//TEMPER_RESERVE[4]= pm;
//TEMPER_RESERVE[5]= ps;
//TEMPER_RESERVE[6]= 0x5555;



  // запускаем процедуру записи в кольцевой буфер текущих параметров времени

    while((rewrite<Repeat_N)||(ERROR>0))// счетчик количества перезаписей  N=5
       {
// Читаем состояние и определяем свободное место в кольцевом буфере, формируем актуальный указатель для записи
//   в EEPROM

//1.
   s= EEPROM_READ(TEMPER_EEPROM_ADR , &TestBuf, 256);// читаем и оределяем указатель
   //свободного  места в EEPROM[128] под параметры ВРЕМЕНИ, с учетов общего выделенного места и
   //размером массива TIME_RESERVE

  a=0;  // control breakpoint
  BUSY_MEMORY_ADR=0;
  i = 0;

   for(i = 0; i < TEMPER_Copy_N; i++)// анализируем очередь прочитанных указателей для каждого массива "ВРЕМЕНИ"       {
{

   a=TestBuf[(i*TempR_N)+1];// +1 линейный сдвиг на первое стационарное слово из 2х байт = 0x55AA;

    if (a!=0xFFFF)
   {
   BUSY_MEMORY_ADR++; // control breakpoint
   }

   }

#ifndef  SET_TEMPER_TO_FLASH
   PRINT("\n");
   PRINT("\n");//control breakpoint

   PRINT(" BUSY_MEMORY_ADR         ----------------------------------->>     = %hu\n",BUSY_MEMORY_ADR-1);
#endif
   if((BUSY_MEMORY_ADR<TEMPER_Copy_N)&(BUSY_MEMORY_ADR>0))// если свободный указатель доступен из выделенного максимума памяти
     {

   FREE_MEMORY_ADR=BUSY_MEMORY_ADR; // то определяем текущую сободную память
#ifndef  SET_TEMPER_TO_FLASH
   PRINT(" 0 + FREE_MEMORY_ADR   ----------------------------------->>     = %hu\n",FREE_MEMORY_ADR);
#endif
     }
   else {

   if(BUSY_MEMORY_ADR==TEMPER_Copy_N)
         {

   s = EEPROM_ERASE(TEMPER_EEPROM_ADR, EEPROM_MIN_ER_SIZE);// стираем всю страницу  в 256  байт
#ifndef  SET_TEMPER_TO_FLASH
   PRINT("\n");
   PRINT(" SCHEDULE_Copy_N  &  ERASE START !! =  -------------------------->>     = %hu\n",SCHEDULE_Copy_N);
   PRINT("\n");
#endif
   a=0x55AA;// пишем стартовый ключ в первый два байта
   s=  EEPROM_WRITE(TEMPER_EEPROM_ADR , &a, 2);

   BUSY_MEMORY_ADR=0; // и сбрасываем все указетели в "0"
   FREE_MEMORY_ADR=0; // и сбрасываем все указетели в "0"
#ifndef  SET_TEMPER_TO_FLASH
   PRINT(" ERASE TIME EEPROM PAGE  OK  ------------------------------->>     = %hu\n",s);
   PRINT(" BUSY_MEMORY_ADR         ----------------------------------->>     = %hu\n",BUSY_MEMORY_ADR-1);
   PRINT(" 0 + FREE_MEMORY_ADR     ----------------------------------->>     = %hu\n",FREE_MEMORY_ADR);
#endif
  //------------------------------------------- DEBUG -------------------------------------------//
#ifndef  SET_TEMPER_TO_FLASH
   PRINT("EEPROM_READ... \n");
#endif

   EEPROM_READ(TEMPER_EEPROM_ADR, TestBuf,  lengthTestBuf*2);

#ifndef  SET_TEMPER_TO_FLASH
   for(i = 0; i < lengthTestBuf; i++)
                 {
   PRINT("%hu ", TestBuf[i]);
                  }
   PRINT("\n");
#endif
  //------------------------------------------- END OFF DEBUG -------------------------------------------//

         }

   if(BUSY_MEMORY_ADR==0)
                  {
#ifndef  SET_TEMPER_TO_FLASH
   PRINT(" BUSY_MEMORY_ADR         ----------------------------------->>     = %hu\n",BUSY_MEMORY_ADR-1);
   PRINT(" 0 + FREE_MEMORY_ADR     ----------------------------------->>     = %hu\n",FREE_MEMORY_ADR);
#endif
   //------------------------------------------- DEBUG -------------------------------------------//
#ifndef  SET_TEMPER_TO_FLASH
   PRINT("EEPROM_READ... \n");
#endif

   EEPROM_READ(TEMPER_EEPROM_ADR, TestBuf,  lengthTestBuf*2);

#ifndef  SET_TEMPER_TO_FLASH
   for(i = 0; i < lengthTestBuf; i++)
                    {
   PRINT("%hu ", TestBuf[i]);
                     }
   PRINT("\n");
#endif
     //------------------------------------------- END OFF DEBUG -------------------------------------------//

    }

    }

   b= FREE_MEMORY_ADR* TempR_N*2;//
   b= b+ TEMPER_RESERVE_6_BASE_ADR;// + линейный сдвиг на первое стационарное слово из 2х байт

   s= EEPROM_WRITE( b  , &TEMPER_RESERVE, TempR_N*2); //записываем  массив TIME_RESERVE в свободную  EEPROM

#ifndef  SET_TEMPER_TO_FLASH
   PRINT(" EEPROM_  TIME_ARRAY  WRITE                    ----------------------------------->>   N  = %hu\n",rewrite);
#endif

   s= EEPROM_READ( b  , &BUFF_TEMPER_RESERVE, TempR_N*2);//читаем контрольно записанный  TIME_RESERVE из EEPROM

   b=0; //control breakpoint

   // читаем контрольно в цикле все елементы записанного массива TIME_RESERVE с выводом на печать
   // если есть ошибка - повторяем цикл записи и считывания . максимальное количество повторов = 5/ можно поменять


   for(i = 0; i < TempR_N; i++)
       {
   if((TEMPER_RESERVE[i])!=(BUFF_TEMPER_RESERVE[i]))
     {
   ERROR++;
     }
#ifndef  SET_TEMPER_TO_FLASH
   PRINT(" %hu ", BUFF_TEMPER_RESERVE[i]);
#endif
       }
#ifndef  SET_TEMPER_TO_FLASH
   PRINT("\n");
   PRINT("\n");
#endif

   //------------------------------ DEBUG  ИТОГОВЫЙ ВЫВОД ВСЕЙ TIME EEPROM ПО ФАКТУ ОБНОВЛЕНИЯ ------------------------------//
#ifndef  SET_TEMPER_TO_FLASH
   PRINT("EEPROM_READ... \n");
#endif

   s= EEPROM_READ(TEMPER_EEPROM_ADR, &TestBuf,  lengthTestBuf*2);
#ifndef  SET_TEMPER_TO_FLASH
   for(i = 0; i < lengthTestBuf; i++)
                         {
   PRINT("%hu ", TestBuf[i]);
                          }
   PRINT("\n");
   PRINT("\n");
#endif
   //------------------------------------------- END OFF DEBUG -------------------------------------------//

   //ERROR=1; // тестовая отладка  на предмет повторных перезаписей "Repeat_N"

    if(ERROR>0)
    {
#ifndef  SET_TEMPER_TO_FLASH
    PRINT(" EEPROM_  TIME_ARRAY WRITE  ERROR !!!   REWRITE         ----------------------------------->>     = %hu\n",ERROR);
    PRINT("\n");
#endif
    ERROR=0;

    if(++rewrite<Repeat_N )
        {
#ifndef  SET_TEMPER_TO_FLASH
      PRINT(" EEPROM_  TIME_ARRAY RE WRITE     rewrite N =              ----------------------------------->>     = %hu\n",rewrite);
#endif
        }

    }else
            {
//#ifndef  SET_TEMPER_TO_FLASH
    PRINT(" EEPROM_  TEMPER_ARRAY WRITE   OK !!!     NEXT              ----------------------------------->>     = %hu\n",ERROR);
    PRINT("\n");
//#endif
    rewrite=Repeat_N ;// принудительный выход из цикла обновления EEPROM while и ОБХОД  if(++rewrite<5)


    }

     }

#ifndef  SET_TEMPER_TO_FLASH
  PRINT("\n");
  PRINT("END \n"); // control breakpoint
#endif

#ifndef  SET_TEMPER_TO_FLASH
  printf("--      \n");
 //  DelayMs(10);// задержка для очистки мусора гипертерминала  перед  GPIOA_ModeCfg(bTXD1, GPIO_ModeIN_PD)
  GPIOB_ModeCfg(bTXD1, GPIO_ModeIN_PD);
#endif



}




void SCHEDULE_TO_FLASH(void);

void SCHEDULE_TO_FLASH(void)
{
static unsigned short a,b,c,d,i,s,ERROR,rewrite,BUSY_MEMORY_ADR, FREE_MEMORY_ADR;
static unsigned short BUFF_SCHEDULE_RESERVE[SHE_N];// буфер для контрольной копии многомерного массива Time_Copy_Pointer
// в одномерный массив BUFF_TIME_RESERVE[126], с дальнейшей выгрузкой /загрузкой в выбранную  флеш страницу

//memcpy(BUFF_SCHEDULE_RESERVE, Shedull_Pointer, sizeof(BUFF_SCHEDULE_RESERVE));// скопировали flash таблицу заводскую в BUFF_SCHEDULE_RESERVE
 // memcpy(SCHEDULE_RESERVE, Shedull_Pointer, sizeof(SCHEDULE_RESERVE));



//#define   DEBUG_SCHEDULE_TO_FLASH

#ifndef  DEBUG_SCHEDULE_TO_FLASH
      GPIOB_SetBits(bTXD1);
      GPIOB_ModeCfg(bTXD1, GPIO_ModeOut_PP_5mA);
#endif



// для пересохранения параметров текущего времени, с учетом состояния кольцевого буфера

a=0,b=0,c=0,d=0,i=0,s=0,ERROR=0,rewrite=0,BUSY_MEMORY_ADR=0, FREE_MEMORY_ADR=0;
// хоть переменные мы обьявили как static..их надо очищать перед использованием

 // запускаем процедуру записи в кольцевой буфер текущих параметров времени

    while((rewrite<Repeat_N)||(ERROR>0))// счетчик количества перезаписей  N=5
       {
// Читаем состояние и определяем свободное место в кольцевом буфере, формируем актуальный указатель для записи
//   в EEPROM

//1.
   s= EEPROM_READ(BASE_EEPROM_ADR , &TestBuf, 256);// читаем и оределяем указатель
   //свободного  места в EEPROM[128] под параметры ВРЕМЕНИ, с учетов общего выделенного места и
   //размером массива TIME_RESERVE


  a=0;  // control breakpoint
  BUSY_MEMORY_ADR=0;
  i = 0;

   for(i = 0; i < SCHEDULE_Copy_N; i++)// анализируем очередь прочитанных указателей для каждого массива "ВРЕМЕНИ"       {
{

    a=    (TestBuf[(i*SHE_N)]+1);// +1 линейный сдвиг на первое стационарное слово из 2х байт = 0x55AA;

    if (a!=0xFFFF)
   {
   BUSY_MEMORY_ADR++; // control breakpoint
   }

   }


#ifndef  DEBUG_SCHEDULE_TO_FLASH
   PRINT(" BUSY_MEMORY_ADR         ----------------------------------->>     = %hu\n",BUSY_MEMORY_ADR-1);
#endif
   if((BUSY_MEMORY_ADR<SCHEDULE_Copy_N)&(BUSY_MEMORY_ADR>0))// если свободный указатель доступен из выделенного максимума памяти
     {

   FREE_MEMORY_ADR=BUSY_MEMORY_ADR; // то определяем текущую сободную память
#ifndef  DEBUG_SCHEDULE_TO_FLASH
   PRINT(" 0 + FREE_MEMORY_ADR   ----------------------------------->>     = %hu\n",FREE_MEMORY_ADR);
#endif
     }
   else {

   if(BUSY_MEMORY_ADR==SCHEDULE_Copy_N)
         {

   s = EEPROM_ERASE(BASE_EEPROM_ADR, EEPROM_MIN_ER_SIZE);// стираем всю страницу  в 256  байт

#ifndef  DEBUG_SCHEDULE_TO_FLASH
   PRINT("\n");
   PRINT(" SCHEDULE_Copy_N  &  ERASE START !! =  -------------------------->>     = %hu\n",SCHEDULE_Copy_N);
   PRINT("\n");
#endif
   a=0x55AA;// пишем стартовый ключ в первый два байта
   s=  EEPROM_WRITE(BASE_EEPROM_ADR , &a, 2);

   BUSY_MEMORY_ADR=0; // и сбрасываем все указетели в "0"
   FREE_MEMORY_ADR=0; // и сбрасываем все указетели в "0"
#ifndef  DEBUG_SCHEDULE_TO_FLASH
   PRINT(" ERASE SCHEDULE EEPROM PAGE  OK  ------------------------------->>     = %hu\n",s);
   PRINT(" BUSY_MEMORY_ADR         ----------------------------------->>     = %hu\n",BUSY_MEMORY_ADR-1);
   PRINT(" 0 + FREE_MEMORY_ADR     ----------------------------------->>     = %hu\n",FREE_MEMORY_ADR);
#endif
  //------------------------------------------- DEBUG -------------------------------------------//
#ifndef  DEBUG_SCHEDULE_TO_FLASH
   PRINT("EEPROM_READ... \n");
   EEPROM_READ(BASE_EEPROM_ADR, TestBuf,  lengthTestBuf*2);
   for(i = 0; i < lengthTestBuf; i++)
                 {
   PRINT("%hu ", TestBuf[i]);
                  }
   PRINT("\n");
#endif
  //------------------------------------------- END OFF DEBUG -------------------------------------------//

         }

   if(BUSY_MEMORY_ADR==0)
                  {
#ifndef  DEBUG_SCHEDULE_TO_FLASH
   PRINT(" BUSY_MEMORY_ADR         ----------------------------------->>     = %hu\n",BUSY_MEMORY_ADR-1);
   PRINT(" 0 + FREE_MEMORY_ADR     ----------------------------------->>     = %hu\n",FREE_MEMORY_ADR);

   //------------------------------------------- DEBUG -------------------------------------------//

   PRINT("EEPROM_READ... \n");
   EEPROM_READ(BASE_EEPROM_ADR, TestBuf,  lengthTestBuf*2);
   for(i = 0; i < lengthTestBuf; i++)
                    {
   PRINT("%hu ", TestBuf[i]);
                     }
   PRINT("\n");
#endif
     //------------------------------------------- END OFF DEBUG -------------------------------------------//

    }

    }

   b= FREE_MEMORY_ADR* SHE_N*2;//
   b= b+ SCHEDULE_RESERVE_6_BASE_ADR;// + линейный сдвиг на первое стационарное слово из 2х байт

   //s= EEPROM_WRITE( b  , &BUFF_SCHEDULE_RESERVE, SHE_N*2); //записываем  массив SCHEDULE_RESERVE в свободную  EEPROM
   s= EEPROM_WRITE( b  , &SCHEDULE_RESERVE, SHE_N*2); //записываем  массив SCHEDULE_RESERVE в свободную  EEPROM


#ifndef  DEBUG_SCHEDULE_TO_FLASH
   PRINT(" EEPROM    <<SCHEDULE_RESERVE ARRAY>>             ----------------------------------->>   N  = %hu\n",rewrite);
#endif
   s= EEPROM_READ( b  , &BUFF_SCHEDULE_RESERVE, SHE_N*2);//читаем контрольно записанный  SCHEDULE_RESERVE из EEPROM
   //s= EEPROM_READ( b  , &SCHEDULE_RESERVE, SHE_N*2);//читаем контрольно записанный  SCHEDULE_RESERVE из EEPROM

   b=0; //control breakpoint

   // читаем контрольно в цикле все елементы записанного массива TIME_RESERVE с выводом на печать
   // если есть ошибка - повторяем цикл записи и считывания . максимальное количество повторов = 5/ можно поменять

#ifndef  DEBUG_SCHEDULE_TO_FLASH
   for(i = 0; i < SHE_N; i++)
       {
   if((*(BUFF_SCHEDULE_RESERVE+i))!=(*(BUFF_SCHEDULE_RESERVE+i)))
     //if((*(SCHEDULE_RESERVE+i))!=(*(SCHEDULE_RESERVE+i)))
     {
   ERROR++;
     }
   PRINT(" %hu ", BUFF_SCHEDULE_RESERVE[i]);
     //PRINT(" %hu ", SCHEDULE_RESERVE[i]);

       }
   PRINT("\n");
   PRINT("\n");
#endif

   PRINT(" EEPROM READ   FROM  <<BUFF_SCHEDULE_RESERVE ARRAY>>       ----------------------------->>     = %hu\n");

   //------------------------------ DEBUG  ИТОГОВЫЙ ВЫВОД ВСЕЙ TIME EEPROM ПО ФАКТУ ОБНОВЛЕНИЯ ------------------------------//
#ifndef  DEBUG_SCHEDULE_TO_FLASH
   PRINT("EEPROM_READ... \n");
   s= EEPROM_READ(BASE_EEPROM_ADR, &TestBuf,  lengthTestBuf*2);
   for(i = 0; i < lengthTestBuf; i++)
                         {
   PRINT("%hu ", TestBuf[i]);
                          }
   PRINT("\n");
   PRINT("\n");
#endif
   PRINT(" EEPROM   READ   <<FROM TestBuf ARRAY>>       ----------------------------->>     = %hu\n");
   //------------------------------------------- END OFF DEBUG -------------------------------------------//


    if(ERROR>0)
    {
#ifndef  DEBUG_SCHEDULE_TO_FLASH
    PRINT(" EEPROM_  SCHEDULE_ARRAY WRITE  ERROR !!!   REWRITE         ----------------------------------->>     = %hu\n",ERROR);
    PRINT("\n");
#endif
    ERROR=0;

    if(++rewrite<Repeat_N )
        {
#ifndef  DEBUG_SCHEDULE_TO_FLASH
     PRINT(" EEPROM_  SCHEDULE_ARRAY RE WRITE     rewrite N =              ----------------------------------->>     = %hu\n",rewrite);
#endif
        }

    }else
            {
//#ifndef  DEBUG_SCHEDULE_TO_FLASH
    PRINT(" EEPROM_  SCHEDULE_ARRAY WRITE   OK !!!     NEXT              ----------------------------------->>     = %hu\n",ERROR);
    PRINT("\n");
//#endif

 //   memcpy( Shedull_Copy_Pointer,BUFF_TIME_RESERVE, sizeof(Shedull_Copy_Pointer));// прочитали пересохраненное значение  для РАСПИСАНИЯ
    // обратно в рабочий  ОЗУ массив   Shedull_Copy_Pointer, для дальнейшей работы термосмостата в "программном режиме"

    rewrite=Repeat_N ;// принудительный выход из цикла обновления EEPROM while и ОБХОД  if(++rewrite<5)

    }

     }

//#ifndef  DEBUG_SCHEDULE_TO_FLASH
  PRINT("\n");
  PRINT("END \n"); //
//#endif


#ifndef  DEBUG_SCHEDULE_TO_FLASH
  printf("--      \n");
 //  DelayMs(10);// задержка для очистки мусора гипертерминала  перед  GPIOA_ModeCfg(bTXD1, GPIO_ModeIN_PD)
  GPIOB_ModeCfg(bTXD1, GPIO_ModeIN_PD);
#endif


}



void SYSTEM_TO_FLASH(void);

void SYSTEM_TO_FLASH(void)
{
static unsigned short a,b,c,d,i,s,ERROR,rewrite,BUSY_MEMORY_ADR, FREE_MEMORY_ADR;
static unsigned short BUFF_SYSTEM_RESERVE[SR_N];// буфер для контрольной копии массива времени TIME_RESERVE
static unsigned short SYSTEM_Copy_Pointer[SYSTEM_Copy_N]; //указатель свободного EEPROM для страницы в 128 элементов(256 байт)
// для пересохранения параметров текущего времени, с учетом состояния кольцевого буфера

a=0,b=0,c=0,d=0,i=0,s=0,ERROR=0,rewrite=0,BUSY_MEMORY_ADR=0, FREE_MEMORY_ADR=0;
// хоть переменные мы обьявили как static..их надо очищать перед использованием


#define   SET_SYSTEM_TO_FLASH

#ifndef  SET_SYSTEM_TO_FLASH
GPIOB_SetBits(bTXD1);
GPIOB_ModeCfg(bTXD1, GPIO_ModeOut_PP_5mA);
#endif


SYSTEM_RESERVE[0]= main_screen_type;;
SYSTEM_RESERVE[1]= LOC_on_off;
SYSTEM_RESERVE[2]= HystPrepere;
SYSTEM_RESERVE[3]= device_on_off;
SYSTEM_RESERVE[4]= sfm_min;
//SYSTEM_RESERVE[5]= ps;
SYSTEM_RESERVE[6]= 0x5555;



  // запускаем процедуру записи в кольцевой буфер текущих параметров времени

    while((rewrite<Repeat_N)||(ERROR>0))// счетчик количества перезаписей  N=5
       {
// Читаем состояние и определяем свободное место в кольцевом буфере, формируем актуальный указатель для записи
//   в EEPROM

//1.
   s= EEPROM_READ(SYSTEM_EEPROM_ADR , &TestBuf, 256);// читаем и оределяем указатель
   //свободного  места в EEPROM[128] под параметры ВРЕМЕНИ, с учетов общего выделенного места и
   //размером массива TIME_RESERVE


  a=0;  // control breakpoint
  BUSY_MEMORY_ADR=0;
  i = 0;


   for(i = 0; i < SYSTEM_Copy_N; i++)// анализируем очередь прочитанных указателей для каждого массива "ВРЕМЕНИ"       {
{
   a=TestBuf[(i*SR_N)+1];// +1 линейный сдвиг на первое стационарное слово из 2х байт = 0x55AA;

    if (a!=0xFFFF)
   {
   BUSY_MEMORY_ADR++; // control breakpoint
   }
 }

#ifndef  SET_SYSTEM_TO_FLASH
   PRINT("\n");
   PRINT("\n");//control breakpoint

   PRINT(" BUSY_MEMORY_ADR         ----------------------------------->>     = %hu\n",BUSY_MEMORY_ADR-1);
#endif

   if((BUSY_MEMORY_ADR<SYSTEM_Copy_N)&(BUSY_MEMORY_ADR>0))// если свободный указатель доступен из выделенного максимума памяти
     {

   FREE_MEMORY_ADR=BUSY_MEMORY_ADR; // то определяем текущую сободную память
#ifndef  SET_SYSTEM_TO_FLASH
   PRINT(" 0 + FREE_MEMORY_ADR   ----------------------------------->>     = %hu\n",FREE_MEMORY_ADR);
#endif
     }
   else {

   if(BUSY_MEMORY_ADR==SYSTEM_Copy_N)
         {

   s = EEPROM_ERASE(SYSTEM_EEPROM_ADR, EEPROM_MIN_ER_SIZE);// стираем всю страницу  в 256  байт

#ifndef  SET_SYSTEM_TO_FLASH
   PRINT("\n");
   PRINT(" SYSTEM_Copy_N  &  ERASE START !! =  -------------------------->>     = %hu\n",SYSTEM_Copy_N);
   PRINT("\n");
#endif

   a=0x55AA;// пишем стартовый ключ в первый два байта
   s=  EEPROM_WRITE(SYSTEM_EEPROM_ADR , &a, 2);

   BUSY_MEMORY_ADR=0; // и сбрасываем все указетели в "0"
   FREE_MEMORY_ADR=0; // и сбрасываем все указетели в "0"

#ifndef  SET_SYSTEM_TO_FLASH
   PRINT(" ERASE SYSTEM EEPROM PAGE  OK  ------------------------------->>     = %hu\n",s);
   PRINT(" BUSY_MEMORY_ADR         ----------------------------------->>     = %hu\n",BUSY_MEMORY_ADR-1);
   PRINT(" 0 + FREE_MEMORY_ADR     ----------------------------------->>     = %hu\n",FREE_MEMORY_ADR);
#endif
  //------------------------------------------- DEBUG -------------------------------------------//
#ifndef  SET_SYSTEM_TO_FLASH
   PRINT("EEPROM_READ... \n");
#endif
   EEPROM_READ(SYSTEM_EEPROM_ADR, TestBuf,  lengthTestBuf*2);
#ifndef  SET_SYSTEM_TO_FLASH
   for(i = 0; i < lengthTestBuf; i++)
                 {
   PRINT("%hu ", TestBuf[i]);
                  }
   PRINT("\n");
#endif
  //------------------------------------------- END OFF DEBUG -------------------------------------------//

         }

   if(BUSY_MEMORY_ADR==0)
                  {
#ifndef  SET_SYSTEM_TO_FLASH
   PRINT(" BUSY_MEMORY_ADR         ----------------------------------->>     = %hu\n",BUSY_MEMORY_ADR-1);
   PRINT(" 0 + FREE_MEMORY_ADR     ----------------------------------->>     = %hu\n",FREE_MEMORY_ADR);
#endif
   //------------------------------------------- DEBUG -------------------------------------------//
#ifndef  SET_SYSTEM_TO_FLASH
   PRINT("EEPROM_READ... \n");
#endif
   EEPROM_READ(SYSTEM_EEPROM_ADR, TestBuf,  lengthTestBuf*2);
#ifndef  SET_SYSTEM_TO_FLASH
   for(i = 0; i < lengthTestBuf; i++)
                    {
   PRINT("%hu ", TestBuf[i]);
                     }
   PRINT("\n");
#endif
     //------------------------------------------- END OFF DEBUG -------------------------------------------//

    }

    }

   b= FREE_MEMORY_ADR* SR_N*2;//
   b= b+ SYSTEM_RESERVE_6_BASE_ADR;// + линейный сдвиг на первое стационарное слово из 2х байт

   s= EEPROM_WRITE( b  , &SYSTEM_RESERVE, SR_N*2); //записываем  массив TIME_RESERVE в свободную  EEPROM

#ifndef  SET_SYSTEM_TO_FLASH
   PRINT(" EEPROM_  TIME_ARRAY  WRITE                    ----------------------------------->>   N  = %hu\n",rewrite);
#endif
   s= EEPROM_READ( b  , &BUFF_SYSTEM_RESERVE, SR_N*2);//читаем контрольно записанный  TIME_RESERVE из EEPROM

   b=0; //control breakpoint

   // читаем контрольно в цикле все елементы записанного массива TIME_RESERVE с выводом на печать
   // если есть ошибка - повторяем цикл записи и считывания . максимальное количество повторов = 5/ можно поменять


   for(i = 0; i < SR_N; i++)
       {
   if((SYSTEM_RESERVE[i])!=(BUFF_SYSTEM_RESERVE[i]))
     {
   ERROR++;
     }
#ifndef  SET_SYSTEM_TO_FLASH
   PRINT(" %hu ", BUFF_SYSTEM_RESERVE[i]);
#endif
       }

#ifndef  SET_SYSTEM_TO_FLASH
   PRINT("\n");
   PRINT("\n");
#endif

   //------------------------------ DEBUG  ИТОГОВЫЙ ВЫВОД ВСЕЙ TIME EEPROM ПО ФАКТУ ОБНОВЛЕНИЯ ------------------------------//
#ifndef  SET_SYSTEM_TO_FLASH
   PRINT("EEPROM_READ... \n");
#endif
   s= EEPROM_READ(SYSTEM_EEPROM_ADR, &TestBuf,  lengthTestBuf*2);
#ifndef  SET_SYSTEM_TO_FLASH
   for(i = 0; i < lengthTestBuf; i++)
                         {
   PRINT("%hu ", TestBuf[i]);
                          }
   PRINT("\n");
   PRINT("\n");
#endif
   //------------------------------------------- END OFF DEBUG -------------------------------------------//

   //ERROR=1; // тестовая отладка  на предмет повторных перезаписей "Repeat_N"

    if(ERROR>0)
    {
#ifndef  SET_SYSTEM_TO_FLASH
    PRINT(" EEPROM_  SYSTEM_ARRAY WRITE  ERROR !!!   REWRITE         ----------------------------------->>     = %hu\n",ERROR);
    PRINT("\n");
#endif
    ERROR=0;

    if(++rewrite<Repeat_N )
        {
#ifndef  SET_SYSTEM_TO_FLASH
      PRINT(" EEPROM_  SYSTEM_ARRAY RE WRITE     rewrite N =              ----------------------------------->>     = %hu\n",rewrite);
#endif
        }

    }else
           {
//#ifndef  SET_SYSTEM_TO_FLASH
    PRINT(" EEPROM_  SYSTEM_ARRAY WRITE   OK !!!     NEXT              ----------------------------------->>     = %hu\n",ERROR);
    PRINT("\n");
//#endif
    rewrite=Repeat_N ;// принудительный выход из цикла обновления EEPROM while и ОБХОД  if(++rewrite<5)

    //if(++rewrite<Repeat_N ) // тестовая отладка
    // {
    //PRINT(" EEPROM_  TIME_ARRAY RE WRITE     rewrite N =              ----------------------------------->>     = %hu\n",rewrite);
    // }
    }

     }

//#ifndef  SET_SYSTEM_TO_FLASH
  PRINT("\n");
  PRINT("END \n"); // control breakpoint
//#endif

  #ifndef  SET_SYSTEM_TO_FLASH
  printf("--      \n");
 //  DelayMs(10);// задержка для очистки мусора гипертерминала  перед  GPIOA_ModeCfg(bTXD1, GPIO_ModeIN_PD)
  GPIOB_ModeCfg(bTXD1, GPIO_ModeIN_PD);
  #endif

}


