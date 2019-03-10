/*
 * DA2B_C.c
 *
 * Created: 3/9/2019 11:22:59 AM
 * Author : becerri2
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int main()
{
	DDRB |= (1<<5);	  //PB5 as an output
	PORTB |= (1<<5);  //turn off LED5 
	DDRB |= (1<<2);   //PB2 as an output
	PORTB |= (1<<2);  //turn off LED2
	
	PORTD |= (1<<2);  //pull-up activated
	
	EIMSK = (1<<INT0); //enable external interrupt 0
	sei(); //enable interrupt

	while(1); //wait here
}
//ISR for external interrupt 0
ISR(INT0_vect)
{
	PORTB ^= (1<<2); //toggle PORT.2
	_delay_ms(1250); //delay of 1.25 seconds
	PORTB ^= (1<<2); //toggle PORT.2
}

