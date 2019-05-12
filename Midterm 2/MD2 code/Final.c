#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "i2c_master.h"
#include "uart.h"
#include "apds.h"

FILE str_uart = FDEV_SETUP_STREAM(uart_putchar, NULL , _FDEV_SETUP_WRITE);
char results[256];

int main(void)
{
	uint16_t red = 0, green = 0, blue = 0; //set up variables
	
	i2c_init(); //call i2c init
	init_UART(); //call uart init
	stdout = &str_uart;
	apds_init(); //adps initialization function
	
 	_delay_ms(2000);
	printf("AT\r\n");//at commands	
	_delay_ms(5000);
	printf("AT+CWMODE=1\r\n"); //at commands	
	_delay_ms(5000);
	printf("AT+CWJAP=\"XXXXX\",\"XXXXX\"\r\n");//at commands	
    while (1) 
    {
		_delay_ms(5000);
		printf("AT+CIPMUX=0\r\n");//atcommands
		
		_delay_ms(5000);
		printf("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n");//at commands
		
		_delay_ms(5000);
		readColor(&red, &green, &blue); //reads color
		printf("AT+CIPSEND=104\r\n"); //at command
		printf("GET https://api.thingspeak.com/update?api_key=1V8WUUJNEHZGA9L7&field1=%05u&field2=%05u&field3=%05u\r\n", red, green, blue); //send to thinkspeak
		
		_delay_ms(3000);
    }
}


