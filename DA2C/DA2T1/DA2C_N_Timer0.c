/*
 * DA2C_N_Timer0.c
 *
 * Created: 3/20/2019 9:07:58 PM
 * Author : becerri2
 */ 

#include <avr/io.h>

int main(void)
{
 uint8_t OVFCount = 0;//set to 0
 TCCR0B = 5;//prescaler 1024
 DDRB |= (1<<2);//set as output
 PORTB |= (1<<2);//set low
 DDRB |= (1<<5);//set as output
 PORTB |= (1<<5);//set low
 while (1)
  {
	    OVFCount = 0;//reset to 0
		TCNT0 = 0;//reset to 0
		while(OVFCount <= 25)
		{
			TCNT0 = 0;//reset to 0
			while ((TIFR0 & 0x01) == 0)
			{
				PORTB ^= (1<<2);//turn LED on
			}
			TCNT0 = 0;//reset to 0
			TIFR0=0x01;//reset flag
			OVFCount++;//increment counter
		}
		OVFCount = 0;//reset to 0
		TCNT0 = 0;//reset to 0
		while(OVFCount <= 17)
		{
			while ((TIFR0 & 0x01) == 0)
			{
				PORTB |= (1<<2);//turn off LED
			}
			OVFCount++;//increment counter
			TIFR0 = 0x01;//reset flag
			TCNT0 = 0;//reset to 0
		}
    }
}
