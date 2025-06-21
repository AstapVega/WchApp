/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef __ALEX_BOARD_H
#define __ALEX__BOARD_H

#include "stdbool.h"


#ifndef M_EF
#define M_EF        2.718281828459F
#define M_LOG2EF    1.442695040888F
#define M_LOG10EF   0.4342944819032F
#define M_LN2F      0.6931471805599F
#define M_LN10F     2.302585092994F
#define M_PIF       3.141592653589F
#define M_PI_2F     1.570796326794F
#define M_PI_4F     0.7853981633974F
#define M_1_PIF     0.3183098861837F
#define M_2_PIF     0.6366197723675F
#define M_1_SQRTPIF 0.5641895835477F
#define M_2_SQRTPIF 1.128379167095F
#define M_SQRT2F    1.414213562373F
#define M_SQRT_2F   0.7071067811865F
#endif


/* Private define ------------------------------------------------------------*/
#define INIT_TIMEOUT       ((uint16_t)0xFFFF)
#define RSF_TIMEOUT        ((uint16_t)0xFFFF)
#define INITF_TIMEOUT      ((uint16_t)0xFFFF)
#define WUTWF_TIMEOUT      ((uint16_t)0xFFFF)
#define ALRAWF_TIMEOUT     ((uint16_t)0xFFFF)
#define RECALPF_TIMEOUT    ((uint16_t)0xFFFF)
#define SHPF_TIMEOUT       ((uint16_t)0xFFFF)


#define TEN_VALUE_BCD      ((uint8_t)0x10)
#define TEN_VALUE_BIN      ((uint8_t)0x0A)

                     // BOARD   V4  130916 //

//                         PORTA
#define SCK_PIN          (   1 << 0)  //PORTA0  pin1   IN PULLUP     //SWIM/SCK
#define PA1_PIN          (   1 << 1)  //PORTA1  pin2   IN PULLUP     //NRST
#define MOSI_PIN         (   1 << 2)  //PORTA2  pin3 OUT OPEN DRAIN  //TX/MOSI_NRF24
#define MISO_PIN         (   1 << 3)  //PORTA3  pin4 OUT OPEN DRAIN  //RX/MISO_NRF24
#define LCD_COM0         (   1 << 4)  //PORTA4  pin5 OUT OPEN DRAIN  //LCD
#define LCD_COM1         (   1 << 5)  //PORTA5  pin6 OUT OPEN DRAIN  //LCD
#define LCD_COM2         (   1 << 6)  //PORTA6  pin7 OUT OPEN DRAIN  //LCD
#define LCD_SEG19        (   1 << 7)  //PORTA7  pin8 OUT OPEN DRAIN  //LCD

//                         PORTB
#define LCD_SEG9         (   1 << 0)  //PORTB0  pin24 OUT OPEN DRAIN  //LCD
#define LCD_SEG8         (   1 << 1)  //PORTB1  pin25 OUT OPEN DRAIN  //LCD
#define LCD_SEG7         (   1 << 2)  //PORTB2  pin26 OUT OPEN DRAIN  //LCD
#define LCD_SEG6         (   1 << 3)  //PORTB3  pin27 OUT OPEN DRAIN  //LCD
#define LCD_SEG5         (   1 << 4)  //PORTB4  pin28 OUT OPEN DRAIN  //LCD
#define LCD_SEG4         (   1 << 5)  //PORTB5  pin29 OUT OPEN DRAIN  //LCD
#define LCD_SEG3         (   1 << 6)  //PORTB6  pin30 OUT OPEN DRAIN  //LCD
#define LCD_SEG2         (   1 << 7)  //PORTB7  pin31 OUT OPEN DRAIN  //LCD

//                         PORTC
#define BKLT_PIN         (   1 << 0)  //PORTC0  pin37 OUT OPEN DRAIN //BKLT
#define PWR_PIN          (   1 << 1)  //PORTC1  pin38 OUT OPEN DRAIN //RADIO_POWER_ON 
#define CSN_PIN          (   1 << 2)  //PORTC2  pin41 OUT PUSH-PULL  //NRF24_CSN
#define AIN1_PIN         (   1 << 3)  //PORTC3  pin42 OUT OPEN DRAIN //ADC_IN#5 
#define AIN2_PIN         (   1 << 4)  //PORTC4  pin43  IN FLOAT      //ADC_IN#4 
#define OSC32_IN         (   1 << 5)  //PORTC5  pin44  IN FLOAT      //OSC32 
#define OSC32_OUT        (   1 << 6)  //PORTC6  pin45  IN FLOAT      //OSC32 
#define K1_PIN           (   1 << 7)  //PORTC7  pin46  IN PULLUP     //ADC IN#3  

//                         PORTD
#define LCD_SEG12        (   1 << 0)  //PORTD0  pin20 OUT OPEN DRAIN  //LCD
#define LCD_COM3         (   1 << 1)  //PORTD1  pin21 OUT OPEN DRAIN  //LCD
#define LCD_SEG11        (   1 << 2)  //PORTD2  pin22 OUT OPEN DRAIN  //LCD
#define LCD_SEG10        (   1 << 3)  //PORTD3  pin23 OUT OPEN DRAIN  //LCD
#define LCD_SEG1         (   1 << 4)  //PORTD4  pin33 OUT OPEN DRAIN  //LCD
#define LCD_SEG0         (   1 << 5)  //PORTD5  pin34 OUT OPEN DRAIN  //LCD
#define REL_PIN          (   1 << 6)  //PORTD6  pin35 OUT OPEN DRAIN  //REL 
#define AINV_PIN         (   1 << 7)  //PORTD7  pin36 OUT PUSH-PULL   //AINV  

//                         PORTE
#define LCD_SEG18        (   1 << 0)  //PORTE0  pin14 OUT OPEN DRAIN  //LCD
#define LCD_SEG17        (   1 << 1)  //PORTE1  pin15 OUT OPEN DRAIN  //LCD
#define LCD_SEG16        (   1 << 2)  //PORTE2  pin16 OUT OPEN DRAIN  //LCD
#define LCD_SEG15        (   1 << 3)  //PORTE3  pin17 OUT OPEN DRAIN  //LCD
#define LCD_SEG14        (   1 << 4)  //PORTE4  pin18 OUT OPEN DRAIN  //LCD
#define LCD_SEG13        (   1 << 5)  //PORTE5  pin19 OUT OPEN DRAIN  //LCD
#define CE_PIN           (   1 << 6)  //PORTE6  pin47 OUT PUSH-PULL   //NRF24_CE 
#define IRQ_PIN          (   1 << 7)  //PORTE7  pin48  IN PULLUP      //NRF24_IRQ 

//                         PORTF
#define PVDIN_PIN        (   1 << 0)  //PORTF0  pin32  IN FLOAT      //ADC_IN#24


//#define TST_ON  GPIOE->ODR |= CE_PIN
//#define TST_OFF GPIOE->ODR &= (uint8_t)(~CE_PIN)
//#define TST_TOGGLE  GPIOE->ODR ^= CE_PIN

//#define BKLT_ON  GPIOC->ODR |= BKLT_PIN
//#define BKLT_OFF GPIOC->ODR &= (uint8_t)(~BKLT_PIN)

//#define REL_ON  GPIOD->ODR |= REL_PIN
//#define REL_OFF GPIOD->ODR &= (uint8_t)(~REL_PIN)

//#define IS_BKLT  (GPIOC->ODR & BKLT_PIN)
//#define IS_RELAY (GPIOD->ODR & REL_PIN)

//#define AINV_ON  GPIOD->ODR |= AINV_PIN
//#define AINV_OFF GPIOD->ODR &= (uint8_t)(~AINV_PIN)


#define TST_ON    CE_PIN
#define TST_OFF   (uint8_t)(~CE_PIN)
#define TST_TOGGLE    CE_PIN

#define BKLT_ON    BKLT_PIN
#define BKLT_OFF   (uint8_t)(~BKLT_PIN)


#define REL_ON       GPIOB_SetBits(GPIO_Pin_10);    port_rel_mask =  0x00000400;

//#define REL_ON       GPIOB_SetBits(GPIO_Pin_10);    port_rel_mask =  0x00000000;


#define REL_OFF      GPIOB_ResetBits(GPIO_Pin_10);  port_rel_mask =  0x00000000;

#define LIGTH_ON       GPIOB_SetBits(GPIO_Pin_21);    port_ligth_mask =  0x00200000;
#define LIGTH_OFF      GPIOB_ResetBits(GPIO_Pin_21);  port_ligth_mask =  0x00000000;

//#define RED_ON       GPIOA_ResetBits(GPIO_Pin_3); GPIOA_SetBits(GPIO_Pin_2);port_red_green_mask =  0x00000004;
//#define GREEN_ON     GPIOA_ResetBits(GPIO_Pin_2); GPIOA_SetBits(GPIO_Pin_3);port_red_green_mask =  0x00000008;

//#define RED_ON      port_red_green_mask =  0x00000004;
//#define GREEN_ON    port_red_green_mask =  0x00000008;

//#define RED_ON           port_red_green_mask =  0x00000008;
//#define GREEN_ON         port_red_green_mask =  0x00000004;

#define RED_ON           port_red_green_mask =  0x00000004;
#define GREEN_ON         port_red_green_mask =  0x00000008;
#define CS_O_ON          port_CS0_mask       =  0x00000010;
#define CS_O_OFF         port_CS0_mask       =  0x00000000;


//#define GREEN_RED_OFF    port_red_green_mask =  0x0000000C;
#define GREEN_RED_OFF    port_red_green_mask =  0x00000000;


extern   uint8 device_on_off;  // при сбросе прибор включается
#define  device_off           1
#define  device_on            0

extern  uint8    device_default ;//  по умолчанию режим "СБРОС" равен  0, его можно активировать в Servise Menu

extern  uint8    LOC_on_off;      // по умолчанию, блокировка клавиатуры отключена!!!

extern uint8    lock_key ;// регистр управления  блокировкой/ разблакировкой  клавиатуры

#define  LOC_on         1 // включен режим "блокировки"
#define  LOC_off        0 // выключен режим блокировки

#define  lock          1 // клавиатура заблокирована
#define  unlock        0 // клавиатура разблокирована


extern uint8 FLASH_UPDATE; // флаг обновления FLASH  1 -  нужно обновить,  0 - не нужно
extern uint8 SCHEDULE_UPDATE; // флаг обновления FLASH  1 -  нужно обновить,  0 - не нужно

extern uint8 BUSY_KEY;// занятость клавиатуры
extern uint8 BUSY_KEY2;// занятость клавиатуры для блокировки вывода HLW8110
extern uint8 BUSY_KEY3;// занятость клавиатуры для обновления FLASH



#define IS_BKLT  (  BKLT_PIN)
#define IS_RELAY (  REL_PIN)

//#define AINV_ON  GPIOD->ODR |= AINV_PIN
//#define AINV_OFF GPIOD->ODR &= (uint8_t)(~AINV_PIN)





#define K1_IN K1_adc()  
#define K2_IN K2_adc() 
#define K3_IN K3_adc() 
#define K4_IN K4_adc() 

typedef struct
{
    BOOL kbl;
    BOOL kb2;
    uint8_t kb;
    uint8_t keyb;
    uint8_t key_period;
    uint8_t key_time;//
}
Keyboard_type;


#define key ((Keyboard_type *)((uint16_t)(&k1)))

#define IWDG_ACCESS     ((uint8_t)0x55)
#define IWDG_ENABLE     ((uint8_t)0xCC)
#define IWDG_REFRESH    ((uint8_t)0xAA)

//#define TIME_INIT       (RTC->ISR1 & RTC_ISR1_INITS)

#define TEMP_MIN_LIM  -200   
#define TEMP_MAX_LIM   400

#define POWER_TIME_MIN_LIM  0   
#define POWER_TIME_MAX_LIM  40

//#define SW_RESET {IWDG->KR = IWDG_ACCESS;IWDG->PR = 2;while(1);}

//#define IWDG_Reset IWDG->KR = IWDG_REFRESH

#define K1_V adc_array[0]   //напряжение на входе клавиатуры
#define AIN2 adc_array[1]   //температура выносного датчика 2
#define AIN1 adc_array[2]   //температура выносного датчика 1
#define LINE adc_array[3]   //реальное напряжение 30V//Делитель 100K/7K5  =  14.3333

#define LINE_MIN 1500       //минимальное напряжение с датчика питания: если меньше - выключение 1600
// включение - по том же датчику, только если напряжение больше срабатывания триггера шмитта

#define Factory_VREFINT 0x4910

#define VERSION 630

#define USE_LSE

#endif

//--------------------------------------- РАСШИРЕНИЯ ДЛЯ alex board.c -----------------------------//


//extern void RTC_Read(void);

extern BOOL power, service_mode, WAKE_UP, power_mode, t_view_mode, view_mode, PWM_mode, last_PWM_mode, PWM_prog_mode, prog_mode;
extern BOOL lock_flag, t_lock_flag, load, error, rst_flag, new_data, new_time, new_period;
extern BOOL POWER_IN, mode_locked;
//extern ErrorStatus crc_err;

extern uint8_t mode;
extern uint8_t time, fl_time, time1, timeout, timeout_del, back_light;
extern uint8_t hours, minutes, seconds;
extern uint8_t p_date, date, month, week, year;
extern uint16_t adc_array[4];
extern uint16_t* adres;
extern uint8_t adc_ch;
extern uint16_t adc_filt[32];
extern uint8_t start_cnt;
extern volatile BOOL ERR_ON;

extern Keyboard_type k1;

extern uint16_t adc_res;

extern uint8_t temp_hyst;

extern uint16_t prog1_time_set[7][6];  //время в программе #1
extern int16_t prog1_temp_set[7][6];   //уставки температуры в программе #1
extern uint16_t prog2_time_set[7][6];  //время в программе #2
extern uint8_t prog2_power_set[7][6];  //уставки для регулятора мощности в программе #2

extern int16_t set_temp, set_power;             //текущие уставки для термостата
extern int16_t prog_set_temp, prog_set_power;   //текущие уставки для термостата, прочитанные из программы //

extern int16_t manual_set_temp;                //уставка для термостата ручная
extern int16_t manual_set_power_time;          //уставка для регулятора мощности ручная

extern int16_t power_time;                     //текущее время работы регулятора мощности
extern uint8_t cnt_day;
extern uint32_t cnt_off_day;
extern uint8_t eco_day[32];

extern uint8_t eco_mon[12];
extern uint8_t cnt_mon;

extern uint8_t EE_eco_day[32];
extern uint8_t EE_cnt_day;
extern uint8_t EE_eco_mon[12];
extern uint8_t EE_cnt_mon;
extern uint32_t EE_prog_array[42];
extern int16_t EE_set_temp;        //уставка для термостата ручная в EEPROMe
extern int16_t EE_set_power;       //уставка для регулятора мощности ручная в EEPROMe
extern uint16_t EE_hyst;

extern uint16_t EE_flags;

extern int real_temp;
extern int temp_max;
extern int temp_min;

extern unsigned char bcd_to_hex(unsigned char data);
extern unsigned char hex_to_bcd(unsigned char data);
extern void convert_temperature(int input_temp);
extern void convert_temperature_set(int set_temp);
extern void convert_temperature_read(int read_temp);
extern int combine_temperature(int8_t temp_whole, int8_t temp_half);
extern int combine_temperature_set(int8_t set_temp_whole, int8_t set_temp_half);
extern int combine_temperature_read(int8_t read_temp_whole, int8_t read_temp_half);


extern int convertToTemperatureInt(float temperature);
extern void checkAndSetFlag(void);
extern void checkConnectAndSync(void);

extern uint32_t GetUnixTime();
extern void ConvertUnixTimeToBytes(uint32_t unixTime);

// Глобальные переменные для байтового представления времени
extern  uint8_t UnixByte0, UnixByte1, UnixByte2, UnixByte3;
extern uint32_t UnixTime;



extern uint8_t what_day (int in_year, int in_month,int in_date );
extern uint16_t time_convert_to_min (uint16_t hours, uint16_t minutes );
extern int getNumberOfDays(int m, int y);
extern void keys(void);
extern int key_event_handling(void);
extern void screen_choice(int screen_pointer);
extern void ioinit(void);
extern void ADC_BUF_ON_OFF(int8 buf_ON);
extern void ADC_setup();
//extern  float get_resist(double_t VrefBUF,double_t  VntcBUF,double_t  R_upper);
extern double round(double x);
extern double get_tempere(double ResistNTC);
extern int8_t tempere_sensor_error(double VrefBUF,double VntcBUF,double ResistNTCBUF );
extern void GET_ADC_Value(void);
extern void power_off_t(void);
extern void power_on_t(uint8_t m);
extern void power_down_t(void);
extern void prog_check(void);
extern void tempere_out_formation(void); // усреднение и формирование выходного значения температуры!
extern void termostat(void);
extern void statistic(void);


extern int16_t Get_Temp(uint16_t adc);
extern double round(double x);
extern u8 SAM_Event(u8 x_event);

extern uint8  Task3_1;
extern uint8 Task3_1_circulation;

#define   RUN_Task        11
#define   STOP_Task       22
#define   One_Time_Task   33
#define   Reload_Task     44

#define  reload_task                  10000  //  выбранная перезагрузка Таска

#define  start_task_delay             200  // время через котрое произойдет выполнение задачи после ее СТАРТА

#define  blynk_image_T                600  // циркуляция для блемания необходимой картинки

#define  blynk_Task_T                 500 // тестовая циркуляция


extern signed short RoughCalib_Value ;// для калибровки АЦП

extern uint8 Link_ON_OFF ;// статус соединения BLE UART - установлено/ разорвано соединения

// ----------------------------------- КНОПКИ и обработчик сканирования спад/наростания--------------------------//

//--------------------------- блокировка прерывания GPIO----------------------------//
 extern uid_t  soft_block;
//----------------------------обработчик сигнала спаданте/возрастание /кнопка через GPIO INTA --------------//
 #define GPIO_scan_period                              5//6//5 // количество циклов локально таймера антидребезг
 #define delay_on_event                 (GPIO_scan_period - 1)
 extern uint8  start_key_timer;
 extern float event_key_count;
 extern uint8 event_GPIO_scan;
 extern uint8 flag;//

 //--------------------------для измерения температуры и сопротивления-----------------//

 extern int8 BLE_NEW_DATA;
 extern int8 BLE_NEW_SENOSOR_TEMPER;
 extern int8 SyncDelay;
 extern int8 SyncStart;

 extern int8 busy_transmit;
 extern int8 busy_transmit_delay;


 extern int  Tout_for_phone;
 extern uint8          invert_temp_cikl ;
 extern float         Tout,Tcur1,Tcur2;                        //Итоговая операционная температура в гр. Цельсия   float
 extern float prevTout ;
 extern int           Tout_int;                     //Итоговая операционная температура в гр. Цельсия  integer
 extern float         T;                           //Текущая температура в гр. Цельсия
 extern int           Tint;
 extern double        Tdec;
 extern double        RX;                          //Сопротивление термодатчика, Ом
 #define              R13          22.0            //Сопротивление резистора подпорки для NTC, Ом
 //#define              R19          2.0             //Сопротивление добавочного резистора, Ом
 extern double        Rn  ;                        //Номинальное сопротивление при 25°C, Ом
 #define              TN          (25.0 + 273.15)  //Номинальная температура в Кельвинах
 #define              Beta         3950.0          //Beta

#define               R19          22.0             //Сопротивление резистора подпорки клавиатуры, Ом

#define               ADC_ref          1.05            //опорное для ADC


extern double buf_resist,key_resist,key_voltage,key_voltage_out;

//--------------------------для обновления значения выводимой температуры в 9876D в программном режиме-------------

extern uint8         invert_setup_temp_cikl ;
extern int16         Tout_setup,Tcur1_setup,Tcur2_setup;
extern int8_t        tempere_setup_change;


//-------------------------------маски на порты-------------------------------------//
extern int32_t port_rel_mask,port_analog_pow_mask,port_ligth_mask,port_red_green_mask,port_CS0_mask;
//----------------------------для ТЕРМОСТАТА----------------------------------------//
extern unsigned short  HystPrepere;
#define HYST_05   5
#define HYST_10   10

extern int8_t  heat_on_off;
extern int8_t tempere_cange;

 //------------------------для  измерения(измерительно/ накопительные буферы) ADC

 extern uint32_t adcBuffSum,adcBuffKey,adcBuffShort;
 extern uint32_t adcBuffSumRef,adcBuffSumKey,adcBuffSumNtc,adcBuffSumRefShort,adcBuffSumNtcShort,adcBuffSumPowOnOff;
 extern uint8_t key_active;
 extern uint8_t UP_press;// флаг выбора режима работы кнопки MODE : UP_press=1 ( по отжатию+ возможность long delay)
 //UP_press=0 , просто по первому касанию.
 extern uint8_t key_plus_flag,key_mode_down_flag,key_mode_UP_flag,key_mode_flag,key_plus_minus_flag,long_key_mode_flag,long_key_plus_minus_flag;

#define long_key_mode_time        6//9//10
#define long_key_plus_minus_time  3

#define key_event_plus            7
#define key_event_minus           6
#define key_event_plus_minus      9
#define key_event_mode            5
#define key_event_mode_down       8

#define key_event_non             2
#define key_long_mode_yes         4
#define key_long_plus_minus_yes   3






 extern uint8_t adclen;
 extern double Vref,VrefShort,Vntc,VntcShort,VoutBuf,Vpow_on_off,VkeyShort,Vkey,VkeyRef,VkeyRefLong;
 extern int8_t Sensor_delay;// счетчик на дополнительную задержку стабилизации значения наполнения  ддинного буфера
 // при  размыкании/замыкании контактов  датчика NTC
 extern int8_t sensor_state;

# define Sensor_delay_value     18
// # define Sensor_delay_value     6


 extern uint16_t ADC_i,ii;// счетчик для ADC буфера и ii счетчик для flash буфера
 extern uint8_t s;// для вывода отладочной информации по обновлению FLASH в цикле на терминал

 extern uint8_t adcBuffLenReady,OnOff_adcBuffLenReady;

 extern uint8_t  event_type; // тип события

 extern uint8_t main_screen_enter_count;



 extern  uint8_t ON_Icon_event,OFF_Icon_event,BackLigth_event;

 //-------------------------для меню---------------------------------------------------
 extern int screen_level;
 extern int8 screen_refresh_flag ;// флаг необходимости визуального обновления всего меню


 //--------------------------------------ДЛЯ ПОДСВЕТКИ------------------------------------------
extern uint8 INTRO;
extern uint8 start_back_light;
#define  time_sek                 7 // время таймера подсветки
#define  time_sek_plus_1          8 // таймер подсветки+ задержка

extern uint8  Stand_Bay_Waike ;

//-----------ФЛАГ ОБНОВЛЕНИЯ ЗНАЧЕНИЯ RTC и требования к дальнейшей перезагрузке после flash write RTC---
extern uint8 TIME_UPDATE;
//-------------------------- ДЛЯ СБРОСА БЛЕМАНИЯ ПРИ НАБОРЕ ЗНАЧЕНИЕ В МЕНЮХАХ ---------------------------
extern uint8 start_bink;

 //----------------------------------------------------------------------------------------------


extern uint8 adc_ready;// флаг STOP/RUN  для  запуска процедуры ADC
 #define adcBuffLenPowOnOff       1
//#define adcBuffLenPowOnOff       10


// #define   adcBuffLen       200

 //#define   adcBuffLen       2500  // время интегрирования значения ADC температуры  около  0.8 сек
 //#define   adcBuffLen       500  // время интегрирования значения ADC температуры  около  0.8 сек
//#define   adcBuffLen       3000  // время интегрирования значения ADC температуры  около  0.8 сек


#define   adcBuffLen       3400  //оптимальное время интеграции при Uref=2.5 и рабочей МАХ T = 45.0 около 8 сек
 // для усреднения колебаний по питанию датчика!!

 extern uint16_t PowOnOff_ADC_count;


 extern uint8_t pin_a,pinb, sum_pin;
 extern unsigned char event_RTC,event_RTC2,event_RTC3,event_RTC4,event_key, evt,sek_count,sek_count_for_prog_anime,start_anime_blink ,sek_01_count;
 extern uint16_t adcBuff[100];
 extern uint8_t DMA_end ;

 //-----------------------------------системмные переменные и  RTC -------------------------------------------//
 extern unsigned char event_RTC,event_key, evt;
 extern unsigned short py, pmon,pd,ph,pm, ps;
 extern int16 my_py, my_pmon, my_pd, my_ph, my_pm, my_ps;
 extern int16 total_py, total_pmon, total_pd, total_ph, total_pm, total_ps;
 extern unsigned char  invert;
 extern int8  Out_Yes_No;

 //-----------------------------------переменные для PM  секции и резевной записи во FLASH---------------------//

 #define count1 25500
 #define RUN_RING_COUNT_BASE 25500






 extern uint8  START;

 extern unsigned short   TestBuf2;
 extern unsigned short    TestBuf3;

 extern unsigned short event_GPIO;
 extern unsigned char power_off,RUN,RUN_RING_event;
 extern unsigned short RUN_RING_COUNT;
 extern unsigned short TOTAL_RUN_RING_COUNT;
 extern unsigned char event_RTC_sleep;

#define event_sleep_START                                10  // для события SLEEP



 //  Романчук переменные ANALOG.h-------------------------//

#define KEY1VALUE                  25
#define KEY2VALUE                   2040
#define CLEARENCE                   100
#define KEYTRESH                    100
//-------------------------------------ADC sequence assist
#define ch_ADC0         0
#define ch_ADC1         1
#define ch_ADC2         2
#define ch_ADC3         3
#define ch_ADC4         4
#define ch_ADC5         5
#define ch_ADC6         6
#define ch_ADC7         7
#define ch_ADC8         8
#define ch_ADC9         9
#define ch_ADC10        10
#define ch_ADC11        11
#define ch_ADC12        12
#define ch_ADC13        13
#define ch_ADC14        14
#define ch_ADC15        15
#define ch_ADCTINT      16
#define ch_ADCVREF      17
//---------------------------------hardware
#define     ADC_DR_OFFSET         0x4c
#define     N_ADC_CONVERTIONS   5
#define   SENSORS           3
//----------------------------------types
 /*
typedef struct{
        s16 valueid;                //код кнопки
        s16 integ;          //интегратор
        s16 lastval;                //последнее значение
        u16 bitmap;         //конфиг и биты
}button;
*/
//---------------------конфиг и биты
#define     NOT_RELEASED    0x0001
#define     LONG_SHOT       0x0002
#define     SHORT_SHOT      0x0004

#define     SHORTTYPE         0x8000
#define   KEYS                  (LONG_SHOT|SHORT_SHOT)
//-----------------------globals
//extern button  but1,but2,but3,but4;
//prototypes for external use
extern void    init_adc(void);      //вызывать один раз
extern void  init_keys(void);   //вызывать один раз
extern void  adc_pass(void);        //1мс функция
extern s16   is_temp_err(void); //ошибка по каналам
extern s16   is_internal(void); //return 1 when internal sensor
extern s16   temperature(void); //выбранная температура
extern s16   poly(void);
extern s16   intsensor(void);
extern s16   extsensor(void);
extern s16   aircvalue(void);
extern s16   debugget(void);
extern float limit_f(float,float,float);
extern s16   abs_s16(s16);

//---------------------------------из файла Романчук Main.


//---------------------------definations of variables

//------------define  my constants
#define IWDG_RELOAD_VALUE   0x0fff
#define MY_PRIORIRY     0xf0UL      //lowest
#define PGROUPS16_PSUBG0    ((u32)0x300)    //16 groups subpriority 0, already alligned
//------------define  system constants
#define IWDG_KEY_ENABLE     0xCCCC
#define IWDG_KEY_RESET      0xAAAA
#define IWDG_KEY_ACSESS     0x5555
#define AIRCR_VECTKEY_MASK    ((u32)0x05FA0000)

#define AHB_CLK_HZ          8000000L    //1 mhz
#define VTIMER_PSC_CLK_HZ       100000L     //100khz
#define VTIMER_PSC_VALUE        ((AHB_CLK_HZ/VTIMER_PSC_CLK_HZ)-1)
#define VTIMER_PSC_CLK_MKS      (1000000L/VTIMER_PSC_CLK_HZ)
#define VTIMER_TICK_MKS         1000L       //1ms tick
#define VTIMER_ARR_VALUE        ((VTIMER_TICK_MKS/VTIMER_PSC_CLK_MKS)-1)


#define TIME1s          (1000000L/VTIMER_TICK_MKS)      //in ticks
#define TIME2s          TIME1s*2
#define TIME5s          TIME1s*5
#define TIME3s          TIME1s*3
#define TIME10s         TIME1s*10
#define TIME3M          ((s32)TIME1s*180)
#define TIME2_5S        ((TIME1s*25)/10)
#define TIME50MS        (1000*50/VTIMER_TICK_MKS)       //
#define TIME100MS       (1000*100/VTIMER_TICK_MKS)      //
#define TIME200MS       (1000*200/VTIMER_TICK_MKS)      //
#define TIME_BLINK_OFF      (1000*700/VTIMER_TICK_MKS)      //700ms
#define TIME_BLINK_ON       (1000*900/VTIMER_TICK_MKS)      //900ms

#define SHORT_BUTTON_TIME_MKS    225000L                //300ms its for holding case
#define SHORT1_BUTTON_TIME_MKS   30000L                 //40ms its for release case
#define LONG_BUTTON_TIME_MKS    1500000L                //1000 ms
#define SHORTPRESS  (SHORT_BUTTON_TIME_MKS/VTIMER_TICK_MKS)
#define SHORTPRESS2 (SHORT1_BUTTON_TIME_MKS/VTIMER_TICK_MKS)
#define LONGPRESS   (LONG_BUTTON_TIME_MKS/VTIMER_TICK_MKS)  //1.5 second
#define INTEG_LIMIT     0x1000                  //some  limit for button
//------------------------------menu limits/values
#define CONTROL_MAX     2L      // control menu has 3 entries
#define CONTROL_MIN     0L
#define CONTROL_HANDLE_ENTRY    0L
#define CONTROL_PROG_ENTRY  1L
#define CONTROL_TIME_ENTRY  2L

//---------------------------
#define LOCK_ENTRY                0L
#define PWM_ENTRY                     1L
#define HYST_ENTRY              2L
#define HILO_ENTRY              3L
#define SERVICE_TIME_ENTRY      4L
#define SERVICE_ECONOMY_ENTRY1  5L
#define SERVICE_ECONOMY_ENTRY2  6L
#define SERVICE_DEFAULT         7L
#define SERVICE_OUT_ENTRY         8L

#define SERVICE_MAX     8L      // control menu has 9 entries
#define SERVICE_MIN     0L
//-----------------------------------

#define TIME_NAVIGATOR_HOUR 0x00000001
#define TIME_NAVIGATOR_MINUTE   0x00000002
#define TIME_NAVIGATOR_YEAR 0x00000004
#define TIME_NAVIGATOR_MONTH    0x00000008
#define TIME_NAVIGATOR_DATE 0x00000010
#define TIME_NAVIGATOR_END  0x00000020

//---------------------PWM  in miliseconds/percents
//#define PWMPERIOD             3600000L  //60min
//#define PWMUNIT                   36000L          //1% in seconds
#define PWMPERIOD               2700000L  //45min
#define PWMUNIT                 60000L    //1min
//------------------backup
#define BKP_POINTER_LAST    18L
#define BKP_DATE_LAST       17L
#define BKP_PERCENTAGE      16L
#define DAY_MIN         0L
#define DAY_MAX         15L

#define MONTH_MIN       0L
#define MONTH_MAX       11L
#define YEAR_MASK       0xf000
#define MONTH_MASK      0x0f00
#define PERCENTAGE      0x00ff
#define PERCENTAGE2     0x007f
#define HALF_MONTH      0x0080

#define DAY_MINUTES_MIN     0L
#define DAY_MINUTES_MAX     1439L       //(24*60-1)=1440-1
#define WEEK_DAY_MIN        0L
#define WEEK_DAY_MAX        6L


#define PROG_SEQ_HOUR       0x00000001  //
#define PROG_SEQ_MINUTE     0x00000002  //
#define PROG_SEQ_TEMP       0x00000004  //
#define PROG_SEQ_MASK_END   0x00000008

#define DAY_INTERVALS       6L      //6 intervals total
#define INTERVAL_MAX    (DAY_INTERVALS-1)
#define INTERVAL_MIN        0L

#define HOUR_MAX        23L
#define HOUR_MIN        0L
#define MINUTE_MAX      59L
#define MINUTE_MIN      0L

#define HOUSES_ALL_ON       6
//---------------------------defination of menu
#define     MAIN_SCREEN                0
#define     PROG_MENU                  1
#define     TIME_MENU                  2
#define     SELECT_DAY_FOR_PROG        3
#define     PROG_SELECTED_DAY          4
#define     CONTROL_MENU               5
#define     STANDBY_MODE               6
#define     SERVICE_MENU               7
#define     COPY_DAY_MENU              8
#define     SERVICE_TIME               9
#define     SERVICE_ECO2              10
#define     SERVICE_LOCK              11
#define     SERVICE_DEF               12
#define     SERVICE_PWM               13
#define     SERVICE_HYST              14
#define     SERVICE_HILO              15
#define     HILO_MENU                 16

#define     TEST_TASK_MENU                 17


//---------------------------defination of hardware
#define OUT0_high
#define OUT0_low
#define CHECK_OUT
#define OUT0_TGL

#define BACKLED_ON
#define BACKLED_OFF
#define CHECK_BLED

#define OUT_MASK    (p0|p1)
//---------------debug
/*#define LED_PC8ON    GPIOC->ODR|=p8
#define LED_PC8OFF   GPIOC->ODR&=~p8
#define LED_PC8TGL   GPIOC->ODR^=p8

#define LED_PC9ON    GPIOC->ODR|=p9
#define LED_PC9OFF   GPIOC->ODR&=~p9
#define LED_PC9TGL   GPIOC->ODR^=p9*/
//-------------------defination in config bitpattern register
#define     CONTROL                     0x0001
#define     TIME_TEMP_SHOW      0x0002
#define     STATE_OFF             0x0004
#define     LOCK_FEATURE          0x0008
//#define       ADAPTIVE              0x0010
#define     PWM                 0x0020

#define     STATE_ON        0x0000

//------------------------------
#define FULLROUND (58*60)
#define PART1 (18*60)
#define PART2 (23*60)
#define PART3 (38*60)
#define PART4 (48*60)

#define HYST11  9
#define HYST12  9
#define HYST13  9
#define HYST14  9
#define HYST15  9

#define HYST1C  7

#define HYST2   8
#define HYST3   5
#define HYST4   4
#define HYST5   4
#define HYST6   4

#define HYST2C   ((signed int)2)
#define HYST3C   ((signed int)0)
#define HYST4C   ((signed int)0)
#define HYST5C   ((signed int)0)
#define HYST6C   ((signed int)0)
//---------------------------defination of flags
#define     RTC_FAILED        0x00000001
#define     FLASH_DEFAULT       0x00000002
#define     INTRO_EVENT       0x00000004    //means menu was changed and new menu "intro event"
#define     OVERRIDE            0x00000008  //this need for "comfort"
#define     UP_DOWN_TOUCH       0x00000010  //was "+" ,"-" activity
#define     TAMPERSET           0x00000020  //1- auto, 0-handle
#define     ADC_NOTREADY        0x00000040  //1- adc ready
#define     BLINK                 0x00000080
#define     LOCK_STATE          0x00000100
#define     SAVE_FLASH        0x00000200
#define     RECOVERY            0x00000400
#define     UP_DOWN_TOUCH2  0x00000800  //was "+" ,"-" activity
#define     LOCK_WINDOW         0x00001000
#define   PWMFIRE                   0x00002000
#define   HOTOCCUR              0x00004000
#define   INITDAYEDIT           0x00008000
#define   DAYCOPY                 0x00010000
#define   DEFAULT_BIT     0x00020000   //used in default entry (service menu)
#define   ANIME           0x00040000
#define   KEYACTIVITY           0x00080000
#define   RESETHOT              0x00100000
#define   OUTBUFFER             0x00200000
#define   LAGRELAY              0x00400000
#define   BACKLIGHTBIT      0x00800000
#define   BACKLOCK        0x01000000
//------------------------
#define BACKLIGHT_ON   flags|=BACKLIGHTBIT
#define BACKLIGHT_OFF  flags&=~BACKLIGHTBIT
#define CHECK_BL       flags&BACKLIGHTBIT
//---------------------
#define   RATEMINHOUR     0.1               //celisium in hour
#define   RATEMAXHOUR     10.0      //celisium in hour
#define   RATEMIN  (RATEMINHOUR/6.0)  // rate in min *10, cause of temp*10 representation
#define   RATEMAX  (RATEMAXHOUR/6.0)
//----------------------


//--------------globals


extern u32 flags;

extern s16 v_timer_SK;
extern s16 v_timer2;
extern s16 v_timer_blink;
extern s16 v_timer_save;
extern s16 keytimer;
extern s16 locktimer;
extern s16 BL_timer;
extern s16 lagtimer;
extern s16 animetimer;
extern s16 debug1;
extern s16 deb2;
extern int deb3;
extern s16 current_percentage;
extern int menu;
extern int control_menu_navigate,time_menu_navigate,pro_tune_menu_navigate,copy_day_menu_navigate,
           copy_day_sourse,copy_day_receiver,select_day_for_prog_menu_navigate,
           prog_selected_day_menu_navigate,service_menu_navigate;
extern int selected_day;

extern int override_temp;
extern int setup_temp_load;
extern int setup_temp;


extern bool  isConnected, prewiosisConnected;    // СТАТУС ПЕРЕМЕННАЯ "Link Status"  - получает состояние по событию сразу  после  Connect /Disconnect

extern int8_t temp_whole;  // Глобальная переменная для целой части температуры
extern int8_t temp_half;   // Глобальная переменная для половинки градуса (0 или 5)


extern  int8_t temp_whole_set;  // Глобальная переменная для целой части температуры
extern  int8_t temp_half_set;   // Глобальная переменная для половинки градуса (0 или 5)

extern  int8_t temp_whole_read;  // Глобальная переменная для целой части температуры
extern  int8_t temp_half_read;   // Глобальная переменная для половинки градуса (0 или 5)







//extern int8 sfm_min;
extern int edit[3];
extern s32 pwmtimer;
extern s32 pwmtres;
extern s16 pwmhold;
extern s16 pwmlast;
extern int trial_timer;
extern int targettemp;
extern int targetinterval;
extern float lastrate;
extern int timetrigger;
extern s16 out_last;
extern s16 lowcnt;
extern s16 highcnt;
extern s16 templast;
extern s16 tempnew;
extern s16 adaptfsm;
extern s16 uptresh;
extern s16 dntresh;
extern s16 hyst;

//0(0day 5interval time),1(0-0day 5interval temperature) even -always temp odd-interval
//thus values descending  moon->housein->barout->barin->houseout->sun,from 0 to 6 day
//-time is daytime in minutes,temp is celsium*10
extern int current_interval;
extern int cur_set_temp;
extern int cur_set_time;
extern int cur_offset;
extern s16 bkldimtimer;
extern s16 bklpwmtimer;
extern s16 parameters[24];
//---------------------------
extern int service_nav;
extern int dayedit;
extern int dayoffset;
extern int dummy;
extern int day_prog_edit;
extern int time_nav;
extern int interval_seq;
extern int actual_interval;
extern int time_edit[2];   //first- day, second-minutes
extern int control;
extern int hilo;
extern int edit_temp;
extern s16 daysource;
extern char cdeb;
extern s16  heatsigntimer;


extern void    save_on_off(u16);
extern int   is_select(void);
extern int     is_OK_LH(void);             //checks if was "ok" long shot,exlusive operation
extern int     is_OK_SH(void);             //checks if was "ok" short shot,exlusive operation
extern int     is_BK_LH(void);             //checks if was "ok" long shot,exlusive operation
extern int     is_BK_SH(void);             //checks if was "ok" short shot,exlusive operation
extern void  is_change(int*, int, int);
extern void  is_change2(int*, int, int);
extern void  loop_ch(int*, int, int);
extern void  pwm_ch(void);
extern void  exlusive_behavior(void);
extern void    make_out(int);
extern void  setactivity(void);
extern s16   restore_control(u16);
extern s16   restore_handle_temp(void);
extern void    check_set_separator(void);
extern void    parametr_save(s16, s16);
extern void    toggle_control_bit(s16);
extern char    read_backup(int);
extern void    merge_interval_time(int, int);              //for edit
extern void    split_interval_time(int, int);              //for edit
extern int   get_interval_time(int, int);                 // gives interval daytime minutes
extern int   get_interval_temp(int, int);                 // gives interval temperature
extern void    set_interval_time(int, int, int);                  // sets interval daytime minutes
extern void    set_interval_temp(int, int, int);                  // sets interval temperature
extern void    check_control_change(void);
extern void  make_anime(s16);
extern void  backlightoff(void);


//------------------------------ FOR DEBUG --------------------------------
extern uint8_t SCi,SCy;


/************************END OF FILE**************************/
