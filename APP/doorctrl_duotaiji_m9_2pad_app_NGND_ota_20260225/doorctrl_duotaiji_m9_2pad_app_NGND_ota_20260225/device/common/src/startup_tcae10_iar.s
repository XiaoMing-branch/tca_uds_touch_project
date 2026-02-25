;********************************************************************************
;*
;* Copyright (c) 2020 Tinychip Microelectronics Co.,Ltd
;* All rights reserved.
;*
;    Redistribution and use in source and binary forms, with or without modification, 
;are permitted provided that the following conditions are met:
;
;    1. Redistributions of source code must retain the above copyright notice, this 
;       list of conditions and the following disclaimer.
;    2. Redistributions in binary form must reproduce the above copyright notice, 
;       this list of conditions and the following disclaimer in the documentation 
;       and/or other materials provided with the distribution.
;    3. Neither the name of the copyright holder nor the names of its contributors 
;       may be used to endorse or promote products derived from this software without 
;       specific prior written permission.
;
;    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
;AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
;WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
;IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
;INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
;NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
;PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
;WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
;ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
;OF SUCH DAMAGE.
;*******************************************************************************
        MODULE  ?cstartup

        ;; Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(3)

        SECTION .intvec:CODE:NOROOT(2)

        EXTERN  __iar_program_start
        EXTERN  SystemInit        
        PUBLIC  __vector_table

        DATA               
__vector_table
                DCD     sfe(CSTACK)
                DCD     Reset_Handler             ; Reset
                DCD     NMI_Handler               ; NMI
                DCD     HardFault_Handler         ; Hard Fault
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     SVC_Handler               ; SVCall
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     PendSV_Handler            ; PendSV
                DCD     SysTick_Handler           ; SysTick
                ; External Interrupts
                DCD     FLASH_IRQHandler         ; 
                DCD     ADC_IRQHandler            ; 
                DCD     PWM_IRQHandler            ; 
                DCD     TIMER_IRQHandler          ; 
                DCD     IWDG_IRQHandler           ; 
                DCD     SCI_IRQHandler            ; 
                DCD     AON_IRQHandler            ; 
                DCD     GPIO_IRQHandler           ; 
                DCD     SPI_IRQHandler            ; 
                DCD     TOUCH_IRQHandler          ; 
                DCD     UART_IRQHandler           ; 
                DCD     IRQ011_Handler            ; 
                DCD     IRQ012_Handler            ; 
                DCD     IRQ013_Handler            ; 
                DCD     IRQ014_Handler            ; 
                DCD     IRQ015_Handler            ; 
                DCD     IRQ016_Handler            ; 
                DCD     IRQ017_Handler            ; 
                DCD     IRQ018_Handler            ; 
                DCD     IRQ019_Handler            ; 
                DCD     IRQ020_Handler            ; 
                DCD     IRQ021_Handler            ; 
                DCD     IRQ022_Handler            ; 
                DCD     IRQ023_Handler            ; 
                DCD     IRQ024_Handler            ; 
                DCD     IRQ025_Handler            ; 
                DCD     IRQ026_Handler            ; 
                DCD     IRQ027_Handler            ; 
                DCD     IRQ028_Handler            ; 
                DCD     IRQ029_Handler            ; 
                DCD     IRQ030_Handler            ; 
                DCD     IRQ031_Handler            ; 

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;
        THUMB

        PUBWEAK Reset_Handler
        SECTION .text:CODE:REORDER:NOROOT(2)

Reset_Handler
        ;flash write disable
        LDR     R0, =0x00FF00F8
        LDR     R1, =0x12345678
        STR     R1, [R0]

        LDR     R0, =SystemInit
        BLX     R0
        LDR     R0, =__iar_program_start
        BX      R0

        PUBWEAK NMI_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
NMI_Handler
        B NMI_Handler


        PUBWEAK HardFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
HardFault_Handler
        B HardFault_Handler


        PUBWEAK SVC_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SVC_Handler
        B SVC_Handler


        PUBWEAK PendSV_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
PendSV_Handler
        B PendSV_Handler


        PUBWEAK SysTick_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SysTick_Handler
        B SysTick_Handler

        PUBWEAK FLASH_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
FLASH_IRQHandler
        B FLASH_IRQHandler

        PUBWEAK ADC_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ADC_IRQHandler
        B ADC_IRQHandler

        PUBWEAK PWM_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
PWM_IRQHandler
        B PWM_IRQHandler

        PUBWEAK TIMER_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TIMER_IRQHandler
        B TIMER_IRQHandler

        PUBWEAK IWDG_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
IWDG_IRQHandler
        B IWDG_IRQHandler

        PUBWEAK SCI_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SCI_IRQHandler
        B SCI_IRQHandler

        PUBWEAK AON_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
AON_IRQHandler
        B AON_IRQHandler

        PUBWEAK GPIO_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
GPIO_IRQHandler
        B GPIO_IRQHandler

        PUBWEAK SPI_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SPI_IRQHandler
        B SPI_IRQHandler

        PUBWEAK TOUCH_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TOUCH_IRQHandler
        B TOUCH_IRQHandler

        PUBWEAK UART_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
UART_IRQHandler
        B UART_IRQHandler


         PUBWEAK IRQ011_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
IRQ011_Handler
        B IRQ011_Handler

        PUBWEAK IRQ012_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
IRQ012_Handler
        B IRQ012_Handler

        PUBWEAK IRQ013_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
IRQ013_Handler
        B IRQ013_Handler

        PUBWEAK IRQ014_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
IRQ014_Handler
        B IRQ014_Handler

        PUBWEAK IRQ015_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
IRQ015_Handler
        B IRQ015_Handler

        PUBWEAK IRQ016_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
IRQ016_Handler
        B IRQ016_Handler

        PUBWEAK IRQ017_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
IRQ017_Handler
        B IRQ017_Handler

        PUBWEAK IRQ018_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
IRQ018_Handler
        B IRQ018_Handler

        PUBWEAK IRQ019_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
IRQ019_Handler
        B IRQ019_Handler

        PUBWEAK IRQ020_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
IRQ020_Handler
        B IRQ020_Handler   

         PUBWEAK IRQ021_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
IRQ021_Handler
        B IRQ021_Handler

        PUBWEAK IRQ022_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
IRQ022_Handler
        B IRQ022_Handler

        PUBWEAK IRQ023_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
IRQ023_Handler
        B IRQ023_Handler

        PUBWEAK IRQ024_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
IRQ024_Handler
        B IRQ024_Handler

        PUBWEAK IRQ025_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
IRQ025_Handler
        B IRQ025_Handler

        PUBWEAK IRQ026_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
IRQ026_Handler
        B IRQ026_Handler

        PUBWEAK IRQ027_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
IRQ027_Handler
        B IRQ027_Handler

        PUBWEAK IRQ028_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
IRQ028_Handler
        B IRQ028_Handler

        PUBWEAK IRQ029_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
IRQ029_Handler
        B IRQ029_Handler

        PUBWEAK IRQ030_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
IRQ030_Handler
        B IRQ030_Handler


        PUBWEAK IRQ031_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
IRQ031_Handler
        B IRQ031_Handler



        END
;************************ (C) COPYRIGHT Tinychip Microelectronics Co.,Ltd*****END OF FILE*****
