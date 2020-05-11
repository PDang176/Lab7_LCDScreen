/*	Author: Patrick Dang
 * 	Partner(s) Name: 
 *	Lab Section: 028
 *	Assignment: Lab #7  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include "io.h"
#include "timer.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{Start, Wait_Press, Increment, Decrement, Reset}state;

unsigned char i;
unsigned char LED;

void Tick(){
	//Transitions
	switch(state){
		case Start:
			state = Wait_Press;
			LED = 0x00;
			break;
		case Wait_Press:
			if((~PINA & 0x01) && (~PINA & 0x02)){
                                state = Reset;
                        }
                        else if(~PINA & 0x01){
                                state = Increment;
                                i = 0;
                        }
                        else if(~PINA & 0x02){
                                state = Decrement;
                                i = 0;
                        }
                        else{
                                state = Wait_Press;
                        }
                        break;
		case Increment:
			if((~PINA & 0x01) && (~PINA & 0x02)){
                                state = Reset;
                        }
                        else if(~PINA & 0x01){
                                state = Increment;
                        }
                        else if(~PINA & 0x02){
                                state = Decrement;
                                i = 0;
                        }
                        else{
                                state = Wait_Press;
                        }
                        break;
		case Decrement:
			if((~PINA & 0x01) && (~PINA & 0x02)){
                                state = Reset;
                        }
                        else if(~PINA & 0x01){
                                state = Increment;
                                i = 0;
                        }
                        else if(~PINA & 0x02){
                                state = Decrement;
                        }
                        else{
                                state = Wait_Press;
                        }
                        break;
		case Reset:
			if((~PINA & 0x01) && (~PINA & 0x02)){
				state = Reset;
			}
			else if(~PINA & 0x01){
				state = Increment;
				i = 0;
			}
			else if(~PINA & 0x02){
				state = Decrement;
				i = 0;
			}
			else{
				state = Wait_Press;
			}
			break;
		default:
			state = Start;
			break;
	}

	//State Actions
	switch(state){
		case Start:
			break;
		case Wait_Press:
			break;
		case Increment:
			LED = (LED < 0x09 && i == 0) ? LED + 1 : LED;
			i = (i < 10) ? i + 1 : 0;
			break;
		case Decrement:
			LED = (LED > 0x00 && i == 0) ? LED - 1 : LED;
			i = (i < 10) ? i + 1 : 0;
			break;
		case Reset:
			LED = 0x00;
			break;
		default:
			break;
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
    	
	i = 0;
	LED = 0;

	TimerSet(100);
	TimerOn();
	LCD_init();

    /* Insert your solution below */
    while (1) {
	Tick();
	LCD_ClearScreen();
	LCD_WriteData(LED + '0');
	while(!TimerFlag){}
	TimerFlag = 0;
    }
    return 1;
}
