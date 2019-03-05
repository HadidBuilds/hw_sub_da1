/*
 * DA2A_taskoneC.c
 *
 * Created: 3/4/2019 8:27:36 PM
 * Author : becerri2
 */ 

#include <avr/io.h>


int main(void)
{
	TCCR1B = 5; //set prescalar as 1024
	//set port b 
	DDRB |= (1<<2); 
	PORTB |= (1<<2);
	DDRB |= (1<<5); 
	PORTB |= (1<<5);
	while(1)
	{
		//reset timer1
		TCNT1 = 0;
		while(TCNT1 != 4687)
		{
			//DELAY
		}
		
		//Toggle pb.2 
		PORTB ^= (1<<2);
		
		//reset timer2
		TCNT1 = 0;
		while(TCNT1 != 6874)
		{
			//Delay
		}
		//toggle pb.2
		PORTB ^= (1<<2);
	}
	return 0;
}

