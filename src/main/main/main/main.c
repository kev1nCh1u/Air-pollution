/*
 * main.c
 *
 * Created: 2018/12/27 下午 09:44:25
 * Author : bsiotmceh
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

double dutyCycle = 0;
int a1 = 0,a2 = 0,a;


int main(void)
{	
	
	DDRD = (1 << PORTD6) | (1 << PORTD5) | (1 << PORTD3);
	DDRB = (1 << PORTB3) | (1 << PORTB1);
		
	
	
	//計數器0為三色LED控制、1為pm2.5的脈波訊號、2為馬達的控制
	TCCR0A = (1 << COM0A1) | (1 << COM0B1) | (1 << WGM00);
	TCCR1A = (1 << COM1A1) | (1 << COM1A0) | (1 << WGM10);
	TCCR2A = (1 << COM2A1) | (1 << WGM20) | (1 << WGM21);
	TIMSK0 = (1 << TOIE0);
	TIMSK1 = (1 << TOIE1);
	TIMSK2 = (1 << TOIE2);
	
	setupADC();
	
	sei();
	
	TCCR0B = (1 << CS00);
	TCCR1B = (1 << CS10) | (1 << CS12) | (1 << WGM12);
	TCCR2B = (1 << CS20) | (1 << CS21) | (1 << CS22);

	OCR1A = 251;
	
    while(1)
    {
        //TODO:: Please write your application code
		if (dutyCycle < 50 ) //green
		{
			OCR0A = 0;
			OCR0B = 255;
		}
		else if (dutyCycle < 100 ) //yellow
		{	
			OCR0A = 180;
			OCR0B = 247;
		}
		else if (dutyCycle < 150) //orange
		{
			OCR0A = 230;
			OCR0B = 255;
		}
		else if (dutyCycle < 200 ) //red
		{
			OCR0A = 255;
			OCR0B = 0;
		}
		else //purple
		{
			OCR0A = 100;
			OCR0B = 100;
		}
		
    }
}
void setupADC()
{
	
	ADMUX = (1 << REFS0) | (1 << MUX0) | (1 << MUX1);
	ADCSRA = 0xaf;
	//ADCSRA = (1 << ADEN) | (1 << ADIE) | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2) | (1 << ADATE);
	ADCSRB = (1 << ADTS2) | (1 << ADTS1);
	DIDR0 = (1 << ADC3D);
	/*
	ADMUX = (1 << REFS0) | (1 << MUX0) | (1 << MUX1);
	ADCSRA = (1 << ADEN) | (1 << ADIE) | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2);
	DIDR0 = (1 << ADC3D);
	*/
	
	//startConversion();
}

ISR(TIMER1_OVF_vect)
{
	//pm2.5
	TCNT1L = 100;
}

ISR(TIMER2_OVF_vect)
{
	//pwm
	OCR2A = dutyCycle / 13.42 + 13;
}

ISR(ADC_vect)
{
	dutyCycle = ADC/4;
}
ISR(TIMER0_OVF_vect)
{
	
}
