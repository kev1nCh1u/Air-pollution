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
    
    TCCR0A = (1 << COM0A1) | (1 << COM0B1) | (1 << WGM00) ;
	TCCR2A = (1 << COM2A1) | (1 << WGM20);
    TIMSK0 = (1 << TOIE0);
    
    setupADC();
    
    sei();
    
    TCCR0B = (1 << CS00) ;
	TCCR2B = (1 << CS20) ;
    
    while(1)
    {
    	//TODO:: Please write your application code
						if (dutyCycle < 50 ) //green
						{
							OCR0A = 0;
							OCR0B = 255;
							OCR2A = 0;
						}
						else if (dutyCycle < 100 ) //yellow
						{
							OCR0A = 180;
							OCR0B = 247;
							OCR2A = 0;
						}
						else if (dutyCycle < 150) //orange
						{
							OCR0A = 230;
							OCR0B = 255;
							OCR2A = 0;
						}
						else if (dutyCycle < 200 ) //red
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

void setupADC()
{
    ADMUX = (1 << REFS0) | (1 << MUX0) | (1 << MUX1);
    ADCSRA = (1 << ADEN) | (1 << ADIE) | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2);
    DIDR0 = (1 << ADC3D);
	
    startConversion();
}

void startConversion()
{
    ADCSRA |= (1 << ADSC);
}

ISR(TIMER0_OVF_vect)
{


}

ISR(ADC_vect)
{
	dutyCycle = ADC/4;
	startConversion();
}