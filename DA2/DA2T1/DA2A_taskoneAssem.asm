;
; DA2A_taskoneAssem.asm
;
; Created: 3/4/2019 8:30:48 PM
; Author : becerri2
;


; Replace with your application code
.org	0x0000
	
 
    ;Initialize the microcontroller stack pointer
  
	ldi		r16, 0x24	; sets p2 and p5
	out		DDRB, r16	; enableing pd5 and p2 as outputs
	ldi		r16, 0x04	; use for toggle later
	ldi		r17, 0x20	; used for toggle later
	ldi		r20, 0x05	; Prescalar to 1024
	
	sts		TCCR1B,	r20 ; sets prescalar

begin:
	ldi		r20, 0x00	; setting up timer counter to 0
	sts		TCNT1H, r20 ; Timer counter is 16 bits
	sts		TCNT1L, r20 ; Thus, requires 2 8 bit regs

	rjmp	delay_on 	; routine call for delay see below 

returnOne:
	eor		r17, r16	; xor to toggle LED
	out		PORTB, r17	; enable pd2

	rjmp	delay_off 	; routine call for delay see below
	 
returnTwo:
	eor		r17, r16	; xor to toggle LED
	out		PORTB, r17	; enable pd2

	rjmp	begin		; repeat main loop


delay_off:
	lds		r29, TCNT1H	; load upper bytes of timer counter to r29
	lds		r28, TCNT1L ; load lower bytes of timer counter to r28

	cpi		r28, 0x12	; check to see if lower 8 bits of timer counter are 0x12
	brsh	body2		;branch if same or equal to then body2
	rjmp	delay_off	; otherwise keep checking lower bytes

body2:
	cpi		r29, 0x4F	; check if upper timer counter have reached 0x4F
	brlt	delay_off	; otherwise recheck the lower bytes
	rjmp returnTwo
	

delay_on:
	lds		r29, TCNT1H	; load upper bytes of timer counter to r29
	lds		r28, TCNT1L ; load lower bytes of timer counter to r28

	cpi		r28, 0xDA	; check to see if lower 8 bits of timer counter are 0xDA
	brsh	body1		;branch if same or equal to then body1
	rjmp	delay_on	; otherwise keep checking lower bytes

body1:
	cpi		r29, 0x1A	; check if upper timer counter is 0x1A
	brlt	delay_on	; otherwise recheck the lower bytes
	rjmp returnOne
