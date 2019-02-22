;
; DA1B.asm
;
; Created: 2/21/2019 5:50:59 PM
; Author : becerri2
;


; Replace with your application code

.equ STARTADDS = 0x0200 ;starting address

.org 0

	CLR R0 ;clearing r0 register
	LDI XL, low(STARTADDS) ;XL = STARTADDS[7:0]
	LDI XH,	high(STARTADDS);XH = STARTADDS[15:8]
	LDI YL, low(0X0400) ;YL=0x00
	LDI YH, high(0X0400);YH=0x04
	LDI ZL, low(0X0600);ZL = 0x00
	LDI ZH, high(0X0600);ZH = 0x06

	LDI R24,0 ;R24 = 0 for addc later
	LDI R22, 3 ;R22 = 3
	LDI R20, 99 ;R20 = 99
	LDI R21, 10 ;R21 = 10
START:

	INC R21 ;R21 = R21 + 1 used to inc num to populate X
	ST X+, R21  ;[X] = R3
	MOV R23, R21 ;R23 = R21
	JMP CHECK ;jump to check divisible by 3

CONTINUE:
	DEC R20 ;R20 = R20 - 1
	BRNE START ; if not equal to 0 continue to get next num in start
	JMP DONE ;jump to done

CHECK:
	SUBI R23, 0X03 ;subtract 3 from num R23
	BRLT NOTDIV ;if less then 0 then go to not divisible
	CPI R23, 0 ;compare R23 to 0
	BRNE CHECK ;if equal not equal to 0 continue to sub
	JMP ISDIV ;jump to divisible

ISDIV:
	ST Y+, R21 ;[Y] = R21
	ADD R16, R21 ; R16 = R16 + R21
	ADC R17, R24 ; R17 = R17 + R24 + carry
	JMP CONTINUE ; jump to continue

NOTDIV:
	ST Z+, R21 ; [z] = R21
	ADD R18, R21 ; R18 = R18 + R21
	ADC R19, R24 ; R19 = R19 + R24 + carry
	JMP CONTINUE ; jump to contiue

DONE:
BREAK
