/*
 * DA4B_T2.c
 *
 * Created: 4/20/2019 9:00:35 PM
 * Author : itzel
 */

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
int temp = 0;//set variable to 0

int main(void)

{
	DDRB = 0xFF; //set DDRB as an output
	DDRD = 0xFF; //set DDRD as an output
	TCCR1B|=(1<<WGM13)|(1<<WGM12)|(1<<CS11)|(1<<CS10); //prescaler 64 & mode
	TCCR1A|=(1<<COM1A1)|(1<<COM1B1)|(1<<WGM11); //set TCCR1A register
	ICR1 = 4999;
	ADMUX = 0x60; //use PC0 as ADC pin
	ADCSRA = 0xA6;//set ADEN, ADSC, ADPS1, ASPS2

	while (1)
	{
		ADCSRA |= ( 1 << ADSC); //start conversion
		while((ADCSRA & (1 << ADIF))== 0);
		temp = ADCH; //check value

		if(temp == 0) //if zero
		{
			OCR1A = 0; //turn 0 degrees
			_delay_ms(1000); //delay
		}
		if(temp == 255) //Max pot value
		{
			OCR1A = 535;  //turn 180 degrees
			_delay_ms(1000); //delay
		}
	}
}
