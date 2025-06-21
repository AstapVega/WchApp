/********************************** (C) COPYRIGHT *******************************
 * File Name          : peripheral.C
 * Author             : zhangxiyi @WCH
 * Version            : v0.1
 * Date               : 2020/11/26
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
#include "devinfoservice.h"
#include "gattprofile.h"
#include "peripheral.h"
#include "app_uart.h"

#include "ble_uart_service.h"





#include <math.h>
#include "CONFIG.h"
#include "devinfoservice.h"
#include "gattprofile.h"
#include "peripheral.h"
#include "ble_uart_service.h"
#include "app_drv_fifo.h"


#include "menu_vlad.h"
#include "alex_board.h"



/*********************************************************************
 * MACROS
 */
//The buffer length should be a power of 2
#define APP_UART_TX_BUFFER_LENGTH    512U
#define APP_UART_RX_BUFFER_LENGTH    2048U

/*********************************************************************
 * CONSTANTS
 */

/*********************************************************************
 * TYPEDEFS
 */

/*********************************************************************
 * GLOBAL VARIABLES

 */


extern uint8 Enable_notify(uint16 Connection_handle,uint8 Enable);

// peripheralConnItem_t peripheralConnList;

// Connection item list
static peripheralConnItem_t peripheralConnList;


extern int8  BLE_NEW_DATA;

#define to_test__b_4_size  20 // ��ѧ٧ާ֧� �ާѧ��ڧӧ� ��֧���ӧ�ԧ� to_test_buffer2

extern uint16_t read_length;
extern uint8_t FOR_BUFER;
extern uint8_t to_test_buffer4[to_test__b_4_size];
extern  uint8_t to_test_buffer42[to_test__b_4_size];

uint8_t to_test_buffer[BLE_BUFF_MAX_LEN - 4 - 3];

extern uint8_t ble_mac[6];




app_drv_fifo_t app_uart_tx_fifo;
app_drv_fifo_t app_uart_rx_fifo;

//interupt uart rx flag ,clear at main loop
bool uart_rx_flag = false;

//for interrupt rx blcak hole ,when uart rx fifo full
uint8_t for_uart_rx_black_hole = 0;

//fifo length less that MTU-3, retry times
uint32_t uart_to_ble_send_evt_cnt = 0;

/*********************************************************************
 * EXTERNAL VARIABLES
 */

/*********************************************************************
 * EXTERNAL FUNCTIONS
 */

/*********************************************************************
 * LOCAL VARIABLES
 */
//

//The tx buffer and rx buffer for app_drv_fifo
//length should be a power of 2
static uint8_t app_uart_tx_buffer[APP_UART_TX_BUFFER_LENGTH] = {0};
static uint8_t app_uart_rx_buffer[APP_UART_RX_BUFFER_LENGTH] = {0};


/*********************************************************************
 * LOCAL FUNCTIONS
 */

/*********************************************************************
 * PROFILE CALLBACKS
 */

/*********************************************************************
 * PUBLIC FUNCTIONS
 */

/*********************************************************************
 * @fn      app_uart_process
 *
 * @brief   process uart data
 *
 * @return  NULL
 */
void app_uart_process(void)
{
    UINT32 irq_status;
    SYS_DisableAllIrq(&irq_status);
    if(uart_rx_flag)
    {
     //   tmos_start_task(Peripheral_TaskID, UART_TO_BLE_SEND_EVT, 2);
     //   uart_rx_flag = false;
    }
    SYS_RecoverIrq(irq_status);

    //tx process
    if(R8_UART3_TFC < UART_FIFO_SIZE)
    {
       // app_drv_fifo_read_to_same_addr(&app_uart_tx_fifo, (uint8_t *)&R8_UART3_THR, UART_FIFO_SIZE - R8_UART3_TFC);
    }

   // Enable_notify(peripheralConnList.connHandle, ENABLE);


   // extern uint8 Enable_notify(uint16 Connection_handle,uint8 Enable);









}

/*********************************************************************
 * @fn      app_uart_init
 *
 * @brief   init uart
 *
 * @return  NULL
 */
void app_uart_init()
{
    //tx fifo and tx fifo
    //The buffer length should be a power of 2
    app_drv_fifo_init(&app_uart_tx_fifo, app_uart_tx_buffer, APP_UART_TX_BUFFER_LENGTH);
    app_drv_fifo_init(&app_uart_rx_fifo, app_uart_rx_buffer, APP_UART_RX_BUFFER_LENGTH);

    //uart tx io
 //   GPIOA_SetBits(bTXD3);
 //   GPIOA_ModeCfg(bTXD3, GPIO_ModeOut_PP_5mA);

    //uart rx io
 //   GPIOA_SetBits(bRXD3);
 //   GPIOA_ModeCfg(bRXD3, GPIO_ModeIN_PU);

    //uart3 init
 //   UART3_DefInit();

    //enable interupt
   // UART3_INTCfg(ENABLE, RB_IER_RECV_RDY | RB_IER_LINE_STAT);
   // PFIC_EnableIRQ(UART3_IRQn);



}

/*********************************************************************
 * @fn      app_uart_tx_data
 *
 * @brief   app_uart_tx_data
 *
 * @return  NULL
 */
void app_uart_tx_data(uint8_t *data, uint16_t length)
{
    uint16_t write_length = length;
    app_drv_fifo_write(&app_uart_tx_fifo, data, &write_length);
}

/*********************************************************************
 * @fn      UART3_IRQHandler
 *
 * @brief   Not every uart reception will end with a UART_II_RECV_TOUT
 *          UART_II_RECV_TOUT can only be triggered when R8_UARTx_RFC is not 0
 *          Here we cannot rely UART_II_RECV_TOUT as the end of a uart reception
 *
 * @return  NULL
 */
__INTERRUPT
__HIGH_CODE
void UART3_IRQHandler(void)
{
    uint16_t error;
    switch(UART3_GetITFlag())
    {
        case UART_II_LINE_STAT:
            UART3_GetLinSTA();
            break;

        case UART_II_RECV_RDY:
        case UART_II_RECV_TOUT:
            error = app_drv_fifo_write_from_same_addr(&app_uart_rx_fifo, (uint8_t *)&R8_UART3_RBR, R8_UART3_RFC);
            if(error != APP_DRV_FIFO_RESULT_SUCCESS)
            {
                for(uint8_t i = 0; i < R8_UART3_RFC; i++)
                {
                    //fifo full,put to fifo black hole
                    for_uart_rx_black_hole = R8_UART3_RBR;
                }
            }
            uart_rx_flag = true;
            break;

        case UART_II_THR_EMPTY:
            break;
        case UART_II_MODEM_CHG:
            break;
        default:
            break;
    }
}

/*********************************************************************
 * @fn      on_bleuartServiceEvt
 *
 * @brief   ble uart service callback handler
 *
 * @return  NULL
 */
void on_bleuartServiceEvt(uint16_t connection_handle, ble_uart_evt_t *p_evt)
{
    switch(p_evt->type)
    {
        case BLE_UART_EVT_TX_NOTI_DISABLED:
            PRINT("%02x:bleuart_EVT_TX_NOTI_DISABLED\r\n", connection_handle);
            break;
        case BLE_UART_EVT_TX_NOTI_ENABLED:
            PRINT("%02x:bleuart_EVT_TX_NOTI_ENABLED\r\n", connection_handle);
            break;
        case BLE_UART_EVT_BLE_DATA_RECIEVED:
          //  PRINT("BLE RX DATA len:%d\r\n", p_evt->data.length);

            // ����اߧ� �է�ҧѧӧڧ�� �ӧ�ӧ�� ���է֧�اڧާ�ԧ� ����ҧ�֧ߧڧ�
            for (int i = 0; i < p_evt->data.length; i++) {
           //  PRINT("Data byte %d: 0x%02X\r\n", i, p_evt->data.p_data[i]);
               PRINT("Data byte %d: %d\n", i, p_evt->data.p_data[i]);

              // FOR_BUFER=p_evt->data.p_data[i];


              }


            //BLE_NEW_DATA =1;// �ާԧߧ�ӧ֧ߧߧ�� ���ӧ֧� ��ҧ�ѧ�ߧ� �ߧ� ��֧ݧ���



            busy_transmit =1;// �ܧѧ� ���ݧ�ܧ� �էѧߧߧ��  ���ڧݧ֧�֧ݧ� �� ��֧ݧ֧��ߧ� �ڧէ֧� �٧ѧէ֧�اܧ�  1 - 2 ��֧ܧ�ߧէ� �էݧ� �ӧ���֧�ߧ�ԧ� �����ܧ�  ��ѧܧ�ԧ� �ܧѧ� ���ߧ�ӧ�� ��ҧߧ�ӧݧ֧ߧڧ�
            //��֧ާ�֧�ѧ����
            busy_transmit_delay =1;// �ܧڧէ�ӧѧ֧� �ߧ� 1 ���֧��ڧ�  �٧ѧէ֧�اܧ� ����ݧ� �٧ѧߧ������ ���� �ҧ� �ߧ� �ҧ�ݧ�  �������������� ������������������ �������� �� ��ݧ��ѧ� �ߧ� �����ݧ� �����֧է�է���
           // ���ߧ�ӧѧ� �ӧ���֧�ѧߧѧ� ��֧�֧ѧէ�� ��֧ާ�֧֧�ѧ���� ��֧ܧ��֧� �ߧ� ��֧ݧ֧��� ��էߧ�ӧ�ާ֧ߧߧ�!!! (�� ��.��ѧܧ� 3 if( busy_transmit_delay>3)  )



             temp_whole_set = p_evt->data.p_data[0];// ���֧ݧѧ� ��ѧ��� ��֧ާ�֧�ѧ���� (�ܧ�ѧ�ߧѧ� �֧էڧߧڧ�ѧ�)
             temp_half_set =  p_evt->data.p_data[1];// ����ݧ�ӧڧߧܧ� �ԧ�ѧէ��� (5 �ڧݧ� 0)




             setup_temp = combine_temperature_set(temp_whole_set,temp_half_set);//���֧�ҧ�ѧ٧�ӧ�ӧѧ֧� �� ����ާѧ� �էݧ� ��֧�ާ���ѧ��


             app_drv_fifo_flush(&app_uart_rx_fifo);

             screen_refresh_flag=1; // �ӧ���ѧӧݧ�֧� ��ݧѧ� �����ߧ�� ����ڧ��ӧܧ� �ߧ�ӧ�ԧ� �ާ֧ߧ� ���� �ӧ��է�  ��ҧ�ѧҧ���ڧ� ��ܧѧߧڧ�ӧ�ѧߧڧ� ������������

             FLASH_UPDATE =1; // �էѧ֧� ��ѧ٧�֧�֧ߧڧ֧ߧ� ��ҧӧݧ֧ߧڧ� ��է֧�� �� ��ݧ֧է���֧� ��ڧܧݧ�  ���������� == 1 ��֧� , �� ������ ��ݧѧ� ��ҧ�ѧ��ӧѧ֧��� ��ѧ�



      /*
            //for notify back test
            //to ble
            uint16_t to_write_length = p_evt->data.length;
            app_drv_fifo_write(&app_uart_rx_fifo, (uint8_t *)p_evt->data.p_data, &to_write_length);
            tmos_start_task(Peripheral_TaskID, UART_TO_BLE_SEND_EVT, 2);
            //end of nofify back test

            //ble to uart
            app_uart_tx_data((uint8_t *)p_evt->data.p_data, p_evt->data.length);

        */


        //    app_drv_fifo_flush(&app_uart_rx_fifo);

          //   BLE_NEW_DATA=1;// ���������� �էѧߧߧ�� �� ��֧ݧ֧��ߧ� ������������������


/*

            if( NEW_DATA_FROM_PHONE==1)
                        {
                            NEW_DATA_FROM_PHONE=0;//�ܧڧէ�ӧѧ֧� ��ݧѧ� ���ڧߧ���� �էѧߧߧ�� �� �اէ֧� ��ݧ֧է��ڧ� ��֧�֧� �ߧ�ӧ�� ��ڧܧ�

                            //�������������������� ������������ �������������� ���� �������������� ������ ������������������ ������������ ���������������� �� ����������������
                                     //������������������ ���������������������� EVICE ID


                            //  GAPRole_GetParameter(GAPROLE_BD_ADDR, ble_mac);


                                              //   to_test_buffer42[0] = FOR_BUFER;  // ���ѧ�ڧ��ӧѧ֧� �٧ߧѧ�֧ߧڧ� �� ��֧�ӧ�� �ҧѧۧ�
                                               //  to_test_buffer42[1] = ble_mac[5];
                                               //  to_test_buffer42[2] = ble_mac[4];
                                               //  to_test_buffer42[3] = ble_mac[3];
                                               //  to_test_buffer42[4] = ble_mac[2];
                                               //  to_test_buffer42[5] = ble_mac[1];
                                               //  to_test_buffer42[6] = ble_mac[0];
                                                // to_test_buffer42[7] = 0x22;

                                                 // //ble_mac[5], ble_mac[4], ble_mac[3], ble_mac[2], ble_mac[1], ble_mac[0]);

                                                           //  FOR_BUFER++;// ���֧��ڧ� ��ҧߧ�ӧݧ֧ߧڧ�  ���� �ܧѧاէ�� �ߧѧاѧ�ڧ�


                                                  //         to_test_buffer42[0] = 0;  //   ���ѧ��ڧ� �ҧѧ� - �էݧ� �ҧ�ݧ��ڧ� �٧ߧѧ�֧ߧڧ� ,�ҧ�ݧ֧� 255
                                                  //         to_test_buffer42[1] = FOR_BUFER; //���ѧ�ڧ��ӧѧ֧� �٧ߧѧ�֧ߧڧ� �� �ާѧݧѧէ�ڧ� �ߧ�ݧ֧ӧ�� �ҧѧۧ� - ���� �էݧڧߧ֧� ���ݧ֧٧ߧ�� �էѧߧߧ�� 256 �ҧѧۧ�
                                                  //         to_test_buffer42[2] = 0;
                                                  //         to_test_buffer42[3] = 5; // �էݧڧߧߧ� ��ѧܧ֧�� (6 �ҧѧۧ�) �� �ҧѧۧ�ѧ� �ߧѧ�ڧߧѧ� �� �ߧ�ݧ֧ӧ�ԧ� �ڧߧէ֧ܧ��
                                                  //         to_test_buffer42[4] = 0x88;// �էѧߧߧ��..
                                                  //         to_test_buffer42[5] = 0x99;// �էѧߧߧ��.
                                                  //         to_test_buffer42[6] = 0x11;// �էѧߧߧ��.
                                                  //         to_test_buffer42[7] = 0x22;// �էѧߧߧ��.
                                                  //         to_test_buffer42[8] = 0x33;// �էѧߧߧ��.
                                                  //         to_test_buffer42[9] = 0x44;// �էѧߧߧ��.

                                                  //         to_test_buffer42[10] = 0x55; // ����ݧ֧էߧڧ� �էӧ� �ҧѧۧ�� �� ��ӧ����  �٧ѧ�֧٧֧�ӧڧ��ӧѧߧ� ���� ����ӧ֧���ߧ�� ���ާާ� �ڧ��
                                                  //         to_test_buffer42[11] = 0xAA; // ���� �٧ߧѧ֧�ߧڧ� ��� ��ާ�ݧ�ѧߧڧ� - ���� ��ѧܧ֧� �٧ѧܧ�ߧ�֧�  0x55 + 0xAA



                                                           //����������: ��֧��1)  �ާѧ��ڧ� �ڧ���է��ڧ�  ��ҧ�֧� �էݧڧߧߧ��  12 �ҧѧۧ�

                                                           //�է�ݧا֧� �ҧ��� �ܧ��֧ܧ�ߧ� ���ڧߧ�� �ҧ֧� ���ڧҧ�� ���� ������ߧߧ�� ��ҧߧ�ӧݧ֧ߧڧ� �� �ާ�էڧ�ڧܧѧ�ڧ� �էѧߧߧ��

                                                           //  FOR_BUFER2++;

                                                           //  to_test_buffer42[0] =FOR_BUFER2;  //   ���ѧ��ڧ� �ҧѧ� - �էݧ� �ҧ�ݧ��ڧ� �٧ߧѧ�֧ߧڧ� ,�ҧ�ݧ֧� 255
                                                             to_test_buffer42[0] =FOR_BUFER;  //   ���ѧ��ڧ� �ҧѧ� - �էݧ� �ҧ�ݧ��ڧ� �٧ߧѧ�֧ߧڧ� ,�ҧ�ݧ֧� 255
                                                             to_test_buffer42[1] = 1; //���ѧ�ڧ��ӧѧ֧� �٧ߧѧ�֧ߧڧ� �� �ާѧݧѧէ�ڧ� �ߧ�ݧ֧ӧ�� �ҧѧۧ� - ���� �էݧڧߧ֧� ���ݧ֧٧ߧ�� �էѧߧߧ�� 256 �ҧѧۧ�
                                                             to_test_buffer42[2] = 2;
                                                             to_test_buffer42[3] = 3; // �էݧڧߧߧ� ��ѧܧ֧�� (6 �ҧѧۧ�) �� �ҧѧۧ�ѧ� �ߧѧ�ڧߧѧ� �� �ߧ�ݧ֧ӧ�ԧ� �ڧߧէ֧ܧ��
                                                             to_test_buffer42[4] = 4;// �էѧߧߧ��..
                                                             to_test_buffer42[5] = 5;// �էѧߧߧ��.
                                                             to_test_buffer42[6] = 6;// �էѧߧߧ��.
                                                             to_test_buffer42[7] = 7;// �էѧߧߧ��.
                                                             to_test_buffer42[8] = 8;// �էѧߧߧ��.
                                                             to_test_buffer42[9] = 9;// �էѧߧߧ��.

                                                             to_test_buffer42[10] = 10; // ����ݧ֧էߧڧ� �էӧ� �ҧѧۧ�� �� ��ӧ����  �٧ѧ�֧٧֧�ӧڧ��ӧѧߧ� ���� ����ӧ֧���ߧ�� ���ާާ� �ڧ��
                                                             to_test_buffer42[11] = 11; // ���� �٧ߧѧ֧�ߧڧ� ��� ��ާ�ݧ�ѧߧڧ� - ���� ��ѧܧ֧� �٧ѧܧ�ߧ�֧�  0x55 + 0xAA

                                                             to_test_buffer42[12] = 12; // ����ݧ֧էߧڧ� �էӧ� �ҧѧۧ�� �� ��ӧ����  �٧ѧ�֧٧֧�ӧڧ��ӧѧߧ� ���� ����ӧ֧���ߧ�� ���ާާ� �ڧ��
                                                             to_test_buffer42[13] = 13; // ���� �٧ߧѧ֧�ߧڧ� ��� ��ާ�ݧ�ѧߧڧ� - ���� ��ѧܧ֧� �٧ѧܧ�ߧ�֧�  0x55 + 0xAA

                                                             to_test_buffer42[14] = 14; // ����ݧ֧էߧڧ� �էӧ� �ҧѧۧ�� �� ��ӧ����  �٧ѧ�֧٧֧�ӧڧ��ӧѧߧ� ���� ����ӧ֧���ߧ�� ���ާާ� �ڧ��
                                                             to_test_buffer42[15] = 15; // ���� �٧ߧѧ֧�ߧڧ� ��� ��ާ�ݧ�ѧߧڧ� - ���� ��ѧܧ֧� �٧ѧܧ�ߧ�֧�  0x55 + 0xAA


                                                             //��ݧ֧٧ߧ�� �էѧߧߧ֧�� �ܧ�ѧ�ߧ� 14 ��.�� 14/28 �ڧ��.. ���� �ާѧ��ڧ� �ڧߧڧ�ڧѧݧڧ٧ڧ��ӧѧ�� �ߧ� +2 �֧էڧߧڧ��



                                                 // ����ݧ��ѧ֧� MAC-�ѧէ�֧� BLE
                                            //     uint8_t ble_mac[6];
                                              //   GAPRole_GetParameter(GAPROLE_BD_ADDR, ble_mac);

                                                 // �����ѧӧݧ�֧� MAC-�ѧէ�֧� �ߧѧ�ڧߧѧ� �� ���֧��֧ԧ� �ҧѧۧ�� (�ڧߧէ֧ܧ� 2)
                                               //  for (int8 i = 0; i < 6; i++)
                                               //  {
                                                     //to_test_buffer42[i + 2] = ble_mac[5 - i];  // ���ѧ�ڧ��ӧѧ֧� �� ��ҧ�ѧ�ߧ�� �����էܧ� �էݧ� ���ѧߧէѧ��ߧ�ԧ� ����ާѧ�� MAC
                                                   //  to_test_buffer42[i + 1] = ble_mac[5 - i];  // ���ѧ�ڧ��ӧѧ֧� �� ��ҧ�ѧ�ߧ�� �����էܧ� �էݧ� ���ѧߧէѧ��ߧ�ԧ� ����ާѧ�� MAC
                                               //  }

                                                 // ����ݧѧէ��ߧ�� �ӧ�ӧ��
                                                // printf("BLE Device ID: %02X:%02X:%02X:%02X:%02X:%02X\n",
                                                 //ble_mac[5], ble_mac[4], ble_mac[3], ble_mac[2], ble_mac[1], ble_mac[0]);


                                           //    app_drv_fifo_flush(&app_uart_rx_fifo);

                                              Enable_notify(peripheralConnList.connHandle, ENABLE);
                                              read_length = to_test__b_4_size-0;// �էݧڧߧߧ� �էѧߧߧ�� �ڧ� �ާѧ��ڧӧ� ��֧���ӧ�ԧ� to_test_buffer2 ="Privet moy drug"
                                              //read_length = to_test__b_4_size;// �էݧڧߧߧ� �էѧߧߧ�� �ڧ� �ާѧ��ڧӧ� ��֧���ӧ�ԧ� to_test_buffer2 ="Privet moy drug"
                                              app_drv_fifo_write(&app_uart_rx_fifo, (uint8_t *)&to_test_buffer42, &read_length);

                                              //app_drv_fifo_write(&app_uart_tx_fifo, (uint8_t *)&to_test_buffer42, &read_length);

                                              tmos_start_task(Peripheral_TaskID, UART_TO_BLE_SEND_EVT, 2);


                        }

*/



            break;
        default:
            break;
    }
}

/*********************************************************************
*********************************************************************/
