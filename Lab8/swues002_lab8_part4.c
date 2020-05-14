/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
void ADC_init(){
	ADCSRA |= (1<<ADEN) | (1<<ADSC) | (1<<ADATE);
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA=0x00; PORTA=0xFF;
    DDRB=0xFF; PORTB=0x00;
    DDRD=0xFF; PORTD=0x00;
    /* Insert your solution below */
    ADC_init();
    unsigned short x;
    while (1) {
	x=ADC;
	if(x>175){
		PORTB=0x80;
	}
	if(x>150){
		PORTB=0x40;
	}
	if(x>125){
                PORTB=0x20;
        }
        if(x>100){
                PORTB=0x10;
        }
	if(x>75){
                PORTB=0x08;
        }
        if(x>50){
                PORTB=0x04;
        }
        if(x>25){
                PORTB=0x02;
        }
        if(x>0){
                PORTB=0x01;
        }


    }
    return 1;
}
