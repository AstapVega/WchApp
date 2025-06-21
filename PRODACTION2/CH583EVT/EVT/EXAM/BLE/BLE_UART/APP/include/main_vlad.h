#ifndef __MAIN_VLAD_H
#define __MAIN_VLAD_H

#include "my_assist32.h"


/*

//------------define  my constants
#define IWDG_RELOAD_VALUE	0x0fff
#define MY_PRIORIRY		0xf0UL		//lowest
#define PGROUPS16_PSUBG0	((u32)0x300)	//16 groups subpriority 0, already alligned
//------------define  system constants
#define IWDG_KEY_ENABLE		0xCCCC
#define IWDG_KEY_RESET		0xAAAA
#define IWDG_KEY_ACSESS		0x5555
#define AIRCR_VECTKEY_MASK    ((u32)0x05FA0000)

#define	AHB_CLK_HZ			8000000L	//1 mhz
#define	VTIMER_PSC_CLK_HZ		100000L		//100khz
#define VTIMER_PSC_VALUE		((AHB_CLK_HZ/VTIMER_PSC_CLK_HZ)-1)
#define	VTIMER_PSC_CLK_MKS		(1000000L/VTIMER_PSC_CLK_HZ)
#define VTIMER_TICK_MKS			1000L		//1ms tick
#define VTIMER_ARR_VALUE		((VTIMER_TICK_MKS/VTIMER_PSC_CLK_MKS)-1)


#define TIME1s			(1000000L/VTIMER_TICK_MKS)		//in ticks
#define TIME2s			TIME1s*2
#define TIME5s			TIME1s*5
#define TIME3s			TIME1s*3
#define TIME10s			TIME1s*10
#define TIME3M			((s32)TIME1s*180)
#define TIME2_5S		((TIME1s*25)/10)
#define TIME50MS		(1000*50/VTIMER_TICK_MKS)		//
#define TIME100MS		(1000*100/VTIMER_TICK_MKS)		//
#define TIME200MS		(1000*200/VTIMER_TICK_MKS)		//
#define TIME_BLINK_OFF		(1000*700/VTIMER_TICK_MKS)		//700ms
#define TIME_BLINK_ON		(1000*900/VTIMER_TICK_MKS)		//900ms

#define	SHORT_BUTTON_TIME_MKS	 225000L				//300ms its for holding case
#define	SHORT1_BUTTON_TIME_MKS	 30000L					//40ms its for release case
#define LONG_BUTTON_TIME_MKS	1500000L				//1000 ms
#define SHORTPRESS	(SHORT_BUTTON_TIME_MKS/VTIMER_TICK_MKS)
#define SHORTPRESS2	(SHORT1_BUTTON_TIME_MKS/VTIMER_TICK_MKS)
#define LONGPRESS	(LONG_BUTTON_TIME_MKS/VTIMER_TICK_MKS)	//1.5 second	
#define INTEG_LIMIT		0x1000					//some  limit for button			
//------------------------------menu limits/values
#define CONTROL_MAX		2L		// control menu has 3 entries
#define CONTROL_MIN		0L
#define CONTROL_HANDLE_ENTRY	0L
#define CONTROL_PROG_ENTRY	1L
#define CONTROL_TIME_ENTRY	2L	

//---------------------------
#define LOCK_ENTRY		          0L
#define PWM_ENTRY			          1L
#define HYST_ENTRY              2L
#define HILO_ENTRY              3L
#define SERVICE_TIME_ENTRY	    4L
#define SERVICE_ECONOMY_ENTRY1	5L
#define SERVICE_ECONOMY_ENTRY2	6L
#define SERVICE_DEFAULT       	7L
#define SERVICE_OUT_ENTRY	      8L

#define SERVICE_MAX		8L		// control menu has 9 entries
#define SERVICE_MIN		0L
//-----------------------------------

#define TIME_NAVIGATOR_HOUR	0x00000001
#define TIME_NAVIGATOR_MINUTE	0x00000002
#define TIME_NAVIGATOR_YEAR	0x00000004
#define TIME_NAVIGATOR_MONTH	0x00000008
#define TIME_NAVIGATOR_DATE	0x00000010
#define TIME_NAVIGATOR_END	0x00000020

//---------------------PWM  in miliseconds/percents
//#define PWMPERIOD				3600000L  //60min
//#define PWMUNIT					36000L			//1% in seconds
#define PWMPERIOD				2700000L  //45min
#define PWMUNIT 				60000L    //1min
//------------------backup
#define	BKP_POINTER_LAST	18L
#define	BKP_DATE_LAST		17L
#define	BKP_PERCENTAGE		16L
#define DAY_MIN			0L
#define DAY_MAX			15L

#define MONTH_MIN		0L
#define MONTH_MAX		11L
#define YEAR_MASK		0xf000
#define MONTH_MASK		0x0f00
#define PERCENTAGE		0x00ff
#define	PERCENTAGE2		0x007f
#define HALF_MONTH		0x0080

#define DAY_MINUTES_MIN		0L
#define DAY_MINUTES_MAX		1439L		//(24*60-1)=1440-1
#define WEEK_DAY_MIN		0L
#define WEEK_DAY_MAX		6L


#define PROG_SEQ_HOUR		0x00000001	//
#define PROG_SEQ_MINUTE		0x00000002	//
#define PROG_SEQ_TEMP		0x00000004	//
#define PROG_SEQ_MASK_END	0x00000008

#define	DAY_INTERVALS		6L		//6 intervals total
#define INTERVAL_MAX	(DAY_INTERVALS-1)
#define INTERVAL_MIN		0L

#define	HOUR_MAX		23L
#define	HOUR_MIN		0L
#define	MINUTE_MAX		59L
#define	MINUTE_MIN		0L

#define	HOUSES_ALL_ON		6
//---------------------------defination of menu
#define		MAIN_SCREEN		     0
#define		PROG_MENU		     1
#define		TIME_MENU		     2
#define		PROG_DAY_SEQ         3
#define		CONTROL_MENU		 4
#define		STANDBY_MODE		 5
#define		SERVICE_MENU		 6
#define		SERVICE_ECO1		 7
#define		SERVICE_TIME		 8
#define		SERVICE_ECO2		 9
#define   SERVICE_LOCK          10
#define   SERVICE_DEF           11
#define   SERVICE_PWM           12
#define   SERVICE_HYST          13
#define   SERVICE_HILO          14
#define   HILO_MENU				15
//---------------------------defination of hardware
#define OUT0_high
#define OUT0_low
#define CHECK_OUT
#define OUT0_TGL

#define BACKLED_ON
#define BACKLED_OFF
#define CHECK_BLED

#define OUT_MASK	(p0|p1)
//---------------debug
/*#define LED_PC8ON    GPIOC->ODR|=p8
#define LED_PC8OFF   GPIOC->ODR&=~p8
#define LED_PC8TGL   GPIOC->ODR^=p8

#define LED_PC9ON    GPIOC->ODR|=p9
#define LED_PC9OFF   GPIOC->ODR&=~p9
#define LED_PC9TGL   GPIOC->ODR^=p9



//-------------------defination in config bitpattern register
#define		CONTROL						0x0001
#define		TIME_TEMP_SHOW		0x0002
#define		STATE_OFF		      0x0004
#define		LOCK_FEATURE		  0x0008 
//#define		ADAPTIVE		      0x0010
#define		PWM		            0x0020 

#define		STATE_ON		0x0000

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
#define		RTC_FAILED		  0x00000001
#define		FLASH_DEFAULT		0x00000002
#define		INTRO_EVENT		  0x00000004	//means menu was changed and new menu "intro event"
#define		OVERRIDE		    0x00000008	//this need for "comfort"
#define		UP_DOWN_TOUCH		0x00000010	//was "+" ,"-" activity
#define		TAMPERSET   		0x00000020	//1- auto, 0-handle
#define		ADC_NOTREADY		0x00000040	//1- adc ready
#define		BLINK			      0x00000080
#define		LOCK_STATE			0x00000100
#define		SAVE_FLASH		  0x00000200
#define		RECOVERY		    0x00000400
#define		UP_DOWN_TOUCH2	0x00000800	//was "+" ,"-" activity
#define		LOCK_WINDOW			0x00001000
#define   PWMFIRE					0x00002000
#define   HOTOCCUR				0x00004000
#define   INITDAYEDIT			0x00008000
#define   DAYCOPY				  0x00010000
#define   DEFAULT_BIT     0x00020000   //used in default entry (service menu)
#define   ANIME           0x00040000
#define   KEYACTIVITY			0x00080000
#define   RESETHOT				0x00100000
#define   OUTBUFFER				0x00200000
#define   LAGRELAY				0x00400000
#define   BACKLIGHTBIT		0x00800000
#define   BACKLOCK        0x01000000
//------------------------
#define BACKLIGHT_ON   flags|=BACKLIGHTBIT
#define BACKLIGHT_OFF  flags&=~BACKLIGHTBIT	
#define CHECK_BL       flags&BACKLIGHTBIT
//---------------------
#define   RATEMINHOUR     0.1				//celisium in hour
#define   RATEMAXHOUR     10.0      //celisium in hour
#define   RATEMIN  (RATEMINHOUR/6.0)  // rate in min *10, cause of temp*10 representation 
#define   RATEMAX  (RATEMAXHOUR/6.0)
//----------------------


//--------------globals


//--------------globals
extern u32  flags;
extern s16  parameters[];
extern int  current_interval;
extern int	setup_temp;
extern int	override_temp;
extern int  cur_set_temp;
extern int	edit[];
extern s16  v_timer_save;
extern s16  pwmhold;
extern s16  pwmlast;
extern s32  pwmtimer;

/*
//--------------exported functions
void	save_on_off(u16);
int   is_select(void);
int  	is_OK_LH(void);				//checks if was "ok" long shot,exlusive operation
int  	is_OK_SH(void);				//checks if was "ok" short shot,exlusive operation
int  	is_BK_LH(void);				//checks if was "ok" long shot,exlusive operation
int  	is_BK_SH(void);				//checks if was "ok" short shot,exlusive operation
void  is_change(int*, int, int);
void  is_change2(int*, int, int);
void  loop_ch(int*, int, int);
void  pwm_ch(void);
void  exlusive_behavior(void);
void 	make_out(int);
void  setactivity(void);
s16	  restore_control(u16);
s16	  restore_handle_temp(void);
void	check_set_separator(void);
void	parametr_save(s16, s16);
void	toggle_control_bit(s16);
char 	read_backup(int);
void	merge_interval_time(int, int);				//for edit
void	split_interval_time(int, int);				//for edit
int	  get_interval_time(int, int);			       // gives interval daytime minutes
int	  get_interval_temp(int, int);			       // gives interval temperature
void	set_interval_time(int, int, int);			       // sets interval daytime minutes
void	set_interval_temp(int, int, int);			       // sets interval temperature
void	check_control_change(void);
void  make_anime(s16);
void  backlightoff(void);
*/

/*

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

*/

#endif				







