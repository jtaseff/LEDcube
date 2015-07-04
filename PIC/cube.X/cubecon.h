/* 
 * File:   cubecon.h
 * Author: John
 *
 * Created on June 11, 2015, 5:04 PM
 */

#ifndef CUBECON_H
#define	CUBECON_H

//public function definitions

void cubecon_update_frame(unsigned char *newframe);
void cubecon_disp_layer(unsigned char *lay);
void cubecon_layerON(unsigned char layer);
void cubecon_init();
void cubecon_disable();
void cubecon_enable();

typedef struct {

    char enable;            // global enable boolean for outputting

    char SPI_stat;          // current SPI out status - tracks sending out each layer
    char layer_stat;        // current layer status - tracks multiplexing each frame

    unsigned char frameCurrent [8][8];      // matrix to store the frame curretly being rendered
    unsigned char frameBuffer [8][8] ;      // matrix to store upcoming frame

    char frame_buffer_is_new;                     // flag whether the current frame is up to date with the buffer

} CUBECON_DATA;

#endif	/* CUBECON_H */

