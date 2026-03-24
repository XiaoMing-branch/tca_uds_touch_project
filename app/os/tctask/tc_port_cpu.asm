;*****************************************************************************
;* @brief  tc port cpu asm
;* @file   tc_port_cpu.asm
;* @author AE/FAE team
;* @date   28/JUL/2023
;*****************************************************************************
;*
;* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
;* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
;* TIME. AS A RESULT, TINYCHIP SHALL NOT BE HELD LIABLE FOR ANY
;* DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
;* FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
;* CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
;*
;* <b>&copy; Copyright (c) 2023 Tinychip Microelectronics Co.,Ltd.</b>
;*
;*****************************************************************************

	EXPORT  TC_CPU_SR_Save                                      ; Functions declared in this file
    EXPORT  TC_CPU_SR_Restore
		
	AREA |.text|, CODE, READONLY, ALIGN=2
	THUMB
	REQUIRE8
	PRESERVE8

;********************************************************************************************************
; Prototypes :     TC_CPU_SR  TC_CPU_SR_Save(void);
;                  void       TC_CPU_SR_Restore(TC_CPU_SR cpu_sr);
;********************************************************************************************************

TC_CPU_SR_Save
        MRS     R0, PRIMASK                 ; Set prio int mask to mask all (except faults)
        CPSID   I
        BX      LR


TC_CPU_SR_Restore
        MSR     PRIMASK, R0
        BX      LR

	END
