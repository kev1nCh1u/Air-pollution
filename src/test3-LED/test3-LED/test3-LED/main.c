/*
 * ADCexample.c
 *
 * Created: 4/13/2013 5:22:48 PM
 *  Author: SAM
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>

double dutyCycle = 0;

int main(void)
{
	DDRD = (1 << PORTD6) | (1 << PORTD5);
	DDRB = (1 << PORTB3);
    
    TCCR0A = (1 << COM0A1) | (1 << COM0B1) | (1 << WGM00) | (1 << WGM01);
	TCCR2A = (1 << COM0A1) | (1 << WGM00) | (1 << WGM01);
    TIMSK0 = (1 << TOIE0);
    
    setupADC();
    
    sei();
    
    TCCR0B = (1 << CS00) | (1 << CS02);
	TCCR2B = (1 << CS00) | (1 << CS02);
    
    while(1)
    {
    	//TODO:: Please write your application code
    }
}

void setupADC()
{
    ADMUX = (1 << REFS0) | (1 << MUX0) | (1 << MUX1);
    ADCSRA = (1 << ADEN) | (1 << ADIE) | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2);
    DIDR0 = (1 << ADC5D);
	
    startConversion();
}

void startConversion()
{
    ADCSRA |= (1 << ADSC);
}

ISR(TIMER0_OVF_vect)
{
	if (dutyCycle < 50 && 0) //green
	{
		OCR0A = 0;
		OCR0B = 20;
		OCR2A = 0;
	}
	else if (dutyCycle < 100 && 0) //yellow
	{
		OCR0A = 15;
		OCR0B = 20;
		OCR2A = 0;
	}
	else if (dutyCycle < 150 && 0) //orange
	{
		OCR0A = 18;
		OCR0B = 20;
		OCR2A = 0;
	}
	else if (dutyCycle < 200 && 1) //red
	{
		OCR0A = 0;
		OCR0B = 0;
		OCR2A = 0;
	}
	else //purple
	{
		OCR0A = 200;
		OCR0B = 0;
		OCR2A = 200;
	}

}

ISR(ADC_vect)
{
	dutyCycle = ADC/4;
	startConversion();
}