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

enum States {Start, Wait, Inc, Dec, Reset} state;
unsigned char value = 0;
unsigned char b = 0;
void tick(){
	b=~PINA&0x03; //buttons
	switch(state){//transitions
		case Start: state=Wait; break;
		case Wait: 
			    if(b==0x01){
				    state=Inc;
			    }else if(b==0x02){
				    state=Dec;
			    }else if(b==0x03){
				    state=Reset;
			    }else{
				    state=Wait;
			    }break;
		case Inc: state=Wait; break;
		case Dec: state=Wait; break;
		case Reset: state=Wait; break;
		default: state=Start; break;
	}//transitions
	switch(state){//action
		case Start: break;
		case Inc: 
			    if(value<9){
				    value++;
				    LCD_ClearScreen();
				    LCD_WriteData(value+'0');
			    }break;
		case Dec:
			    if(value>0){
				    value--;
				    LCD_ClearScreen();
				    LCD_WriteData( value+'0');
			    }break;
		case Reset: value=0; LCD_ClearScreen();  LCD_WriteData(value+'0'); break;
		case Wait: break;
	}//actions
}
int main(void) {
    /* Insert DDR and PORT initializations */
    DDRC = 0xFF; PORTC = 0x00;
    DDRD = 0xFF; PORTD = 0x00;
    DDRA = 0x00; PORTA = 0xFF;
    LCD_init();
    TimerSet(1000);
    TimerOn();
    /* Insert your solution below */
    while (1) {
	tick();
	while(!TimerFlag);
	TimerFlag=0;
	continue;
    }
    return 1;
}
