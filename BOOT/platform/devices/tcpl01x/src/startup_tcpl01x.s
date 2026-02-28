;
;*****************************************************************************
; @brief   startup_tcpl01x.s  file.
;
; @file    startup_tcpl01x.s .h
; @author  AE/FAE team
; @date    2024.01.01
;******************************************************************************
;
; THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
; WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
; TIME. AS A RESULT, TINYCHIP SHALL NOT BE HELD LIABLE FOR ANY
; DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
; FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
; CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
;
; <b>&copy; Copyright (c) 2024 Tinychip Microelectronics Co.,Ltd.</b>
;
; *****************************************************************************

;<h> Stack Configuration
;  <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
;</h>

Stack_Size      EQU      0x00000400

                AREA     STACK, NOINIT, READWRITE, ALIGN=3
__stack_limit
Stack_Mem       SPACE    Stack_Size
__initial_sp


;<h> Heap Configuration
;  <o> Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
;</h>

Heap_Size       EQU      0x00000100

                IF       Heap_Size != 0                      ; Heap is provided
                AREA     HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE    Heap_Size
__heap_limit
                ENDIF


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
                DCD     AFE_INT_IRQHandler        ;
                DCD     TIMER_IRQHandler          ;
                DCD     IWDG_IRQHandler           ;
                DCD     FLASH_IRQHandler          ;
                DCD     AFE_COM_IRQHandler        ;

                SPACE   ( 27 * 4 )                ; Interrupts 5 .. 31 are left out
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

; Macro to define default exception/interrupt handlers.
; Default handler are weak symbols with an endless loop.
; They can be overwritten by real handlers.
                MACRO
                Set_Default_Handler  $Handler_Name
$Handler_Name   PROC
                EXPORT   $Handler_Name             [WEAK]
                B        .
                ENDP
                MEND

; Default exception/interrupt handler

                Set_Default_Handler  NMI_Handler
                Set_Default_Handler  HardFault_Handler
                Set_Default_Handler  SVC_Handler
                Set_Default_Handler  PendSV_Handler
                Set_Default_Handler  SysTick_Handler

                Set_Default_Handler  AFE_INT_IRQHandler
                Set_Default_Handler  TIMER_IRQHandler
                Set_Default_Handler  IWDG_IRQHandler
                Set_Default_Handler  FLASH_IRQHandler
                Set_Default_Handler  AFE_COM_IRQHandler

                ALIGN

; User setup Stack & Heap

                IF       :LNOT::DEF:__MICROLIB
                IMPORT   __use_two_region_memory
                ENDIF

                EXPORT   __stack_limit
                EXPORT   __initial_sp
                IF       Heap_Size != 0                      ; Heap is provided
                EXPORT   __heap_base
                EXPORT   __heap_limit
                ENDIF

                END

;************************ (C) COPYRIGHT Tinychip Microelectronics Co.,Ltd*****END OF FILE*****