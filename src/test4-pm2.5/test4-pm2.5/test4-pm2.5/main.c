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
int a1 = 0,a2 = 0,a;


int main(void)
{	
	
	DDRD = (1 << PORTD6) | (1 << PORTD7);
	
	TCCR2A = (1 << COM2A1) | (1 << WGM20) | (1 << WGM21);
	TIMSK2 = (1 << TOIE2);
	
	OCR2A = (dutyCycle/100.0)*255;
	/*
	TCCR0A = (1 << COM0A1) | (1 << WGM00) | (1 << WGM01);
	TIMSK0 = (1 << TOIE0);
	
	OCR0A = (dutyCycle/100.0)*255.0;
	*/
	setupADC();
	sei();
	
	TCCR2B = (1 << CS20);
	//TCCR0B = (1 << CS00) | (1 << CS02);
	
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
	/*
	if(a == 0){
		a1++;
		if(a1 >= 10){
			a1 = 0;
			a2++;
			if(a2 >= 6){
				PORTD |= (1 << PORTD7);
				a1 = 0;
				a2 = 0;
				a = 1;
			}
		}	
	}else if (a == 1){
		a1++;
		if(a1 >= 10){
			a1 = 0;
			a2++;
			if(a2 >= 6){
				PORTD &= (0 << PORTD7);
				a1 = 0;
				a2 = 0;
				a = 0;
				//startConversion();
			}
		}
	}
	//OCR0A = (dutyCycle/100.0)*255;
	*/
}
ISR(TIMER2_OVF_vect)
{
	if(a == 0){
		PORTD |= (1 << PORTD7);
		a = 1;
		TCNT2 = 250;
	}else if (a == 1){
		PORTD &= (0 << PORTD7);
		a = 0;
		startConversion();
		TCNT2 = 200;
	}
	
}
ISR(ADC_vect)
{
	//OCR0A = dutyCycle/4;
	dutyCycle = ADC;
	//startConversion();
}