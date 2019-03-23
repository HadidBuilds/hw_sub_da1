/*
 * TIMER0_COMPA_vect_CTC_switch.c
 *
 * Created: 3/20/2019 11:23:12 PM
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
	uint8_t OVFCount = 0; //set OVFCOUNT to zero
	if(!(PINC & (1<<PINC2))) //if high enter statement
	{
		TCNT0 = 0; //reset TCNT0
		
		while(OVFCount < 77) //while less then 0
		{
			while ((TIFR0 & (1<<OCF0A)) == 0) //while not 255
			{
				PORTB &= ~(1<<2); //turn PB.2 on
			}
			OVFCount++; //increment counter
			TIFR0 |= (1<<OCF0A); //reset flag
			TCNT0 = 0; //reset TCNT0
		}
		
		TCNT0 = 0;//reset TCNT0
		OVFCount = 0; //set OVFcount to 0
	}
	else
	{
		PORTB |= (1<<2); //turn PB.2 off
	}
}