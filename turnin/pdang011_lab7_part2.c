/*	Author: Patrick Dang
 * 	Partner(s) Name: 
 *	Lab Section: 028
 *	Assignment: Lab #7  Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *	
 *	Video Link: https://drive.google.com/file/d/16tdfKeN-y7VlFOQa3QEzwfQVy5bI89lL/view?usp=sharing
 */
#include <avr/io.h>
#include "io.h"
#include "timer.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States{Start, LED_0, LED_1, LED_2, Pause_Wait, Pause_Released}state;

unsigned char score;
unsigned char next;
unsigned char released;

void Tick(){
	//Transitions
	switch(state){
		case Start:
			state = LED_0;
			released = 0x01;
			break;
		case LED_0:
			if((~PINA & 0x01) && released){
                                state = Pause_Wait;
                                score = (score > 0x00) ? score - 1 : score;
                        }
                        else{
                                state = LED_1;
                        }
			next = LED_2;
			released = (~PINA & 0x01) ? 0x00 : 0x01;
			break;
		case LED_1:
			if((~PINA & 0x01) && released){
				state = Pause_Wait;
				score = (score < 0x09) ? score + 1 : score;
			}
			else{
				state = next;
			}
			released = (~PINA & 0x01) ? 0x00 : 0x01;
			break;
		case LED_2:
			if((~PINA & 0x01) && released){
                                state = Pause_Wait;
                                score = (score > 0x00) ? score - 1 : score;
                        }
                        else{
                                state = LED_1;
                        }
			next = LED_0;
			released = (~PINA & 0x01) ? 0x00 : 0x01;
			break;
		case Pause_Wait:
			state = (~PINA & 0x01) ? Pause_Wait : Pause_Released;
			break;
		case Pause_Released:
			if(~PINA & 0x01){
				state = Start;
				released = 0x00;
			}
			else{
				state = Pause_Released;
			}
			break;
		default:
			break;
	}

	//State Actions
	switch(state){
		case Start:
		case LED_0:
			PORTB = 0x01;
			break;
		case LED_1:
			PORTB = 0x02;
			break;
		case LED_2:
			PORTB = 0x04;
			break;
		case Pause_Wait:
		case Pause_Released:
		default:
			break;
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
    	
	score = 0x05;

	TimerSet(300);
	TimerOn();
	LCD_init();

    /* Insert your solution below */
    while (1) {
	Tick();
	if(score >= 9){
		LCD_DisplayString(1, "Victory!");
	}
	else{
		LCD_ClearScreen();
		LCD_WriteData(score + '0');
	}
	while(!TimerFlag){}
	TimerFlag = 0;
    }
    return 1;
}
