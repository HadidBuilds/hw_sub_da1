;
; DA2B_assem.asm
;
; Created: 3/9/2019 12:02:17 PM
; Author : becerri2
;


; Replace with your application code
.ORG 0  ;location for reset
JMP MAIN

.ORG 0x02 ;location for external interrupt 0
JMP EX0_ISR

MAIN:
;initialize stack
LDI R20,HIGH(RAMEND)
OUT SPH,R20
LDI R20,LOW(RAMEND)
OUT SPL,R20   
;initialize stack

LDI R16, 0xFF  ;load register to set all leds
OUT DDRB, R16  ;enable output
OUT PORTB, R16 ;set low
LDI R16, 0x04  ;load in register and will be used later for xor
LDI R21, 56    ;used for xor later
LDI R19, 0xFF  ;used later to set pins to low

LDI R20, 0X2   ;make INT0 falling edge triggered
STS EICRA, R20 ;pull-up activated
SBI DDRB, 2 ;port.2 = output
SBI PORTD, 2 ; pull-up activated
LDI R20, (1<<INT0) ;enable INT0
OUT EIMSK, R20
SEI ;enable interrupts 

HERE:
OUT PORTB, R19 ;setting to low
JMP HERE

EX0_ISR:
	EOR R21, R16    ;toggling LEDs
	OUT PORTB, R21	;ouputs LED
	
;;;;;Delay subroutine;;;;;;;;;;;;;;;
	LDI R23, 70
D3:
	LDI R24, 229
D4:
	LDI R22, 249
D5:
	NOP
	NOP
	DEC R22
	BRNE D5
	DEC R24
	BRNE D4
	DEC R23
	BRNE D3
	RETI
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

