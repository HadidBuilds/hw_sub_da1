#define F_CPU 16000000UL
#define BAUD 9600
#define UBRR F_CPU/16/BAUD-1

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void read_adc(void);  //read_adc function prototype
void USART_init(unsigned int value); //USART_init function prototype
void USART_tx_string(char *data); //USART_tx_string function prototype
volatile unsigned int temp; //volatile variable
char outs[256]; //array outs

volatile char received; //volatile variable recieved

int main(void) {

	USART_init(UBRR); // function call USART_init
	_delay_ms(500); // delay

	ADMUX = (0<<REFS1)| // Reference Selection Bits

	(1<<REFS0)| // AVcc - external cap at AREF
	(0<<ADLAR)| // ADC Left Adjust Result
	(0<<MUX2)| // ANalog Channel Selection Bits
	(1<<MUX1)| // ADC2 (PC2 PIN25)
	(0<<MUX0);

	ADCSRA = (1<<ADEN)| // ADC Enable

	(0<<ADSC)| // ADC Start Conversion
	(0<<ADATE)| // ADC Auto Trigger Enable
	(0<<ADIF)| // ADC Interrupt Flag
	(0<<ADIE)| // ADC Interrupt Enable
	(1<<ADPS2)| // ADC Prescaler Select Bits
	(0<<ADPS1)|
	(1<<ADPS0);

	TIMSK1 |= (1<<TOIE1); // enable overflow interrupt
	TCCR1B |= (1<<CS12)|(1<<CS10); // prescaler
	TCNT1 = 49911; //((16MHz/1024)*1)-1 = 15624
	sei(); //interrupt

	while(1)
	{

	}
}

ISR(TIMER1_OVF_vect)
{
	char AT[] = "AT\r\n"; //AT Commands
	char CWMODE[] = "AT+CWMODE=1\r\n"; //Set mode
	char CWJAP[] = "AT+CWJAP=\"XXXXXX\",\"XXXXXXX\"\r\n"; //WIFI and password
	char CIPMUX[] = "AT+CIPMUX=0\r\n";//set mux
	char CIPSTART[] = "AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n";//tcp
	char CIPSEND[] = "AT+CIPSEND=100\r\n";//size

	_delay_ms(2000); //delay
	USART_tx_string(AT); //send commands
	_delay_ms(5000); //delay
	USART_tx_string(CWMODE); //set mode
	_delay_ms(5000);//delay
	USART_tx_string(CWJAP); //connect to Wifi
	_delay_ms(15000);//delay
	USART_tx_string(CIPMUX); //select MUX
	_delay_ms(10000);//delay
	USART_tx_string(CIPSTART);//connect TCP
	_delay_ms(10000);//delay
	USART_tx_string(CIPSEND);//send size
	_delay_ms(5000);//delay

	PORTC^=(1<<5);//portc
	read_adc(); //read ADC
	snprintf(outs,sizeof(outs),"GET https://api.thingspeak.com/update?api_key=82GUOYOQ18PYG7JW&field1=%3d\r\n", temp);// print temp value
	USART_tx_string(outs);//send data
	_delay_ms(10000);//delay
	TCNT1 = 49911; //reset TCNT
}

void USART_init( unsigned int value )
{
	UBRR0H = (unsigned char)(value>>8); //set higher bits of value
	UBRR0L = (unsigned char)value; //set to value
	UCSR0C |= (1<<UCSZ01) | (1 << UCSZ00); //8-bit data
	UCSR0B |= (1 << TXEN0) | (1 << RXEN0)| ( 1 << RXCIE0); // Enable TX & RX
}

//print strings
void USART_tx_string( char *data ) {
	while ((*data != '\0')) {
		while (!(UCSR0A & (1 <<UDRE0)));
		UDR0 = *data;
		data++;
	}
}

unsigned char USART_receive(void) //received data
{
	while(!(UCSR0A & (1<< RXC0))); //while not true
	return received; //return receive value
}

void read_adc(void) {
	unsigned char i =4;//set to 4
	temp = 0; //initialize
	while (i--) {
		ADCSRA |= (1<<ADSC);
		while(ADCSRA & (1<<ADSC));//while true
		temp+= ADC; //add to temp
		_delay_ms(50);//delay
	}
	temp = temp / 8; // Average a few samples
}
