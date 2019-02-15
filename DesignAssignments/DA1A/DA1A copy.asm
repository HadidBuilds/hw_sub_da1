;
; DA1A.asm
;
; Created: 2/15/2019 12:18:20 AM
; Author : itzel
;


; Replace with your application code
.org 0x0000
 
START:
	LDI R25, 0X10   ;High byte multiplicand = 16
	LDI R24, 0X01	;Low byte multiplicand = 1
	;high and low together is 4097
	LDI R22, 0X11   ;multiplier = 17
	LDI R26, 0		;set to zero for carry
	MOV	R27, R22	;saved iteration for loop
	INC R27			;increment by one to compare to breq
	CLR R18			;resets R18
	CLR R19			;resets R19
	CLR R20			;resets R20
	CPI R22, 0		;compares R22 to 0
	BREQ DONE		;if it is equal to 0 then go to done

CONTINUE:			
	DEC R27			;dec counter
	BREQ DONE		;if not equal to 0 jump to done
	ADD R18, R24	;add 
	ADC R19,R25		;add carry
	ADC R20, R26	;add carry
	JMP CONTINUE	;jmp back to continue

DONE:
	BREAK ;answer should have 011011 = 694649