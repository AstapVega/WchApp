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

#define to_test__b_4_size  20 // §â§Ñ§Ù§Þ§Ö§â §Þ§Ñ§ã§ã§Ú§Ó§Ñ §ä§Ö§ã§ä§à§Ó§à§Ô§à to_test_buffer2

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

            // §¯§å§Ø§ß§à §Õ§à§Ò§Ñ§Ó§Ú§ä§î §Ó§í§Ó§à§Õ §ã§à§Õ§Ö§â§Ø§Ú§Þ§à§Ô§à §ã§à§à§Ò§ë§Ö§ß§Ú§ñ
            for (int i = 0; i < p_evt->data.length; i++) {
           //  PRINT("Data byte %d: 0x%02X\r\n", i, p_evt->data.p_data[i]);
               PRINT("Data byte %d: %d\n", i, p_evt->data.p_data[i]);

              // FOR_BUFER=p_evt->data.p_data[i];


              }


            //BLE_NEW_DATA =1;// §Þ§Ô§ß§à§Ó§Ö§ß§ß§í§Û §à§ä§Ó§Ö§ä §à§Ò§â§Ñ§ä§ß§à §ß§Ñ §ä§Ö§Ý§æ§à§ß



            busy_transmit =1;// §Ü§Ñ§Ü §ä§à§Ý§î§Ü§à §Õ§Ñ§ß§ß§í§Ö  §á§â§Ú§Ý§Ö§ä§Ö§Ý§Ú §ã §ä§Ö§Ý§Ö§æ§à§ß§Ñ §Ú§Õ§Ö§ä §Ù§Ñ§Õ§Ö§â§Ø§Ü§Ñ  1 - 2 §ã§Ö§Ü§å§ß§Õ§í §Õ§Ý§ñ §Ó§ã§ä§â§Ö§é§ß§à§Ô§à §á§à§ä§à§Ü§Ñ  §ä§Ñ§Ü§à§Ô§à §Ü§Ñ§Ü §æ§à§ß§à§Ó§à§Ö §à§Ò§ß§à§Ó§Ý§Ö§ß§Ú§Ö
            //§ä§Ö§Þ§á§Ö§â§Ñ§ä§å§â§í
            busy_transmit_delay =1;// §Ü§Ú§Õ§í§Ó§Ñ§Ö§Þ §ß§Ñ 1 §ã§é§Ö§ä§é§Ú§Ü  §Ù§Ñ§Õ§Ö§â§Ø§Ü§Ú §á§à§ã§Ý§Ö §Ù§Ñ§ß§ñ§ä§à§ã§ä§Ú §é§ä§à §Ò§í §ß§Ö §Ò§í§Ý§à  §®§²§´§°§£§¤§° §°§¯§µ§­§¦§£§°§¤§° §°§¬§¯§¡ §Ú §ã§Ý§å§é§Ñ§Û §ß§Ö §á§â§à§ê§Ý§Ñ §á§â§à§è§Ö§Õ§å§Õ§å§â§Ñ
           // §æ§à§ß§à§Ó§Ñ§ñ §Ó§ã§ä§â§Ö§é§Ñ§ß§Ñ§ñ §á§Ö§â§Ö§Ñ§Õ§é§Ú §ä§Ö§Þ§á§Ö§Ö§â§Ñ§ä§å§â§í §ä§Ö§Ü§å§ë§Ö§Û §ß§Ñ §ä§Ö§Ý§Ö§æ§à§ß §à§Õ§ß§à§Ó§â§Þ§Ö§ß§ß§à!!! (§ã §Þ.§ä§Ñ§Ü§ã 3 if( busy_transmit_delay>3)  )



             temp_whole_set = p_evt->data.p_data[0];// §¸§Ö§Ý§Ñ§ñ §é§Ñ§ã§ä§î §ä§Ö§Þ§á§Ö§â§Ñ§ä§å§â§í (§Ü§â§Ñ§ä§ß§Ñ§ñ §Ö§Õ§Ú§ß§Ú§è§Ñ§Þ)
             temp_half_set =  p_evt->data.p_data[1];// §±§à§Ý§à§Ó§Ú§ß§Ü§Ñ §Ô§â§Ñ§Õ§å§ã§Ñ (5 §Ú§Ý§Ú 0)




             setup_temp = combine_temperature_set(temp_whole_set,temp_half_set);//§á§â§Ö§à§Ò§â§Ñ§Ù§à§Ó§í§Ó§Ñ§Ö§Þ §Ó §æ§à§â§Þ§Ñ§ä §Õ§Ý§ñ §ä§Ö§â§Þ§à§ã§ä§Ñ§ä§Ñ


             app_drv_fifo_flush(&app_uart_rx_fifo);

             screen_refresh_flag=1; // §Ó§í§ã§ä§Ñ§Ó§Ý§ñ§Ö§Þ §æ§Ý§Ñ§Ô §ã§â§à§é§ß§à§Û §à§ä§â§Ú§ã§à§Ó§Ü§Ú §ß§à§Ó§à§Ô§à §Þ§Ö§ß§ð §á§â§Ú §Ó§ç§à§Õ§Ö  §à§Ò§â§Ñ§Ò§à§ä§é§Ú§Ü §ã§Ü§Ñ§ß§Ú§â§Ó§à§Ñ§ß§Ú§ñ §¬§¯§°§±§°§¬

             FLASH_UPDATE =1; // §Õ§Ñ§Ö§Þ §â§Ñ§Ù§â§Ö§ê§Ö§ß§Ú§Ö§ß§Ñ §à§Ò§Ó§Ý§Ö§ß§Ú§Ö §æ§Õ§Ö§ê§Ñ §Ó §ã§Ý§Ö§Õ§å§ð§ë§Ö§Þ §è§Ú§Ü§Ý§Ö  §´§¡§³§¬§¡ == 1 §ã§Ö§Ü , §Ú §á§à§ä§à§Þ §æ§Ý§Ñ§Ô §ã§Ò§â§Ñ§ã§í§Ó§Ñ§Ö§ä§ã§ñ §ã§Ñ§Þ



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

          //   BLE_NEW_DATA=1;// §¯§°§£§½§¦ §Õ§Ñ§ß§ß§í§Ö §ã §ä§Ö§Ý§Ö§æ§à§ß§Ñ §±§²§ª§­§¦§´§¦§­§ª


/*

            if( NEW_DATA_FROM_PHONE==1)
                        {
                            NEW_DATA_FROM_PHONE=0;//§Ü§Ú§Õ§í§Ó§Ñ§Ö§Þ §æ§Ý§Ñ§Ô §á§â§Ú§ß§ñ§ä§í§ç §Õ§Ñ§ß§ß§í§ç §Ú §Ø§Õ§Ö§Þ §ã§Ý§Ö§Õ§å§ë§Ú§ç §é§Ö§â§Ö§Ù §ß§à§Ó§í§Û §è§Ú§Ü§Ý

                            //§°§¢§¯§°§£§­§¦§¯§ª§¦ §¥§¡§¯§¯§½§· §°§¢§²§¡§´§¯§° §¯§¡ §´§¦§­§¦§¶§°§¯ §±§²§ª §±§°§­§µ§¹§¦§¯§ª§ª §¥§¡§¯§¯§½§· §±§²§ª§¯§Á§´§½§· §³ §´§¦§­§¦§¶§°§¯§¡
                                     //§¥§°§¢§¡§£§­§Á§¦§® §¬§°§¯§´§²§°§­§¾§¯§½§« EVICE ID


                            //  GAPRole_GetParameter(GAPROLE_BD_ADDR, ble_mac);


                                              //   to_test_buffer42[0] = FOR_BUFER;  // §©§Ñ§á§Ú§ã§í§Ó§Ñ§Ö§Þ §Ù§ß§Ñ§é§Ö§ß§Ú§Ö §Ó §á§Ö§â§Ó§í§Û §Ò§Ñ§Û§ä
                                               //  to_test_buffer42[1] = ble_mac[5];
                                               //  to_test_buffer42[2] = ble_mac[4];
                                               //  to_test_buffer42[3] = ble_mac[3];
                                               //  to_test_buffer42[4] = ble_mac[2];
                                               //  to_test_buffer42[5] = ble_mac[1];
                                               //  to_test_buffer42[6] = ble_mac[0];
                                                // to_test_buffer42[7] = 0x22;

                                                 // //ble_mac[5], ble_mac[4], ble_mac[3], ble_mac[2], ble_mac[1], ble_mac[0]);

                                                           //  FOR_BUFER++;// §ã§é§Ö§ä§é§Ú§Ü §à§Ò§ß§à§Ó§Ý§Ö§ß§Ú§ñ  §á§â§Ú §Ü§Ñ§Ø§Õ§à§Þ §ß§Ñ§Ø§Ñ§ä§Ú§Ú


                                                  //         to_test_buffer42[0] = 0;  //   §ã§ä§Ñ§â§ê§Ú§Û §Ò§Ñ§Û - §Õ§Ý§ñ §Ò§à§Ý§î§ê§Ú§ç §Ù§ß§Ñ§é§Ö§ß§Ú§Û ,§Ò§à§Ý§Ö§Ö 255
                                                  //         to_test_buffer42[1] = FOR_BUFER; //§©§Ñ§á§Ú§ã§í§Ó§Ñ§Ö§Þ §Ù§ß§Ñ§é§Ö§ß§Ú§Ö §Ó §Þ§Ñ§Ý§Ñ§Õ§ê§Ú§Û §ß§å§Ý§Ö§Ó§à§Û §Ò§Ñ§Û§ä - §á§â§Ú §Õ§Ý§Ú§ß§Ö§Ö §á§à§Ý§Ö§Ù§ß§í§ç §Õ§Ñ§ß§ß§í§ç 256 §Ò§Ñ§Û§ä
                                                  //         to_test_buffer42[2] = 0;
                                                  //         to_test_buffer42[3] = 5; // §Õ§Ý§Ú§ß§ß§Ñ §á§Ñ§Ü§Ö§ä§Ñ (6 §Ò§Ñ§Û§ä) §Ó §Ò§Ñ§Û§ä§Ñ§ç §ß§Ñ§é§Ú§ß§Ñ§ñ §ã §ß§å§Ý§Ö§Ó§à§Ô§à §Ú§ß§Õ§Ö§Ü§ã§Ñ
                                                  //         to_test_buffer42[4] = 0x88;// §Õ§Ñ§ß§ß§í§Ö..
                                                  //         to_test_buffer42[5] = 0x99;// §Õ§Ñ§ß§ß§í§Ö.
                                                  //         to_test_buffer42[6] = 0x11;// §Õ§Ñ§ß§ß§í§Ö.
                                                  //         to_test_buffer42[7] = 0x22;// §Õ§Ñ§ß§ß§í§Ö.
                                                  //         to_test_buffer42[8] = 0x33;// §Õ§Ñ§ß§ß§í§Ö.
                                                  //         to_test_buffer42[9] = 0x44;// §Õ§Ñ§ß§ß§í§Ö.

                                                  //         to_test_buffer42[10] = 0x55; // §á§à§ã§Ý§Ö§Õ§ß§Ú§Ö §Õ§Ó§Ñ §Ò§Ñ§Û§ä§Ö §Ó §ç§Ó§à§ã§ä§Ö  §Ù§Ñ§â§Ö§Ù§Ö§â§Ó§Ú§â§à§Ó§Ñ§ß§í §á§à§Õ §á§â§à§Ó§Ö§â§à§é§ß§å§ð §ã§å§Þ§Þ§å §Ú§ä§Õ
                                                  //         to_test_buffer42[11] = 0xAA; // §ï§ä§à §Ù§ß§Ñ§Ö§é§ß§Ú§ñ §á§à §å§Þ§à§Ý§é§Ñ§ß§Ú§ð - §é§ä§à §á§Ñ§Ü§Ö§ä §Ù§Ñ§Ü§à§ß§é§Ö§ß  0x55 + 0xAA



                                                           //§ª§´§°§¤§°: §ä§Ö§ã§ä1)  §Þ§Ñ§ã§ã§Ú§Ó §Ú§ã§ç§à§Õ§ñ§ë§Ú§Û  §à§Ò§ë§Ö§Û §Õ§Ý§Ú§ß§ß§à§Û  12 §Ò§Ñ§Û§ä

                                                           //§Õ§à§Ý§Ø§Ö§ß §Ò§í§ä§î §Ü§à§â§Ö§Ü§ä§ß§à §á§â§Ú§ß§ñ§ä §Ò§Ö§Ù §à§ê§Ú§Ò§à§Ü §á§â§Ú §á§à§ã§ä§à§ß§ß§à§Þ §à§Ò§ß§à§Ó§Ý§Ö§ß§Ú§Ú §Ú §Þ§à§Õ§Ú§æ§Ú§Ü§Ñ§è§Ú§Ú §Õ§Ñ§ß§ß§í§ç

                                                           //  FOR_BUFER2++;

                                                           //  to_test_buffer42[0] =FOR_BUFER2;  //   §ã§ä§Ñ§â§ê§Ú§Û §Ò§Ñ§Û - §Õ§Ý§ñ §Ò§à§Ý§î§ê§Ú§ç §Ù§ß§Ñ§é§Ö§ß§Ú§Û ,§Ò§à§Ý§Ö§Ö 255
                                                             to_test_buffer42[0] =FOR_BUFER;  //   §ã§ä§Ñ§â§ê§Ú§Û §Ò§Ñ§Û - §Õ§Ý§ñ §Ò§à§Ý§î§ê§Ú§ç §Ù§ß§Ñ§é§Ö§ß§Ú§Û ,§Ò§à§Ý§Ö§Ö 255
                                                             to_test_buffer42[1] = 1; //§©§Ñ§á§Ú§ã§í§Ó§Ñ§Ö§Þ §Ù§ß§Ñ§é§Ö§ß§Ú§Ö §Ó §Þ§Ñ§Ý§Ñ§Õ§ê§Ú§Û §ß§å§Ý§Ö§Ó§à§Û §Ò§Ñ§Û§ä - §á§â§Ú §Õ§Ý§Ú§ß§Ö§Ö §á§à§Ý§Ö§Ù§ß§í§ç §Õ§Ñ§ß§ß§í§ç 256 §Ò§Ñ§Û§ä
                                                             to_test_buffer42[2] = 2;
                                                             to_test_buffer42[3] = 3; // §Õ§Ý§Ú§ß§ß§Ñ §á§Ñ§Ü§Ö§ä§Ñ (6 §Ò§Ñ§Û§ä) §Ó §Ò§Ñ§Û§ä§Ñ§ç §ß§Ñ§é§Ú§ß§Ñ§ñ §ã §ß§å§Ý§Ö§Ó§à§Ô§à §Ú§ß§Õ§Ö§Ü§ã§Ñ
                                                             to_test_buffer42[4] = 4;// §Õ§Ñ§ß§ß§í§Ö..
                                                             to_test_buffer42[5] = 5;// §Õ§Ñ§ß§ß§í§Ö.
                                                             to_test_buffer42[6] = 6;// §Õ§Ñ§ß§ß§í§Ö.
                                                             to_test_buffer42[7] = 7;// §Õ§Ñ§ß§ß§í§Ö.
                                                             to_test_buffer42[8] = 8;// §Õ§Ñ§ß§ß§í§Ö.
                                                             to_test_buffer42[9] = 9;// §Õ§Ñ§ß§ß§í§Ö.

                                                             to_test_buffer42[10] = 10; // §á§à§ã§Ý§Ö§Õ§ß§Ú§Ö §Õ§Ó§Ñ §Ò§Ñ§Û§ä§Ö §Ó §ç§Ó§à§ã§ä§Ö  §Ù§Ñ§â§Ö§Ù§Ö§â§Ó§Ú§â§à§Ó§Ñ§ß§í §á§à§Õ §á§â§à§Ó§Ö§â§à§é§ß§å§ð §ã§å§Þ§Þ§å §Ú§ä§Õ
                                                             to_test_buffer42[11] = 11; // §ï§ä§à §Ù§ß§Ñ§Ö§é§ß§Ú§ñ §á§à §å§Þ§à§Ý§é§Ñ§ß§Ú§ð - §é§ä§à §á§Ñ§Ü§Ö§ä §Ù§Ñ§Ü§à§ß§é§Ö§ß  0x55 + 0xAA

                                                             to_test_buffer42[12] = 12; // §á§à§ã§Ý§Ö§Õ§ß§Ú§Ö §Õ§Ó§Ñ §Ò§Ñ§Û§ä§Ö §Ó §ç§Ó§à§ã§ä§Ö  §Ù§Ñ§â§Ö§Ù§Ö§â§Ó§Ú§â§à§Ó§Ñ§ß§í §á§à§Õ §á§â§à§Ó§Ö§â§à§é§ß§å§ð §ã§å§Þ§Þ§å §Ú§ä§Õ
                                                             to_test_buffer42[13] = 13; // §ï§ä§à §Ù§ß§Ñ§Ö§é§ß§Ú§ñ §á§à §å§Þ§à§Ý§é§Ñ§ß§Ú§ð - §é§ä§à §á§Ñ§Ü§Ö§ä §Ù§Ñ§Ü§à§ß§é§Ö§ß  0x55 + 0xAA

                                                             to_test_buffer42[14] = 14; // §á§à§ã§Ý§Ö§Õ§ß§Ú§Ö §Õ§Ó§Ñ §Ò§Ñ§Û§ä§Ö §Ó §ç§Ó§à§ã§ä§Ö  §Ù§Ñ§â§Ö§Ù§Ö§â§Ó§Ú§â§à§Ó§Ñ§ß§í §á§à§Õ §á§â§à§Ó§Ö§â§à§é§ß§å§ð §ã§å§Þ§Þ§å §Ú§ä§Õ
                                                             to_test_buffer42[15] = 15; // §ï§ä§à §Ù§ß§Ñ§Ö§é§ß§Ú§ñ §á§à §å§Þ§à§Ý§é§Ñ§ß§Ú§ð - §é§ä§à §á§Ñ§Ü§Ö§ä §Ù§Ñ§Ü§à§ß§é§Ö§ß  0x55 + 0xAA


                                                             //§à§Ý§Ö§Ù§ß§í§Ö §Õ§Ñ§ß§ß§Ö§í§Ö §Ü§â§Ñ§ä§ß§à 14 §ä.§Ö 14/28 §Ú§ä§Õ.. §¯§à §Þ§Ñ§ã§ã§Ú§Ó §Ú§ß§Ú§è§Ú§Ñ§Ý§Ú§Ù§Ú§â§à§Ó§Ñ§ä§î §ß§Ñ +2 §Ö§Õ§Ú§ß§Ú§è§í



                                                 // §±§à§Ý§å§é§Ñ§Ö§Þ MAC-§Ñ§Õ§â§Ö§ã BLE
                                            //     uint8_t ble_mac[6];
                                              //   GAPRole_GetParameter(GAPROLE_BD_ADDR, ble_mac);

                                                 // §£§ã§ä§Ñ§Ó§Ý§ñ§Ö§Þ MAC-§Ñ§Õ§â§Ö§ã §ß§Ñ§é§Ú§ß§Ñ§ñ §ã §ä§â§Ö§ä§î§Ö§Ô§à §Ò§Ñ§Û§ä§Ñ (§Ú§ß§Õ§Ö§Ü§ã 2)
                                               //  for (int8 i = 0; i < 6; i++)
                                               //  {
                                                     //to_test_buffer42[i + 2] = ble_mac[5 - i];  // §©§Ñ§á§Ú§ã§í§Ó§Ñ§Ö§Þ §Ó §à§Ò§â§Ñ§ä§ß§à§Þ §á§à§â§ñ§Õ§Ü§Ö §Õ§Ý§ñ §ã§ä§Ñ§ß§Õ§Ñ§â§ä§ß§à§Ô§à §æ§à§â§Þ§Ñ§ä§Ñ MAC
                                                   //  to_test_buffer42[i + 1] = ble_mac[5 - i];  // §©§Ñ§á§Ú§ã§í§Ó§Ñ§Ö§Þ §Ó §à§Ò§â§Ñ§ä§ß§à§Þ §á§à§â§ñ§Õ§Ü§Ö §Õ§Ý§ñ §ã§ä§Ñ§ß§Õ§Ñ§â§ä§ß§à§Ô§à §æ§à§â§Þ§Ñ§ä§Ñ MAC
                                               //  }

                                                 // §°§ä§Ý§Ñ§Õ§à§é§ß§í§Û §Ó§í§Ó§à§Õ
                                                // printf("BLE Device ID: %02X:%02X:%02X:%02X:%02X:%02X\n",
                                                 //ble_mac[5], ble_mac[4], ble_mac[3], ble_mac[2], ble_mac[1], ble_mac[0]);


                                           //    app_drv_fifo_flush(&app_uart_rx_fifo);

                                              Enable_notify(peripheralConnList.connHandle, ENABLE);
                                              read_length = to_test__b_4_size-0;// §Õ§Ý§Ú§ß§ß§Ñ §Õ§Ñ§ß§ß§í§ç §Ú§Ù §Þ§Ñ§ã§ã§Ú§Ó§Ñ §ä§Ö§ã§ä§à§Ó§à§Ô§à to_test_buffer2 ="Privet moy drug"
                                              //read_length = to_test__b_4_size;// §Õ§Ý§Ú§ß§ß§Ñ §Õ§Ñ§ß§ß§í§ç §Ú§Ù §Þ§Ñ§ã§ã§Ú§Ó§Ñ §ä§Ö§ã§ä§à§Ó§à§Ô§à to_test_buffer2 ="Privet moy drug"
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
