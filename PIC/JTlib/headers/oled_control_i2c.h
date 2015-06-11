/* 
 * File:   oled_control_i2c.h
 * Author: John
 *
 * Created on April 11, 2015, 8:14 PM
 *
 * source: 433 reference and files
 * 
 */

// bare-bones driver for interfacing with the SSD1306 OLED display via I2C
// not fully featured, just demonstrates basic operation
// note that resetting the PIC does not perform a reset on the OLED display, only power cycling does

// this is an intermediate layer for interfacing with the OLED
// main graphics functionality in OLED_GRAPHICS

#ifndef OLED_CONTROL_I2C_H
#define OLED_CONTROL_I2C_H

#include "i2c_master.h"

#define WIDTH 128 //display width in bits
#define HEIGHT 64 //display height, in bits

void display_init(); // initialize I2C2

void display_command(unsigned char cmd); // issue a command to the display

void display_draw();                       // draw the buffer in the display

void display_clear();                     // clear the display

void display_pixel_set(int row, int col, int val); // set the pixel at the given row and column

int display_pixel_get(int row, int col);  // get the pixel at the given row and column

#endif	/* OLED_CONTROL_I2C_H */

