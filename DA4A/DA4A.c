/*
 * DA4A.c
 *
 * Created: 4/12/2019 11:53:41 AM
 * Author : becerri2
 */

#define F_CPU 16000000UL // clock is 16MHz
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void init_adc(void);
int potencon; // controlling the motor with potentiometer
int toggle = 0; // to toggle the motor with the switch

int main()
{
	DDRD = 0x40; //enable port D
	DDRC = 0x02; // set Port C as outputs
	PORTC |= (1<<1); // enable pull-up pin
	TCCR0A=0x83; // set fast PWM & clear OCR0A on MATCH
	TCCR0B=0x05; // set prescaler to 1024
	PCICR = 0x02; // 0x02 is PCIE1, that is, enable PCIE1 for PCMSK1 to work
	PCMSK1 = 0x02; // enable pin changes on PCINT9 (PC1)

	sei(); // enable interrupt
	init_adc(); //call init_adc

	while (1)
	{


	}
}
void init_adc(void) // Initiate ADC function
{
	ADMUX = (1<<REFS0); // Reference voltage at Aref
	ADCSRA = (1<<ADEN)|(1<<ADSC)|(1<<ADATE)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
	// from ADCRSA we Enable ADC, Start Conversion, Set prescalar as 128
}

ISR(PCINT1_vect){
	if(!(PINC & (1<<PINC1)))
	{
		if(toggle == 0)
		{
			OCR0A = 0;
			_delay_ms(1000);
		}
		if (toggle == 1){
			while((ADCSRA&(1<<ADIF))==0); // wait for conversion

			potencon = ADC/5; // ADC Conversion
			OCR0A = potencon; // Output to converted value to 0CR0A
			_delay_ms(1000);
		}
		toggle ^= 1; //update state of motor to on
	}
}
