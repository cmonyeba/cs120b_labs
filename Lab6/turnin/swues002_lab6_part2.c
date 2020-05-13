/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
// demo: https://youtu.be/Cmn_vTa7Xlo

#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
#include "timer.h"

enum States{Start, One, Two, Three, Wait, W, Fall} State;
void Tick(){
	switch(State){
		case Start:
			State = One;
		break;
		case One:
		 	State = Two;
		break;

		case Two:
			State = Three;
		break;

		case Three:
			State = Wait;
		break;

		case Wait:
                        if(PINA == 0x01){
                                State = Wait;
                        }
                        else{
                                State = W;
                        }
               break;

		case W:
			State = Fall;
		break;

		case Fall:
                        if(PINA == 0x01){
				State = Fall;
                        }
                        else{
                                State = One;
                        }
                break;

		
	}

	switch(State){
		case One:
			if(PINA = 0x01){
				PORTB = PORTB;
			}
			PORTB = 0x01;
		break;
		case Two:
			if(PINA = 0x01){
                                PORTB = PORTB;
                        }

			PORTB = 0x02;
		break;
		case Three:
			if(PINA = 0x01){
                                PORTB = PORTB;
                        }

			PORTB = 0x04;
		break;
		case W:
			if(PINA = 0x01){
                                PORTB = PORTB;
                        }

                        PORTB = 0x02;
                break;

	}
}

int main(void) {
    DDRB = 0xFF; PORTB = 0x00;
    DDRA = 0x00; PORTA = 0xFF;
    TimerSet(300);
    TimerOn();
    State = Start;
    while (1) {
	Tick();
	while(!TimerFlag);
	TimerFlag=0;
    }
    return 1;
}
