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

// сюда можно писать различные тесты и процедуры!! и вызывать их из основного цикла !!
// да бы не ломать основную прогу!!
#include "CONFIG.h"
#include "my_assist32.h" // дополнительные битовые макросы и макросы типов заимственны из STM8 Raide
#include "my_test.h"
#include "my_large_LCD32.h"

//-------------------- PIN5_LCD_SK7  - ДЛЯ БАЗОВОГО ТЕСТА---------------------------
#define PIN5_LCD_SEG1        GPIO_Pin_2   //
#define PIN5_LCD_SK7        PIN5_LCD_SEG1  // перенаправление для тестовой отладки в начальном тесте, не используется в
// основном коде


 vu32  GPIO_test;
 uint8  CR1=0 ;

 typedef int32_t  s32;
 typedef int16_t s16;
 typedef int8_t  s8;

 typedef uint32_t  u32;
 typedef uint16_t u16;
 typedef uint8_t  u8;

#define  debug1              GPIO_Pin_1   //
#define  debug2              GPIO_Pin_2   //

#define  TIME1              FREQ_SYS / 160
#define  TIME2              FREQ_SYS / 760

//#define  DEAD_TIME          FREQ_SYS / 450// рекомендуется при 3,5 в
//#define  ACTIVE_TIME        FREQ_SYS /170//


 uint8 RING_FASE =0;
 uint8 inverstest=255, invers_image =255 ,second_sep_invers=255,invers_clock_icon=0;
 uint8 invers_blynk_image,invers_blynk_image_1S;
 uint8 Virtual_timer=0,Virtual_timer2=0,Virtual_timer3=0;
 uint16 Tik_1_sek=0;



 int Count_Tik=0,long_mode_Tik=0, plus_minus_Tik=0;
 int8_t Count_Plus=0,Count_Minus=0,Count_Mode=0;





void    Bit_Test(void);

#define Test1  // пример условной компиляции
//#undef Test1
#ifdef Test1

void    Bit_Test(void)
{

          GPIO_test =0;
          R32_PA_OUT =0;
      // тестирование с битовыми операциями на примере порта А
          GPIO_test|=(p15);// выставить / наложить бит 15 в порте R32_PA_OUT
          GPIOA_SetBits(p15);
          GPIO_test=R32_PA_OUT;
          GPIOA_ResetBits(p15);
          GPIO_test=R32_PA_OUT;
          GPIOA_SetBits(p15);
          GPIO_test=R32_PA_OUT;
          GPIOA_ResetBits(p15);
          GPIO_test=R32_PA_OUT;

          GPIO_test|=(p2|p3|p6|p10|p11|p12|p13|p14|p15);// выставить / наложить бит 15 в порте R32_PA_OUT
          R32_PA_OUT=GPIO_test;
          R32_PA_OUT=0;
          R32_PA_OUT=0x5555;
          R32_PA_OUT=0xAAAA;
          R32_PA_OUT=0;
          GPIO_test|=(p2|p3|p6|p10|p11|p12|p13|p14|p15);// выставить / наложить бит 15 в порте R32_PA_OUT
          R32_PA_OUT=GPIO_test;

          GPIO_test|=(p2|p3|p6|p10|p11|p12|p13|p14|p15);
          GPIO_test&=~(p2|p3|p6|p10|p11|p12);// выставить / наложить бит 15 в порте R32_PA_OUT
          R32_PA_OUT=GPIO_test;
          GPIO_test|=(p2|p3|p6|p10|p11|p12|p13|p14);
          GPIO_test&=~(p2|p3|p12);


          R32_PA_OUT=0;
          R32_PA_OUT=0x5555;
          R32_PA_OUT=0xAAAA;
          R32_PA_OUT=0;
          GPIO_test&=(p2|p3|p6|p10|p11|p12|p13|p14|p15);
          GPIO_test&=~(p2|p3|p6|p10|p11|p12|p13|p14|p15);// выставить / наложить бит 15 в порте R32_PA_OUT
          R32_PA_OUT=GPIO_test;

}

#endif

//---------TMR0_IRQHandler Routine Test for LCD COM1-COM4 ver.1----

void COM1_COM4_Handler_Test1(void); //одиночный тест с домиками // без DEAD TIME

void COM1_COM4_Handler_Test1(void)
{

            RING_FASE++;

    ////////////////////////// COM1
            if(((RING_FASE)==1 )|((RING_FASE)==2 ))// анализируем фазу 1 и фазу2
            {

            if((RING_FASE)==1 )
            {
                GPIOB_ResetBits(PIN1_LCD_COM1);
                GPIOB_ModeCfg( PIN1_LCD_COM1, GPIO_ModeOut_PP_20mA );
                DelayUs(300);


                if(inverstest==0)
                                   {
                                     GPIOA_SetBits(PIN5_LCD_SK7);// //зажигаем сегмент противоположным уровнем
                                 //    GPIOA_SetBits(debug1);
                                   }else {

                                     GPIOA_ResetBits(PIN5_LCD_SK7);// //зажигаем сегмент противоположным уровнем
                                    // GPIOA_ResetBits(debug2);
                              }


            }

            if((RING_FASE)==2 )
            {

                GPIOB_SetBits(PIN1_LCD_COM1);
                GPIOB_ModeCfg( PIN1_LCD_COM1, GPIO_ModeOut_PP_20mA );
                DelayUs(300);

                if(inverstest==0)
                                   {
                                     GPIOA_ResetBits(PIN5_LCD_SK7);// //зажигаем сегмент противоположным уровнем

                                  //   GPIOA_SetBits(debug1);
                                   }else {

                                     GPIOA_SetBits(PIN5_LCD_SK7);// //зажигаем сегмент противоположным уровнем
                                     // GPIOA_ResetBits(debug2);
                              }


            }


            }else {
                GPIOB_ModeCfg( PIN1_LCD_COM1, GPIO_ModeIN_Floating );
            }


       //////////////////////// COM2
            if(((RING_FASE)==3 )|((RING_FASE)==4 ))// анализируем фазу 1 и фазу2
                   {

                   if((RING_FASE)==3 )
                   {
                       GPIOB_ResetBits(PIN2_LCD_COM2);
                       GPIOB_ModeCfg( PIN2_LCD_COM2, GPIO_ModeOut_PP_20mA );

                       if(inverstest)
                       {
                         GPIOA_SetBits(PIN5_LCD_SK7);// //зажигаем сегмент противоположным уровнем

                       //  GPIOA_SetBits(debug1);
                       }else {

                         GPIOA_ResetBits(PIN5_LCD_SK7);// //зажигаем сегмент противоположным уровнем
                        // GPIOA_ResetBits(debug2);
                  }

                      // GPIOA_ResetBits(PIN5_LCD_SK7);//гасим сегмент совпадающим уровнем "1"
                     //  GPIOA_SetBits(PIN5_LCD_SK7);// //зажигаем сегмент противоположным уровнем
                   }

                   if((RING_FASE)==4 )
                   {

                       GPIOB_SetBits(PIN2_LCD_COM2);
                       GPIOB_ModeCfg( PIN2_LCD_COM2, GPIO_ModeOut_PP_20mA );


                       if(inverstest)
                       {

                       GPIOA_ResetBits(PIN5_LCD_SK7);//зажигаем сегмент противоположным уровнем
                      // GPIOA_ResetBits(debug1);
                       }else {

                        GPIOA_SetBits(PIN5_LCD_SK7);// гасим сегмент совпадающим уровнем "1"
                         R32_PA_OUT=R32_PA_OUT|p15;
                       // GPIOA_SetBits(debug2);
                   }
                      // GPIOA_SetBits(PIN5_LCD_SK7);// гасим сегмент совпадающим уровнем "1"
                      // GPIOA_ResetBits(PIN5_LCD_SK7);//зажигаем сегмент противоположным уровнем
                                          //GPIOA_ResetBits(debug2);
                   }


                   } else {

                       GPIOB_ModeCfg( PIN2_LCD_COM2, GPIO_ModeIN_Floating );
                }


            //////////////////////// COM3
                    if(((RING_FASE)==5 )|((RING_FASE)==6 ))// анализируем фазу 1 и фазу2
                           {

                           if((RING_FASE)==5 )
                           {
                               GPIOB_ResetBits(PIN3_LCD_COM3);
                               GPIOB_ModeCfg( PIN3_LCD_COM3, GPIO_ModeOut_PP_20mA );


                               if(inverstest==0)
                               {
                                 GPIOA_SetBits(PIN5_LCD_SK7);// //зажигаем сегмент противоположным уровнем

                               //  GPIOA_SetBits(debug1);
                               }else {

                                 GPIOA_ResetBits(PIN5_LCD_SK7);// //зажигаем сегмент противоположным уровнем
                               //  GPIOA_ResetBits(debug2);
                          }

                              // GPIOA_ResetBits(PIN5_LCD_SK7);//гасим сегмент совпадающим уровнем "1"
                             //  GPIOA_SetBits(PIN5_LCD_SK7);// //зажигаем сегмент противоположным уровнем
                           }

                           if((RING_FASE)==6 )
                           {

                               GPIOB_SetBits(PIN3_LCD_COM3);
                               GPIOB_ModeCfg( PIN3_LCD_COM3, GPIO_ModeOut_PP_20mA );


                               if(inverstest==0)
                               {

                               GPIOA_ResetBits(PIN5_LCD_SK7);//зажигаем сегмент противоположным уровнем
                              // GPIOA_ResetBits(debug1);
                               }else {

                                GPIOA_SetBits(PIN5_LCD_SK7);// гасим сегмент совпадающим уровнем "1"

                             //   GPIOA_SetBits(debug2);
                           }
                             //  GPIOA_SetBits(PIN5_LCD_SK7);// гасим сегмент совпадающим уровнем "1"
                              // GPIOA_ResetBits(PIN5_LCD_SK7);//зажигаем сегмент противоположным уровнем
                              //GPIOA_ResetBits(debug2);
                           }


                           } else {

                               GPIOB_ModeCfg( PIN3_LCD_COM3, GPIO_ModeIN_Floating );
                        }


              //////////////////////// COM4
                     if(((RING_FASE)==7 )|((RING_FASE)==8 ))// анализируем фазу 1 и фазу2
                          {

                           if((RING_FASE)==7 )
                             {
                              GPIOB_ResetBits(PIN4_LCD_COM4);
                              GPIOB_ModeCfg( PIN4_LCD_COM4, GPIO_ModeOut_PP_20mA );


                                 if(inverstest)
                                {
                                  GPIOA_SetBits(PIN5_LCD_SK7);// //зажигаем сегмент противоположным уровнем

                                //  GPIOA_SetBits(debug1);
                                }else {

                                  GPIOA_ResetBits(PIN5_LCD_SK7);// //зажигаем сегмент противоположным уровнем
                                //  GPIOA_ResetBits(debug2);
                                }

                                //   GPIOA_ResetBits(PIN5_LCD_SK7);//гасим сегмент совпадающим уровнем "1"
                               //  GPIOA_SetBits(PIN5_LCD_SK7);// //зажигаем сегмент противоположным уровнем
                                  }

                                 if((RING_FASE)==8 )
                                  {

                                  GPIOB_SetBits(PIN4_LCD_COM4);
                                  GPIOB_ModeCfg( PIN4_LCD_COM4, GPIO_ModeOut_PP_20mA );


                                if(inverstest)
                                {

                                GPIOA_ResetBits(PIN5_LCD_SK7);//зажигаем сегмент противоположным уровнем


                               // GPIOA_ResetBits(debug1);
                                }else {

                                 GPIOA_SetBits(PIN5_LCD_SK7);// гасим сегмент совпадающим уровнем "1"


                                // GPIOA_SetBits(debug2);
                                 }
                                  // GPIOA_SetBits(PIN5_LCD_SK7);// гасим сегмент совпадающим уровнем "1"
                                // GPIOA_ResetBits(PIN5_LCD_SK7);//зажигаем сегмент противоположным уровнем
                                                                  //GPIOA_ResetBits(debug2);
                                   }


                                } else {

                                   GPIOB_ModeCfg( PIN4_LCD_COM4, GPIO_ModeIN_Floating );
                                        }




        if ((RING_FASE==3)|(RING_FASE==4)|(RING_FASE==5)|(RING_FASE==6)|(RING_FASE==7)|(RING_FASE==8) )
        {

            GPIOB_ModeCfg( PIN1_LCD_COM1, GPIO_ModeIN_Floating );

        }
    //////////////////////////////////////

        if ((RING_FASE==1)|(RING_FASE==2)|(RING_FASE==5)|(RING_FASE==6)|(RING_FASE==7)|(RING_FASE==8) )
           {

               GPIOB_ModeCfg( PIN2_LCD_COM2, GPIO_ModeIN_Floating );

           }

     //////////////////////////////////////

         if ((RING_FASE==1)|(RING_FASE==2)|(RING_FASE==3)|(RING_FASE==4)|(RING_FASE==7)|(RING_FASE==8) )
               {

               GPIOB_ModeCfg( PIN3_LCD_COM3, GPIO_ModeIN_Floating );

               }


     //////////////////////////////////////

          if ((RING_FASE==1)|(RING_FASE==2)|(RING_FASE==3)|(RING_FASE==4)|(RING_FASE==5)|(RING_FASE==6) )
               {

               GPIOB_ModeCfg( PIN4_LCD_COM4, GPIO_ModeIN_Floating );

               }




        if(RING_FASE>7)
            {
                RING_FASE=0;
            }


        if(++Tik_1_sek==550)
           {
               Tik_1_sek=0;
               inverstest=~inverstest;

           }

        if(inverstest)
        {
            //GPIOA_ResetBits(debug1);
        }else {
           // GPIOA_SetBits(debug1);
        }

}

void COM1_COM4_Handler_Test2(void); // тест с DEAD TIME - Работает!! РАБОЧАЯ ПРОЦЕДУРА

void COM1_COM4_Handler_Test2(void)
{
    fsm++;              // новое состояние
        //  if(lcd_flags&BYPASS_ON)fsm++;   // новое состояние
            if(fsm>3)fsm2++;    // круговорот
            fsm&=FSM_MASK;      //ограничение состояний
            fsm2&=FSM2_MASK;    //ограничение состояний



            if(fsm&0x00000001)
            {
                TMR0_TimerInit( DEAD_TIME);
            }
            else{
                //TIM2->ARR=LCD_ACTIVE_TIME_ARR;
                TMR0_TimerInit( ACTIVE_TIME);
                        //if(lcd_flags&BYPASS_ON_REQ){       //
                    //resetbit(lcd_flags,BYPASS_ON_REQ);   //
                    //setbit(lcd_flags,BYPASS_ON);}    //
                //if(lcd_flags&BYPASS_OFF_REQ)resetbit(lcd_flags,(BYPASS_OFF_REQ|BYPASS_ON));  //
            }
            drive_ALL();            //сгенерировать новый выход //



}

void COM1_COM4_Handler_Test3(void);// разнесеннный вывод через видео буфер

void COM1_COM4_Handler_Test3(void)
{

    RING_FASE++;

/////////////////////////////////// COM1
               if(((RING_FASE)==1 )|((RING_FASE)==2 ))// анализируем фазу 1 и фазу2
               {

               if((RING_FASE)==1 )
               {

               SEG_PortToLCD_OUT(com1_charge ,charghe);

               drive_COM1();

               }

               if((RING_FASE)==2 )
               {

               SEG_PortToLCD_OUT(com1_discharge ,discharghe);

               drive_COM1();

               }

               }

 //////////////////////////////// COM2
               if(((RING_FASE)==3 )|((RING_FASE)==4 ))// анализируем фазу 1 и фазу2
                      {

               if((RING_FASE)==3 )
               {

                SEG_PortToLCD_OUT(com2_charge ,charghe);

                drive_COM2();

                }

               if((RING_FASE)==4 )
               {

                SEG_PortToLCD_OUT(com2_discharge ,discharghe);

                drive_COM2();

               }

               }


 ///////////////////////////////// COM3
               if(((RING_FASE)==5 )|((RING_FASE)==6 ))// анализируем фазу 1 и фазу2
               {

               if((RING_FASE)==5 )
               {

               SEG_PortToLCD_OUT(com3_charge ,charghe);

               drive_COM3();

               }

               if((RING_FASE)==6 )
               {

             SEG_PortToLCD_OUT(com3_discharge ,discharghe);

               drive_COM3();

               }

               }


/////////////////////////////////// COM4
               if(((RING_FASE)==7 )|((RING_FASE)==8 ))// анализируем фазу 1 и фазу2
               {

               if((RING_FASE)==7 )
               {

               SEG_PortToLCD_OUT(com4_charge ,charghe);

               drive_COM4();

               }

               if((RING_FASE)==8 )
               {

               SEG_PortToLCD_OUT(com4_discharge ,discharghe);

               drive_COM4();

               }

               }





           if(RING_FASE>7)
               {
                   RING_FASE=0;
               }


}



void COM1_COM4_Handler_Test4(void); // работает распоковка "на лету" без DEAD TIME

void COM1_COM4_Handler_Test4(void){


    RING_FASE++;

/////////////////////////////////// COM1
               if(((RING_FASE)==1 )|((RING_FASE)==2 ))// анализируем фазу 1 и фазу2
               {

               if((RING_FASE)==1 )
               {

               drive_COM1();
               charge_SEG(com1,out_LCD_ON);
               COM1_LOW;
               }

               if((RING_FASE)==2 )
               {
               drive_COM1();
               discharge_SEG(com1,out_LCD_ON);
               COM1_HIGH;

               }

               }

 //////////////////////////////// COM2
               if(((RING_FASE)==3 )|((RING_FASE)==4 ))// анализируем фазу 1 и фазу2
                      {

               if((RING_FASE)==3 )
               {
               drive_COM2();
               charge_SEG(com2,out_LCD_ON);
               COM2_LOW;
                }

               if((RING_FASE)==4 )
               {
               drive_COM2();
               discharge_SEG(com2,out_LCD_ON);
               COM2_HIGH;

               }

               }


 ///////////////////////////////// COM3
               if(((RING_FASE)==5 )|((RING_FASE)==6 ))// анализируем фазу 1 и фазу2
               {

               if((RING_FASE)==5 )
               {
               drive_COM3();
               charge_SEG(com3,out_LCD_ON);
               COM3_LOW;

               }

               if((RING_FASE)==6 )
               {
               drive_COM3();
               discharge_SEG(com3,out_LCD_ON);
               COM3_HIGH;
               }

               }


/////////////////////////////////// COM4
               if(((RING_FASE)==7 )|((RING_FASE)==8 ))// анализируем фазу 1 и фазу2
               {

               if((RING_FASE)==7 )
               {
               drive_COM4();
               charge_SEG(com4,out_LCD_ON);
               COM4_LOW;
               }

               if((RING_FASE)==8 )
               {
               drive_COM4();
               discharge_SEG(com4,out_LCD_ON);
               COM4_HIGH;
               }

               }





           if(RING_FASE>7)
               {
                   RING_FASE=0;
               }




}





void COM1_COM4_Handler_Test8(void); // просто смена таймера на ходу, без DEAD TIME

void COM1_COM4_Handler_Test8(void)
{


            RING_FASE++;

    ////////////////////////// COM1
            if(((RING_FASE)==1 )|((RING_FASE)==2 ))// анализируем фазу 1 и фазу2
            {

            if((RING_FASE)==1 )
            {


                COM1_LOW;

                TMR0_TimerInit(TIME1);         // 设置定时时间 100ms

            }

            if((RING_FASE)==2 )
            {



                COM1_HIGH;

                TMR0_TimerInit(TIME2);         // 设置定时时间 100ms


            }


            }else {
                GPIOB_ModeCfg( PIN1_LCD_COM1, GPIO_ModeIN_Floating );
            }


       //////////////////////// COM2
            if(((RING_FASE)==3 )|((RING_FASE)==4 ))// анализируем фазу 1 и фазу2
                   {

                   if((RING_FASE)==3 )
                   {


                       COM2_LOW;

                       TMR0_TimerInit(TIME1);         // 设置定时时间 100ms

                   }

                   if((RING_FASE)==4 )
                   {



                       COM2_HIGH;

                       TMR0_TimerInit(TIME2);         // 设置定时时间 100ms

                   }


                   } else {

                       GPIOB_ModeCfg( PIN2_LCD_COM2, GPIO_ModeIN_Floating );
                }


            //////////////////////// COM3
                    if(((RING_FASE)==5 )|((RING_FASE)==6 ))// анализируем фазу 1 и фазу2
                           {

                           if((RING_FASE)==5 )
                           {


                               COM3_LOW;

                         TMR0_TimerInit(TIME1);         // 设置定时时间 100ms



                           }

                           if((RING_FASE)==6 )
                           {



                               COM3_HIGH;

                         TMR0_TimerInit(TIME2);         // 设置定时时间 100ms


                           }


                           } else {

                               GPIOB_ModeCfg( PIN3_LCD_COM3, GPIO_ModeIN_Floating );
                        }


              //////////////////////// COM4
                     if(((RING_FASE)==7 )|((RING_FASE)==8 ))// анализируем фазу 1 и фазу2
                          {

                           if((RING_FASE)==7 )
                             {




                              COM4_LOW;

                       TMR0_TimerInit(TIME1);         // 设置定时时间 100ms



                                  }

                                 if((RING_FASE)==8 )
                                  {



                                  COM4_HIGH;


                        TMR0_TimerInit(TIME2);         // 设置定时时间 100ms


                                   }


                                } else {

                                   GPIOB_ModeCfg( PIN4_LCD_COM4, GPIO_ModeIN_Floating );
                                        }



    //////////////////////////////////////

        if ((RING_FASE==3)|(RING_FASE==4)|(RING_FASE==5)|(RING_FASE==6)|(RING_FASE==7)|(RING_FASE==8) )
        {

            GPIOB_ModeCfg( PIN1_LCD_COM1, GPIO_ModeIN_Floating );

        }
    //////////////////////////////////////

        if ((RING_FASE==1)|(RING_FASE==2)|(RING_FASE==5)|(RING_FASE==6)|(RING_FASE==7)|(RING_FASE==8) )
           {

               GPIOB_ModeCfg( PIN2_LCD_COM2, GPIO_ModeIN_Floating );

           }

     //////////////////////////////////////

         if ((RING_FASE==1)|(RING_FASE==2)|(RING_FASE==3)|(RING_FASE==4)|(RING_FASE==7)|(RING_FASE==8) )
               {

               GPIOB_ModeCfg( PIN3_LCD_COM3, GPIO_ModeIN_Floating );

               }


     //////////////////////////////////////

          if ((RING_FASE==1)|(RING_FASE==2)|(RING_FASE==3)|(RING_FASE==4)|(RING_FASE==5)|(RING_FASE==6) )
               {

               GPIOB_ModeCfg( PIN4_LCD_COM4, GPIO_ModeIN_Floating );

               }




        if(RING_FASE>7)
            {
                RING_FASE=0;
            }


}


