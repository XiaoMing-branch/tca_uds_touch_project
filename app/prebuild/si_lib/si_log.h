/**
*****************************************************************************
* @brief  si log header
* @file   si_log.h
* @author AE/FAE team
* @date   28/JUL/2023
*****************************************************************************
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
* TIME. AS A RESULT, TINYCHIP SHALL NOT BE HELD LIABLE FOR ANY
* DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
* FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
* CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*
* <b>&copy; Copyright (c) 2023 Tinychip Microelectronics Co.,Ltd.</b>
*
*****************************************************************************
*/

#ifndef SI_LOG_H__
#define SI_LOG_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifdef SI_PC_DEBUG

#define LOG_COLOR_E
#define LOG_COLOR_W
#define LOG_COLOR_I
#define LOG_COLOR_D
#define LOG_COLOR_V
#define LOG_RESET_COLOR

#define SI_LOG_VERBOSE     0
#define SI_LOG_DEBUG       1
#define SI_LOG_INFO        2
#define SI_LOG_WARN        3
#define SI_LOG_ERROR       4

#define SI_LOG_FORMAT(letter, desp, format) LOG_COLOR_##letter #desp " %s: " format LOG_RESET_COLOR

#define SI_LOGE(tag, format, ...) SI_LOG_WRITE(SI_LOG_ERROR, SI_LOG_FORMAT(E, _LOGE, format), tag, ##__VA_ARGS__)
#define SI_LOGW(tag, format, ...) SI_LOG_WRITE(SI_LOG_WARN, SI_LOG_FORMAT(W, _LOGW, format), tag, ##__VA_ARGS__)
#define SI_LOGI(tag, format, ...) SI_LOG_WRITE(SI_LOG_INFO, SI_LOG_FORMAT(I, _LOGI, format), tag, ##__VA_ARGS__)
#define SI_LOGD(tag, format, ...) SI_LOG_WRITE(SI_LOG_DEBUG, SI_LOG_FORMAT(D, _LOGD, format), tag, ##__VA_ARGS__)
#define SI_LOGV(tag, format, ...) SI_LOG_WRITE(SI_LOG_VERBOSE, SI_LOG_FORMAT(V, _LOGV, format), tag, ##__VA_ARGS__)

extern void (*SI_LOG_SYMBOL_U8)(const char *name, const void *p, int len);
extern void (*SI_LOG_SYMBOL_I8)(const char *name, const void *p, int len);
extern void (*SI_LOG_SYMBOL_U16)(const char *name, const void *p, int len);
extern void (*SI_LOG_SYMBOL_I16)(const char *name, const void *p, int len);
extern void (*SI_LOG_SYMBOL_U32)(const char *name, const void *p, int len);
extern void (*SI_LOG_SYMBOL_I32)(const char *name, const void *p, int len);

extern void (*SI_LOG_WRITE)(int t, const char *format, ...);

#else

#define SI_LOGE(tag, format, ...)   {(void)(tag);(void)(format);}
#define SI_LOGW(tag, format, ...)   {(void)(tag);(void)(format);}
#define SI_LOGI(tag, format, ...)   {(void)(tag);(void)(format);}
#define SI_LOGD(tag, format, ...)   {(void)(tag);(void)(format);}
#define SI_LOGV(tag, format, ...)   {(void)(tag);(void)(format);}

#define SI_LOG_SYMBOL_U8(name, p, len)      {(void)(name);(void)(p);(void)(len);}
#define SI_LOG_SYMBOL_I8(name, p, len)      {(void)(name);(void)(p);(void)(len);}
#define SI_LOG_SYMBOL_U16(name, p, len)     {(void)(name);(void)(p);(void)(len);}
#define SI_LOG_SYMBOL_I16(name, p, len)     {(void)(name);(void)(p);(void)(len);}
#define SI_LOG_SYMBOL_U32(name, p, len)     {(void)(name);(void)(p);(void)(len);}
#define SI_LOG_SYMBOL_I32(name, p, len)     {(void)(name);(void)(p);(void)(len);}

#endif

#ifdef __cplusplus
}
#endif

#endif
