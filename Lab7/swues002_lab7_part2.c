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
#include "io.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
#include "timer.h"

enum States {Start, One, Two, Three, Fall, Win, Lose} state;
unsigned char i = 0;
unsigned char cnt = 5;
unsigned char button = 0;
void tick(){
	button = ~PINA&0x01;//Button

	switch(state){//transitions
		case Start: state=One; break;
		case One:
			   if(button){
				   state=Lose;
			   }else{
				  state=Two;
			   } break;
		case Two:
			  if(button){
				  state=Win;
			  }
			  else{
				  state=Three;
			  }
			  break;
		case Three:
			  if(button){
				  state=Lose;
			  }else{
				 state=One;
			  } break;
		case Fall: if(button){
				   state=Fall;
			   }else{
				   state=One;
			   }break;
		case Win: state=Fall; break;
		case Lose: state=Fall; break;
		default: state=Start; break;
	}//transition
	switch(state){//state action
		case Start: i=0x00;PORTB=i; break;
		case One: i=0x01;PORTB=i; break;
		case Two: i=0x02;PORTB=i; break;
		case Three: i=0x04;PORTB=i; break;
	        case Fall: break;
		case Win: if(cnt<=8){
				  cnt++;
				  LCD_ClearScreen();
				  LCD_WriteData(cnt+'0');
			  }
			  else{
				  cnt=5;
				  LCD_ClearScreen();
				  LCD_DisplayString(1, "Winner Winner      Chicky Dinner!");
			  } break;
		case Lose: if(cnt>0){
				   cnt--;
				   LCD_ClearScreen();
				   LCD_WriteData(cnt+'0');
			   }break;
	}//stateaction
}

int main(void) {
    DDRD = 0xFF; PORTD = 0x00;
    DDRC = 0xFF; PORTC = 0x00;
    DDRB = 0xFF; PORTB = 0x00;
    DDRA = 0x00; PORTA = 0xFF;
    TimerSet(300);
    TimerOn();
    LCD_init();
    while (1) {
	tick();
	while(!TimerFlag);
	TimerFlag=0;
    }
    return 1;
}
