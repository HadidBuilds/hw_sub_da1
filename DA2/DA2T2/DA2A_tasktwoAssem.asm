;
; DA2A_tasktwoAssem.asm
;
; Created: 3/4/2019 11:00:55 PM
; Author : becerri2
;


; Replace with your application code
.org 0

ldi r16,0      ;r16 = 0
out ddrc, r16  ;enable as output
ldi r16, 0xff  ;r16 = 0xff
out ddrb, r16  ;enable as output
out portb, r16 ;enable as output

Start:	
		SBIC	PINC, 2	; PINC2 == high, skip
		RJMP	Start ; jumps to start until button is pressed
		RCALL	LED ; Call subroutine LED

Done:
		RJMP Start; will restart	

LED:
		CBI		PORTB, 2	; PB2 = 0
		LDI		R20, 5	; prescalar is set to 1024
		STS		TCCR1B, R20 ; set prescalar
		LDI		R20, 0	; timer is set to 0
		STS		TCNT1H, R20	; clear high 8 bits
		STS		TCNT1L, R20 ; clear lower 8 bits
		RJMP	Delayforlowbyte	; jump to delay routine
Delayforlowbyte:
		LDS		R29, TCNT1H		; load upper bytes of timer counter to r29
		LDS		R28, TCNT1L 	; load lower bytes of timer counter to r28
		CPI		R28, 0x4A		; check to see if lower 8 bits of timer counter are 0x4A
		BRSH	Delayforhighbyte
		RJMP	Delayforlowbyte		; otherwise keep checking
Delayforhighbyte:	
		CPI		R29, 0x4C		; check if upper timer counter have reached value
		BRLT	Delayforlowbyte	; otherwise recheck the lower bytes
		SBI		PORTB, 2		; will turn off LED
		RET
