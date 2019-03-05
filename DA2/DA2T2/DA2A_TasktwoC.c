/*
 * DA2A_TasktwoC.c
 *
 * Created: 3/4/2019 11:02:28 PM
 * Author : becerri2
 */ 

#define F_CPU 16000000UL //Setting up to 16Mhz

#include <avr/io.h>
#include <util/delay.h>

int main (void)
{
	//set portb for output
	DDRB |= (1<<2);
	DDRB |= (1<<5);
	PORTB |= (1<<5);//turn led off
	PORTB |= (1<<2);//turn led off
	
	//set switch portc for input
	DDRC &= (0<<2);
	PORTC |= (0<<2);
	
	while(1)
	{
		
		if(!(PINC & (1<<PINC2)))
		{
			PORTB &= ~(1<<2); //turn pb.2 on
			_delay_ms(1250);  //set delay of 1.250
		}
		else
		{
			PORTB |= (1<<2);//turn pb.2 off
		}
	}
	return 0;
}


