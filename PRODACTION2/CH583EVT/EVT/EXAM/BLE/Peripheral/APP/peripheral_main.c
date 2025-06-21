/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : WCH
 * Version            : V1.1
 * Date               : 2020/08/06
 * Description        : 外设从机应用主函数及任务系统初始化
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for 
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

/******************************************************************************/
/* 头文件包含 */
#include "CONFIG.h"
#include "HAL.h"
#include "gattprofile.h"
#include "peripheral.h"


#include <math.h>
#include <stdio.h>
#include <stdlib.h> // для перехода на русский язык

#include "CONFIG.h"
#include "HAL.h"
#include "gattprofile.h"
#include "peripheral.h"
#include "my_assist32.h" // дополнительные битовые макросы и макросы типов заимственны из STM8 Raide
#include "my_large_LCD32.h"
#include "my_directtest.h"
#include "my_test.h"
#include "lcd_test.h"
#include "PM_test.h"
#include "my_FLASH.h"
#include "alex_board.h"


#include "hlw8110.h"






/*********************************************************************
 * GLOBAL TYPEDEFS
 */
__attribute__((aligned(4))) uint32_t MEM_BUF[BLE_MEMHEAP_SIZE / 4];

//#if(defined(BLE_MAC)) && (BLE_MAC == TRUE)
const uint8_t MacAddr[6] = {0x84, 0xC2, 0xE4, 0x03, 0x02, 0x02};
//#endif







//extern void performPeriodicTask(void);



/*********************************************************************
 * @fn      Main_Circulation
 *
 * @brief   主循环
 *
 * @return  none
 */

/*
__HIGH_CODE
__attribute__((noinline))
void Main_Circulation()
{
    while(1)
    {


       // performPeriodicTask();
        TMOS_SystemProcess();
    }
}

*/
/*********************************************************************
 * @fn      main
 *
 * @brief   主函数
 *
 * @return  none
 */
/*
int main(void)
{
    SetSysClock(CLK_SOURCE_PLL_60MHz);
     GPIOA_ModeCfg(GPIO_Pin_All,GPIO_ModeOut_PP_20mA );//предварительно настравиваем все порты на нули
     GPIOB_ModeCfg(GPIO_Pin_All,GPIO_ModeOut_PP_20mA );//предварительно настравиваем все порты на нули
     GPIOA_ResetBits(GPIO_Pin_All);// обнуляем и проверяем что бы не было шума
     GPIOB_ResetBits(GPIO_Pin_All);

     // Делаем UART1 с пинов PA8/PA9 на PB12/PB13 ( он же основной USB для прошивания)
      GPIOPinRemap(ENABLE , RB_PIN_UART1); // ремап UART1 с порта А на портB (см даташит)
      GPIOB_ModeCfg(bRXD1, GPIO_ModeIN_PU);      // RXD-
      GPIOB_SetBits(bTXD1);
      GPIOB_ModeCfg(bTXD1, GPIO_ModeOut_PP_20mA);// TXD-

      UART1_DefInit();// MAX SPEED (800000/24 Mhz)
    PRINT("%s\n", VER_LIB);
    CH58X_BLEInit();
    HAL_Init();
    GAPRole_PeripheralInit();
    Peripheral_Init();
    TEST_Init();

    Main_Circulation();
}
*/

/******************************** endfile @ main ******************************/






//void    key_screen_work(void);
extern void app_uart_process(void);
extern void app_uart_init(void);
extern void hard_faile_reset(uint8 faill);
//extern void Test_Start_Boot-(void);
extern void Start_Boot_for_Schedule(void);
extern void Start_Boot_for_System(void);
extern void Start_Boot_for_Set_Temper(void);

extern uint8 ble_reset;





__HIGH_CODE
__attribute__((noinline))
void Main_Circulation()
{

    while(1)
        {

        TMOS_SystemProcess();
        app_uart_process();
        hard_faile_reset(ble_reset);// повторная инициализация всего без апаратного RESET


        }

}





int main(void)
{

   //  SetSysClock(CLK_SOURCE_PLL_24MHz);// оптимально
   // SetSysClock(CLK_SOURCE_PLL_32MHz);

   // SetSysClock(CLK_SOURCE_PLL_60MHz);

    SetSysClock(CLK_SOURCE_PLL_80MHz);

    GPIOA_ModeCfg(GPIO_Pin_All,GPIO_ModeOut_PP_20mA );//предварительно настравиваем все порты на нули
    GPIOB_ModeCfg(GPIO_Pin_All,GPIO_ModeOut_PP_20mA );//предварительно настравиваем все порты на нули
    GPIOA_ResetBits(GPIO_Pin_All);// обнуляем и проверяем что бы не было шума
    GPIOB_ResetBits(GPIO_Pin_All);

    DelayMs(200);

    clear_screen();
    init_LCD();//первый BREAKPOINT для дальнейшего раздупления JTAG !!!

  // PS:  для отладки значение системмной частоты и источника тактирования должны совпадать для нормальной работы
    // функций delay итд.
  // на более низких частотакх SetSysClock наблюдаются системмные сбои

//    PWR_DCDCCfg( ENABLE );






    // Делаем UART1 с пинов PA8/PA9 на PB12/PB13 ( он же основной USB для прошивания)
     GPIOPinRemap(ENABLE , RB_PIN_UART1); // ремап UART1 с порта А на портB (см даташит)

     GPIOB_ModeCfg(bRXD1, GPIO_ModeIN_PU);      // RXD-
     GPIOB_SetBits(bTXD1);
     GPIOB_ModeCfg(bTXD1, GPIO_ModeOut_PP_20mA);// TXD-

     UART1_DefInit();// MAX SPEED (800000/24 Mhz)

     PRINT("\n");
     PRINT("\n");
     PRINT("Start  ChipID CH5%02x\n", R8_CHIP_ID);
     PRINT("\n");
     PRINT("%s\n", VER_LIB);
     PRINT("\n");

//     Start_Boot_for_Schedule();
 //    Start_Boot_for_System();
 //    Start_Boot_for_Set_Temper();


// ИТОГО: на базе  Start_Boot_for_Time(); нужно еще выделить минимум 3 - и EEPROM/FLASH массива и их обработчики
// для пересохранения /обновления/ сброса данных в процессе работы и стартовой загрузки


    CH58X_BLEInit(); // без инициализации  не возможно отладка переменных !!
                     // ставим вызов этой функции именно ТУТ!!

//    GPIOA_ModeCfg(GPIO_Pin_All,GPIO_ModeOut_PP_20mA );//предварительно настравиваем все порты на нули
//    GPIOB_ModeCfg(GPIO_Pin_All,GPIO_ModeOut_PP_20mA );//предварительно настравиваем все порты на нули
//    GPIOA_ResetBits(GPIO_Pin_All);// обнуляем и проверяем что бы не было шума
//    GPIOB_ResetBits(GPIO_Pin_All);


    TMR0_TimerInit(FREQ_SYS / 160);         //  100ms
   //  TMR0_TimerInit(FREQ_SYS / 80);         //  100ms


    TMR0_ITCfg(ENABLE, TMR0_3_IT_CYC_END); //
    init_LCD();//первый BREAKPOINT для дальнейшего раздупления JTAG !!!
    clear_screen();

    //PFIC_EnableIRQ(TMR0_IRQn);// разрешаем прерывания  от ТАЙМЕРА0 LCD
    PFIC_DisableIRQ(TMR0_IRQn);// разрешаем прерывания  от ТАЙМЕРА0 LCD



//#define R_TRIGER_TEST
#ifdef  R_TRIGER_TEST
//------------------------------R TRIGER TEST ------------------------------------
      GPIOA_ModeCfg(GPIO_Pin_1, GPIO_ModeIN_PD);
      GPIOA_ITModeCfg(GPIO_Pin_1, GPIO_ITMode_HighLevel);
#endif
//----------------------------------------------------------------------------------

#define POWER_ON_OFF_PIN
#ifdef  POWER_ON_OFF_PIN
//------------------------------POWER ON OFF PIN " ON SLEEP EVENT "  -----------------------------------

      GPIOA_ModeCfg(GPIO_Pin_1, GPIO_ModeIN_Floating);// под пин POWER OFF/ON
     //GPIOA_ITModeCfg(GPIO_Pin_1, GPIO_ITMode_FallEdge); // работает и по уровню и по фронту
     //GPIOA_ITModeCfg(GPIO_Pin_1, GPIO_ITMode_LowLevel); // работает и по уровню и по фронту

     // в спячку впадаем по низкому уровню..
     //подбираем задержку и условние срабатывания уже на конечном устройстве

     // ВНИМАНИЕ!!!!

// PS: практически такой подход не стабилен к помехам в схемах со стационарным и неразвязанным питание
// для недопущения  ложных срабатываний  вход в "спячку производим" пулингом / измерениями ADC
// а проспания происходит по прерыванию Rising ADGE  on  пин POWER OFF/ON

      //блокировка всей клавы при долгом удержании
#endif
//---------------------------------------------------------------------------------


      PWR_PeriphWakeUpCfg(ENABLE, RB_SLP_RTC_WAKE, Long_Delay); // Включить паралельно нашей кнопке,  пробуждение по RTC с заданным до этого//
      PWR_PeriphWakeUpCfg(ENABLE, RB_SLP_GPIO_WAKE, Long_Delay);// повторно включаем модуль проспания GPIO

  //------------------------------------------------------------------------------


      PRINT("SET <<down_key_and_RTC>> MODE  OK... \n");


 //----------------------------------ENABLE ANALOG PIN POWER--------------------------------------//
      GPIOB_ModeCfg(GPIO_Pin_11, GPIO_ModeOut_PP_20mA);// ENABLE ANALOG PIN POWER
      GPIOB_SetBits(GPIO_Pin_11);
      port_analog_pow_mask = 0x00000800;// маска на выход управления analog_pow при обновлении PORTB для LCD
      GPIOB_ModeCfg( GPIO_Pin_21, GPIO_ModeOut_PP_20mA );// реле
      //GPIOB_ModeCfg( GPIO_Pin_12, GPIO_ModeOut_PP_20mA );//подсветка
      GPIOA_ModeCfg( GPIO_Pin_2|GPIO_Pin_3, GPIO_ModeOut_PP_20mA );// Red & Green Led

    //  GPIOA_ModeCfg(GPIO_Pin_4, GPIO_ModeOut_PP_20mA);// CS0 - DEBUG PIN
      //GPIOA_SetBits(GPIO_Pin_5);






//---------------------------------режим "ОТЛАДКА"--------------------------------------------------//
//#define  TEST_DEBUG
  #ifdef TEST_DEBUG
//--------- Тестово отладочная секция/ цикл-------------------------
    while(1)
    {}
    #endif


//------------------------------- BLE UART + рабочий шаблон------------------------------------------//
        GPIOA_ClearITFlagBit(GPIO_Pin_1);
        PRINT("\n");
        HAL_Init();
// --------------после HAL_Init() можно делать инициализацию всего остального итд --------------------//

        PRINT("  HAL_Init()      .... \n  ");
        PRINT("\n");
        PRINT("  START BLE + Main_Circulation()  ... \n  ");
        PRINT("\n");
        GAPRole_PeripheralInit();
        Peripheral_Init();

        TEST2_Init();

       // TEST_Init();

        GPIOA_ClearITFlagBit(GPIO_Pin_1);
        PFIC_DisableIRQ(GPIO_A_IRQn);// специально запрещаем что бы можно было начать со сканирования чистого флага GPIO INTA
        PFIC_EnableIRQ(RTC_IRQn); //
        GPIOA_ClearITFlagBit(GPIO_Pin_1);

        TMR0_TimerInit(FREQ_SYS / (160));         //  100ms
        TMR0_ITCfg(ENABLE, TMR0_3_IT_CYC_END); //
        PFIC_EnableIRQ(TMR0_IRQn);// разрешаем прерывания  от ТАЙМЕРА0 LCD

        ADC_setup();// инициализируем работу АЦП

//       WWDG_SetCounter(0); //Feed the dog // обновление сторожевого таймера Fsys =(131072/24000000)*255=1.392 сек
       // время полного переполнения 8 битного регистра R8_WDOG_COUNT
//       WWDG_ClearFlag();
 //      WWDG_ResetCfg(ENABLE);

  //      GPIOA_ModeCfg(GPIO_Pin_4, GPIO_ModeOut_PP_20mA);// CS0 - DEBUG PIN


  //      UART1_ByteTrigCfg(UART_4BYTE_TRIG);
  //      UART1_INTCfg(ENABLE, RB_IER_RECV_RDY | RB_IER_LINE_STAT);
     //   UART1_INTCfg(DISABLE, RB_IER_RECV_RDY | RB_IER_LINE_STAT);
  //      PFIC_EnableIRQ(UART1_IRQn);//PFIC_DisableIRQ
     //   PFIC_DisableIRQ(UART1_IRQn);//PFIC_DisableIRQ

        //UART1_DefInit1();//9600 + паритет
       // Init_HLW8110();

        Main_Circulation();



}

/******************************** endfile @ main ******************************/



