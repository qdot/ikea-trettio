#include <avr/io.h>
#include <avr/interrupt.h>

#define FOSC 10000000 // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

void USART_Init( unsigned int ubrr)
{
// Set baud rate
	DDRB = 0xff;
//	PORTB = 0x0;
	DDRD = (1<<4) | (1<<5);
	UBRRH = (unsigned char)(ubrr>>8);
	UBRRL = (unsigned char)ubrr;
	UCSRB = (1<<RXEN);
	UCSRC = (1<<URSEL)|(1<<USBS)|(3<<UCSZ0);

	//OCRA: Fast PWM MOD (WGM01 | WGM00)
	//We don't turn PWM on until we get a message telling use to do so.
	TCCR0 = _BV(WGM01) | _BV(WGM00) | _BV(CS02);

	TCCR1A = _BV(WGM10);
	TCCR1B = _BV(WGM12) | _BV(CS12);
	OCR0 = 0x0;
	OCR1AL = 0x0;
	OCR1BL = 0x0;
}

int main()
{
	USART_Init ( MYUBRR );
	int light, speed;
	while(1)
	{
		while ( !( UCSRA & (1<<RXC)) );
		light = UDR;
		while ( !( UCSRA & (1<<RXC)) );
		speed = UDR;
		if(light == 0)
		{
			if(!speed) 
			{
				TCCR0 &= ~(_BV(COM01));
				continue;
			}
			TCCR0 |= _BV(COM01);
			OCR0 = speed;
			continue;
		}
		else if (light == 1) 
		{
			if(!speed) 
			{
				TCCR1A &= ~(_BV(COM1A1));
				continue;
			}
			TCCR1A |= _BV(COM1A1);
			OCR1AL = speed;
			continue;
		}
		else if (light == 2) 
		{
			if(!speed) 
			{
				TCCR1A &= ~(_BV(COM1B1));
				continue;
			}
			TCCR1A |= _BV(COM1B1);
			OCR1BL = speed;
			continue;
		}
	}
	return 0;
}

/*
		if(light == 0)
		{
			if(!speed) 
			{
				TCCR0 &= ~(_BV(COM01));
				continue;
			}
			TCCR0 |= _BV(COM01);
			OCR0 = speed;
			continue;
		}
		else if (light == 1) 
		{
			if(!speed) 
			{
				TCCR1A &= ~(_BV(COM1A1));
				continue;
			}
			TCCR1A |= _BV(COM1A1);
			OCR1AL = speed;
			continue;
		}
		else if (light == 2) 
		{
			if(!speed) 
			{
				TCCR1A &= ~(_BV(COM1B1));
				continue;
			}
			TCCR1A |= _BV(COM1B1);
			OCR1BL = speed;
			continue;
		}
	}
*/
