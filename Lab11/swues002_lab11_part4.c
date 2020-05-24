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
#include "bit.h"
#include "timer.h"
#include "keypad.h"
#include "io.h"

typedef struct _task{
	signed char state;
	unsigned long int period;
	unsigned long int elapsedTime;
	int(*TickFct)(int);
} task;

unsigned char flag=0;
unsigned char i=0;

enum SM1_States {SM1_Start, SM1_Wait, SM1_Press};

int SM1_Tick(int state){
	unsigned char key = GetKeypadKey();
	switch(state){
		case SM1_Start:state=SM1_Wait;break;
		case SM1_Wait:
			       if(key!='\0'){
				       state=SM1_Press;
			       }break;
		case SM1_Press:
			       if(key=='\0'){
				       state=SM1_Wait;
			       }else{
				       state=SM1_Press;
			       }break;
		default:state=SM1_Wait;break;
	}
	switch(state){
		case SM1_Wait:
			key=0x1F;
			flag=0;break;
		case SM1_Press:
			switch(key){
				case '\0':break;
				case '0':LCD_WriteData('0');flag=1;break;
				case '1':LCD_WriteData('1');flag=1;break;
				case '2':LCD_WriteData('2');flag=1;break;
				case '3':LCD_WriteData('3');flag=1;break;
				case '4':LCD_WriteData('4');flag=1;break;
				case '5':LCD_WriteData('5');flag=1;break;
				case '6':LCD_WriteData('6');flag=1;break;
				case '7':LCD_WriteData('7');flag=1;break;
				case '8':LCD_WriteData('8');flag=1;PORTB=0x00;break;
				case '9':LCD_WriteData('9');flag=1;PORTB=0x01;break;
				case 'A':LCD_WriteData('A');flag=1;break;
				case 'B':LCD_WriteData('B');flag=1;break;
				case 'C':LCD_WriteData('C');flag=1;break;
				case 'D':LCD_WriteData('D');flag=1;break;
				case '*':LCD_WriteData('*');flag=1;break;
				case '#':LCD_WriteData('#');flag=1;break;
				}			
			break;
	}
	return state;
}

enum Shift_States {Start, Shift};

int Shift_Tick(int state){
	switch(state){
		case Start: state=Shift;break;
		case Shift:state=Shift;break;
		default:state=Shift;break;
	}
	switch(state){
		case Start:break;
		case Shift:if(flag){
				   if(i<16){
					   i++;
					   LCD_Cursor(i);
				   }else{
					   i=0;
					   LCD_Cursor(i);
				   }
			   }break;
	}
	return state;
}


	
int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA=0xF0; PORTA=0x0F;
    DDRB=0xFF; PORTB=0x00;
    DDRC=0xFF; PORTC=0x00;
    DDRD=0xFF; PORTD=0x00;
    static task task1, task2;
    task *tasks[]={&task1, &task2};
    const unsigned short numTasks=sizeof(tasks)/sizeof(task*);

    task1.state=-1;
    task1.period=100;
    task1.elapsedTime=task1.period;
    task1.TickFct=&SM1_Tick;

    LCD_init();
    LCD_DisplayString(1, "Congratulations!");
    task2.state=-1;
    task2.period=100;
    task2.elapsedTime=task2.period;
    task2.TickFct=&Shift_Tick;

   
	
    TimerSet(100);
    TimerOn();

    /* Insert your solution below */
    unsigned short i;
    while (1) {

	for(i=0;i<numTasks;i++){
		if(tasks[i]->elapsedTime==tasks[i]->period){
			tasks[i]->state=tasks[i]->TickFct(tasks[i]->state);
			tasks[i]->elapsedTime=0;
		}
		tasks[i]->elapsedTime+=50;
	}
	while(!TimerFlag);
	TimerFlag=0;
    }
	return 0;
}
   

