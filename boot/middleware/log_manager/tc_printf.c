/**
 *****************************************************************************
 * @brief   tc_printf source file.
 *
 * @file    tc_printf.c
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

#include <stdarg.h>
#include "tc_printf.h"

/* Pointer to the output stream */
void (*log_func)(unsigned char);
static char *outptr;

/********************************************************
** \brief   Put a character
**
** \param   char    c
**
** \retval  None
*********************************************************/
void tc_putc(char c)
{
    if (CONVERT_CR_2_CRLF && c == '\n')
    {
        tc_putc('\r');    /* CR -> CRLF */
    }

    if (outptr)
    {
        *outptr++ = (unsigned char)c;
        return;
    }

    if (log_func)
    {
        log_func((unsigned char)c);
    }
}

/********************************************************
** \brief   Put a null-terminated string
**
** \param   const char *    fmt      Pointer to the string
**
** \retval  None
*********************************************************/
void tc_puts(const char *str)
{
    while (*str)
    {
        tc_putc(*str++);
    }
}

/********************************************************
** \brief   tc_fputs
**
** \param   void(*func)(unsigned char)  Pointer to the output function
** \param   const char *          str   Pointer to the string
**
** \retval  None
*********************************************************/
void tc_fputs(void(*func)(unsigned char), const char *str)
{
    void (*pf)(unsigned char);

    pf = log_func;     /* Save current output device */
    log_func = func;   /* Switch output to specified device */

    while (*str)        /* Put the string */
    {
        tc_putc(*str++);
    }

    log_func = pf;     /* Restore output device */
}

/*----------------------------------------------*/
/* Formatted string output                      */
/*----------------------------------------------*/
/*  tc_printf("%d", 1234);            "1234"
    tc_printf("%6d,%3d%%", -200, 5);  "  -200,  5%"
    tc_printf("%-6u", 100);           "100   "
    tc_printf("%ld", 12345678L);      "12345678"
    tc_printf("%04x", 0xA3);          "00a3"
    tc_printf("%08LX", 0x123ABC);     "00123ABC"
    tc_printf("%016b", 0x550F);       "0101010100001111"
    tc_printf("%s", "String");        "String"
    tc_printf("%-4s", "abc");         "abc "
    tc_printf("%4s", "abc");          " abc"
    tc_printf("%c", 'a');             "a"
    tc_printf("%f", 10.0);            <tc_printf lacks floating point support>
*/

/********************************************************
** \brief   tc_vprintf
**
** \param   const char *    fmt      Pointer to the format string
** \param   va_list          arp      Pointer to arguments
**
** \retval  None
*********************************************************/
static void tc_vprintf(const char *fmt, va_list arp)
{
    unsigned int r, i, j, w, f;
    unsigned long v;
    char s[16], c, d, *p;

    for (;;)
    {
        c = *fmt++;                 /* Get a char */

        if (!c)
        {
            break;    /* End of format? */
        }

        if (c != '%')               /* Pass through it if not a % sequense */
        {
            tc_putc(c);
            continue;
        }

        f = 0;
        c = *fmt++;                 /* Get first char of the sequense */

        if (c == '0')               /* Flag: '0' padded */
        {
            f = 1;
            c = *fmt++;
        }
        else
        {
            if (c == '-')           /* Flag: left justified */
            {
                f = 2;
                c = *fmt++;
            }
        }

        for (w = 0; c >= '0' && c <= '9'; c = *fmt++)   /* Minimum width */
        {
            w = w * 10 + c - '0';
        }

        if (c == 'l' || c == 'L')   /* Prefix: Size is long int */
        {
            f |= 4;
            c = *fmt++;
        }

        if (!c)
        {
            break;    /* End of format? */
        }

        d = c;

        if (d >= 'a')
        {
            d -= 0x20;
        }

        switch (d)                  /* Type is... */
        {
            case 'S' :                  /* String */
                p = va_arg(arp, char *);

                for (j = 0; p[j]; j++) ;

                while (!(f & 2) && j++ < w)
                {
                    tc_putc(' ');
                }

                tc_puts(p);

                while (j++ < w)
                {
                    tc_putc(' ');
                }

                continue;

            case 'C' :                  /* Character */
                tc_putc((char)va_arg(arp, int));
                continue;

            case 'B' :                  /* Binary */
                r = 2;
                break;

            case 'O' :                  /* Octal */
                r = 8;
                break;

            case 'D' :                  /* Signed decimal */
            case 'U' :                  /* Unsigned decimal */
                r = 10;
                break;

            case 'X' :                  /* Hexdecimal */
                r = 16;
                break;

            default:                    /* Unknown type (passthrough) */
                tc_putc(c);
                continue;
        }

        /* Get an argument and put it in numeral */
        v = (f & 4) ? va_arg(arp, long) : ((d == 'D') ? (long)va_arg(arp, int) : (long)va_arg(arp, unsigned int));

        if (d == 'D' && (v & 0x80000000))
        {
            v = 0 - v;
            f |= 8;
        }

        i = 0;

        do
        {
            d = (char)(v % r);
            v /= r;

            if (d > 9)
            {
                d += (c == 'x') ? 0x27 : 0x07;
            }

            s[i++] = d + '0';
        }
        while (v && i < sizeof(s));

        if (f & 8)
        {
            s[i++] = '-';
        }

        j = i;
        d = (f & 1) ? '0' : ' ';

        while (!(f & 2) && j++ < w)
        {
            tc_putc(d);
        }

        do
        {
            tc_putc(s[--i]);
        }
        while (i);

        while (j++ < w)
        {
            tc_putc(' ');
        }
    }
}

/********************************************************
** \brief   Put a formatted string to the default device
**
** \param   const char *    fmt      Pointer to the format string
**
** \retval  None
*********************************************************/
void tc_printf(const char *fmt,  ...)
{
    va_list arp;

    va_start(arp, fmt);
    tc_vprintf(fmt, arp);
    va_end(arp);
}

/********************************************************
** \brief  Put a formatted string to the memory
**
** \param   char*            buff    Pointer to the output buffer
** \param   const char *     fmt     Pointer to the format string
**
** \retval  None
*********************************************************/
void tc_sprintf(char *buff, const char *fmt, ...)
{
    va_list arp;

    outptr = buff;      /* Switch destination for memory */

    va_start(arp, fmt);
    tc_vprintf(fmt, arp);
    va_end(arp);

    *outptr = 0;        /* Terminate output string with a \0 */
    outptr = 0;         /* Switch destination for device */
}

/********************************************************
** \brief  Put a formatted string to the specified device
**
** \param   void(*func)(unsigned char)      Pointer to the output function
** \param   const char *        fmt         Pointer to the format string
**
** \retval  None
*********************************************************/
void tc_fprintf(void(*func)(unsigned char), const char *fmt,  ...)
{
    va_list arp;
    void (*pf)(unsigned char);

    pf = log_func;     /* Save current output device */
    log_func = func;   /* Switch output to specified device */

    va_start(arp, fmt);
    tc_vprintf(fmt, arp);
    va_end(arp);

    log_func = pf;     /* Restore output device */
}
