/*
 * DA3A.c
 *
 * Created: 3/27/2019 5:25:17 PM
 * Author : becerri2
 */

#define F_CPU 16000000UL
#define BAUD 9600

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>

void USART_tx_string( char* data); //prototype for printing string
void USART_init( void ); //prototype for USART_init function
void USART_send(char val); //prototype fo send function

char str[] = "Hello World!"; //string that will be printed
char outs[20];  //array of characters
volatile float tmp = 27.23; //float number


int main(void)
{
	TCCR1B = 5; //setting the prescaler to 1024
	TIMSK1 = (1<<TOIE1); //enable interrupt flag
	TCNT1 = 49911; //set TCNT

	USART_init(); //call function

	sei();//enable interrupt


	while(1)
	{
		//main loop
	}
}

ISR(TIMER1_OVF_vect)
{
	USART_tx_string(str); //pass string to function
	USART_tx_string("\n"); //line feed
	USART_send('7'); //print integer 7
	USART_tx_string("\n"); //line feed
	snprintf(outs,sizeof(outs),"%f\r\n", tmp);// print it
	USART_tx_string(outs); //pass array to function
	USART_tx_string("\n"); //linefeed

	TCNT1 = 49911; //reset tcnt
}

void USART_init( void )
{
	UBRR0H = 0; //set lower bits
	UBRR0L = F_CPU/16/BAUD - 1; //
	UCSR0C = _BV(UCSZ01) | _BV(UCSZ00); /* 8-bit data */
	UCSR0B = _BV(RXEN0) | _BV(TXEN0);   /* Enable RX and TX */
}

//*****************************************
/*Sends some data to the serial port*/
void USART_tx_string(char *data)
{
	while((*data != '\0'))
	{
		while(!(UCSR0A & (1<<UDRE0)));
			UDR0 = *data;
				data++;
	}
}
//*****************************************
void USART_send(char val)
{
/*wait for data to be recieved*/
	while(!(UCSR0A & (1<<UDRE0)));
	 UDR0 = val;
}
