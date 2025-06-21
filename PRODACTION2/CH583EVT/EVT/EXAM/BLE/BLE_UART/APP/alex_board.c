/* MAIN.C file

 /* Includes ------------------------------------------------------------------*/


//#include "alex_v3_lcd.h"
#include "my_large_LCD32.h"
//#include "alex_v3_rtc.h"
//#include "eeprom.h"


#include "CONFIG.h"
#include <math.h>
#include "my_assist32.h"
#include "alex_board.h"
#include "main_vlad.h"
#include "menu_vlad.h"
#include "ext_my_directtest.h"
#include "my_test.h"
#include "lcd_test.h"



//uint8  Task3_1= STOP_Task;// по умолчанию остановлен
uint8  Task3_1= RUN_Task;// дернули - запустили цикл
uint8  Task3_1_circulation = RUN_Task;

//uint8  Task3_1_circulation = One_Time_Task;



signed short RoughCalib_Value = 0;// для калибровки АЦП

uint8 Link_ON_OFF = 0;// статус соединения BLE UART - установлено/ разорвано соединения



typedef struct{
        s16 valueid;                //код кнопки
        s16 integ;          //интегратор
        s16 lastval;                //последнее значение
        u16 bitmap;         //конфиг и биты
}button;





button  but1,but2,but3,but4;

//--------------------------- блокировка прерывания GPIO----------------------------//
 uid_t  soft_block=0;
//----------------------------обработчик сигнала спаданте/возрастание /кнопка через GPIO INTA --------------//
 uint8 event_GPIO_scan=0;
 uint8  start_key_timer=0;
 float event_key_count=0;
 uint8 flag;//
//--------------------------для измерения температуры и сопротивления-----------------//

 int8 BLE_NEW_DATA;
 int8 BLE_NEW_SENOSOR_TEMPER;
 int8 SyncStart;
 int8 SyncDelay;

 int8 busy_transmit;
 int8 busy_transmit_delay;





 int  Tout_for_phone;
 uint8          invert_temp_cikl =0;
 float         Tout,Tcur1= - 40.0,Tcur2= -40.0;                        //Итоговая операционная температура в гр. Цельсия
 float prevTout = 0.0;
 int           Tout_int;
 float         T=0;                         //Текущая температура в гр. Цельсия
 int           Tint;
 double        Tdec;
 double        RX;                          //Сопротивление термодатчика, Ом
 double        Rn       =   10000.00;           //Номинальное сопротивление при 25°C, Ом

 double buf_resist,key_resist,key_voltage,key_voltage_out;
 //--------------------------для обновления значения выводимой температуры в 9876D в программном режиме-------------

 uint8         invert_setup_temp_cikl =0;
 int16         Tout_setup,Tcur1_setup= 0,Tcur2_setup= 0;
 int8_t        tempere_setup_change=0;


//-------------------------------маски на порты-------------------------------------//
int32_t port_rel_mask,port_analog_pow_mask,port_ligth_mask,port_red_green_mask,port_CS0_mask;
//----------------------------для ТЕРМОСТАТА----------------------------------------//

unsigned short  HystPrepere  = HYST_10;// значение по умолчанию 1,0 С ( а по факту 1,5 С)
int8_t  heat_on_off=0;
int8_t tempere_cange=0;

 //------------------------для  измерения(измерительно/ накопительные буферы) ADC
 uint32_t adcBuffSum=0,adcBuffKey=0,adcBuffShort=0;
 uint32_t adcBuffSumRef=0,adcBuffSumKey,adcBuffSumNtc=0,adcBuffSumRefShort=0,adcBuffSumNtcShort=0,adcBuffSumPowOnOff=0;

 uint8_t key_active=0; // флаг активности клавиатуры
 uint8_t UP_press=0;//// флаг выбора режима работы кнопки MODE : UP_press=1 ( по отжатию+ возможность long delay)
 //UP_press=0 , просто по первому касанию.
 uint8_t key_plus_flag=0,key_minus_flag=0,key_mode_down_flag=0,key_mode_UP_flag=0,key_plus_minus_flag=0,long_key_mode_flag=0,long_key_plus_minus_flag=0;
 uint8_t adclen;
 uint8_t adcBuffLenReady=0,OnOff_adcBuffLenReady=0;

 uint8_t  event_type;  // тип события

 uint8_t main_screen_enter_count=0;// счетчик количества входа в MAIN


 uint8_t ON_Icon_event=0,OFF_Icon_event=0,BackLigth_event=0;


 uint8    device_on_off =   0;  // при сбросе прибор включается если не сохранить состояние во FLASH

 uint8    device_default = 0;//  по умолчанию режим "СБРОС" равен  0, его можно активировать в Servise Menu

 uint8    LOC_on_off =   0;  // по умолчанию, блокировка клавиатуры отключена!!!

 uint8    lock_key = 0;// регистр управления  блокировкой/ разблакировкой  клавиатуры



 //-------------------------для обновления FLASH --------------------------------------
 uint8 FLASH_UPDATE=0; // флаг обновления FLASH  1 -  нужно обновить,  0 - не нужно
 uint8 SCHEDULE_UPDATE=0; // флаг обновления FLASH  1 -  нужно обновить,  0 - не нужно

 uint8 BUSY_KEY=0;
 uint8 BUSY_KEY2=0;
 uint8 BUSY_KEY3=0;

 //-------------------------для меню---------------------------------------------------

 int screen_level=0;
 int8 screen_refresh_flag = 0;// флаг необходимости визуального обновления всего меню

//---------------------- для подсветки ------------------------------------------------
uint8    INTRO=1;
uint8    start_back_light=0;
#define  time_sek      7

uint8  Stand_Bay_Waike = 0;              // флаг выхода из режима Stand Bay  - аля типа включен экран (а все остальное работает)

//-----------ФЛАГ ОБНОВЛЕНИЯ ЗНАЧЕНИЯ RTC и требования к дальнейшей перезагрузке после flash write RTC---
uint8 TIME_UPDATE=0;

//-------------------------- ДЛЯ СБРОСА БЛЕМАНИЯ ПРИ НАБОРЕ ЗНАЧЕНИЕ В МЕНЮХАХ ---------------------------

uint8 start_bink=1;


 double Vref=0,VrefShort=0,Vntc=0,VntcShort =0,VoutBuf=0,Vpow_on_off=0,VkeyShort=0,Vkey=0,VkeyRef=0,VkeyRefLong=0;

 int8_t Sensor_delay =0;// счетчик на дополнительную задержку стабилизации значения наполнения  ддинного буфера
 // при  размыкании/замыкании контактов  датчика NTC
 int8_t sensor_state;



 uint8 adc_ready=0;// флаг STOP/RUN  для  запуска процедуры ADC
 uint16_t ADC_i=0,ii=0;//  счетчик для ADC буфера и ii счетчик для flash буфера
 uint8_t s;// для вывода отладочной информации по обновлению FLASH в цикле на терминал
 uint16_t PowOnOff_ADC_count;

 uint8_t pin_a,pinb, sum_pin;
 uint16_t adcBuff[100];
 uint8_t DMA_end = 0;

 //-----------------------------------системмные переменные и  RTC -------------------------------------------//
 unsigned char event_RTC,event_RTC2,event_RTC3,event_RTC4,event_key, evt,sek_count=0,sek_count_for_prog_anime =0,start_anime_blink =0,sek_01_count=0;
 unsigned short py, pmon, pd, ph, pm, ps;
int16 my_py=0, my_pmon=0, my_pd=0, my_ph=0, my_pm=0, my_ps=0;
int16 total_py=0, total_pmon=0, total_pd=0, total_ph=0, total_pm=0, total_ps=0;

 unsigned char  invert = 0;
 int8  Out_Yes_No = 0;

//-----------------------------------переменные для PM  секции и резевной записи во FLASH---------------------//


uint8  START=0;// флаг инициализации прохождения начального загрузчика при подачи питания Start_Boot
unsigned short   TestBuf2;
unsigned short    TestBuf3;

unsigned short event_GPIO=0;
unsigned char power_off=0,RUN=255,RUN_RING_event=255;
unsigned short RUN_RING_COUNT=RUN_RING_COUNT_BASE;
unsigned short TOTAL_RUN_RING_COUNT=0;
unsigned char event_RTC_sleep=0;




 uint8_t what_day (int in_year, int in_month,int in_date );
 uint16_t time_convert_to_min (uint16_t hours, uint16_t minutes );
 int getNumberOfDays(int m, int y);
 double  get_resist(double VrefBUF,double VntcBUF,double R_upper);
 double get_tempere(double ResistNTC);
 double round(double x);
 int8_t tempere_sensor_error(double VrefBUF,double VntcBUF,double ResistNTCBUF );
 void ADC_BUF_ON_OFF(int8 buf_ON);
 void ADC_setup();
 void GET_ADC_Value(void);
 void keys(void);
 int key_event_handling(void);
 void screen_choice(int screen_pointer);
 void tempere_out_formation(void); // усреднение и формирование выходного значения температуры!
 void termostat(void);



double round(double x);
u8 SAM_Event(u8 x_event);

//---------------------------------из файла Романчук Main.c

//---------------------------definations of variables

u32 flags;

s16 v_timer_SK;
s16 v_timer2;
s16 v_timer_blink;
s16 v_timer_save;
s16 keytimer;
s16 locktimer;
s16 BL_timer;
s16 lagtimer;
s16 animetimer;
s16 debug1;
s16 deb2;
int deb3;
s16 current_percentage;
int menu;
int control_menu_navigate=0,time_menu_navigate=0,pro_tune_menu_navigate=0,copy_day_menu_navigate=0,
    copy_day_sourse=1,copy_day_receiver=1,select_day_for_prog_menu_navigate=1,
    prog_selected_day_menu_navigate=0,service_menu_navigate=0;
int selected_day =0;
int override_temp;

//int setup_temp_load=270;
int setup_temp  ;


//int8 sfm_min=5;
int edit[3];
s32 pwmtimer;
s32 pwmtres;
s16 pwmhold;
s16 pwmlast;
int trial_timer;
int targettemp;
int targetinterval;
float lastrate;
int timetrigger;
s16 out_last;
s16 lowcnt;
s16 highcnt;
s16 templast;
s16 tempnew;
s16 adaptfsm;
s16 uptresh;
s16 dntresh;
s16 hyst;



// Глобальные переменные для байтового представления времени
uint8_t UnixByte0, UnixByte1, UnixByte2, UnixByte3;
uint32_t UnixTime;


bool  isConnected, prewiosisConnected;    // СТАТУС ПЕРЕМЕННАЯ "Link Status"  - получает состояние по событию сразу  после  Connect /Disconnect


int8_t temp_whole;  // Глобальная переменная для целой части температуры
int8_t temp_half;   // Глобальная переменная для половинки градуса (0 или 5)


 int8_t temp_whole_set;  // Глобальная переменная для целой части температуры
 int8_t temp_half_set;   // Глобальная переменная для половинки градуса (0 или 5)

 int8_t temp_whole_read;  // Глобальная переменная для целой части температуры
 int8_t temp_half_read;   // Глобальная переменная для половинки градуса (0 или 5)



//0(0day 5interval time),1(0-0day 5interval temperature) even -always temp odd-interval
//thus values descending  moon->housein->barout->barin->houseout->sun,from 0 to 6 day
//-time is daytime in minutes,temp is celsium*10
int current_interval;
int cur_set_temp;
int cur_set_time;
int cur_offset;
s16 bkldimtimer;
s16 bklpwmtimer;
s16 parameters[24];
//---------------------------
int service_nav;
int dayedit;
int dayoffset;
int dummy;
int day_prog_edit;
int time_nav;
int interval_seq;
int actual_interval;
int time_edit[2];   //first- day, second-minutes
int control;
int hilo;
int edit_temp;
s16 daysource;
char cdeb;
s16  heatsigntimer;
//---------------------------



s16   restore_control(u16 mask){return(parameters[0]&mask);}        //проверка бита конфигурации



//------------------------------ FOR DEBUG --------------------------------
uint8_t SCi,SCy;






///////////////////////////////////////////////////////////////////////////////////////

 int getNumberOfDays(int m, int y)
    {
        int leap = (1 - (y % 4 + 2) % (y % 4 + 1)) * ((y % 100 + 2) % (y % 100 + 1)) + (1 - (y % 400 + 2) % (y % 400 + 1));

        return 28 + ((m + (m / 8)) % 2) + 2 % m + ((1 + leap) / m) + (1/m) - (leap/m);
    }


 uint8_t what_day (int in_year, int in_month,int in_date )
 {

     uint8_t return_val;

     in_year=in_year-2000;

     int a = (14 - in_month) / 12;
     int y = (2000 + in_year) - a;
     int m = in_month + 12 * a - 2;
     return_val = (uint8_t)((7000 + (in_date + y + y / 4 - y / 100 + y / 400 + (31 * m) / 12)) % 7);

     if(return_val==0){
     return return_val=7;}
     else {
     return return_val;
    }

         //воскресенье = 7,понедельник = 1,вторник = 2, и т.д.
 }


 uint16_t time_convert_to_min (uint16_t hours, uint16_t minutes )
 {
 int mux ;//

 mux = hours*60 + minutes;


 return mux;

 }



void GET_ADC_Value(void);






void keys(void)//50 mS
{

    if(VkeyShort>3.10) // если напряжение ядра более 2,9- обновляем его
               {
         VkeyRef = VkeyShort;
        //VkeyRef = 3.5;
              }

         key_voltage_out =   VkeyShort / (VkeyRef/100.00); // меряем текущее значения  кнопок с учетом VkeyRef, в процентах от VkeyRef


         //if((key_voltage_out < (100*1.03)) & (key_active ==0)) //+ 4% ловим изменение относительно Vref  и обрабатываем
         if((key_voltage_out < (100*1.00)) & (key_active ==0)) //+ 4% ловим изменение относительно Vref  и обрабатываем
             // далее сами кнопки + даем алгоритм локальным таймером "антидребезговой" задержки
            {


         if((key_voltage_out<=58)&(key_voltage_out>=53))
            {
             key_active =1;
             key_plus_flag =1;
             }

         if((key_voltage_out<46)&(key_voltage_out>38))
            {
             key_active =1;
             key_minus_flag =1;
            }

         if((key_voltage_out<34)&(key_voltage_out>26))
            {
             key_active =1;
             key_plus_minus_flag=1;
            }

         if(key_voltage_out<5) // если кнопка MODE нажата

         //if((key_voltage_out<52)&(key_voltage_out>48))
              // если кнопка MODE нажата
            {
             key_active =1;
             key_mode_down_flag =1;
            }

            }

    //----------------------------------------------------------------------------------------------------

            if((key_active ==1)&( start_key_timer==0))
             {
             start_key_timer =1;
             }

            if( (event_GPIO_scan<=GPIO_scan_period)&( start_key_timer==1))
             {
             event_GPIO_scan++;// наполняем  значение счетчика задержки "антидребезга"
             }

            if((event_GPIO_scan>GPIO_scan_period))
             {
             event_GPIO_scan=0; // обнуляем счетчик
             start_key_timer =0;// остановили локальный таймер задержки  после первого срабатывания кнопки
             key_active=0;// сбросили флаг нажатой кнопки

//--------------- контрольно проверяем удержание нажатия кнопки /кнопок  и фиксируем "LONG PRESS"-------------------------

             if(UP_press==1)// если разрешен режим по отжатию + Long Press
                {
            if((key_voltage_out<5)) // если кнопка MODE  "есть нажатие" то фиксируем счетчик нажатий
             {
             long_key_mode_flag++;


             key_active=1; // нажатие кнопки
             }
          else
             {
             long_key_mode_flag=0; // если MODE "нет нажатия" ,значит отпускание кнопки , и счетчик нажатия обнуляется
             }
                }
//-----------------------------------------------------------------------------------------------------
             if(UP_press==1)// если разрешен режим по отжатию + Long Press
                           {
          if((key_voltage_out<34)&(key_voltage_out>26)) // если кнопка "+" и "-"  "есть нажатие" то фиксируем счетчик нажатий
            {
             long_key_plus_minus_flag++;
            }
             else
            {
           long_key_plus_minus_flag=0; // если кнопка "+" и "-"  "нет нажатия" ,значит отпускание кнопки , и счетчик нажатия обнуляется
            }
                           }
//--------------------------------------------------------------------------------------------------------

       if(UP_press==1)// если разрешен режим по отжатию + Long Press
       {
         if((key_voltage_out>(VkeyRef-0.2))&(key_mode_down_flag ==1)) // если кнопка MODE  "есть отжатие" после того как
                {                                           // словивили  key_mode_down_flag ==1, то фиксируем
                key_mode_UP_flag++;                         // событие "отжатия" предварительно нажатой кнопки "MODE"
                }
             else
                {
                 key_mode_UP_flag=0; // если MODE "нет нажатия" ,значит отпускание кнопки , и счетчик нажатия обнуляется
                }
       }
   //-----------------------------------------------------------------------------------------------------------------

              }

}




void screen_choice(int screen_pointer)
{

    menu= screen_pointer;
    clear_screen();

    #define  DEBUG_print_out
     #ifndef  DEBUG_print_out
         GPIOA_SetBits(bTXD1);
         GPIOA_ModeCfg(bTXD1, GPIO_ModeOut_PP_5mA);
         PRINT(" event_type    =%d\n", event_type);
         PRINT(" screen_level    =%d\n", screen_level);
         PRINT(" menu    =%d\n", menu);
         printf("--      \n");
         DelayMs(10);// задержка для очистки мусора гипертерминала  перед  GPIOA_ModeCfg(bTXD1, GPIO_ModeIN_PD)
         GPIOA_ModeCfg(bTXD1, GPIO_ModeIN_PD);
     #endif



    switch (menu){

        case MAIN_SCREEN:            main_menu();                break;
        case SERVICE_MENU:           service_menu();             break;
        case PROG_MENU:              prog_menu();                break;
        case TIME_MENU:              time_menu();                break;
        case PROG_SELECTED_DAY:      prog_selected_day();        break;
        case CONTROL_MENU:           control_menu();             break;
        case COPY_DAY_MENU:          copy_day_menu();            break;
        case SERVICE_LOCK:           loc_entry();                break;
        case SERVICE_DEF:            default_entry();            break;
        case SERVICE_HYST:           hysteresis_entry();         break;

        case TEST_TASK_MENU :        TEST_Task();                 break;


        }










}







int key_event_handling(void)
{

    int event_retern =0;

    if(key_plus_flag ==1)
       {
          key_plus_flag =0;
          Count_Tik = Count_Tik+1;

#define  DEBUG_key_event_handling

#ifndef  DEBUG_key_event_handling
          GPIOA_SetBits(bTXD1);
          GPIOA_ModeCfg(bTXD1, GPIO_ModeOut_PP_5mA);
          printf("  <<  key_plus_flag  >>       =%d  \n",      Count_Tik  );
          printf("--      \n");
          GPIOA_ModeCfg(bTXD1, GPIO_ModeIN_PD);
#endif
           event_retern= key_event_plus;
       }

       if(key_minus_flag ==1)
       {
          key_minus_flag =0;
          Count_Tik = Count_Tik-1;
#ifndef  DEBUG_key_event_handling
          GPIOA_SetBits(bTXD1);
          GPIOA_ModeCfg(bTXD1, GPIO_ModeOut_PP_5mA);
          printf("  <<  key_minus_flag  >>       =%d  \n",      Count_Tik  );
          printf("--      \n");
          GPIOA_ModeCfg(bTXD1, GPIO_ModeIN_PD);
#endif
          event_retern =  key_event_minus;
       }




     // в зависимости от режима пользовательского интерфейса можно переключаться на разній режим анализа

    /// по "отжиманию" для релизации  функции длинного нажатия в динамическом меню  - но низкаю чуствительность

       if(UP_press==1)
       {
        if(key_mode_UP_flag ==1) // если произошло срабатывание одиночное кнопки MODE по ОТПУСКАНИЮ но
       {                          // но до момента срабатывания "ДИННОЕ НАЖАТИЕ"
           key_mode_down_flag =0;
           key_mode_UP_flag =0;

         // Count_Tik = Count_Tik+1;
#ifndef  DEBUG_key_event_handling
          GPIOA_SetBits(bTXD1);
          GPIOA_ModeCfg(bTXD1, GPIO_ModeOut_PP_5mA);
          printf("  <<  key_mode_flag  >>       =%d  \n",      Count_Tik  );
          printf("--      \n");
          GPIOA_ModeCfg(bTXD1, GPIO_ModeIN_PD);
#endif
          event_retern =  key_event_mode;// возвращает в результате "отжатия"

        }
       }  else {

// по "касанию" для релизации  функции короткого нажатия
        if(key_mode_down_flag ==1) // если произошло срабатывание одиночное кнопки MODE по ОТПУСКАНИЮ но
           {                          // но до момента срабатывания "ДИННОЕ НАЖАТИЕ"
               key_mode_down_flag =0;
               //key_mode_UP_flag =0;

              //Count_Tik = Count_Tik+1;
    #ifndef  DEBUG_key_event_handling
              GPIOA_SetBits(bTXD1);
              GPIOA_ModeCfg(bTXD1, GPIO_ModeOut_PP_5mA);
              printf("  <<  key_mode_flag  >>       =%d  \n",      Count_Tik  );
              printf("--      \n");
              GPIOA_ModeCfg(bTXD1, GPIO_ModeIN_PD);
    #endif
              //event_retern =   key_event_mode_down;
              event_retern =  key_event_mode; // возвращает в результате касания

            }

       }




       if(long_key_mode_flag>long_key_mode_time) // если нажатие продолжается N раз - то фиксируем "длинное нажатие
       {
          key_mode_UP_flag=0;// обнуляем флаги нажатия  и отпускания для  кнопки MODE
          key_mode_down_flag=0;// что бы не ловить ложное короткое срабатывание после отпускания "длинного нажатия"

          long_key_mode_flag=0;
          Count_Tik = Count_Tik+30;
#ifndef  DEBUG_key_event_handling
          GPIOA_SetBits(bTXD1);
          GPIOA_ModeCfg(bTXD1, GPIO_ModeOut_PP_5mA);
          printf("  << LONG PRESS MODE >>       =%d  \n",    Count_Tik  );
          printf("--      \n");
          GPIOA_ModeCfg(bTXD1, GPIO_ModeIN_PD);
#endif
          event_retern =  key_long_mode_yes;
        }

       if(key_plus_minus_flag ==1)
        {
        key_plus_minus_flag =0;
        event_retern =  key_event_plus_minus;
        }

       if(long_key_plus_minus_flag>long_key_plus_minus_time) // если нажатие продолжается N раз - то фиксируем "длинное нажатие
        {
        long_key_plus_minus_flag=0;
        plus_minus_Tik = plus_minus_Tik+50;
        Count_Tik = Count_Tik+50;
#ifndef  DEBUG_key_event_handling
        GPIOA_SetBits(bTXD1);
        GPIOA_ModeCfg(bTXD1, GPIO_ModeOut_PP_5mA);
        printf("  << LONG PRESS PLUS & MINUS  >>       =%d  \n",    plus_minus_Tik  );
        printf("--      \n");
        GPIOA_ModeCfg(bTXD1, GPIO_ModeIN_PD);
#endif
        event_retern =  key_long_plus_minus_yes;
               }

       if (event_retern != key_event_non)
       {
           return event_retern;
       }else
       {
           return key_event_non;
    }



}

void GET_ADC_Value(void)
{

    if( PowOnOff_ADC_count <=adcBuffLenPowOnOff) // короткие измерения "SHORT"
    {

                 PowOnOff_ADC_count++;

                 ADC_ExtSingleChSampInit(SampleFreq_8,ADC_PGA_1_4 );
                 //ADC_ExtSingleChSampInit( SampleFreq_3_2,ADC_PGA_1_4 );

                 ADC_ChannelCfg(9);// - PA0
                 //RoughCalib_Value = ADC_DataCalib_Rough();
                 //adcBuffShort = ADC_ExcutSingleConver()+ RoughCalib_Value;
                 adcBuffShort = ADC_ExcutSingleConver();
                 adcBuffKey =adcBuffKey + adcBuffShort;
                 ADC_ChannelCfg(8);// - PA1
                 //RoughCalib_Value = ADC_DataCalib_Rough();
                 //adcBuffShort = ADC_ExcutSingleConver()+ RoughCalib_Value;
                 adcBuffShort = ADC_ExcutSingleConver();
                 adcBuffSumPowOnOff =adcBuffSumPowOnOff + adcBuffShort;

               //  if(adc_ready==0) // если измерения  разрешены
               //    {
                 //ADC_ChannelCfg(0);// - PA4
                 ADC_ChannelCfg(14);// - Vbat / Vcc
                 adcBuffShort = ADC_ExcutSingleConver();
                 adcBuffSumRefShort= adcBuffSumRefShort + adcBuffShort;


         //        ADC_ExtSingleChSampInit(SampleFreq_8,ADC_PGA_0 );
                 ADC_ExtSingleChSampInit(SampleFreq_8,ADC_PGA_1_2 );
                 ADC_ChannelCfg(11);// - PA7
                 //RoughCalib_Value = ADC_DataCalib_Rough();
                 //adcBuffShort = ADC_ExcutSingleConver()+ RoughCalib_Value;
                 adcBuffShort = ADC_ExcutSingleConver();
                 adcBuffSumNtcShort =adcBuffSumNtcShort + adcBuffShort;
                //   }


    if( PowOnOff_ADC_count==adcBuffLenPowOnOff)
        {

                 adcBuffKey=adcBuffKey/adcBuffLenPowOnOff;
                 adcBuffSumPowOnOff=adcBuffSumPowOnOff/adcBuffLenPowOnOff;


                 VkeyShort = (((double)adcBuffKey/512)-3)*1.05;
                 Vpow_on_off = (((double)adcBuffSumPowOnOff/512)-3)*ADC_ref;

             //    if(adc_ready==0) // если измерения  разрешены
            //                      {
                 adcBuffSumRefShort=adcBuffSumRefShort/adcBuffLenPowOnOff;
                 adcBuffSumNtcShort=adcBuffSumNtcShort/adcBuffLenPowOnOff;
                 VrefShort =   (((double)adcBuffSumRefShort/512)-3)*ADC_ref;
                 //VntcShort =   (((double)adcBuffSumNtcShort/512)-3)*1.05;
                 VntcShort = ( ( ((double)(adcBuffSumNtcShort))/1024.0)-1.0)*ADC_ref;
                            //      }

                 OnOff_adcBuffLenReady =1;
                 PowOnOff_ADC_count=0;
                 adcBuffKey=0;
                 adcBuffSumPowOnOff=0;
                 adcBuffSumRefShort=0;
                 adcBuffSumNtcShort=0;

        }

             //  PowOnOff_ADC_count++;
    }



  //------------------ обработка внутри измерений----------------------------------



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




  //------------------END OFF   обработка внутри измерений----------------------------------

}

void tempere_out_formation(void)
{

 #define DEBUG_tempere_out_formation

#ifndef   DEBUG_tempere_out_formation
   if((main_screen_type== main_screen_manual)||(main_screen_type== main_screen_prog))
        {
    GPIOB_SetBits(bTXD1);
    GPIOB_ModeCfg(bTXD1, GPIO_ModeOut_PP_5mA);
    RTC_GetTime( &py,&pmon,&pd,&ph,&pm,& ps);
        }
#endif

 // ------------------------- постоянное считывание "быстрых значений "  + анализ ERROR и состояние ДАТЧИКА
   // VkeyRef*1.019
      //buf_resist =  get_resist(VkeyRef*1.019,VntcShort,R13);// вводим передачу входных параметров
    buf_resist =  get_resist(VrefShort,VntcShort,R13);// вводим передачу входных параметров

     T= get_tempere(buf_resist);//// вводим передачу входных параметров
     //sensor_state=tempere_sensor_error(VrefShort,VntcShort,buf_resist);

     sensor_state=tempere_sensor_error(VkeyRef*1.019,VntcShort,buf_resist);




 //-----------------------------------------------------------------------------------------


    //sensor_state=0; // отладка
    if(sensor_state==1)// если состояние датчика нормальное  то sensor_state =1 !! иначе выдает коды ошибки
    {
   //----------------------------анализ полученных "быстрых значений"-------------------------


       if(Sensor_delay>0)
      {
#ifndef   DEBUG_tempere_out_formation
      printf("\n");
      printf("----------------- SHORT TIME ----------------\n");
      printf( "%d year %d month %d day %d hour %d minute %d second  \n" ,py,pmon,pd,ph,pm,ps);
      printf(" VrefShort PA4 =%f volts \n", VrefShort ); // вывод на дисплей/ терминал результата  измерений
      printf(" VntcShort PA7 =%f volts \n", VntcShort );// либо в цикле for либо в "ЗАДАЧЕ" для LCD COM

#endif

    if(sek_count==0)//если виртуальный таймер после включения девайса, насчитал 0 SEK =
                   //то показываем один раз короткое значение
   {

        if(VkeyShort>=3.0) // если напряжение ядра более 3,0- обновляем его
                           {
            VkeyShort = 3.30;// обманное значение в первую секунду МК после старта
            //VkeyRef = VkeyShort;
                          }

     //buf_resist =  get_resist(VkeyRef*1.019,VntcShort,R13);// вводим передачу входных параметров

      buf_resist =  get_resist(VrefShort,VntcShort,R13);// вводим передачу входных параметров

    //printf(" NTC RESIST   =%f kOmh \n",  buf_resist );
      T= get_tempere(buf_resist);//// вводим передачу входных параметров
      Tout=T; // выводим короткое  измеренное значение температуры в кончный выходной буфер
      Tout = round(Tout);
   }

         Tout=T; // выводим короткое  измеренное значение температуры в кончный выходной буфер
         Tout = round(Tout);



#ifndef   DEBUG_tempere_out_formation
  //    printf(" VrefShort PA4 =%f volts \n", VrefShort ); // вывод на дисплей/ терминал результата  измерений
  //    printf(" VntcShort PA7 =%f volts \n", VntcShort );// либо в цикле for либо в "ЗАДАЧЕ" для LCD COM
  //    printf(" Vpow_on_off PA1 =%f volts \n",  Vpow_on_off );// либо в цикле for либо в "ЗАДАЧЕ" для LCD COM
  //    printf("  <<OUTPUT>>   T celsium   =%f   degree C*  \n", Tout );
  //    printf("\n");
#endif
      }
   //----------------------------------------------------------------------------------------------------------

     if((adcBuffLenReady==1)& (Sensor_delay==0) )
    // if(((VrefShort>0.15)&(VntcShort>0.15))  &  (adcBuffLenReady==1 ) & (Sensor_delay==0) )
    {
      adcBuffLenReady=0;// синхронизируем  RESTART медленного буфера с вызовом текущего TASK
                        //  для медленного обновления температуры
   //   ADC_i = 0 ;       // перезапускаем   длинный буфер
#ifndef   DEBUG_tempere_out_formation
      printf("\n");
      printf("---------------- LONG TIME ----------------\n");
      printf( "%d year %d month %d day %d hour %d minute %d second  \n" ,py,pmon,pd,ph,pm,ps);

      //uint32_t GetSysClock(void)
      printf( "%d GetSysClock \n" ,GetSysClock());

#endif
     //  buf_resist =  get_resist(Vref,Vntc,R13);// пересчитываем  сопротивление с рачетом длинны буфера

      if(Vkey>=3.0) // если напряжение ядра более 2,9- обновляем его
                    {
          VkeyRefLong = Vkey;
                   }


      //buf_resist =  get_resist(VkeyRefLong*1.019,Vntc,R13);// пересчитываем  сопротивление с рачетом длинны буфера

      buf_resist =  get_resist(Vref,Vntc,R13);// пересчитываем  сопротивление с рачетом длинны буфера

      //printf(" NTC RESIST   =%f kOmh \n",  buf_resist );
      T= get_tempere(buf_resist);//// пересчитываем  температуру  с рачетом длинны буфера
 //     sensor_state=tempere_sensor_error(VrefShort,VntcShort,buf_resist);// контрольно состояние "разьема"

      //Tout=T;  // выводим медленное измеренное значение температуры в кончный выходной буфер

      if(ON_Icon_event==0)// если реле выключено
              {
              Tout=T;
             // Tout=T*1.0050;

              Tout = round(Tout);//round(Tout);//итоговое округление кратно  0,5
              }else {// если включено

              Tout=T*1.0040;
             //   Tout=T;
           //   Tout = round(Tout * 10); // округляем десятые
           //   Tout = (Tout /10);

              Tout = round(Tout);//итоговое округление кратно  0,5
            }

      if( Link_ON_OFF==TRUE)// если Link включен
      {
         // Tout=Tout*0.9990;
       //   Tout = round(Tout * 10); // округляем десятые
       //   Tout = (Tout /10);

          //Tout=Tout*1.001;
            Tout=T*1.0020;
          Tout = round(Tout);//round(Tout);//итоговое округление кратно  0,5

      }else { // если выключен

          Tout=Tout;

          Tout = round(Tout);//итоговое округление кратно  0,5
      }



#ifndef   DEBUG_tempere_out_formation
      printf(" Vref PA4 =%f volts \n", Vref ); // вывод на дисплей/ терминал результата  измерений
      printf(" Vkey   =%f   volts   \n",  Vkey*1.019 );
      printf(" Vntc PA7 =%f volts \n", Vntc );// либо в цикле for либо в "ЗАДАЧЕ" для LCD COM
      printf(" NTC RESIST  =%f kOmh \n",  buf_resist );// либо в цикле for либо в "ЗАДАЧЕ" для LCD COM
      printf(" Vpow_on_off PA1 =%f volts \n",  Vpow_on_off );// либо в цикле for либо в "ЗАДАЧЕ" для LCD COM
      printf("  <<OUTPUT>>   T celsium   =%f   degree C*  \n", Tout );
      printf("\n");
#endif
      }
   //--------------------------  задержка на стабилизацию дилинного температурного буфера после ERROR------------

       if(((VkeyRef*1.019>2.0)&(VntcShort>0.25)) &(Sensor_delay>0))

     // if(((VrefShort>2.0)&(VntcShort>0.25)) &(Sensor_delay>0))

     {
   //  значение количества циклов -  "Sensor_delay_value"  - определяется реальной длительностью наполнения буфера / регулируется




    if(Sensor_delay == Sensor_delay_value)
     {
     adcBuffSumRef=0;
     adcBuffSumKey=0;
     adcBuffSumNtc=0;

     adc_ready=0; //стартуем длинное измерение АЦП
     ADC_i = 0;
     }

     if(Sensor_delay>0)
       {
       Sensor_delay--; //уменьшаем значение задержки после ERROR
#ifndef   DEBUG_tempere_out_formation
       PRINT("  Sensor_delay  SHORT  cycles  =%hu\n",  Sensor_delay);
#endif

       }


     if(Sensor_delay==0)
          {

           // adc_ready=0; //стартуем длинное измерение АЦП

            printf("  <<Sensor_delay_value>>    =%d  \n", Sensor_delay );
            printf("\n");
          }


       }

    }

#ifndef   DEBUG_tempere_out_formation
   // printf("--      \n");
    DelayMs(5);// задержка для очистки мусора гипертерминала  перед  GPIOA_ModeCfg(bTXD1, GPIO_ModeIN_PD)
    GPIOB_ModeCfg(bTXD1, GPIO_ModeIN_PD);
    //GPIOB_SetBits(p13);
#endif
}



void termostat(void)
{

#define  DEBUG_termostat
#ifndef  DEBUG_termostat
      GPIOA_SetBits(bTXD1);
      GPIOA_ModeCfg(bTXD1, GPIO_ModeOut_PP_5mA);
#endif

 // HystPrepere = HYST_05 ;
  HystPrepere = HYST_10 ;

if(HystPrepere==HYST_10)// если в настройках гестеризис равен "0,5"
{
   // if(((setup_temp-Tout_int)>=HYST_05)&(ON_Icon_event==0))// верхнее отсечение
    if(((setup_temp-Tout_int)>=HYST_05))// верхнее отсечение
    {
     Tout_int=  Tout_int-2; // отняли попрвку 0,2 С (градуса) на дрейф напряжения

     //повторный итоговый анализ
    // if(((setup_temp-Tout_int)>=HYST_05)&(ON_Icon_event==0))// верхнее отсечение

      if(((setup_temp-Tout_int)>=HYST_05))// верхнее отсечение
         {
    if( start_back_light==0)// если подсветка выключена
    {

        REL_ON;



    } // то включаем физически реле

    heat_on_off=1;
    ON_Icon_event=1; // генерим событие для значка  ON
    OFF_Icon_event=0;

#ifdef SK3_LCD  // если определен "малый єкран"
      RED_ON;
#endif

         }


    }
   // if(((Tout_int-setup_temp)>=HYST_10)&(OFF_Icon_event==0))// нижнее отсечение

     if(((Tout_int-setup_temp)>=HYST_10))// нижнее отсечение
    {
     Tout_int=  Tout_int+2; // возвращаем попрвку 0,2 С (градуса) на дрейф напряжения

     //повторный итоговый анализ
     //if(((Tout_int-setup_temp)>=HYST_10)&(OFF_Icon_event==0))// нижнее отсечение
     if(((Tout_int-setup_temp)>=HYST_10))// нижнее отсечение

        {

     REL_OFF;


     heat_on_off=1;
     ON_Icon_event=0;
     OFF_Icon_event=1; // генерим событие для значка  OFF (тушим ON)

#ifdef SK3_LCD  // если определен "малый єкран"
      GREEN_ON;
#endif

        }

    }

}


if(HystPrepere==HYST_05)// если в настройках гестеризис равен "0,5"
{
  //  if(((setup_temp-Tout_int)>=HYST_05)&(ON_Icon_event==0))// верхнее отсечение
    if(((setup_temp-Tout_int)>=HYST_05))// верхнее отсечение

    {
     Tout_int=  Tout_int-2; // отняли попрвку 0,2 С (градуса) на дрейф напряжения

     //повторный итоговый анализ
   //  if(((setup_temp-Tout_int)>=HYST_05)&(ON_Icon_event==0))// верхнее отсечение
     if(((setup_temp-Tout_int)>=HYST_05))// верхнее отсечение

         {
    if( start_back_light==0)// если подсветка выключена
    {

        REL_ON;


    } // то включаем физически реле

    heat_on_off=1;
    ON_Icon_event=1; // генерим событие для значка  ON
    OFF_Icon_event=0;

#ifdef SK3_LCD  // если определен "малый єкран"
      RED_ON;
#endif



         }


    }
   // if(((Tout_int-setup_temp)>=HYST_05)&(OFF_Icon_event==0))// нижнее отсечение
    if(((Tout_int-setup_temp)>=HYST_05))// нижнее отсечение
    {
     Tout_int=  Tout_int+2; // возвращаем попрвку 0,2 С (градуса) на дрейф напряжения

     //повторный итоговый анализ
   // if(((Tout_int-setup_temp)>=HYST_05)&(OFF_Icon_event==0))// нижнее отсечение
     if(((Tout_int-setup_temp)>=HYST_05))// нижнее отсечение
        {

     REL_OFF;

     heat_on_off=1;
     ON_Icon_event=0;
     OFF_Icon_event=1; // генерим событие для значка  OFF (тушим ON)

#ifdef SK3_LCD  // если определен "малый єкран"
      GREEN_ON;
#endif


        }

    }

}

#ifndef  DEBUG_termostat
PRINT("  HystPrepere  =%hu\n",  HystPrepere);
PRINT("  setup_temp  =%hu\n",  setup_temp);
PRINT("  Tout_int  =%hu\n",  Tout_int);
 printf("--      \n");
 DelayMs(10);// задержка для очистки мусора гипертерминала  перед  GPIOA_ModeCfg(bTXD1, GPIO_ModeIN_PD)
 GPIOA_ModeCfg(bTXD1, GPIO_ModeIN_PD);
#endif

}




void ADC_BUF_ON_OFF(int8 buf_ON)
{
    if(buf_ON==1)
    {
    R8_ADC_CFG = R8_ADC_CFG | RB_ADC_BUF_EN ;
    }
}


void ADC_setup(void)
{

/* Single channel sampling: interrupt mode, select adc channel 1 for sampling, corresponding to PA5 pin, without data calibration */
                             PRINT("\n5. Single channel sampling in interrupt mode... \n");


                             //GPIOA_ModeCfg(GPIO_Pin_4, GPIO_ModeIN_Floating);//  ADC_Channel 0 // Vref  - на питании датчика
                             GPIOA_ModeCfg(GPIO_Pin_4,  GPIO_ModeIN_PU);



                             GPIOA_ModeCfg(GPIO_Pin_7, GPIO_ModeIN_Floating);//  ADC_Channel 11


                             GPIOA_ModeCfg(GPIO_Pin_1, GPIO_ModeIN_Floating);//  ADC_Channel 8
                             GPIOA_ModeCfg(GPIO_Pin_0, GPIO_ModeIN_Floating);//  ADC_Channel 9


                            // GPIOA_ModeCfg(GPIO_Pin_4, GPIO_ModeIN_PD);//  ADC_Channel 0


                             ADC_ExtSingleChSampInit(SampleFreq_8,ADC_PGA_1_4 );
                             ADC_BUF_ON_OFF(1);

                             adclen = 0;
                             ADC_ClearITFlag();
                             //PFIC_EnableIRQ(ADC_IRQn);
                             PFIC_DisableIRQ(ADC_IRQn);
                            // ADC_StartUp(); //запуск измерений ADC

}




double  get_resist(double VrefBUF,double VntcBUF,double R_upper)
{

    double  Rntc=0, Rup_test =0;

 #define NTC_pull_up // переключаем вариант запитки делителя R13/ Rntc

#ifdef NTC_pull_up //eсли NTC датчик подтянут к питанию через R13 //нужно перепаять подачу питания на R13 и Rntc!!
#define  R_up1      R_upper    // в kOmh

//VntcBUF=VntcBUF*1.033;
//VrefBUF=VrefBUF*1.033;



//Rup_test = (1.20*R_up1 *VntcBUF)/ (VrefBUF-VntcBUF);

    Rup_test = (R_up1 *VntcBUF)/ (VrefBUF-VntcBUF);

//return Rup_test*1.05;

    return Rup_test;

 //   return Rup_test;

#else // eсли NTC датчик подтянут к земле через R13 ( Как у Лизунова) // нужно перепаять подачу питания на R13 и Rntc

#define  Rref         R_upper    // в kOmh

Rntc = ( (VrefBUF*Rref) - (VntcBUF*Rref) ) / VntcBUF ;

return Rntc*0.95 ;

#endif





}

double get_tempere(double ResistNTC)
{

    double return_T;

    RX = ResistNTC;

    RX= RX*1000; // переводим килоомы  в Омы

    T = 1/(log(RX/Rn)/Beta + 1/TN) - 273.15;

  //  T = round(T * 10); // округляем десятые
  //  T = (T /10);

  //   T = round(T * 5); // округляем десятые
   //   T = (T /5);


    // T = round(T * 2);  // округляем конечное значение и выводим кратно 0,5
    // T = (T /2);


    return_T= T;

   // return_T= round(T);// округляем выходное значение до 0,5

   // return return_T+2.0;

    // return return_T -0.5;

    return return_T ;

}


void convert_temperature(int input_temp) {
            temp_whole = input_temp / 10;        // Целая часть температуры (кратная единицам)
            temp_half = (input_temp % 10) == 5 ? 5 : 0; // Половинка градуса (5 или 0)
        }



void convert_temperature_set(int set_temp) {
            temp_whole_set = set_temp / 10;        // Целая часть температуры (кратная единицам)
            temp_half_set = (set_temp % 10) == 5 ? 5 : 0; // Половинка градуса (5 или 0)
        }


void convert_temperature_read(int read_temp) {
           temp_whole_read = read_temp / 10;        // Целая часть температуры (кратная единицам)
           temp_half_read = (read_temp % 10) == 5 ? 5 : 0; // Половинка градуса (5 или 0)
        }





int combine_temperature(int8_t temp_whole, int8_t temp_half) {

    int setup_temp_buf;

    setup_temp_buf = (temp_whole * 10) + (temp_half == 5 ? 5 : 0);

    return setup_temp_buf;

}


int combine_temperature_set(int8_t set_temp_whole, int8_t set_temp_half) {

    int setup_temp_buf;

    setup_temp_buf = (set_temp_whole * 10) + (set_temp_half == 5 ? 5 : 0);

    return setup_temp_buf;

}


int combine_temperature_read(int8_t read_temp_whole, int8_t read_temp_half) {

    int setup_temp_buf;

    setup_temp_buf = (read_temp_whole * 10) + (read_temp_half == 5 ? 5 : 0);

    return setup_temp_buf;

}







// Функция преобразования float в int
int convertToTemperatureInt(float temperature) {


    //--------------------------------------- Преобразование температуры float в INT ---------------------------------

      //  Tout_to_int=temperature;
     //   Tout_to_int=Tout_to_int*10;
     //   Tout_int = (int)Tout_to_int;


    // Умножаем на 10 и приводим к int
    return (int)(temperature * 10);

  //   return Tout_int;


}


// Функция для анализа изменения значения Tout

// использует глобальные перменные

void checkAndSetFlag() {
    if (Tout != prevTout) {
       //BLE_NEW_DATA = 1;  // Установить флаг
        BLE_NEW_SENOSOR_TEMPER=1;
        prevTout = Tout;   // Обновить предыдущее значение
    }
}



// Функция для анализа изменения значения Tout

// использует глобальные перменные

void checkConnectAndSync() {

    if (isConnected != prewiosisConnected) {

        prewiosisConnected = isConnected;   // обновилось значение


        if(isConnected == true ) // если актуальное текущее значение isConnected == true, то передаем ткущие даненые  на телефон посел соединения один раз
        {
            SyncStart =1; // тарт синхронизации
          //  DelayMs(2000);


        } else {

         SyncDelay = 0;
        // DelayMs(2000);

        }

    }






}









///////////////////////////////////////////////////////////////////////////////
///////////////////////
// функция округления
//Аргументы:
//x – число, которое необходимо округлить.
//Возвращаемое значение:
//Округленный аргумент.

double round(double x)
{
int i;
double d,y;
i = (int)x;      //целая часть
d = x - i;       //дробная часть



if((d>0.2)&(d<0.8))
{
 y= (float)i  + 0.5;


 return y;


}  else {

    if(d>=0.8)
    {  //если больше или равно 0,5
    return(ceil(x)); //округляем до большего
    }

    if(d<=0.2)
    {
    return(floor(x)); //округляем до меньшего
    }

}


}



 int8_t tempere_sensor_error(double VrefBUF,double VntcBUF,double ResistNTCBUF )
{

#define  DEBUG_tempere_sensor_error
 int8_t error=0;

    if((VntcBUF< 0.15 )|(VntcBUF> 3.0 ))
 {

#ifndef  DEBUG_tempere_sensor_error
      GPIOA_SetBits(bTXD1);
      GPIOA_ModeCfg(bTXD1, GPIO_ModeOut_PP_5mA);
#endif
 printf(" Sensor Connection Error !   =  %f \n", VntcBUF );
#ifndef  DEBUG_tempere_sensor_error
    printf("--      \n");
    DelayMs(5);// задержка для очистки мусора гипертерминала  перед  GPIOA_ModeCfg(bTXD1, GPIO_ModeIN_PD)
    GPIOA_ModeCfg(bTXD1, GPIO_ModeIN_PD);
#endif

 error = 0x11;
 adc_ready=1; //тормозим длинное измерение АЦП
 Vref=0;
 Vntc=0;
 ADC_i = 0 ;
 adcBuffSumRef=0;
 adcBuffSumKey=0;
 adcBuffSumNtc=0;

 Sensor_delay = Sensor_delay_value;
 adcBuffLenReady=0;


 }
     else {

 if ((T> -30.00 )&(T<= 99.50 ))
 {
 //printf(" T celsium   =%f   degree C*  \n", T );

  error =1 ;//  возвращать "0" функция не хочет, поэтому когда все НОРМ - возвращаем 1 , а при авариях
  // коды ошибок!!

 }
    else
 {


    if(ResistNTCBUF< 0.15 )
  {
#ifndef  DEBUG_tempere_sensor_error
      GPIOA_SetBits(bTXD1);
      GPIOA_ModeCfg(bTXD1, GPIO_ModeOut_PP_5mA);
#endif
  printf(" Sensor Short Circuit Error !   =  %f \n", VntcBUF );
#ifndef  DEBUG_tempere_sensor_error
    printf("--      \n");
    DelayMs(5);// задержка для очистки мусора гипертерминала  перед  GPIOA_ModeCfg(bTXD1, GPIO_ModeIN_PD)
    GPIOA_ModeCfg(bTXD1, GPIO_ModeIN_PD);
#endif
  error = 0x22;
  adc_ready=1; //тормозим длинное измерение АЦП
  Vref=0;
  Vntc=0;
  ADC_i = 0 ;
  adcBuffSumRef=0;
  adcBuffSumKey=0;
  adcBuffSumNtc=0;

  Sensor_delay = Sensor_delay_value;
  adcBuffLenReady=0;

  }
  else {

 if((T> 85.00 )&(T<= 150.00 ))
 {
#ifndef  DEBUG_tempere_sensor_error
      GPIOA_SetBits(bTXD1);
      GPIOA_ModeCfg(bTXD1, GPIO_ModeOut_PP_5mA);
#endif
 printf(" Sensor Temperature Overdrive !   =  %f \n", T );
#ifndef  DEBUG_tempere_sensor_error
    printf("--      \n");
    DelayMs(5);// задержка для очистки мусора гипертерминала  перед  GPIOA_ModeCfg(bTXD1, GPIO_ModeIN_PD)
    GPIOA_ModeCfg(bTXD1, GPIO_ModeIN_PD);
#endif
 error = 0x33;

 }

 }

 }

 }



   return error;
}



/*********************************************************************
  * @fn ADC_IRQHandler
  *
  * @brief ADC interrupt function
  *
  * @return none
  *///********************************************************************

 __attribute__((interrupt("WCH-Interrupt-fast")))
  __attribute__((section(".highcode")))
  void ADC_IRQHandler(void)
  {
      if(ADC_GetDMAStatus())
      {
          ADC_ClearDMAFlag();
          ADC_StopDMA();
  //        R16_ADC_DMA_BEG = (uint16_t)(uint32_t)&adcBuff[0];
          DMA_end = 1;
      }
      if(ADC_GetITStatus())
      {
          ADC_ClearITFlag();
          if(adclen < adcBuffLen)
          {
    //          adcBuff[adclen] = ADC_ReadConverValue();
    //          ADC_StartUp(); // function clears the interrupt flag and opens a new round of sampling
          }
          adclen++;
      }
  }


/*********************************************************************
 * @fn      TMR0_IRQHandler
 *
 * @brief   TMR0中断函数
 *
 * @return  none
 */


__INTERRUPT
__HIGH_CODE
void TMR0_IRQHandler(void) // TMR0 定时中断
{
// ВНИМАНИЕ!! BLE стек не восстанавливается самостоятельно после отановки в прерывании!!
//---простым языком его нужно перезапускать прогррамынм методом а также попробывать
//программный планировщик в качестве альтернативы Hardware IRQ !!!

    if(TMR0_GetITFlag(TMR0_3_IT_CYC_END))
    {
        TMR0_ClearITFlag(TMR0_3_IT_CYC_END); // 清除中断标志

        init_LCD();//

        COM1_COM4_Handler();


        //GPIOB_SetBits(bTXD1);// артифакт пер на UART один при перебивке GPIO LCD
        //GPIOB_ResetBits(bTXD1);// артифакт пер на UART один при перебивке GPIO LCD

  //      GET_ADC_Value();

    }

}



__INTERRUPT
__HIGH_CODE
void GPIOA_IRQHandler(void)
{
    event_GPIO++;

    if( soft_block==1)
    {
    PFIC_DisableIRQ(GPIO_A_IRQn);
    }else {

    {
    GPIOA_ClearITFlagBit(GPIO_Pin_1);
    PFIC_EnableIRQ(GPIO_A_IRQn);
    // if(slep=1)
    //{
    //   GPIOA_ModeCfg(GPIO_Pin_1, GPIO_ModeIN_PD);
    //  GPIOA_ITModeCfg(GPIO_Pin_1, GPIO_ITMode_HighLevel); // 下降沿唤醒
    //}
       }
    }
}


__attribute__((interrupt("WCH-Interrupt-fast")))
__attribute__((section(".highcode")))
void SysTick_Handler()
{
   //  PFIC_ClearPendingIRQ(SysTick_IRQn);

}






u8 SAM_Event(u8 x_event)
{


 u8 NewEvent=0;

 Tout = setup_temp;



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


if(tempere_cange==1)
{
    return NewEvent=1;
}else

{
    return NewEvent=0;
}



}



// Глобальные переменные для RTC
//uint16_t py;  // Год
//uint8_t pmon; // Месяц
//uint8_t pd;   // День
//uint8_t ph;   // Часы
//uint8_t pm;   // Минуты
//uint8_t ps;   // Секунды

// Функция для вычисления Unix Time
uint32_t GetUnixTime() {
    // Количество дней в каждом месяце (не учитывая високосные года)
    static const uint8_t daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    uint32_t unixTime = 0;
    uint16_t year = py;
    uint8_t month = pmon;
    uint8_t day = pd;

    // Добавляем секунды за прошедшие годы
    for (uint16_t y = 1970; y < year; y++) {
        unixTime += (y % 4 == 0 && (y % 100 != 0 || y % 400 == 0)) ? 31622400 : 31536000;
    }

    // Добавляем секунды за прошедшие месяцы текущего года
    for (uint8_t m = 1; m < month; m++) {
        unixTime += daysInMonth[m - 1] * 86400;
        if (m == 2 && (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))) {
            unixTime += 86400; // Високосный год
        }
    }

    // Добавляем секунды за прошедшие дни текущего месяца
    unixTime += (day - 1) * 86400;

    // Добавляем секунды за прошедшие часы, минуты и секунды текущего дня
    unixTime += ph * 3600 + pm * 60 + ps;

    return unixTime;
}

// Глобальные переменные для байтового представления времени
//uint8_t UnixByte0, UnixByte1, UnixByte2, UnixByte3;

// Функция для преобразования Unix Time в 4 байта
void ConvertUnixTimeToBytes(uint32_t unixTime) {
    UnixByte0 = (unixTime >> 24) & 0xFF; // Старший байт
    UnixByte1 = (unixTime >> 16) & 0xFF;
    UnixByte2 = (unixTime >> 8) & 0xFF;
    UnixByte3 = unixTime & 0xFF;         // Младший байт
}














//-----------------------------------------END OF ASTAP BOARD-----------------------------------//

