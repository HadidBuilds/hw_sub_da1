/*
 * DA4B_T1.c
 *
 * Created: 4/20/2019 8:42:49 PM
 * Author : itzel
 */

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void adc_int(void); //prototype for adc init function
void timer_init(void); //prototype for timer init function
volatile unsigned int speed; // variable for control delay
volatile int stop = 0; // if 1, the motor is turned off

int main(void)
{
	DDRB = 0x0F;   //Enable as output for portB
	PORTB = 0x00; // initialize to 0v
	adc_int();	  // call ADC function
	TCCR1B = 0x1A; // set CTC mode and 1024 prescaler
	ICR1 = 62258; //set value of ICR1

	while(1)
	{
		while((ADCSRA&(1<<ADIF))==0); // wait for conversion
		if (ADC >= 820)
		{
			 stop = 1;
		}
		if ((ADC < 820) && (ADC >= 617))
		{
			  stop = 0;
			  speed = 0x1869;
		}
		if ((ADC < 617) && (ADC >= 414))
		{
			stop = 0;
			speed = 0x124F;
		}
		if ((ADC < 414) && (ADC >= 211))
		{
			stop = 0;
			speed = 0x0C34;
		}
		if ((ADC < 211) && (ADC >= 000))
		{
			stop = 0;
			speed = 0x061A;
		}

		OCR1A = speed;		// set OCR1A to the determined speed
		TCNT1 = 0x00;		// reset the clock
		if(stop == 0)
		{
			// if the motor is not stopped, run a step with the assigned length delay
			while((TIFR1 & 0x2) != 0x2);
			PORTB = 0x09;
			TIFR1 |= (1<<OCF1A);
			while((TIFR1 & 0x2) != 0x2);
			PORTB = 0x03;
			TIFR1 |= (1<<OCF1A);
			while((TIFR1 & 0x2) != 0x2);
			PORTB = 0X06;
			TIFR1 |= (1<<OCF1A);
			while((TIFR1 & 0x2) != 0x2);
			PORTB = 0X0C;
			TIFR1 |= (1<<OCF1A);
		}
	}
}

void adc_int(void){
	ADMUX = (0<<REFS1)|//Reference selection bits
	(1<<REFS0)|//AVcc-external cap at AREF
	(0<<ADLAR)|//ADC Left Adjust Result
	(0<<MUX3)|
	(0<<MUX2)|//ANalogChannel Selection	Bits
	(0<<MUX1)|//ADC0 (PC0)
	(0<<MUX0);

	ADCSRA = (1<<ADEN)|//ADC ENable
	(1<<ADSC)|//ADC	Start Conversion
	(1<<ADATE)|//ADC Auto Trigger Enable
	(0<<ADIF)|//ADC	Interrupt Flag
	(1<<ADIE)|//ADC	Interrupt Enable
	(1<<ADPS2)|//ADC PrescalerSelect Bits
	(1<<ADPS1)|
	(1<<ADPS0);
}
