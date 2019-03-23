/*
 * TIMER0_COMPA_vect_CTC.c
 *
 * Created: 3/20/2019 10:19:19 PM
 * Author : becerri2
 */ 

#define F_CPU 16000000UL //Setting to 16Mhz
#include <avr/interrupt.h>
#include <avr/io.h>

int main(void)
{
	DDRB |= (1<<2); //set PB.2 as an output
	DDRB |= (1<<5); //set PB.5 as an output
	PORTB |= (1<<2); //set low
	PORTB |= (1<<5); //set low
	
	OCR0A = 0xFF; //set output compare register
	TCCR0A = (1<<WGM01); //set mode to CTC
	TCCR0B = (1<<CS02) | (1<<CS00); //set prescaler to 1024
	TIMSK0 |= (1<<OCIE0A); //enable overflow interrupt
	TCNT0 = 0;//set to 0
	
	sei();//enable interrupts
		
	while (1)
	{
		//main loop
	}
}

ISR(TIMER0_COMPA_vect)//timer 0 overflow interrupt
{
	uint8_t OVFCount = 0; //set to 0
	
	OVFCount = 0;//set to 0
	TCNT0 = 0; //set to 0
	while(OVFCount <= 25)
	{
		TCNT0 = 0;//set to 0
		while ((TIFR0 & (1<<OCF0A)) == 0)
		{
			PORTB ^= (1<<2); //light up LED
		}
		TCNT0 = 0;//set to 0
		TIFR0 |= (1<<OCF0A);//reset flag
		OVFCount++;//increment counter
	}
	OVFCount = 0;//reset to 0
	TCNT0 = 0;//reset to 0
	while(OVFCount <= 17)
	{
		while ((TIFR0 & (1<<OCF0A)) == 0)
		{
			PORTB |= (1<<2); //keep LED off
		}
		OVFCount++;//increment counter
		TIFR0 |= (1<<OCF0A);//reset flag
		TCNT0 = 0;//reset to 0
	}
}