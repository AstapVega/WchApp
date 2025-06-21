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
#include "ble_uart_service.h"
#include "app_drv_fifo.h"
#include "app_uart.h"


#include <math.h>
#include "CONFIG.h"
#include "devinfoservice.h"
#include "gattprofile.h"
#include "peripheral.h"
#include "ble_uart_service.h"
#include "app_drv_fifo.h"

#include "my_assist32.h"
// файл с префиксом ext  - расширения для внешнего перехода/связи основного Си файла и моих библиотек

#include "main_vlad.h"
#include "menu_vlad.h"
#include "my_large_LCD32.h"
#include "ext_my_directtest.h"
#include "my_test.h"
#include "lcd_test.h"
#include "PM_test.h"
#include "HAL.h"
#include "my_FLASH.h"
#include "alex_board.h"

#include "hlw8110.h"

#include "CH58x_common.h"


// все файлы Си моих библиотек для работы термостата , для сязки в структуре проета, буду связывать через основной header
//и header с приставкой ext , где будут дублироаться обьявленные переменные, константы , структуры и функции как ext !




 void  Sleep_Start_Test(void);
 extern void  Sleep_Start_Test(void);
 void    Sleep_Start_Time_Write(void);
 extern void    Sleep_Start_Time_Write(void);
 void hard_faile_reset(uint8 faill);
 extern void hard_faile_reset(uint8 faill);
 void Test_Start_Boot(void);
 extern void Test_Start_Boot(void);
 void Start_Boot_for_Schedule(void);
 extern void Start_Boot_for_Schedule(void);
 void Start_Boot_for_System(void);
 extern void Start_Boot_for_System(void);
 void Start_Boot_for_Set_Temper(void);
 extern  void Start_Boot_for_Set_Temper(void);


 uint8_t debug_out_tik;

 extern uint8 flag;

 #define event_sleep_START                                10  // для события SLEEP

// uint8  START=0;// флаг инициализации прохождения начального загрузчика при подачи питания Start_Boot
// extern uint8  START;

 uint8 ble_reset=0;// флаг активации сброса RESET
 extern uint8 ble_reset;//

//#define RTC_TRIGFunCfg_Time_Valie                         32768*60*60 // время СНА в сек  по функции ТРИГЕРА
 #define RTC_TRIGFunCfg_Time_Valie                         32768*5 // время СНА в сек  по функции ТРИГЕРА
 uint32 RTC_TRIGFunCfg_Time=RTC_TRIGFunCfg_Time_Valie;

 uint8 SleepStop=2;

 int8 pEVT=1;

 uint16_t read_length = 0;

 uint8 EEPROM_ARRAY_Counter=0;
 extern uint8 EEPROM_ARRAY_Counter;


//------------------------------------------- FOR TIME FLASH WRITE TEST --------------------------------------------------//
 unsigned short TIME_ARRAY[12];
 extern unsigned short TIME_ARRAY[12];

 unsigned short Time_Write=0;
 extern unsigned short Time_Write;





#define   sub_event_1   0x01
#define   sub_event_2   0x02
#define   sub_event_3   0x04
#define   sub_event_4   0x08
#define   sub_event_5   0x10
#define   sub_event_6   0x40
#define   sub_event_7   0x80
#define   sub_event_8   0x100
#define   sub_event_9   0x200
#define   sub_event_10   0x400
#define   sub_event_11   0x800
#define   sub_event_12   0x1000
#define   sub_event_13   0x2000
#define   sub_event_14   0x4000



 //int8 BLE_NEW_DATA;




extern int   event_RTC1;
#define to_test__b_2_size  80 // размер массива тестового to_test_buffer2
#define to_test__b_3_size  80 // размер массива тестового to_test_buffer2
//#define to_test__b_4_size  4 // размер массива тестового to_test_buffer2
#define to_test__b_4_size  16// размер массива тестового to_test_buffer2

uint16_t read_length;// отладка для контрольного считывания тестового буфера

const uint8_t to_test_buffer2[to_test__b_2_size] =  " START:Thermostat_test_22/1 /Thermostat_test_22/2 /Thermostat_test_22/3 /:END ";
const uint8_t to_test_buffer3[to_test__b_3_size] =  " START:Thermostat_test_33/1 /Thermostat_test_33/2 /Thermostat_test_33/3 /:END ";
//const uint8_t to_test_buffer4[to_test__b_4_size] =  "ST";


uint8_t FOR_BUFER;
uint8_t FOR_BUFER2;



uint8_t to_test_buffer42[to_test__b_4_size];


uint8_t to_test_buffer4[to_test__b_4_size];
uint8_t previous_FOR_BUFER = 0;  // Глобальная переменная для отслеживания изменений


//uint8_t ble_mac[6];

uint8_t ble_mac[6] = {0x50, 0x54, 0x7b, 0x74, 0xb8, 0xbb};//50 54 7b 74 b8 bb



/*********************************************************************
 * MACROS
 */

/*********************************************************************
 * CONSTANTS
 */

// How often to perform periodic event
#define SBP_PERIODIC_EVT_PERIOD              1600

// How often to perform read rssi event
#define SBP_READ_RSSI_EVT_PERIOD             3200

// Parameter update delay
#define SBP_PARAM_UPDATE_DELAY               6400

// What is the advertising interval when device is discoverable (units of 625us, 80=50ms)
//#define DEFAULT_ADVERTISING_INTERVAL         160

//#define DEFAULT_ADVERTISING_INTERVAL         32

#define DEFAULT_ADVERTISING_INTERVAL         40


// Limited discoverable mode advertises for 30.72s, and then stops
// General discoverable mode advertises indefinitely
#define DEFAULT_DISCOVERABLE_MODE            GAP_ADTYPE_FLAGS_GENERAL

// Minimum connection interval (units of 1.25ms, 10=12.5ms)
#define DEFAULT_DESIRED_MIN_CONN_INTERVAL    8

// Maximum connection interval (units of 1.25ms, 100=125ms)
#define DEFAULT_DESIRED_MAX_CONN_INTERVAL    20

// Slave latency to use parameter update
#define DEFAULT_DESIRED_SLAVE_LATENCY        0

// Supervision timeout value (units of 10ms, 100=1s)
#define DEFAULT_DESIRED_CONN_TIMEOUT         100

// Company Identifier: WCH
#define WCH_COMPANY_ID                       0x07D7

/*********************************************************************
 * TYPEDEFS
 */

/*********************************************************************
 * GLOBAL VARIABLES
 */

uint8_t Peripheral_TaskID = INVALID_TASK_ID; // Task ID for internal task/event processing

/*********************************************************************
 * EXTERNAL VARIABLES
 */

/*********************************************************************
 * EXTERNAL FUNCTIONS
 */

/*********************************************************************
 * LOCAL VARIABLES
 */

//for send to ble
typedef enum
{
    SEND_TO_BLE_TO_SEND = 1,
    SEND_TO_BLE_ALLOC_FAILED,
    SEND_TO_BLE_SEND_FAILED,
} send_to_ble_state_t;
send_to_ble_state_t send_to_ble_state = SEND_TO_BLE_TO_SEND;

blePaControlConfig_t pa_lna_ctl;

//static uint8 Peripheral_TaskID = INVALID_TASK_ID;   // Task ID for internal task/event processing

// GAP - SCAN RSP data (max size = 31 bytes)
static uint8 scanRspData[] = {
    // complete name
    19, // length of this data
    GAP_ADTYPE_LOCAL_NAME_COMPLETE,
   // 'c', 'h', '5', '8', '3', '_', 'b', 'l', 'e', '_', 'u', 'a', 'r', 't',

    'V', 'E', 'G', 'A', '-', 'L', 'T', 'C', ' ', '0', '7', '0', ' ', ':',' ', 'B', 'L', 'E',


    //static uint8 attDeviceName[GAP_DEVICE_NAME_LEN] = "VEGA-HIJ 030 : BLE";



    // connection interval range
    0x05, // length of this data
    GAP_ADTYPE_SLAVE_CONN_INTERVAL_RANGE,
    LO_UINT16(DEFAULT_DESIRED_MIN_CONN_INTERVAL), // 100ms
    HI_UINT16(DEFAULT_DESIRED_MIN_CONN_INTERVAL),
    LO_UINT16(DEFAULT_DESIRED_MAX_CONN_INTERVAL), // 1s
    HI_UINT16(DEFAULT_DESIRED_MAX_CONN_INTERVAL),

    // Tx power level
    0x02, // length of this data
    GAP_ADTYPE_POWER_LEVEL,
    5 // 0dBm
};

// GAP - Advertisement data (max size = 31 bytes, though this is
// best kept short to conserve power while advertisting)
static uint8 advertData[] = {
    // Flags; this sets the device to use limited discoverable
    // mode (advertises for 30 seconds at a time) instead of general
    // discoverable mode (advertises indefinitely)
    0x02, // length of this data
    GAP_ADTYPE_FLAGS,
    DEFAULT_DISCOVERABLE_MODE | GAP_ADTYPE_FLAGS_BREDR_NOT_SUPPORTED,

    // service UUID, to notify central devices what services are included
    // in this peripheral
    0x03,                  // length of this data
    GAP_ADTYPE_16BIT_MORE, // some of the UUID's, but not all
    LO_UINT16(SIMPLEPROFILE_SERV_UUID),
    HI_UINT16(SIMPLEPROFILE_SERV_UUID)};

// GAP GATT Attributes
//static uint8 attDeviceName[GAP_DEVICE_NAME_LEN] = "ch583_ble_uart";

static uint8 attDeviceName[GAP_DEVICE_NAME_LEN] = "VEGA-LTC 070 : BLE";

// Connection item list
static peripheralConnItem_t peripheralConnList;

/*********************************************************************
 * LOCAL FUNCTIONS
 */
static void Peripheral_ProcessTMOSMsg(tmos_event_hdr_t *pMsg);
static void peripheralStateNotificationCB(gapRole_States_t newState, gapRoleEvent_t *pEvent);

static void peripheralParamUpdateCB(uint16 connHandle, uint16 connInterval,
                                    uint16 connSlaveLatency, uint16 connTimeout);
static void peripheralInitConnItem(peripheralConnItem_t *peripheralConnList);
static void peripheralRssiCB(uint16 connHandle, int8 rssi);

extern uint8 Enable_notify(uint16 Connection_handle,uint8 Enable);





//#define   sleep_test_by_RTC_TRIGFunCfg
#define   sleep_test_by_Power_ON_OFF_PIN

// Connection item list
static peripheralConnItem_t peripheralConnList;





/*********************************************************************
 * PROFILE CALLBACKS
 */

// GAP Role Callbacks
static gapRolesCBs_t Peripheral_PeripheralCBs = {
    peripheralStateNotificationCB, // Profile State Change Callbacks
    peripheralRssiCB,              // When a valid RSSI is read from controller (not used by application)
    peripheralParamUpdateCB};

// Broadcast Callbacks
static gapRolesBroadcasterCBs_t Broadcaster_BroadcasterCBs = {
    NULL, // Not used in peripheral role
    NULL  // Receive scan request callback
};

// GAP Bond Manager Callbacks
static gapBondCBs_t Peripheral_BondMgrCBs = {
    NULL, // Passcode callback (not used by application)
    NULL  // Pairing / Bonding state Callback (not used by application)
};

/*********************************************************************
 * PUBLIC FUNCTIONS
 */

/*********************************************************************
 * @fn      Peripheral_Init
 *
 * @brief   Initialization function for the Peripheral App Task.
 *          This is called during initialization and should contain
 *          any application specific initialization (ie. hardware
 *          initialization/setup, table initialization, power up
 *          notificaiton ... ).
 *
 * @param   task_id - the ID assigned by TMOS.  This ID should be
 *                    used to send messages and set timers.
 *
 * @return  none
 */
void Peripheral_Init()
{
    Peripheral_TaskID = TMOS_ProcessEventRegister(Peripheral_ProcessEvent);

    // Setup the GAP Peripheral Role Profile

    {

        Enable_notify(peripheralConnList.connHandle, ENABLE);


        uint8  initial_advertising_enable = TRUE;
        uint16 desired_min_interval = 6;
        uint16 desired_max_interval = 1000;

        // Set the GAP Role Parameters
        GAPRole_SetParameter(GAPROLE_ADVERT_ENABLED, sizeof(uint8), &initial_advertising_enable);
        GAPRole_SetParameter(GAPROLE_SCAN_RSP_DATA, sizeof(scanRspData), scanRspData);
        GAPRole_SetParameter(GAPROLE_ADVERT_DATA, sizeof(advertData), advertData);
        GAPRole_SetParameter(GAPROLE_MIN_CONN_INTERVAL, sizeof(uint16), &desired_min_interval);
        GAPRole_SetParameter(GAPROLE_MAX_CONN_INTERVAL, sizeof(uint16), &desired_max_interval);
    }

    // Set advertising interval
    {
        uint16 advInt = DEFAULT_ADVERTISING_INTERVAL;

        GAP_SetParamValue(TGAP_DISC_ADV_INT_MIN, advInt);
        GAP_SetParamValue(TGAP_DISC_ADV_INT_MAX, advInt);
    }

    // Setup the GAP Bond Manager
    {
        uint32 passkey = 0; // passkey "000000"
        uint8  pairMode = GAPBOND_PAIRING_MODE_WAIT_FOR_REQ;
        uint8  mitm = TRUE;
        uint8  bonding = TRUE;
        uint8  ioCap = GAPBOND_IO_CAP_DISPLAY_ONLY;
        GAPBondMgr_SetParameter(GAPBOND_PERI_DEFAULT_PASSCODE, sizeof(uint32), &passkey);
        GAPBondMgr_SetParameter(GAPBOND_PERI_PAIRING_MODE, sizeof(uint8), &pairMode);
        GAPBondMgr_SetParameter(GAPBOND_PERI_MITM_PROTECTION, sizeof(uint8), &mitm);
        GAPBondMgr_SetParameter(GAPBOND_PERI_IO_CAPABILITIES, sizeof(uint8), &ioCap);
        GAPBondMgr_SetParameter(GAPBOND_PERI_BONDING_ENABLED, sizeof(uint8), &bonding);
    }

    // Initialize GATT attributes
    GGS_AddService(GATT_ALL_SERVICES);         // GAP
    GATTServApp_AddService(GATT_ALL_SERVICES); // GATT attributes
    DevInfo_AddService();                      // Device Information Service


// ВОТ СДЕСЬ ВСТАВЬ ВЫВОД ID  BLE девайса!!



    // --- Здесь добавляем вывод BLE ID ---
  //      uint8_t ble_mac[6];
   //     GAPRole_GetParameter(GAPROLE_BD_ADDR, ble_mac); // Получаем MAC-адрес BLE

   //     printf("BLE Device ID: %02X:%02X:%02X:%02X:%02X:%02X\n",
    //           ble_mac[5], ble_mac[4], ble_mac[3], ble_mac[2], ble_mac[1], ble_mac[0]);
        // --------------------------------------








    ble_uart_add_service(on_bleuartServiceEvt);

    // Set the GAP Characteristics
    GGS_SetParameter(GGS_DEVICE_NAME_ATT, sizeof(attDeviceName), attDeviceName);

    // Init Connection Item
    peripheralInitConnItem(&peripheralConnList);

    // Register receive scan request callback
    GAPRole_BroadcasterSetCB(&Broadcaster_BroadcasterCBs);

    // Setup a delayed profile startup
    tmos_set_event(Peripheral_TaskID, SBP_START_DEVICE_EVT);
}

/*********************************************************************
 * @fn      peripheralInitConnItem
 *
 * @brief   Init Connection Item
 *
 * @param   peripheralConnList -
 *
 * @return  NULL
 */
static void peripheralInitConnItem(peripheralConnItem_t *peripheralConnList)
{
    peripheralConnList->connHandle = GAP_CONNHANDLE_INIT;
    peripheralConnList->connInterval = 0;
    peripheralConnList->connSlaveLatency = 0;
    peripheralConnList->connTimeout = 0;
}

uint32_t get_fattime(void)
{
    return 0;
}

/*********************************************************************
 * @fn      Peripheral_ProcessEvent
 *
 * @brief   Peripheral Application Task event processor.  This function
 *          is called to process all events for the task.  Events
 *          include timers, messages and any other user defined events.
 *
 * @param   task_id - The TMOS assigned task ID.
 * @param   events - events to process.  This is a bit map and can
 *                   contain more than one event.
 *
 * @return  events not processed
 */
uint16 Peripheral_ProcessEvent(uint8 task_id, uint16 events)
{
    static attHandleValueNoti_t noti;
    //  VOID task_id; // TMOS required parameter that isn't used in this function




    if(events & SYS_EVENT_MSG)
    {
        uint8 *pMsg;

        if((pMsg = tmos_msg_receive(Peripheral_TaskID)) != NULL)
        {
            Peripheral_ProcessTMOSMsg((tmos_event_hdr_t *)pMsg);
            // Release the TMOS message
            tmos_msg_deallocate(pMsg);
        }
        // return unprocessed events
        return (events ^ SYS_EVENT_MSG);
    }

    if(events & SBP_START_DEVICE_EVT)
    {
        // Start the Device
        GAPRole_PeripheralStartDevice(Peripheral_TaskID, &Peripheral_BondMgrCBs, &Peripheral_PeripheralCBs);
        return (events ^ SBP_START_DEVICE_EVT);
    }
    if(events & SBP_PARAM_UPDATE_EVT)
    {
        // Send connect param update request
        GAPRole_PeripheralConnParamUpdateReq(peripheralConnList.connHandle,
                                             DEFAULT_DESIRED_MIN_CONN_INTERVAL,
                                             DEFAULT_DESIRED_MAX_CONN_INTERVAL,
                                             DEFAULT_DESIRED_SLAVE_LATENCY,
                                             DEFAULT_DESIRED_CONN_TIMEOUT,
                                             Peripheral_TaskID);

        //        GAPRole_PeripheralConnParamUpdateReq( peripheralConnList.connHandle,
        //                                              10,
        //                                              20,
        //                                              0,
        //                                              400,
        //                                              Peripheral_TaskID);

        return (events ^ SBP_PARAM_UPDATE_EVT);
    }

    if(events & UART_TO_BLE_SEND_EVT)
    {
        static uint16_t read_length = 0;
        ;
        uint8_t result = 0xff;
        switch(send_to_ble_state)
        {
            case SEND_TO_BLE_TO_SEND:

                //notify is not enabled
                if(!ble_uart_notify_is_ready(peripheralConnList.connHandle))
                {
                    if(peripheralConnList.connHandle == GAP_CONNHANDLE_INIT)
                    {
                        //connection lost, flush rx fifo here
                        app_drv_fifo_flush(&app_uart_rx_fifo);
                    }
                    break;
                }
                read_length = ATT_GetMTU(peripheralConnList.connHandle) - 3;

                if(app_drv_fifo_length(&app_uart_rx_fifo) >= read_length)
                {
                    PRINT("FIFO_LEN:%d\r\n", app_drv_fifo_length(&app_uart_rx_fifo));
                    result = app_drv_fifo_read(&app_uart_rx_fifo, to_test_buffer, &read_length);
                    uart_to_ble_send_evt_cnt = 0;
                }
                else
                {
                    if(uart_to_ble_send_evt_cnt > 10)
                    {
                        result = app_drv_fifo_read(&app_uart_rx_fifo, to_test_buffer, &read_length);
                        uart_to_ble_send_evt_cnt = 0;
                    }
                    else
                    {
                        tmos_start_task(Peripheral_TaskID, UART_TO_BLE_SEND_EVT, 4);
                        uart_to_ble_send_evt_cnt++;


                    //    PRINT("NO TIME OUT\r\n");  //часто притет при передачи БЛЕ - но показывает жив или мертв


                    }
                }

                if(APP_DRV_FIFO_RESULT_SUCCESS == result)
                {
                    noti.len = read_length;
                    noti.pValue = GATT_bm_alloc(peripheralConnList.connHandle, ATT_HANDLE_VALUE_NOTI, noti.len, NULL, 0);
                    if(noti.pValue != NULL)
                    {
                        tmos_memcpy(noti.pValue, to_test_buffer, noti.len);
                        result = ble_uart_notify(peripheralConnList.connHandle, &noti, 0);
                        if(result != SUCCESS)
                        {
                            PRINT("R1:%02x\r\n", result);
                            send_to_ble_state = SEND_TO_BLE_SEND_FAILED;
                            GATT_bm_free((gattMsg_t *)&noti, ATT_HANDLE_VALUE_NOTI);
                            tmos_start_task(Peripheral_TaskID, UART_TO_BLE_SEND_EVT, 2);
                        }
                        else
                        {
                            send_to_ble_state = SEND_TO_BLE_TO_SEND;
                            //app_fifo_write(&app_uart_tx_fifo,to_test_buffer,&read_length);
                            //app_drv_fifo_write(&app_uart_tx_fifo,to_test_buffer,&read_length);
                            read_length = 0;
                            tmos_start_task(Peripheral_TaskID, UART_TO_BLE_SEND_EVT, 2);
                        }
                    }
                    else
                    {
                        send_to_ble_state = SEND_TO_BLE_ALLOC_FAILED;
                        tmos_start_task(Peripheral_TaskID, UART_TO_BLE_SEND_EVT, 2);
                    }
                }
                else
                {
                    //send_to_ble_state = SEND_TO_BLE_FIFO_EMPTY;
                }
                break;
            case SEND_TO_BLE_ALLOC_FAILED:
            case SEND_TO_BLE_SEND_FAILED:

                noti.len = read_length;
                noti.pValue = GATT_bm_alloc(peripheralConnList.connHandle, ATT_HANDLE_VALUE_NOTI, noti.len, NULL, 0);
                if(noti.pValue != NULL)
                {
                    tmos_memcpy(noti.pValue, to_test_buffer, noti.len);
                    result = ble_uart_notify(peripheralConnList.connHandle, &noti, 0);
                    if(result != SUCCESS)
                    {
                        PRINT("R2:%02x\r\n", result);
                        send_to_ble_state = SEND_TO_BLE_SEND_FAILED;
                        GATT_bm_free((gattMsg_t *)&noti, ATT_HANDLE_VALUE_NOTI);
                        tmos_start_task(Peripheral_TaskID, UART_TO_BLE_SEND_EVT, 2);
                    }
                    else
                    {
                        send_to_ble_state = SEND_TO_BLE_TO_SEND;
                        //app_drv_fifo_write(&app_uart_tx_fifo,to_test_buffer,&read_length);
                        read_length = 0;
                        tmos_start_task(Peripheral_TaskID, UART_TO_BLE_SEND_EVT, 2);
                    }
                }
                else
                {
                    send_to_ble_state = SEND_TO_BLE_ALLOC_FAILED;
                    tmos_start_task(Peripheral_TaskID, UART_TO_BLE_SEND_EVT, 2);
                }
                break;
            default:
                break;
        }
        return (events ^ UART_TO_BLE_SEND_EVT);
    }
    // Discard unknown events
    return 0;
}

/*********************************************************************
 * @fn      Peripheral_ProcessTMOSMsg
 *
 * @brief   Process an incoming task message.
 *
 * @param   pMsg - message to process
 *
 * @return  none
 */
static void Peripheral_ProcessTMOSMsg(tmos_event_hdr_t *pMsg)
{
    switch(pMsg->event)
    {
        default:
            break;
    }
}

/*********************************************************************
 * @fn      Peripheral_LinkEstablished
 *
 * @brief   Process link established.
 *
 * @param   pEvent - event to process
 *
 * @return  none
 */
static void Peripheral_LinkEstablished(gapRoleEvent_t *pEvent)
{
    gapEstLinkReqEvent_t *event = (gapEstLinkReqEvent_t *)pEvent;

    // See if already connected
    if(peripheralConnList.connHandle != GAP_CONNHANDLE_INIT)
    {
        GAPRole_TerminateLink(pEvent->linkCmpl.connectionHandle);
        PRINT("Connection max...\n");
    }
    else
    {
        peripheralConnList.connHandle = event->connectionHandle;
        peripheralConnList.connInterval = event->connInterval;
        peripheralConnList.connSlaveLatency = event->connLatency;
        peripheralConnList.connTimeout = event->connTimeout;

        // Set timer for param update event
        tmos_start_task(Peripheral_TaskID, SBP_PARAM_UPDATE_EVT, SBP_PARAM_UPDATE_DELAY);

        PRINT("Conn %x - Int %x \n", event->connectionHandle, event->connInterval);
    }
}

/*********************************************************************
 * @fn      Peripheral_LinkTerminated
 *
 * @brief   Process link terminated.
 *
 * @param   pEvent - event to process
 *
 * @return  none
 */
static void Peripheral_LinkTerminated(gapRoleEvent_t *pEvent)
{
    gapTerminateLinkEvent_t *event = (gapTerminateLinkEvent_t *)pEvent;

    if(event->connectionHandle == peripheralConnList.connHandle)
    {
        peripheralConnList.connHandle = GAP_CONNHANDLE_INIT;
        peripheralConnList.connInterval = 0;
        peripheralConnList.connSlaveLatency = 0;
        peripheralConnList.connTimeout = 0;

        // Restart advertising
        {
            uint8 advertising_enable = TRUE;
            GAPRole_SetParameter(GAPROLE_ADVERT_ENABLED, sizeof(uint8), &advertising_enable);
        }
    }
    else
    {
        PRINT("ERR..\n");
    }
}

/*********************************************************************
 * @fn      peripheralRssiCB
 *
 * @brief   RSSI callback.
 *
 * @param   connHandle - connection handle
 * @param   rssi - RSSI
 *
 * @return  none
 */
static void peripheralRssiCB(uint16 connHandle, int8 rssi)
{
    PRINT("RSSI -%d dB Conn  %x \n", -rssi, connHandle);
}

/*********************************************************************
 * @fn      peripheralParamUpdateCB
 *
 * @brief   Parameter update complete callback
 *
 * @param   connHandle - connect handle
 *          connInterval - connect interval
 *          connSlaveLatency - connect slave latency
 *          connTimeout - connect timeout
 *
 * @return  none
 */
static void peripheralParamUpdateCB(uint16 connHandle, uint16 connInterval,
                                    uint16 connSlaveLatency, uint16 connTimeout)
{
    if(connHandle == peripheralConnList.connHandle)
    {
        peripheralConnList.connInterval = connInterval;
        peripheralConnList.connSlaveLatency = connSlaveLatency;
        peripheralConnList.connTimeout = connTimeout;

        PRINT("Update %x - Int %x \n", connHandle, connInterval);
    }
    else
    {
        PRINT("peripheralParamUpdateCB err..\n");
    }
}

/*********************************************************************
 * @fn      peripheralStateNotificationCB
 *
 * @brief   Notification from the profile of a state change.
 *
 * @param   newState - new state
 *
 * @return  none
 */
static void peripheralStateNotificationCB(gapRole_States_t newState, gapRoleEvent_t *pEvent)
{
    switch(newState & GAPROLE_STATE_ADV_MASK)
    {
        case GAPROLE_STARTED:
            PRINT("Initialized..\n");
            break;

        case GAPROLE_ADVERTISING:
            if(pEvent->gap.opcode == GAP_LINK_TERMINATED_EVENT)
            {
                Peripheral_LinkTerminated(pEvent);
            }
            PRINT("Advertising..\n");
            break;

        case GAPROLE_CONNECTED:
            if(pEvent->gap.opcode == GAP_LINK_ESTABLISHED_EVENT)
            {
                Peripheral_LinkEstablished(pEvent);
                PRINT("Connected..\n");

                // точко обновления флага " isConnected "
                  isConnected = true; // Соединение  = Disconnected




            }
            break;

        case GAPROLE_CONNECTED_ADV:
            PRINT("Connected Advertising..\n");
            break;

        case GAPROLE_WAITING:
            if(pEvent->gap.opcode == GAP_END_DISCOVERABLE_DONE_EVENT)
            {
                PRINT("Waiting for advertising..\n");
            }
            else if(pEvent->gap.opcode == GAP_LINK_TERMINATED_EVENT)
            {
                Peripheral_LinkTerminated(pEvent);
                PRINT("Disconnected.. Reason:%x\n", pEvent->linkTerminate.reason);


               // точко обновления флага " isConnected "
                isConnected = false; // Соединение  = Disconnected



            }
            else if(pEvent->gap.opcode == GAP_LINK_ESTABLISHED_EVENT)
            {
                if(pEvent->gap.hdr.status != SUCCESS)
                {
                    PRINT("Waiting for advertising..\n");
                }
                else
                {
                    PRINT("Error..\n");
                }
            }
            else
            {
                PRINT("Error..%x\n", pEvent->gap.opcode);
            }
            break;

        case GAPROLE_ERROR:
            PRINT("Error..\n");
            break;

        default:
            break;
    }
}

/*********************************************************************
*********************************************************************/




int   event_RTC1;

extern int   event_RTC1;

static tmosTaskID task11;





tmosEvents Task11_ProcessEvent( tmosTaskID task_id, tmosEvents events )
{

  // ВНИМАНИЕ: ВЫВОД ОТЛАДОЧНОЙ ИНФОРМАЦИИ В РЕЖИМЕ РЕЗИЛ УБИРАТЬ!!. так как это влияет на работу LCD
  // при загрузке процессами!!!

  int * msgPtr;



  if( events & sub_event_1 )
  {






      //---------------------------------  передача данных в BLE по обновленнном входящему ссобш=щению------------------------------------------------------//

   //   NEW_DATA_FROM_PHONE=1;

     // checkAndSetFlag();// как только поменялось знаечние температуры Tout то выставляется флаг  BLE_NEW_DATA =1; и передаются данные

   //    BLE_NEW_DATA=0;


      if( BLE_NEW_DATA==1)
              {

          BLE_NEW_DATA=0;//кидываем флаг принятых данных и ждем следущих через новый цикл

           //температуры


          RTC_GetTime( &py,&pmon,&pd,&ph,&pm,& ps);
          UnixTime = GetUnixTime();
          ConvertUnixTimeToBytes( UnixTime);

          to_test_buffer42[4] =  UnixByte0;  // 1/4 UnixTime  при каждом отслыке данных на телфон , что приложение принимало новый пакет
          to_test_buffer42[5] =  UnixByte1;  // 1/4 UnixTime  при каждом отслыке данных на телфон , что приложение принимало новый пакет
          to_test_buffer42[6] =  UnixByte2;  // 1/4 UnixTime  при каждом отслыке данных на телфон , что приложение принимало новый пакет
          to_test_buffer42[7] =  UnixByte3;  // 1/4 UnixTime при каждом отслыке данных на телфон , что приложение принимало новый пакет


       //   FOR_BUFER++;// счетчик обновления пакета  при каждом отслыке данных на телфон

          convert_temperature_set(setup_temp);// обратное преобразование от термомостата для телефона температура задачния  младший байт и старший
          to_test_buffer42[0] =temp_whole_set;  //   температура задания первый байт
          to_test_buffer42[1] =temp_half_set;  //   температура задания второй байт




        //  Tout_for_phone =convertToTemperatureInt(Tout);
        //  convert_temperature(Tout_for_phone);// обратное преобразование  промежуточное
        //  to_test_buffer42[2] =temp_whole;  //   температура текущая первый байт
        //  to_test_buffer42[3] =temp_half;  //   температура текущая второй байт







                                       // Получаем MAC-адрес BLE
                                  //     uint8_t ble_mac[6];
                                    //   GAPRole_GetParameter(GAPROLE_BD_ADDR, ble_mac);

                                       // Вставляем MAC-адрес начиная с третьего байта (индекс 2)
                                    //   for (int8 i = 0; i < 6; i++)
                                       //{
                                           //to_test_buffer42[i + 2] = ble_mac[5 - i];  // Записываем в обратном порядке для стандартного формата MAC
                                      //     to_test_buffer42[i + 1] = ble_mac[5 - i];  // Записываем в обратном порядке для стандартного формата MAC
                                      // }

                                       // Отладочный вывод
                                      // printf("BLE Device ID: %02X:%02X:%02X:%02X:%02X:%02X\n",
                                       //ble_mac[5], ble_mac[4], ble_mac[3], ble_mac[2], ble_mac[1], ble_mac[0]);


                                    app_drv_fifo_flush(&app_uart_rx_fifo);

                                    Enable_notify(peripheralConnList.connHandle, ENABLE);
                                    read_length = to_test__b_4_size-0;// длинна данных из массива тестового to_test_buffer2 ="Privet moy drug"
                                    //read_length = to_test__b_4_size;// длинна данных из массива тестового to_test_buffer2 ="Privet moy drug"
                                    app_drv_fifo_write(&app_uart_rx_fifo, (uint8_t *)&to_test_buffer42, &read_length);

                                    //app_drv_fifo_write(&app_uart_tx_fifo, (uint8_t *)&to_test_buffer42, &read_length);

                                    tmos_start_task(Peripheral_TaskID, UART_TO_BLE_SEND_EVT, 2);

              }





         tmos_start_task( task11 , sub_event_1 ,1.6*1.0*25 ); // 625mks*1.6*1*200 = 0.2 sek  период запуска task1/sub_event_1
    // tmos_start_task( task11 , sub_event_1 ,1.6*1.0*100 ); // 625mks*1.6*1*200 = 0.2 sek  период запуска task1/sub_event_1
    // tmos_start_task( task11 , sub_event_1 ,1.6*1.0*1000 ); // 625mks*1.6*1*1000 = 1 sek  период запуска task1/sub_event_1


    return events ^ sub_event_1;

  }
  //-------------------------------------------------------------------------------------------------//



  return 0;

}


void TEST_Init2()
{



   task11 = TMOS_ProcessEventRegister(Task11_ProcessEvent);


   tmos_set_event(task11, sub_event_1); // инициализируем  период и запуск задачи  task1/sub_event_1 и  стартуем



}




//-----------------------------ТЕРМО КОД ---------------------------------------------------



static tmosTaskID task1;
static tmosTaskID task2;
static tmosTaskID task3;




tmosEvents Task1_ProcessEvent( tmosTaskID task_id, tmosEvents events )
{

  // ВНИМАНИЕ: ВЫВОД ОТЛАДОЧНОЙ ИНФОРМАЦИИ В РЕЖИМЕ РЕЗИЛ УБИРАТЬ!!. так как это влияет на работу LCD
  // при загрузке процессами!!!

  int * msgPtr;
  uint16_t read_length = 0;// отладка для контрольного считывания тестового буфера
//  uint8_t SCi;

  if( events & sub_event_1 )
  {


     //WDT_clear =0;   // сброс  WDT раз в 2 секунды

      RTC_GetTime( &py,&pmon,&pd,&ph,&pm,& ps);// считываем фоново раз в 1 сек / значения

      tempere_out_formation();// усреднение и формирование выходного значения температуры!

      debug_out_tik= debug_out_tik+1;

    //  if((debug_out_tik>5)&(SCHEDULE_UPDATE==1))
        if(SCHEDULE_UPDATE==1)
      {
          debug_out_tik=0;


          GPIOB_SetBits(bTXD1);
          GPIOB_ModeCfg(bTXD1, GPIO_ModeOut_PP_5mA);


#define  DEBUG__for_Schedule

#ifndef  DEBUG__for_Schedule

          GPIOB_SetBits(bTXD1);
               GPIOB_ModeCfg(bTXD1, GPIO_ModeOut_PP_5mA);

               printf("--      \n");
               printf( "  tempere_setup_change =%ld \n" ,    tempere_setup_change);
               printf( "  curent_intr =%ld \n" ,   curent_intr);
               printf( "  curent_DAY =%ld \n" ,   what_day (py, pmon,pd ));
               printf( "  setup_temp =%ld \n" ,    shudle_setup_t);
               printf( "%d year %d month %d day %d hour %d minute %d second  \n" ,py,pmon,pd,ph,pm,ps);
               //выводим отладку на ТЕРМИНАЛ: дата: часы: минуты : номер дня недели: номер интервала: температура задания
               //вывод таблицы SHEDULE - для наглядного контроля

               printf("--      \n");
               printf("--      \n");

                for(SCi = 0; SCi < 126; SCi++)
                                      {
                PRINT("%hu ", SCHEDULE_RESERVE[SCi]);

                SCy=SCy+1;
                if(SCy==18)
                {
                SCy=0;
                printf("--      \n");
                printf("--      \n");
                }

                }

                PRINT("\n");
                printf("--      \n");

               GPIOB_ModeCfg(bTXD1, GPIO_ModeIN_PD);

#endif

      }
/*
         if(invert_temp_cikl==255){
             Tcur1=Tout;
            if(Tcur1!=Tcur2)
           {
           Tout = Tcur2;
           tempere_cange=1;     // произошло изменение
           }
         }
         else {
             Tcur2=Tout;
             if(Tcur2!=Tcur1)
              {
              Tout = Tcur2;
              tempere_cange=1;     // произошло изменение
              }
        }

      invert_temp_cikl= ~invert_temp_cikl;

*/









//------------------------------------- event_RTC 1sek -------------------------------------//

      #define  DEBUG_print_event_RTC
      #ifndef  DEBUG_print_event_RTC
            GPIOB_SetBits(bTXD1);
            GPIOB_ModeCfg(bTXD1, GPIO_ModeOut_PP_5mA);
      #endif


 //    #define  DEBUG_HLW8110

     #ifndef  DEBUG_HLW8110
      //---------------------------------- HLW8110 PART-----------------------------------------//
/*
            //event_RTC2=2;

            if((event_RTC2>5)&(BUSY_KEY2==0))
           // if(event_RTC2>5)
          // if(BUSY_KEY==0)// если клавиатура не занята - нет критических задач
            {
           event_RTC2=0;
           UART1_DefInit1();//9600 + паритет
           Init_HLW8110();
           Calculate_HLW8110_MeterData();
           UART1_DefInit2();//115200(800000)  без паритета
           printf("                     \n");
       // припаять параллельно UART1 - ноги от HLW
           //Judge_CheckSum_HLW8110_Calfactor_printf();//выводим на терминал и обнуляем флаги для printf
          // Calculate_HLW8110_MeterData_printf();//выводим на терминал и обнуляем флаги для printf
            }

            */
      //------------------------------ END OFF HLW8110 PART ------------------------------------//
     #endif


#ifndef  DEBUG_print_event_RTC
    printf("-- DEBUG_HLW8110     \n");
    DelayMs(5);// задержка для очистки мусора гипертерминала  перед  GPIOA_ModeCfg(bTXD1, GPIO_ModeIN_PD)
    GPIOB_ModeCfg(bTXD1, GPIO_ModeIN_PD);
    #endif

  //  GPIOB_ModeCfg(bTXD1, GPIO_ModeIN_PD);

             //  FLASH_UPDATE=0;

            if(( FLASH_UPDATE>0)&(BUSY_KEY3==0))
            //if( FLASH_UPDATE>0)
                   {
                   FLASH_UPDATE=0;
                   SET_TEMPER_TO_FLASH();
                   SYSTEM_TO_FLASH();
                 //  SCHEDULE_TO_FLASH();
                   }

            if(SCHEDULE_UPDATE==1)
            {
                SCHEDULE_UPDATE=0;
                SCHEDULE_TO_FLASH();
            }





//------------------------------------- END OFF event_RTC 1 sek -------------------------------------//

   #define  DEBUG_Task1_ProcessEvent

  #ifndef  DEBUG_Task1_ProcessEvent
            printf("--      \n");
           GPIOB_SetBits(bTXD1);
           GPIOB_ModeCfg(bTXD1, GPIO_ModeOut_PP_5mA);
  #endif

      screen_refresh_flag=1;// взвод флага  "обновление ОЗУ єкрана"
     // event_RTC_sleep++;// виртуальный таймер для RTC sleep ??
      event_RTC++;// виртуальный таймер для RTC
      event_RTC2++;// виртуальный таймер для RTC №2
      event_RTC3++;// виртуальный таймер для RTC №3
     // event_RTC4++;
      if(start_sfm_timer1==1)// виртуальный таймер для SFM
      {sfm_sek_active++;}
      if(start_lock_anime_timer==TRUE)// виртуальный таймер для LOC - динамической заставки при нажатии на кнопку в MAIN режиме
      {lock_anime_timer++;}
      if(lock_anime_timer>1)// если после нажатия кнопки в режиме LOC, прошло более чем Х сек - останавливаем таймер/заставки LOC
      {lock_anime_timer =0;
      start_lock_anime_timer = 0;
      }// делаем "разблокировку экрана"}



      if((main_screen_type!= main_screen_manual)!=(main_screen_type== main_screen_prog)!=(main_screen_type== main_screen_SFM))
        {
         // BUSY_KEY2=1;
         // event_RTC3=1;
        }

      if(BUSY_KEY2==1)
              {
          printf( "  BUSY_KEY2 =%ld \n" ,  BUSY_KEY2);
              }


        if((main_screen_type== main_screen_manual)||(main_screen_type== main_screen_prog)||
                                                    (main_screen_type== main_screen_SFM ) )
        {
      if((BUSY_KEY2==1)&(event_RTC3>6))

      {
       BUSY_KEY2=0;//сбрасываем перехваченый флаг занятости клавиатуры
          //происходит только при переходе в єтих 3х єкранах , иначе HL8110  -заблокировано
      }

      if(BUSY_KEY3>0)// обновление FLASH через 1 сек после отпускания кнопки в рабочих ЭКРАНАХ
         {
          BUSY_KEY3=0;
         }


        }

      if(event_RTC3>7)
      {
       event_RTC3=0;//сброс флага занятости кнопок через  event_RTC3==7 сек
      }

      if(event_RTC2>7)
      {
        event_RTC2=0;
      }





   // надо сохранять сигнатуру и перезагружаться: после "изменений" установки часов

      second_sep_invers=~second_sep_invers;// мигаем значком двоеточия в "часах"
      invers_clock_icon=~invers_clock_icon;// для мигания значка часы в ГЛАВНОМ ЭКРАНЕ


//----------------------------------------------- ОТЛАДОЧНАЯ ИНФА ------------------------------------------



#ifndef  DEBUG_Task1_ProcessEvent
        printf("--      \n");
        DelayMs(5);// задержка для очистки мусора гипертерминала  перед  GPIOA_ModeCfg(bTXD1, GPIO_ModeIN_PD)
        GPIOB_ModeCfg(bTXD1, GPIO_ModeIN_PD);
#endif


 //-----------------------------------------------------------------------------------------------------------//
#ifdef   sleep_test_by_Power_ON_OFF_PIN
   //  event_RTC_sleep=25;//блокировка тика  "event_RTC_sleep" что бы не вмешивалось в работу от пина Power_ON_OFF_PIN
#endif
     //event_RTC_sleep=25;
    // screen_refresh_flag=1;// взвод флага  "обновление ОЗУ єкрана"


        // event_RTC4++;
    // if( event_RTC4>0)
   //  {
   //  GPIOA_SetBits(GPIO_Pin_4);// CS0 - DEBUG PIN
    // }
   //  if( event_RTC4>1)
   //  {
  //   GPIOA_ResetBits(GPIO_Pin_4);// CS0 - DEBUG PIN
   //  event_RTC4 =0;
   // }


        // Получаем MAC-адрес BLE

       // GAPRole_GetParameter(GAPROLE_BD_ADDR, ble_mac);



       // printf("BLE Device ID: %02X:%02X:%02X:%02X:%02X:%02X\n",
       // ble_mac[5], ble_mac[4], ble_mac[3], ble_mac[2], ble_mac[1], ble_mac[0]);





        GAPRole_GetParameter(GAPROLE_BD_ADDR, ble_mac);

          checkConnectAndSync();// если произошел коннект то передаем первичные актальные  данные на телефон




             if(( SyncStart ==1) & (SyncDelay ==2))// самая первая синхронизация с приложением после коннекта
             {

                 SyncStart =0;
                 SyncDelay =0;

                 // блокируем задачу  фонового обновления ТЕМПЕРАТУРЫ текущей на 3-5 сек после первичной синхронизации   ОДИН РАЗ после старта коннекта
                 busy_transmit =1;// как только данные  прилетели с телефона идет задержка  1 - 2 секунды для встречного потока  такого как фоновое обновление
                 busy_transmit_delay =1;                         //температуры



               //  FOR_BUFER++;// счетчик обновления пакета  при каждом отслыке данных на телфон

                 RTC_GetTime( &py,&pmon,&pd,&ph,&pm,& ps);
                 UnixTime = GetUnixTime();
                 ConvertUnixTimeToBytes( UnixTime);

                 to_test_buffer42[4] =  UnixByte0;  // 1/4 UnixTime  при каждом отслыке данных на телфон , что приложение принимало новый пакет
                 to_test_buffer42[5] =  UnixByte1;  // 1/4 UnixTime  при каждом отслыке данных на телфон , что приложение принимало новый пакет
                 to_test_buffer42[6] =  UnixByte2;  // 1/4 UnixTime  при каждом отслыке данных на телфон , что приложение принимало новый пакет
                 to_test_buffer42[7] =  UnixByte3;  // 1/4 UnixTime при каждом отслыке данных на телфон , что приложение принимало новый пакет



                 BLE_NEW_SENOSOR_TEMPER=0;//кидываем флаг принятых данных и ждем следущих через новый цикл


                         convert_temperature_set(setup_temp);// обратное преобразование от термомостата для телефона температура задачния  младший байт и старший
                         to_test_buffer42[0] =temp_whole_set;  //   температура задания первый байт
                         to_test_buffer42[1] =temp_half_set;  //   температура задания второй байт



                      Tout_for_phone =convertToTemperatureInt(Tout);

                    // printf( " Tout_int  =  %ld \n" ,convertToTemperatureInt(Tout));

                       convert_temperature_read(Tout_for_phone);// обратное преобразование  промежуточное
                       to_test_buffer42[2] =temp_whole_read;  //   температура текущая первый байт
                       to_test_buffer42[3] =temp_half_read;  //   температура текущая второй байт


                       //  to_test_buffer42[2] =25;  //   температура текущая первый байт
                       //  to_test_buffer42[3] =5;  //   температура текущая второй байт




                       app_drv_fifo_flush(&app_uart_rx_fifo);

                       Enable_notify(peripheralConnList.connHandle, ENABLE);
                       read_length = to_test__b_4_size-0;// длинна данных из массива тестового to_test_buffer2 ="Privet moy drug"
                       //read_length = to_test__b_4_size;// длинна данных из массива тестового to_test_buffer2 ="Privet moy drug"
                       app_drv_fifo_write(&app_uart_rx_fifo, (uint8_t *)&to_test_buffer42, &read_length);

                      //app_drv_fifo_write(&app_uart_tx_fifo, (uint8_t *)&to_test_buffer42, &read_length);

                      tmos_start_task(Peripheral_TaskID, UART_TO_BLE_SEND_EVT, 2);


        }



             if(( SyncStart ==1)&(SyncDelay < 2))
                  {
                   SyncDelay++;
                  }




     tmos_start_task( task1 , sub_event_1 ,1.6*1.0*1000 ); // 625mks*1.6*1*1000 = 1 sek  период запуска task1/sub_event_1


    return events ^ sub_event_1;

  }
  //-------------------------------------------------------------------------------------------------//


  if( events & sub_event_2 )// подзадача перехвата сканирования быстрых событий таких как клавиатура , EVENT SLEEP.
    {                       // и перебора COM0 -COM3 для LCD


//----------------------------------------- LCD task invertor   " ОТЛАДКА "  -----------------------------------------//

//----------------------------------------- END OFF  LCD task invertor   " ОТЛАДКА "  -----------------------------------------//

//----------------------------------------- MUST HAVE CODE !!-------------------------------------------------------
     //         init_LCD();//
     //         fsm++;              // новое состояние
      //        if(fsm>3)fsm2++;    // круговорот
      //        fsm&=FSM_MASK;      //ограничение состояний
       //       fsm2&=FSM2_MASK;    //ограничение состояний
       //       drive_ALL();            //сгенерировать новый выход //
       //       GPIOA_SetBits(bTXD1);// артифакт пер на UART один при перебивке GPIO LCD

/*

               if(fsm&0x00000001)
              {
                 tmos_start_task( task1 , sub_event_2 ,2 );// регулировка помаргивания при частом обновлении/ контрастности
                 //   tmos_start_task( task1 , sub_event_2 ,1 );
              }
               else
               {
                 tmos_start_task( task1 , sub_event_2 ,5 );// регулировка помаргивания при частом обновлении/ контрастности
                 //  tmos_start_task( task1 , sub_event_2 ,3 );
               }

*/

      if(BUSY_KEY==1)
      {
          BUSY_KEY2=1;// ловим занятость клавиатуры и передаем в меленный поток  BUSY_KEY2=1,затем ждем 2 сек
      }


      if( Task3_1==RUN_Task) //запускаем (дергаем) Task3_1
          {
              Task3_1=0;
              tmos_start_task( task3 , sub_event_1 ,1.6*1.0* start_task_delay);
          }

      if( Task3_1==STOP_Task)
          {
              Task3_1=0;
              tmos_clear_event( task3, sub_event_1 );
              tmos_stop_task( task3 , sub_event_1 );
          }

      if( Task3_1==Reload_Task)
          {
              Task3_1=0;
              tmos_start_reload_task( task3 , sub_event_1 ,1.6*1.0* start_task_delay);
          }


      tmos_start_task( task1 , sub_event_2 ,1.6*1.0*5 );// тик таймера 5 милисекунд

      //tick++;//каждые 5 милисекунд
     // #define TimeSet  1000

      // T = tick*5;
      //if( T== TimeSet )
     // {
        // inversblink  = ~inversblink;
     // }

      //как только нажали кнопку, то :

      // 1. скинули таймер tick
      // 2.  inversblink =255 (все светится)

      // т.е останавливать task1_1 не нужно. Максимально потеряем 5 милисекунд
      // главное програмно сбросить счетчик таймер tick





      return events ^ sub_event_2;
    }
  //-------------------------------------------------------------------------------------------------//

  if( events & sub_event_3 )
    {





      if(busy_transmit ==1)// если иедет парелельно передача данных , то приостанавливаем данную процедуру на  1-2 секунды пока не скинется
          // флаг busy_transmit ==0
      {
          busy_transmit_delay++;//счетчик цикло задержки

      }


      if( busy_transmit_delay>2)
        {
          busy_transmit =0;//даем добро на разрешение передачи данных - коализий не должно быть встречных
          busy_transmit_delay =0;

          FLASH_UPDATE =1; // даем разрешениена обвление фдеша в следующем цикле  ТАСКА == 1 сек , и потом флаг сбрасывается сам

          BLE_NEW_SENOSOR_TEMPER =1;//даем добро на обновление один раз данных по событию в конце  окончания занятости

        }

         checkAndSetFlag();//если температура изменилась то выдаем ее на телефон

        if( ( BLE_NEW_SENOSOR_TEMPER==1)&(BLE_NEW_DATA==0)&(busy_transmit ==0))
        //  if( ((BLE_NEW_DATA==0)&(busy_transmit ==0)) )

                    {
            BLE_NEW_SENOSOR_TEMPER =0; // скидываем и ждем измегнеия температуры


        //  FOR_BUFER++;// счетчик обновления пакета  при каждом отслыке данных на телфон

          RTC_GetTime( &py,&pmon,&pd,&ph,&pm,& ps);
          UnixTime = GetUnixTime();
          ConvertUnixTimeToBytes( UnixTime);

          to_test_buffer42[4] =  UnixByte0;  // 1/4 UnixTime  при каждом отслыке данных на телфон , что приложение принимало новый пакет
          to_test_buffer42[5] =  UnixByte1;  // 1/4 UnixTime  при каждом отслыке данных на телфон , что приложение принимало новый пакет
          to_test_buffer42[6] =  UnixByte2;  // 1/4 UnixTime  при каждом отслыке данных на телфон , что приложение принимало новый пакет
          to_test_buffer42[7] =  UnixByte3;  // 1/4 UnixTime при каждом отслыке данных на телфон , что приложение принимало новый пакет




          convert_temperature_set(setup_temp);// обратное преобразование от термомостата для телефона температура задачния  младший байт и старший
          to_test_buffer42[0] =temp_whole_set;  //   температура задания первый байт
          to_test_buffer42[1] =temp_half_set;  //   температура задания второй байт


            Tout_for_phone =convertToTemperatureInt(Tout);

          // Tout_for_phone =convertToTemperatureInt(23.0);
          // Tout_for_phone =convertToTemperatureInt(FOR_BUFER); //отладка


          // printf( " Tout_int  =  %ld \n" ,convertToTemperatureInt(Tout));
           convert_temperature_read(Tout_for_phone);// обратное преобразование  промежуточное
           to_test_buffer42[2] =temp_whole_read;  //   температура текущая первый байт
           to_test_buffer42[3] =temp_half_read;  //   температура текущая второй байт



           app_drv_fifo_flush(&app_uart_rx_fifo);
           Enable_notify(peripheralConnList.connHandle, ENABLE);
           read_length = to_test__b_4_size-0;// длинна данных из массива тестового to_test_buffer2 ="Privet moy drug"
           app_drv_fifo_write(&app_uart_rx_fifo, (uint8_t *)&to_test_buffer42, &read_length);


               tmos_start_task(Peripheral_TaskID, UART_TO_BLE_SEND_EVT, 2);

                    }



        tmos_start_task( task_id , sub_event_3 ,1.6*3*1500 ); // 0.625mks*1.6*3*1000 = 3 sek период запуска task1/sub_event_1
    //   tmos_start_task( task_id , sub_event_3 ,1.6*3*2000 ); // 0.625mks*1.6*3*1000 = 3 sek период запуска task1/sub_event_1



      return events ^ sub_event_3;
    }
  //-------------------------------------------------------------------------------------------------//

  if( events & sub_event_14 )
      {

    //    tmos_start_task( task_id , sub_event_14 ,1.6*14*1000 ); // 0.625s*1.6*14*1000 = 14 sek период запуска task1/sub_event_1

        return events ^ sub_event_14;
      }


  return 0;

}




tmosEvents Task2_ProcessEvent( tmosTaskID task_id, tmosEvents events )
{
    int * msgPtr;
    uint16_t read_length = 0;// отладка для контрольного считывания тестового буфера

    // uint8_t read_length = 0;// отладка для контрольного считывания тестового буфера

  if( events & sub_event_1 )
  {

    //  PRINT(" Task2_ProcessEvent1 -> PM_Test  :   =%d\n");
    //  PRINT("\n");


      Sleep_Start_Time_Write();// переобновление по кольцу Времени в EEPROM/ Flash + Sleep Power On/Off



    return events ^ sub_event_1;
  }
  //-------------------------------------------------------------------------------------------------//

  // ------------------------------------- КЛАВИАТУРА------------------------------------------------//

  // 1. измеряем значение (Vmax) Vcore на подпорке клавиатуры
  // 2. затем зная реальное значение Vcore , с точностью 4% ловим в процетном соотношении изменния значения Vkey

  if( events & sub_event_2 )
    {
 #define  DEBUG_key_event
 #ifndef  DEBUG_key_event
          GPIOA_SetBits(bTXD1);
          GPIOA_ModeCfg(bTXD1, GPIO_ModeOut_PP_5mA);
 #endif


      keys();  //  анализ состояния входов АЦП для клавиатуры + генерация событий коротких/длинных


      //отладка
        event_type=key_event_handling();// сканирвоание и обработка событий от клавиатуры


      if((event_type == key_event_plus)||(event_type== key_event_minus)
              ||(event_type== key_event_mode)||(event_type== key_event_plus_minus)
              ||(event_type== key_long_plus_minus_yes)|| (event_type== key_long_mode_yes)
              ||(screen_refresh_flag==1)||(heat_on_off==1)||(tempere_cange==1))
      {


      tempere_cange=0;// произошло изменение температуры в буфере
      heat_on_off=0; // скинули флаг собтия при изменение гистерезиса значка "ON"__ "OFF"
      screen_refresh_flag=0;//скинули флаг срочного обновления єкрана посли изменения содержимого ЄКРАНА на другой ЄКРАН
/*
if(event_type== key_event_mode)
{
          GPIOA_SetBits(bTXD1);
           GPIOA_ModeCfg(bTXD1, GPIO_ModeOut_PP_5mA);
           PRINT(" event_type ++               =%d\r\n", event_type);
          printf("--      \n");
           GPIOA_ModeCfg(bTXD1, GPIO_ModeIN_PD);
}
*/
      screen_choice(screen_level); // обновление выбранного экрана от конкретного произошедшего события!!

      event_type =0;// очистка события после очередной проресовки меню

#ifndef  DEBUG_key_event
printf("--      \n");
//    DelayMs(10);// задержка для очистки мусора гипертерминала  перед  GPIOA_ModeCfg(bTXD1, GPIO_ModeIN_PD)
GPIOA_ModeCfg(bTXD1, GPIO_ModeIN_PD);
#endif
        }






         tmos_start_task( task_id , sub_event_2 ,1.6*30 );//  опросный поток для кнопок с частотой 35 mlsek

     //  tmos_start_task( task_id , sub_event_2 ,1.6*25 );//  опросный поток для кнопок с частотой 35 mlsek



      return events ^ sub_event_2;
    }
//-------------------------------------------------------------------------------------------------//


  if( events & sub_event_3 )
    {
//-------------------------------виртуальный таймер для длиннх задержек LED/моргание єкрана итд------------

    //if(Virtual_timer2==20) // 20 тиков таймера*100 милисекунд = 1 секунда
      if(Virtual_timer2==10) // 20 тиков таймера*100 милисекунд = 1 секунда
      {
      Virtual_timer2=0;
      sek_count++; // фоновый счетчик секунд для подсветки и тому подобное.
      if(start_anime_blink==1)// если разрешен запуск виртуального таймера аниме
      {
      sek_count_for_prog_anime++;// фоновый счетчик секунд для моргания аниме заставки для разных режимов  .
      }
   //   second_sep_invers=~second_sep_invers;// мигаем значком двоеточия в "часах"
   //   screen_refresh_flag=1;
      }
//------------------------------------ ПАУЗА для LED ПОДСВЕТКИ И ЗАТЕМ ЕЕ ОТКЛЮЧЕНИЕ----------------------------------
      if( (start_back_light==1)&(sek_count> time_sek ))
      {

      LIGTH_OFF;         // тушим подсветку

      if((ON_Icon_event==1 )&(sek_count> time_sek_plus_1)) // интервал между отключением подсветки и вкл LED не менее 1 СЕК !
      {
      start_back_light=0;// сбрасываем таймер подсветки

     // REL_ON; // включаем обратно  реле если оно должно быть включенным

      }

      if((sek_count> time_sek_plus_1)&(FLASH_UPDATE==0)) // интервал между отключением подсветки и вкл LED не менее 1 СЕК !
            {
          start_back_light=0;
      //  FLASH_UPDATE++;

          if(LOC_on_off==LOC_on)
             {
              lock_key = lock; // активируем  "блокировку клавиатуры" если она разрешена // выводим изображение "замок" + lock_key = true;
              UP_press=1;// переводим кнопку MODE  в режим  ОТЖАТИЯ (для возможности LONG PRESS)
             }

            }

      DelayMs(10);
      adc_ready=0; //возобновляем длинное измерение АЦП
      }
//------------------------------------ СБРОС БЛЕМАНИЯ ПРИ НАБОРЕ ЗНАЧЕНИЕ В МЕНЮХАХ ----------------------------------
    //  if((start_bink==0)&( Virtual_timer>0)&(Virtual_timer<10))// если произведен сброс моргания меню , то даем задержку на ее возобновление!!
    //  {
     //     Virtual_timer=0; // один тик ТАЙМЕРА= периоду task  (250 млсек)
          // обнуляем Таймер - синхронизируем для коректного моргания при нажатии кнопок + и +
    //      start_bink=1;//перезапускаем моргание по истечению данной паузы
       //   tmos_start_reload_task( task3 , sub_event_2 ,1.6*5 );
    //  }
//------------------------------------------------------------------------------------------------------------------------

      Virtual_timer++;
      Virtual_timer2++;

   /*

      if((main_screen_type== main_screen_manual)||(main_screen_type== main_screen_prog))
      {
      termostat();// обновление изменения  в функции термостат
      }// иначе управление реле в режиме SFM

*/



//---------------------------   обработка вычислений ADC
/*

      // adc_ready=0;
       if(adc_ready==0) // если измерения  разрешены
       {

       if( ++ADC_i <=adcBuffLen)// длинные измерения + накопления "LONG"
        {

                    ADC_ExtSingleChSampInit(SampleFreq_8,ADC_PGA_1_4 );
                     //ADC_ExtSingleChSampInit(SampleFreq_8,ADC_PGA_0 );
                    ADC_ChannelCfg(9);// - PA0
                    //RoughCalib_Value = ADC_DataCalib_Rough();
                   // RoughCalib_Value=0;
                    //adcBuffSum = ADC_ExcutSingleConver()+RoughCalib_Value;
                    adcBuffSum = ADC_ExcutSingleConver();
                    adcBuffSumKey =adcBuffSumKey + adcBuffSum;

                   // ADC_ChannelCfg(0);// - PA4
                     ADC_ChannelCfg(14);// - PA4
                    adcBuffSum = ADC_ExcutSingleConver();
                    adcBuffSumRef= adcBuffSumRef + adcBuffSum;

                    //ADC_ExtSingleChSampInit(SampleFreq_8,ADC_PGA_1_4 );
                    //ADC_ExtSingleChSampInit(SampleFreq_8,ADC_PGA_0 );
                    ADC_ExtSingleChSampInit(SampleFreq_8,ADC_PGA_1_2 );

                    ADC_ChannelCfg(11);// - PA7
                   // RoughCalib_Value = ADC_DataCalib_Rough();
                    //adcBuffSum = ADC_ExcutSingleConver()+RoughCalib_Value;
                    adcBuffSum = ADC_ExcutSingleConver();

                    adcBuffSumNtc =adcBuffSumNtc + adcBuffSum;


       if( ADC_i==adcBuffLen)
        {
                    adcBuffSumKey= adcBuffSumKey/adcBuffLen;
                    adcBuffSumRef=adcBuffSumRef/adcBuffLen;
                    adcBuffSumNtc=adcBuffSumNtc/adcBuffLen;
                   // Vref= (((float)adcBuffSumRef/512)-3)*1.05;


                    Vkey = ( ( ((double)(adcBuffSumKey))/512.0)-3.0)*ADC_ref;

                    Vref= ( ( ((double)(adcBuffSumRef))/512.0)-3.0)*ADC_ref;


                    Vntc= ( ( ((double)(adcBuffSumNtc))/1024.0)-1.0)*ADC_ref;

                    //Vntc= ((double)(adcBuffSumNtc))/2048.0 * 1.05;


           adcBuffLenReady =1;
           adcBuffSumRef=0;
           adcBuffSumNtc=0;
           adcBuffSumKey=0;


           ADC_i=0;

        }


        }

       }


*/

//--------------------------------  конец обработки ADC


      WWDG_SetCounter(0);//Feed the dog // обновление сторожевого таймера Fsys =(131072/24000000)*255=1.392 сек
      // время полного переполнения 8 битного регистра R8_WDOG_COUNT





         //     UART1_DefInit1();//9600 + паритет
        //     Init_HLW8110();

              //UART1_DefInit1();//9600 + паритет
          //    Calculate_HLW8110_MeterData();
          //    UART1_DefInit2();//115200(800000)  без паритета








/*

      if( NEW_DATA_FROM_PHONE==1)
              {
                  NEW_DATA_FROM_PHONE=0;//кидываем флаг принятых данных и ждем следущих через новый цикл

                  //ОБНОВЛЕНИЕ ДАННЫХ ОБРАТНО НА ТЕЛЕФОН ПРИ ПОЛУЧЕНИИ ДАННЫХ ПРИНЯТЫХ С ТЕЛЕФОНА
                           //ДОБАВЛЯЕМ КОНТРОЛЬНЫЙ EVICE ID


                  //  GAPRole_GetParameter(GAPROLE_BD_ADDR, ble_mac);


                                    //   to_test_buffer42[0] = FOR_BUFER;  // Записываем значение в первый байт
                                     //  to_test_buffer42[1] = ble_mac[5];
                                     //  to_test_buffer42[2] = ble_mac[4];
                                     //  to_test_buffer42[3] = ble_mac[3];
                                     //  to_test_buffer42[4] = ble_mac[2];
                                     //  to_test_buffer42[5] = ble_mac[1];
                                     //  to_test_buffer42[6] = ble_mac[0];
                                      // to_test_buffer42[7] = 0x22;

                                       // //ble_mac[5], ble_mac[4], ble_mac[3], ble_mac[2], ble_mac[1], ble_mac[0]);

                                                 //  FOR_BUFER++;// счетчик обновления  при каждом нажатии


                                        //         to_test_buffer42[0] = 0;  //   старший бай - для больших значений ,более 255
                                        //         to_test_buffer42[1] = FOR_BUFER; //Записываем значение в маладший нулевой байт - при длинее полезных данных 256 байт
                                        //         to_test_buffer42[2] = 0;
                                        //         to_test_buffer42[3] = 5; // длинна пакета (6 байт) в байтах начиная с нулевого индекса
                                        //         to_test_buffer42[4] = 0x88;// данные..
                                        //         to_test_buffer42[5] = 0x99;// данные.
                                        //         to_test_buffer42[6] = 0x11;// данные.
                                        //         to_test_buffer42[7] = 0x22;// данные.
                                        //         to_test_buffer42[8] = 0x33;// данные.
                                        //         to_test_buffer42[9] = 0x44;// данные.

                                        //         to_test_buffer42[10] = 0x55; // последние два байте в хвосте  зарезервированы под проверочную сумму итд
                                        //         to_test_buffer42[11] = 0xAA; // это знаечния по умолчанию - что пакет закончен  0x55 + 0xAA



                                                 //ИТОГО: тест1)  массив исходящий  общей длинной  12 байт

                                                 //должен быть коректно принят без ошибок при постонном обновлении и модификации данных



                                                   to_test_buffer42[0] =FOR_BUFER;  //   старший бай - для больших значений ,более 255
                                                   to_test_buffer42[1] = 1; //Записываем значение в маладший нулевой байт - при длинее полезных данных 256 байт
                                                   to_test_buffer42[2] = 2;
                                                   to_test_buffer42[3] = 3; // длинна пакета (6 байт) в байтах начиная с нулевого индекса
                                                   to_test_buffer42[4] = 4;// данные..
                                                   to_test_buffer42[5] = 5;// данные.
                                                   to_test_buffer42[6] = 6;// данные.
                                                   to_test_buffer42[7] = 7;// данные.
                                                   to_test_buffer42[8] = 8;// данные.
                                                   to_test_buffer42[9] = 9;// данные.

                                                   to_test_buffer42[10] = 10; // последние два байте в хвосте  зарезервированы под проверочную сумму итд
                                                   to_test_buffer42[11] = 11; // это знаечния по умолчанию - что пакет закончен  0x55 + 0xAA

                                                   to_test_buffer42[12] = 12; // последние два байте в хвосте  зарезервированы под проверочную сумму итд
                                                   to_test_buffer42[13] = 13; // это знаечния по умолчанию - что пакет закончен  0x55 + 0xAA

                                                   to_test_buffer42[14] = 14; // последние два байте в хвосте  зарезервированы под проверочную сумму итд
                                                   to_test_buffer42[15] = 15; // это знаечния по умолчанию - что пакет закончен  0x55 + 0xAA


                                                   //олезные даннеые кратно 14 т.е 14/28 итд.. Но массив инициализировать на +2 единицы



                                       // Получаем MAC-адрес BLE
                                  //     uint8_t ble_mac[6];
                                    //   GAPRole_GetParameter(GAPROLE_BD_ADDR, ble_mac);

                                       // Вставляем MAC-адрес начиная с третьего байта (индекс 2)
                                     //  for (int8 i = 0; i < 6; i++)
                                     //  {
                                           //to_test_buffer42[i + 2] = ble_mac[5 - i];  // Записываем в обратном порядке для стандартного формата MAC
                                         //  to_test_buffer42[i + 1] = ble_mac[5 - i];  // Записываем в обратном порядке для стандартного формата MAC
                                     //  }

                                       // Отладочный вывод
                                      // printf("BLE Device ID: %02X:%02X:%02X:%02X:%02X:%02X\n",
                                       //ble_mac[5], ble_mac[4], ble_mac[3], ble_mac[2], ble_mac[1], ble_mac[0]);



                                 //   Enable_notify(peripheralConnList.connHandle, ENABLE);
                                    read_length = to_test__b_4_size-0;// длинна данных из массива тестового to_test_buffer2 ="Privet moy drug"
                                    //read_length = to_test__b_4_size;// длинна данных из массива тестового to_test_buffer2 ="Privet moy drug"
                                    app_drv_fifo_write(&app_uart_rx_fifo, (uint8_t *)&to_test_buffer42, &read_length);

                                    tmos_start_task(Peripheral_TaskID, UART_TO_BLE_SEND_EVT, 2);


              }

*/








     // tmos_start_task( task_id , sub_event_3 ,1.6*50 );//  опросный поток для системмных флагов с частотой 75 mlsek
      tmos_start_task( task_id , sub_event_3 ,1.6*100 );//  опросный поток для системмных флагов с частотой 75 mlsek



      return events ^ sub_event_3;
    }




  if( events & sub_event_14 )
      {


        return events ^ sub_event_14;
      }

  return 0;

}




tmosEvents Task3_ProcessEvent( tmosTaskID task_id, tmosEvents events )
{
  int * msgPtr;
  uint16_t read_length = 0;// отладка для контрольного считывания тестового буфера


  if( events & sub_event_1 )
  {

#define   DEBUG_Task3_1


      if(Task3_1_circulation==RUN_Task)
    {

#ifndef   DEBUG_Task3_1
          GPIOB_SetBits(bTXD1);
          GPIOB_ModeCfg(bTXD1, GPIO_ModeOut_PP_5mA);
#endif

       //  printf(" Task3_1_circulation    =%d\r\n", Task3_1_circulation);

#ifndef  DEBUG_Task3_1
         printf("--      \n");
         GPIOB_ModeCfg(bTXD1, GPIO_ModeIN_PD);
#endif


         if(BUSY_KEY==0)//если клавиатура отжата
           {
           invers_blynk_image_1S=~invers_blynk_image_1S;

           }
         else
           { //иначе очистка занятости клавиатуры через 0,6 секунды после последнего нажатия
           invers_blynk_image_1S =255;// закидываем значение  255 что бы без мигания выводилось значение на экран
           BUSY_KEY=0;//
           }



         tmos_start_task( task3 , sub_event_1 ,1.6* blynk_Task_T);



    }







      if(Task3_1_circulation==One_Time_Task) // иначе одноразово заходим и по окончанию віполнения задачи - останавливаемся

    {

#ifndef   DEBUG_Task3_1
          GPIOB_SetBits(bTXD1);
          GPIOB_ModeCfg(bTXD1, GPIO_ModeOut_PP_5mA);
#endif
      //   printf(" Task3_1_One Time Run    =%d\r\n", Task3_1_circulation);
#ifndef  DEBUG_Task3_1
         printf("--      \n");
         GPIOB_ModeCfg(bTXD1, GPIO_ModeIN_PD);
#endif


    }




    return events ^ sub_event_1;

  }
  //-------------------------------------------------------------------------------------------------//

  if( events & sub_event_2 )// подзадача моргания изображений при изменении параметров времени и настройках програматора
    {

      /*
      if(event_RTC_sleep!=event_sleep_START)
       {
      UART1_DefInit1();//9600 + паритет
      Uart_Read_HLW8110_Reg(REG_RMS_IAC_ADDR,2);
      Receive_to_Bufer(u8_RX_Length);
      }
*/
            event_RTC4=~event_RTC4;

            if( event_RTC4==255)
            {
          // GPIOA_SetBits(GPIO_Pin_4);// CS0 - DEBUG PIN
                CS_O_ON ;//если ЖКИ включен

           //     if(event_RTC_sleep!=event_sleep_START)
                //  {
            //      UART1_DefInit1();//9600 + паритет
            //      Uart_Read_HLW8110_Reg(REG_RMS_IAC_ADDR,2);
             //     Receive_to_Bufer(u8_RX_Length);
                 //  }


            }else
            {
          // GPIOA_ResetBits(GPIO_Pin_4);// CS0 - DEBUG PIN
                CS_O_OFF;//если ЖКИ включен
         }





      tmos_start_task( task3 , sub_event_2 ,1.6* 100);



         return events ^ sub_event_2;
    }
  //-------------------------------------------------------------------------------------------------//

  if( events & sub_event_3 )
    {

      if( OnOff_adcBuffLenReady) // ожидаем готовность  измерений и наполнения буфера ADC для пина POW ON OFF
       {

      OnOff_adcBuffLenReady=0;


    // отладка
      Vpow_on_off =1.6;

      if( Vpow_on_off<1.4)  // читаем текущий результат из  данного буфера
        {
           event_RTC_sleep=event_sleep_START;// стартуем " SLEEP"

           REL_OFF;
           LIGTH_OFF;
        }
     }







     if( event_RTC_sleep==event_sleep_START)
        {
      event_key_count=0;
   //   event_RTC_sleep=0;
      SleepStop=1;

  //    RTC_TRIGFunCfg_Time=RTC_TRIGFunCfg_Time_Valie;
  //    PRINT(" SLEEP TIME =  RTC_TRIGFunCfg_Time=32768*10 sek    =%d\n", RTC_TRIGFunCfg_Time);

      soft_block=0;

      //запускаем  спячку в другой задаче!!!
      tmos_start_task( task2 , sub_event_1 ,1.6*1.0*1);


  //    tmos_start_task( task2 , sub_event_1 ,1);

                   }

      GET_ADC_Value();

      //НАДО в конце попробавть алгоритм опроса и наполнения по DMA!!!
      // а также поправку согласно Vref Max

        tmos_start_task( task_id , sub_event_3 ,3 );
      //tmos_start_task( task_id , sub_event_3 ,5 );
       //tmos_start_task( task_id , sub_event_3 ,10 );

      return events ^ sub_event_3;
    }
  //-------------------------------------------------------------------------------------------------//

  if( events & sub_event_14 )
      {

        return events ^ sub_event_14;
      }

  return 0;

}









void TEST_Init()
{

  //  Peripheral_TaskID = TMOS_ProcessEventRegister(Peripheral_ProcessEvent);// пример иницализации для BLE

   task1 = TMOS_ProcessEventRegister(Task1_ProcessEvent);
   task2 = TMOS_ProcessEventRegister(Task2_ProcessEvent);//
   task3 = TMOS_ProcessEventRegister(Task3_ProcessEvent);//

   tmos_set_event(task1, sub_event_1); // инициализируем  период и запуск задачи  task1/sub_event_1 и  стартуем
   tmos_set_event(task1, sub_event_2); // инициализируем  период и запуск задачи  task1/sub_event_2 и  стартуем
   tmos_set_event(task1, sub_event_3); // инициализируем  период и запуск задачи  task1/sub_event_2 и  стартуем

   tmos_set_event(task2, sub_event_2); // инициализируем   задачу сканер клавиатуры
   tmos_set_event(task2, sub_event_3); // инициализируем   задачу обновление видео
   tmos_set_event(task3, sub_event_2); // инициализируем  период и запуск задачи  task1/sub_event_3 и  стартуем
   tmos_set_event(task3, sub_event_3); // инициализируем  период и запуск задачи  task1/sub_event_3 и  стартуем
   tmos_set_event(task3, sub_event_1);



 //   tmos_stop_task(task1, sub_event_1); // инициализируем  период и запуск задачи  task1/sub_event_1 и  стартуем
//    tmos_stop_task(task1, sub_event_2); // инициализируем  период и запуск задачи  task1/sub_event_2 и  стартуем
//    tmos_stop_task(task2, sub_event_2); // инициализируем   задачу сканер клавиатуры
//    tmos_stop_task(task2, sub_event_3); // инициализируем   задачу обновление видео
//    tmos_stop_task(task3, sub_event_2); // инициализируем  период и запуск задачи  task1/sub_event_3 и  стартуем
//    tmos_stop_task(task3, sub_event_3); // инициализируем  период и запуск задачи  task1/sub_event_3 и  стартуем

}











//---------------------------------------------FOR TERMO CODE-----------------------------------------


void Start_Boot_for_Schedule(void)
{

static unsigned short a,b,c,d,i,s,ERROR,rewrite,BUSY_MEMORY_ADR, FREE_MEMORY_ADR,LAST_MEMORY_ADR;
static unsigned short BUFF_SCHEDULE_RESERVE[SHE_N];// буфер для контрольной копии массива времени TIME_RESERVE
static unsigned short SCHEDULE_Copy_Pointer[SCHEDULE_Copy_N];

a=0,b=0,c=0,d=0,i=0,s=0,ERROR=0,rewrite=0,BUSY_MEMORY_ADR=0, FREE_MEMORY_ADR=0,LAST_MEMORY_ADR=0;

#define   DEBUG_Start_Boot_for_Schedule

#ifndef  DEBUG_Start_Boot_for_Schedule
         GPIOB_SetBits(bTXD1);
         GPIOB_ModeCfg(bTXD1, GPIO_ModeOut_PP_5mA);
#endif

#ifndef  DEBUG_Start_Boot_for_Schedule
    PRINT("EEPROM_READ... \n");
#endif

    //-------------------------------------читаем копируем обратно последнее сохраненное Schedule ---------------------//

 //1.
    s= EEPROM_READ(BASE_EEPROM_ADR , &TestBuf, 256);// читаем и оределяем указатель
    //свободного  места в EEPROM[128] под параметры Schedule, с учетов общего выделенного места и
    //размером массива Schedule_RESERVE

    a=TestBuf[0];

#ifndef  DEBUG_Start_Boot_for_Schedule
    for(i = 0; i < lengthTestBuf; i++)
                          {
    PRINT("%hu ", TestBuf[i]);
                           }
    PRINT("\n");
#endif

 //-----------------------------------------------------------------------------------------------------//

    if((a!= 0x55AA))// если нет стартового слова!! (или испорчено или первый раз)
              {

    s = EEPROM_ERASE(BASE_EEPROM_ADR, EEPROM_MIN_ER_SIZE);// стираем принудительно всю страницу  в 256  байт
#ifndef  DEBUG_Start_Boot_for_Schedule
    PRINT("EEPROM_ERASE   OK=%02x\n",s);
#endif
    TestBuf[0] = 0x55AA;// записываем стартовое слово в начало страницы

    s=  EEPROM_WRITE(BASE_EEPROM_ADR , &TestBuf, 2); // записываем первый 16 бит (2байта) стартовый регистр
#ifndef  DEBUG_Start_Boot_for_Schedule
    PRINT("EEPROM_WRITE BOOT  OK=%02x\n",s);
#endif
 //--------------------------------------------------------------------------------------------------------------//


  //  py   =  2021;//py;
  //  pmon =  1;//pmon;
  //  pd   =  1;//pd;
  //  ph   =  0;//ph;
  //  pm   =  0;//pm;
  //  ps   =  0;//ps

  //  SCHEDULE_RESERVE[0]= py;
 //   SCHEDULE_RESERVE[1]= pmon;
 //   SCHEDULE_RESERVE[2]= pd;
 //   SCHEDULE_RESERVE[3]= ph;
 //   SCHEDULE_RESERVE[4]= pm;
  //  SCHEDULE_RESERVE[5]= ps;
  //  SCHEDULE_RESERVE[6]= 0xAAAA; // стартовая маска НЕ ОБНОВЛЕННАЯ SLEP / WRITE

    memcpy(SCHEDULE_RESERVE, Shedull_Pointer, sizeof(SCHEDULE_RESERVE));


    s=  EEPROM_WRITE(BASE_EEPROM_ADR+2 , &SCHEDULE_RESERVE, 252); // инициализируем текущеее расписание "заводскими настройками"
#ifndef  DEBUG_Start_Boot_for_Schedule
    PRINT("\n");
    PRINT("EEPROM_WRITE <<FACTORY START BOOT FOR Schedule>>   OK=%02x\n",s);
    PRINT("\n");
#endif
 //--------------------------------контрольное считывание и вывод всех 256 байт страницы-----------------------------------//
    s= EEPROM_READ(BASE_EEPROM_ADR , &TestBuf, 256);// читаем и оределяем указатель
     //свободного  места в EEPROM[128] под параметры ВРЕМЕНИ, с учетов общего выделенного места и
     //размером массива TIME_RESERVE
#ifndef  DEBUG_Start_Boot_for_Schedule
    for(i = 0; i < lengthTestBuf; i++)
                           {
    PRINT("%hu ", TestBuf[i]);
                            }
    PRINT("\n");
#endif
              }
//------------------------------------------------------------------------------------------------------//

 //2.//  анализ считаного и указателя  свободной/ занятой памяти
    a=0;  // control breakpoint
    BUSY_MEMORY_ADR=0;
    i = 0;

    for(i = 0; i < SCHEDULE_Copy_N; i++)// анализируем очередь прочитанных указателей для каждого массива "ВРЕМЕНИ"       {
    {
     //  PRINT(" %hu ", (i*TR_N)+1);
     //  PRINT(" %hu ", TestBuf[(i*TR_N)]+1);
    a=TestBuf[(i*SHE_N)+1];// +1 линейный сдвиг на первое стационарное слово из 2х байт = 0x55AA;

    if (a!=0xFFFF)
       {
    BUSY_MEMORY_ADR++; // control breakpoint
       }

       }
#ifndef  DEBUG_Start_Boot_for_Schedule
    PRINT("\n");//control breakpoint
    PRINT(" BUSY_MEMORY_ADR         ----------------------------------->>     = %hu\n",BUSY_MEMORY_ADR-1);
    PRINT("\n");
#endif


    if((BUSY_MEMORY_ADR<=SCHEDULE_Copy_N)&(BUSY_MEMORY_ADR>0))// если свободный указатель доступен из выделенного максимума памяти
    {

    FREE_MEMORY_ADR=BUSY_MEMORY_ADR; // то определяем текущую сободную память
#ifndef  DEBUG_Start_Boot_for_Schedule
    PRINT(" 0 + FREE_MEMORY_ADR   ----------------------------------->>     = %hu\n",FREE_MEMORY_ADR);
#endif
         }
    else {


    if(BUSY_MEMORY_ADR==0)
       {
#ifndef  DEBUG_Start_Boot_for_Schedule
    PRINT(" BUSY_MEMORY_ADR         ----------------------------------->>     = %hu\n",BUSY_MEMORY_ADR-1);
    PRINT(" 0 + FREE_MEMORY_ADR     ----------------------------------->>     = %hu\n",FREE_MEMORY_ADR);
#endif
   //------------------------------------------- DEBUG -------------------------------------------//
#ifndef  DEBUG_Start_Boot_for_Schedule
    PRINT("EEPROM_READ... \n");
#endif
    EEPROM_READ(BASE_EEPROM_ADR, TestBuf,  lengthTestBuf*2);
#ifndef  DEBUG_Start_Boot_for_TIME
    for(i = 0; i < lengthTestBuf; i++)
         {
    PRINT("%hu ", TestBuf[i]);
         }
    PRINT("\n");
#endif
         //------------------------------------------- END OFF DEBUG -------------------------------------------//

     }

     }

     LAST_MEMORY_ADR=FREE_MEMORY_ADR-1 ;

     b=LAST_MEMORY_ADR * SHE_N * 2;//

     b= b+ SCHEDULE_RESERVE_6_BASE_ADR;// + линейный сдвиг на первое стационарное слово из 2х байт

    //после определения указателя занятого/свободного флеш читаем его содержимое в массив для RTC - TIME_RESERVE[TRN]
#ifndef  DEBUG_Start_Boot_for_Schedule
     PRINT(" FREE_MEMORY_ADR* TR_N*2 + 2    %hu ",  b);
     PRINT("\n");
     PRINT("\n");
#endif
     s= EEPROM_READ( b  , &SCHEDULE_RESERVE, SHE_N*2);//читаем контрольно записанный  TIME_RESERVE из EEPROM

#ifndef  DEBUG_Start_Boot_for_Schedule
     for(i = 0; i < SHE_N; i++)
        {
     PRINT(" %hu ", SCHEDULE_RESERVE[i]);

        }
     PRINT("\n");
     PRINT("\n");
#endif


//---------------------------------------------------------------------------------------------------------------//

   //     RTC_GetTime( &py,&pmon,&pd,&ph,&pm,& ps);

#ifndef  DEBUG_Start_Boot_for_Schedule
  //      printf("\n");
  //      printf( " TIME ON START \n");
  //      printf( "%d year %d month %d day %d hour %d minute %d second  \n" ,py,pmon,pd,ph,pm,ps);
  //      printf("\n");
#endif



         if(SCHEDULE_RESERVE[126]==0x5555)// или контрольный CRC

  //  if((TIME_RESERVE[6]==0x5555)||(py!=2020))  //без флага обновления WRITE RTC ON SLEEP - часы получают левые данные - все зависает
   // после первого RESET без WRITE RTC ON SLEEP !!
       {





    }else

    {// если произошел  системный или HARD сбой в RTC - то сбрасываем часы RTC на заводскую настройку
     // следующее сохранение времени будет после удачной работы RTC+ BAT+ WRITE RTC ON SLEEP прик отключении питания
     // во всех остальных случаях нет особого смысла периодически обновлять время в EEPROM, иначе оно будет сдвигатся
     //при следующем старте RESET, что не есть актуально для пользователя
//#ifndef  DEBUG_Start_Boot_for_Schedule
     PRINT("\n");
   //  PRINT("  Schedule WRITE ERROR !!!  =%hu\n",  Time_Write);
   //  PRINT("  Schedule WRITE ERROR !!!  =%hu\n",  Time_Write);
       PRINT("  << UPDATE Schedule Boot From  EEPROM>>  ОК  (NO CRC check!)  =%hu\n",  Time_Write);

     PRINT("\n");
//#endif
 //       py   = TIME_RESERVE[0];
 //       pmon = TIME_RESERVE[1];
 //       pd   = TIME_RESERVE[2];
 //       ph   = TIME_RESERVE[3];
 //       pm   = TIME_RESERVE[4];
//        ps   = TIME_RESERVE[5];


 //    PRINT("\n");
 //    PRINT(" Time_Write=0xAAAA  OK=%02x\n",Time_Write);
 //    PRINT("\n");
  //             py   =  2024;//py;
  //             pmon =  1;//pmon;
 //              pd   =  1;//pd;
  //             ph   =  0;//ph;
  //             pm   =  0;//pm;
  //             ps   =  0;//ps


  //   RTC_InitTime(py, pmon, pd, ph, pm, ps);

    }

#ifndef  DEBUG_Start_Boot_for_TIME
         printf("--      \n");
         DelayMs(5);// задержка для очистки мусора гипертерминала  перед  GPIOA_ModeCfg(bTXD1, GPIO_ModeIN_PD)
         GPIOB_ModeCfg(bTXD1, GPIO_ModeIN_PD);
#endif

}


void    Start_Boot_for_System(void)
{

static unsigned short a,b,c,d,i,s,ERROR,rewrite,BUSY_MEMORY_ADR, FREE_MEMORY_ADR,LAST_MEMORY_ADR;
static unsigned short BUFF_SYSTEM_RESERVE[SR_N];// буфер для контрольной копии массива  SYSTEM_RESERVE
static unsigned short System_Copy_Pointer[SYSTEM_Copy_N];

a=0,b=0,c=0,d=0,i=0,s=0,ERROR=0,rewrite=0,BUSY_MEMORY_ADR=0, FREE_MEMORY_ADR=0,LAST_MEMORY_ADR=0;

RTC_GetTime( &py,&pmon,&pd,&ph,&pm,& ps);// ОБЯЗАТЕЛЬНО ПРОЧИТАТЬ ТЕКУЩЕЕ ВРЕМЯ ПОСЛЕ RESET!!!!
    // иначе функция  RTC_InitTime(py, pmon, pd, ph, pm, ps); //запишет  везде "0" !!


#define  DEBUG_Start_Boot_for_System

#ifndef  DEBUG_Start_Boot_for_System
         GPIOB_SetBits(bTXD1);
         GPIOB_ModeCfg(bTXD1, GPIO_ModeOut_PP_5mA);
#endif


#ifndef  DEBUG_Start_Boot_for_System
    PRINT("EEPROM_READ... \n");
#endif
    //---------------------------------------читаем копируем обратно последнее сохраненное время---------------------//

 //1.
    s= EEPROM_READ(SYSTEM_EEPROM_ADR , &TestBuf, 256);// читаем и оределяем указатель
    //свободного  места в EEPROM[128] под параметры ВРЕМЕНИ, с учетов общего выделенного места и
    //размером массива TIME_RESERVE

    a=TestBuf[0];

#ifndef  DEBUG_Start_Boot_for_System
    for(i = 0; i < lengthTestBuf; i++)
                          {
    PRINT("%hu ", TestBuf[i]);
                           }
    PRINT("\n");
#endif
 //-----------------------------------------------------------------------------------------------------//

    if((a!= 0x55AA))// если нет стартового слова!! (или испорчено или первый раз)
              {
    s = EEPROM_ERASE(SYSTEM_EEPROM_ADR, EEPROM_MIN_ER_SIZE);// стираем принудительно всю страницу  в 256  байт

#ifndef  DEBUG_Start_Boot_for_System
    PRINT("EEPROM_ERASE   OK=%02x\n",s);
#endif
    TestBuf[0] = 0x55AA;// записываем стартовое слово в начало страницы

    s=  EEPROM_WRITE(SYSTEM_EEPROM_ADR , &TestBuf, 2); // записываем первый 16 бит (2байта) стартовый регистр

#ifndef  DEBUG_Start_Boot_for_System
    PRINT("EEPROM_WRITE BOOT  OK=%02x\n",s);
#endif
 //--------------------------------------------------------------------------------------------------------------//
    py   =  2020;//py;
    pmon =  1;//pmon;
    pd   =  1;//pd;
    ph   =  0;//ph;
    pm   =  0;//pm;
    ps   =  0;//ps

    RTC_InitTime(py, pmon, pd, ph, pm, ps);// первичная инициализация RTC

    main_screen_type = 0; // тип работы  в главном экране  " РУЧНОЙ РЕЖИМ" по умолчанию
    sfm_min = 25;// значение SFM по умолчанию
    active_time =  sfm_min;
    active_buf = active_time;
    relax_buf = (active_time_max - sfm_min)+ dead_time;

    SYSTEM_RESERVE[0]=   main_screen_type;
  //  SYSTEM_RESERVE[1]=   LOC_on_off;
    SYSTEM_RESERVE[2]= HystPrepere;
//    SYSTEM_RESERVE[3]= ph;
    SYSTEM_RESERVE[4]= sfm_min;
//    SYSTEM_RESERVE[5]= ps;
    SYSTEM_RESERVE[6]= 0xAAAA; // стартовая маска НЕ ОБНОВЛЕННАЯ SLEP / WRITE

    s=  EEPROM_WRITE(SYSTEM_EEPROM_ADR+2 , &SYSTEM_RESERVE, 14); // инициализируем время "заводскими настройками"

#ifndef  DEBUG_Start_Boot_for_System
    PRINT("EEPROM_WRITE START TIME OK=%02x\n",s);
#endif
 //--------------------------------контрольное считывание и вывод--------------------------------------//
    s= EEPROM_READ(SYSTEM_EEPROM_ADR , &TestBuf, 256);// читаем и оределяем указатель
     //свободного  места в EEPROM[128] под параметры ВРЕМЕНИ, с учетов общего выделенного места и
     //размером массива TIME_RESERVE

#ifndef  DEBUG_Start_Boot_for_System
    for(i = 0; i < lengthTestBuf; i++)
                           {
    PRINT("%hu ", TestBuf[i]);
                            }
    PRINT("\n");
#endif
              }
//------------------------------------------------------------------------------------------------------//

 //2.//  анализ считаного и указателя  свободной/ занятой памяти
    a=0;  // control breakpoint
    BUSY_MEMORY_ADR=0;
    i = 0;

    for(i = 0; i < SYSTEM_Copy_N ; i++)// анализируем очередь прочитанных указателей для каждого массива "ВРЕМЕНИ"       {
    {
     //  PRINT(" %hu ", (i*TR_N)+1);
     //  PRINT(" %hu ", TestBuf[(i*TR_N)]+1);
    a=TestBuf[(i*SR_N)+1];// +1 линейный сдвиг на первое стационарное слово из 2х байт = 0x55AA;

    if (a!=0xFFFF)
       {
    BUSY_MEMORY_ADR++; // control breakpoint
       }

       }

#ifndef  DEBUG_Start_Boot_for_System
    PRINT("\n");//control breakpoint
    PRINT(" BUSY_MEMORY_ADR         ----------------------------------->>     = %hu\n",BUSY_MEMORY_ADR-1);
#endif


    if((BUSY_MEMORY_ADR<=SYSTEM_Copy_N )&(BUSY_MEMORY_ADR>0))// если свободный указатель доступен из выделенного максимума памяти
    {

    FREE_MEMORY_ADR=BUSY_MEMORY_ADR; // то определяем текущую сободную память

#ifndef  DEBUG_Start_Boot_for_System
    PRINT(" 0 + FREE_MEMORY_ADR   ----------------------------------->>     = %hu\n",FREE_MEMORY_ADR);
#endif
         }
    else {


    if(BUSY_MEMORY_ADR==0)
       {

#ifndef  DEBUG_Start_Boot_for_System
    PRINT(" BUSY_MEMORY_ADR         ----------------------------------->>     = %hu\n",BUSY_MEMORY_ADR-1);
    PRINT(" 0 + FREE_MEMORY_ADR     ----------------------------------->>     = %hu\n",FREE_MEMORY_ADR);
#endif
   //------------------------------------------- DEBUG -------------------------------------------//

#ifndef  DEBUG_Start_Boot_for_System
    PRINT("EEPROM_READ... \n");
#endif
    EEPROM_READ(SYSTEM_EEPROM_ADR, TestBuf,  lengthTestBuf*2);

#ifndef  DEBUG_Start_Boot_for_System
    for(i = 0; i < lengthTestBuf; i++)
         {
    PRINT("%hu ", TestBuf[i]);
         }
    PRINT("\n");
#endif
         //------------------------------------------- END OFF DEBUG -------------------------------------------//

     }

     }

     LAST_MEMORY_ADR=FREE_MEMORY_ADR-1 ;

     b=LAST_MEMORY_ADR * SR_N * 2;//

     b= b+ SYSTEM_RESERVE_6_BASE_ADR;// + линейный сдвиг на первое стационарное слово из 2х байт

    //после определения указателя занятого/свободного флеш читаем его содержимое в массив для RTC - TIME_RESERVE[TRN]

#ifndef  DEBUG_Start_Boot_for_System
     PRINT(" FREE_MEMORY_ADR* TR_N*2 + 2    %hu ",  b);
     PRINT("\n");
     PRINT("\n");
#endif
     s= EEPROM_READ( b  , &SYSTEM_RESERVE, SR_N*2);//читаем контрольно записанный  TIME_RESERVE из EEPROM

#ifndef  DEBUG_Start_Boot_for_System
     for(i = 0; i < SR_N; i++)
        {
     PRINT(" %hu ", SYSTEM_RESERVE[i]);

        }
     PRINT("\n");
     PRINT("\n");
#endif



     main_screen_type = SYSTEM_RESERVE[0];//  читаем  актуальный режим работы "главного экрана"
     LOC_on_off  = SYSTEM_RESERVE[1] ;//  читаем  актуальный режим работы "LOC"
     HystPrepere = SYSTEM_RESERVE[2];// читаем актуальный гистерезис
     device_on_off = SYSTEM_RESERVE[3];// читаем актуальное состояние вкл/выкл девайса
     sfm_min= SYSTEM_RESERVE[4];//читаем последнее сохраненное значение для SFM
     active_time =  sfm_min;
     active_buf = active_time;
     relax_buf = (active_time_max - sfm_min)+ dead_time;


//---------------------------------------------------------------------------------------------------------------//



//#ifndef  DEBUG_Start_Boot_for_System
//        printf("\n");
 //       printf( " TIME ON START \n");
  //      printf( "%d year %d month %d day %d hour %d minute %d second  \n" ,py,pmon,pd,ph,pm,ps);
 //       printf("\n");
//#endif


         //if(py!=2020)
         if(SYSTEM_RESERVE[6]==0x5555)

  //  if((TIME_RESERVE[6]==0x5555)||(py!=2020))  //без флага обновления WRITE RTC ON SLEEP - часы получают левые данные - все зависает
   // после первого RESET без WRITE RTC ON SLEEP !!
       {
//    py   = TIME_RESERVE[0];
//    pmon = TIME_RESERVE[1];
//    pd   = TIME_RESERVE[2];
//    ph   = TIME_RESERVE[3];
//    pm   = TIME_RESERVE[4];
//    ps   = TIME_RESERVE[5];

    //     py   =  2023;//py;
    //     pmon =  1;//pmon;
    //     pd   =  1;//pd;
    //     ph   =  0;//ph;
    //     pm   =  0;//pm;
    //     ps   =  0;//ps



  //  RTC_InitTime(py, pmon, pd, ph, pm, ps);


    }else

    {// если произошел  системный или HARD сбой в RTC - то сбрасываем часы RTC на заводскую настройку
     // следующее сохранение времени будет после удачной работы RTC+ BAT+ WRITE RTC ON SLEEP прик отключении питания
     // во всех остальных случаях нет особого смысла периодически обновлять время в EEPROM, иначе оно будет сдвигатся
     //при следующем старте RESET, что не есть актуально для пользователя

//#ifndef  DEBUG_Start_Boot_for_System
     PRINT("\n");
    // PRINT("  RTC CLOCK WRITE ERROR !!!  =%hu\n",  Time_Write);
     //PRINT("  RTC CLOCK WRITE ERROR !!!  =%hu\n",  Time_Write);
     PRINT("   WRITE Boot_for_System  \n");
     PRINT("\n");
//#endif
 //       py   = TIME_RESERVE[0];
 //       pmon = TIME_RESERVE[1];
 //       pd   = TIME_RESERVE[2];
 //       ph   = TIME_RESERVE[3];
 //       pm   = TIME_RESERVE[4];
//        ps   = TIME_RESERVE[5];


 //    PRINT("\n");
 //    PRINT(" Time_Write=0xAAAA  OK=%02x\n",Time_Write);
 //    PRINT("\n");
  //             py   =  2024;//py;
  //             pmon =  1;//pmon;
 //              pd   =  1;//pd;
  //             ph   =  0;//ph;
  //             pm   =  0;//pm;
  //             ps   =  0;//ps


  //   RTC_InitTime(py, pmon, pd, ph, pm, ps);

    }

         if((py<2021)||(py>2060))
         {
          set_date_clock=0;  // если год  прочитанный  меньше 2022 или более 2060 , значит время сбилось
         }else
         {
          set_date_clock=1; // иначе время выставленное идет
         }



#ifndef  DEBUG_Start_Boot_for_System
         printf("--      \n");
         DelayMs(5);// задержка для очистки мусора гипертерминала  перед  GPIOA_ModeCfg(bTXD1, GPIO_ModeIN_PD)
         GPIOB_ModeCfg(bTXD1, GPIO_ModeIN_PD);
#endif



}



void  Start_Boot_for_Set_Temper(void)
{

static unsigned short a,b,c,d,i,s,ERROR,rewrite,BUSY_MEMORY_ADR, FREE_MEMORY_ADR,LAST_MEMORY_ADR;
static unsigned short BUFF_TEMPER_RESERVE[TempR_N];// буфер для контрольной копии массива  TEMPER_RESERVE
static unsigned short TEMPER_Copy_Pointer[TEMPER_Copy_N];

a=0,b=0,c=0,d=0,i=0,s=0,ERROR=0,rewrite=0,BUSY_MEMORY_ADR=0, FREE_MEMORY_ADR=0,LAST_MEMORY_ADR=0;


#define  DEBUG_Start_Boot_for_TEMPER

#ifndef  DEBUG_Start_Boot_for_TEMPER
         GPIOB_SetBits(bTXD1);
         GPIOB_ModeCfg(bTXD1, GPIO_ModeOut_PP_5mA);
#endif


#ifndef  DEBUG_Start_Boot_for_TEMPER
    PRINT("EEPROM_READ... \n");
#endif
    //---------------------------------------читаем копируем обратно последнее сохраненное время---------------------//

 //1.
    s= EEPROM_READ(TEMPER_EEPROM_ADR , &TestBuf, 256);// читаем и оределяем указатель
    //свободного  места в EEPROM[128] под параметры ВРЕМЕНИ, с учетов общего выделенного места и
    //размером массива TIME_RESERVE

    a=TestBuf[0];

#ifndef  DEBUG_Start_Boot_for_TEMPER
    for(i = 0; i < lengthTestBuf; i++)
                          {
    PRINT("%hu ", TestBuf[i]);
                           }
    PRINT("\n");
#endif
 //-----------------------------------------------------------------------------------------------------//

    if((a!= 0x55AA))// если нет стартового слова!! (или испорчено или первый раз)
              {

    s = EEPROM_ERASE(TEMPER_EEPROM_ADR, EEPROM_MIN_ER_SIZE);// стираем принудительно всю страницу  в 256  байт

#ifndef  DEBUG_Start_Boot_for_TEMPER
    PRINT("EEPROM_ERASE   OK=%02x\n",s);
#endif
    TestBuf[0] = 0x55AA;// записываем стартовое слово в начало страницы

    s=  EEPROM_WRITE(TEMPER_EEPROM_ADR , &TestBuf, 2); // записываем первый 16 бит (2байта) стартовый регистр

#ifndef  DEBUG_Start_Boot_for_TEMPER
    PRINT("EEPROM_WRITE BOOT  OK=%02x\n",s);
#endif


    setup_temp=270;

    TEMPER_RESERVE[0]= setup_temp;
 //   TEMPER_RESERVE[1]= pmon;
 //   TEMPER_RESERVE[2]= pd;
 //   TEMPER_RESERVE[3]= ph;
 //   TEMPER_RESERVE[4]= pm;
 //   TEMPER_RESERVE[5]= ps;
 //   TEMPER_RESERVE[6]= 0xAAAA; // стартовая маска НЕ ОБНОВЛЕННАЯ SLEP / WRITE

    s=  EEPROM_WRITE(TEMPER_EEPROM_ADR+2 , &TEMPER_RESERVE, TempR_N*2); // инициализируем время "заводскими настройками"



#ifndef  DEBUG_Start_Boot_for_TEMPER
    PRINT("EEPROM_WRITE START TIME OK=%02x\n",s);
#endif
 //--------------------------------контрольное считывание и вывод--------------------------------------//
    s= EEPROM_READ(TEMPER_EEPROM_ADR , &TestBuf, 256);// читаем и оределяем указатель
     //свободного  места в EEPROM[128] под параметры ВРЕМЕНИ, с учетов общего выделенного места и
     //размером массива TIME_RESERVE

#ifndef  DEBUG_Start_Boot_for_TEMPER
    for(i = 0; i < lengthTestBuf; i++)
                           {
    PRINT("%hu ", TestBuf[i]);
                            }
    PRINT("\n");
#endif
              }
//------------------------------------------------------------------------------------------------------//

 //2.//  анализ считаного и указателя  свободной/ занятой памяти
    a=0;  // control breakpoint
    BUSY_MEMORY_ADR=0;
    i = 0;

    for(i = 0; i < TEMPER_Copy_N ; i++)// анализируем очередь прочитанных указателей для каждого массива "ВРЕМЕНИ"       {
    {
     //  PRINT(" %hu ", (i*TR_N)+1);
     //  PRINT(" %hu ", TestBuf[(i*TR_N)]+1);
    a=TestBuf[(i*TempR_N )+1];// +1 линейный сдвиг на первое стационарное слово из 2х байт = 0x55AA;

    if (a!=0xFFFF)
       {
    BUSY_MEMORY_ADR++; // control breakpoint
       }

       }

#ifndef  DEBUG_Start_Boot_for_TEMPER
    PRINT("\n");//control breakpoint
    PRINT(" BUSY_MEMORY_ADR         ----------------------------------->>     = %hu\n",BUSY_MEMORY_ADR-1);
#endif


    if((BUSY_MEMORY_ADR<=TEMPER_Copy_N )&(BUSY_MEMORY_ADR>0))// если свободный указатель доступен из выделенного максимума памяти
    {

    FREE_MEMORY_ADR=BUSY_MEMORY_ADR; // то определяем текущую сободную память

#ifndef  DEBUG_Start_Boot_for_TEMPER
    PRINT(" 0 + FREE_MEMORY_ADR   ----------------------------------->>     = %hu\n",FREE_MEMORY_ADR);
#endif
         }
    else {


    if(BUSY_MEMORY_ADR==0)
       {

#ifndef  DEBUG_Start_Boot_for_TEMPER
    PRINT(" BUSY_MEMORY_ADR         ----------------------------------->>     = %hu\n",BUSY_MEMORY_ADR-1);
    PRINT(" 0 + FREE_MEMORY_ADR     ----------------------------------->>     = %hu\n",FREE_MEMORY_ADR);
#endif
   //------------------------------------------- DEBUG -------------------------------------------//

#ifndef  DEBUG_Start_Boot_for_TEMPER
    PRINT("EEPROM_READ... \n");
#endif
    EEPROM_READ(TEMPER_EEPROM_ADR, TestBuf,  lengthTestBuf*2);

#ifndef  DEBUG_Start_Boot_for_TEMPER
    for(i = 0; i < lengthTestBuf; i++)
         {
    PRINT("%hu ", TestBuf[i]);
         }
    PRINT("\n");
#endif
         //------------------------------------------- END OFF DEBUG -------------------------------------------//

     }

     }

     LAST_MEMORY_ADR=FREE_MEMORY_ADR-1 ;

     b=LAST_MEMORY_ADR * TempR_N* 2;//

     b= b+ TEMPER_RESERVE_6_BASE_ADR;// + линейный сдвиг на первое стационарное слово из 2х байт

    //после определения указателя занятого/свободного флеш читаем его содержимое в массив для RTC - TIME_RESERVE[TRN]

#ifndef  DEBUG_Start_Boot_for_TEMPER
     PRINT(" FREE_MEMORY_ADR* TR_N*2 + 2    %hu ",  b);
     PRINT("\n");
     PRINT("\n");
#endif
     s= EEPROM_READ( b  , &TEMPER_RESERVE, TempR_N*2);//читаем контрольно записанный  TIME_RESERVE из EEPROM

#ifndef  DEBUG_Start_Boot_for_TEMPER
     for(i = 0; i < TempR_N; i++)
        {
     PRINT(" %hu ", TEMPER_RESERVE[0]);

        }
     PRINT("\n");
     PRINT("\n");
#endif


     setup_temp =TEMPER_RESERVE[0];// прочитали последнее пересохраненное значение температуры ЗАДАНИЯ


//---------------------------------------------------------------------------------------------------------------//



         if(py!=2020)
     //    if(TEMPER_RESERVE[6]==0x5555)

  //  if((TIME_RESERVE[6]==0x5555)||(py!=2020))  //без флага обновления WRITE RTC ON SLEEP - часы получают левые данные - все зависает
   // после первого RESET без WRITE RTC ON SLEEP !!
       {
//    py   = TIME_RESERVE[0];
//    pmon = TIME_RESERVE[1];
//    pd   = TIME_RESERVE[2];
//    ph   = TIME_RESERVE[3];
//    pm   = TIME_RESERVE[4];
//    ps   = TIME_RESERVE[5];

    //     py   =  2023;//py;
    //     pmon =  1;//pmon;
    //     pd   =  1;//pd;
    //     ph   =  0;//ph;
    //     pm   =  0;//pm;
    //     ps   =  0;//ps




  //  RTC_InitTime(py, pmon, pd, ph, pm, ps);


    }else

    {// если произошел  системный или HARD сбой в RTC - то сбрасываем часы RTC на заводскую настройку
     // следующее сохранение времени будет после удачной работы RTC+ BAT+ WRITE RTC ON SLEEP прик отключении питания
     // во всех остальных случаях нет особого смысла периодически обновлять время в EEPROM, иначе оно будет сдвигатся
     //при следующем старте RESET, что не есть актуально для пользователя

//#ifndef  DEBUG_Start_Boot_for_System
     PRINT("\n");
    // PRINT("  RTC CLOCK WRITE ERROR !!!  =%hu\n",  Time_Write);
    // PRINT("  RTC CLOCK WRITE ERROR !!!  =%hu\n",  Time_Write);

     PRINT("  WRITE Boot_for_TEMPER  \n");

     PRINT("\n");
//#endif
 //       py   = TIME_RESERVE[0];
 //       pmon = TIME_RESERVE[1];
 //       pd   = TIME_RESERVE[2];
 //       ph   = TIME_RESERVE[3];
 //       pm   = TIME_RESERVE[4];
//        ps   = TIME_RESERVE[5];


 //    PRINT("\n");
 //    PRINT(" Time_Write=0xAAAA  OK=%02x\n",Time_Write);
 //    PRINT("\n");
  //             py   =  2024;//py;
  //             pmon =  1;//pmon;
 //              pd   =  1;//pd;
  //             ph   =  0;//ph;
  //             pm   =  0;//pm;
  //             ps   =  0;//ps


  //   RTC_InitTime(py, pmon, pd, ph, pm, ps);

    }



#ifndef  DEBUG_Start_Boot_for_TEMPER
         printf("--      \n");
         DelayMs(5);// задержка для очистки мусора гипертерминала  перед  GPIOA_ModeCfg(bTXD1, GPIO_ModeIN_PD)
         GPIOB_ModeCfg(bTXD1, GPIO_ModeIN_PD);
#endif


}


void    Start_Boot_for_Time(void)
{

static unsigned short a,b,c,d,i,s,ERROR,rewrite,BUSY_MEMORY_ADR, FREE_MEMORY_ADR,LAST_MEMORY_ADR;
static unsigned short BUFF_TIME_RESERVE[TR_N];// буфер для контрольной копии массива времени TIME_RESERVE
static unsigned short Time_Copy_Pointer[Time_Copy_N];

a=0,b=0,c=0,d=0,i=0,s=0,ERROR=0,rewrite=0,BUSY_MEMORY_ADR=0, FREE_MEMORY_ADR=0,LAST_MEMORY_ADR=0;

//#define   DEBUG_Start_Boot_for_TIME
#ifndef  DEBUG_Start_Boot_for_TIME
         GPIOA_SetBits(bTXD1);
         GPIOA_ModeCfg(bTXD1, GPIO_ModeOut_PP_5mA);
#endif

         RTC_GetTime( &py,&pmon,&pd,&ph,&pm,& ps);// ОБЯЗАТЕЛЬНО ПРОЧИТАТЬ ТЕКУЩЕЕ ВРЕМЯ ПОСЛЕ RESET!!!!
         // иначе функция  RTC_InitTime(py, pmon, pd, ph, pm, ps); //запишет  везде "0" !!


#ifndef  DEBUG_Start_Boot_for_TIME
    PRINT("EEPROM_READ... \n");
#endif

    //---------------------------------------читаем копируем обратно последнее сохраненное время---------------------//

 //1.
    s= EEPROM_READ(BASE_EEPROM_ADR , &TestBuf, 256);// читаем и оределяем указатель
    //свободного  места в EEPROM[128] под параметры ВРЕМЕНИ, с учетов общего выделенного места и
    //размером массива TIME_RESERVE

    a=TestBuf[0];

#ifndef  DEBUG_Start_Boot_for_TIME
    for(i = 0; i < lengthTestBuf; i++)
                          {
    PRINT("%hu ", TestBuf[i]);
                           }
    PRINT("\n");
#endif

 //-----------------------------------------------------------------------------------------------------//

    if((a!= 0x55AA))// если нет стартового слова!! (или испорчено или первый раз)
              {

    s = EEPROM_ERASE(BASE_EEPROM_ADR, EEPROM_MIN_ER_SIZE);// стираем принудительно всю страницу  в 256  байт
#ifndef  DEBUG_Start_Boot_for_TIME
    PRINT("EEPROM_ERASE   OK=%02x\n",s);
#endif
    TestBuf[0] = 0x55AA;// записываем стартовое слово в начало страницы

    s=  EEPROM_WRITE(BASE_EEPROM_ADR , &TestBuf, 2); // записываем первый 16 бит (2байта) стартовый регистр
#ifndef  DEBUG_Start_Boot_for_TIME
    PRINT("EEPROM_WRITE BOOT  OK=%02x\n",s);
#endif
 //--------------------------------------------------------------------------------------------------------------//
    py   =  2021;//py;
    pmon =  1;//pmon;
    pd   =  1;//pd;
    ph   =  0;//ph;
    pm   =  0;//pm;
    ps   =  0;//ps

    TIME_RESERVE[0]= py;
    TIME_RESERVE[1]= pmon;
    TIME_RESERVE[2]= pd;
    TIME_RESERVE[3]= ph;
    TIME_RESERVE[4]= pm;
    TIME_RESERVE[5]= ps;
    TIME_RESERVE[6]= 0xAAAA; // стартовая маска НЕ ОБНОВЛЕННАЯ SLEP / WRITE

    s=  EEPROM_WRITE(BASE_EEPROM_ADR+2 , &TIME_RESERVE, 14); // инициализируем время "заводскими настройками"
#ifndef  DEBUG_Start_Boot_for_TIME
    PRINT("EEPROM_WRITE START TIME OK=%02x\n",s);
#endif
 //--------------------------------контрольное считывание и вывод--------------------------------------//
    s= EEPROM_READ(BASE_EEPROM_ADR , &TestBuf, 256);// читаем и оределяем указатель
     //свободного  места в EEPROM[128] под параметры ВРЕМЕНИ, с учетов общего выделенного места и
     //размером массива TIME_RESERVE
#ifndef  DEBUG_Start_Boot_for_TIME
    for(i = 0; i < lengthTestBuf; i++)
                           {
    PRINT("%hu ", TestBuf[i]);
                            }
    PRINT("\n");
#endif
              }
//------------------------------------------------------------------------------------------------------//

 //2.//  анализ считаного и указателя  свободной/ занятой памяти
    a=0;  // control breakpoint
    BUSY_MEMORY_ADR=0;
    i = 0;

    for(i = 0; i < Time_Copy_N; i++)// анализируем очередь прочитанных указателей для каждого массива "ВРЕМЕНИ"       {
    {
     //  PRINT(" %hu ", (i*TR_N)+1);
     //  PRINT(" %hu ", TestBuf[(i*TR_N)]+1);
    a=TestBuf[(i*TR_N)+1];// +1 линейный сдвиг на первое стационарное слово из 2х байт = 0x55AA;

    if (a!=0xFFFF)
       {
    BUSY_MEMORY_ADR++; // control breakpoint
       }

       }
#ifndef  DEBUG_Start_Boot_for_TIME
    PRINT("\n");//control breakpoint
    PRINT(" BUSY_MEMORY_ADR         ----------------------------------->>     = %hu\n",BUSY_MEMORY_ADR-1);
    PRINT("\n");
#endif


    if((BUSY_MEMORY_ADR<=Time_Copy_N)&(BUSY_MEMORY_ADR>0))// если свободный указатель доступен из выделенного максимума памяти
    {

    FREE_MEMORY_ADR=BUSY_MEMORY_ADR; // то определяем текущую сободную память
#ifndef  DEBUG_Start_Boot_for_TIME
    PRINT(" 0 + FREE_MEMORY_ADR   ----------------------------------->>     = %hu\n",FREE_MEMORY_ADR);
#endif
         }
    else {


    if(BUSY_MEMORY_ADR==0)
       {
#ifndef  DEBUG_Start_Boot_for_TIME
    PRINT(" BUSY_MEMORY_ADR         ----------------------------------->>     = %hu\n",BUSY_MEMORY_ADR-1);
    PRINT(" 0 + FREE_MEMORY_ADR     ----------------------------------->>     = %hu\n",FREE_MEMORY_ADR);
#endif
   //------------------------------------------- DEBUG -------------------------------------------//
#ifndef  DEBUG_Start_Boot_for_TIME
    PRINT("EEPROM_READ... \n");
#endif
    EEPROM_READ(BASE_EEPROM_ADR, TestBuf,  lengthTestBuf*2);
#ifndef  DEBUG_Start_Boot_for_TIME
    for(i = 0; i < lengthTestBuf; i++)
         {
    PRINT("%hu ", TestBuf[i]);
         }
    PRINT("\n");
#endif
         //------------------------------------------- END OFF DEBUG -------------------------------------------//

     }

     }

     LAST_MEMORY_ADR=FREE_MEMORY_ADR-1 ;

     b=LAST_MEMORY_ADR * TR_N * 2;//

     b= b+ TIME_RESERVE_6_BASE_ADR;// + линейный сдвиг на первое стационарное слово из 2х байт

    //после определения указателя занятого/свободного флеш читаем его содержимое в массив для RTC - TIME_RESERVE[TRN]
#ifndef  DEBUG_Start_Boot_for_TIME
     PRINT(" FREE_MEMORY_ADR* TR_N*2 + 2    %hu ",  b);
     PRINT("\n");
     PRINT("\n");
#endif
     s= EEPROM_READ( b  , &TIME_RESERVE, TR_N*2);//читаем контрольно записанный  TIME_RESERVE из EEPROM

#ifndef  DEBUG_Start_Boot_for_TIME
     for(i = 0; i < TR_N; i++)
        {
     PRINT(" %hu ", TIME_RESERVE[i]);

        }
     PRINT("\n");
     PRINT("\n");
#endif


//---------------------------------------------------------------------------------------------------------------//

#ifndef  DEBUG_Start_Boot_for_TIME
 //       printf("\n");
 //       printf( " TIME ON START \n");
 //       printf( "%d year %d month %d day %d hour %d minute %d second  \n" ,py,pmon,pd,ph,pm,ps);
 //       printf("\n");
#endif


         //if(py!=2020)
         if(TIME_RESERVE[6]==0x5555)

  //  if((TIME_RESERVE[6]==0x5555)||(py!=2020))  //без флага обновления WRITE RTC ON SLEEP - часы получают левые данные - все зависает
   // после первого RESET без WRITE RTC ON SLEEP !!
       {
//    py   = TIME_RESERVE[0];
//    pmon = TIME_RESERVE[1];
//    pd   = TIME_RESERVE[2];
//    ph   = TIME_RESERVE[3];
//    pm   = TIME_RESERVE[4];
//    ps   = TIME_RESERVE[5];

    //     py   =  2023;//py;
    //     pmon =  1;//pmon;
    //     pd   =  1;//pd;
    //     ph   =  0;//ph;
    //     pm   =  0;//pm;
    //     ps   =  0;//ps




 //   RTC_InitTime(py, pmon, pd, ph, pm, ps);


    }else

    {// если произошел  системный или HARD сбой в RTC - то сбрасываем часы RTC на заводскую настройку
     // следующее сохранение времени будет после удачной работы RTC+ BAT+ WRITE RTC ON SLEEP прик отключении питания
     // во всех остальных случаях нет особого смысла периодически обновлять время в EEPROM, иначе оно будет сдвигатся
     //при следующем старте RESET, что не есть актуально для пользователя
#ifndef  DEBUG_Start_Boot_for_TIME
     PRINT("\n");
     PRINT("  RTC CLOCK WRITE ERROR !!!  =%hu\n",  Time_Write);
     PRINT("  RTC CLOCK WRITE ERROR !!!  =%hu\n",  Time_Write);
     PRINT("\n");
#endif
 //       py   = TIME_RESERVE[0];
 //       pmon = TIME_RESERVE[1];
 //       pd   = TIME_RESERVE[2];
 //       ph   = TIME_RESERVE[3];
 //       pm   = TIME_RESERVE[4];
//        ps   = TIME_RESERVE[5];


 //    PRINT("\n");
 //    PRINT(" Time_Write=0xAAAA  OK=%02x\n",Time_Write);
 //    PRINT("\n");
  //             py   =  2024;//py;
  //             pmon =  1;//pmon;
 //              pd   =  1;//pd;
  //             ph   =  0;//ph;
  //             pm   =  0;//pm;
  //             ps   =  0;//ps


//     RTC_InitTime(py, pmon, pd, ph, pm, ps);

    }

#ifndef  DEBUG_Start_Boot_for_TIME
     GPIOA_SetBits(bTXD1);
     GPIOA_ModeCfg(bTXD1, GPIO_ModeOut_PP_5mA);
#endif

}





void hard_faile_reset(uint8 faill)// повторная инициализация всего без апаратного RESET
{
//#define GAPRole_Periph_Init
//#define BLE_Phone_Connect
#define Sleep_ResetExecute

    if(faill==5)
    {
        ble_reset=0;

      if(SleepStop==2)//первый проход
        {
#ifdef GAPRole_Periph_Init
          GAPRole_PeripheralInit();//обязательно вызвается только эта строчка после спячки
          PRINT(" ------------------->>   event_RTC_sleep            =%d\r\n", SleepStop);
          PRINT(" ------------------->>   GAPRole_PeripheralInit()   =%d\r\n", SleepStop);
#endif

#ifdef   BLE_Phone_Connect
         Peripheral_Init();// мешает при сбросе хода без первичного BLE соединения и путает картину
         //для жесткой отладки без первичного соединения лучше убирать в обоих местах /и или добавлять
         // но обеспечивает первое соединение с телефоном что бы работало жестко в цикле - нужно убирать
         PRINT(" ------------------->>   event_RTC_sleep            =%d\r\n", SleepStop);
         PRINT(" ------------------->>   Peripheral_Init()          =%d\r\n", SleepStop);
#endif

//-----------------------------------------------------------------------------------------------------------

         event_GPIO_scan=0;
         soft_block=0;
         start_key_timer =0;// остановили локальный таймер задержки  после первого срабатывания INT GPIO
         GPIOA_ClearITFlagBit(GPIO_Pin_1);
         PFIC_DisableIRQ(GPIO_A_IRQn);
   //      GPIOA_ModeCfg(GPIO_Pin_1, GPIO_ModeIN_Floating);// под пин POWER OFF/ON
   //      GPIOA_ITModeCfg(GPIO_Pin_1, GPIO_ITMode_FallEdge); // работает и по уровню и по фронту, только по


         //init_LCD();//
         //DelayMs(100);
      }

      if(SleepStop==1)    //второй  проход
      {

#ifdef GAPRole_Periph_Init
       GAPRole_PeripheralInit();//обязательно вызвается только эта строчка после спячки
       PRINT(" ------------------->>  event_RTC_sleep              =%d\r\n", SleepStop);
       PRINT(" ------------------->>  GAPRole_PeripheralInit() 22     =%d\r\n", SleepStop);
#endif

#ifdef BLE_Phone_Connect
       Peripheral_Init();// мешает при сбросе хода без первичного BLE соединения и путает картину


    // для жесткой отладки без первичного соединения лучше убирать в обоих местах /и или добавлять
    // но обеспечивает первое соединение с телефоном что бы работало жестко в цикле - нужно убирать
#endif
   //PRINT(" ------------------->>  event_RTC_sleep              =%d\r\n", SleepStop);
   //PRINT(" ------------------->>  Peripheral_Init()            =%d\r\n", SleepStop);
//---------------------------------------------------------------------------------------------------------//
   //PRINT("  Task3_count FOR CONNECT  =%02d\n", Task3_count);
  //tmos_start_task( task3 , sub_event_1 ,1.6*1.0 );

//---------------------------- восстанавливаем работу LCD после сна ---------------------------------//

   //PFIC_DisableIRQ(TMR0_IRQn);// разрешаем прерывания  от ТАЙМЕРА0 LCD
   //clear_screen();
   //init_LCD();//
   //DelayMs(1000);
   //PFIC_EnableIRQ(TMR0_IRQn);// разрешаем прерывания  от ТАЙМЕРА0 LCD

//---------------------------------------------------------------------------------------------------//
    PRINT("\n");
    PRINT(" ------------------->>        READY  AFTER  SLEEP         ");

//---------------------------------------------------------------------------------------------------//
    event_GPIO_scan=0;
    soft_block=0;
    start_key_timer =0;// остановили локальный таймер задержки  после первого срабатывания INT GPIO
    GPIOA_ClearITFlagBit(GPIO_Pin_1);
    PFIC_DisableIRQ(GPIO_A_IRQn);
 //   GPIOA_ModeCfg(GPIO_Pin_1, GPIO_ModeIN_Floating);// под пин POWER OFF/ON
 //   GPIOA_ITModeCfg(GPIO_Pin_1, GPIO_ITMode_FallEdge); // работает и по уровню и по фронту, только по уровню идет


#ifdef   Sleep_ResetExecute

    PRINT("\n");
    PRINT(" ------------------->>         SYS_ResetExecute  !!!!!        ");
    PRINT("\n");
    PRINT("\n");
    SYS_ResetExecute();//      FULL  RESET CH582 !!
                       //нужна запись в память перед апаратной перезагрузкой   !!!!!!!
#endif

    }
  //-- работает только как тест на сквозняк "без слипа", соединение можно восстановить программно
  // у нас слетает GAAT STATUS без HARD RESET  - 133 - Ошибка
    //PRINT(" ------------------->>   Hard_Faile_Reset             =%d\r\n", faill);
    //PRINT(" ------------------->>   Task3_ COUNT                 =%d\r\n", Task3_count);
    }

// Тест вызова прямого/ косвенно управления небходимого Task !!!
// аналогичный тест см. в функции прямого цикла app_uart_process(); !!!

   // if (event_RTC>5) // 1 раз в 2 секунду
   //  if (event_RTC>0)// 1 раз в секунду
   // {

      // для наглядности  нужно -> (event_RTC>5) с дальнейшим сбросом   event_RTC=0;
      //  event_RTC=0;

     // косвенное  управление  через постоянный опросный  цикл Task1_2
     //  Task3_1=Reload_Task;//сбросили и перезагрузили  Task3_1

     //прямое управление через функцию в освном цикле While
     //  tmos_start_reload_task( task3 , sub_event_1 ,1.6*1.0* start_task_delay);

     //  Вывод: управление напрямую производится , только если крутимся в функции , которя в свою
     //  очередь крутиться основном While цикле
     // иначе управление косвенное с помощью вспомогательных команд/флагов или сообщений
     // которые в свою очередь, вызывают в теле заригистрированной задачи непосредственно
     // необходимый конкретный вызов типа   Reload_Task, StopTask,Starttask!!!

       // ВНИМАНИЕ !!! управление также не производится при ошибочном цикличном повторе операции

      // Необходимо:
      // событие-> управление Task = правильно управление передается
      // событие->событие->  управление Task = НЕ  правильно управление передается

      // на одно собыйтие идет четко один вызов управления задачей!!!!
      // это нужно контролировать как при прямом так и косвенном вызове /управлении задачами
      // (передача сообщений производится только по событиям , без ошибочных повторных сообщений(команд)


   // }


}


void    Sleep_Start_Time_Write(void)
{

#define    Sleep_ON


      GPIOB_SetBits(bTXD1);
      GPIOB_ModeCfg(bTXD1, GPIO_ModeOut_PP_5mA);

 //----------------------------------DISABLE ANALOG PIN POWER--------------------------------------//

  //       GPIOB_ModeCfg(GPIO_Pin_11, GPIO_ModeOut_PP_20mA);//отладочный пин под осцилограф
         //DelayUs(1);
  //       GPIOB_ResetBits(GPIO_Pin_11);// инверсия для віхода осцилограф - индикация времени цикла


      event_RTC2=2;//блокируем обмен с HLW8110
      PFIC_DisableIRQ(TMR0_IRQn);// запрещаем прерывания  от ТАЙМЕРА0 LCD
      TMR0_ITCfg( DISABLE, TMR0_3_IT_CYC_END);

      UART1_INTCfg(DISABLE, RB_IER_RECV_RDY | RB_IER_LINE_STAT);
      PFIC_DisableIRQ(UART1_IRQn);//PFIC_DisableIRQ

      tmos_stop_task( task1, sub_event_1 );
      tmos_stop_task( task1, sub_event_2 );
      tmos_stop_task( task1, sub_event_1 );
      tmos_stop_task( task1, sub_event_2 );
      tmos_stop_task( task3 ,sub_event_1 );
      tmos_stop_task( task3 ,sub_event_2 );


  //----------------------------- END OFF  стирание EEPROM--------------------------------//

      PRINT(" -- \n");
      PRINT(" -- \n");
      printf( " event_RTC_sleep ON SLEEP  =  %ld \n" ,event_RTC_sleep);
      PRINT(" sleep mode sleep     \r\n");
      PRINT(" -- \n");
      PRINT(" -- \n");



    //----------------переконфигурация всех нужных пинов для спячки-------------------------//
    // -------в момент пробуждения , обратно перенастраиваем нужные пины--------------------//

    // DelayMs(80);
      GPIOA_ModeCfg(GPIO_Pin_All, GPIO_ModeIN_PD);
      GPIOB_ModeCfg(GPIO_Pin_All, GPIO_ModeIN_PD);
      PFIC_DisableIRQ(TMR0_IRQn);// запрещаем прерывания  от ТАЙМЕРА0 LCD
      GPIOA_ClearITFlagBit(GPIO_Pin_1);
      PFIC_DisableIRQ(GPIO_A_IRQn);//
     // DelayMs(50);// !!! антидребезг для успакаивания спада на линиии power ON/Off. напряжение питания делителя power ON/Off 3,5 B-3.9

     //   DelayMs(500);


     //задержк от 50 до 80 на выбранной частоте реально нужна!!!
      // или бывает уходит почему то в неопределенное состояние!!


      //сюда еще можно вставить контрольное измерение уровня напряжения вместо "тупой " длительной задержки.

     // как только  напряжение == 0 то засыпаем, иначе переконфигрурируем пин в начально положение и ждем второй раз
      // срабатывания прерывания....
      //таким образом можно сделать "задержка" + "контрольное измерение" -> sleep , иначе выходим из процедуры без засыпания
      //это нужно отлаживать на рабочем приборе с конкретной PCB !!! и с нагрузкой в сети итд..
      // Программная защита от помех в сети или ложного срабатывания.
      // можно делать контрольное проспание и измерение через 5 сек после первого засыпания
      // если измеренное значение будет 0 то спин, иначе ложно и просыпаемся.

      // защита от ложного Reset...имхо смотреть пин внеший Reset.

      // сделать бструю зарядку через резистор + стабилитрон на 4,3 вольта поданый с линии +30 в прямо на ионистор..



#ifdef  sleep_test_by_RTC_TRIGFunCfg //  и отцепить проводок  POWER OFF/ON, инче жрет тока непомерно и все глючит!!
      RTC_TRIGFunCfg(RTC_TRIGFunCfg_Time);//32768тиков*60= 60 секунд, взвели таймер на "СБРОС" с данного момента
      GPIOA_ClearITFlagBit(GPIO_Pin_1);
      PFIC_DisableIRQ(GPIO_A_IRQn);//
      DelayMs(100);
      GPIOA_ModeCfg(GPIO_Pin_1, GPIO_ModeIN_PD);
      GPIOA_ITModeCfg(GPIO_Pin_1, GPIO_ITMode_HighLevel); // //вариант под клавиатуру GPIO INTA
#endif


#ifdef  sleep_test_by_Power_ON_OFF_PIN
      GPIOA_ModeCfg(GPIO_Pin_1, GPIO_ModeIN_Floating);
      GPIOA_ITModeCfg(GPIO_Pin_1, GPIO_ITMode_RiseEdge);// под пин POWER OFF/ON
      PWR_PeriphWakeUpCfg(ENABLE, RB_SLP_GPIO_WAKE, Long_Delay);// повторно включаем модуль проспания GPIO
      GPIOA_ClearITFlagBit(GPIO_Pin_1);
      //DelayMs(5);
      PFIC_EnableIRQ(GPIO_A_IRQn);
#endif

                if( SleepStop==1)
                   {

#ifdef Sleep_ON


      LowPower_Sleep(RB_PWR_RAM2K | RB_PWR_RAM30K | RB_PWR_EXTEND );
      HSECFG_Current(HSE_RCur_100);
      DelayMs(5);
#endif
                   };

    //-------------------------после возможного сна -----------------------------------


         tmos_set_event(task1, sub_event_1); // инициализируем  период и запуск задачи  task1/sub_event_1 и  стартуем
         tmos_set_event(task1, sub_event_2); // инициализируем  период и запуск задачи  task1/sub_event_2 и  стартуем
         tmos_set_event(task3, sub_event_1); // инициализируем  период и запуск задачи  task1/sub_event_3 и  стартуем
         tmos_set_event(task3, sub_event_2); // инициализируем  период и запуск задачи  task1/sub_event_3 и  стартуем



      GPIOB_SetBits(bTXD1);
      GPIOB_ModeCfg(bTXD1, GPIO_ModeOut_PP_5mA);
      DelayMs(5);

      RTC_GetTime( &py,&pmon,&pd,&ph,&pm,& ps);
     //  выводим значение времени и даты по каждому событию RTC
      PRINT( "event_RUN:-> " );
      PRINT( "%d year %d month %d day %d hour %d minute %d second " ,py,pmon,pd,ph,pm,ps);
      PRINT("\n");
      PRINT("\n");

     //--------------------------------ОБНОВЛЕНИЕ   EEPROM-----------------------------------//


 //     SCHEDULE_TO_FLASH();// на всякий случай сохраняем время во флеш  после сна и бутимся
 //     SYSTEM_TO_FLASH();

      // как оказывается, часы после Reset не слетают, если не делать принудительную повторную инициализацию
      // времени в HAL-> time setup !!!
      // столько трахался с сохранением времени во флеш..а оно и не обязательно, если не переобновлять принудительно
      // функию  Time init после reset
      // главное условие сохранения тика TRC - устойчивое физическое питание  на шине!!
      //  reset - не сбрасывает ход часов после sleep!!
      // таким образом можно безболезненно создавать любые профили и интервалы и впадать в SLEEP!!!!!



  //----------------------------------------------------------------------------------------------------------------------
      ble_reset=5;
      event_RTC_sleep=0;


}








