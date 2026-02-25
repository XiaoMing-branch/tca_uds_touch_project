/*
 * vectors_tcpt.c
 *
 *  Created on: 2022年4月30日
 *      Author: RAMI ABD ALMALK
 */

/*
 * This file was automatically generated from the Arm assembly file.
 * Copyright (c) 2020 Liviu Ionescu.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

// The list of external handlers is from the Arm assembly startup files.
// ----------------------------------------------------------------------------
#include "exception-handlers.h"
#include "interrupt.h"
#include "tc_log.h"

// ----------------------------------------------------------------------------

void __attribute__((weak)) Default_Handler ( void );

// Forward declaration of the specific IRQ handlers. These are aliased
// to the Default_Handler, which is a 'forever' loop. When the application
// defines a handler (with the same name), this will automatically take
// precedence over these weak definitions

void __attribute__ ((weak, alias ("Default_Handler"))) IRQ000_Handler ( void );
void __attribute__ ((weak, alias ("Default_Handler"))) IRQ001_Handler ( void );
void __attribute__ ((weak, alias ("Default_Handler"))) IRQ002_Handler ( void );
void __attribute__ ((weak, alias ("Default_Handler"))) IRQ003_Handler ( void );
void __attribute__ ((weak, alias ("Default_Handler"))) IRQ004_Handler ( void );
void __attribute__ ((weak, alias ("Default_Handler"))) IRQ005_Handler ( void );
void __attribute__ ((weak, alias ("Default_Handler"))) IRQ006_Handler ( void );
void __attribute__ ((weak, alias ("Default_Handler"))) IRQ007_Handler ( void );
void __attribute__ ((weak, alias ("Default_Handler"))) IRQ008_Handler ( void );
void __attribute__ ((weak, alias ("Default_Handler"))) IRQ009_Handler ( void );
void __attribute__ ((weak, alias ("Default_Handler"))) IRQ010_Handler ( void );
void __attribute__ ((weak, alias ("Default_Handler"))) IRQ011_Handler ( void );
void __attribute__ ((weak, alias ("Default_Handler"))) IRQ012_Handler ( void );
void __attribute__ ((weak, alias ("Default_Handler"))) IRQ013_Handler ( void );
void __attribute__ ((weak, alias ("Default_Handler"))) IRQ014_Handler ( void );
void __attribute__ ((weak, alias ("Default_Handler"))) IRQ015_Handler ( void );
void __attribute__ ((weak, alias ("Default_Handler"))) IRQ016_Handler ( void );
void __attribute__ ((weak, alias ("Default_Handler"))) IRQ017_Handler ( void );
void __attribute__ ((weak, alias ("Default_Handler"))) IRQ018_Handler ( void );
void __attribute__ ((weak, alias ("Default_Handler"))) IRQ019_Handler ( void );
void __attribute__ ((weak, alias ("Default_Handler"))) IRQ020_Handler ( void );
void __attribute__ ((weak, alias ("Default_Handler"))) IRQ021_Handler ( void );
void __attribute__ ((weak, alias ("Default_Handler"))) IRQ022_Handler ( void );
void __attribute__ ((weak, alias ("Default_Handler"))) IRQ023_Handler ( void );
void __attribute__ ((weak, alias ("Default_Handler"))) IRQ024_Handler ( void );
void __attribute__ ((weak, alias ("Default_Handler"))) IRQ025_Handler ( void );
void __attribute__ ((weak, alias ("Default_Handler"))) IRQ026_Handler ( void );
void __attribute__ ((weak, alias ("Default_Handler"))) IRQ027_Handler ( void );
void __attribute__ ((weak, alias ("Default_Handler"))) IRQ028_Handler ( void );
void __attribute__ ((weak, alias ("Default_Handler"))) IRQ029_Handler ( void );
void __attribute__ ((weak, alias ("Default_Handler"))) IRQ030_Handler ( void );
void __attribute__ ((weak, alias ("Default_Handler"))) IRQ031_Handler ( void );

// ----------------------------------------------------------------------------

extern unsigned int __stack;

typedef void (*const pHandler) ( void );

// ----------------------------------------------------------------------------

// The table of interrupt handlers. It has an explicit section name
// and relies on the linker script to place it at the correct location
// in memory.

__attribute__ ((section(".isr_vector"),used)) pHandler __isr_vectors[] =
    {
    // Cortex-M Core Handlers
            (pHandler) &__stack,               // The initial stack pointer
            Reset_Handler,                     // The reset handler

            NMI_Handler,                       // The NMI handler
            HardFault_Handler,                 // The hard fault handler
            0,                                 // Reserved
            0,                                 // Reserved
            0,                                 // Reserved
            0,                                 // Reserved
            0,                                 // Reserved
            0,                                 // Reserved
            0,                                 // Reserved
            SVC_Handler,                       // SVCall handler
            0,                                 // Reserved
            0,                                 // Reserved
            PendSV_Handler,                    // The PendSV handler
            SysTick_Handler,                   // The SysTick handler

            // ----------------------------------------------------------------------
            // External Interrupts
            /* @formatter:off */
            IRQ000_Handler,
            IRQ001_Handler,
            IRQ002_Handler,
            IRQ003_Handler,
            IRQ004_Handler,
            IRQ005_Handler,
            IRQ006_Handler,
            IRQ007_Handler,
            IRQ008_Handler,
            IRQ009_Handler,
            IRQ010_Handler,
            IRQ011_Handler,
            IRQ012_Handler,
            IRQ013_Handler,
            IRQ014_Handler,
            IRQ015_Handler,
            IRQ016_Handler,
            IRQ017_Handler,
            IRQ018_Handler,
            IRQ019_Handler,
            IRQ020_Handler,
            IRQ021_Handler,
            IRQ022_Handler,
            IRQ023_Handler,
            IRQ024_Handler,
            IRQ025_Handler,
            IRQ026_Handler,
            IRQ027_Handler,
            IRQ028_Handler,
            IRQ029_Handler,
            IRQ030_Handler,
            IRQ031_Handler,
    };
                                    /* @formatter:on */
// ----------------------------------------------------------------------------
// Processor ends up here if an unexpected interrupt occurs or a
// specific handler is not present in the application code.
// When in DEBUG, trigger a debug exception to clearly notify
// the user of the exception and help identify the cause.
void __attribute__ ((section(".after_vectors"))) Default_Handler ( void )
{
#if defined(DEBUG)
    __DEBUG_BKPT();
#endif
    TC_LOG("[Default_Handler\n]");
    while (1)
    {
        ;
    }
}

// ----------------------------------------------------------------------------

