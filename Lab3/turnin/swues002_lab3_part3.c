/*	Author: swues002
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

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF; //input
    DDRC = 0xFF; PORTC = 0x00; //output
    /* Insert your solution below */
	
    unsigned char level = 0x00;
    unsigned char sensor = 0x00;
    unsigned char temp = 0x00; //to check for seatbelt

    while (1) {
	level = PINA & 0x0F;
	temp = PINA & 0x30;  //keep inputs get rid of everything else
	if((level & 0x00) == 0){
	    sensor = 0x40;
	}
	if((level == 0x01) || (level == 0x02)){
	    sensor = 0x60;
	}
	if((level == 0x03) || (level == 0x04)){
	    sensor = 0x70;
	}
	if((level == 0x05) || (level == 0x06)){
	    sensor = 0x38;
	}
	if((level >= 0x07) && (level <= 0x09)){
	    sensor = 0x3C;
	}
	if((level >= 0x0A) && (level <= 0x0C)){
	    sensor = 0x3E;
	}
	if((level >= 0x0D) && (level <= 0x0F)){
	    sensor = 0x3F;
	}
	if(temp == 0x30){
	    sensor = sensor | 0x80;  //turn on light if seat not on
	}
	PORTC = sensor;
    }
    return 1;
}
