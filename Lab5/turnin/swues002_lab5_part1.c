/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

//LAB DEMO: https://youtu.be/TTCPP6Msq2M

#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;
    /* Insert your solution below */
    unsigned char button = 0x00;
    unsigned char temp = 0x00;
    unsigned char led = 0x00;
    
    while (1) {
        temp = PINA;
	button = ~temp&0x0F; //buttons
        if(button==0x00){
		led = 0x40;
	}
	if(button==0x01 || button==0x02){
		led = 0X60;
	}
	if(button==0x03 || button==0x04){
		led = 0x70;
	}
	if(button==0x05 || button==0x06){
		led = 0x38;
	}
	if(button>=0x07 && button<=0x09){
		led = 0x3C;
	}
	if(button>=0x0A && button<=0x0C){
		led = 0x3E;
	}
	if(button>=0x0D && button<=0x0F){
		led = 0x3F;
	}
	PORTC = led;
    }
    return 1;
}
