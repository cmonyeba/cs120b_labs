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
#include "pwm.h"

enum States {Start, Rest, Up, Down, Toggle, Fall} state;
unsigned char button=0x00;
double freq[]={261.63,293.66,329.63,349.23,392.00,440.00,493.88,523.25};
unsigned char temp=0x00;
unsigned char i = 0x00;
unsigned char toggle=0x00;
void tick(){
	temp = PINA;
	button = ~PINA&0x07;

	switch(state){//transitions
		case Start: state=Rest; break;
                case Rest:
			    if(button==0x01){
				    state = Up;
			    }
			    if(button==0x02){
				    state = Down;
			    }
			    if(button==0x04){
				    state = Toggle;
			    }
			    if(button==0x00||button==0x03||button==0x05||button==0x06){
				    state = Rest;
			    }
			    break;
		case Up: state=Fall; break;
		case Down: state=Fall; break;
		case Toggle: state=Fall; break;
		case Fall:
			     if(button==0x00){
				     state=Rest;
			     }
			     else{
				     state=Fall;
			     }
			     break;
		default: state=Start; break;
	}//transitions

	switch(state){//state actions
		case Rest:
			set_PWM(freq[i]);
			break;
		case Up:
			if(i<7){
			i++;
			set_PWM(freq[i]);
			}else{
				set_PWM(freq[i]);
			}
			break;
		case Down:
			if(i>0){
			i--;
			set_PWM(freq[i]);
			}else{
				set_PWM(freq[i]);
			}
			break;
		case Toggle:
			toggle=~toggle;
			if(toggle){
			PWM_off();
			}
			else{
				PWM_on();
			}
			break;
		default:break;
	}//state actions
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA=0x00; PORTA=0xFF;
    DDRB=0x40; PORTB=0x00;
    /* Insert your solution below */
    state=Start;
    PWM_on();
    set_PWM(1);
    while (1) {
	tick();
    }
    return 1;
}
