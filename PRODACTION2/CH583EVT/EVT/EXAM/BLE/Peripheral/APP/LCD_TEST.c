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

// сюда можно писать различные тесты и процедуры для LCD!! и вызывать их из основного цикла !!
// да бы не ломать основную прогу!!
#include "CONFIG.h"
#include "my_assist32.h" // дополнительные битовые макросы и макросы типов заимственны из STM8 Raide
#include "my_test.h"
#include "my_large_LCD32.h"
#include "lcd_test.h"



// для большого LCD типа SK7 - тестирование драйвера "прямого управления" через резестивный делитель
// напряжения для выводов COM1-COM4

void    LCD_SK7_Test1(void);
void    LCD_Global_Test1(void);


void    LCD_SK7_Test1(void)
{

    // pack_temperature123D(125);//
    // pack_temperature9876D(845);

    //pack123D_custom(((SIGN_H<<16)|(SIGN_O<<8)|SIGN_t));
    //pack123D_custom(((get_symbol(1)<<16)|(get_symbol(2)<<8)|get_symbol(3)));
    pack123D_custom(((get_symbol(4)<<16)|(get_symbol(5)<<8)|get_symbol(6)));
    //функция get_symbol возвращает перекодированное значение для знакогенератора, введеного десятичного
    //параметра

    // функция pack123D_custom выводит значения в знакоместа 123
    // можно закидывать информацию в виде строки
    // а моожно по очереди выводить в каждое знакоместо  функциями типа pack1d ,2d,3d,9d,8d,7d,6d -
    // см pdf.

    // pack123D_custom(SIGN_t);
    // pack123D_custom(SIGN_t<<8);
    // pack123D_custom(SIGN_t<<16);
//-------------------------------------------------------------------------------------------------

    //  pack1d(get_symbol(5));// обращение к "отдельной восьмерке" 1d
    //  pack2d(get_symbol(4));// обращение к "отдельной восьмерке" 2d
    //  pack3d(get_symbol(3));// обращение к "отдельной восьмерке" 3d
    //  pack9d(get_symbol(5));// обращение к "отдельной восьмерке" 9d
    //  pack8d(get_symbol(4));// обращение к "отдельной восьмерке" 8d
    //  pack7d(get_symbol(3));// обращение к "отдельной восьмерке" 7d
    //  pack6d(get_symbol(2));// обращение к "отдельной восьмерке" 6d

//--------------------------вариант вывода тестовой надписи HOT
    //   pack1d(SIGN_H);
    //   pack2d(SIGN_O);
    //   pack3d(SIGN_t);

       //  pack9d(SIGN_t);
       //  pack8d(SIGN_E);
       //  pack7d(SIGN_S);
       //  pack6d(SIGN_t);

            pack9d(SIGN_r);
            pack8d(SIGN_S);
            pack7d(SIGN_t);



//--------------------------вариант вывода тестовой надписи HOT

    //   pack123D_custom(((SIGN_H<<16)|(SIGN_O<<8)|SIGN_t));


//------------------------ХИТРОЕ ЗНАКОМЕСТО--------------

    frame_5G_on(); // зажечь рамку
    //frame_5G_off()//потушить рамку
    pack_heap(ANT);//зажечь антенну
    //pack_heap(8);//зажечь "8"  или любое аналогичное число


}




// для малого LCD типа SK3 - тестирование драйвера "прямого управления" через резестивный делитель
// напряжения для выводов COM1-COM4

void    LCD_SK3_Test1(void);


void    LCD_SK3_Test1(void)
{

    // pack_temperature123D(125);//
    // pack_temperature9876D(845);

    //pack123D_custom(((SIGN_H<<16)|(SIGN_O<<8)|SIGN_t));
    //pack123D_custom(((get_symbol(1)<<16)|(get_symbol(2)<<8)|get_symbol(3)));
   // pack123D_custom(((get_symbol(4)<<16)|(get_symbol(5)<<8)|get_symbol(6)));
    //функция get_symbol возвращает перекодированное значение для знакогенератора, введеного десятичного
    //параметра

    // функция pack123D_custom выводит значения в знакоместа 123
    // можно закидывать информацию в виде строки
    // а моожно по очереди выводить в каждое знакоместо  функциями типа pack1d ,2d,3d,9d,8d,7d,6d -
    // см pdf.

    // pack123D_custom(SIGN_t);
    // pack123D_custom(SIGN_t<<8);
    // pack123D_custom(SIGN_t<<16);
//-------------------------------------------------------------------------------------------------

    //  pack1d(get_symbol(5));// обращение к "отдельной восьмерке" 1d
    //  pack2d(get_symbol(4));// обращение к "отдельной восьмерке" 2d
    //  pack3d(get_symbol(3));// обращение к "отдельной восьмерке" 3d
    //  pack9d(get_symbol(5));// обращение к "отдельной восьмерке" 9d
    //  pack8d(get_symbol(4));// обращение к "отдельной восьмерке" 8d
    //  pack7d(get_symbol(3));// обращение к "отдельной восьмерке" 7d
    //  pack6d(get_symbol(2));// обращение к "отдельной восьмерке" 6d

//--------------------------вариант вывода тестовой надписи HOT
    //   pack1d(SIGN_H);
    //   pack2d(SIGN_O);
    //   pack3d(SIGN_t);

    //  pack9d(SIGN_t);
    //  pack8d(SIGN_E);
    //  pack7d(SIGN_S);
    //  pack6d(SIGN_t);

    //   pack9d(SIGN_r);
    //   pack8d(SIGN_S);
    //   pack7d(SIGN_t);



        //pack1d(get_symbol(Count_Tik));// обращение к "отдельной восьмерке" 1d  +
        //pack2d(get_symbol(Count_Tik));// обращение к "отдельной восьмерке" 1d  +
        //pack3d(get_symbol(Count_Tik));// обращение к "отдельной восьмерке" 1d  +

         //  pack_temperature123D(-125);//

           //pack_temperature9876D(-845);
           //pack_temperature7654D(-845);

            //pack_hours(21);        //use this function to update hours
            //pack_hours(non_hour);        //use this function to update hours
            //pack_minutes(30);      //use this function to update minutes




#ifdef SK3_LCD
       // pack4d(get_symbol(Count_Tik));// обращение к "отдельной восьмерке" 1d  +
       // pack5d(get_symbol(Count_Tik));// обращение к "отдельной восьмерке" 1d  +
#endif
       // pack6d(get_symbol(Count_Tik));// обращение к "отдельной восьмерке" 1d  -
       // pack7d(get_symbol(Count_Tik));// обращение к "отдельной восьмерке" 1d  -

#ifndef SK3_LCD
       //pack8d(get_symbol(Count_Tik));// обращение к "отдельной восьмерке" 1d  +
       //pack9d(get_symbol(Count_Tik));// обращение к "отдельной восьмерке" 1d  +
#endif


   //----------------------------------остальные сегементы в статике SK3 & SK7
    sun_on();//+
    moon_on();//+
    house_out_on();//+
    house_in_on();//+
    percent_on();//+
    bar_out_on();//+
    bar_in_on();//+
    heat_on();//+
    clock_on();//+
    hand_on();//+
    second_sep_on();//+
    time_dots_on();//+
    celsium_on();// SK7 only
    minusup_on();// SK7 only
    lock_on();// SK7 only
    pack_heap(Count_Tik);// SK7 only
    frame_5G_on();// SK7 only
    //minusdw_on();
    //ANT_on();// выводим ANT в "хитрое знакоместо"



//--------------------------вариант вывода тестовой надписи HOT

    //pack123D_custom(((SIGN_H<<16)|(SIGN_O<<8)|SIGN_t));


//------------------------ХИТРОЕ ЗНАКОМЕСТО--------------

    //frame_5G_on(); // зажечь рамку
    //frame_5G_off()//потушить рамку
    //pack_heap(ANT);//зажечь антенну
    //pack_heap(8);//зажечь "8"  или любое аналогичное число

}


void    LCD_Global_Test1(void)
{


   // if(++Count_Tik==10)
    //                   {
    //                    Count_Tik=0;
     //                  }



    if(inverstest)
                  {
                  clear_screen(); // очистка ОЗУ экрана
                  LCD_SK3_Test1();

                //second_sep_on();
                pack_hours(Count_Tik);        //use this function to update hours
                pack_minutes(Count_Tik);//use this function to update hours

                  // тест для SK3 + SK7
                  pack_temperature123D(100+Count_Tik);

                  //pack_temperature9876D(100+Count_Tik);
                  //pack_temperature_TIME(999);

                  // тест для SK3
            //      pack_temperature7654D(100+Count_Tik);

                 // sun_on();//+
                 // moon_on();//+
                //  house_out_on();//+
                //  house_in_on();//+
                //  percent_on();//+
                //  bar_out_on();//+
                 // bar_in_on();//+
                 // heat_on();//+
                 // clock_on();//+
                 // hand_on();//+
                //  second_sep_on();//+
                 // time_dots_on();//+
                 // celsium_on();// SK7 only
                 // minusup_on();// SK7 only
                 // lock_on();// SK7 only
                //  minusdw_on();//+
                //  ANT_on();//+

                   //SEG_1_on();//+  SK3(single segment) and SK7(heap version)
                   //SEG_2_on();//+  SK3(single segment) and SK7(heap version)
                   //SEG_3_on();//+  SK3(single segment) and SK7(heap version)
                   //SEG_4_on();//+  SK3(single segment) and SK7(heap version)
                   //SEG_5_on();//+  SK3(single segment) and SK7(heap version)
                   //SEG_6_on();//+  SK3(single segment) and SK7(heap version)
                   //SEG_7_on();//+  SK3(single segment) and SK7(heap version)



                   //VideoToPort_SEG();

                 }else {

                clear_screen();// очистка ОЗУ экрана
                LCD_SK3_Test1();

               //second_sep_off();
               //pack_hours(non_hour);//use this function to update hours
               //pack_hours(defise_time);//use this function to update hours
               //pack_minutes(non_min);//use this function to update hours
               //pack_minutes(defise_time);//use this function to update hours

                // тест для SK3 + SK7
                pack_temperature123D(non_temp_large);//очистка температуры
                pack_temperature123D(defise_temp);// выводи только "дефис" на место значений
                // тест для SK3
               // pack_temperature7654D(non_temp_small);//очистка температуры
               // pack_temperature7654D(defise_temp);// выводи только "дефис" на место значений


                     pack_temperature_TIME(non_temp_small);
                     pack_temperature_TIME(defise_temp);

                  // pack_temperature9876D(non_temp_small);//очистка температуры
                  // pack_temperature9876D(defise_temp);// выводи только "дефис" на место значений

         //        pack_temperature7654D(non_temp_small);//очистка температуры
         //        pack_temperature7654D(defise_temp);// выводи только "дефис" на место значений


                //pack9d(0);// обращение к "отдельной восьмерке" 9d // очистка восьмерки
                //pack8d(0);// обращение к "отдельной восьмерке" 8d // очистка восьмерки
                //pack9d(SIGN_DEFIS);// обращение к "отдельной восьмерке" 9d
                //pack8d(SIGN_DEFIS);// обращение к "отдельной восьмерке" 8d

              //  sun_off();
              //  moon_off();
              //  house_out_off();
              //  house_in_off();
              //  percent_off();
               // bar_out_off();
               // bar_in_off();
               // heat_off();
              //  clock_off();
               // hand_off();
               // second_sep_off();
               // time_dots_off();
              //  celsium_off();// SK7 only
              //  minusup_off();// SK7 only
              //  lock_off();// SK7 only
              //  minusdw_off();
             //   ANT_off();

                // pack_heap(non_heap);// SK7 only
                 //pack_heap(defis_heap);// SK7 only

                 //SEG_1_off();//+ SK3 only
                 //SEG_2_off();//+ SK3 only
                 //SEG_3_off();//+ SK3 only
                 //SEG_4_off();//+ SK3 only
                 //SEG_5_off();//+ SK3 only
                 //SEG_6_off();//+ SK3 only
                // SEG_7_off();//+ SK3 only



                 //VideoToPort_SEG();// выводим результат рендеринга в ОЗУ

                 }

           }









