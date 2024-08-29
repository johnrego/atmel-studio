/*
 * in_out.c
 *
 * Created: 20/08/2024 19:53:16
 * Author : Jefferson
 */ 

#define F_CPU 16000000

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>


int main(void)
{
    DDRB |= (1<<PB7); // Define o pino 13 como saída
    while (1){
		for (size_t a = 0; a < 5; a++){
			PORTB |= (1<<PB7);
			_delay_ms(500);
			PORTB &= ~(1<<PB7);
			_delay_ms(2000);
		}
		return 0;
    }
}

