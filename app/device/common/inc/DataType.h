/**
*****************************************************************************
* @brief
*
* @file   DataType.h
* @author AE/FAE team
* @date   2021-11-11
*****************************************************************************
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
* TIME. AS A RESULT, TINYCHIP SHALL NOT BE HELD LIABLE FOR ANY
* DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
* FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
* CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*
* Copyright (c) 2021 Tinychip Microelectronics Co.,Ltd.
*
*****************************************************************************
*/

#ifndef _GENERAL_DATA_TYPE_
#define _GENERAL_DATA_TYPE_

#include "stdint.h"


//========================================= Marco Defination =========================================

#ifndef TRUE
#define TRUE  1
#endif

#ifndef FALSE
#define FALSE 0
#endif


#ifndef NULL
#define NULL  0
#endif

#ifndef VOID
typedef void           VOID;
#endif

#ifndef BOOL
typedef unsigned char  BOOL;
#endif

#ifndef CHAR
typedef signed char    CHAR;
#endif

#ifndef UCHAR
typedef unsigned char  UCHAR;
#endif

#ifndef INT16
typedef signed short   INT16;
#endif

#ifndef UINT16
typedef unsigned short UINT16;
#endif

#ifndef INT32
typedef signed int     INT32;
#endif

#ifndef UINT32
typedef unsigned int   UINT32;
#endif

#ifndef FLOAT
typedef float          FLOAT;
#endif

#ifndef DOUBLE
typedef double         DOUBLE;
#endif

#undef  BOOLEAN
#undef  INT8U
#undef  INT8S
#undef  INT16U
#undef  INT16S
#undef  INT32U
#undef  INT32S
#undef  INT64U
#undef  INT64S
#undef  FP32
#undef  FP64

typedef unsigned char       BOOLEAN;
typedef unsigned char       INT8U;          /* Unsigned  8 bit quantity*/
typedef signed   char       INT8S;          /* Signed    8 bit quantity*/
typedef unsigned short      INT16U;         /* Unsigned 16 bit quantity*/
typedef signed   short      INT16S;         /* Signed   16 bit quantity*/
typedef unsigned int        INT32U;         /* Unsigned 32 bit quantity*/
typedef signed   int        INT32S;         /* Signed   32 bit quantity*/
typedef unsigned long long  INT64U;         /* Unsigned 64 bit quantity*/
typedef signed   long long  INT64S;         /* Signed   64 bit quantity*/
typedef float               FP32;           /* Single precision FP32ing point*/
typedef double              FP64;           /* Double precision FP32ing point*/


//----------------------------------------------------------------------------------------------------

#endif


