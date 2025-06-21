#ifndef __MENU_VLAD_H
#define __MENU_VLAD_H



extern void	main_menu(void);
extern void	service_menu(void);

extern void	prog_menu(void);
extern void prog_selected_day(void);
extern void    copy_day_menu(void);
extern uint8 main_screen_type ;// §ä§Ú§á §ï§Ü§â§Ñ§ß§Ñ
extern uint8 set_date_clock ; // §Õ§Ñ§ä§Ñ/§Ó§â§Ö§Þ§ñ §å§ã§ä§Ñ§ß§à§Ó§Ý§Ö§ß§í §Ú§Ý§Ú §ß§Ö§ä

//--------------------------------- FOR SFM  §â§Ö§Ø§Ú§Þ§Ñ ------------------------------------------------
#define SFM_default_time   25

#define  dead_time    5 // §Ù§ß§Ñ§é§Ö§ß§Ú§Ö §Ó§â§Ö§Þ§Ö§ß§Ú  §á§à§ã§ä§à§ñ§ß§ß§à§Ô§à §à§ä§Õ§í§ç§Ñ §Õ§Ý§ñ SFM
#define  active_time_max    40
extern int16 sfm_min;
extern int16 start_sfm_timer1,start_sfm_timer2;
extern int16 active_time ,active_time_evnt; //(§Þ§Ú§ß§Ú§Þ§Ñ§Ý§î§ß§à§Ö §â§Ñ§Ò§à§é§Ö§Ö §Ó§â§Ö§Þ§ñ §á§à §å§Þ§à§Ý§é§Ñ§ß§Ú§ð) ( §Ù§Ñ§Ò§â§Ñ§ã§í§Ó§Ñ§Ö§Þ §ä§å§Õ§Ñ §Ù§ß§Ñ§é§Ö§ß§Ú§ñ §ä§Ö§Þ§á§Ö§â§Ñ§ä§å§â§í)
extern int16 sfm_sek_active,sfm_sek_relax;
extern int16 relax_time , relax_time_evnt ;
extern int16 relax_buf ;
extern int16 active_buf;

extern uint8_t LOCK_PRINT_OUT ;// §æ§Ý§Ñ§Ô §ß§Ö§Ø§Ö§Ý§Ñ§ä§Ö§Ý§î§ß§à§Ô§à §Ó§í§Ó§à§Õ§Ñ §Ú§ß§æ§í §ß§Ñ §á§Ö§é§Ñ§ä§î §Ó §ã§å§Ò§è§Ú§Ü§Ý§Ö §Õ§Ý§ñ timersfm

extern int16  minutes_tm_1 ,minutes_tm_2; // 255 min - MAX
//extern int8 sfm_min_dec, sfm_min_unit,relax_time_dec,relax_time_unit;

//------------------------------ §Õ§Ý§ñ §â§Ö§Ø§Ú§Þ §¢§­§°§¬§ª§²§°§£§¬§ª LOC ----------------------------------------
extern  uint8  start_lock_anime_timer ;
extern  uint8  lock_anime_timer ;

//--------------------------------------------------------------------------------------------------
#define main_screen_manual    0
#define main_screen_prog      1
#define main_screen_SFM       2

extern int16 dss ;// §ã§Þ§Ö§ê§Ö§ß§Ú§Ö §Ó §ä§Ñ§Ò§Ý§Ú§è§Ö  §â§Ñ§ã§á§Ú§ã§Ñ§ß§Ú§ñ §ã §å§é§Ö§ä§à§Þ §Ó§í§Ò§â§Ñ§ß§ß§à§Ô§à  §¥§¯§Á §¯§¦§¥§¦§­§ª
extern int16 select_day_buf ;
extern u16 shudle_setup_t,shudle_hours,shudle_minute;

//---------------------------------§Õ§Ý§ñ §Ô§Ý§Ñ§Ó§ß§à§Ô§à §ï§Ü§â§Ñ§ß§Ñ---------------------------------------------
extern s16 temp ;
extern float Tout_to_int;//§Ó§ã§á§à§Þ§à§Ô§Ñ§ä§Ö§Ý§î§ß§Ñ§ñ §Ò§å§æ§Ö§â§ß§Ñ§ñ §á§Ö§â§Ö§Þ§Ö§ß§ß§Ñ§ñ §Õ§Ý§ñ §Ü§à§â§Ö§Ü§ä§ß§à§Ô§à §á§â§Ö§à§Ò§â§Ñ§Ù§à§Ó§Ñ§ß§Ú§ñ  float T §Ó int T
extern s16 intr_time_N ,curent_intr ,curent_sys_time ,curent_intr_time ,prev_intr_time ,next_intr_time;
extern s16 int_buf;
extern s16 total_time1,total_time2,minut_debug, hours_debug;
#define next_int      1  // §Õ§Ý§ñ §æ§å§ß§Ü§è§Ú§Ú int_position
#define prev_int      0  // §Õ§Ý§ñ §æ§å§ß§Ü§è§Ú§Ú int_position
//-------------------------------------------------------------------------------------------------

extern void	  time_menu(void);
extern int16  set_blynk_hours(int16 hours,int16 minutes);
extern int16  set_blynk_minutes(int16 minutes,int16 hours);
extern int16  set_shedule_tempere(int16 tempere);
extern int16  set_shedule_hours(int16 hours,int16 minutes);
extern int16  set_shedule_minutes(int16 minutes,int16 hours);
extern s16 int_position(s16 N_interval, s8 interval_direction);
extern void   SFM_mode_timer(void);
extern void	control_menu(void);
extern void    loc_entry(void);
extern void    hysteresis_entry(void);
extern void    default_entry(void);

extern void TEST_Task(void);

//-----------------
extern s16 heatsigntimer;

#endif				







