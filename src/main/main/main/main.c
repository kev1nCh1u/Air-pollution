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
	
	DDRD = (1 << PORTD6) | (1 << PORTD5) | (1 << PORTD3) | (1 << PORTD4) | (1 << PORTD7);
	DDRB = (1 << PORTB3) | (1 << PORTB0);
	
	//計數器0為三色LED控制、1為pm2.5的脈波訊號、2為馬達的控制
	TCCR0A = (1 << COM0A1) | (1 << COM0B1) | (1 << WGM00);
	TCCR1A = (1 << COM1A1) | (1 << WGM10);
	TCCR2A = (1 << COM2A1) | (1 << COM2B1) | (1 << WGM20) | (1 << WGM21);
	TIMSK0 = (1 << TOIE0);
	TIMSK1 = (1 << TOIE1);
	TIMSK2 = (1 << TOIE2);
	
	setupADC();
	
	sei();
	
	TCCR0B = (1 << CS00);
	TCCR1B = (1 << CS10) | (1 << CS12) | (1 << WGM12);
	TCCR2B = (1 << CS20) | (1 << CS22);

	OCR1A = 103;
	
    while(1)
    {
        //TODO:: Please write your application code
		if (dutyCycle < 50 ) //green
		{
			PORTD &= 0 << PORTD4;
			PORTD &= 0 << PORTD7;
			PORTB &= 0 << PORTB0;
		}
		else if (dutyCycle < 100 ) //yellow
		{
			PORTD |= 1 << PORTD4;
			PORTD &= 0 << PORTD7;
			PORTB &= 0 << PORTB0;
		}
		else if (dutyCycle < 150) //orange
		{
			PORTD &= 0 << PORTD4;
			PORTD |= 1 << PORTD7;
			PORTB &= 0 << PORTB0;
		}
		else if (dutyCycle < 200 ) //red
		{
			PORTD |= 1 << PORTD4;
			PORTD |= 1 << PORTD7;
			PORTB &= 0 << PORTB0;
		}
		else //purple
		{
			PORTD &= 0 << PORTD4;
			PORTD &= 0 << PORTD7;
			PORTB |= 1 << PORTB0;
		}
		//PWM
		OCR2A = dutyCycle / 4 / 13.42 + 13;
    }
}
void setupADC()
{
	ADMUX = (1 << REFS0) | (1 << MUX0) | (1 << MUX1);
	ADCSRA = (1 << ADEN) | (1 << ADIE) | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2);
	DIDR0 = (1 << ADC5D);
}
void startConversion()
{
	ADCSRA |= (1 << ADSC);
}


ISR(TIMER1_OVF_vect)
{
	//pm2.5
	TCNT1L = 100;
	startConversion();
}

ISR(ADC_vect)
{
	dutyCycle = ADC/4;
}
