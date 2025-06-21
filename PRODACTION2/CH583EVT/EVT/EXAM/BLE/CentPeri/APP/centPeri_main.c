/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : WCH
 * Version            : V1.1
 * Date               : 2019/11/05
 * Description        :
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for 
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

/*********************************************************************
 * INCLUDES
 */
#include "CONFIG.h"
#include "HAL.h"
#include "peripheral.h"
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
 * @brief   ��ѭ��
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
 * @brief   ������
 *
 * @return  none
 */
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

    PRINT("\n");
    PRINT("\n");
    PRINT("Start  ChipID CH5%02x\n", R8_CHIP_ID);
    PRINT("\n");
    PRINT("%s\n", VER_LIB);
    PRINT("\n");

    PRINT("%s\n", VER_LIB);
    CH58X_BLEInit();
    HAL_Init();
    GAPRole_PeripheralInit();
    GAPRole_CentralInit();
    Peripheral_Init();
    Central_Init();
    Main_Circulation();
}

/******************************** endfile @ main ******************************/
