/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : WCH
 * Version            : V1.1
 * Date               : 2020/08/06
 * Description        :
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for 
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

/******************************************************************************/
/* 头文件包含 */
#include "CONFIG.h"
#include "hal.h"
#include "central.h"

/*********************************************************************
 * GLOBAL TYPEDEFS
 */
__attribute__((aligned(4))) uint32_t MEM_BUF[BLE_MEMHEAP_SIZE / 4];

#if(defined(BLE_MAC)) && (BLE_MAC == TRUE)
const uint8_t MacAddr[6] = {0x84, 0xC2, 0xE4, 0x03, 0x02, 0x02};
#endif

/*********************************************************************
 * @fn      Main_Circulation
 *
 * @brief   主循环
 *
 * @return  none
 */
__HIGH_CODE
__attribute__((noinline))
void Main_Circulation()
{
    while(1)
    {
        TMOS_SystemProcess();
    }
}

/*********************************************************************
 * @fn      main
 *
 * @brief   主函数
 *
 * @return  none
 */
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
    GAPRole_CentralInit();
    Central_Init();
    Main_Circulation();
}

/******************************** endfile @ main ******************************/
