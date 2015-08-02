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

#include <xc.h>
#include <string.h>
#include "usb.h"
#include "usb_config.h"
#include "usb_ch9.h"
#include "usb_cdc.h"


// actual cube board buttons
#define btn1 PORTBbits.RB7
#define btn2 PORTBbits.RB8
#define btn3 PORTBbits.RB9



// public function definitions
void cubeper_init();

// returns whether usb is connected and configured
char cubeper_usb_configured();

// tasks to be completed every program loop
int cubeper_tasks();

#endif	/* CUBEPER_H */

