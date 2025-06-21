/********************************** (C) COPYRIGHT *******************************
* File Name          : directtest..h
* Author             : WCH
* Version            : V1.0
* Date               : 2018/12/11
* Description        :
*******************************************************************************/

#ifndef MY_DIRECTTEST_H
#define MY_DIRECTTEST_H

#ifdef __cplusplus
extern "C"
{
#endif



/*********************************************************************
 * FUNCTIONS
 */

extern void TEST_Init();

#define  TEST_EVENT    1


#define LED_PIN GPIO_Pin_15   // DI


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




/*******************************************************************************
 * @fn          API_LE_ReceiverTestCmd API
 *
 * @brief       used to start a test where the DUT generates test reference packets at a fixed interval
 *
 * input parameters
 *
 * @param       tx_channel - RF channel(0-39)
 *              len        - 测试数据包长度(1-255)
 *              payload    - 测试的数据类型(0-7),8种数据类型。
 *                           0：PRBS9       1：全部为0xF0  2：全部为0xAA  3：PRBS15
 *                           4：全部为0xFF  5：全部为0x00  6：全部为0x0F  7：全部为0x55
 *              tx_power   - bit0~5: 测试的发送功率（1-31）对应（-20dBM至5dBm）
 *                           bit7: 1-关白化(接入地址0x71764129);0-开白化(接入地址0x8E86BED9)
 *
 * output parameters
 *
 * @param       None
 *
 * @return      Command Status.
 *
 * Command Complete event
 */
//extern u8 API_LE_TransmitterTestCmd( u8 tx_channel, u8 len, u8 payload, u8 tx_power );

/*******************************************************************************
 * @fn          API_LE_TestEndCmd API
 *
 * @brief       used to stop any test which is in progress
 *
 * input parameters
 *
 * @param       None
 *
 * output parameters
 *
 * @param       None
 *
 * @return      Command Status.
 *
 * Command Complete event
 */
extern u8 API_LE_TestEndCmd( void  );


/*********************************************************************
*********************************************************************/

#ifdef __cplusplus
}
#endif

#endif
