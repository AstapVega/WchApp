
#include "CONFIG.h"
#include "my_assist32.h"
#include "alex_board.h"
#include "menu_vlad.h"
#include "main_vlad.h"
#include "my_large_LCD32.h"
//#include "analog.h"
//#include "rtc2.h"
//#include "flash.h"
#include "my_test.h"
#include "peripheral.h"
#include "ext_my_directtest.h"
#include "my_FLASH.h"




extern int8  BLE_NEW_DATA;

//-------------------------------------------------------------------------------------------------
void    standby_menu(void);
void    main_menu(void);
uint8 main_screen_type =0; // тип экрана
uint8 set_date_clock = 0; // дата/время установлены или нет

//--------------------------------- FOR SFM  режима ------------------------------------------------
int16 active_time =SFM_default_time, active_time_evnt = 0 ; //(минимальное рабочее время по умолчанию) ( забрасываем туда значения температуры)


int16 sfm_sek_active=0,sfm_sek_relax=0;
//int16 sfm_min = SFM_default_time;
int16 sfm_min ;
int16 start_sfm_timer1 = 0,start_sfm_timer2 = 0;
int16 relax_time =0, relax_time_evnt = 0;
int16 relax_buf = 0;
int16 active_buf = SFM_default_time;
//int8 sfm_min_dec, sfm_min_unit,relax_time_dec,relax_time_unit;

uint8_t LOCK_PRINT_OUT = 0;// флаг нежелательного вывода инфы на печать в субцикле для timersfm

int16 minutes_tm_1 = 0,minutes_tm_2 =0; // 255 min - MAX

//------------------------------ для режим БЛОКИРОВКИ LOC ----------------------------------------
uint8  start_lock_anime_timer = 0;
uint8  lock_anime_timer =0;



//--------------------------------- для расписания  -----------------------------------------------
int16 dss =0;// смешение в таблице  расписания с учетом выбранного  ДНЯ НЕДЕЛИ
int16 select_day_buf = 0;
u16   shudle_setup_t,shudle_hours,shudle_minute;
//---------------------------------для главного экрана---------------------------------------------
s16 temp = 0;
float Tout_to_int;//вспомогательная буферная переменная для коректного преобразования  float T в int T
s16 intr_time_N = 0, curent_intr = 0,curent_sys_time = 0 ,curent_intr_time = 0,prev_intr_time = 0,next_intr_time = 0;
s16 int_buf;
s16 total_time1,total_time2,minut_debug, hours_debug;


//-------------------------------------------------------------------------------------------------

void    service_menu(void);
void    prog_menu(void);
void    prog_selected_day(void);
void    copy_day_menu(void);
void    time_menu(void);
int16   set_blynk_hours(int16 hours,int16 minutes);
int16   set_blynk_minutes(int16 minutes,int16 hours);
int16   set_shedule_tempere(int16 tempere);
int16   set_shedule_hours(int16 hours,int16 minutes);
int16   set_shedule_minutes(int16 minutes,int16 hours);
s16 int_position(s16 N_interval, s8 interval_direction);
void    SFM_mode_timer(void);
void    prog_day_seq(void);
void    control_menu(void);
void    service_eco1(void);
void    service_eco2(void);
void    service_time(void);
void    loc_entry(void);
void    pwm_entry(void);
void    hysteresis_entry(void);
void    hilo_submenu2(void);
void    hilo_hilo(void);
void    default_entry(void);

void key_screen_work(void);

void TEST_Task(void);



void	main_menu(void) {


     shudle_setup_t=0;
     shudle_hours=0;
     shudle_minute=0;

     temp = 0;
	 intr_time_N = 0;
	 curent_intr = 0;
	 curent_sys_time = 0;
	 curent_intr_time = 0;


	 if( device_on_off== device_on)// если устройство аля программно "ВКЛ"
	 {


//---------------------------------------INTRO------------------------------------------------//

	if(INTRO==1)
	{
	    //event_type= key_event_mode; // при старте МК входим в главній єкран и один раз зажигаем посветку
	    // эмитируем фальсстар нажатия кнопки MODE
	    // сбрасываем "INTRO" до следующего запуска девайса
	    // INTRO=0;
	    // если происходит нажатие  кнопок в главном єкране
	    // sek_count=0;// обнуляем счетчик секунд

	    UP_press=0;// переводим кнопку MODE  в режим  КАСАНИЯ

	    start_back_light=1;// стартует отсчет в главной ЗАДАЧЕ с интервалом = 1 сек
	       // по истечению таймера подсветка тухнет а  реле обратно вклается
	     if(Virtual_timer > 1)// задержка  на для очистки буфера после стартовой подачи питания
	   // if(sek_count==1)// задержка  на для очистки буфера после стартовой подачи питания
	      {
	        INTRO=0;
	       // adc_ready=1; //тормозим длинное измерение АЦП
	        adcBuffSumRef=0;// чистим буфер
	        adcBuffSumNtc=0;// чистим буфер
	        LIGTH_ON;//ВКЛЮЧЕНИЕ LED ПОДСВЕТКИ ПРИ НАЧАЛЬНОЙ ЗАСТАВКЕ
	      }

     if(ON_Icon_event==1 )
	       {
	        REL_OFF;// отключаем реле
	        DelayMs(10);
	       }
	}

      if(((event_type == key_event_plus)||(event_type== key_event_minus)||(event_type== key_event_mode)||(Stand_Bay_Waike==1)) &(lock_key == unlock))
      {
          if(Stand_Bay_Waike==1)
          {Stand_Bay_Waike=0;}// брос после режима ожидания с выключенным єкраном
 //-------------------------------------- ВКЛЮЧЕНИЕ LED ПОДСВЕТКИ ПРИ НАЖАТИИ КНОПОК---------------------------------
  // если происходит нажатие  кнопок в главном єкране
      sek_count=0;// обнуляем счетчик секунд
      start_back_light=1; // стартует отсчет в главной ЗАДАЧЕ с интервалом = 1 сек
// по истечению таймера подсветка тухнет а  реле обратно вклается

      adc_ready=1; //тормозим длинное измерение АЦП
      DelayMs(10);
     if(ON_Icon_event==1 )
     {
     DelayMs(10);
     REL_OFF;// отключаем реле
	 }
	 LIGTH_ON; // включаем подсветку если нажали на любую кнопку в главном  ЭКРАНЕ !!
	 }
//-----------------------------------------------------------------------------------------------------------------


      //LOC_on_off=LOC_on;//ктивировали режим блокировки
      //lock_key = lock;// взвели флаг " заблокировать клавиатуру"

     // if((event_type == key_event_plus_minus)&(LOC_on_off==LOC_on)&(lock_key == lock))// разблокировка одновременным нажатием + и -
      if((event_type == key_long_plus_minus_yes)&(lock_key == lock))
      {
      start_lock_anime_timer = TRUE;

      screen_refresh_flag=1; // статическое изображение "LOC" + замок иконка
      lock_key = unlock;
      UP_press=0;// переводим кнопку MODE  в режим  КАСАНИЯ

  //-------------------------------------- ВКЛЮЧЕНИЕ LED ПОДСВЕТКИ ПРИ НАЖАТИИ КНОПОК---------------------------------
  // если происходит нажатие  кнопок в главном єкране
           sek_count=0;// обнуляем счетчик секунд
           start_back_light=1; // стартует отсчет в главной ЗАДАЧЕ с интервалом = 1 сек
  // по истечению таймера подсветка тухнет а  реле обратно вклается

           adc_ready=1; //тормозим длинное измерение АЦП
           DelayMs(10);
          if(ON_Icon_event==1 )
          {
          DelayMs(10);
          REL_OFF;// отключаем реле
          }
          LIGTH_ON; // включаем подсветку если нажали на любую кнопку в главном  ЭКРАНЕ !!

      }


 if(((event_type == key_event_mode)||(event_type == key_event_plus)||(event_type == key_event_minus))&(lock_key == lock))
          // если произошло касание клавиатуры и активирована "блокировка"
        {
         start_lock_anime_timer = 1;
         clear_screen();
#ifndef SK3_LCD  // если определен "большой єкран"
         LockIcon;
#else

#endif
         screen_refresh_flag=1; // статическое изображение "LOC" + замок иконка
         // для разблокировки нужно сбросить  lock_key в unlock
        }


	if((event_type == key_event_mode)&(lock_key==unlock)) // если произошло нажатие кнопок  "MODE"
	 {
	  main_screen_enter_count++;
	//if(main_screen_enter_count>1)// вход в в CONTROL MENU  с ложным нажатие "MODE"
	if(main_screen_enter_count>0) // вход в в CONTROL MENU  без ложного нажатиея "MODE" - сразу
	{
	main_screen_enter_count=0;
	screen_level=CONTROL_MENU; // меняем дальнейший указатель меню на CONTROL_MENU
    RTC_GetTime( &py,&pmon,&pd,&ph,&pm,& ps);
	// делаем предварительную загрузку параметров текущего времени из RTC для дальнейшей работы
    // модификации  в меню "время"
    my_py   = py;
	my_pmon = pmon;
	my_pd   = pd;
	my_ph   = ph;
	my_pm   = pm;

	//control_menu_navigate=0;// заходим в контрол меню на позицию "0"
	screen_refresh_flag=1; // выставляем флаг срочной отрисовки нового меню при входе  обработчик сканирвоания КНОПОК
	}

	}



// -----------------------  наполнение значения  температуры задания при нажатии кнопок + и - -------------------
	if((main_screen_type== main_screen_manual)||(main_screen_type== main_screen_prog))// если "ручной " или "програматор"
	{

	 if(lock_key==unlock)
	 {
	// if((event_type == key_event_plus)&(setup_temp<400))
	  if((event_type == key_event_plus)&(setup_temp<900))
	 {setup_temp = setup_temp + 5;
     sek_count_for_prog_anime=7;// выставляем значение таймера попеременного отображения часы/температура для показания
     //температуры  в момент касания
	 FLASH_UPDATE=1; // выставляем флаг обновления FLASH. Обновление происходит затем в основном потоке 1 -3 сек}
	 BUSY_KEY=1;
	 BUSY_KEY2=1;
	 BUSY_KEY3 =1;

	 //обновляем блютуз
	 BLE_NEW_DATA=1;

    }
	if((event_type== key_event_minus)&(setup_temp>0))
	 {setup_temp = setup_temp - 5;
     sek_count_for_prog_anime=7;// выставляем значение таймера попеременного отображения часы/температура для показания
     //температуры  в момент касания
	 FLASH_UPDATE=1;// выставляем флаг обновления FLASH. Обновление происходит затем в основном потоке 1 -3 сек
	 BUSY_KEY=1;
	 BUSY_KEY2=1;
	 BUSY_KEY3 =1;


	 //обновляем блютуз
	  BLE_NEW_DATA=1;

	 }
	 }

	} else  // иначе для режима SFM

	{

    if(lock_key==unlock)
	 {

	if(event_type == key_event_plus)
	 {//sfm_min = sfm_min + 5;
	  sfm_min = sfm_min + 1;

	if( sfm_min >40 ) // ограничение дапазона выставляемых значений кнопками - и + для SFM
	 {sfm_min=40;  }

	  active_time =  sfm_min;
	  active_buf = active_time;
	  relax_buf = (active_time_max - sfm_min)+ dead_time;
	  minutes_tm_1 = 0;

     FLASH_UPDATE=1; // выставляем флаг обновления FLASH. Обновление происходит затем в основном потоке 1 -3 сек}
	 }

	if(event_type== key_event_minus)
	 {//sfm_min = sfm_min - 5;
	  sfm_min = sfm_min - 1;

	  if( sfm_min <0 )
	  {sfm_min=0;  }

	  active_time =  sfm_min;
	  active_buf = active_time;
	  relax_buf = (active_time_max - sfm_min)+ dead_time;
	  minutes_tm_1 = 0;

	 FLASH_UPDATE=1;// выставляем флаг обновления FLASH. Обновление происходит затем в основном потоке 1 -3 сек

	 }

	 }


    }
//--------------------------------------- Преобразование температуры float в INT ---------------------------------

	Tout_to_int=Tout;
	Tout_to_int=Tout_to_int*10;
	Tout_int = (int)Tout_to_int;

 //------------------------------------------- Ручной Режим -----------------------------------------------------
	if(((main_screen_type== main_screen_manual)&( start_lock_anime_timer==0))||((main_screen_type== main_screen_manual)&(lock_key == unlock))  )
	{
		hand_on();

#ifndef SK3_LCD
      pack_temperature9876D(setup_temp);
#else
      pack_temperature7654D(setup_temp);
#endif


	//	sensor_state=tempere_sensor_error(VrefShort,VntcShort,buf_resist);
		  if(sensor_state== 0x11)
		{ pack123D_custom(((SIGN_E << 16) | (SIGN_r << 8) | SIGN_r));
		Tout_int=600;
		//termostat();
		//REL_OFF;
		}
		else {

		    pack_temperature123D(Tout_int);termostat();
		 //   termostat();

		}
	}

    if(( start_lock_anime_timer==1)&(lock_key == lock)&(LOC_on_off==LOC_on))
    {
      clear_screen();
      //выводим "блокировку"

#ifndef SK3_LCD  // если определен "большой єкран"
         LockIcon;
#else

#endif
      screen_refresh_flag=1; // статическое изображение "LOC" + замок иконка
     // для разблокировки нужно сбросить  lock_key в unlock
    }


    if(( start_lock_anime_timer==0)&(lock_key == lock)&(LOC_on_off==LOC_on))
     {
     // выводим значек "LOC" поверх основного изображения  если активна  блокировка
#ifndef SK3_LCD  // если определен "большой єкран"
         LockIcon;
#else

#endif
      screen_refresh_flag=1; // статическое изображение "LOC" + замок иконка
     }




//-------------------------------------- Вывод иконки "часы"----------------------------------------------------

  if(start_lock_anime_timer==0)
  {
    if(set_date_clock==0)//если время сбросилось, то показываем иконку "часы"
	 {
	     if(invers_clock_icon==0 ) // моргаем иконкой "часы"
	     {
	  clock_off();
	     }else {
	  clock_on();
        }

	 }else
	 {
	  clock_off(); // иначе не показываем  иконку "часы" для данного режима
     }

  }


//-------------------------------------- Программный режим -----------------------------------------------------
	//if(main_screen_type== main_screen_prog)

if(((main_screen_type== main_screen_prog)&( start_lock_anime_timer==0))||((main_screen_type== main_screen_prog)&(lock_key == unlock))  )

	{

	    sensor_state=tempere_sensor_error(VrefShort,VntcShort,buf_resist);
	          if(sensor_state== 0x11)
	        { pack123D_custom(((SIGN_E << 16) | (SIGN_r << 8) | SIGN_r));
	        Tout_int=600;
	       // termostat();
	        //REL_OFF;
	        }
	        else {
	            pack_temperature123D(Tout_int);
	        //    termostat();
	        }

//---------------------------------------- Вывод времени ------------------------------------------------------

	start_anime_blink =1;// разрешаем работу виртуального таймера для отсчета секунд формирования попеременного моргания
	// времени - температуры задания

	memcpy(Shedull_Copy_Pointer, SCHEDULE_RESERVE, sizeof(Shedull_Copy_Pointer));
	curent_sys_time =  time_convert_to_min (ph, pm );// преобразуем текущее системное время в минуты

    for(intr_time_N = 0; intr_time_N < 6; intr_time_N++)
    {

curent_intr_time =  time_convert_to_min (Shedull_Copy_Pointer[( what_day (py, pmon,pd )-1)][intr_time_N][Shed_ph],
                                        Shedull_Copy_Pointer[( what_day (py, pmon,pd )-1)][intr_time_N][Shed_pm] );

                          // преобразуем время  начала  интервала в минуты


        if((curent_sys_time >curent_intr_time)&(intr_time_N==5))// последний интервал 6 - й
        {

         curent_intr = intr_time_N ;

         shudle_hours =Shedull_Copy_Pointer[( what_day (py, pmon,pd ))-1][curent_intr][Shed_ph];
         shudle_minute=Shedull_Copy_Pointer[( what_day (py, pmon,pd ))-1][curent_intr][Shed_pm];
         shudle_setup_t = Shedull_Copy_Pointer[( what_day (py, pmon,pd ))-1][curent_intr][Shed_tp];

       //  printf("--      \n");
         intr_time_N = 6;// выходим из цикла for
        }


     if((curent_intr_time == curent_sys_time))// как только текущее время совпало с временем интервала
    {

     curent_intr = intr_time_N ;


     shudle_hours =Shedull_Copy_Pointer[( what_day (py, pmon,pd ))-1][curent_intr][Shed_ph];
     shudle_minute=Shedull_Copy_Pointer[( what_day (py, pmon,pd ))-1][curent_intr][Shed_pm];
     shudle_setup_t = Shedull_Copy_Pointer[( what_day (py, pmon,pd ))-1][curent_intr][Shed_tp];


     intr_time_N = 6;// выходим из цикла for
    }

       if((curent_intr_time > curent_sys_time))
        {
        curent_intr = intr_time_N -1;



         if(curent_intr<0)
                {
                curent_intr=5;// если время системмноен меньше чем значение 1 го интервала, значит мы находимся в 6 интервале
                // предыдущего дня с соответсвующим значением T !!
                pd=pd-1;// берем крайнее значение Т от предыдущего дня
                shudle_setup_t = Shedull_Copy_Pointer[( what_day (py, pmon,pd ))-1][curent_intr][Shed_tp];
                pd=pd+1;// Возвращяем  в текущий день для дальнейших преобразований
                }
         else {
                shudle_setup_t = Shedull_Copy_Pointer[( what_day (py, pmon,pd ))-1][curent_intr][Shed_tp];
        }

                shudle_hours =Shedull_Copy_Pointer[( what_day (py, pmon,pd ))-1][curent_intr][Shed_ph];
                shudle_minute=Shedull_Copy_Pointer[( what_day (py, pmon,pd ))-1][curent_intr][Shed_pm];


         intr_time_N = 6;// выходим из цикла for
        }


     }




//-------------------------------------------вывод знкоместа 9876D --------------------------------------------
    if(sek_count_for_prog_anime<=6)
	{
     ClockIcon;
	 pack_minutes(pm);
	 pack_hours(ph);
	 //pack_minutes(shudle_minute);
	 //pack_hours(shudle_hours);
	 houses_control(curent_intr);

     if(second_sep_invers==0)
     {
	 second_sep_on();
     }else {
     second_sep_off();
    }
	}
       else

	{
	 ClockIcon;

	 // Tout_setup= curent_intr; //загружаем номер текущего интервала
	 Tout_setup=  shudle_setup_t;

     if(invert_setup_temp_cikl==255){
             Tcur1_setup=Tout_setup;
            if(Tcur1_setup!=Tcur2_setup)
           {
           Tout_setup = Tcur2_setup;
           tempere_setup_change=1;     // как только интервал изменился
           }
         }
         else {
             Tcur2_setup=Tout_setup;
             if(Tcur2_setup!=Tcur1_setup)
              {
              Tout_setup = Tcur2_setup;
              tempere_setup_change=1;     // как только интервал изменился
              //
              }
        }

      invert_setup_temp_cikl= ~  invert_setup_temp_cikl;


      if(tempere_setup_change==1)// как только произошло обновление  в смене интервала, и поменялась Температура
      {
      setup_temp = shudle_setup_t;// загружаем обновленное  значение Температурі интервала и вводим на экран
      tempere_setup_change=0; // пока кнопкам не изменим

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

      }

#ifndef SK3_LCD
      pack_temperature9876D(setup_temp);
#else
      pack_temperature7654D(setup_temp);
#endif

	 //pack_temperature9876D(shudle_setup_t);
	 houses_control(curent_intr);

//	 setup_temp = shudle_setup_t;


	if(sek_count_for_prog_anime>12)
    {
	sek_count_for_prog_anime =0;
	}

    }
//--------------------------------------- Вывод иконки "часы"-----------------------------------------------------
     if(set_date_clock==0)//если время сбросилось, то показываем иконку "часы"
      {
          if(invers_clock_icon==0 ) // моргаем иконкой "часы"
          {
       clock_off();
          }else {
       clock_on();
         }

      }else
      {
       clock_on(); // иначе статично  показываем  иконку "часы" для данного режима
      }

#ifndef SK3_LCD  // если НЕ  маленький ЖКИ  , т.е большой
     frame_5G_on();// зажигаем рамку
     pack_heap(what_day (py, pmon,pd ));//
#else
     pack_day(what_day (py, pmon,pd ));//
#endif

	}



//------------------------------------------- SFM  режим --------------------------------------------------------

	if(main_screen_type== main_screen_SFM)
	    {

    int8 sfm_min_dec, sfm_min_unit,relax_time_dec,relax_time_unit;

	    sfm_min_dec =   sfm_min/10;// количество десятков
	    sfm_min_unit = sfm_min - (sfm_min_dec*10);// количество единиц

	 // в этом режиме функция термостата " НЕ ДОСТУПНА"
	 //   Tout_int = 0;


if(( start_lock_anime_timer==0)||(lock_key == unlock))// в случае  "LOC" ON/OFF
{
	        pack1d(get_symbol(sfm_min_dec));
	        pack2d(get_symbol(sfm_min_unit));
			clock_on();
}

if(( start_lock_anime_timer==0)||(lock_key == unlock))// в случае  "LOC" ON/OFF
{
	if(active_time>0)
     {

	    pack_minutes(active_time);

    if( start_back_light==0)// если подсветка выключена
     {

        REL_ON;

     } // то включаем физически реле

#ifdef SK3_LCD  // если определен "малый єкран"
      RED_ON;
#endif
      heat_on_off=1;
      ON_Icon_event=1; // генерим событие для значка  ON
      OFF_Icon_event=0;
      }

	if(active_time==0)
      {
#ifndef SK3_LCD  // если НЕ  маленький ЖКИ  , т.е большой
	  pack8d( SIGN_DEFIS);
#else
	  pack6d( SIGN_DEFIS);
#endif

      pack_minutes(relax_time);

      REL_OFF;
#ifdef SK3_LCD  // если определен "малый єкран"
      GREEN_ON;
#endif
      heat_on_off=1;
      ON_Icon_event=0;
      OFF_Icon_event=1; // генерим событие для значка  OFF (тушим ON)

            }
}

			SFM_mode_timer(); // вставляем в виртуальный таймер с тиком 1 секунда!!

if(( start_lock_anime_timer==0)||(lock_key == unlock))// в случае  "LOC" ON/OFF
{
	        if(second_sep_invers==0)// моргаем двоеточием  в знакоместе часы
	           {second_sep_on();}
	        else
	           {second_sep_off();}
}


	            //ON_Icon_event=1;
	            //OFF_Icon_event=0;



	      }

//----------------------------------------- end off SFM  режим --------------------------------------------------


	if((main_screen_type== main_screen_manual)||(main_screen_type== main_screen_prog))
    {


    termostat();// обновление изменения  в функции термостат







    }// иначе управление реле в режиме SFM

//-------------------------- обновление значка  НАГРЕВ в MAIN_SCREEN --------------------------------------------



	if(start_lock_anime_timer==0)// показываем если "РАЗЛОЧЕНО"
	  {
	                if(ON_Icon_event==1 )
	                {
	                    heat_on();
	                }
	                if(OFF_Icon_event==1 )
	                {
	                    heat_off();
	                }
	  }



}
	 else   // иначе  устройство аля программно "ВЫКЛ"
{

#ifdef SK3_LCD
    GREEN_RED_OFF;// гасим светодиоды
#endif
  // переводим устройство в меню "control",где оно дальше будет ждать быстрого нажатия иди долгодо кнопки MODE итд//
  // согласно базовой последовательности

	     screen_level=CONTROL_MENU;
	     UP_press=1;// переводим кнопку MODE на "отжатие" + Long Press Mode
}









}


void    control_menu(void) {


    if((device_on_off== device_on)&(screen_level == CONTROL_MENU)) // если девайс  программно "включен"
  {
    start_back_light=0;// останавливаем счетчик автопогашения подсветки , если успели зайти раньше из Основного экрана

    if(ON_Icon_event==1 )
    {
    REL_OFF;//   отключаем реле
    DelayMs(10);
    }
    LIGTH_ON;
  } else {   //   если девайс программно "выключен"

    LIGTH_OFF;
    REL_OFF;

#ifdef SK3_LCD
    GREEN_RED_OFF;// гасим светодиоды
#endif
    if(event_type== key_event_mode) // при нажатии на кнопку mode - попадаем в начало процесса в MAIN_SCREEN
        {
        //SetSysClock(CLK_SOURCE_PLL_60MHz);// возвращаем системмную частоту
        //обновляем статус device_on_off нашего девайса
        device_on_off= device_on;
        // пишем во флеш состояние
        SYSTEM_TO_FLASH();
        GPIOB_SetBits(bTXD1);
        GPIOB_ModeCfg(bTXD1, GPIO_ModeOut_PP_5mA);
        UART1_DefInit();

        device_on_off= device_on;
        screen_level = MAIN_SCREEN;
        screen_refresh_flag=1;
        Stand_Bay_Waike=1;

        //------------------------------------проверка device_default--------------------------------------------
          if(device_default == TRUE)
           {
           device_default = FALSE;   // сбрасываем флаг device_default,если он был выставлен)
           clear_screen();
           pack123D_custom(((SIGN_r << 16) | (SIGN_E << 8) | SIGN_S));
           s = EEPROM_ERASE(SYSTEM_EEPROM_ADR, EEPROM_MIN_ER_SIZE);//затираем SYSTEM_EEPROM
           DelayMs(1000);
           s = EEPROM_ERASE(BASE_EEPROM_ADR, EEPROM_MIN_ER_SIZE);//затираем РАСПИСАНИЕ
           DelayMs(3000);
           SYS_ResetExecute();//      FULL  RESET CH582 !!
           }
        //---------------------------------------------------------------------------------------------------------

        }


    if(event_type== key_long_mode_yes) // при линном нажатии на кнопку mode - попадаем в SEVICE MENU
       {
        screen_level = SERVICE_MENU;
        screen_refresh_flag=1;
       }


   }

  if((device_on_off== device_on)&(screen_level == CONTROL_MENU))
  {
  //---------------------------------- АНАЛИЗИРУЕМ КНОПКИ--------------------------------
    if(event_type == key_event_plus)
        {control_menu_navigate =  control_menu_navigate + 1;BUSY_KEY=1;}
    if(event_type== key_event_minus)
        {control_menu_navigate =  control_menu_navigate - 1;BUSY_KEY=1;}
    if(control_menu_navigate >5)
       {control_menu_navigate= 0;}
    if(control_menu_navigate <0)
       {control_menu_navigate=5;}

 //--------------------------------------- ХОД ПО  КРУГОВОМУ МЕНЮ-----------------------------------
   if(control_menu_navigate==0) // если меню  "ручной режим"
   {clear_screen();HandIcon; screen_refresh_flag=1;

   if(event_type== key_event_mode)
   {screen_level = MAIN_SCREEN; screen_refresh_flag=1;
   sek_count=0;//сбрасываем таймер подсветки
   start_back_light=1;// стартуем таймер подсветки так выходим обратно в  MAIN_SCREEN
   main_screen_type= main_screen_manual;
   FLASH_UPDATE=1;
   if(TIME_UPDATE==1)// при обновлении RTC - пишем во flash _ reset
         {
       SYSTEM_TO_FLASH();
       LIGTH_OFF;         // тушим подсветку
       clear_screen();// чистим экран
       REL_OFF;
       GPIOA_ModeCfg(GPIO_Pin_All, GPIO_ModeIN_PD);
       GPIOB_ModeCfg(GPIO_Pin_All, GPIO_ModeIN_PD);
       RTC_InitTime(my_py, my_pmon, my_pd, my_ph, my_pm, my_ps);
       SYS_ResetExecute();//      FULL  RESET CH582 !!
         }
   }
   }
 //---------------------------------------------------------------------------
   if(control_menu_navigate==2)// если меню  "программный режим"
   {clear_screen();ProgIcon; screen_refresh_flag=1;

                if(event_type == key_event_mode)// если ловим короткое нажатие  mode
                {
                  screen_level = MAIN_SCREEN; screen_refresh_flag=1;
                  sek_count=0;//сбрасываем таймер подсветки
                  start_back_light=1;// стартуем таймер подсветки так выходим обратно в  MAIN_SCREEN
                  main_screen_type= main_screen_prog;
                  FLASH_UPDATE=1;
                  if(TIME_UPDATE==1)// при обновлении RTC - пишем во flash _ reset
                  {
                      SYSTEM_TO_FLASH();
                      LIGTH_OFF;         // тушим подсветку
                      clear_screen();// чистим экран
                      REL_OFF;
                      GPIOA_ModeCfg(GPIO_Pin_All, GPIO_ModeIN_PD);
                      GPIOB_ModeCfg(GPIO_Pin_All, GPIO_ModeIN_PD);
                      RTC_InitTime(my_py, my_pmon, my_pd, my_ph, my_pm, my_ps);
                      SYS_ResetExecute();//      FULL  RESET CH582 !!
                  }
                }


   }
    //---------------------------------------------------------------------------
      if(control_menu_navigate==3)// если меню  "настройка программного програмного режима"
      {clear_screen();//ProgIcon;

                    pack123D_custom(((SIGN_P << 16) | (SIGN_r<< 8) | (SIGN_o )));


                    pack9876D_custom(( (SIGN_t << 24) | (SIGN_u << 16) | (SIGN_n << 8)| (0 << 0) ) );


                    screen_refresh_flag=1;// флаг обновления єкрана

                    if(event_type == key_event_mode)
                    //анализируем движение по внутреннему круговому меню level_1  программного режима
                    {
                    screen_level = PROG_MENU;
                  //  memcpy(Shedull_Copy_Pointer, SCHEDULE_RESERVE, sizeof(Shedull_Copy_Pointer));
                    // копируем прочитанное из EEPROM расписание для одномерноего ОЗУ буфера
                    // в 3D ОЗУ многомерный массивЮ для удобства дальнейшего обновления / анализа
                    }

      }

      if(control_menu_navigate==4)// если меню  режим "SFM"
   {clear_screen();PowModeIcon;
   //percent_on();
   clock_on(); screen_refresh_flag=1;

   if(event_type == key_event_mode)// если ловим короткое нажатие  mode
    {
        screen_refresh_flag=1;
        main_screen_type  = main_screen_SFM;// активция режима SFM
        FLASH_UPDATE=1;// пишем во флеш состояние
        screen_level = MAIN_SCREEN;
        sek_count=0;//сбрасываем таймер подсветки
        start_back_light=1;// стартуем таймер подсветки так выходим обратно в  MAIN_SCREEN
    }

   }

//-----------------------------------------------------------------------------
      if(control_menu_navigate==5)// если меню "настройка часов"
   {clear_screen();ClockIcon; screen_refresh_flag=1;

   if(event_type== key_event_mode)
   {screen_level = TIME_MENU;
   invers_blynk_image_1S =255;
   Task3_1=Reload_Task;//сбросили и перезагрузили  Task3_1

   screen_refresh_flag=1;}
   }
//----------------------------------------------------------------------------
     if(control_menu_navigate==1) //  если меню выключение девайса
    {
     if (device_on_off== device_on)
     {
    pack123D_custom(((SIGN_O  << 16) | (SIGN_F << 8) | SIGN_F));

    }
    if((event_type== key_event_mode)&(device_on_off== device_on))
       {
       LIGTH_OFF;         // тушим подсветку
       clear_screen();// чистим экран
       REL_OFF;
       device_on_off= device_off;
       screen_refresh_flag=1;

       UP_press=1;// переводим кнопку MODE на "отжатие" + Long Press Mode

       // FLASH_UPDATE=1;// пишем во флеш состояние
       SYSTEM_TO_FLASH();

       SetSysClock(CLK_SOURCE_PLL_20MHz);// понижаем системмную частоту
       GPIOB_SetBits(bTXD1);
       GPIOB_ModeCfg(bTXD1, GPIO_ModeOut_PP_5mA);
       UART1_DefInit();



       }
        }
//----------------------------------------------------------------------------
#define  DEBUG_print_out
#ifndef  DEBUG_print_out
      GPIOA_SetBits(bTXD1);
      GPIOA_ModeCfg(bTXD1, GPIO_ModeOut_PP_5mA);
#endif

    #ifndef  DEBUG_print_out
    PRINT(" control_menu_navigate    =%d\n", control_menu_navigate);

    printf("--      \n");
    DelayMs(10);// задержка для очистки мусора гипертерминала  перед  GPIOA_ModeCfg(bTXD1, GPIO_ModeIN_PD)
    GPIOA_ModeCfg(bTXD1, GPIO_ModeIN_PD);
#endif

  }

}

void    time_menu(void)
{
// ВНИМАНИЕ! системмные RTC инициализируются только раз или после RESET при инициализации HAL TIME ( перед запуском стека)!
 // поєтому можно менять "добавочные парметры" которые  можно  приплюсовывать к текущему  RTC_InitTim


       if(event_type == key_event_mode)
        {

       if( time_menu_navigate >5)
         { time_menu_navigate= 0;
         }

       if(control_menu_navigate <0)
         {
           time_menu_navigate=5;
         }

        time_menu_navigate++;
        invers_blynk_image_1S =255;

 //----------------------------ПЕРЕДАЧА СООБЩЕНИЙ/УПРАВЛЕНИЯ МЕЖДУ TASK - ами !!!  -------------------------//

   // прямое управление из разных функций от одного Task к другому Task, в явном виде не вызываются при вызове глубоких уровней

   // нужно использовать косвенную передачу команд собщений, которые нормально вызываются
   // в основном теле любого Task!!!

   // НЕ ВЫЗЫВАЕТСЯ!!!  tmos_start_reload_task( task3 , sub_event_1 ,1.6*1.0* start_task_delay);

   // ВЫЗЫВАЕТСЯ ПРАВИЛЬНО  Task3_1=Reload_Task; косвенно через фоновый Task1_2

      Task3_1=Reload_Task;//сбросили и перезагрузили  Task3_1

        }



//-------------------------- START OFF  обновление знакоместа "час"-----------------------------------
        if(time_menu_navigate==3)  // заходим в настройку  "час"

       { screen_refresh_flag=1;

      my_ph =set_blynk_hours(my_ph,my_pm);// my_ph -динамически обновляемый параметр, обновляется и возвращает в
   // my_ph обновленный результат!!!, my_pm -  чисто для визуальной картинки статического значения в соседнем отображаемом  знакоместе

       }//---------------------------END OFF  обновление знакоместа "час"-------------------------------


 //-------------------------------- START OFF  обновление знакоместа "МИНУТЫ"---------------------------
         if(time_menu_navigate==4)
       { screen_refresh_flag=1;

         my_pm = set_blynk_minutes(my_pm,my_ph);// my_pm -динамически обновляемый параметр, обновляется и возвращает в
      // my_pm обновленный результат!!!, my_ph - чисто для визуальной картинки статического значения в соседнем отображаемом  знакоместе

       }//---------------------------END OFF  обновление знакоместа "МИНУТЫ"-------------------------------


  //-------------------------- START OFF  обновление знакоместа "ДЕНЬ"-----------------------------------
         if(time_menu_navigate==2)  // заходим в настройку  "час"
       { // статического изображения - маски нет в оригинале
       screen_refresh_flag=1;

       u8 max_day = 0; // максимум дней в текущем месяце
       max_day = getNumberOfDays(my_pmon, my_py);

  //-----------------------------------------------------------------------------------------------------
       if(event_type == key_event_plus)
       {my_pd++;BUSY_KEY=1;
       Task3_1=Reload_Task;//сбросили и перезагрузили  Task3_1
       pack_minutes(my_pd);
       screen_refresh_flag=1;
       invers_blynk_image =255;

       }//обновление "час" по кнопке +

       if(event_type== key_event_minus)
       { my_pd--;BUSY_KEY=1;
       Task3_1=Reload_Task;//сбросили и перезагрузили  Task3_1
       pack_minutes(my_pd);
       screen_refresh_flag=1;
       invers_blynk_image =255;


       }//обновление "час" по кнопке -

     //  max_day


         if(my_pd >max_day)// сброс кольца при переполнении час в случа +
           {my_pd= 1;}
           if(my_pd <1)//  сброс кольца при переполнении час в случа -
           {my_pd=max_day;}





  //--------------------------фоновое обновление(моргание) знакоместа "час" по состоянию измениея invers_image =  255 / 0


     if(BUSY_KEY==1)//как только нажали кнопку, то обнулили таймер обновления HLW8110
       {// и ждем пока он натикает через время Т после отпускания кнопки + 1сек
       invers_blynk_image_1S=255;
       }

     if(invers_blynk_image_1S==255 )
       {
       pack_minutes(my_pd);//   выводим фоново с учетом таймера моргания  "час"
       }
        else // если не разрешено моргание
       {
       pack_hours(non_hour);//  тушим фоново  с учетом таймера моргания  "час"
       pack_minutes(non_min);
                    }


 }//---------------------------END OFF  обновление знакоместа "ДЕНЬ"-------------------------------


//-------------------------- START OFF  обновление знакоместа "МЕСЯЦ"-----------------------------------
         if(time_menu_navigate==1)  // заходим в настройку  "час"

       { // статического изображения - маски нет в оригинале
           screen_refresh_flag=1;

  //-----------------------------------------------------------------------------------------------------
       if(event_type == key_event_plus)
       {my_pmon++;BUSY_KEY=1;
       Task3_1=Reload_Task;//сбросили и перезагрузили  Task3_1
       pack_hours(my_pmon);
       screen_refresh_flag=1;
       invers_blynk_image =255;
       }
       //обновление "час" по кнопке +
       if(event_type== key_event_minus)
       {my_pmon--;BUSY_KEY=1;
       Task3_1=Reload_Task;//сбросили и перезагрузили  Task3_1
       pack_hours(my_pmon);
       screen_refresh_flag=1;
       invers_blynk_image =255;
       }//обновление "час" по кнопке -
       if(my_pmon >12)// сброс кольца при переполнении час в случа +
       {my_pmon= 1;}
       if(my_pmon <1)//  сброс кольца при переполнении час в случа -
       {my_pmon=12;}

 //--------------------------фоновое обновление(моргание) знакоместа "час" по состоянию измениея invers_image =  255 / 0


       if(BUSY_KEY==1)//как только нажали кнопку, то обнулили таймер обновления HLW8110
             {// и ждем пока он натикает через время Т после отпускания кнопки + 1сек
             invers_blynk_image_1S=255;
             }

           if(invers_blynk_image_1S==255 )
             {
             pack_hours(my_pmon);//   выводим фоново с учетом таймера моргания  "час"
             }
            else // если не разрешено моргание
             {
             pack_hours(non_hour);//  тушим фоново  с учетом таймера моргания  "час"
             pack_minutes(non_min);
             }


   }//---------------------------END OFF  обновление знакоместа "час"-------------------------------




 //-------------------------- START OFF  обновление знакоместа " ГОД "-----------------------------------
       if(time_menu_navigate==0)  // заходим в настройку  "час"

      { // статического изображения - маски нет в оригинале

       //   my_py = (py-2020)+ my_py;
          screen_refresh_flag=1;
 //-----------------------------------------------------------------------------------------------------
      if(event_type == key_event_plus)
      {my_py++;BUSY_KEY=1;
      Task3_1=Reload_Task;//сбросили и перезагрузили  Task3_1
       pack_year(my_py);screen_refresh_flag=1;
       invers_blynk_image =255;
      }//обновление "час" по кнопке +
      if(event_type== key_event_minus)
      {my_py--;BUSY_KEY=1;
       Task3_1=Reload_Task;//сбросили и перезагрузили  Task3_1
       pack_year(my_py);  screen_refresh_flag=1;
        invers_blynk_image =255;
      }//обновление "час" по кнопке -
      if(my_py >2150)// сброс кольца при переполнении час в случа +
      {my_py= 2020;}
      if(my_py <2020)//  сброс кольца при переполнении час в случа -
      {my_py=2020;}

//--------------------------фоновое обновление(моргание) знакоместа "час" по состоянию измениея invers_image =  255 / 0

      if(BUSY_KEY==1)//как только нажали кнопку, то обнулили таймер обновления HLW8110
        {// и ждем пока он натикает через время Т после отпускания кнопки + 1сек
        invers_blynk_image_1S=255;
        }

      if(invers_blynk_image_1S==255 )
        {
        pack_year(my_py);//   выводим фоново с учетом таймера моргания  "час"
        }
       else // если не разрешено моргание
        {
        pack_hours(non_hour);//  тушим фоново  с учетом таймера моргания  "час"
        pack_minutes(non_min);
        }

//-----------------------------------------------------------------------------------


      }//---------------------------END OFF  обновление знакоместа "час"-------------------------------

      if(time_menu_navigate==5)  //циклический выход после входа
           {
           time_menu_navigate=0;
           screen_level = CONTROL_MENU;
           start_bink=0;//запрещаем блинканье

           TIME_UPDATE=1;// если сделали измения в RTC отличное от того что после включения девайса
           //то после выхода в главный экран идет RESET  системм с обновленными параметрами времени

           }


}


void prog_menu(void)
{
        LIGTH_ON;

 //---------------------------- крутим  и анализируем пункты  данного кругового меню кнопками + и -
               if(event_type == key_event_plus)//
               {pro_tune_menu_navigate++ ;BUSY_KEY=1;
               }
               if(event_type== key_event_minus)
               {pro_tune_menu_navigate--;BUSY_KEY=1;
               }
               if(pro_tune_menu_navigate >8)
                {pro_tune_menu_navigate= 0;}
               if(pro_tune_menu_navigate <0)
                {pro_tune_menu_navigate=8;}

 // 1. ------------------------------ подменю "НАСТРОЙКА РАСПИСАНИЯ --------------------

 //  ------------------------------ подменю "выбор дня недели --------------------

               if(pro_tune_menu_navigate<=6) // заходим в настройку  "OUT"
                {
                selected_day=pro_tune_menu_navigate+1;
                screen_refresh_flag=1;
#ifndef SK3_LCD
                pack_heap(selected_day);//
#else

#endif

 //---------------------------------------РАМКА ХИТРОГО ЗНАКОМЕСТА------------------------------------
               if(invers_blynk_image_1S==255 )
                {
#ifndef SK3_LCD
                  frame_5G_on();// зажигаем рамку
#else
                  pack_day(selected_day);// высвечиваем выбранный день для малого экрана
#endif
                }
                  else
                {
#ifndef SK3_LCD   // или не обновлем обьект 1 секунду до следующего цикла маоргания
                  frame_5G_off();//тушим рамку
#else
                  pack_day(~selected_day);// высвечиваем выбранный день для малого экрана
#endif
                }
 //----------------------------------------------------------------------------------------------------
               if(event_type == key_event_mode)
                {
                screen_level = PROG_SELECTED_DAY;// переходим в подменю " prog_tune_selected_day()"
                screen_refresh_flag=1;
                memcpy(Shedull_Copy_Pointer, SCHEDULE_RESERVE, sizeof(Shedull_Copy_Pointer));
                FLASH_UPDATE=1;

                // копируем прочитанное из EEPROM расписание для одномерноего ОЗУ буфера
               // в 3D ОЗУ многомерный массивЮ для удобства дальнейшего обновления / анализа



                }
                }
 // 2. ------------------------------ подменю  " РЕЖИМ "COPY DAY" --------------------
               if(pro_tune_menu_navigate==7)  // заходим в настройку  "OUT"
                { // статического изображения - маски нет в оригинале
                 pack123D_custom(((SIGN_d << 16) | (SIGN_A<< 8) | (SIGN_Y )));
                 pack9876D_custom(( (SIGN_C << 24) | (SIGN_O << 16) | (SIGN_P << 8)| (SIGN_Y << 0) ) );
                 screen_refresh_flag=1;// флаг обновления єкрана

                if(event_type == key_event_mode)
                {
                 screen_level = COPY_DAY_MENU ;// переходим в подменю " prog_tune_selected_day()"
                 memcpy(Shedull_Copy_Pointer, SCHEDULE_RESERVE, sizeof(Shedull_Copy_Pointer));
                 FLASH_UPDATE=1;
                 //заносим первоначальное значение расписания в буфер
                 screen_refresh_flag=1;
                }
      // при нажатии на кнопку "MODE", активируем  переход внутрь меню "COPY DAY"


                 }

 // 3. ------------------------------ ВЫХОД  в предыдущее МЕНЮ   --------------------
               if(pro_tune_menu_navigate==8)  // заходим в настройку  "OUT"
                 { // статического изображения - маски нет в оригинале
                 pack123D_custom(((SIGN_O << 16) | (SIGN_u<< 8) | (SIGN_t )));
                 screen_refresh_flag=1;// флаг обновления єкрана

                if(event_type== key_event_mode)// в подменю OUT  , при коротком нажатии MDE возвращаемся в предыдущее МЕНЮ
                {
                screen_level = CONTROL_MENU; screen_refresh_flag=1;
                //control_menu_navigate=0;
                tmos_stop_task( task3 , sub_event_2 );
                SCHEDULE_UPDATE=1;// при выходе из меню - пересохраняем РАСПИСАНИЕ в EEPROM
                pro_tune_menu_navigate = 0; // сбрасываем в исходное положение указатель меню prog_level_1
                }
                 }
//--------------------------------------------------------------------------------------

}




void prog_selected_day(void) // выбор дня недели для дальнейшей настройки / выход в предыдущее меню
{

uint8 shudele_p =0;

UP_press=1;// переводим кнопку MODE  в режим  LONG PRESS

#ifndef SK3_LCD
    frame_5G_on();// зажигаем рамку
#else

#endif

#ifndef  SK3_LCD   // сли Большой єкран
    pack_heap(selected_day);//
#else
    pack_day(selected_day);// высвечиваем выбранный день для малого экрана
#endif

    screen_refresh_flag=1;

    select_day_buf =selected_day -1;
    dss = DAY_SHUFT* select_day_buf;

    curent_sys_time =  time_convert_to_min (ph, pm );// преобразуем текущее системное время в минуты

    if(event_type == key_event_mode) // если нажали кнопку Mode
   // if(event_type == key_long_mode_yes) // если нажали кнопку Mode

     {
        prog_selected_day_menu_navigate++;
        tmos_stop_task( task3 , sub_event_2 );
     }

    if(prog_selected_day_menu_navigate >17+1)// сброс кольца при переполнении  в случае +
             {prog_selected_day_menu_navigate= 0;
             }
    if(prog_selected_day_menu_navigate <0)//  сброс кольца при переполнении в случае -
             {prog_selected_day_menu_navigate=17+1;
             }

    // анализ и изменения параметров по результатам нажатия кнопок + и -
    //в самих функциях:
    //set_blynk_hours
    //set_blynk_minutes
    //set_blynk_tempere


         switch (prog_selected_day_menu_navigate)
          {

     case  0:  curent_intr=0;SCHED_3D[select_day_buf][curent_intr][Shed_ph] =  set_shedule_hours (SCHED_3D[select_day_buf][curent_intr][Shed_ph],
               SCHED_3D[select_day_buf][curent_intr][Shed_pm]);sun_on();
               break;
     case  1:  curent_intr=0;SCHED_3D[select_day_buf][curent_intr][Shed_pm] =  set_shedule_minutes (SCHED_3D[select_day_buf][curent_intr][Shed_pm],
               SCHED_3D[select_day_buf][curent_intr][Shed_ph]);sun_on();
               break;
     case  2:  curent_intr=0;SCHED_3D[select_day_buf][curent_intr][Shed_tp] =  set_shedule_tempere (SCHED_3D[select_day_buf][curent_intr][Shed_tp]);
               sun_on();
               break;
     case  3:  curent_intr=1;SCHED_3D[select_day_buf][curent_intr][Shed_ph] =  set_shedule_hours (SCHED_3D[select_day_buf][curent_intr][Shed_ph],
               SCHED_3D[select_day_buf][curent_intr][Shed_pm]);house_out_on();
               break;
     case  4:  curent_intr=1;SCHED_3D[select_day_buf][curent_intr][Shed_pm] =  set_shedule_minutes (SCHED_3D[select_day_buf][curent_intr][Shed_pm],
               SCHED_3D[select_day_buf][curent_intr][Shed_ph]);house_out_on();
               break;
     case  5:  curent_intr=1;SCHED_3D[select_day_buf][curent_intr][Shed_tp] =  set_shedule_tempere (SCHED_3D[select_day_buf][curent_intr][Shed_tp]);
               house_out_on();
               break;
     case  6:  curent_intr=2;SCHED_3D[select_day_buf][curent_intr][Shed_ph] =  set_shedule_hours (SCHED_3D[select_day_buf][curent_intr][Shed_ph],
               SCHED_3D[select_day_buf][curent_intr][Shed_pm]);bar_in_on();
               break;
     case  7:  curent_intr=2;SCHED_3D[select_day_buf][curent_intr][Shed_pm] =  set_shedule_minutes (SCHED_3D[select_day_buf][curent_intr][Shed_pm],
               SCHED_3D[select_day_buf][curent_intr][Shed_ph]);bar_in_on();
               break;
     case  8:  curent_intr=2;SCHED_3D[select_day_buf][curent_intr][Shed_tp] =  set_shedule_tempere (SCHED_3D[select_day_buf][curent_intr][Shed_tp]);
               bar_in_on();
               break;
     case  9:  curent_intr=3;SCHED_3D[select_day_buf][curent_intr][Shed_ph] =  set_shedule_hours (SCHED_3D[select_day_buf][curent_intr][Shed_ph],
               SCHED_3D[select_day_buf][curent_intr][Shed_pm]);bar_out_on();
               break;
     case 10:  curent_intr=3;SCHED_3D[select_day_buf][curent_intr][Shed_pm] =  set_shedule_minutes (SCHED_3D[select_day_buf][curent_intr][Shed_pm],
               SCHED_3D[select_day_buf][curent_intr][Shed_ph]);bar_out_on();
               break;
     case 11:  curent_intr=3;SCHED_3D[select_day_buf][curent_intr][Shed_tp] =  set_shedule_tempere (SCHED_3D[select_day_buf][curent_intr][Shed_tp]);
               bar_out_on();
               break;
     case 12:  curent_intr=4;SCHED_3D[select_day_buf][curent_intr][Shed_ph] =  set_shedule_hours (SCHED_3D[select_day_buf][curent_intr][Shed_ph],
               SCHED_3D[select_day_buf][curent_intr][Shed_pm]);house_in_on();
               break;
     case 13:  curent_intr=4;SCHED_3D[select_day_buf][curent_intr][Shed_pm] =  set_shedule_minutes (SCHED_3D[select_day_buf][curent_intr][Shed_pm],
               SCHED_3D[select_day_buf][curent_intr][Shed_ph]);house_in_on();
               break;
     case 14:  curent_intr=4;SCHED_3D[select_day_buf][curent_intr][Shed_tp] =  set_shedule_tempere (SCHED_3D[select_day_buf][curent_intr][Shed_tp]);
               house_in_on();
               break;
     case 15:  curent_intr=5;SCHED_3D[select_day_buf][curent_intr][Shed_ph] =  set_shedule_hours (SCHED_3D[select_day_buf][curent_intr][Shed_ph],
               SCHED_3D[select_day_buf][curent_intr][Shed_pm]);moon_on();
               break;
     case 16:  curent_intr=5;SCHED_3D[select_day_buf][curent_intr][Shed_pm] =  set_shedule_minutes (SCHED_3D[select_day_buf][curent_intr][Shed_pm],
               SCHED_3D[select_day_buf][curent_intr][Shed_ph]);moon_on();
               break;
     case 17:  curent_intr=5;SCHED_3D[select_day_buf][curent_intr][Shed_tp] =  set_shedule_tempere (SCHED_3D[select_day_buf][curent_intr][Shed_tp]);
               moon_on();
               break;



     case 18: prog_selected_day_menu_navigate=0;screen_level=PROG_MENU;
              //pro_tune_menu_navigate++;// автопереход на следующий день...можно убрать

              memcpy(SCHEDULE_RESERVE, Shedull_Copy_Pointer, sizeof(SCHEDULE_RESERVE));// копируем обратно в ОЗУ обновленный  3D массив
              // в одномерній массив для дальнейшей перезаписи в EEPROM
              FLASH_UPDATE=1;
              UP_press=0;// переводим кнопку MODE  в режим  КАСАНИЯ
              break;// выход из  switch + возврат в предыдущее меню


          }









}

void SFM_mode_timer(void)// ставляем в виртуальный таймер с тиком 1 секунда!!
{


//#define SFM_mode_timer_debug

//    if(main_screen_type== TRUE)


#ifndef SFM_mode_timer_debug
        GPIOB_SetBits(bTXD1);
        GPIOB_ModeCfg(bTXD1, GPIO_ModeOut_PP_5mA);
#endif

    if(main_screen_type== main_screen_SFM)
          {

                   start_sfm_timer1=1;// запустили виртуальный таймер


//----------------------------------------------------------------------------------

                  if(sfm_sek_active==60)
                //    if(sfm_sek_active==1)
                   {
                   sfm_sek_active=0;
                   minutes_tm_1++;// виртуальный счетчик минут  , анализирует ход секунд RTC
                   relax_buf = (active_time_max - sfm_min)+ dead_time;//загружаем  relax таймер // test2 +
                   }



//----------------------------------------------------------------------------------
                   if(active_time>0)
                   {
                   active_time=active_buf- minutes_tm_1;// отображаем обратный отчет "активной фазы" без знака минус


                   if(active_time>0) // пропускаем для вывода на дисплей модифицированный active_time ==0
                     {                // выводим его далее в  if(active_time==0)

                       if((sfm_sek_active==0)&(LOCK_PRINT_OUT==0))
                    {
                     printf( "  active_time =%ld \n" ,    active_time);
                    // printf( "  sfm_sek_active =%ld \n" ,   sfm_sek_active);
                    }
                     }

                   }
///*
//-----------------------------------------------------------------------------------
                   if(active_time==0)
                   {
                   relax_time=relax_buf- (minutes_tm_1-sfm_min);

                   if( relax_time==0)// если релакс фаза закончилась
                   {
                    active_time =  sfm_min;// загружаем заново таймер
                    minutes_tm_1=0;
                    if((sfm_sek_active==0)&(LOCK_PRINT_OUT==0))
                    {
                    printf( "  active_time =%ld \n" ,    active_time);
                    }
                   }

                   if(relax_time!=0)
                   {
                   if((sfm_sek_active==0)&(LOCK_PRINT_OUT==0))
                   {
                   printf( "  relax_time =- %ld \n" ,    relax_time);
                   }
                   }

                   }
//------------------------------------------------------------------------------------




                   if((sfm_sek_active==0)&(LOCK_PRINT_OUT==0))
                    {
                     LOCK_PRINT_OUT=1;
                    }

                    if(sfm_sek_active>0)
                    {
                     LOCK_PRINT_OUT=0;// сбрасываем флаг блокировки вывода на гипертерминал
                    }



 //-----------------------------------end  of start_sfm_timer1 -----------------------------------------


                #ifndef SFM_mode_timer_debug
                 // printf("--      \n");
                  DelayMs(5);// задержка для очистки мусора гипертерминала  перед  GPIOA_ModeCfg(bTXD1, GPIO_ModeIN_PD)
                  GPIOB_ModeCfg(bTXD1, GPIO_ModeIN_PD);
                  //GPIOB_SetBits(p13);
                #endif




           } else
           {
               start_sfm_timer1=0;// в противном случае отсанавливаем Таймер SFM
               sfm_sek_active=0;// и обнуляем его
        }


}




int16  set_blynk_hours(int16 hours,int16 minutes)
{

    ClockIcon;pack_minutes(minutes);second_sep_on();// статическое значение - неподвижная МАСКА
   //-----------------------------------------------------------------------------------------------------
          if(event_type == key_event_plus)
          {hours++;BUSY_KEY=1;
      //    tmos_stop_task( task3 , sub_event_2 );
          //tmos_start_reload_task( task3 , sub_event_2 ,1.6*reload_task );
          ClockIcon;pack_hours(hours);
          //screen_refresh_flag=1;
          //start_bink=0;
          //Virtual_timer=1;
          invers_blynk_image =255;
          Task3_1=Reload_Task;//сбросили и перезагрузили  Task3_1
          }//обновление "час" по кнопке +
          if(event_type== key_event_minus)
          { hours--;BUSY_KEY=1;
    //      tmos_stop_task( task3 , sub_event_2 );
          //tmos_start_reload_task( task3 , sub_event_2 ,1.6*reload_task );
          ClockIcon;pack_hours(hours);
          screen_refresh_flag=1;
          //start_bink=0;
          //Virtual_timer=1;
          Task3_1=Reload_Task;//сбросили и перезагрузили  Task3_1
          invers_blynk_image =255;
          }//обновление "час" по кнопке -
          if(hours >23)// сброс кольца при переполнении час в случа +
            {hours= 0;}
          if(hours <0)//  сброс кольца при переполнении час в случа -
            {hours=23;}

   //--------------------------фоновое обновление(моргание) знакоместа "час" по состоянию измениея invers_image =  255 / 0


          if(BUSY_KEY==1)//как только нажали кнопку, то обнулили таймер обновления HLW8110
              {// и ждем пока он натикает через время Т после отпускания кнопки + 1сек
              invers_blynk_image_1S=255;
              }

            if(invers_blynk_image_1S==255 )
              {
                pack_hours(hours);//   выводим фоново с учетом таймера моргания  "час"
                second_sep_off();
              }
               else // если не разрешено моргание
              {
              pack_hours(non_hour);//  тушим фоново  с учетом таймера моргания  "час"
              pack_minutes(non_min);
                           }


        //    tmos_start_reload_task( task3 , sub_event_2 ,1.6*1 );



      return hours;

}

int16 set_blynk_minutes(int16 minutes,int16 hours)
{

    ClockIcon;pack_hours(hours);second_sep_on();// статическое значение - неподвижная МАСКА
     //-----------------------------------------------------------------------------------------------------
           if(event_type == key_event_plus)
           { minutes++;BUSY_KEY=1;

            ClockIcon;pack_minutes(minutes);
           screen_refresh_flag=1;
            Task3_1=Reload_Task;//сбросили и перезагрузили  Task3_1
           invers_blynk_image =255;
           }
           //обновление "час" по кнопке +
           if(event_type== key_event_minus)
           { minutes--;BUSY_KEY=1;
           ClockIcon;pack_minutes(minutes);
           screen_refresh_flag=1;
           Task3_1=Reload_Task;//сбросили и перезагрузили  Task3_1
           invers_blynk_image =255;
           }//обновление "час" по кнопке -
           if(minutes >59)// сброс кольца при переполнении час в случа +
           {minutes= 0;}
           if(minutes <0)//  сброс кольца при переполнении час в случа -
           {minutes=59;}
    //--------------------------фоновое обновление(моргание) знакоместа "час" по состоянию измениея invers_image =  255 / 0
  /*
           if(start_bink==1) // если разрешено  моргание
           {
           if(invers_blynk_image==0 )
           {
               second_sep_on();
               pack_minutes(minutes);//   выводим фоново с учетом таймера моргания  "минуты"

           } else {
               second_sep_off();
               pack_minutes(non_min);//  тушим фоново  с учетом таймера моргания  "минуты"
           }
           } else // если не разрешено моргание
           {
            pack_minutes(minutes);//   выводим фоново с учетом таймера моргания  "минуты"
           }
*/

           if(BUSY_KEY==1)//как только нажали кнопку, то обнулили таймер обновления HLW8110
               {// и ждем пока он натикает через время Т после отпускания кнопки + 1сек
               invers_blynk_image_1S=255;
               }

             if(invers_blynk_image_1S==255 )
               {
                 pack_minutes(minutes);;//   выводим фоново с учетом таймера моргания  "час"
                 second_sep_off();
               }
                else // если не разрешено моргание
               {
               pack_hours(non_hour);//  тушим фоново  с учетом таймера моргания  "час"
               pack_minutes(non_min);
                            }

       //      tmos_start_reload_task( task3 , sub_event_2 ,1.6*1 );


           return  minutes;


}




int16 set_shedule_tempere(int16 tempere)
{

         //-----------------------------------------------------------------------------------------------------
               if(event_type == key_event_plus)
               { tempere=tempere+5;
               BUSY_KEY=1;
               //tmos_stop_task( task3 , sub_event_2 );
               Task3_1=Reload_Task;//сбросили и перезагрузили  Task3_1
#ifndef SK3_LCD
      pack_temperature9876D(tempere);
#else
      pack_temperature7654D(tempere);
#endif
               screen_refresh_flag=1;
               //start_bink=0;Virtual_timer=0;
               invers_blynk_image=255;
               }//обновление "час" по кнопке +

               if(event_type== key_event_minus)
               { tempere = tempere-5;
               BUSY_KEY=1;
               //tmos_stop_task( task3 , sub_event_2 );
               Task3_1=Reload_Task;//сбросили и перезагрузили  Task3_1
#ifndef SK3_LCD
      pack_temperature9876D(tempere);
#else
      pack_temperature7654D(tempere);
#endif
               screen_refresh_flag=1;
               //start_bink=0;Virtual_timer=0;
               invers_blynk_image=255;
               }//
               if(tempere >500)// сброс кольца при переполнении час в случа +
               {tempere= 500;}
               if(my_pm <-200)//  сброс кольца при переполнении час в случа -
               {tempere=-200;}
        //--------------------------фоновое обновление(моргание) знакоместа "час" по состоянию измениея invers_image =  255 / 0

   /*
               if(start_bink==1) // если разрешено  моргание
               {
               if(invers_blynk_image==0 )
               {
#ifndef SK3_LCD
      pack_temperature9876D(tempere);
#else
      pack_temperature7654D(tempere);
#endif

               } else { //не моргает

#ifndef SK3_LCD
      pack_temperature9876D(tempere);
#else
      pack_temperature7654D(tempere);
#endif
                 //pack_temperature9876D(non_temp_large);//моргает
               }
               } else // если не разрешено моргание
               {

#ifndef SK3_LCD
      pack_temperature9876D(tempere);
#else
      pack_temperature7654D(tempere);
#endif

               }

 */

    // лучше без моргания выставлять температуру!!!

    //блокировка моргания

        invers_blynk_image_1S=255;

       if(BUSY_KEY==1)//как только нажали кнопку, то обнулили таймер обновления HLW8110
         {// и ждем пока он натикает через время Т после отпускания кнопки + 1сек
         invers_blynk_image_1S=255;
         }

       if(invers_blynk_image_1S==255 )
         {
#ifndef SK3_LCD
      pack_temperature9876D(tempere);
#else
      pack_temperature7654D(tempere);
#endif
         }
         else // если не разрешено моргание
         {
#ifndef SK3_LCD
      pack_temperature9876D(non_temp_large);
#else
      pack_temperature7654D(non_temp_small);
#endif
         }

//----------------------------------------------------------------------------------------------------------//

         if(event_type== key_long_mode_yes)   // в разделе "настройка минут" удерживаем MODE, то возвращаемся в
           // предыдущую настройку
           {
           prog_selected_day_menu_navigate--;
           }


    return  tempere;
}

// PS: !!!
// остальные прототипы пока реализованы прямо в теле TIME MENU



int16  set_shedule_hours(int16 hours,int16 minutes)// для работы с таблицей Shedule
{

    GPIOA_SetBits(bTXD1);
    GPIOA_ModeCfg(bTXD1, GPIO_ModeOut_PP_5mA);


    ClockIcon;
    pack_minutes(minutes);
    second_sep_on();// статическое значение - неподвижная МАСКА
   //-----------------------------------------------------------------------------------------------------
   //считываем время начала  текущего интервала согласно текщуему значению  таблицы Shedule . Оперируем в минутах


    curent_intr_time =  time_convert_to_min (hours,minutes );
    prev_intr_time =  time_convert_to_min (SCHED_3D[select_day_buf][int_position(curent_intr, prev_int)][Shed_ph],
                                           SCHED_3D[select_day_buf][int_position(curent_intr, prev_int)][Shed_pm] );

    next_intr_time =  time_convert_to_min (SCHED_3D[select_day_buf][int_position(curent_intr, next_int)][Shed_ph],
                                           SCHED_3D[select_day_buf][int_position(curent_intr, next_int)][Shed_pm] );

 //   minut_debug = minutes ;


   if(curent_intr==0)// находимся в 0 м интервале
   {
   prev_intr_time = 0; //00.00
   }

   if(curent_intr==5)// находимся в 5 м интервале
    {
    next_intr_time = 60*23+60 ; // 1440 минут
    }




          if(event_type == key_event_plus)
          {//hours++;

              curent_intr_time =  time_convert_to_min (hours,minutes );
              BUSY_KEY=1;
              printf("--      \n");


          if( (next_intr_time-30)- curent_intr_time>60)
        // if( next_intr_time- curent_intr_time>60)// разница в количестве часов более 1 часа, то можно сдвигать границу
         {                                //в сторону увеличения
            hours++;


     //      printf( "  hours  =%ld \n" ,    hours);
     //      printf( "  next_intr_time  =%ld \n" ,     next_intr_time);
     //      printf( "  curent_intr_time  =%ld \n" ,     curent_intr_time);


         }

          Task3_1=Reload_Task;//сбросили и перезагрузили  Task3_1
          ClockIcon;
          pack_hours(hours);
          screen_refresh_flag=1;
          invers_blynk_image_1S =255;
          }//обновление "час" по кнопке +



          if(event_type== key_event_minus)
          { //hours--;
          curent_intr_time =  time_convert_to_min (hours,minutes );
          BUSY_KEY=1;
          printf("--      \n");


          if(  curent_intr_time-(prev_intr_time-30)>60)
          //if(  curent_intr_time-prev_intr_time>30)// разница в количестве часов более 1 часа, то можно сдвигать границу
          {                                //в сторону уменьшения
          hours--;

   //       printf( "  hours  =%ld \n" ,    hours);
  //        printf( "  prev_intr_time  =%ld \n" ,     prev_intr_time);
   //       printf( "  curent_intr_time  =%ld \n" ,     curent_intr_time);


           }

          Task3_1=Reload_Task;//сбросили и перезагрузили  Task3_1
          ClockIcon;
          pack_hours(hours);
          screen_refresh_flag=1;
          invers_blynk_image_1S =255;
          }//обновление "час" по кнопке -



          pack_minutes(minutes);


          if(hours >23)// сброс кольца при переполнении час в случа +
            {hours= 0;}
          if(hours <0)//  сброс кольца при переполнении час в случа -
            {hours=23;}

   //--------------------------фоновое обновление(моргание) знакоместа "час" по состоянию измениея invers_image =  255 / 0

          if(BUSY_KEY==1)//как только нажали кнопку, то обнулили таймер обновления HLW8110
           {// и ждем пока он натикает через время Т после отпускания кнопки + 1сек
           invers_blynk_image_1S=255;
           }

          if(invers_blynk_image_1S==255 )
           {
           second_sep_on();
           pack_hours(hours);//   выводим фоново с учетом таймера моргания  "час"
           }
          else // если не разрешено моргание
           {
           second_sep_off();
           pack_hours(non_hour);//  тушим фоново  с учетом таймера моргания  "час"
           }


//-------------------------------------------------------------------------------------------------//
          if(event_type== key_long_mode_yes)   // в разделе "настройка минут" удерживаем MODE, то возвращаемся в
                   // предыдущую настройку
         {
          prog_selected_day_menu_navigate--;
          if(prog_selected_day_menu_navigate<0) // если меньше 0 , то идет возврат на выбор ДНЯ
          {
 prog_selected_day_menu_navigate=0;screen_level=PROG_MENU;
 memcpy(SCHEDULE_RESERVE, Shedull_Copy_Pointer, sizeof(SCHEDULE_RESERVE));// копируем обратно в ОЗУ обновленный  3D массив
                            // в одномерній массив для дальнейшей перезаписи в EEPROM
 FLASH_UPDATE=1;

          }

         }


      return hours;


      printf("---      \n");
      GPIOA_ModeCfg(bTXD1, GPIO_ModeIN_PD);



}


int16 set_shedule_minutes(int16 minutes,int16 hours)
{

    ClockIcon;pack_hours(hours);second_sep_on();// статическое значение - неподвижная МАСКА

    curent_intr_time =  time_convert_to_min (hours,minutes );
    prev_intr_time =  time_convert_to_min (SCHED_3D[select_day_buf][int_position(curent_intr, prev_int)][Shed_ph],
                                           SCHED_3D[select_day_buf][int_position(curent_intr, prev_int)][Shed_pm] );

    next_intr_time =  time_convert_to_min (SCHED_3D[select_day_buf][int_position(curent_intr, next_int)][Shed_ph],
                                           SCHED_3D[select_day_buf][int_position(curent_intr, next_int)][Shed_pm] );



   if(curent_intr==5)// находимся в 5 м интервале
    {

      next_intr_time = 60*23+60 ; // 1440 минут
    }


     //-----------------------------------------------------------------------------------------------------
           if(event_type == key_event_plus)
           {// minutes++;

               BUSY_KEY=1;

           if( next_intr_time- curent_intr_time>30)// разница в количестве минут более 30 , то можно сдвигать границу
           {                                //в сторону увеличения
             minutes++;

             if(minutes >59)// сброс кольца при переполнении час в случа +
             {
             minutes= 0;
             hours++;

             SCHED_3D[select_day_buf][curent_intr][Shed_ph]=hours;

             }

           }

           Task3_1=Reload_Task;//сбросили и перезагрузили  Task3_1
           ClockIcon;
           pack_minutes(minutes);
           screen_refresh_flag=1;
           invers_blynk_image_1S =255;
           }//обновление "час" по кнопке +

 //-------------------------------------------------------------------------------------------------------------

           if(event_type== key_event_minus)
           {// minutes--;

               BUSY_KEY=1;

           if(curent_intr_time<60)// если находимся в 0 м интервале
           {
           curent_intr_time = curent_intr_time + 1440; //00.00

           }else {

               if(curent_intr==0)// находимся в 0 м интервале
                  {
                  prev_intr_time = 0; //00.00
                  }
            }

           if(  curent_intr_time-prev_intr_time>30)// разница в количестве часов более 1 часа, то можно сдвигать границу
           {                                //в сторону уменьшения
           minutes--;


           if(minutes <0)// сброс кольца при переполнении час в случа +
                    {
                    minutes= 59;
                    hours--;

                    SCHED_3D[select_day_buf][curent_intr][Shed_ph]=hours;

                    }

           }

           Task3_1=Reload_Task;//сбросили и перезагрузили  Task3_1
           ClockIcon;
           pack_minutes(minutes);
           screen_refresh_flag=1;
           invers_blynk_image_1S =255;

           }


//--------------------------фоновое обновление(моргание) знакоместа "час" по состоянию измениея invers_image =  255 / 0


           if(BUSY_KEY==1)//как только нажали кнопку, то обнулили таймер обновления HLW8110
            {// и ждем пока он натикает через время Т после отпускания кнопки + 1сек
            invers_blynk_image_1S=255;
            }

           if(invers_blynk_image_1S==255 )
            {
            second_sep_on();
            pack_minutes(minutes);//   выводим фоново с учетом таймера моргания  "минуты"
            }
           else // если не разрешено моргание
            {
            second_sep_off();
            pack_minutes(non_min);//  тушим фоново  с учетом таймера моргания  "минуты"
            }

//--------------------------------------------------------------------------------------------------//
           if(event_type== key_long_mode_yes)   // в разделе "настройка минут" удерживаем MODE, то возвращаемся в
           // предыдущую настройку
            {
           prog_selected_day_menu_navigate--;
            }

           return  minutes;

}



s16 int_position(s16 N_interval, s8 interval_direction)//номер текущего интервала, и что возвращаем позицию следующего
{ // интервала в с лучае interval_direction == MAX (1) или предыдущего интервала  в с лучае interval_direction == MIN (0)



    if (interval_direction==1)
    {
        N_interval = N_interval + 1;

        if(N_interval >5)
        {
           N_interval = 0;
        }


    } else

    {

        N_interval = N_interval - 1;

        if(N_interval <0)
        {
           N_interval = 5;
        }

    }


  //  int_buf = N_interval;

 //  return int_buf;

    return N_interval;



}


//-------------------------------  COPY  DAY MENU ----------------------------------------

void copy_day_menu(void)
{
        LIGTH_ON;


        if(copy_day_menu_navigate==0)  //  заходим в  "COPY DAY" - отображение  дня "ИСТОЧНИКА КОПИРОВАНИЯ"
        { // статического изображения - маски нет в оригинале

         pack9876D_custom(( (SIGN_C << 24) | (SIGN_O << 16) | (SIGN_P << 8)| (SIGN_Y << 0) ) );
      //   pack123D_custom(((SIGN_d << 16) | (SIGN_A<< 8) | (SIGN_Y )));
         screen_refresh_flag=1;// флаг обновления єкрана

         if(invers_blynk_image_1S==255 )
          {
#ifndef SK3_LCD
            frame_5G_on();// зажигаем рамку
            pack_heap(selected_day);//
#else
            pack_day(selected_day);// высвечиваем выбранный день для малого экрана
#endif
          }
            else
          {
#ifndef SK3_LCD   // или не обновлем обьект 1 секунду до следующего цикла маоргания
            frame_5G_off();//тушим рамку
            pack_heap(selected_day);//
#else
          pack_day(~selected_day);// высвечиваем выбранный день для малого экрана
#endif
          }

 // ---------------ВЫБОР ДНЯ НЕДЕЛИ  "ИСТОЧНИКА КОПИРОВАНИЯ" ----------------------------------
            if(event_type == key_event_plus)//
            {copy_day_sourse++ ;
            BUSY_KEY=1;
            //screen_refresh_flag=1;
            //Task3_1=Reload_Task;//сбросили и перезагрузили  Task3_1
            }
            if(event_type== key_event_minus)
            {copy_day_sourse--;
            BUSY_KEY=1;
            //screen_refresh_flag=1;
            //Task3_1=Reload_Task;//сбросили и перезагрузили  Task3_1
            }
            if(copy_day_sourse >7)
            {copy_day_sourse= 1;
            }
            if(copy_day_sourse <1)
            {copy_day_sourse=7;
            }
            selected_day=copy_day_sourse;
//---------------------------------------------------------------------------------------------


        if(event_type== key_event_mode)// в подменю OUT  , при коротком нажатии MODE возвращаемся в предыдущее МЕНЮ
        {
        event_type=0;// !!! очистка флага до момента выбора следующего подменю

        copy_day_menu_navigate++; // переходим на следующее подменю настройки "ПРИЕМНИКА КОПИРОВАНИЯ"
        screen_refresh_flag=1;

        memcpy(Shedull_Copy_Pointer_1D, Shedull_Copy_Pointer[copy_day_sourse-1], sizeof(Shedull_Copy_Pointer_1D));


        }
        }


        if(copy_day_menu_navigate==1)  //  заходим в  "COPY DAY" - отображение  дня "ПРИЕМНИКА КОПИРОВАНИЯ"
        { // статического изображения - маски нет в оригинале

       // pack9876D_custom(( (SIGN_C << 24) | (SIGN_O << 16) | (SIGN_P << 8)| (SIGN_Y << 0) ) );
           screen_refresh_flag=1;// флаг обновления єкрана


    // ---------------ВЫБОР ДНЯ НЕДЕЛИ  "ПРИЕМНИКА КОПИРОВАНИЯ" ----------------------------------
     if(event_type == key_event_plus)//
       {copy_day_receiver++ ;
       BUSY_KEY=1;
       screen_refresh_flag=1;
       Task3_1=Reload_Task;//сбросили и перезагрузили  Task3_1
       }
     if(event_type== key_event_minus)
       {copy_day_receiver--;
       BUSY_KEY=1;
       screen_refresh_flag=1;
       Task3_1=Reload_Task;//сбросили и перезагрузили  Task3_1
       }

       if(copy_day_receiver >7)
       {copy_day_receiver= 1;}
       if(copy_day_receiver <1)
       {copy_day_receiver=7;}

       selected_day=copy_day_receiver;





//---------------------------------------------------------------------------------------------------//
/*
           if(invers_blynk_image_1S==255 )
                 {
       #ifndef SK3_LCD

       #else
                   pack123D_custom(((SIGN_o << 16) | (SIGN_n<< 8) ));
       #endif
                 }
                   else
                 {
       #ifndef SK3_LCD   // или не обновлем обьект 1 секунду до следующего цикла маоргания

       #else
                   pack123D_custom(((SIGN_o << 16) | (SIGN_n<< 8) ));
                   pack3d(get_symbol(selected_day));
       #endif
                 }
*/

       if(BUSY_KEY==1)//как только нажали кнопку, то обнулили таймер обновления HLW8110
            {// и ждем пока он натикает через время Т после отпускания кнопки + 1сек
            invers_blynk_image_1S=255;
            }

           if(invers_blynk_image_1S==255 )
            {
            pack123D_custom(((SIGN_o << 16) | (SIGN_n<< 8) ));
            pack3d(get_symbol(selected_day));
            }
           else // если не разрешено моргание
            {
            pack123D_custom(((SIGN_o << 16) | (SIGN_n<< 8) ));
            }

 //---------------------------------------------------------------------------------------------

        if(event_type== key_event_mode)// в подменю OUT  , при коротком нажатии MDE возвращаемся в предыдущее МЕНЮ
        {
        copy_day_menu_navigate =0; //сбрасываем указатель меню на 0
        screen_level = PROG_MENU;
        screen_refresh_flag=1;
        SCHEDULE_UPDATE=1;// при выходе из меню - пересохраняем РАСПИСАНИЕ в EEPROM
        pro_tune_menu_navigate=7; // сбрасываем в исходное положение указатель меню prog_level_7 - "COPY DAY"

       memcpy(Shedull_Copy_Pointer[copy_day_receiver-1], Shedull_Copy_Pointer_1D, sizeof(Shedull_Copy_Pointer[copy_day_receiver-1]));

       memcpy(SCHEDULE_RESERVE, Shedull_Copy_Pointer, sizeof(SCHEDULE_RESERVE));// копируем обратно в ОЗУ обновленный  3D массив
                    // в одномерній массив для дальнейшей перезаписи в EEPROM


        }
        }


}



void    service_menu(void)
{

    screen_refresh_flag=1;// флаг обновления єкрана
    LIGTH_ON;// включили подсветку


 //------------------------------------- АНАЛИЗИРУЕМ КНОПКИ----------------------------------
      if(event_type == key_event_plus)
          {service_menu_navigate =  service_menu_navigate + 1;BUSY_KEY=1;}
      if(event_type== key_event_minus)
          {service_menu_navigate=  service_menu_navigate - 1;BUSY_KEY=1;}
      if(service_menu_navigate >3)
         {service_menu_navigate= 0;}
      if(service_menu_navigate <0)
         {service_menu_navigate=3;}

 //--------------------------------------- ХОД ПО  КРУГОВОМУ МЕНЮ-----------------------------------
        if(service_menu_navigate==0) // если меню  "LOC"
        {
#ifndef  SK3_LCD
        LockIcon;
#else

#endif
        pack9876D_custom(( (0 << 24) | (SIGN_L << 16) | (SIGN_O << 8)| (SIGN_C << 0) ) );
        screen_refresh_flag=1;

        if(event_type== key_event_mode)// если одиночное нажатие MODE
        {
        screen_level = SERVICE_LOCK; screen_refresh_flag=1;// переходим в меню SERVICE_LOCK
        }

        }
//--------------------------------------------------------------------------------------------------
        if(service_menu_navigate==1) // если меню  "HYST"
           {
           Celsium_Icon; pack9876D_custom(( (SIGN_H << 24) | (SIGN_Y << 16) | (SIGN_S << 8)| (SIGN_t << 0) ) );
           screen_refresh_flag=1;

           if(event_type== key_event_mode)// если одиночное нажатие MODE
           {
           screen_level = SERVICE_HYST; screen_refresh_flag=1;// переходим в меню SERVICE_LOCK
           }

           }
//---------------------------------------------------------------------------------------------------
        if(service_menu_navigate==2) // если меню  "RES"
            {
            pack9876D_custom(( (0 << 24) | (SIGN_r << 16) | (SIGN_E << 8)| (SIGN_S << 0) ) );
            screen_refresh_flag=1;

            if(event_type== key_event_mode)// если одиночное нажатие MODE
            {
            screen_level = SERVICE_DEF; screen_refresh_flag=1;// переходим в меню SERVICE_LOCK
            }

            }

//---------------------------------------------------------------------------------------------------
        if(service_menu_navigate==3) // если меню  "OUT"
           {
            pack123D_custom(((SIGN_O << 16) | (SIGN_u << 8) | SIGN_t));
            screen_refresh_flag=1;

            if(event_type== key_event_mode)// если одиночное нажатие MODE
            {
             FLASH_UPDATE=1;// при выходе обновляем весь FLASH/EEPROM
             screen_level = CONTROL_MENU; screen_refresh_flag=1;// переходим в меню CONTROL_MENU
             }
           }




}



void    loc_entry(void)// вход в меню "LOC"
{

#ifndef  SK3_LCD
        LockIcon;
#else

#endif

    pack9876D_custom(( (0 << 24) | (SIGN_L << 16) | (SIGN_O << 8)| (SIGN_C << 0) ) );
    // LockIcon; pack9876D_custom(( (0 << 24) | (SIGN_t << 16) | (SIGN_u << 8)| (SIGN_n << 0) ) );
    screen_refresh_flag=1; // статическое изображение "LOC" + замок иконка

    if(event_type == key_event_plus)
     {LOC_on_off =LOC_on ;BUSY_KEY=1;// включам режим  блокировки клавиатуры
     }
    if(event_type== key_event_minus)
     {LOC_on_off =LOC_off;BUSY_KEY=1;// отключаем режим  блокировки клавиатуры
     }

    if(LOC_on_off==1)
    {
     pack123D_custom(((SIGN_O << 16) | (SIGN_n << 8) | 0));
     screen_refresh_flag=1;
    }else {
     pack123D_custom(((SIGN_O << 16) | (SIGN_F << 8) | SIGN_F));
     screen_refresh_flag=1;
    }

    if(event_type== key_event_mode)//подтверждение ИЗМЕНЕНИЯ  и обратный возврат в SERVICE MENU
      {
      screen_level = SERVICE_MENU;
      }



}


void    hysteresis_entry(void)
{
    Celsium_Icon;
    pack9876D_custom(( (SIGN_H << 24) | (SIGN_Y << 16) | (SIGN_S << 8)| (SIGN_t << 0) ) );
    //pack9876D_custom(( (0 << 24) | (SIGN_t << 16) | (SIGN_u << 8)| (SIGN_n << 0) ) );
    screen_refresh_flag=1; // статическое изображение "LOC" + замок иконка

 //---------------------------------------  анализ кнопок + и -  -------------------------------------------
    if(event_type == key_event_plus)
        {HystPrepere = HYST_10;BUSY_KEY=1;// включам блокировку клавиатуры
        }
       if(event_type== key_event_minus)
        {HystPrepere = HYST_05;BUSY_KEY=1;// отключаем  блокировку клавиатуры
        }

       if(HystPrepere == HYST_10)
       {
           pack_temperature123D(10);
        screen_refresh_flag=1;
       }else {
           pack_temperature123D(5);
        screen_refresh_flag=1;
       }


 //----------------------------------------------------------------------------------------------------
       if(event_type== key_event_mode)//подтверждение ИЗМЕНЕНИЯ  и обратный возврат в SERVICE MENU
           {
           screen_level = SERVICE_MENU;
           }


}





void default_entry(void)// вход в меню "RES"
{
    pack9876D_custom(( (0 << 24) | (SIGN_r << 16) | (SIGN_E << 8)| (SIGN_S << 0) ) );
   //LockIcon; pack9876D_custom(( (0 << 24) | (SIGN_t << 16) | (SIGN_u << 8)| (SIGN_n << 0) ) );
   screen_refresh_flag=1; // статическое изображение "LOC" + замок иконка


    if(event_type == key_event_plus)
     { device_default = TRUE;BUSY_KEY=1;// включам блокировку клавиатуры
     }
    if(event_type== key_event_minus)
     { device_default = FALSE;BUSY_KEY=1;// отключаем  блокировку клавиатуры
     }

    if(device_default == TRUE)
    {
     pack123D_custom(((SIGN_O << 16) | (SIGN_n << 8) | 0));
     screen_refresh_flag=1;
    }else {
     pack123D_custom(((SIGN_O << 16) | (SIGN_F << 8) | SIGN_F));
     screen_refresh_flag=1;
    }

    if(event_type== key_event_mode)//подтверждение ИЗМЕНЕНИЯ  и обратный возврат в SERVICE MENU
      {
      screen_level = SERVICE_MENU;
      }




}




void TEST_Task(void)
{

    tmos_start_reload_task( task3 , sub_event_1 ,1.6*1.0* start_task_delay);


}






