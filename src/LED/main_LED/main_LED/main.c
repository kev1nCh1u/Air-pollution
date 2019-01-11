/*
 * main_LED.c
 *
 * Created: 2018/12/30 下午 10:16:15
 * Author : bsiotmceh
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>

double dutyCycle = 0;

int main(void)
{
	DDRD = (1 << PORTD6) | (1 << PORTD5);
	DDRB = (1 << PORTB3);
	DDRC = 0x00;
	PORTC |= 0x07;
	
	TCCR0A = (1 << COM0A1) | (1 << COM0B1) | (1 << WGM00) ;
	TCCR2A = (1 << COM2A1) | (1 << WGM20);
	TIMSK0 = (1 << TOIE0);
	//TIMSK2 = (1 << TOIE2);
	
	sei();
	
	TCCR0B = (1 << CS00) | (1 << CS02);
	TCCR2B = (1 << CS20) | (1 << CS22);
	
	while(1)
	{
		if ((PINC & 0x07)==0x00) //green
		{
			OCR0A = 0;
			OCR0B = 255;
			OCR2A = 0;
		}
		else if ((PINC & 0x07)==0x01)//yellow
		{
			OCR0A = 180;
			OCR0B = 247;
			OCR2A = 0;
		}
		else if ((PINC & 0x07)==0x02)//orange
		{
			OCR0A = 230;
			OCR0B = 255;
			OCR2A = 0;
		}
		else if ((PINC & 0x07)==0x03) //red
		{
			OCR0A = 255;
			OCR0B = 0;
			OCR2A = 0;
		}
		else //purple
		{
			OCR0A = 205;
			OCR0B = 0;
			OCR2A = 255;
		}
	}
}




