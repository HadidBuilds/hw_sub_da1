/*
 * DA2C_ N_Timer0_Switch.c
 *
 * Created: 3/20/2019 7:25:06 PM
 * Author : becerri2
 */ 

#define F_CPU 16000000UL //Setting to 16Mhz

#include <avr/io.h>

int main(void)
{
	uint8_t OVFCount = 0; //set OVFCOUNT to zero
	DDRB |= (1<<2); //set PB.2 as an output
	DDRB |= (1<<5); //set PB.5 as an output
	PORTB |= (1<<2); //set low
	PORTB |= (1<<5); //set low
	
	DDRC &= (0<<2); //set PC.2 as an input
	PORTC |= (0<<2); //set
	
	TCCR0A = 0; // Normal Operation
	TCNT0=0; // start the timer at 0
	TCCR0B |= 5; //set prescaler 1024
	
	while (1)
	{
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
	return 0;
}