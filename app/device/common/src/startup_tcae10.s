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
;

; Amount of memory (in bytes) allocated for Stack
; Tailor this value to your application needs
; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>
    IF	:DEF:STACK_SIZE
Stack_Size      EQU     STACK_SIZE
    ELSE
Stack_Size      EQU     0x300
    ENDIF

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size      EQU     0x0

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit

                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset
                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

__Vectors       DCD     __initial_sp                   ; Top of Stack
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
                
__Vectors_End

__Vectors_Size  EQU  __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY

; Reset handler routine
Reset_Handler    PROC
                 EXPORT  Reset_Handler                 [WEAK]
                 IMPORT  TcMain
                 IMPORT  SystemInit
                 IMPORT  |Image$$RW_IRAM1$$ZI$$Base|
                 IMPORT  |Image$$RW_IRAM1$$ZI$$Limit|
                 ;interrupt disable
                 CPSID   I
                 ;close test mode
                 LDR     R0, =0x4000F000
                 LDR     R1, =0xFEDCBA98
                 STR     R1, [R0]
                 ;flash write disable
                 LDR     R0, =0x00FF00F8
                 LDR     R1, =0x12345678
                 STR     R1, [R0]
                 ;stack space zero init
                 MOVS    R0, #0
                 LDR     R1, =|Image$$RW_IRAM1$$ZI$$Base|
                 LDR     R2, =|Image$$RW_IRAM1$$ZI$$Limit|
FillZero
                 STR     R0, [R1, #0]
                 ADDS    R1, R1, #4
                 CMP     R1, R2
                 BCC     FillZero

                 LDR     R0, =SystemInit
                 BLX     R0
                 LDR     R0, =TcMain
                 BX      R0
                 ENDP

; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler                    [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler              [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler                    [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler                 [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler                [WEAK]
                B       .
                ENDP
Default_Handler PROC
                EXPORT  FLASH_IRQHandler               [WEAK]
                EXPORT  ADC_IRQHandler                  [WEAK]
                EXPORT  PWM_IRQHandler                  [WEAK]
                EXPORT  TIMER_IRQHandler                [WEAK]
                EXPORT  IWDG_IRQHandler                 [WEAK]
                EXPORT  SCI_IRQHandler                  [WEAK]
                EXPORT  AON_IRQHandler                  [WEAK]
                EXPORT  GPIO_IRQHandler                 [WEAK]
                EXPORT  SPI_IRQHandler                  [WEAK]
                EXPORT  TOUCH_IRQHandler                [WEAK]
                EXPORT  UART_IRQHandler                 [WEAK]
                EXPORT  IRQ011_Handler                  [WEAK]
                EXPORT  IRQ012_Handler                  [WEAK]
                EXPORT  IRQ013_Handler                  [WEAK]
                EXPORT  IRQ014_Handler                  [WEAK]
                EXPORT  IRQ015_Handler                  [WEAK]
                EXPORT  IRQ016_Handler                  [WEAK]
                EXPORT  IRQ017_Handler                  [WEAK]
                EXPORT  IRQ018_Handler                  [WEAK]
                EXPORT  IRQ019_Handler                  [WEAK]
                EXPORT  IRQ020_Handler                  [WEAK]
                EXPORT  IRQ021_Handler                  [WEAK]
                EXPORT  IRQ022_Handler                  [WEAK]
                EXPORT  IRQ023_Handler                  [WEAK]
                EXPORT  IRQ024_Handler                  [WEAK]
                EXPORT  IRQ025_Handler                  [WEAK]
                EXPORT  IRQ026_Handler                  [WEAK]
                EXPORT  IRQ027_Handler                  [WEAK]
                EXPORT  IRQ028_Handler                  [WEAK]
                EXPORT  IRQ029_Handler                  [WEAK]
                EXPORT  IRQ030_Handler                  [WEAK]
                EXPORT  IRQ031_Handler                  [WEAK]


FLASH_IRQHandler
ADC_IRQHandler
PWM_IRQHandler
TIMER_IRQHandler
IWDG_IRQHandler
SCI_IRQHandler
AON_IRQHandler
GPIO_IRQHandler
SPI_IRQHandler
TOUCH_IRQHandler
UART_IRQHandler
IRQ011_Handler
IRQ012_Handler
IRQ013_Handler
IRQ014_Handler
IRQ015_Handler
IRQ016_Handler
IRQ017_Handler
IRQ018_Handler
IRQ019_Handler
IRQ020_Handler
IRQ021_Handler
IRQ022_Handler
IRQ023_Handler
IRQ024_Handler
IRQ025_Handler
IRQ026_Handler
IRQ027_Handler
IRQ028_Handler
IRQ029_Handler
IRQ030_Handler
IRQ031_Handler
                B       .
                ENDP

                ALIGN

;*******************************************************************************
; User Stack and Heap initialization
;*******************************************************************************
                 IF      :DEF:__MICROLIB

                 EXPORT  __initial_sp
                 EXPORT  __heap_base
                 EXPORT  __heap_limit

                 ELSE

                 IMPORT  __use_two_region_memory
                 EXPORT  __user_initial_stackheap

__user_initial_stackheap

                 LDR     R0, =  Heap_Mem
                 LDR     R1, =(Stack_Mem + Stack_Size)
                 LDR     R2, = (Heap_Mem +  Heap_Size)
                 LDR     R3, = Stack_Mem
                 BX      LR

                 ALIGN

                 ENDIF

                 END

;************************ (C) COPYRIGHT Tinychip Microelectronics Co.,Ltd*****END OF FILE*****
