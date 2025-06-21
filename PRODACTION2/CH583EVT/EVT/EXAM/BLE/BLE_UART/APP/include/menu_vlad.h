#ifndef __MENU_VLAD_H
#define __MENU_VLAD_H



extern void	main_menu(void);
extern void	service_menu(void);

extern void	prog_menu(void);
extern void prog_selected_day(void);
extern void    copy_day_menu(void);
extern uint8 main_screen_type ;// ��ڧ� ��ܧ�ѧߧ�
extern uint8 set_date_clock ; // �էѧ��/�ӧ�֧ާ� ����ѧߧ�ӧݧ֧ߧ� �ڧݧ� �ߧ֧�

//--------------------------------- FOR SFM  ��֧اڧާ� ------------------------------------------------
#define SFM_default_time   25

#define  dead_time    5 // �٧ߧѧ�֧ߧڧ� �ӧ�֧ާ֧ߧ�  �������ߧߧ�ԧ� ���է��� �էݧ� SFM
#define  active_time_max    40
extern int16 sfm_min;
extern int16 start_sfm_timer1,start_sfm_timer2;
extern int16 active_time ,active_time_evnt; //(�ާڧߧڧާѧݧ�ߧ�� ��ѧҧ��֧� �ӧ�֧ާ� ��� ��ާ�ݧ�ѧߧڧ�) ( �٧ѧҧ�ѧ��ӧѧ֧� ���է� �٧ߧѧ�֧ߧڧ� ��֧ާ�֧�ѧ����)
extern int16 sfm_sek_active,sfm_sek_relax;
extern int16 relax_time , relax_time_evnt ;
extern int16 relax_buf ;
extern int16 active_buf;

extern uint8_t LOCK_PRINT_OUT ;// ��ݧѧ� �ߧ֧ا֧ݧѧ�֧ݧ�ߧ�ԧ� �ӧ�ӧ�է� �ڧߧ�� �ߧ� ��֧�ѧ�� �� ���ҧ�ڧܧݧ� �էݧ� timersfm

extern int16  minutes_tm_1 ,minutes_tm_2; // 255 min - MAX
//extern int8 sfm_min_dec, sfm_min_unit,relax_time_dec,relax_time_unit;

//------------------------------ �էݧ� ��֧اڧ� �������������������� LOC ----------------------------------------
extern  uint8  start_lock_anime_timer ;
extern  uint8  lock_anime_timer ;

//--------------------------------------------------------------------------------------------------
#define main_screen_manual    0
#define main_screen_prog      1
#define main_screen_SFM       2

extern int16 dss ;// ��ާ֧�֧ߧڧ� �� ��ѧҧݧڧ��  ��ѧ��ڧ�ѧߧڧ� �� ���֧��� �ӧ�ҧ�ѧߧߧ�ԧ�  ������ ������������
extern int16 select_day_buf ;
extern u16 shudle_setup_t,shudle_hours,shudle_minute;

//---------------------------------�էݧ� �ԧݧѧӧߧ�ԧ� ��ܧ�ѧߧ�---------------------------------------------
extern s16 temp ;
extern float Tout_to_int;//�ӧ���ާ�ԧѧ�֧ݧ�ߧѧ� �ҧ��֧�ߧѧ� ��֧�֧ާ֧ߧߧѧ� �էݧ� �ܧ��֧ܧ�ߧ�ԧ� ���֧�ҧ�ѧ٧�ӧѧߧڧ�  float T �� int T
extern s16 intr_time_N ,curent_intr ,curent_sys_time ,curent_intr_time ,prev_intr_time ,next_intr_time;
extern s16 int_buf;
extern s16 total_time1,total_time2,minut_debug, hours_debug;
#define next_int      1  // �էݧ� ���ߧܧ�ڧ� int_position
#define prev_int      0  // �էݧ� ���ߧܧ�ڧ� int_position
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







