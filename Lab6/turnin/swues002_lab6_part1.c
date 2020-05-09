/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
//Lab Demo: https://youtu.be/ZvIL34WgD-Q

#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
#include "timer.h"

enum States {Start, One, Two, Three} state;
unsigned char i = 0;
void tick(){
	switch(state){//transitions
		case Start: state=One; break;
		case One: state=Two; break;
		case Two: state=Three; break;
		case Three: state=One; break;
		default: state=Start; break;
	}//transition
	switch(state){//state action
		case Start: PORTB = 0x00; break;
		case One: PORTB = 0x01; break;
		case Two: PORTB = 0x02; break;
		case Three: PORTB = 0x04; break;
	}//stateaction
}

int main(void) {
    DDRB = 0xFF; PORTB = 0x00;
    TimerSet(1000);
    TimerOn();
    while (1) {
	tick();
	while(!TimerFlag);
	TimerFlag=0;
    }
    return 1;
}
