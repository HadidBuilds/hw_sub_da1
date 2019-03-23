/*
 * DA2C_TIMER0_OVF_vect_interrupt_N.c
 *
 * Created: 3/20/2019 8:26:18 PM
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
		uint8_t OVFCount = 0; //set OVFCOUNT to zero
		if(!(PINC & (1<<PINC2))) //if high enter statement
		{
			TCNT0 = 0; //reset TCNT0
	
			while(OVFCount < 77) //while less then 0
			{
				while ((TIFR0 & 0x01) == 0) //while not 255
				{
					PORTB &= ~(1<<2); //turn PB.2 on
				}
				OVFCount++; //increment counter
				TIFR0=0x01; //reset flag
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