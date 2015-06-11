/* 
 * File:   oled_graphics.h
 * Author: John
 *
 * Created on April 12, 2015, 6:34 PM
 */

#ifndef OLED_GRAPHICS_H
#define	OLED_GRAPHICS_H

//#ifndef	WIDTH
//#define WIDTH 128 //display width in bits
//#define HEIGHT 64 //display height, in bits
//#endif

#include "oled_control_i2c.h"

void oled_init();
void oled_command(unsigned char cmd);
void oled_update();
void oled_clear_buffer();
void oled_clear_screen();
void oled_pixel(int row, int col, char val);
void oled_draw_char(int xpos, int ypos, char fontwd, unsigned char c, char color);
void oled_draw_string(int xpos, int ypos, char * s, char color);
void oled_draw_hline(int x1, int x2, int ypos, char color);
void oled_draw_vline(int xpos, int y1, int y2, char color);
void oled_draw_line(int x1, int x2, int y1, int y2, char color);
void oled_draw_rect(int x1, int x2, int y1, int y2, char color);

#endif	/* OLED_GRAPHICS_H */

