/*
 * hlw8110.c
 *
 *  Created on: Sep 26, 2023
 *      Author: Astap
 */
#include "CONFIG.h"
#include "CH58x_common.h"
#include "hlw8110.h"
#include "stdio.h"
#include "my_assist32.h"
#include "ext_my_directtest.h"


#include "alex_board.h"

/*---------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------------------------*/
union IntData
{
    u16 inte;
    u8 byte[2];
};
union LongData
{
    u32 word;
    u16 inte[2];
    u8 byte[4];
};
/*---------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------------------------*/

uint8_t ij=0;
uint8_t count=0;
uint16_t count2=0;
uint8_t len=0;

unsigned char u8_TxBuf[10];
unsigned char u8_RxBuf[10];
unsigned char reciver_byte;
unsigned char chek_receive;

unsigned char u8_TX_Length;
unsigned char u8_RX_Length;
unsigned char u8_RX_Index;

//unsigned char B_ReadReg_Time_EN; // Serial read register data, time counter flag bit, 1 - turn on counting, 0 - turn off counting
//unsigned char B_Tx_Finish;
unsigned char B_Rx_Finish;
unsigned char B_Rx_Data_ING; // Receive data flag bit , < 1:Receiving data in progress, 0:Not receiving data>
unsigned char B_Read_Error; // UART read data checksum error,< 1:data read error,0:data read correctly >
//unsigned char u8_ReadReg_Index;
//unsigned char u8_ReadReg_Time; // The time when the serial port reads the register data.
/*---------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------------------------*/

unsigned int U16_TempData;

unsigned int U16_IFData;
unsigned int U16_RIFData;
unsigned int U16_LineFData;
unsigned int U16_AngleData;
unsigned int U16_PFData;
unsigned int U16_HFConst_RegData;
/*---------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------*/
unsigned int U16_RMSIAC_RegData; // A-channel current conversion factor
unsigned int U16_RMSIBC_RegData; // B-channel current conversion factor
unsigned int U16_RMSUC_RegData; // Voltage Channel Conversion Factor
unsigned int U16_PowerPAC_RegData; // A-channel power conversion factor
unsigned int U16_PowerPBC_RegData; // B-channel power conversion factor
unsigned int U16_PowerSC_RegData; // Apparent power conversion coefficient, if you select channel A, it is the apparent power conversion coefficient of channel A. Channel A and B can only choose one of the two.
unsigned int U16_EnergyAC_RegData; // A-channel active energy (quantity) conversion factor
unsigned int U16_EnergyBC_RegData; // A-channel active energy (quantity) conversion factor
unsigned int U16_CheckSUM_RegData; // CheckSum of the conversion factor
unsigned int U16_CheckSUM_Data; // Conversion coefficient calculated CheckSum

unsigned int U16_Check_SysconReg_Data;
unsigned int U16_Check_EmuconReg_Data;
unsigned int U16_Check_Emucon2Reg_Data;

/*---------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------------------------*/
unsigned long U32_RMSIA_RegData; // A-channel current RMS value register
unsigned long U32_RMSU_RegData; // Voltage RMSU register; // Voltage RMSU register; // Voltage RMSU register; // Voltage RMSU register.
unsigned long U32_POWERPA_RegData; // A-channel power RMS register
unsigned long U32_ENERGY_PA_RegData; // A-channel active power (quantity) effective value register

unsigned long U32_RMSIB_RegData; // B-channel current RMS value register
unsigned long U32_POWERPB_RegData; // B-channel power RMS value register
unsigned long U32_ENERGY_PB_RegData; // B-channel active energy (quantity) effective value register

unsigned long U32_Linear_Freq_Reg;
unsigned long U32_A_ch_Power_factor_Reg;
unsigned long U32_A_ch_Line_Phase_Angle_Reg;

float F_Current_overrun_voltage;
float F_Current_hysteresis_voltage;
/*---------------------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------------------------*/
float F_AC_V; // Voltage Effective Value
float F_AC_I; // A-channel current
float F_AC_P; // A-channel active power
float F_AC_E; // A-channel active energy (quantity)
float F_AC_BACKUP_E; // A-channel power back up
float F_AC_BACKUP_E_SUM=0; // A-channel power back up SUM ...накапливаем при сбросе HLW в пямяти К
float F_AC_BACKUP_E_ADD=0; // A-channel power back up SUM ...накапливаем при сбросе HLW в пямяти К
float F_AC_PF; // Power factor, only one of A and B channels can be selected.
float F_Angle; // phase angle, only one of A and B channels can be selected

float F_AC_I_B; // B-channel current rms value
float F_AC_P_B; // B channel active power
float F_AC_E_B; // B-channel active energy (quantity)
float F_AC_BACKUP_E_B; // B-channel power backup
float F_AC_LINE_Freq; // Utility Linear Frequency
/*---------------------------------------------------------------------------------------------------------*/

//---------------------------for Judge_CheckSum_HLW8110_Calfactor_printf ---------------------------------
uint8_t A_ch_cur_conver_factor;
uint8_t Volt_ch_conver_factor;
uint8_t A_ch_pow_conver_factor;
uint8_t Appar_pow_conver_factor;
uint8_t A_ch_pow_conver_coeffic;
uint8_t Coefficient_checksum;
uint8_t Calcul_coeffic_checksum;
uint8_t Checksum_correct;
uint8_t Checksum_error;
//-------------------------- end Judge_CheckSum_HLW8110_Calfactor_printf --------------------------------


//--------------------------- for Calculate_HLW8110_MeterData_printf ------------------------------------
uint8_t SysconReg_reg_written;
uint8_t SysconReg_reg_read_err;
uint8_t EmuconReg_reg_written;
uint8_t EmuconReg_reg_read_err;
uint8_t Emucon2Reg_reg_reg_written;
uint8_t Emucon2Reg_reg_read_error;

uint8_t A_ch_current_reg;
uint8_t Err_read_A_ch_curr_reg;
uint8_t Volt_ch_reg;
uint8_t Volt_ch_reg_read_err;
uint8_t A_ch_power_reg;
uint8_t Err_read_A_ch_power_reg;
uint8_t A_ch_active_power_reg;
uint8_t Err_read_A_ch_active_power_reg;
uint8_t HFCONST_const_reg;
uint8_t Err_read_HFCONST_const_reg;
uint8_t Ch_A_Linear_Freq_Reg;
uint8_t Err_read_A_ch_linear_freq_reg;
uint8_t A_Ch_Line_Phase_Angle_Reg;
uint8_t Err_in_A_ch_line_phase_angle_reg;
uint8_t Current_overrun_voltage;
uint8_t Current_hysteresis_voltage;
uint8_t A_ch_power_factor_reg;
uint8_t Err_read_A_ch_power_factor_reg;


//--------------------------  end Calculate_HLW8110_MeterData_printf ---------------------------------

void Uart_HLW8110_WriteREG_EN(void);
unsigned char HLW8110_checkSum_Read(unsigned char u8_Reg_length);
unsigned char HLW8110_checkSum_Write(unsigned char u8_Reg_length);
void Start_Send_UartData(unsigned char len);
void Uart_HLW8110_Set_Channel_A(void);
void Clear_RxBuf(void);
void Uart_Read_HLW8110_Reg(unsigned char ADDR_Reg,unsigned char u8_reg_length);
void Uart_Write_HLW8110_Reg(unsigned char ADDR_Reg,unsigned char u8_reg_length,unsigned long u32_data);
void Uart_HLW8110_WriteREG_DIS(void);
void Uart_HLW8110_Reset(void);
char Receive_to_Bufer(unsigned char receive_data_length);
void Init_HLW8110(void);
void Check_WriteReg_Success(void);
void Read_HLW8110_IA(void);
void Read_HLW8110_U(void);
void Read_HLW8110_PA(void);
void Read_HLW8110_EA(void);
void Read_HLW8110_LineFreq(void);
void Read_HLW8110_PF(void);
void Read_HLW8110_Angle(void);

void Calculate_HLW8110_MeterData(void);
void Calculate_HLW8110_MeterData_printf(void);
unsigned char Judge_CheckSum_HLW8110_Calfactor(void);
void Judge_CheckSum_HLW8110_Calfactor_printf(void);

void UART1_DefInit1(void);
void UART1_DefInit2(void);

void UART1_DefInit1(void)
{

    UART1_BaudRateCfg(9600);
    R8_UART1_FCR = (2 << 6) | RB_FCR_TX_FIFO_CLR | RB_FCR_RX_FIFO_CLR | RB_FCR_FIFO_EN; // FIFO打开，触发点4字节
    R8_UART1_LCR = RB_LCR_WORD_SZ|RB_LCR_PAR_EN | RB_LCR_PAR_MOD;
    R8_UART1_IER = RB_IER_TXD_EN;
    R8_UART1_DIV = 1;

}


void UART1_DefInit2(void)
{

     UART1_BaudRateCfg(256000);
     //UART1_BaudRateCfg(115200);

     R8_UART1_FCR = (2 << 6) | RB_FCR_TX_FIFO_CLR | RB_FCR_RX_FIFO_CLR | RB_FCR_FIFO_EN; // FIFO打开，触发点4字节
     R8_UART1_LCR = RB_LCR_WORD_SZ;
     R8_UART1_IER = RB_IER_TXD_EN;
     R8_UART1_DIV = 1;


}

/*=========================================================================================================
 * Function : void Uart_HLW8110_WriteREG_EN(void)
 * Describe :
 * Input    : none
 * Output   : none
 * Return   : none
 * Record   : 2019/04/03
==========================================================================================================*/
void Uart_HLW8110_WriteREG_EN(void)
{

    u8_TX_Length = 4;
    u8_RX_Length = 0;

    u8_TxBuf[0] = 0xa5;
    u8_TxBuf[1] = 0xea;
    u8_TxBuf[2] = 0xe5;
//  u8_TxBuf[3] = 0x8b;  //checksum
    u8_TxBuf[3] = HLW8110_checkSum_Write(u8_TX_Length);

    Start_Send_UartData(u8_TX_Length);

}

/*=========================================================================================================
 * Function : unsigned char HLW8110_checkSum_Read(void)
 * Describe :
 * Input    : none
 * Output   : none
 * Return   : none
 * Record   : 2019/04/03
==========================================================================================================*/
unsigned char HLW8110_checkSum_Read(unsigned char u8_Reg_length)
{
    unsigned char i;
    unsigned char Temp_u8_checksum;
    unsigned int a;

    a = 0x0000;
    Temp_u8_checksum = 0;
    for (i = 0; i< (u8_Reg_length-1); i++)
        {
            a += u8_RxBuf[i];
        }

    a = a + u8_TxBuf[0] + u8_TxBuf[1];
    a = ~a;

    Temp_u8_checksum = a & 0xff;

    return Temp_u8_checksum;

}
/*=========================================================================================================
 * Function : unsigned char HLW8110_checkSum_Write(unsigned char u8_Reg_length)
 * Describe :
 * Input    : none
 * Output   : none
 * Return   : none
 * Record   : 2019/04/03
=========================================================================================================*/
unsigned char HLW8110_checkSum_Write(unsigned char u8_Reg_length)
{
    unsigned char i;
    unsigned char Temp_u8_checksum;
    unsigned int    a;

    a = 0x0000;
    Temp_u8_checksum = 0;
    for (i = 0; i< (u8_Reg_length-1); i++)
        {
            a += u8_TxBuf[i];
        }

    a = ~a;
    Temp_u8_checksum = a & 0xff;

    return Temp_u8_checksum;

}

/*=========================================================================================================
 * Function : void Start_Send_UartData(unsigned char len)
 * :: Describe : UART2 serial port sends data
 * Input : none
 * Output : none
 * Return : none
 * Record : 2019/04/16

=========================================================================================================*/

void Start_Send_UartData(unsigned char len)
{
    unsigned char i;

  //  printf( " event_RTC_sleep ON TX  =  %ld \n" ,event_RTC_sleep);
 //   printf( "----  \n");


  //  if(event_RTC_sleep!=event_sleep_START)//если не сработал Sleep
  //  {

    UART1_DefInit1();

   // /*

    for(i=0;i<len;i++)
    {

        DelayUs(50); //add delay between two bytes

        UART1_SendByte(u8_TxBuf[i]);

    }

//*/

  //  }



}

/*=========================================================================================================
 * Function : void Uart_HLW8110_Set_Channel_A(void)
 * Describe :
 * Input    : none
 * Output   : none
 * Return   : none
 * Record   : 2019/04/03
==========================================================================================================*/
void Uart_HLW8110_Set_Channel_A(void)
{
    u8_TX_Length = 4;
    u8_RX_Length = 0;

    u8_TxBuf[0] = 0xa5;
    u8_TxBuf[1] = 0xea;
    u8_TxBuf[2] = 0x5a;
//  u8_TxBuf[3] = 0x16;  //checksum
    u8_TxBuf[3] = HLW8110_checkSum_Write(u8_TX_Length);

    Start_Send_UartData(u8_TX_Length);
}




/*=========================================================================================================
 * Function : void Clear_RxBuf(void)
 * :: Describe : clear the receive buffer before preparing to receive serial port data
 * Input : none
 * Output : none
 * Return : none

=========================================================================================================*/
void Clear_RxBuf(void)
{
    unsigned char i;

    ij=0;//очистка указателя в прерівании

    for(i = 0;i<10;i++)
    {
        u8_RxBuf[i] = 0x00;
    }

    B_Rx_Data_ING = 0;
    B_Rx_Finish = FALSE;
    u8_RX_Index = 0;
}


/*=========================================================================================================
 * Function : void Uart_Read_HLW8110_Reg(unsigned char ADDR_Reg,unsigned char u8_reg_length)
 * Describe :
 * Input    :
 * Output   :
 * Return   :
 * Record   : 2019/04/04
==========================================================================================================*/
void Uart_Read_HLW8110_Reg(unsigned char ADDR_Reg,unsigned char u8_reg_length)
{
    u8_TxBuf[0] = 0xa5;
    u8_TxBuf[1] = ADDR_Reg;
    u8_TX_Length = 2;
    u8_RX_Length = u8_reg_length + 1; // +1, because the length of the received data, in addition to the REG value, has a checksum data


    Clear_RxBuf(); //clear receive buffer
    Start_Send_UartData(u8_TX_Length);
}

/*=========================================================================================================
 * Function : void Uart_Write_HLW8110_Reg(unsigned char ADDR_Reg,unsigned char u8_reg_length,unsigned long u32_data)
 * Describe : Write Register command, u8_reg_length : length of register data bytes to be written
 * :: Input.
 * Output.
 * :: Return.
 * Record : 2019/04/03

==========================================================================================================*/
void Uart_Write_HLW8110_Reg(unsigned char ADDR_Reg,unsigned char u8_reg_length,unsigned long u32_data)
{
    unsigned char i;
    union LongData Temp_u32_a;


    u8_TxBuf[0] = 0xa5;
    u8_TxBuf[1] = ADDR_Reg|0x80;

    Temp_u32_a.word = u32_data;
    for (i = 0; i< u8_reg_length; i++)
        {
            u8_TxBuf[i+2] = Temp_u32_a.byte[u8_reg_length-1-i]; // STM32, 32-bit MCU, union definition, is low bit first
            //u8_TxBuf[i+2] = Temp_u32_a.byte[4-u8_reg_length + i]; //STM8,STC MCU, union definition, is high bit first
        }

    u8_TX_Length = 3 + u8_reg_length ;
        u8_TX_Length = 3 + u8_reg_length;
    u8_RX_Length = 0;

    u8_TxBuf[u8_TX_Length-1] = HLW8110_checkSum_Write(u8_TX_Length);

    Start_Send_UartData(u8_TX_Length);
}



/*=========================================================================================================
 * Function : void Uart_HLW8110_WriteREG_DIS(void)
 * Describe :
 * Input    : none
 * Output   : none
 * Return   : none
 * Record   : 2019/04/03
==========================================================================================================*/
void Uart_HLW8110_WriteREG_DIS(void)
{

    u8_TX_Length = 4;
    u8_RX_Length = 0;

    u8_TxBuf[0] = 0xa5;
    u8_TxBuf[1] = 0xea;
    u8_TxBuf[2] = 0xdc;
//  u8_TxBuf[3] = 0x94;  //checksum
    u8_TxBuf[3] = HLW8110_checkSum_Write(u8_TX_Length);

    Start_Send_UartData(u8_TX_Length);
}

/*=========================================================================================================
 * Function : void Uart_HLW8110_Reset(void)
 * Describe :
 * Input    : none
 * Output   : none
 * Return   : none
 * Record   : 2019/04/03
==========================================================================================================*/
void Uart_HLW8110_Reset(void)
{

    u8_TX_Length = 4;
    u8_RX_Length = 0;

    u8_TxBuf[0] = 0xa5;
    u8_TxBuf[1] = 0xea;
    u8_TxBuf[2] = 0x96;
//  u8_TxBuf[3] = 0xda;  //checksum

    u8_TxBuf[3] = HLW8110_checkSum_Write(u8_TX_Length);

    Start_Send_UartData(u8_TX_Length);
}


char Receive_to_Bufer(unsigned char receive_data_length)
{

 unsigned char  REC_length;
 REC_length= receive_data_length;

 count=0;
 count2=0;



// printf( " event_RTC_sleep ON RX  =  %ld \n" ,event_RTC_sleep);
// printf( "----  \n");

 //if(event_RTC_sleep!=event_sleep_START)
 //{
 //UART1_DefInit1();
 //GPIOB_SetBits(bTXD1);
 //GPIOB_ModeCfg(bTXD1, GPIO_ModeOut_PP_5mA);



 while(count<  (REC_length))
       {
           //len = UART3_RecvString(& reciver_byte);

             len = UART1_RecvString(& reciver_byte);


           count2++;// накапливаем счетчик для антивыхода в случае зависания

            if(len>0)
                 {
                  count++;
                  len=0;
                 }
           if(count>0)
           {
            u8_RxBuf[count-1]=reciver_byte;
           }

           if(count2>(count+3000))// как только счетчик зависания больше на 2 чем реальные принятые байты - сброс и выход

          // if(count2>(count+20))//??
           {

            count=REC_length+2;// и выходим из While

           // UART3_DefInit();
           // Init_HLW8110();
          //     while(1);
           }


   //    }



  }







 return count2;

}


/*=========================================================================================================
 * Function : void Judge_CheckSum_HLW8110_Calfactor(void)
 * :: Describe : verify the coefficients of addresses 0x70-0x77 and
 * Input : none
 * Output : none
 * Return : none
 * Record : 2019/03/18

==========================================================================================================*/
unsigned char Judge_CheckSum_HLW8110_Calfactor(void)
{
    unsigned long a;
    //unsigned int b;
    //unsigned int c.
    unsigned char d;

  // Read the values of RmsIAC, RmsIBC, RmsUC, PowerPAC, PowerPBC, PowerSC, EnergAc, EnergBc

    Uart_Read_HLW8110_Reg(REG_RMS_IAC_ADDR,2);
    Receive_to_Bufer(u8_RX_Length);


    if ( u8_RxBuf[u8_RX_Length-1] == HLW8110_checkSum_Read(u8_RX_Length) )
    {
        U16_RMSIAC_RegData = (u8_RxBuf[0]<<8) + u8_RxBuf[1] ;
        //printf("A channel current conversion factor:%x\n " ,U16_RMSIAC_RegData);
        A_ch_cur_conver_factor=1;

    }

 //   DelayMs(50);




  //  Uart_Read_HLW8110_Reg(REG_RMS_IBC_ADDR,2);
 //   Receive_to_Bufer(u8_RX_Length);
  //  if ( u8_RxBuf[u8_RX_Length-1] == HLW8110_checkSum_Read(u8_RX_Length) )
  //  {
  //      U16_RMSIBC_RegData = (u8_RxBuf[0]<<8) + u8_RxBuf[1] ;
       // printf("B channel current conversion factor:%x\n " ,U16_RMSIBC_RegData);
  //  }
  //  DelayMs(50);


    Uart_Read_HLW8110_Reg(REG_RMS_UC_ADDR,2);
    Receive_to_Bufer(u8_RX_Length);
    if ( u8_RxBuf[u8_RX_Length-1] == HLW8110_checkSum_Read(u8_RX_Length) )
    {
        U16_RMSUC_RegData = (u8_RxBuf[0]<<8) + u8_RxBuf[1] ;
     //   printf("Voltage channel conversion factor:%x\n " ,U16_RMSUC_RegData);
          Volt_ch_conver_factor=1;
    }

 //   DelayMs(50);


    Uart_Read_HLW8110_Reg(REG_POWER_PAC_ADDR,2);
    Receive_to_Bufer(u8_RX_Length);
    if ( u8_RxBuf[u8_RX_Length-1] == HLW8110_checkSum_Read(u8_RX_Length) )
    {
        U16_PowerPAC_RegData = (u8_RxBuf[0]<<8) + u8_RxBuf[1] ;
   //     printf("A-channel power conversion factor:%x\n " ,U16_PowerPAC_RegData);
        A_ch_pow_conver_factor=1;
    }
 //   DelayMs(50);

  //  Uart_Read_HLW8110_Reg(REG_POWER_PBC_ADDR,2);
  //  Receive_to_Bufer(u8_RX_Length);
  //  if ( u8_RxBuf[u8_RX_Length-1] == HLW8110_checkSum_Read(u8_RX_Length) )
  //  {
   //     U16_PowerPBC_RegData = (u8_RxBuf[0]<<8) + u8_RxBuf[1] ;
   //     printf("B channel power conversion factor:%x\n " ,U16_PowerPAC_RegData);
  //  }

 //   DelayMs(50);

    Uart_Read_HLW8110_Reg(REG_POWER_SC_ADDR,2);
    Receive_to_Bufer(u8_RX_Length);
    if ( u8_RxBuf[u8_RX_Length-1] == HLW8110_checkSum_Read(u8_RX_Length) )
    {
        U16_PowerSC_RegData = (u8_RxBuf[0]<<8) + u8_RxBuf[1] ;
    //    printf("Apparent power conversion factor:%x\n " ,U16_PowerSC_RegData);
        Appar_pow_conver_factor=1;
    }

 //   DelayMs(50);

    Uart_Read_HLW8110_Reg(REG_ENERGY_AC_ADDR,2);
    Receive_to_Bufer(u8_RX_Length);
    if ( u8_RxBuf[u8_RX_Length-1] == HLW8110_checkSum_Read(u8_RX_Length) )
    {
        U16_EnergyAC_RegData = (u8_RxBuf[0]<<8) + u8_RxBuf[1] ;
        //printf("A-channel power conversion coefficient:%x\n " ,U16_EnergyAC_RegData);
        A_ch_pow_conver_coeffic=1;

    }

 //   DelayMs(50);

  //  Uart_Read_HLW8110_Reg(REG_ENERGY_BC_ADDR,2);
  //  Receive_to_Bufer(u8_RX_Length);
  //  if ( u8_RxBuf[u8_RX_Length-1] == HLW8110_checkSum_Read(u8_RX_Length) )
   // {
   //     U16_EnergyBC_RegData = (u8_RxBuf[0]<<8) + u8_RxBuf[1] ;
      //  printf("B-channel power conversion factor:%x\n " ,U16_EnergyBC_RegData);
  //  }

 //   DelayMs(50);

    Uart_Read_HLW8110_Reg(REG_CHECKSUM_ADDR,2);
    Receive_to_Bufer(u8_RX_Length);
    if ( u8_RxBuf[u8_RX_Length-1] == HLW8110_checkSum_Read(u8_RX_Length) )
    {
        U16_CheckSUM_RegData= (u8_RxBuf[0]<<8) + u8_RxBuf[1] ;
     //   printf("Coefficient checksum:%x\n " ,U16_CheckSUM_RegData);
        Coefficient_checksum=1;
    }

 //   DelayMs(50);

    a = 0;
  a = ~(0xffff+U16_RMSIAC_RegData + U16_RMSIBC_RegData + U16_RMSUC_RegData +
        U16_PowerPAC_RegData + U16_PowerPBC_RegData + U16_PowerSC_RegData +
          U16_EnergyAC_RegData + U16_EnergyBC_RegData );

    U16_CheckSUM_Data = a & 0xffff;

   // printf("Calculating coefficient checksum:%x\n " ,U16_CheckSUM_Data);
        Calcul_coeffic_checksum=1;

    if ( U16_CheckSUM_Data == U16_CheckSUM_RegData )
    {
        d = 1;
        //printf("Checksum is correct\r\n ");
        Checksum_correct=1;

    }
    else
    {
        d = 0;
        //printf("Checksum error \r\n ");
        Checksum_error=1;
    }

   // Judge_CheckSum_HLW8110_Calfactor_printf();//выводим на терминал и обнуляем флаги для printf

    return d;




}

void Judge_CheckSum_HLW8110_Calfactor_printf(void)
{

    if(A_ch_cur_conver_factor)
    {printf("A channel current conversion factor:%x\n " ,U16_RMSIAC_RegData);}
    if(Volt_ch_conver_factor)
    {printf("Voltage channel conversion factor:%x\n " ,U16_RMSUC_RegData);}
    if(A_ch_pow_conver_factor)
    {printf("A-channel power conversion factor:%x\n " ,U16_PowerPAC_RegData);}
    if(Appar_pow_conver_factor)
    { printf("Apparent power conversion factor:%x\n " ,U16_PowerSC_RegData);}
    if(A_ch_pow_conver_coeffic)
    {printf("A-channel power conversion coefficient:%x\n " ,U16_EnergyAC_RegData);}
    if(Coefficient_checksum)
    { printf("Coefficient checksum:%x\n " ,U16_CheckSUM_RegData);}
    if(Calcul_coeffic_checksum)
    {printf("Calculating coefficient checksum:%x\n " ,U16_CheckSUM_Data);}
    if(Checksum_correct)
    {printf("Checksum is correct\r\n ");}
    if(Checksum_error)
    {printf("Checksum error \r\n ");}


    A_ch_cur_conver_factor=0;
    Volt_ch_conver_factor=0;
    A_ch_pow_conver_factor=0;
    Appar_pow_conver_factor=0;
    A_ch_pow_conver_coeffic=0;
    Coefficient_checksum=0;
    Calcul_coeffic_checksum=0;
    Checksum_correct=0;
    Checksum_error=0;


}

/*=========================================================================================================
 * Function : void Init_HLW8110(void)
 * Describe :
 * Input    : none
 * Output   : none
 * Return   : none
 * Record   : 2019/04/03
==========================================================================================================*/
void Init_HLW8110(void)
{

//9600 bps,1S transmission 9600/11bit = 872byte

    Uart_HLW8110_WriteREG_EN();
    DelayMs(10);

//The /Current Channel A Setup command specifies that the channel currently used to calculate the signal indications for apparent power, power factor, phase angle, instantaneous active power, instantaneous apparent power, and active power overload is Channel A.
    Uart_HLW8110_Set_Channel_A();
    DelayMs(10);
    Uart_Write_HLW8110_Reg(REG_SYSCON_ADDR,2,0x0a04); //Turn on channel A, turn off channel B. Voltage channel PGA = 1, current channel PGA = 16
    DelayMs(10);


  //  Uart_Write_HLW8110_Reg(REG_EMUCON_ADDR,2,0x0001); //1, enable PFA pulse output and active energy register accumulation;
  //  DelayMs(10);

// Uart_Write_HLW8110_Reg(REG_EMUCON_ADDR,2,0x0018); // Both positive and negative zero crossing points are changed, ZXD0 = 1, ZXD1 = 1
  //  Uart_Write_HLW8110_Reg(REG_EMUCON2_ADDR,2,0x0465); //0x0001 is the default value of EMUCON2, waveEn = 1,zxEn = 1, A-channel power register, uncleared after reading, EPA_CB = 1; turn on the power factor detection
   // DelayMs(10);


  //  Uart_HLW8110_WriteREG_DIS();
  //  DelayMs(10);


  // Read the registers whose addresses are 0x6F to 0x77 to verify that the coefficients are correct
    Judge_CheckSum_HLW8110_Calfactor();

}

/*=========================================================================================================
 * Function : void Check_WriteReg_Success(void)
 * :: Describe : verify that the written REG is written correctly
 * Input : none
 * Output : none
 * Return : none
 * Record : 2020/04/02
==========================================================================================================*/
void Check_WriteReg_Success(void)
{
    Uart_Read_HLW8110_Reg(REG_SYSCON_ADDR,2);
    Receive_to_Bufer(u8_RX_Length);
   // DelayMs(10);
    if ( u8_RxBuf[u8_RX_Length-1] == HLW8110_checkSum_Read(u8_RX_Length) )
    {
        U16_Check_SysconReg_Data = (u8_RxBuf[0]<<8) + (u8_RxBuf[1]);
       // printf("SysconReg register written:%lx\n " ,U16_Check_SysconReg_Data);
        SysconReg_reg_written=1;
    }
    else
    {
        //printf("SysconReg register read error\r\n");
        SysconReg_reg_read_err=1;
        B_Read_Error = 1;
    }

    Uart_Read_HLW8110_Reg(REG_EMUCON_ADDR,2);
    Receive_to_Bufer(u8_RX_Length);
  //  DelayMs(10);
    if ( u8_RxBuf[u8_RX_Length-1] == HLW8110_checkSum_Read(u8_RX_Length) )
    {
        U16_Check_EmuconReg_Data = (u8_RxBuf[0]<<8) + (u8_RxBuf[1]);
        //printf("EmuconReg register written:%lx\n " ,U16_Check_EmuconReg_Data);
        EmuconReg_reg_written=1;
    }
    else
    {
        //printf("EmuconReg register read error\r\n");
        EmuconReg_reg_read_err=1;
        B_Read_Error = 1;
    }


    Uart_Read_HLW8110_Reg(REG_EMUCON2_ADDR,2);
    Receive_to_Bufer(u8_RX_Length);
   // DelayMs(10);
    if ( u8_RxBuf[u8_RX_Length-1] == HLW8110_checkSum_Read(u8_RX_Length) )
    {
        U16_Check_Emucon2Reg_Data = (u8_RxBuf[0]<<8) + (u8_RxBuf[1]);
       // printf("Emucon2Reg register register written:%lx\n " ,U16_Check_Emucon2Reg_Data);
        Emucon2Reg_reg_reg_written=1;
    }
    else
    {
       // printf("Emucon2Reg register read error\r\n");
        Emucon2Reg_reg_read_error=1;
        B_Read_Error = 1;
    }

}


/*=========================================================================================================
 * Function : void Read_HLW8112_IA(void)
 * :: Describe : Reading A-channel current
 * Input : none
 * Output : none
 * Return : none
 * Record : 2019/04/03

==========================================================================================================*/
void Read_HLW8110_IA(void)
{
    float a;

    Uart_Read_HLW8110_Reg(REG_RMSIA_ADDR,3);
    Receive_to_Bufer(u8_RX_Length);
   // DelayMs(10);

    if ( u8_RxBuf[u8_RX_Length-1] == HLW8110_checkSum_Read(u8_RX_Length) )
    {
        U32_RMSIA_RegData = (unsigned long)(u8_RxBuf[0]<<16) + (unsigned long)(u8_RxBuf[1]<<8) + (unsigned long)(u8_RxBuf[2]);
 //       printf("A channel current register:%lx\n " ,U32_RMSIA_RegData);
        A_ch_current_reg=1;

        B_Read_Error = 0;
    }
    else
    {
//        printf("Error reading A channel current register \r\n");
        Err_read_A_ch_curr_reg=1;

        B_Read_Error = 1;
    }


   //A channel current PGA = 16, voltage channel PGA = 1; current sampling resistor 1mR, voltage sampling resistor 1M
  //Calculation formula,U16_AC_I = (U32_RMSIA_RegData * U16_RMSIAC_RegData)/(current factor* 2^23)
    if (((U32_RMSIA_RegData & 0x800000) == 0x800000)||( B_Read_Error == 1))
     {
            F_AC_I = 0;
     }
     else
     {
        a = (float)U32_RMSIA_RegData;
        a = a * U16_RMSIAC_RegData;
        a = a/0x800000; //current calculated in mA floating point units, e.g. 5003.12
        //a = a/1; // 1 = current factor

              a = a*2.5;

        a = a/1000; //a= 5003ma,a/1000 = 5.003A, units converted to A
        a = a * D_CAL_A_I; //D_CAL_A_I is the correction factor, default is 1
        F_AC_I = a;
     }
}


/*=========================================================================================================
 * Function : void Read_HLW8110_U(void)
 * :: Describe : reading voltage
 * Input : none
 * Output : none
 * Return : none
 * Record : 2019/04/03

==========================================================================================================*/
void Read_HLW8110_U(void)
{
    float a;

    Uart_Read_HLW8110_Reg(REG_RMSU_ADDR,3);
    Receive_to_Bufer(u8_RX_Length);
    //    DelayMs(10);
    if ( u8_RxBuf[u8_RX_Length-1] == HLW8110_checkSum_Read(u8_RX_Length) )
    {
        U32_RMSU_RegData = (unsigned long)(u8_RxBuf[0]<<16) + (unsigned long)(u8_RxBuf[1]<<8) + (unsigned long)(u8_RxBuf[2]);
 //       printf("Voltage channel register:%lx\n " ,U32_RMSU_RegData);
        Volt_ch_reg=1;

        B_Read_Error = 0;
    }
    else
    {
 //       printf("Voltage channel register read error \r\n");
        Volt_ch_reg_read_err=1;

        B_Read_Error = 1;
    }

        //Voltage
    // Calculation:U16_AC_V = (U32_RMSU_RegData * U16_RMSUC_RegData)/2^23

     if (((U32_RMSU_RegData &0x800000) == 0x800000) || (B_Read_Error == 1))
     {
            F_AC_V = 0;
     }
  else
    {
  a = (float)U32_RMSU_RegData;
  a = a*U16_RMSUC_RegData;
  a = a/0x400000;
  a = a/1; // 1 = voltage factor
  a = a/100; //calculated a = 22083.12mV,a/100 means 220.8312V, the voltage is converted to V
  a = a*D_CAL_U; //D_CAL_U is the calibration factor, default is 1,
  F_AC_V = a;
    }
}

/*=========================================================================================================
 * Function : void Read_HLW8110_PA(void)
 * :: Describe : Read A-channel power
 * Input : none
 * Output : none
 * Return : none
 * Record : 2019/04/03
==========================================================================================================*/
void Read_HLW8110_PA(void)
{
    float a;
    float b;

    Uart_Read_HLW8110_Reg(REG_POWER_PA_ADDR,4);
    Receive_to_Bufer(u8_RX_Length);
  //      DelayMs(10);
    if ( u8_RxBuf[u8_RX_Length-1] == HLW8110_checkSum_Read(u8_RX_Length) )
    {
        U32_POWERPA_RegData = (unsigned long)(u8_RxBuf[0]<<24) + (unsigned long)(u8_RxBuf[1]<<16) + (unsigned long)(u8_RxBuf[2]<< 8) + (unsigned long)(u8_RxBuf[3]);
 //       printf("A channel power register:%lx\n " ,U32_POWERPA_RegData);
        A_ch_power_reg=1;

        B_Read_Error = 0;
    }
    else
    {
 //       printf("Error reading A-channel power register \r\n");
        Err_read_A_ch_power_reg=1;

        B_Read_Error = 1;
    }


   if( B_Read_Error == 0)
   {

     if (U32_POWERPA_RegData > 0x80000000)
   {
     b = ~U32_POWERPA_RegData;
     a = (float)b;
   }
   else
     a = (float)U32_POWERPA_RegData;


    //Power needs to be divided into positive and negative work
  // Calculation,U16_AC_P = (U32_POWERPA_RegData * U16_PowerPAC_RegData)/(2^31*Voltage Factor*Current Factor)
    // unit of W, for example, calculated 5000.123, said 5000.123W

    a = a*U16_PowerPAC_RegData;
    a = a/0x80000000;
    //a = a/1; // 1 = current factor
    //a = a/1; // 1 = voltage factor
      a = a*2.5; // 1 = current factor
    a = a * D_CAL_A_P; //D_CAL_A_P is the correction factor, default 1
    F_AC_P = a; // unit of W, such as calculated 5000.123, said 5000.123W

   }else
   {

       F_AC_P = 0;
   }

}

/*=========================================================================================================
* Function : void void Read_HLW8112_EA(void)
 * :: Describe : Reading the active power of channel A.
 * Input : none
 * Output : none
 * Return : none
 * Record : 2019/04/03
==========================================================================================================*/
void Read_HLW8110_EA(void)
{
    float a;
    Uart_Read_HLW8110_Reg(REG_ENERGY_PA_ADDR,3);
    Receive_to_Bufer(u8_RX_Length);
 //   DelayMs(10);

    if ( u8_RxBuf[u8_RX_Length-1] == HLW8110_checkSum_Read(u8_RX_Length) )
    {
        U32_ENERGY_PA_RegData = (unsigned long)(u8_RxBuf[0]<<16) + (unsigned long)(u8_RxBuf[1]<<8) + (unsigned long)(u8_RxBuf[2]);
 //       printf("A channel active power register:%lx\n " ,U32_ENERGY_PA_RegData);
        A_ch_active_power_reg=1;

        B_Read_Error = 0;
    }
    else
    {
 //       printf("Error reading A-channel active power register \r\n");
        Err_read_A_ch_active_power_reg=1;

        B_Read_Error = 1;
    }

    Uart_Read_HLW8110_Reg(REG_HFCONST_ADDR,2);
    Receive_to_Bufer(u8_RX_Length);
 //   DelayMs(10);
    if ( u8_RxBuf[u8_RX_Length-1] == HLW8110_checkSum_Read(u8_RX_Length) )
    {
        U16_HFConst_RegData = (unsigned int)(u8_RxBuf[0]<<8) + (unsigned int)(u8_RxBuf[1]);
  //      printf("HFCONST constant register = :%d\n " ,U16_HFConst_RegData);
        HFCONST_const_reg=1;

        B_Read_Error = 0;
    }
    else
    {
 //       printf("Error reading HFCONST constant register \r\n");
        Err_read_HFCONST_const_reg=1;

        B_Read_Error = 1;
    }

    // power calculation,power = (U32_ENERGY_PA_RegData * U16_EnergyAC_RegData * HFCONST) /(K1*K2 * 2^29 * 4096)
    //HFCONST: default value is 0x1000, HFCONST/(2^29 * 4096) = 0x20000000
    a = (float)U32_ENERGY_PA_RegData;
  a = a*U16_EnergyAC_RegData;
  a = a/0x20000000; //Electricity unit is 0.001KWH, for example, calculated to be 2.002, said 2.002KWH
   a = a/1; // 1 = current factor
   a = a/1; // 1 = voltage factor
   a = a * D_CAL_A_E; //D_CAL_A_E is the correction factor, default 1
   F_AC_E = a;
    F_AC_BACKUP_E = F_AC_E;


    if((F_AC_BACKUP_E==0)&(F_AC_BACKUP_E_SUM!=0))//если произошел сбой текущей памяти а псоденее буферное значение больше
        //нуля
    {
        F_AC_BACKUP_E_ADD=F_AC_BACKUP_E_SUM;
    }

    F_AC_BACKUP_E = F_AC_E+F_AC_BACKUP_E_ADD;

    if(F_AC_BACKUP_E !=0.00000)// если в микросхеме квт/час >0
    {
    F_AC_BACKUP_E_SUM= F_AC_BACKUP_E;// копируем это значение в F_AC_BACKUP_E_SUM
    }


}

/*=========================================================================================================
 * Function : void Read_HLW8110_LineFreq(void)
 * :: Describe : Reads the linear frequency of the A channel.
 * Input : none
 * Output : none
 * Return : none
 * Record : 2019/04/12
==========================================================================================================*/
void Read_HLW8110_LineFreq(void)
{
    float a;
    unsigned long b;
    Uart_Read_HLW8110_Reg(REG_UFREQ_ADDR,2);
    Receive_to_Bufer(u8_RX_Length);
  //  DelayMs(10);
    if ( u8_RxBuf[u8_RX_Length-1] == HLW8110_checkSum_Read(u8_RX_Length) )
    {
        b = (unsigned long)(u8_RxBuf[0]<<8) + (unsigned long)(u8_RxBuf[1]);

        U32_Linear_Freq_Reg=b;
 //       printf("Channel A Linear Frequency Register: %ld\n " ,U32_Linear_Freq_Reg);
        Ch_A_Linear_Freq_Reg=1;

        B_Read_Error = 0;
    }
    else
    {
 //       printf("Error reading A channel linear frequency register \r\n");
        Err_read_A_ch_linear_freq_reg=1;

        B_Read_Error = 1;
    }
    a = (float)b;
    a = 3579545/(8*a);
    F_AC_LINE_Freq = a;
}


/*=========================================================================================================
 * Function : void Read_HLW8110_PF(void)
 * :: Describe : read power factor
 * Input : none
 * Output : none
 * Return : none
 * Record : 2019/03/18
==========================================================================================================*/
void Read_HLW8110_PF(void)
{
  float a;
  unsigned long b;

//Measuring the power factor of channel A requires sending the EA+5A command
//Measurement of the power factor of channel B requires sending the command EA+A5

    Uart_Read_HLW8110_Reg(REG_PF_ADDR,3);
    Receive_to_Bufer(u8_RX_Length);
 //   DelayMs(10);
    if ( u8_RxBuf[u8_RX_Length-1] == HLW8110_checkSum_Read(u8_RX_Length) )
    {
        b = (unsigned long)(u8_RxBuf[0]<<16) + (unsigned long)(u8_RxBuf[1]<<8) + (unsigned long)(u8_RxBuf[2]);
 //
        U32_A_ch_Power_factor_Reg=b;
        //printf("A-channel power factor register: %ld\n " ,U32_A_ch_Power_factor_Reg);
        A_ch_power_factor_reg=1;

        B_Read_Error = 0;
    }
    else
    {
 //       printf("Error reading A-channel power factor register\r\n");
        Err_read_A_ch_power_factor_reg=1;

        B_Read_Error = 1;
    }



  if (b>0x800000) // negative, capacitive loads
  {
      a = (float)(0xffffff-b + 1)/0x7fffffff;
  }
  else
  {
      a = (float)b/0x7fffff;
  }

  if (F_AC_P < 0.3) // less than 0.3W, no load or low power, PF not allowed
      a = 0;


//Power factor*100, max. 100, min. minus 100
  F_AC_PF = a;

}


/*=========================================================================================================
 * Function : void Read_HLW8110_Angle(void)
 * :: Describe : read phase angle
 * Input : none
 * Output : none
 * Return : none
 * Record : 2019/04/12
==========================================================================================================*/
void Read_HLW8110_Angle(void)
{
    float a;
    unsigned long b;
    Uart_Read_HLW8110_Reg(REG_ANGLE_ADDR,2);
    Receive_to_Bufer(u8_RX_Length);
 //   DelayMs(10);
    if ( u8_RxBuf[u8_RX_Length-1] == HLW8110_checkSum_Read(u8_RX_Length) )
    {
        b = (unsigned long)(u8_RxBuf[0]<<8) + (unsigned long)(u8_RxBuf[1]);
        U32_A_ch_Line_Phase_Angle_Reg=b;
 //       printf("A Channel Line Phase Angle Register:%ld\n " ,U32_A_ch_Line_Phase_Angle_Reg);
        A_Ch_Line_Phase_Angle_Reg=1;

        B_Read_Error = 0;

    }
    else
    {
//        printf("Error in A channel line phase angle register\r\n");
        Err_in_A_ch_line_phase_angle_reg=1;

        B_Read_Error = 1;
    }

    if ( F_AC_PF < 55) // Linear frequency 50HZ
    {
        a = b;
        a = a * 0.0805;
        F_Angle = a;
    }
    else
    {
        //Linear frequency 60Hz
        a = b;
        a = a * 0.0965;
        F_Angle = a;
    }


  //  float F_Current_overrun_voltage;
  //  float F_Current_hysteresis_voltage;


        if (F_AC_P < 0.5) // power less than 0.5 means no load, phase angle 0
    {
        F_Angle = 0;
    }

    if (F_Angle < 90)
    {
        a = F_Angle;
        F_Current_overrun_voltage=a;

  //      printf("Current overrun voltage:%f\n " ,F_Current_overrun_voltage);
    }
    else if (F_Angle < 180)
    {
        a = 180-F_Angle;
        F_Current_hysteresis_voltage=a;
 //       printf("Current hysteresis voltage:%f\n " ,F_Current_hysteresis_voltage);
    }
    else if (F_Angle < 360)
    {
        a = 360 - F_Angle;
        F_Current_hysteresis_voltage=a;
 //       printf("Current hysteresis voltage:%f\n " ,F_Current_hysteresis_voltage);
    }
    else
    {
            a = F_Angle -360;
            F_Current_overrun_voltage=a;
 //           printf("Current overrun voltage:%f\n " ,F_Current_overrun_voltage);
    }
}


/*=========================================================================================================
 * Function : void Calculate_HLW8110_MeterData(void);
 * Describe :
 * Input    : none
 * Output   : none
 * Return   : none
 * Record   : 2018/05/10
==========================================================================================================*/
void Calculate_HLW8110_MeterData(void)
{


    Check_WriteReg_Success();


    Read_HLW8110_IA();
    Read_HLW8110_U();
    Read_HLW8110_PA();
    Read_HLW8110_EA();
    Read_HLW8110_LineFreq();
    Read_HLW8110_Angle();
    Read_HLW8110_PF();




 //   Calculate_HLW8110_MeterData_printf();

}

void Calculate_HLW8110_MeterData_printf(void)
{

    /*
 //-----------------------------------УСЛОВНЫЙ ВЫВОД РЕГИСТРОВ С УЧЕТОМ ERROR-----------------------------

    printf(" DYNAMIC  OUTPUT + ERROR STATE \r\n");//insert newlines
 //--------for Check_WriteReg_Success();
    if(SysconReg_reg_written)
    {printf("SysconReg register written:%lx\n " ,U16_Check_SysconReg_Data);};SysconReg_reg_written=0;
    if(SysconReg_reg_read_err)
    {printf("SysconReg register read error\r\n");};SysconReg_reg_read_err=0;
    if(EmuconReg_reg_written)
    {printf("EmuconReg register written:%lx\n " ,U16_Check_EmuconReg_Data);};EmuconReg_reg_written=0;
    if(EmuconReg_reg_read_err)
    {printf("EmuconReg register read error\r\n");};EmuconReg_reg_read_err=0;
    if(Emucon2Reg_reg_reg_written)
    {printf("Emucon2Reg register register written:%lx\n " ,U16_Check_Emucon2Reg_Data);}Emucon2Reg_reg_reg_written=0;
    if(Emucon2Reg_reg_read_error)
    {printf("Emucon2Reg register read error\r\n");}Emucon2Reg_reg_read_error=0;
//-------------------------------------------




 //------------------ for Read_HLW8110_IA()-----------------------------
    if(A_ch_current_reg)
 {printf("A channel current register:%x\n " ,U32_RMSIA_RegData);};A_ch_current_reg=0;
 if(Err_read_A_ch_curr_reg)
 {printf("Error reading A channel current register \r\n");};Err_read_A_ch_curr_reg=0;

//------------------ for Read_HLW8110_U()-----------------------------
    if(Volt_ch_reg)
 {printf("Voltage register:%x\n " ,U32_RMSU_RegData);};Volt_ch_reg=0;
    if(Volt_ch_reg_read_err)
 {printf("Voltage channel register read error \r\n");};Volt_ch_reg_read_err=0;

//------------------ for Read_HLW8110_PA()-----------------------------
    if(A_ch_power_reg)
 {printf("A channel power register:%lx\n " ,U32_POWERPA_RegData);};A_ch_power_reg=0;
    if(Err_read_A_ch_power_reg)
 {printf("Error reading A-channel power register \r\n");};Err_read_A_ch_power_reg=0;

//------------------ for Read_HLW8110_EA()-----------------------------
    if(A_ch_active_power_reg)
 { printf("A channel active power register:%lx\n " ,U32_ENERGY_PA_RegData);};A_ch_active_power_reg=0;
    if(Err_read_A_ch_active_power_reg)
 {printf("Error reading A-channel active power register \r\n");};Err_read_A_ch_active_power_reg=0;
    if(HFCONST_const_reg)
 { printf("HFCONST constant register = :%d\n " ,U16_HFConst_RegData);};HFCONST_const_reg=0;
    if(Err_read_HFCONST_const_reg)
 { printf("Error reading HFCONST constant register \r\n");};Err_read_HFCONST_const_reg=0;

//------------------ for Read_HLW8110_LineFreq()-----------------------------
    if(Ch_A_Linear_Freq_Reg)
 {printf("Channel A Linear Frequency Register: %ld\n " ,U32_Linear_Freq_Reg);};Ch_A_Linear_Freq_Reg=0;
    if(Err_read_A_ch_linear_freq_reg)
 {printf("Error reading A channel linear frequency register \r\n");};Err_read_A_ch_linear_freq_reg=0;

//------------------ for Read_HLW8110_Angle()-----------------------------
    if( A_Ch_Line_Phase_Angle_Reg)
 {printf("A Channel Line Phase Angle Register:%ld\n " ,U32_A_ch_Line_Phase_Angle_Reg);}; A_Ch_Line_Phase_Angle_Reg=0;
    if(Err_in_A_ch_line_phase_angle_reg)
 {printf("Error in A channel line phase angle register\r\n");};Err_in_A_ch_line_phase_angle_reg=0;
    if(Current_overrun_voltage)
 {printf("Current overrun voltage:%f\n " ,F_Current_overrun_voltage);};Current_overrun_voltage=0;
    if(Current_hysteresis_voltage)
 {printf("Current hysteresis voltage:%f\n " ,F_Current_hysteresis_voltage);};Current_hysteresis_voltage=0;

//------------------ for Read_HLW8110_PF()-----------------------------
    if(A_ch_power_factor_reg)
 {printf("A-channel power factor register: %ld\n " ,U32_A_ch_Power_factor_Reg);};A_ch_power_factor_reg=0;
    if(Err_read_A_ch_power_factor_reg)
 {printf("Error reading A-channel power factor register\r\n");};Err_read_A_ch_power_factor_reg=0;
//---------------------------------------------------------------------
 printf("\r\n");





//-----------------------------СТАТИЧЕСКИЙ ВЫВОД РЕГИСТРОВ-----------------
    printf(" STATIC  REG  OUTPUT \r\n");//insert newlines
    printf("A channel current conversion factor:%x\n " ,U16_RMSIAC_RegData);
/   printf("B channel current conversion factor:%x\n " ,U16_RMSIBC_RegData);
    printf("Voltage channel conversion factor:%x\n " ,U16_RMSUC_RegData);
    printf("A-channel power conversion factor:%x\n " ,U16_PowerPAC_RegData);
    printf("B channel power conversion factor:%x\n " ,U16_PowerPBC_RegData);
    printf("Apparent power conversion factor:%x\n " ,U16_PowerSC_RegData);
    printf("A-channel power conversion coefficient:%x\n " ,U16_EnergyAC_RegData);
    printf("B-channel power conversion factor:%x\n " ,U16_EnergyBC_RegData);
    printf("Converting coefficient checksum:%x\n " ,U16_CheckSUM_RegData);
    printf("Checksum calculated by conversion factor:%x\n " ,U16_CheckSUM_Data);
    printf("\r\n");

*/



//------------------------------ИТОГОВЫЙ ВЫВОД ПОСЧИТАННЫХ ЗНАЧЕНИЙ-----------------
    printf(" FINISH  READY  OUTPUT \r\n");//insert newlines
    printf("F_AC_I = %f A \n " ,F_AC_I); //current
    printf("F_AC_V = %f V \n " ,F_AC_V); //voltage
    printf("F_AC_P = %f W \n " ,F_AC_P); //power
    printf("F_AC_BACKUP_E = %f KWH \n " ,F_AC_BACKUP_E); //electricity
 //   printf("F_AC_BACKUP_E_SUM = %f KWH \n " ,F_AC_BACKUP_E_SUM); //electricity
 //   printf(" F_AC_BACKUP_E_ADD = %f KWH \n " , F_AC_BACKUP_E_ADD); //electricity
    printf("F_AC_LINE_Freq = %f Hz\n " ,F_AC_LINE_Freq); // Utility linear frequency
    printf("F_Angle = %f\n " ,F_Angle); //phase angle of L and N
    printf("F_AC_PF = %f\n " ,F_AC_PF); //power factor
    printf("\r\n");


}





//*********************************************************************
// * @fn      UART1_IRQHandler
// *
 //* @brief   UART1中断函数
// *
 //* @return  none
 //*/


__INTERRUPT
__HIGH_CODE
void UART1_IRQHandler(void)
{

    switch(UART1_GetITFlag())
    {
        case UART_II_LINE_STAT: // 线路状态错误
        {
            UART1_GetLinSTA();
            break;
        }

        case UART_II_RECV_RDY: // 数据达到设置触发点


            break;

        case UART_II_RECV_TOUT: // 接收超时，暂时一帧数据接收完成


            while(R8_UART1_RFC)
            {
            u8_RxBuf[len] = R8_UART1_RBR;
            len++;
            }

            break;


        case UART_II_THR_EMPTY: // 发送缓存区空，可继续发送
            break;

        case UART_II_MODEM_CHG: // 只支持串口0
            break;

        default:
            break;
    }
}








