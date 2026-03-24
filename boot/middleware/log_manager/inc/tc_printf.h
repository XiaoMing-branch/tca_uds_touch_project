/**
 *****************************************************************************
 * @brief   tc_printf header file.
 *
 * @file    tc_printf.h
 * @author  AE/FAE team
 * @date    2024.01.01
 *****************************************************************************
 *
 * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
 * TIME. AS A RESULT, TINYCHIP SHALL NOT BE HELD LIABLE FOR ANY
 * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
 * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
 * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 *
 * <b>&copy; Copyright (c) 2024 Tinychip Microelectronics Co.,Ltd.</b>
 *
 *****************************************************************************
 */

#ifndef __TC_PRINTF_H__
#define __TC_PRINTF_H__

#ifdef __cplusplus
extern "C"
{
#endif

#define CONVERT_CR_2_CRLF        1   /* 1: Convert \n ==> \r\n in the output char */

#define log_out_func(func) log_func = (void(*)(unsigned char))(func)

extern void (*log_func)(unsigned char);

void tc_putc(char c);
void tc_puts(const char *str);
void tc_fputs(void (*func)(unsigned char), const char *str);
void tc_printf(const char *fmt, ...);
void tc_sprintf(char *buff, const char *fmt, ...);
void tc_fprintf(void (*func)(unsigned char), const char *fmt, ...);

#ifdef __cplusplus
}
#endif
#endif /* __TC_PRINTF_H__ */
