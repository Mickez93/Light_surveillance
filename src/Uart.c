/*
 * Uart.c
 *
 * Created: 2022-11-14 17:36:47
 *  Author: mini0072
 */ 
#include <avr/io.h>
#include <avr/sfr_defs.h>

volatile int test = 0;

void UART_init(void)
{	
	//PORT FÖR TX SÄTTS SOM UTGÅNG
	DDRD = 0xFF;
	//
	UCSR1A = 0;
	UCSR1B = (1<<TXEN0);
	UCSR1C = (1<<UCSZ01)|(UCSZ00);
	//
	UBRR1L = 12;
	UBRR0H = 0;
	
}

void UART_tx(char tecken)
{
	while( (UCSR1A & (1<<UDRE1)) == 0)
	{
		test = 1;
	}
	UDR1 = tecken;
}