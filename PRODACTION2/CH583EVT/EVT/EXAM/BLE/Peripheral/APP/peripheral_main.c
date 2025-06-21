/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : WCH
 * Version            : V1.1
 * Date               : 2020/08/06
 * Description        : ����ӻ�Ӧ��������������ϵͳ��ʼ��
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for 
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

/******************************************************************************/
/* ͷ�ļ����� */
#include "CONFIG.h"
#include "HAL.h"
#include "gattprofile.h"
#include "peripheral.h"


#include <math.h>
#include <stdio.h>
#include <stdlib.h> // �էݧ� ��֧�֧��է� �ߧ� �����ܧڧ� ��٧��

#include "CONFIG.h"
#include "HAL.h"
#include "gattprofile.h"
#include "peripheral.h"
#include "my_assist32.h" // �է���ݧߧڧ�֧ݧ�ߧ�� �ҧڧ��ӧ�� �ާѧܧ���� �� �ާѧܧ���� ��ڧ��� �٧ѧڧާ��ӧ֧ߧߧ� �ڧ� STM8 Raide
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
 * @brief   ��ѭ��
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
 * @brief   ������
 *
 * @return  none
 */
/*
int main(void)
{
    SetSysClock(CLK_SOURCE_PLL_60MHz);
     GPIOA_ModeCfg(GPIO_Pin_All,GPIO_ModeOut_PP_20mA );//���֧էӧѧ�ڧ�֧ݧ�ߧ� �ߧѧ���ѧӧڧӧѧ֧� �ӧ�� ������ �ߧ� �ߧ�ݧ�
     GPIOB_ModeCfg(GPIO_Pin_All,GPIO_ModeOut_PP_20mA );//���֧էӧѧ�ڧ�֧ݧ�ߧ� �ߧѧ���ѧӧڧӧѧ֧� �ӧ�� ������ �ߧ� �ߧ�ݧ�
     GPIOA_ResetBits(GPIO_Pin_All);// ��ҧߧ�ݧ�֧� �� ����ӧ֧��֧� ���� �ҧ� �ߧ� �ҧ�ݧ� ���ާ�
     GPIOB_ResetBits(GPIO_Pin_All);

     // ���֧ݧѧ֧� UART1 �� ��ڧߧ�� PA8/PA9 �ߧ� PB12/PB13 ( ��� �ا� ���ߧ�ӧߧ�� USB �էݧ� �����ڧӧѧߧڧ�)
      GPIOPinRemap(ENABLE , RB_PIN_UART1); // ��֧ާѧ� UART1 �� ������ �� �ߧ� �����B (��� �էѧ�ѧ�ڧ�)
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
        hard_faile_reset(ble_reset);// ���ӧ���ߧѧ� �ڧߧڧ�ڧѧݧڧ٧ѧ�ڧ� �ӧ�֧ԧ� �ҧ֧� �ѧ�ѧ�ѧ�ߧ�ԧ� RESET


        }

}





int main(void)
{

   //  SetSysClock(CLK_SOURCE_PLL_24MHz);// ����ڧާѧݧ�ߧ�
   // SetSysClock(CLK_SOURCE_PLL_32MHz);

   // SetSysClock(CLK_SOURCE_PLL_60MHz);

    SetSysClock(CLK_SOURCE_PLL_80MHz);

    GPIOA_ModeCfg(GPIO_Pin_All,GPIO_ModeOut_PP_20mA );//���֧էӧѧ�ڧ�֧ݧ�ߧ� �ߧѧ���ѧӧڧӧѧ֧� �ӧ�� ������ �ߧ� �ߧ�ݧ�
    GPIOB_ModeCfg(GPIO_Pin_All,GPIO_ModeOut_PP_20mA );//���֧էӧѧ�ڧ�֧ݧ�ߧ� �ߧѧ���ѧӧڧӧѧ֧� �ӧ�� ������ �ߧ� �ߧ�ݧ�
    GPIOA_ResetBits(GPIO_Pin_All);// ��ҧߧ�ݧ�֧� �� ����ӧ֧��֧� ���� �ҧ� �ߧ� �ҧ�ݧ� ���ާ�
    GPIOB_ResetBits(GPIO_Pin_All);

    DelayMs(200);

    clear_screen();
    init_LCD();//��֧�ӧ�� BREAKPOINT �էݧ� �էѧݧ�ߧ֧ۧ�֧ԧ� ��ѧ٧է��ݧ֧ߧڧ� JTAG !!!

  // PS:  �էݧ� ���ݧѧէܧ� �٧ߧѧ�֧ߧڧ� ��ڧ��֧ާާߧ�� ��ѧ����� �� �ڧ����ߧڧܧ� ��ѧܧ�ڧ��ӧѧߧڧ� �է�ݧاߧ� ���ӧ�ѧէѧ�� �էݧ� �ߧ��ާѧݧ�ߧ�� ��ѧҧ���
    // ���ߧܧ�ڧ� delay �ڧ��.
  // �ߧ� �ҧ�ݧ֧� �ߧڧ٧ܧڧ� ��ѧ����ѧܧ� SetSysClock �ߧѧҧݧ�էѧ���� ��ڧ��֧ާާߧ�� ��ҧ��

//    PWR_DCDCCfg( ENABLE );






    // ���֧ݧѧ֧� UART1 �� ��ڧߧ�� PA8/PA9 �ߧ� PB12/PB13 ( ��� �ا� ���ߧ�ӧߧ�� USB �էݧ� �����ڧӧѧߧڧ�)
     GPIOPinRemap(ENABLE , RB_PIN_UART1); // ��֧ާѧ� UART1 �� ������ �� �ߧ� �����B (��� �էѧ�ѧ�ڧ�)

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


// ����������: �ߧ� �ҧѧ٧�  Start_Boot_for_Time(); �ߧ�اߧ� �֧�� �ӧ�է֧ݧڧ�� �ާڧߧڧާ�� 3 - �� EEPROM/FLASH �ާѧ��ڧӧ� �� �ڧ� ��ҧ�ѧҧ���ڧܧ�
// �էݧ� ��֧�֧����ѧߧ֧ߧڧ� /��ҧߧ�ӧݧ֧ߧڧ�/ ��ҧ���� �էѧߧߧ�� �� �����֧��� ��ѧҧ��� �� ���ѧ���ӧ�� �٧ѧԧ��٧ܧ�


    CH58X_BLEInit(); // �ҧ֧� �ڧߧڧ�ڧѧݧڧ٧ѧ�ڧ�  �ߧ� �ӧ�٧ާ�اߧ� ���ݧѧէܧ� ��֧�֧ާ֧ߧߧ�� !!
                     // ���ѧӧڧ� �ӧ�٧�� ����� ���ߧܧ�ڧ� �ڧާ֧ߧߧ� ������!!

//    GPIOA_ModeCfg(GPIO_Pin_All,GPIO_ModeOut_PP_20mA );//���֧էӧѧ�ڧ�֧ݧ�ߧ� �ߧѧ���ѧӧڧӧѧ֧� �ӧ�� ������ �ߧ� �ߧ�ݧ�
//    GPIOB_ModeCfg(GPIO_Pin_All,GPIO_ModeOut_PP_20mA );//���֧էӧѧ�ڧ�֧ݧ�ߧ� �ߧѧ���ѧӧڧӧѧ֧� �ӧ�� ������ �ߧ� �ߧ�ݧ�
//    GPIOA_ResetBits(GPIO_Pin_All);// ��ҧߧ�ݧ�֧� �� ����ӧ֧��֧� ���� �ҧ� �ߧ� �ҧ�ݧ� ���ާ�
//    GPIOB_ResetBits(GPIO_Pin_All);


    TMR0_TimerInit(FREQ_SYS / 160);         //  100ms
   //  TMR0_TimerInit(FREQ_SYS / 80);         //  100ms


    TMR0_ITCfg(ENABLE, TMR0_3_IT_CYC_END); //
    init_LCD();//��֧�ӧ�� BREAKPOINT �էݧ� �էѧݧ�ߧ֧ۧ�֧ԧ� ��ѧ٧է��ݧ֧ߧڧ� JTAG !!!
    clear_screen();

    //PFIC_EnableIRQ(TMR0_IRQn);// ��ѧ٧�֧�ѧ֧� ���֧��ӧѧߧڧ�  ��� ��������������0 LCD
    PFIC_DisableIRQ(TMR0_IRQn);// ��ѧ٧�֧�ѧ֧� ���֧��ӧѧߧڧ�  ��� ��������������0 LCD



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

      GPIOA_ModeCfg(GPIO_Pin_1, GPIO_ModeIN_Floating);// ���� ��ڧ� POWER OFF/ON
     //GPIOA_ITModeCfg(GPIO_Pin_1, GPIO_ITMode_FallEdge); // ��ѧҧ��ѧ֧� �� ��� ����ӧߧ� �� ��� ����ߧ��
     //GPIOA_ITModeCfg(GPIO_Pin_1, GPIO_ITMode_LowLevel); // ��ѧҧ��ѧ֧� �� ��� ����ӧߧ� �� ��� ����ߧ��

     // �� �����ܧ� �ӧ�ѧէѧ֧� ��� �ߧڧ٧ܧ�ާ� ����ӧߧ�..
     //���էҧڧ�ѧ֧� �٧ѧէ֧�اܧ� �� ���ݧ�ӧߧڧ� ���ѧҧѧ��ӧѧߧڧ� ��ا� �ߧ� �ܧ�ߧ֧�ߧ�� ������ۧ��ӧ�

     // ����������������!!!!

// PS: ���ѧܧ�ڧ�֧�ܧ� ��ѧܧ�� ���է��� �ߧ� ���ѧҧڧݧ֧� �� ���ާ֧�ѧ� �� ���֧ާѧ� ��� ���ѧ�ڧ�ߧѧ�ߧ�� �� �ߧ֧�ѧ٧ӧ�٧ѧߧߧ�� ��ڧ�ѧߧڧ�
// �էݧ� �ߧ֧է����֧ߧڧ�  �ݧ�اߧ�� ���ѧҧѧ��ӧѧߧڧ�  �ӧ��� �� "�����ܧ� ����ڧ٧ӧ�էڧ�" ���ݧڧߧԧ�� / �ڧ٧ާ֧�֧ߧڧ�ާ� ADC
// �� ������ѧߧڧ� ����ڧ���էڧ� ��� ���֧��ӧѧߧڧ� Rising ADGE  on  ��ڧ� POWER OFF/ON

      //�ҧݧ�ܧڧ��ӧܧ� �ӧ�֧� �ܧݧѧӧ� ���� �է�ݧԧ�� ��է֧�اѧߧڧ�
#endif
//---------------------------------------------------------------------------------


      PWR_PeriphWakeUpCfg(ENABLE, RB_SLP_RTC_WAKE, Long_Delay); // ���ܧݧ��ڧ�� ��ѧ�ѧݧ֧ݧ�ߧ� �ߧѧ�֧� �ܧߧ��ܧ�,  ����ҧ�اէ֧ߧڧ� ��� RTC �� �٧ѧէѧߧߧ�� �է� ����ԧ�//
      PWR_PeriphWakeUpCfg(ENABLE, RB_SLP_GPIO_WAKE, Long_Delay);// ���ӧ���ߧ� �ӧܧݧ��ѧ֧� �ާ�է�ݧ� ������ѧߧڧ� GPIO

  //------------------------------------------------------------------------------


      PRINT("SET <<down_key_and_RTC>> MODE  OK... \n");


 //----------------------------------ENABLE ANALOG PIN POWER--------------------------------------//
      GPIOB_ModeCfg(GPIO_Pin_11, GPIO_ModeOut_PP_20mA);// ENABLE ANALOG PIN POWER
      GPIOB_SetBits(GPIO_Pin_11);
      port_analog_pow_mask = 0x00000800;// �ާѧ�ܧ� �ߧ� �ӧ���� ����ѧӧݧ֧ߧڧ� analog_pow ���� ��ҧߧ�ӧݧ֧ߧڧ� PORTB �էݧ� LCD
      GPIOB_ModeCfg( GPIO_Pin_21, GPIO_ModeOut_PP_20mA );// ��֧ݧ�
      //GPIOB_ModeCfg( GPIO_Pin_12, GPIO_ModeOut_PP_20mA );//���է�ӧ֧�ܧ�
      GPIOA_ModeCfg( GPIO_Pin_2|GPIO_Pin_3, GPIO_ModeOut_PP_20mA );// Red & Green Led

    //  GPIOA_ModeCfg(GPIO_Pin_4, GPIO_ModeOut_PP_20mA);// CS0 - DEBUG PIN
      //GPIOA_SetBits(GPIO_Pin_5);






//---------------------------------��֧اڧ� "��������������"--------------------------------------------------//
//#define  TEST_DEBUG
  #ifdef TEST_DEBUG
//--------- ���֧���ӧ� ���ݧѧէ��ߧѧ� ��֧ܧ�ڧ�/ ��ڧܧ�-------------------------
    while(1)
    {}
    #endif


//------------------------------- BLE UART + ��ѧҧ��ڧ� ��ѧҧݧ��------------------------------------------//
        GPIOA_ClearITFlagBit(GPIO_Pin_1);
        PRINT("\n");
        HAL_Init();
// --------------����ݧ� HAL_Init() �ާ�اߧ� �է֧ݧѧ�� �ڧߧڧ�ڧѧݧڧ٧ѧ�ڧ� �ӧ�֧ԧ� ����ѧݧ�ߧ�ԧ� �ڧ�� --------------------//

        PRINT("  HAL_Init()      .... \n  ");
        PRINT("\n");
        PRINT("  START BLE + Main_Circulation()  ... \n  ");
        PRINT("\n");
        GAPRole_PeripheralInit();
        Peripheral_Init();

        TEST2_Init();

       // TEST_Init();

        GPIOA_ClearITFlagBit(GPIO_Pin_1);
        PFIC_DisableIRQ(GPIO_A_IRQn);// ���֧�ڧѧݧ�ߧ� �٧ѧ��֧�ѧ֧� ���� �ҧ� �ާ�اߧ� �ҧ�ݧ� �ߧѧ�ѧ�� ��� ��ܧѧߧڧ��ӧѧߧڧ� ��ڧ���ԧ� ��ݧѧԧ� GPIO INTA
        PFIC_EnableIRQ(RTC_IRQn); //
        GPIOA_ClearITFlagBit(GPIO_Pin_1);

        TMR0_TimerInit(FREQ_SYS / (160));         //  100ms
        TMR0_ITCfg(ENABLE, TMR0_3_IT_CYC_END); //
        PFIC_EnableIRQ(TMR0_IRQn);// ��ѧ٧�֧�ѧ֧� ���֧��ӧѧߧڧ�  ��� ��������������0 LCD

        ADC_setup();// �ڧߧڧ�ڧѧݧڧ٧ڧ��֧� ��ѧҧ��� ������

//       WWDG_SetCounter(0); //Feed the dog // ��ҧߧ�ӧݧ֧ߧڧ� ������ا֧ӧ�ԧ� ��ѧۧާ֧�� Fsys =(131072/24000000)*255=1.392 ��֧�
       // �ӧ�֧ާ� ���ݧߧ�ԧ� ��֧�֧��ݧߧ֧ߧڧ� 8 �ҧڧ�ߧ�ԧ� ��֧ԧڧ���� R8_WDOG_COUNT
//       WWDG_ClearFlag();
 //      WWDG_ResetCfg(ENABLE);

  //      GPIOA_ModeCfg(GPIO_Pin_4, GPIO_ModeOut_PP_20mA);// CS0 - DEBUG PIN


  //      UART1_ByteTrigCfg(UART_4BYTE_TRIG);
  //      UART1_INTCfg(ENABLE, RB_IER_RECV_RDY | RB_IER_LINE_STAT);
     //   UART1_INTCfg(DISABLE, RB_IER_RECV_RDY | RB_IER_LINE_STAT);
  //      PFIC_EnableIRQ(UART1_IRQn);//PFIC_DisableIRQ
     //   PFIC_DisableIRQ(UART1_IRQn);//PFIC_DisableIRQ

        //UART1_DefInit1();//9600 + ��ѧ�ڧ�֧�
       // Init_HLW8110();

        Main_Circulation();



}

/******************************** endfile @ main ******************************/



