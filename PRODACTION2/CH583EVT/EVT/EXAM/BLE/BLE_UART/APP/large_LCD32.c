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
#include "my_large_LCD32.h"
#include "alex_board.h"



#define    out_LCD_ON       0x01
#define    out_LCD_OFF      0x00

#define    discharghe       0x01
#define    charghe          0x02

#define    com1_charge      0x01
#define    com1_discharge   0x02
#define    com2_charge      0x03
#define    com2_discharge   0x04
#define    com3_charge      0x05
#define    com3_discharge   0x06
#define    com4_charge      0x07
#define    com4_discharge   0x08

#define    ANT              10


//-------------------для Charge/ Disharge-------------------

  u32 tempB=0;
  u32 tempA=0;
  u32 mask=0x00000001;
  int cnt=0;
  u32 tmp =0;

//--------------imported functions
//-------------------выходные буфера для комов
u32 com1;   //buffer for com1
u32 com2;   //buffer for com2
u32 com3;   //buffer for com3
u32 com4;   //buffer for com4
s16 fsm;    //автомат
s16 fsm2;   //автомат
u32 lcd_flags;
u32 lcd_debug1;
u32 lcd_debug2;
u32 lcd_debug3;

u32 outportA,outportB;

u32 COM1_charghe_PA,COM2_charghe_PA,COM3_charghe_PA,COM4_charghe_PA;
u32 COM1_charghe_PB,COM2_charghe_PB,COM3_charghe_PB,COM4_charghe_PB;

u32 COM1_discharghe_PA,COM2_discharghe_PA,COM3_discharghe_PA,COM4_discharghe_PA;
u32 COM1_discharghe_PB,COM2_discharghe_PB,COM3_discharghe_PB,COM4_discharghe_PB;



//----------------------flash распиновка сегментов
const u32 segpin[20]={  LCDPIN5,   LCDPIN6,   LCDPIN7,   LCDPIN8,
            LCDPIN9,   LCDPIN10,  LCDPIN11,  LCDPIN12,
            LCDPIN13,  LCDPIN14,  LCDPIN15,  LCDPIN16,
            LCDPIN17,  LCDPIN18,  LCDPIN19,  LCDPIN20,
            LCDPIN21,  LCDPIN22,  LCDPIN23,  LCDPIN24};
// and some usefull things
//------------------------------------генератор цифр
const char symgen[]={
            (SEGA|SEGB|SEGC|SEGD|SEGE|SEGF) ,       //'0'
            (SEGB|SEGC)         ,                   //'1'
            (SEGA|SEGB|SEGD|SEGE|SEGG)  ,           //'2'
            (SEGA|SEGB|SEGC|SEGD|SEGG)  ,           //'3'
            (SEGB|SEGC|SEGG|SEGF)       ,           //'4'
            (SEGA|SEGF|SEGG|SEGC|SEGD)  ,           //'5'
            (SEGA|SEGG|SEGC|SEGD|SEGE|SEGF) ,       //'6'
            (SEGA|SEGB|SEGC)        ,               //'7'
            (SEGA|SEGB|SEGC|SEGD|SEGE|SEGF|SEGG),   //'8'
            (SEGA|SEGB|SEGC|SEGD|SEGF|SEGG) ,       //'9'
             0x00,                                  // 10 -  all are shut off
            (SEGG)    };                            // '--' 11- non_line
//--------------------------------генератор цифр
const u16  symgen2[]={

       (HSYM_4A|HSYM_4B|HSYM_5I|HSYM_5D|HSYM_4E|HSYM_4I|HSYM_4F|HSYM_4D)                         , // '0' NEW SK7
       (HSYM_4B|HSYM_4C|HSYM_4H|HSYM_4D|HSYM_4E)                                                 , // '1' NEW SK7
       (HSYM_4A|HSYM_4B|HSYM_5I|HSYM_4H|HSYM_4G|HSYM_4I|HSYM_4E|HSYM_4D)                         , // '2' NEW SK7
       (HSYM_4A|HSYM_4B|HSYM_5I|HSYM_4H|HSYM_4G|HSYM_5D|HSYM_4E|HSYM_4D)                         , // '3' NEW SK7
       (HSYM_5I|HSYM_4H|HSYM_4G|HSYM_5D|HSYM_4F)                                                 , // '4' NEW SK7
       (HSYM_4A|HSYM_4B|HSYM_4H|HSYM_4G|HSYM_4F|HSYM_5D|HSYM_4E|HSYM_4D)                         , // '5' NEW SK7
       (HSYM_4A|HSYM_4B|HSYM_4H|HSYM_4G|HSYM_4F|HSYM_5D|HSYM_4E|HSYM_4I|HSYM_4D)                 , // '6' NEW SK7
       (HSYM_4A|HSYM_4B|HSYM_5I|HSYM_5D)                                                         , // '7' NEW SK7
       (HSYM_4A|HSYM_4B|HSYM_4H|HSYM_4G|HSYM_4F|HSYM_5D|HSYM_4E|HSYM_4I|HSYM_5I|HSYM_4D)         , // '8' NEW SK7
       (HSYM_4A|HSYM_4B|HSYM_4H|HSYM_4G|HSYM_4F|HSYM_5D|HSYM_4E|HSYM_5I|HSYM_4D)                 , // '9' NEW SK7
       (HSYM_4C|HSYM_4H|HSYM_4C|HSYM_5E|HSYM_5F)                                                 , // 'ANT' NEW SK7
       (HSYM_4G|HSYM_4H)                                                                         , //  HEAP  DEFIS
        0x0000                                                                                   , // 11- all are shut off
                     };
//-----------------------------


//--prototypes for internal use
void    My_drive_ALL(void);
void    drive_ALL(void);
void    drive_COM1(void);
void    drive_COM2(void);
void    drive_COM3(void);
void    drive_COM4(void);
void    drive_COM_dead(void);
void    dead_time_phase(void);
void    charge_SEG(u32,u8);
void    discharge_SEG(u32,u8);
void    VideoToPort_SEG(void);
void    SEG_PortToLCD_OUT(u32,u8);

u16     bindec_decoder(int);


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& logic of driving segments
//           |com|seg_on|seg_off|
//     charge| 0 |  1   |  0    |
//  discharge| 1 |  0   |  1    |
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
void    drive_ALL(void){
    //-------------

    if((fsm&0x00000001)){

        dead_time_phase();
            return;
        }


        if(fsm2==COM1_WORK){
            drive_COM1();
            if(fsm==CHARGE_ACT_COMX){   //заряд
            //    COM1_LOW;       //заряд -низкий уровень
                charge_SEG(com1,out_LCD_ON);
                COM1_LOW; }
            else{               //разряд -высокий уровень
                //COM1_HIGH;
                discharge_SEG(com1,out_LCD_ON);
                COM1_HIGH; }
            return;
        }
        //------------
        if(fsm2==COM2_WORK){
            drive_COM2();
            if(fsm==CHARGE_ACT_COMX){   //charge operation
             //   COM2_LOW;
                charge_SEG(com2,out_LCD_ON);
                COM2_LOW; }
            else{               //discharge operation
             //   COM2_HIGH;
                discharge_SEG(com2,out_LCD_ON);
                COM2_HIGH; }
            return;
        }
        //------------
        if(fsm2==COM3_WORK){
            drive_COM3();
            if(fsm==CHARGE_ACT_COMX){   //charge operation
            //    COM3_LOW;
                charge_SEG(com3,out_LCD_ON);
                COM3_LOW; }
            else{               //discharge operation
              //  COM3_HIGH;
                discharge_SEG(com3,out_LCD_ON);
                COM3_HIGH; }
            return;
        }
        //------------
        if(fsm2==COM4_WORK){
            drive_COM4();
            if(fsm==CHARGE_ACT_COMX){   //charge operation
            //    COM4_LOW;
                charge_SEG(com4,out_LCD_ON);
                COM4_LOW; }
            else{                //discharge operation
             //   COM4_HIGH;
                discharge_SEG(com4,out_LCD_ON);
                COM4_HIGH; }
            return;
        }

}



void    dead_time_phase(void){
    drive_COM_dead();   //все пины в ноль
    SEGA_DEAD;
    SEGB_DEAD;
}

void init_LCD(void){
    //---------enable needed clocks(see init_RCC)
    //-------- function "perform_fsms" performs setup and drive COMs and drive SEG

    // -- настриваем все ноги LCD включая COM1-COM4 на выходы и кидаем все на "0"
    //GPIOA_ModeCfg(p2|p3|p6|p10|p11|p12|p13|p14|p15, GPIO_ModeOut_PP_20mA );
    //GPIOA_ModeCfg(p2|p3|p6|p12|p13|p14|p15|p8|p9, GPIO_ModeOut_PP_20mA );

#ifndef  SK3_LCD    // если определен большой єкран
    GPIOA_ModeCfg(p2|p3|p6|p12|p13|p14|p15|p8|p9, GPIO_ModeOut_PP_20mA );
#else
    GPIOA_ModeCfg(p6|p12|p13|p14|p15|p8|p9, GPIO_ModeOut_PP_20mA );
#endif


    GPIOB_ModeCfg( p0|p1|p2|p3|p4|p5|p6|p7|p8|p9|16|p17|p18|p19|p20, GPIO_ModeOut_PP_20mA );

    //GPIOB_ModeCfg( p0|p1|p2|p3|p4|p5|p6|p7|p8|p9|16|p17|p18|p19|p20|p13|p12, GPIO_ModeOut_PP_20mA );
    // p10|p11 - надо перебить, так как на них весит часовой кварц 32768!!! на p13|p12 или PB23 и PA5 !!!


#ifndef  SK3_LCD    // если определен большой єкран
    GPIOA_ResetBits(p2|p3|p6|p12|p13|p14|p15|p8|p9);
#else  //  иначе малый, и SEG19/20 определен под LED RED/ LED GREEN
    GPIOA_ResetBits(p6|p12|p13|p14|p15|p8|p9);
#endif


    GPIOB_ResetBits(p0|p1|p2|p3|p4|p5|p6|p7|p8|p9|16|p17|p18|p19|p20);

    //GPIOB_ResetBits(p0|p1|p2|p3|p4|p5|p6|p7|p8|p9|16|p17|p18|p19|p20|p13|p12);

    // p10|p11 - надо перебить, так как на них весит часовой кварц 32768!!!

    //-------------------------------------------------
    //fsm=DISCHARGE_DEAD_COMX;        // discharge com4-> charge com1
    //fsm2=COM4_WORK;             //last com

   // настриваем и запускаем  Timer0 ( в дальнейшем можно TASK) с базовой частотой +-60 Hzh

   // TMR0_TimerInit(FREQ_SYS / 160);         //  100ms

   // TMR0_ITCfg(ENABLE, TMR0_3_IT_CYC_END); //

}


//-----------------------------------------
void COM1_COM4_Handler(void);

void COM1_COM4_Handler(void)
{
    fsm++;              // новое состояние
        //  if(lcd_flags&BYPASS_ON)fsm++;   // новое состояние
            if(fsm>3)fsm2++;    // круговорот
            fsm&=FSM_MASK;      //ограничение состояний
            fsm2&=FSM2_MASK;    //ограничение состояний


            drive_ALL();            //сгенерировать новый выход //

            if(fsm&0x00000001)
            {
               // TMR0_TimerInit( DEAD_TIME/2.5);
                 TMR0_TimerInit( DEAD_TIME/2);//  625*2
               // tmos_start_task( task1 , sub_event_2 ,1.6*1*30 );
            }
            else{

               // TMR0_TimerInit( ACTIVE_TIME/2.5);
                 TMR0_TimerInit( ACTIVE_TIME/2); //625*5
               // tmos_start_task( task1 , sub_event_2 ,1.6*1*30 );
            }


}


//-------------------------------------------
//----------------переводят 1 ком на выход 3 на вход
#pragma inline
void    drive_COM1() {
    //GPIOB->CRL = ((GPIOB->CRL & 0x000fffff) | 0x44400000);    // PB7(COM2) input/float(U/2) // PB6(COM3)input/float(U/2) // PB5(COM4) input/float(U/2)
    //GPIOB->CRH = ((GPIOB->CRH & 0xfffffff0) | 0x00000002);  // PB8(COM1) output(2mHz)/push_pull -> out "0" or "1"
    // CRL : 0100|0100|0100|0000|0000|0000|0000|0000
    // CRH : 0000|0000|0000|0000|0000|0000|0000|0010

       GPIOB_ModeCfg( PIN1_LCD_COM1, GPIO_ModeOut_PP_20mA );
       GPIOB_ModeCfg( PIN2_LCD_COM2|PIN3_LCD_COM3|PIN4_LCD_COM4, GPIO_ModeIN_Floating );

      // GPIOA_ModeCfg(p2|p3|p6|p10|p11|p12|p13|p14|p15, GPIO_ModeOut_PP_20mA );
    //   GPIOB_ModeCfg( p0|p1|p2|p3|p4|p9|16|p17|p18|p19|p20, GPIO_ModeOut_PP_20mA );


}
//---------------------------------------------
#pragma inline
void    drive_COM2() {
    //GPIOB->CRL = ((GPIOB->CRL & 0x000fffff) | 0x24400000);    // PB7(COM2) output(2mHz)/push_pull // PB6(COM3)input/float(U/2) // PB5(COM4) input/float(U/2)
    //GPIOB->CRH = ((GPIOB->CRH & 0xfffffff0) | 0x00000004);  // PB8(COM1) input/float(U/2)
    // CRL : 0010|0100|0100|0000|0000|0000|0000|0000
    // CRH : 0000|0000|0000|0000|0000|0000|0000|0100

       GPIOB_ModeCfg( PIN2_LCD_COM2, GPIO_ModeOut_PP_20mA );
       GPIOB_ModeCfg( PIN1_LCD_COM1|PIN3_LCD_COM3|PIN4_LCD_COM4, GPIO_ModeIN_Floating );


      // GPIOA_ModeCfg(p2|p3|p6|p10|p11|p12|p13|p14|p15, GPIO_ModeOut_PP_20mA );
      // GPIOB_ModeCfg( p0|p1|p2|p3|p4|p9|16|p17|p18|p19|p20, GPIO_ModeOut_PP_20mA );
}
//----------------------------------------------
#pragma inline
void    drive_COM3() {
    //GPIOB->CRL = ((GPIOB->CRL & 0x000fffff) | 0x42400000);   // PB7(COM2) input/float(U/2) // PB6(COM3)output(2mHz)/push_pull  // PB5(COM4) input/float(U/2)
    //GPIOB->CRH = ((GPIOB->CRH & 0xfffffff0) | 0x00000004);   // PB8(COM1) input/float(U/2)
    // CRL : 0100|0010|0100|0000|0000|0000|0000|0000
    // CRH : 0000|0000|0000|0000|0000|0000|0000|0100

       GPIOB_ModeCfg( PIN3_LCD_COM3, GPIO_ModeOut_PP_20mA );
       GPIOB_ModeCfg( PIN1_LCD_COM1|PIN2_LCD_COM2|PIN4_LCD_COM4, GPIO_ModeIN_Floating );


      // GPIOA_ModeCfg(p2|p3|p6|p10|p11|p12|p13|p14|p15, GPIO_ModeOut_PP_20mA );
      // GPIOB_ModeCfg( p0|p1|p2|p3|p4|p9|16|p17|p18|p19|p20, GPIO_ModeOut_PP_20mA );


}
//---------------------------------------------
#pragma inline
void    drive_COM4() {
    //GPIOB->CRL = ((GPIOB->CRL & 0x000fffff) | 0x44200000);    // PB7(COM2) input/float(U/2) // PB6(COM3) input/float(U/2)  // PB5(COM4) output(2mHz)/push_pull
    //GPIOB->CRH = ((GPIOB->CRH & 0xfffffff0) | 0x00000004);  // PB8(COM1) input/float(U/2)

      GPIOB_ModeCfg( PIN4_LCD_COM4, GPIO_ModeOut_PP_20mA );
      GPIOB_ModeCfg( PIN2_LCD_COM2|PIN3_LCD_COM3|PIN1_LCD_COM1, GPIO_ModeIN_Floating );


     // GPIOA_ModeCfg(p2|p3|p6|p10|p11|p12|p13|p14|p15, GPIO_ModeOut_PP_20mA );
    //  GPIOB_ModeCfg( p0|p1|p2|p3|p4|p9|16|p17|p18|p19|p20, GPIO_ModeOut_PP_20mA );

}
//--------------------------все комы выходы и в нуле
#pragma inline
void    drive_COM_dead() {
    //GPIOB->CRL = ((GPIOB->CRL & 0x000fffff) | 0x22200000);   // режим всех СOM переводим output(2mHz)/push_pull !!!
    //GPIOB->CRH = ((GPIOB->CRH & 0xfffffff0) | 0x00000002);   //
    //GPIOB->ODR &= ~(p5 | p6 | p7 | p8); // переводим все комы в "0" на выходе

    GPIOB_ModeCfg( PIN1_LCD_COM1|PIN2_LCD_COM2|PIN3_LCD_COM3|PIN4_LCD_COM4, GPIO_ModeOut_PP_20mA );
    GPIOB_ResetBits( PIN1_LCD_COM1|PIN2_LCD_COM2|PIN3_LCD_COM3|PIN4_LCD_COM4);

    GPIOB_ResetBits(p5|p6|p7|p8);
    //GPIOB->ODR |= (p5 | p6 | p7 | p8); // переводим все комы в "0" на выходе (тест на обратный потенциал!)


}
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& logic of driving segments
//           |seg_on|seg_off|
//     charge|  1   |  0    |
//  discharge|  0   |  1    |
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//------------------------------------------------
void charge_SEG(u32 source, u8 OUT){ //заряд

    tempB=0;
    tempA=0;
    mask=0x00000001;
    cnt=0;
    tmp =0;


    outportA =0; // чистим глобальные буферы
    outportB =0;

   // tempB=GPIOB_ReadPort();
   // tempA=GPIOA_ReadPort();


    tempB&=~MASK_SEG_PORTB;
    tempA&=~MASK_SEG_PORTA;    // почистить нужное


    do{
        tmp=segpin[cnt++];
        if(source&mask){        //сегмен включен 1->1
            if(tmp&PORTB)
                tempB|=tmp;     //и пин вкл
            else
                tempA|=tmp;
        }               //если выключен, 0->0
        mask<<=1;
    }while(mask!=0x00100000);      //4*5 =20 пин крутить

//    GPIOB->ODR=(tempB&(~PORTB));        //почистить индетификатор
//    GPIOA->ODR=tempA;       //обновить
    //  R32_PB_OUT = tempB;        //почистить индетификатор


    if(OUT==out_LCD_ON)
    {
      R32_PB_OUT=(tempB&(~PORTB))|port_analog_pow_mask|port_rel_mask |port_ligth_mask; //выводим распаковку сегментную на пины портов LCD
      //R32_PB_OUT=(tempB&(~PORTB)); //выводим распаковку сегментную на пины портов LCD

#ifdef SK3_LCD   // если  определен малый экран

      tempA = tempA&(~p2)&(~p3);// чистим в "0 "  пин Red/ Green в зависимости  от текущего состояния port_red_green_mask
      R32_PA_OUT = tempA|port_red_green_mask|port_CS0_mask ;// на подчищенное место для пин Red/ Green наклдаываем port_red_green_mask

   //   R32_PA_OUT = tempA ; //

 #else
        R32_PA_OUT = tempA ; //
#endif


    }else{

        outportB = (tempB&(~PORTB));// ничего не выводим на LCD
        //R32_PB_OUT=(tempB&(~PORTB))|port_analog_pow_mask|port_rel_mask |port_ligth_mask; //выводим распаковку сегментную на пины портов LCD

        outportA = tempA ;//

    }

}

//------------------------------------------------
void discharge_SEG(u32 source,u8 OUT){ //разряд

    tempB=0;
    tempA=0;
    mask=0x00000001;
    cnt=0;
    tmp =0;

    outportA =0;
    outportB =0;


  //  tempB=GPIOB_ReadPort();
   // tempA=GPIOA_ReadPort();

    tempB&=~MASK_SEG_PORTB;
    tempA&=~MASK_SEG_PORTA;    // почистить нужное


    do{
        tmp=segpin[cnt++];
        if(!(source&mask)){     //сегмен выключен 0->1
            if(tmp&PORTB)tempB|=tmp;     //then pin on
            else tempA|=tmp;
        }               //если включен 1->0
        mask<<=1;
    }while(mask!=0x00100000);      //4*5 =20 пин крутить

 //   GPIOB->ODR=(tempB&(~PORTB));        //почистить индетификатор
 //   GPIOA->ODR=tempA;           //обновить

      if(OUT==out_LCD_ON)
          {
            R32_PB_OUT=(tempB&(~PORTB))|port_analog_pow_mask|port_rel_mask|port_ligth_mask ; //выводим распаковку сегментную на пины портов LCD
            //R32_PB_OUT=(tempB&(~PORTB)); //выводим распаковку сегментную на пины портов LCD

            // паралельно включаем (накладываем в выход порта)PIN 11 (PB11 - аналоговое питание )

#ifdef SK3_LCD   // если  определен малый экран

        tempA = tempA&(~p2)&(~p3);// чистим в "0 "  пин Red/ Green в зависимости  от текущего состояния port_red_green_mask
        R32_PA_OUT = tempA|port_red_green_mask|port_CS0_mask ;// на подчищенное место для пин Red/ Green наклдаываем port_red_green_mask

     //       R32_PA_OUT = tempA ; //

#else
       R32_PA_OUT = tempA ; //
#endif


          }else{

              outportB = (tempB&(~PORTB));// ничего не выводим на LCD, только в буфер
              //R32_PB_OUT=(tempB&(~PORTB))|port_analog_pow_mask|port_rel_mask |port_ligth_mask; //выводим распаковку сегментную на пины портов LCD

              outportA = tempA;//

          }


}
//-------------------------------------------------


void VideoToPort_SEG(void){

    //-----------------------------------------COM1
    charge_SEG(com1,out_LCD_OFF);
    COM1_charghe_PB=outportB ;//вывод распоковку сегментов в промежуточные регистры для их дальнейшего вывода на LCD
    resetbit(COM1_charghe_PB, PIN1_LCD_COM1);
    COM1_charghe_PA=outportA;

   //-----------------------------//
    discharge_SEG(com1,out_LCD_OFF);
    COM1_discharghe_PB=outportB;//вывод распоковку сегментов в промежуточные регистры для их дальнейшего вывода на LCD
    setbit(COM1_discharghe_PB, PIN1_LCD_COM1);
    COM1_discharghe_PA=outportA;

  //--------------------------------------------COM2
  //----------------------------//
    charge_SEG(com2,out_LCD_OFF);
    COM2_charghe_PB=outportB;//вывод распоковку сегментов в промежуточные регистры для их дальнейшего вывода на LCD
    resetbit(COM2_charghe_PB, PIN2_LCD_COM2);
    COM2_charghe_PA=outportA;
  //----------------------------//
    discharge_SEG(com2,out_LCD_OFF);
    COM2_discharghe_PB=outportB;//вывод распоковку сегментов в промежуточные регистры для их дальнейшего вывода на LCD
    setbit(COM2_discharghe_PB, PIN2_LCD_COM2);
    COM2_discharghe_PA=outportA;

  //--------------------------------------------COM3
  //----------------------------//
    charge_SEG(com3,out_LCD_OFF);
    COM3_charghe_PB=outportB;//вывод распоковку сегментов в промежуточные регистры для их дальнейшего вывода на LCD
    resetbit(COM3_charghe_PB, PIN3_LCD_COM3);
    COM3_charghe_PA=outportA;
  //----------------------------//
    discharge_SEG(com3,out_LCD_OFF);
    COM3_discharghe_PB=outportB;//вывод распоковку сегментов в промежуточные регистры для их дальнейшего вывода на LCD
    setbit(COM3_discharghe_PB, PIN3_LCD_COM3);
    COM3_discharghe_PA=outportA;

    //-------------------------------------------COM4
    //----------------------------//
    charge_SEG(com4,out_LCD_OFF);
    COM4_charghe_PB=outportB;//вывод распоковку сегментов в промежуточные регистры для их дальнейшего вывода на LCD
    resetbit(COM4_charghe_PB, PIN4_LCD_COM4);
    COM4_charghe_PA=outportA;
  //----------------------------//
    discharge_SEG(com4,out_LCD_OFF);
    COM4_discharghe_PB=outportB;//вывод распоковку сегментов в промежуточные регистры для их дальнейшего вывода на LCD
    setbit(COM4_discharghe_PB, PIN4_LCD_COM4);
    COM4_discharghe_PA=outportA;



}

void SEG_PortToLCD_OUT(u32 source , u8 state){

//--------------------------------------COM1
if((source==com1_charge)&(state==charghe))
{
    R32_PB_OUT= COM1_charghe_PB;
    R32_PA_OUT= COM1_charghe_PA;
    //COM1_LOW;
    //COM1_OUT;
}

if((source==com1_discharge)&(state==discharghe))
{
    R32_PB_OUT= COM1_discharghe_PB;
    R32_PA_OUT= COM1_discharghe_PA;
    //COM1_HIGH;
    //COM1_OUT;
}
//---------------------------------------COM2
if((source==com2_charge)&(state==charghe))
{
    R32_PB_OUT= COM2_charghe_PB;
    R32_PA_OUT= COM2_charghe_PA;
    //COM2_LOW;
    //COM2_OUT;
}

if((source==com2_discharge)&(state==discharghe))
{
    R32_PB_OUT= COM2_discharghe_PB;
    R32_PA_OUT= COM2_discharghe_PA;
    //COM2_HIGH;
    //COM2_OUT;
}
//-----------------------------------------COM3
if((source==com3_charge)&(state==charghe))
{
    R32_PB_OUT= COM3_charghe_PB;
    R32_PA_OUT= COM3_charghe_PA;
    //COM3_LOW;
    //COM3_OUT;
}

if((source==com3_discharge)&(state==discharghe))
{
    R32_PB_OUT= COM3_discharghe_PB;
    R32_PA_OUT= COM3_discharghe_PA;
    //COM3_HIGH;
    //COM3_OUT;
}
//------------------------------------------COM4
if((source==com4_charge)&(state==charghe))
{
    R32_PB_OUT= COM4_charghe_PB;
    R32_PA_OUT= COM4_charghe_PA;
    //COM4_LOW;
    //COM4_OUT;
}

if((source==com4_discharge)&(state==discharghe))
{
    R32_PB_OUT= COM4_discharghe_PB;
    R32_PA_OUT= COM4_discharghe_PA;
    //COM4_HIGH;
    //COM4_OUT;
}


}



//--------------------------очистка екрана
void    clear_screen(void){
    com1=0;
    com2=0;
    com3=0;
    com4=0;
}
//------------------------------
char    get_symbol(char what){return symgen[what];};
//------------------------------запаковка знакоместа


#ifdef SK3_LCD

void    pack1d(char symbol){
    u32 temp;

    if(symbol&SEGA)com1|=NEW_TMPR1D_1A;

    temp=com2;
    if(symbol&SEGB)temp|=NEW_TMPR1D_1B;
    if(symbol&SEGF)temp|=NEW_TMPR1D_1F;

    com2=temp;
    temp=com3;
    if(symbol&SEGC)temp|=NEW_TMPR1D_1C;
    if(symbol&SEGG)temp|=NEW_TMPR1D_1G;

    com3=temp;
    temp=com4;
    if(symbol&SEGE)temp|=NEW_TMPR1D_1E;
    if(symbol&SEGD)temp|=NEW_TMPR1D_1D;

    com4=temp;
}

#else



void    pack1d(char symbol){
    u32 temp;
    if(symbol&SEGA)com1|=TMPR1D_1A;
    temp=com2;
    if(symbol&SEGB)temp|=TMPR1D_1B;
    if(symbol&SEGF)temp|=TMPR1D_1F;
    com2=temp;
    temp=com3;
    if(symbol&SEGE)temp|=TMPR1D_1E;
    if(symbol&SEGG)temp|=TMPR1D_1G;
    com3=temp;
    temp=com4;
    if(symbol&SEGC)temp|=TMPR1D_1C;
    if(symbol&SEGD)temp|=TMPR1D_1D;
    com4=temp;
}

#endif
//---------------------------------------

#ifdef SK3_LCD

void    pack2d(char symbol){
    u32 temp;
    if(symbol&SEGA)com1|=NEW_TMPR2D_2A;
    temp=com2;
    if(symbol&SEGB)temp|=NEW_TMPR2D_2B;
    if(symbol&SEGF)temp|=NEW_TMPR2D_2F;
    com2=temp;
    temp=com3;
    if(symbol&SEGC)temp|=NEW_TMPR2D_2C;
    if(symbol&SEGG)temp|=NEW_TMPR2D_2G;
    com3=temp;
    temp=com4;
    if(symbol&SEGE)temp|=NEW_TMPR2D_2E;
    if(symbol&SEGD)temp|=NEW_TMPR2D_2D;
    com4=temp;
}
#else


void    pack2d(char symbol){
    u32 temp;
    if(symbol&SEGA)com1|=TMPR2D_2A;
    temp=com2;
    if(symbol&SEGB)temp|=TMPR2D_2B;
    if(symbol&SEGF)temp|=TMPR2D_2F;
    com2=temp;
    temp=com3;
    if(symbol&SEGE)temp|=TMPR2D_2E;
    if(symbol&SEGG)temp|=TMPR2D_2G;
    com3=temp;
    temp=com4;
    if(symbol&SEGC)temp|=TMPR2D_2C;
    if(symbol&SEGD)temp|=TMPR2D_2D;
    com4=temp;
}

#endif

//-----------------------------------------

#ifdef SK3_LCD

void    pack3d(char symbol){
    u32 temp;
    if(symbol&SEGA)com1|=NEW_TMPR3D_3A;
    temp=com2;
    if(symbol&SEGB)temp|=NEW_TMPR3D_3B;
    if(symbol&SEGF)temp|=NEW_TMPR3D_3F;
    com2=temp;
    temp=com3;
    if(symbol&SEGC)temp|=NEW_TMPR3D_3C;
    if(symbol&SEGG)temp|=NEW_TMPR3D_3G;
    com3=temp;
    temp=com4;
    if(symbol&SEGE)temp|=NEW_TMPR3D_3E;
    if(symbol&SEGD)temp|=NEW_TMPR3D_3D;
    com4=temp;
}
#else

void    pack3d(char symbol){
    u32 temp;
    if(symbol&SEGA)com1|=TMPR3D_3A;
    temp=com2;
    if(symbol&SEGB)temp|=TMPR3D_3B;
    if(symbol&SEGF)temp|=TMPR3D_3F;
    com2=temp;
    temp=com3;
    if(symbol&SEGE)temp|=TMPR3D_3E;
    if(symbol&SEGG)temp|=TMPR3D_3G;
    com3=temp;
    temp=com4;
    if(symbol&SEGC)temp|=TMPR3D_3C;
    if(symbol&SEGD)temp|=TMPR3D_3D;
    com4=temp;
}

#endif





//-----------------------------------------

#ifdef SK3_LCD

void    pack4d(char symbol){
    u32 temp;
    if(symbol&SEGD)com1|=NEW_TIME4D_4D;
    temp=com2;
    if(symbol&SEGC)temp|=NEW_TIME4D_4C;
    if(symbol&SEGE)temp|=NEW_TIME4D_4E;
    com2=temp;
    temp=com3;
    if(symbol&SEGB)temp|=NEW_TIME4D_4B;
    if(symbol&SEGG)temp|=NEW_TIME4D_4G;
    com3=temp;
    temp=com4;
    if(symbol&SEGA)temp|=NEW_TIME4D_4A;
    if(symbol&SEGF)temp|=NEW_TIME4D_4F;
    com4=temp;
}


#endif

#ifdef SK3_LCD

void    pack5d(char symbol){
    u32 temp;

       if(symbol&SEGD)com1|=NEW_TIME5D_5D;
       temp=com2;
       if(symbol&SEGC)temp|=NEW_TIME5D_5C;
       if(symbol&SEGE)temp|=NEW_TIME5D_5E;
       com2=temp;
       temp=com3;
       if(symbol&SEGB)temp|=NEW_TIME5D_5B;
       if(symbol&SEGG)temp|=NEW_TIME5D_5G;
       com3=temp;
       temp=com4;
       if(symbol&SEGA)temp|=NEW_TIME5D_5A;
       if(symbol&SEGF)temp|=NEW_TIME5D_5F;
       com4=temp;

}


#endif


#ifdef SK3_LCD

void    pack6d(char symbol){
    u32 temp;

    temp=com1;
     if(symbol&SEGD)temp|=NEW_TIME6D_6D;
    com1=temp;

    temp=com2;
    if(symbol&SEGC)temp|=NEW_TIME6D_6C;
    if(symbol&SEGE)temp|=NEW_TIME6D_6E;
    com2=temp;

    temp=com3;
    if(symbol&SEGB)temp|=NEW_TIME6D_6B;
    if(symbol&SEGG)temp|=NEW_TIME6D_6G;
    com3=temp;

    temp=com4;
    if(symbol&SEGA)temp|=NEW_TIME6D_6A;
    if(symbol&SEGF)temp|=NEW_TIME6D_6F;
    com4=temp;
}

#else

void    pack6d(char symbol){
    u32 temp;
    if(symbol&SEGD)com1|=TIME6D_6D;
    temp=com2;
    if(symbol&SEGC)temp|=TIME6D_6C;
    if(symbol&SEGE)temp|=TIME6D_6E;
    com2=temp;
    temp=com3;
    if(symbol&SEGF)temp|=TIME6D_6F;
    if(symbol&SEGG)temp|=TIME6D_6G;
    com3=temp;
    temp=com4;
    if(symbol&SEGA)temp|=TIME6D_6A;
    if(symbol&SEGB)temp|=TIME6D_6B;
    com4=temp;
}
#endif



//----------------------------------------
#ifdef SK3_LCD

void    pack7d(char symbol){
    u32 temp;
    if(symbol&SEGD)com1|=NEW_TIME7D_7D;
    temp=com2;
    if(symbol&SEGC)temp|=NEW_TIME7D_7C;
    if(symbol&SEGE)temp|=NEW_TIME7D_7E;
    com2=temp;
    temp=com3;
    if(symbol&SEGB)temp|=NEW_TIME7D_7B;
    if(symbol&SEGG)temp|=NEW_TIME7D_7G;
    com3=temp;
    temp=com4;
    if(symbol&SEGA)temp|=NEW_TIME7D_7A;
    if(symbol&SEGF)temp|=NEW_TIME7D_7F;
    com4=temp;
}
#else

void    pack7d(char symbol){
    u32 temp;
    if(symbol&SEGD)com1|=TIME7D_7D;
    temp=com2;
    if(symbol&SEGC)temp|=TIME7D_7C;
    if(symbol&SEGE)temp|=TIME7D_7E;
    com2=temp;
    temp=com3;
    if(symbol&SEGF)temp|=TIME7D_7F;
    if(symbol&SEGG)temp|=TIME7D_7G;
    com3=temp;
    temp=com4;
    if(symbol&SEGA)temp|=TIME7D_7A;
    if(symbol&SEGB)temp|=TIME7D_7B;
    com4=temp;
}
#endif



//---------------------------------------


#ifndef  SK3_LCD                    // если не определен SK3 LCD , то доступно для  SK7 LCD

void    pack8d(char symbol){
    u32 temp;
    if(symbol&SEGD)com1|=TIME8D_8D;
    temp=com2;
    if(symbol&SEGC)temp|=TIME8D_8C;
    if(symbol&SEGE)temp|=TIME8D_8E;
    com2=temp;
    temp=com3;
    if(symbol&SEGF)temp|=TIME8D_8F;
    if(symbol&SEGG)temp|=TIME8D_8G;
    com3=temp;
    temp=com4;
    if(symbol&SEGA)temp|=TIME8D_8A;
    if(symbol&SEGB)temp|=TIME8D_8B;
    com4=temp;
}
//----------------------------------------

#endif

#ifndef  SK3_LCD                     // если не определен SK3 LCD , то доступно для SK7 LCD

void    pack9d(char symbol){
    u32 temp;
    if(symbol&SEGD)com1|=TIME9D_9D;
    temp=com2;
    if(symbol&SEGC)temp|=TIME9D_9C;
    if(symbol&SEGE)temp|=TIME9D_9E;
    com2=temp;
    temp=com3;
    if(symbol&SEGF)temp|=TIME9D_9F;
    if(symbol&SEGG)temp|=TIME9D_9G;
    com3=temp;
    temp=com4;
    if(symbol&SEGA)temp|=TIME9D_9A;
    if(symbol&SEGB)temp|=TIME9D_9B;
    com4=temp;
}

#endif
//----------------------------------
u16 bindec_decoder(int value){
    #define MINUS  0x4000
    // значения в пределах 000-999
    u16 result=0;

    if(value<0){        //минусовое
        value=0-value;      //плюсовое
        result|=MINUS;    //минус в результате
    }
    result|=(value/100)<<8; //сотни
    value%=100;
    result|=(value/10)<<4;  //десятки
    result|=value%10;       //мелочь
    return result;
}

//-------------------------------------
void  allseg(void){  //заженчь все сегменгты
    com1=ALLGEG;
    com2=ALLGEG;
    com3=ALLGEG;
    com4=ALLGEG;
}
//-------------------------------------температера на 123

#ifdef SK3_LCD

void    pack_temperature123D(int temperature){
    u16 decoded;
    u16 temp;
    if(temperature<non_temp_large )
        {
    minusdw_off();
    decoded=bindec_decoder(temperature);
    pack3d(get_symbol(decoded&0x000f));     //dimes
    decoded>>=4;
    pack2d(get_symbol(decoded&0x000f));     //tens
    decoded>>=4;
    temp=decoded&0x000f;
    if(temp)pack1d(get_symbol(temp));      //non zero pack, zero scip
    if(decoded&0x00f0)minusdw_on();
        }

    if(temperature==non_temp_large)
         {
           pack1d(get_symbol(10));
           pack2d(get_symbol(10));
           pack3d(get_symbol(10));
         }
    if(temperature==defise_temp )
         {
          pack1d(get_symbol(11));
          pack2d(get_symbol(11));
          pack3d(get_symbol(11));
         }
        celsium_on();
}

#else

void    pack_temperature123D(int temperature){
    u16 decoded;
    u16 temp;

    if(temperature<non_temp_large )
    {
    minusdw_off();
    decoded=bindec_decoder(temperature);
    pack3d(get_symbol(decoded&0x000f));     //dimes
    decoded>>=4;
    pack2d(get_symbol(decoded&0x000f));     //tens
    decoded>>=4;
    temp=decoded&0x000f;
    if(temp)pack1d(get_symbol(temp));      //non zero pack, zero scip
    if(decoded&0x00f0)minusdw_on();
    }

    if(temperature==non_temp_large)
      {
        pack1d(get_symbol(10));
        pack2d(get_symbol(10));
        pack3d(get_symbol(10));
      }

    if(temperature==defise_temp )
        {
          pack1d(get_symbol(11));
          pack2d(get_symbol(11));
          pack3d(get_symbol(11));
        }

    celsium_on();
}
#endif
//---------------------------------------температера на7654

#ifdef SK3_LCD

void    pack_temperature7654D(int temperature){
    u16 decoded;
    u16 temp;
    minusup_off();
    if(temperature<non_temp_small )
           {
    decoded=bindec_decoder(temperature);
    pack4d(get_symbol(decoded&0x000f));     //dimes
    decoded>>=4;
    pack5d(get_symbol(decoded&0x000f));     //tens
    decoded>>=4;
    temp=decoded&0x000f;
    if(temp)pack6d(get_symbol(temp));      //non zero pack, zero scip
    if(decoded&0x00f0)minusup_on();
           }
    if(temperature==non_temp_small)
        {
          pack4d(get_symbol(10));
          pack5d(get_symbol(10));
          pack6d(get_symbol(10));
        }
      if(temperature==defise_temp )
          {
            pack4d(get_symbol(11));
            pack5d(get_symbol(11));
            pack6d(get_symbol(11));
          }
    time_dots_on();              //decimal point and degree sign
}
#else

//---------------------------------------температера на9876

void    pack_temperature9876D(int temperature){
    u16 decoded;
    u16 temp;
    minusup_off();
    if(temperature<non_temp_small )
    {
    decoded=bindec_decoder(temperature);
    pack7d(get_symbol(decoded&0x000f));     //dimes
    decoded>>=4;
    pack8d(get_symbol(decoded&0x000f));     //tens
    decoded>>=4;
    temp=decoded&0x000f;
    if(temp)pack9d(get_symbol(temp));      //non zero pack, zero scip
    if(decoded&0x00f0)minusup_on();
     }
    if(temperature==non_temp_small)
      {
       pack7d(get_symbol(10));
       pack8d(get_symbol(10));
       pack9d(get_symbol(10));
      }
    if(temperature==defise_temp )
      {
       pack7d(get_symbol(11));
       pack8d(get_symbol(11));
       pack9d(get_symbol(11));
       }

    time_dots_on();              //decimal point and degree sign
}

#endif

//------------------------АВТООПРЕДЕЛЯЕМАЯ ПРИ КОМПИЛЯЦИИ  ФУНКЦИЯ ДЛЯ ОБОИХ ДРАЙВЕРОВ С ОБЩИМ ВЫЗОВОМ-------------//

#ifdef SK3_LCD

void  pack_temperature_TIME(int temperature)
{
    u16 decoded;
        u16 temp;
        minusup_off();
        if(temperature<non_temp_small )
               {
        decoded=bindec_decoder(temperature);
        pack4d(get_symbol(decoded&0x000f));     //dimes
        decoded>>=4;
        pack5d(get_symbol(decoded&0x000f));     //tens
        decoded>>=4;
        temp=decoded&0x000f;
        if(temp)pack6d(get_symbol(temp));      //non zero pack, zero scip
        if(decoded&0x00f0)minusup_on();
               }
        if(temperature==non_temp_small)
            {
              pack4d(get_symbol(10));
              pack5d(get_symbol(10));
              pack6d(get_symbol(10));
            }
          if(temperature==defise_temp )
              {
                pack4d(get_symbol(11));
                pack5d(get_symbol(11));
                pack6d(get_symbol(11));
              }
        time_dots_on();
}
#else

void  pack_temperature_TIME(int temperature)
{
    u16 decoded;
        u16 temp;
        minusup_off();
        if(temperature<non_temp_small )
        {
        decoded=bindec_decoder(temperature);
        pack7d(get_symbol(decoded&0x000f));     //dimes
        decoded>>=4;
        pack8d(get_symbol(decoded&0x000f));     //tens
        decoded>>=4;
        temp=decoded&0x000f;
        if(temp)pack9d(get_symbol(temp));      //non zero pack, zero scip
        if(decoded&0x00f0)minusup_on();
         }
        if(temperature==non_temp_small)
          {
           pack7d(get_symbol(10));
           pack8d(get_symbol(10));
           pack9d(get_symbol(10));
          }
        if(temperature==defise_temp )
          {
           pack7d(get_symbol(11));
           pack8d(get_symbol(11));
           pack9d(get_symbol(11));
           }
        time_dots_on();              //decimal point and degree sign
}

#endif




#ifdef SK3_LCD
//---------------------------------------минуты
void    pack_minutes(int minutes){
    u16 decoded=bindec_decoder(minutes);
    if(minutes<non_min)
    {
    pack4d(get_symbol(decoded&0x000f));     //few
    decoded>>=4;
    pack5d(get_symbol(decoded&0x000f));  //tens
    }
    if(minutes==non_min)
        {
        pack4d(get_symbol(10));
        pack5d(get_symbol(10));
        }
    if(minutes==defise_time)
        {
        pack4d(get_symbol(11));
        pack5d(get_symbol(11));
        }
        }
//----------------------------------------часы
void    pack_hours(int hours){
    u16 decoded=bindec_decoder(hours);
    if(hours<non_hour)
    {
    pack6d(get_symbol(decoded&0x000f));     //few
    decoded>>=4;
    pack7d(get_symbol(decoded&0x000f));     //tens
    }
    if(hours==non_hour)
       {
           pack6d(get_symbol(10));
           pack7d(get_symbol(10));
       }
    if(hours==defise_time)
       {
           pack6d(get_symbol(11));
           pack7d(get_symbol(11));
       }
}



void    pack_year(int16_t year)
{
 int16_t year_buf1,year_buf2, year_hundreds,year_terns;

 year_buf1=year;
 year_buf2 =year;

 year_hundreds = year_buf1/100;
 year_terns = year_buf2 -  year_hundreds*100 ;

 pack_hours(year_hundreds);//обновляем знакоместо часы  - значением "сотни лет"
 pack_minutes(year_terns); //обновляем знакоместо минуты  - значением "десятки лет"

}

#else

//---------------------------------------минуты
void    pack_minutes(int minutes){
    u16 decoded=bindec_decoder(minutes);
    if(minutes<non_min)
    {
    pack6d(get_symbol(decoded&0x000f));     //few
    decoded>>=4;
    pack7d(get_symbol(decoded&0x000f));     //tens
    }
        if(minutes==non_min)
      {
          pack6d(get_symbol(10));
          pack7d(get_symbol(10));
      }
       if(minutes==defise_time)
      {
          pack6d(get_symbol(11));
          pack7d(get_symbol(11));
      }
}
//----------------------------------------часы
void    pack_hours(int hours){
    u16 decoded=bindec_decoder(hours);

    if(hours<non_hour)
    {
    pack8d(get_symbol(decoded&0x000f));     //few
    decoded>>=4;
    pack9d(get_symbol(decoded&0x000f));     //tens
    }
    if(hours==non_hour)
    {
        pack8d(get_symbol(10));
        pack9d(get_symbol(10));
    }
    if(hours==defise_time)
    {
        pack8d(get_symbol(11));
        pack9d(get_symbol(11));
    }
}



void    pack_year(int16_t year)
{
 int16_t year_buf1,year_buf2, year_hundreds,year_terns;

 year_buf1=year;
 year_buf2 =year;

 year_hundreds = year_buf1/100;
 year_terns = year_buf2 -  year_hundreds*100 ;

 pack_hours(year_hundreds);//обновляем знакоместо часы  - значением "сотни лет"
 pack_minutes(year_terns); //обновляем знакоместо минуты  - значением "десятки лет"

}





//---------------------------------------

void    pack_heap(int digit){               //хитрое знакоместо
    u16 pack;
    int temp=symgen2[digit];
    pack=temp&COM1_CL_MASK;
    com1|=(pack<<6);
    pack=temp&COM2_CL_MASK;
    com2|=(pack<<2);
    pack=temp&COM3_CL_MASK;
    com3|=(pack>>2);
    pack=temp&COM4_CL_MASK;
    com4|=(pack>>6);
}


#endif


//---------------------------------------
void    pack123D_custom(int segpattern){ //запаковка чем угодно
    pack1d((char)(segpattern>>16));
    pack2d((char)(segpattern>>8));
    pack3d((char)segpattern);
}


#ifndef  SK3_LCD  // ЕСЛИ  ОПРЕДЕЛЕН НЕ МАЛЫЙ ЭКРАН , Т. Е БОЛЬШОЙ
//-----------------------------
void    pack9876D_custom(int segpattern){ ////запаковка чем угодно 31-24b->DIGIT9, 23-16b->DIGIT3, 15-8b->DIGIT2, 7-0b->DIGIT1
    pack9d((char)(segpattern>>24));
    pack8d((char)(segpattern>>16));
    pack7d((char)(segpattern>>8));
    pack6d((char)segpattern);
}
#else  // иначе "малый"

void    pack9876D_custom(int segpattern){ ////запаковка чем угодно 31-24b->DIGIT9, 23-16b->DIGIT3, 15-8b->DIGIT2, 7-0b->DIGIT1
    pack7d((char)(segpattern>>24));
    pack6d((char)(segpattern>>16));
    pack5d((char)(segpattern>>8));
    pack4d((char)segpattern);
}


void    pack_day(int digit)// вівод дня недели для малого ЖКИ
{

    switch(digit){
        case 1: SEG_1_on();       break;
        case 2: SEG_2_on();       break;
        case 3: SEG_3_on();       break;
        case 4: SEG_4_on();       break;
        case 5: SEG_5_on();       break;
        case 6: SEG_6_on();       break;
        case 7: SEG_7_on();       break;

        case ~1: SEG_1_off();       break;
        case ~2: SEG_2_off();       break;
        case ~3: SEG_3_off();       break;
        case ~4: SEG_4_off();       break;
        case ~5: SEG_5_off();       break;
        case ~6: SEG_6_off();       break;
        case ~7: SEG_7_off();       break;

    }



}








#endif












//-------------------------
void    houses_control(int variant){ //домики

    switch(variant){
        case 5: moon_on();       break;
        case 4: house_in_on();   break;
        case 3: bar_out_on();    break;
        case 2: bar_in_on();     break;
        case 1: house_out_on();  break;
        case 0: sun_on();        break;
        case 6: {moon_on();house_in_on();
             bar_out_on();bar_in_on();
             house_out_on();sun_on();break;}
    }


}




#ifdef SK3_LCD

//----------------------------------отдельные сегменты  SK3 LCD
void    sun_on(){com4|=SUN_1I;};
void    sun_off(){com4&=~SUN_1I;};
void    moon_on(){com3|=MOON_1H;};
void    moon_off(){com3&=~MOON_1H;};
void    house_out_on(){com1|=HOUSEOUT_10C;};
void    house_out_off(){com1&=~HOUSEOUT_10C;};
void    house_in_on(){com1|=HOUSEIN_2H;};
void    house_in_off(){com1&=~HOUSEIN_2H;};
void    percent_on(){com1|=PERCENT_2I;};
void    percent_off(){com1&=~PERCENT_2I;};
void    bar_out_on(){com2|=BAROUT_10H;};
void    bar_out_off(){com2&=~BAROUT_10H;};
void    bar_in_on(){com1|=BARIN_10B;};
void    bar_in_off(){com1&=~BARIN_10B;};
void    celsium_on(){com1|=CELSIUM_3H;};
void    celsium_off(){com1&=~CELSIUM_3H;};
void    heat_on(){com1|=HEAT_9I;};
void    heat_off(){com1&=~HEAT_9I;};
void    clock_on(){com4|=CLOCK_9H;};
void    clock_off(){com4&=~CLOCK_9H;};
void    second_sep_on(){com1|=TIMESEP_8H;};
void    second_sep_off(){com1&=~TIMESEP_8H;};
void    time_dots_on(){com1|=TIMEDOT_7H;};
void    time_dots_off(){com1&=~TIMEDOT_7H;};
void    hand_on(){com3|=HAND_6H;};
void    hand_off(){com3&=~HAND_6H;};
void    minusdw_on(){com1|=LWMINUS_T;};
void    minusdw_off(){com1&=~LWMINUS_T;};
void    minusup_on(){com3|=UPMINUS_TEMP;};
void    minusup_off(){com3&=~UPMINUS_TEMP;};
void    ANT_on(){com2|=ANT_T22;};
void    ANT_off(){com2&=~ANT_T22;};

//------------------------------- 7 DAY BAR-----------------------------//


void    SEG_1_on(){com4|=SEG_1;};
void    SEG_1_off(){com4&=~SEG_1;};
void    SEG_2_on(){com3|=SEG_2;};
void    SEG_2_off(){com3&=~SEG_2;};
void    SEG_3_on(){com2|=SEG_3;};
void    SEG_3_off(){com2&=~SEG_3;};
void    SEG_4_on(){com2|=SEG_4;};
void    SEG_4_off(){com2&=~SEG_4;};
void    SEG_5_on(){com3|=SEG_5;};
void    SEG_5_off(){com3&=~SEG_5;};
void    SEG_6_on(){com4|=SEG_6;};
void    SEG_6_off(){com4&=~SEG_6;};
void    SEG_7_on(){com1|=SEG_7;};
void    SEG_7_off(){com1&=~SEG_7;};


//----------------------------------------
#else


//----------------------------------отдельные сегменты  SK7 LCD
void    sun_on(){com4|=SUN_1I;};
void    sun_off(){com4&=~SUN_1I;};
void    moon_on(){com4|=MOON_1H;};
void    moon_off(){com4&=~MOON_1H;};
void    house_out_on(){com3|=HOUSEOUT_10C;};
void    house_out_off(){com3&=~HOUSEOUT_10C;};
void    house_in_on(){com1|=HOUSEIN_2H;};
void    house_in_off(){com1&=~HOUSEIN_2H;};
void    percent_on(){com1|=PERCENT_2I;};
void    percent_off(){com1&=~PERCENT_2I;};
void    bar_out_on(){com1|=BAROUT_10H;};
void    bar_out_off(){com1&=~BAROUT_10H;};
void    bar_in_on(){com2|=BARIN_10B;};
void    bar_in_off(){com2&=~BARIN_10B;};
void    celsium_on(){com1|=CELSIUM_3H;};
void    celsium_off(){com1&=~CELSIUM_3H;};
void    heat_on(){com1|=HEAT_9I;};
void    heat_off(){com1&=~HEAT_9I;};
void    clock_on(){com1|=CLOCK_9H;};
void    clock_off(){com1&=~CLOCK_9H;};
void    second_sep_on(){com1|=TIMESEP_8H;};
void    second_sep_off(){com1&=~TIMESEP_8H;};
void    time_dots_on(){com1|=TIMEDOT_7H;};
void    time_dots_off(){com1&=~TIMEDOT_7H;};
void    hand_on(){com1|=HAND_6H;};
void    hand_off(){com1&=~HAND_6H;};
void    frame_5G_on(){com3|=HEAP_5G;};
void    frame_5G_off(){com3&=~HEAP_5G;};
void    minusup_on(){com2|=UPMINUS_T1;};
void    minusup_off(){com2&=~UPMINUS_T1;};
void    minusdw_on(){com4|=LWMINUS_T;};
void    minusdw_off(){com4&=~LWMINUS_T;};
void    lock_on(){com1|=LOCK_T2;};
void    lock_off(){com2&=~LOCK_T2;};

//---------------------------------ХИТРОЕ ЗНАКОМЕСТО--------------------------------//

void    ANT_on(){com2|=HEAP_5E;com2|=HEAP_4H;com3|=HEAP_4C;com4|=HEAP_5F;};
void    ANT_off(){com2&=~HEAP_5E;com2&=~HEAP_4H;com3&=~HEAP_4C;com4&=~HEAP_5F;};

void    SEG_1_on(){ pack_heap(1);};
void    SEG_1_off(){ pack_heap(non_heap);};
void    SEG_2_on(){ pack_heap(2);};
void    SEG_2_off(){ pack_heap(non_heap);};
void    SEG_3_on(){ pack_heap(3);};
void    SEG_3_off(){ pack_heap(non_heap);};
void    SEG_4_on(){ pack_heap(4);};
void    SEG_4_off(){ pack_heap(non_heap);};
void    SEG_5_on(){ pack_heap(5);};
void    SEG_5_off(){ pack_heap(non_heap);};
void    SEG_6_on(){ pack_heap(6);};
void    SEG_6_off(){ pack_heap(non_heap);};
void    SEG_7_on(){ pack_heap(7);};
void    SEG_7_off(){ pack_heap(non_heap);};


#endif

//--------------------------------------



