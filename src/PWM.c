/*
 * PWM.c
 *
 * Created: 3/20/2013 9:29:11 PM
 *  Author: SAM
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

double dutyCycle = 0;

int main(void)
{	
	DDRD = (1 << PORTD6);
	
	TCCR0A = (1 << COM0A1) | (1 << WGM00) | (1 << WGM01);
	TIMSK0 = (1 << TOIE0);
	
	OCR0A = (dutyCycle/100.0)*255.0;
	
	sei();
	
	TCCR0B = (1 << CS00) | (1 << CS02);
	
    while(1)
    {
        //TODO:: Please write your application code
		_delay_ms(100);
		
		dutyCycle += 10;
		
		if(dutyCycle > 100)
		{
			dutyCycle = 0;
		}						
    }
}

ISR(TIMER0_OVF_vect)
{
	OCR0A = (dutyCycle/100.0)*255;
}