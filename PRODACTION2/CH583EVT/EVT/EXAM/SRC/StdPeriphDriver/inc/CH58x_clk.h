/********************************** (C) COPYRIGHT *******************************
 * File Name          : CH57x_clk.h
 * Author             : WCH
 * Version            : V1.2
 * Date               : 2021/11/17
 * Description
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for 
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

#ifndef __CH58x_CLK_H__
#define __CH58x_CLK_H__

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief  ПµНіЦчЖµ¶ЁТе
 */
typedef enum
{
    CLK_SOURCE_LSI = 0x00,
    CLK_SOURCE_LSE,

    CLK_SOURCE_HSE_16MHz = 0x22,
    CLK_SOURCE_HSE_8MHz = 0x24,
    CLK_SOURCE_HSE_6_4MHz = 0x25,
    CLK_SOURCE_HSE_4MHz = 0x28,
    CLK_SOURCE_HSE_2MHz = (0x20 | 16),
    CLK_SOURCE_HSE_1MHz = (0x20 | 0),

    CLK_SOURCE_PLL_80MHz = 0x46,
    CLK_SOURCE_PLL_60MHz = 0x48,
    CLK_SOURCE_PLL_48MHz = (0x40 | 10),
    CLK_SOURCE_PLL_40MHz = (0x40 | 12),
    CLK_SOURCE_PLL_36_9MHz = (0x40 | 13),
    CLK_SOURCE_PLL_32MHz = (0x40 | 15),
    CLK_SOURCE_PLL_30MHz = (0x40 | 16),
    CLK_SOURCE_PLL_24MHz = (0x40 | 20),
    CLK_SOURCE_PLL_20MHz = (0x40 | 24),
    CLK_SOURCE_PLL_15MHz = (0x40 | 0),
} SYS_CLKTypeDef;

/**
 * @brief  32KК±ЦУСЎФс
 */
typedef enum
{
    Clk32K_LSI = 0,
    Clk32K_LSE,

} LClk32KTypeDef;

/**
 * @brief  32Mѕ§ХсµзБчµІО»
 */
typedef enum
{
    HSE_RCur_75 = 0,
    HSE_RCur_100,
    HSE_RCur_125,
    HSE_RCur_150

} HSECurrentTypeDef;

/**
 * @brief  32Mѕ§ХсДЪІїµзИЭµІО»
 */
typedef enum
{
    HSECap_10p = 0,
    HSECap_12p,
    HSECap_14p,
    HSECap_16p,
    HSECap_18p,
    HSECap_20p,
    HSECap_22p,
    HSECap_24p

} HSECapTypeDef;

/**
 * @brief  32Kѕ§ХсµзБчµІО»
 */
typedef enum
{
    LSE_RCur_70 = 0,
    LSE_RCur_100,
    LSE_RCur_140,
    LSE_RCur_200

} LSECurrentTypeDef;

/**
 * @brief  32Kѕ§ХсДЪІїµзИЭµІО»
 */
typedef enum
{
    LSECap_2p = 0,
    LSECap_13p,
    LSECap_14p,
    LSECap_15p,
    LSECap_16p,
    LSECap_17p,
    LSECap_18p,
    LSECap_19p,
    LSECap_20p,
    LSECap_21p,
    LSECap_22p,
    LSECap_23p,
    LSECap_24p,
    LSECap_25p,
    LSECap_26p,
    LSECap_27p

} LSECapTypeDef;

#define MAX_DAY                   0x00004000
#define MAX_2_SEC                 0x0000A8C0
//#define	 MAX_SEC		0x545FFFFF

#define BEGYEAR                   2020
#define IsLeapYear(yr)            (!((yr) % 400) || (((yr) % 100) && !((yr) % 4)))
#define YearLength(yr)            (IsLeapYear(yr) ? 366 : 365)
#define monthLength(lpyr, mon)    (((mon) == 1) ? (28 + (lpyr)) : (((mon) > 6) ? (((mon) & 1) ? 31 : 30) : (((mon) & 1) ? 30 : 31)))

/**
 * @brief  rtc timer mode period define
 */
typedef enum
{
    Period_0_125_S = 0, // 0.125s ЦЬЖЪ
    Period_0_25_S,      // 0.25s ЦЬЖЪ
    Period_0_5_S,       // 0.5s ЦЬЖЪ
    Period_1_S,         // 1s ЦЬЖЪ
    Period_2_S,         // 2s ЦЬЖЪ
    Period_4_S,         // 4s ЦЬЖЪ
    Period_8_S,         // 8s ЦЬЖЪ
    Period_16_S,        // 16s ЦЬЖЪ
} RTC_TMRCycTypeDef;

/**
 * @brief  rtc interrupt event define
 */
typedef enum
{
    RTC_TRIG_EVENT = 0, // RTC ґҐ·ўКВјю
    RTC_TMR_EVENT,      // RTC ЦЬЖЪ¶ЁК±КВјю

} RTC_EVENTTypeDef;

/**
 * @brief  rtc interrupt event define
 */
typedef enum
{
    RTC_TRIG_MODE = 0, // RTC ґҐ·ўДЈКЅ
    RTC_TMR_MODE,      // RTC ЦЬЖЪ¶ЁК±ДЈКЅ

} RTC_MODETypeDef;

typedef enum
{
    /* РЈЧјѕ«¶ИФЅёЯЈ¬єДК±ФЅі¤ */
    Level_32 = 3, // УГК± 1.2ms 1000ppm (32M ЦчЖµ)  1100ppm (60M ЦчЖµ)
    Level_64,     // УГК± 2.2ms 800ppm  (32M ЦчЖµ)  1000ppm (60M ЦчЖµ)
    Level_128,    // УГК± 4.2ms 600ppm  (32M ЦчЖµ)  800ppm  (60M ЦчЖµ)

} Cali_LevelTypeDef;

/**
 * @brief   32K µНЖµК±ЦУАґФґ
 *
 * @param   hc  - СЎФс32KК№УГДЪІї»№КЗНвІї
 */
void LClk32K_Select(LClk32KTypeDef hc);

/**
 * @brief   HSEѕ§Ме Ж«ЦГµзБчЕдЦГ
 *
 * @param   c   - 75%,100%,125%,150%
 */
void HSECFG_Current(HSECurrentTypeDef c);

/**
 * @brief   HSEѕ§Ме ёєФШµзИЭЕдЦГ
 *
 * @param   c   - refer to HSECapTypeDef
 */
void HSECFG_Capacitance(HSECapTypeDef c);

/**
 * @brief   LSEѕ§Ме Ж«ЦГµзБчЕдЦГ
 *
 * @param   c   - 70%,100%,140%,200%
 */
void LSECFG_Current(LSECurrentTypeDef c);

/**
 * @brief   LSEѕ§Ме ёєФШµзИЭЕдЦГ
 *
 * @param   c   - refer to LSECapTypeDef
 */
void LSECFG_Capacitance(LSECapTypeDef c);

void Calibration_LSI(Cali_LevelTypeDef cali_Lv); /* УГЦчЖµРЈЧјДЪІї32KК±ЦУ */

/**
 * @brief   RTCК±ЦУіхКј»Їµ±З°К±јд
 *
 * @param   y       - ЕдЦГДкЈ¬MAX_Y = BEGYEAR + 44
 * @param   mon     - ЕдЦГФВЈ¬MAX_MON = 12
 * @param   d       - ЕдЦГИХЈ¬MAX_D = 31
 * @param   h       - ЕдЦГРЎК±Ј¬MAX_H = 23
 * @param   m       - ЕдЦГ·ЦЦУЈ¬MAX_M = 59
 * @param   s       - ЕдЦГГлЈ¬MAX_S = 59
 */
void RTC_InitTime(uint16_t y, uint16_t mon, uint16_t d, uint16_t h, uint16_t m, uint16_t s);

/**
 * @brief   »сИЎµ±З°К±јд
 *
 * @param   py      - »сИЎµЅµДДкЈ¬MAX_Y = BEGYEAR + 44
 * @param   pmon    - »сИЎµЅµДФВЈ¬MAX_MON = 12
 * @param   pd      - »сИЎµЅµДИХЈ¬MAX_D = 31
 * @param   ph      - »сИЎµЅµДРЎК±Ј¬MAX_H = 23
 * @param   pm      - »сИЎµЅµД·ЦЦУЈ¬MAX_M = 59
 * @param   ps      - »сИЎµЅµДГлЈ¬MAX_S = 59
 */
void RTC_GetTime(uint16_t *py, uint16_t *pmon, uint16_t *pd, uint16_t *ph, uint16_t *pm, uint16_t *ps);

/**
 * @brief   »щУЪLSE/LSIК±ЦУЈ¬ЕдЦГµ±З°RTC ЦЬЖЪКэ
 *
 * @param   cyc     - ЕдЦГЦЬЖЪјЖКэіхЦµЈ¬MAX_CYC = 0xA8BFFFFF = 2831155199
 */
void RTC_SetCycle32k(uint32_t cyc);

/**
 * @brief   »щУЪLSE/LSIК±ЦУЈ¬»сИЎµ±З°RTC ЦЬЖЪКэ
 *
 * @return  µ±З°ЦЬЖЪКэЈ¬MAX_CYC = 0xA8BFFFFF = 2831155199
 */
uint32_t RTC_GetCycle32k(void);

/**
 * @brief   RTC¶ЁК±ДЈКЅЕдЦГЈЁЧўТв¶ЁК±»щЧј№М¶ЁОЄ32768HzЈ©
 *
 * @param   t   - refer to RTC_TMRCycTypeDef
 */
void RTC_TRIGFunCfg(uint32_t cyc);

/**
 * @brief   RTC¶ЁК±ДЈКЅЕдЦГЈЁЧўТв¶ЁК±»щЧј№М¶ЁОЄ32768HzЈ©
 *
 * @param   t   - refer to RTC_TMRCycTypeDef
 */
void RTC_TMRFunCfg(RTC_TMRCycTypeDef t);

/**
 * @brief   RTC ДЈКЅ№¦ДЬ№Ш±Х
 *
 * @param   m   - РиТЄ№Ш±ХµДµ±З°ДЈКЅ
 */
void RTC_ModeFunDisable(RTC_MODETypeDef m);

/**
 * @brief   »сИЎRTCЦР¶П±кЦѕ
 *
 * @param   f   - refer to RTC_EVENTTypeDef
 *
 * @return  ЦР¶П±кЦѕЧґМ¬
 */
uint8_t RTC_GetITFlag(RTC_EVENTTypeDef f);

/**
 * @brief   ЗеіэRTCЦР¶П±кЦѕ
 *
 * @param   f   - refer to RTC_EVENTTypeDef
 */
void RTC_ClearITFlag(RTC_EVENTTypeDef f);

#ifdef __cplusplus
}
#endif

#endif // __CH58x_CLK_H__
