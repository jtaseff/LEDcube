#include <stdio.h>
#include <string.h>
#include "oled_control_i2c.h"
#include "fonts.h"
#include "oled_graphics.h"

void oled_init() {
    display_init();
    oled_clear_screen();
}

void oled_command(unsigned char cmd) {
    display_command(cmd);
}

void oled_update() {
    display_draw(); // update/draw the buffer to the actual screen
}

void oled_clear_buffer() { //clear the buffer
    display_clear();
}

void oled_clear_screen() { //clear the buffer and send to the screen
    display_clear();
    display_draw();
}

void oled_pixel(int row, int col, char val) {
    display_pixel_set(row, col, val);
}

void oled_draw_char(int xpos, int ypos, char fontwd, unsigned char c, char color) {
    // draws a single character to the buffer at the given potition (top left)
    // fontwd allows choosing different font sizes, only 5x8px implemented now
    if (fontwd != 5)
        return;
    int fontht = 8;
    if ((xpos < 0) || // check if char will fit on screeen
            (ypos < 0) ||
            (xpos + fontwd > WIDTH) ||
            (ypos + fontht > HEIGHT)) {
        return;
    }

    int iirow = 0;
    int jjcol = 0;
    int line;
    for (jjcol = 0; jjcol < fontwd; jjcol++) {
        line = font5x8sys[5 * (c - 32) + jjcol]; // grab font data
        for (iirow = 0; iirow < fontht; iirow++) {
            if ((line >> iirow) & 1)
                display_pixel_set(xpos + jjcol, ypos + iirow, ((line >> iirow) & 1) ^ !color);
        }
    }
}

void oled_draw_string(int xpos, int ypos, char * s, char color) {

    // check wrapping - maybe recurse?

    int numchars = strlen(s);  //length of string

    if ((xpos < 0) ||
            (ypos < 0) ||
            (xpos + 6*numchars > WIDTH) ||
            (ypos + 8 > HEIGHT))
        return;

    int strcount;
    for (strcount = 0; strcount < numchars; strcount++) {
        oled_draw_char(xpos + strcount * 6, ypos, 5, s[strcount], color);
        //oled_draw_vline(xpos + strcount * 6)
    }
}

void oled_draw_hline(int x1, int x2, int ypos, char color) {
    if (x1 > x2) {          //swap so we're left to right
        int temp = x2;
        x2 = x1;
        x1 = temp;
    }

    if ((x1 < 0) ||         //make sure we're in bounds
            (x2 > WIDTH-1) ||
            (ypos < 0) ||
            (ypos > HEIGHT-1))
        return;

    for (; x1 <= x2; x1++) {
        display_pixel_set(x1, ypos, color);
    }
}

void oled_draw_vline(int xpos, int y1, int y2, char color) {
    if (y1 > y2) {          //swap so we're left to right
        int temp = y2;
        y2 = y1;
        y1 = temp;
    }

    if ((y1 < 0) ||         //make sure we're in bounds
            (y2 > HEIGHT-1) ||
            (xpos < 0) ||
            (xpos > WIDTH-1))
        return;

    for (; y1 <= y2; y1++) {
        display_pixel_set(xpos, y1, color);
    }
}

void oled_draw_rect(int x1, int x2, int y1, int y2, char color) {
    oled_draw_hline(x1, x2, y1, color);
    oled_draw_hline(x1, x2, y2, color);
    oled_draw_vline(x1, y1, y2, color);
    oled_draw_vline(x2, y1, y2, color);
    
}

void oled_draw_rect_fill(int x1, int x2, int y1, int y2, char color) {
    if (y1 > y2) {
        int temp = y2;
        y2 = y1;
        y1 = temp;
    }
    for (; y1 <= y2; y1++)
    {
        oled_draw_hline(x1, x2, y1, color);
    }
}

void oled_draw_line(int x1, int x2, int y1, int y2, char color) {
    //yeah do that
}

void oled_draw_circle(int xpos, int ypos, int rad, char color) {
    //eventually
}