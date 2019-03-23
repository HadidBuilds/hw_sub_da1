/*
 * DA2C_TIMER0_OVF_vect_N.c
 *
 * Created: 3/20/2019 10:05:35 PM
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
	
	DDRC &= (0<<2); //set PC.2 as an input
	PORTC |= (0<<2); //set
	
	TIMSK0 |= (1<<TOIE0); //enabling timer overflow interrupt

	TCNT0 = 0; // start the timer at 0

	sei();//enable interrupts
	TCCR0B = 5;	//set prescaler
	
	while (1)
	{
		//main loop
	}
}

ISR(TIMER0_OVF_vect)//timer 0 overflow interrupt
{
	uint8_t OVFCount = 0; //set to 0
	
	OVFCount = 0;//set to 0
	TCNT0 = 0; //set to 0
	while(OVFCount <= 25)
	{
		TCNT0 = 0;//set to 0
		while ((TIFR0 & 0x01) == 0)
		{
			PORTB ^= (1<<2); //light up LED
		}
		TCNT0 = 0;//set to 0
		TIFR0=0x01;//reset flag
		OVFCount++;//increment counter
	}
	OVFCount = 0;//reset to 0
	TCNT0 = 0;//reset to 0
	while(OVFCount <= 17)
	{
		while ((TIFR0 & 0x01) == 0)
		{
			PORTB |= (1<<2); //keep LED off
		}
		OVFCount++;//increment counter
		TIFR0 = 0x01;//reset flag
		TCNT0 = 0;//reset to 0
	}
}