#ifndef __MY_ASSIST_H
#define __MY_ASSIST_H



#include "stdint.h"

/*!< STM8 Standard Peripheral Library old types (maintained for legacy purpose) */


typedef int32_t  s32;
typedef int16_t s16;
typedef int8_t  s8;

typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;


/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef signed long  s32;
typedef signed short s16;
typedef signed char  s8;

typedef signed long  const sc32;  /* Read Only */
typedef signed short const sc16;  /* Read Only */
typedef signed char  const sc8;   /* Read Only */

typedef volatile signed long  vs32;
typedef volatile signed short vs16;
typedef volatile signed char  vs8;

typedef volatile signed long  const vsc32;  /* Read Only */
typedef volatile signed short const vsc16;  /* Read Only */
typedef volatile signed char  const vsc8;   /* Read Only */

typedef unsigned long  u32;
typedef unsigned short u16;
typedef unsigned char  u8;

typedef unsigned long  const uc32;  /* Read Only */
typedef unsigned short const uc16;  /* Read Only */
typedef unsigned char  const uc8;   /* Read Only */

typedef volatile unsigned long  vu32;
typedef volatile unsigned short vu16;
typedef volatile unsigned char  vu8;

typedef volatile unsigned long  const vuc32;  /* Read Only */
typedef volatile unsigned short const vuc16;  /* Read Only */
typedef volatile unsigned char  const vuc8;   /* Read Only */

#define U8_MAX     ((u8)255)
#define S8_MAX     ((s8)127)
#define S8_MIN     ((s8)-128)
#define U16_MAX    ((u16)65535u)
#define S16_MAX    ((s16)32767)
#define S16_MIN    ((s16)-32768)
#define U32_MAX    ((u32)4294967295uL)
#define S32_MAX    ((s32)2147483647)
#define S32_MIN    ((s32)-2147483648)

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */


////typedef enum {FALSE = 0, TRUE = !FALSE} bool;

//typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus, BitStatus, BitAction;

//typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;
//#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))

//typedef enum {ERROR = 0, SUCCES = !ERROR} ErrorStatus;





/******************************************************************************/
/*                         Peripheral memory map                              */
/******************************************************************************/
// pin in gpio
#define p0           ((u32)0x00000001)
#define p1           ((u32)0x00000002)
#define p2           ((u32)0x00000004)
#define p3           ((u32)0x00000008)
#define p4           ((u32)0x00000010)
#define p5           ((u32)0x00000020)
#define p6           ((u32)0x00000040)
#define p7           ((u32)0x00000080)
#define p8           ((u32)0x00000100)
#define p9           ((u32)0x00000200)
#define p10          ((u32)0x00000400)
#define p11          ((u32)0x00000800)
#define p12          ((u32)0x00001000)
#define p13          ((u32)0x00002000)
#define p14          ((u32)0x00004000)
#define p15          ((u32)0x00008000)
#define p16          ((u32)0x00010000)
#define p17          ((u32)0x00020000)
#define p18          ((u32)0x00040000)
#define p19          ((u32)0x00080000)
#define p20          ((u32)0x00100000)
#define p21          ((u32)0x00200000)
#define p22          ((u32)0x00400000)
#define p23          ((u32)0x00800000)





/* Exported macro ------------------------------------------------------------*/
#define SET_BIT(REG, BIT)     ((REG) |= (BIT))
#define setbit(REG, BIT)      ((REG) |= (BIT))

#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))
#define resetbit(REG, BIT)    ((REG) &= ~(BIT))

#define READ_BIT(REG, BIT)    ((REG) & (BIT))

#define CLEAR_REG(REG)        ((REG) = 0x0)

#define WRITE_REG(REG, VAL)   ((REG) = VAL)

#define READ_REG(REG)         ((REG))

#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~CLEARMASK)) | (SETMASK)))












#endif /* __MY_ASSIST_H */
