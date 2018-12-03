/*
 * test2.c
 *
 * Created: 2018/11/30 上午 10:22:30
 * Author : bsiotmceh
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    /* Replace with your application code */
    DDRB = 0xFF;
	PORTB = 0x00;
	DDRC = 0x00;
	PORTC |= 0b00000011; 
	
	while (1) 
    {
		if((PINC & 0b00000001)==1)
			PORTB |= 0b00100000;
		else if((PINC & 0b00000001)==0)
			PORTB &= 0b11011111;
    }
}

