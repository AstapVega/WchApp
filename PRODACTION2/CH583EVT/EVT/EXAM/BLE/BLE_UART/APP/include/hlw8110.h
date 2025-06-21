/*
 * hlw8110.h
 *
 *  Created on: Sep 26, 2023
 *      Author: Astap
 */

#ifndef _HLW8110_H_
#define _HLW8110_H_

#include "stdio.h"


//#define event_sleep_START                                10  // §Õ§Ý§ñ §ã§à§Ò§í§ä§Ú§ñ SLEEP
//extern unsigned char event_RTC_sleep; // §Õ§Ý§ñ §ã§à§Ò§í§ä§Ú§ñ SLEEP

//---------------------------for Judge_CheckSum_HLW8110_Calfactor_printf ---------------------------------
extern uint8_t A_ch_cur_conver_factor;
extern uint8_t Volt_ch_conver_factor;
extern uint8_t A_ch_pow_conver_factor;
extern uint8_t Appar_pow_conver_factor;
extern uint8_t A_ch_pow_conver_coeffic;
extern uint8_t Coefficient_checksum;
extern uint8_t Calcul_coeffic_checksum;
extern uint8_t Checksum_correct;
extern uint8_t Checksum_error;
//-------------------------- end Judge_CheckSum_HLW8110_Calfactor_printf ---------------------------------

//--------------------------- for Calculate_HLW8110_MeterData_printf ------------------------------------
extern uint8_t SysconReg_reg_written;
extern uint8_t SysconReg_reg_read_err;
extern uint8_t EmuconReg_reg_written;
extern uint8_t EmuconReg_reg_read_err;
extern uint8_t Emucon2Reg_reg_reg_written;
extern uint8_t Emucon2Reg_reg_read_error;

extern uint8_t A_ch_current_reg;
extern uint8_t Err_read_A_ch_curr_reg;
extern uint8_t Volt_ch_reg;
extern uint8_t Volt_ch_reg_read_err;
extern uint8_t A_ch_power_reg;
extern uint8_t Err_read_A_ch_power_reg;
extern uint8_t A_ch_active_power_reg;
extern uint8_t Err_read_A_ch_active_power_reg;
extern uint8_t HFCONST_const_reg;
extern uint8_t Err_read_HFCONST_const_reg;
extern uint8_t Ch_A_Linear_Freq_Reg;
extern uint8_t Err_read_A_ch_linear_freq_reg;
extern uint8_t A_Ch_Line_Phase_Angle_Reg;
extern uint8_t Err_in_A_ch_line_phase_angle_reg;
extern uint8_t Current_overrun_voltage;
extern uint8_t Current_hysteresis_voltage;
extern uint8_t A_ch_power_factor_reg;
extern uint8_t Err_read_A_ch_power_factor_reg;


//--------------------------  end Calculate_HLW8110_MeterData_printf ---------------------------------



extern uint8_t ij;
extern uint8_t count;

extern uint16_t count2;
extern uint16_t count3;
extern unsigned char  REC_length;
extern uint8_t len;

extern unsigned char u8_TxBuf[10];
extern unsigned char u8_RxBuf[10];
extern unsigned char u8_TX_Length;
extern unsigned char u8_RX_Length;
extern unsigned char u8_RX_Index;

/*---------------------------------------------------------------------------------------------------------*/
extern  unsigned int U16_RMSIAC_RegData; // A-channel current conversion factor
extern unsigned int U16_RMSIBC_RegData; // B-channel current conversion factor
extern unsigned int U16_RMSUC_RegData; // Voltage Channel Conversion Factor
extern unsigned int U16_PowerPAC_RegData; // A-channel power conversion factor
extern unsigned int U16_PowerPBC_RegData; // B-channel power conversion factor
extern unsigned int U16_PowerSC_RegData; // Apparent power conversion coefficient, if you select channel A, it is the apparent power conversion coefficient of channel A. Channel A and B can only choose one of the two.
extern unsigned int U16_EnergyAC_RegData; // A-channel active energy (quantity) conversion factor
extern unsigned int U16_EnergyBC_RegData; // A-channel active energy (quantity) conversion factor
extern unsigned int U16_CheckSUM_RegData; // CheckSum of the conversion factor
extern unsigned int U16_CheckSUM_Data; // Conversion coefficient calculated CheckSum

extern unsigned int U16_Check_SysconReg_Data;
extern unsigned int U16_Check_EmuconReg_Data;
extern unsigned int U16_Check_Emucon2Reg_Data;

/*---------------------------------------------------------------------------------------------------------*/

// IO Port Definition
#define LED0 PBout(5) // DS0
#define LED1 PEout(5) // DS1

// DC correction factor

//8112A channel or 8110 channel correction factor
#define D_CAL_U 1000/1000 // Voltage correction factor
#define D_CAL_A_I 1000/1000 // A channel current correction factor
#define D_CAL_A_P 1000/1000 //A channel power correction factor
#define D_CAL_A_E 1000/1000 // A-channel electrical energy correction factor

//8112 B-channel correction factor
#define D_CAL_B_P 1000/1000 //B channel power correction factor
#define D_CAL_B_I 1000/1000 // B channel current correction factor
#define D_CAL_B_E 1000/1000 // B-channel electrical energy correction factor


//8112/8110 reg define
#define REG_SYSCON_ADDR 0x00
#define REG_EMUCON_ADDR 0x01
#define REG_HFCONST_ADDR 0x02
#define REG_EMUCON2_ADDR 0x13
#define REG_ANGLE_ADDR 0x22 //Phase angle registers
#define REG_UFREQ_ADDR 0x23 // utility linear frequency address
#define REG_RMSIA_ADDR 0x24
#define REG_RMSIB_ADDR 0x25
#define REG_RMSU_ADDR 0x26
#define REG_PF_ADDR 0x27
#define REG_ENERGY_PA_ADDR 0x28
#define REG_ENERGY_PB_ADDR 0x29
#define REG_POWER_PA_ADDR 0x2C
#define REG_POWER_PB_ADDR 0x2D


#define REG_OVLVL_ADDR 0x19

#define REG_INT_ADDR 0x1D
#define REG_IE_ADDR 0x40
#define REG_IF_ADDR 0x41
#define REG_RIF_ADDR 0x42

#define REG_RDATA_ADDR 0x44

#define REG_CHECKSUM_ADDR 0x6f
#define REG_RMS_IAC_ADDR 0x70
#define REG_RMS_IBC_ADDR 0x71
#define REG_RMS_UC_ADDR 0x72
#define REG_POWER_PAC_ADDR 0x73
#define REG_POWER_PBC_ADDR 0x74
#define REG_POWER_SC_ADDR 0x75
#define REG_ENERGY_AC_ADDR 0x76
#define REG_ENERGY_BC_ADDR 0x77



#define D_TIME1_50MS 50


//void Init_HLW8110(void).
//void Calculate_HLW8110_MeterData(void).
//void Init_HLW8112(void).
//void HLW8112_Measure(void).


extern void Init_HLW8110(void);
extern void Calculate_HLW8110_MeterData(void);
extern void Uart_Read_HLW8110_Reg(unsigned char ADDR_Reg,unsigned char u8_reg_length);
extern char Receive_to_Bufer(unsigned char receive_data_length);
extern unsigned char HLW8110_checkSum_Read(unsigned char u8_Reg_length);

extern void Calculate_HLW8110_MeterData_printf(void);
extern void Judge_CheckSum_HLW8110_Calfactor_printf(void);

extern void UART1_DefInit1(void);
extern void UART1_DefInit2(void);

#endif /* SRC_HLW8110_H_ */
