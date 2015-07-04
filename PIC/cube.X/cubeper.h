/* 
 * File:   cubeper.h
 * Author: John
 *
 * 
 * Functions to control peripherals of cube - buttons, displays, comms
 *
 */

#ifndef CUBEPER_H
#define	CUBEPER_H

// debug breadboard LEDs and buttons for quick access
//#define btn1 PORTBbits.RB2
//#define btn2 PORTBbits.RB3
//#define LED1 LATBbits.LATB7
//#define LED2 LATBbits.LATB15

// actual cube board buttons
#define btn1 PORTBbits.RB7
#define btn2 PORTBbits.RB8
#define btn3 PORTBbits.RB9


// public function definitions
void cubeper_init();



#endif	/* CUBEPER_H */

