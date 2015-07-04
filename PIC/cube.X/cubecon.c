#include "cubecon.h"
#include <xc.h>
#include <plib.h>


// pin definitions
#define LE LATBbits.LATB0
#define OE1 LATBbits.LATB1
#define OE2 LATAbits.LATA0


// data and variables
CUBECON_DATA conData;

// lookup table for output order of the columns (sinks)
static const char columnsLUT[8] = {7, 6, 5, 4, 0, 1, 2, 3};
// lookup table for output order of layers (sources)
static const char layersLUT[8] = {3, 1, 2, 0, 5, 7, 4, 6};


//private function prototypes
void cubecon_SPI_config();
void cubecon_timers_config();
void cubecon_SM_config();
unsigned char row_reorder(unsigned char row, char colnum);



//////////////////////////////
// public display functions //
//////////////////////////////

void cubecon_update_frame(unsigned char *newframe) {
    memcpy(conData.frameBuffer, newframe, 64);
    conData.frame_buffer_is_new = 1;
}


////////////////////////
// INTERRUPT HANDLERS //
////////////////////////

// T5 interrupt - for changing layers and updating frames, yo
// happens every 256 Hz

void __ISR(_TIMER_5_VECTOR, IPL5SOFT) Timer5_ISR(void) {

    if (conData.enable) {

        // (can still be enabled until we're ready to latch data)

        // send new layer source data
        SPI2BUF = (unsigned char) (0b1 << layersLUT[conData.layer_stat]);

        char col;
        for (col = 0; col < 8; col++) {
            SPI1BUF = row_reorder(conData.frameCurrent[conData.layer_stat][columnsLUT[col]], columnsLUT[col]);
            while (SPI1STATbits.SPITBF) ;
        }
        // latch and enable
        OE2 = 1;            // disable sources then sinks
        OE1 = 1;
        LE = 1;             // latch data
        LE = 0;
        OE2 = 0;            // enable sinks then sources
        OE1 = 0;


        // if this is the last layer
        conData.layer_stat++;
        if (conData.layer_stat > 7) {
            // roll over to new frame
            conData.layer_stat = 0;

            // update frame from buffer, if it has been updated
            if (conData.frame_buffer_is_new) {
                memcpy(conData.frameCurrent, conData.frameBuffer, 64);
                conData.frame_buffer_is_new = 0;
            }
        }


    }

    IFS0bits.T5IF = 0;
    //service interrupt flag
}



//////////////////////////////
// INITIALIZATION FUNCTIONS //
//////////////////////////////

void cubecon_init() {
    // Ports config
    ANSELACLR = 0b11;           // ANSEL off A0 and A1
    ANSELBCLR = 0xF00F;         // ANSEL off B0, B1, B13, B14 for LE OE SDO SCK
    TRISACLR = 0b11;            // TRIS output on A0 and A1 for OE2
    TRISBCLR = 0xF00F;          // TRIS output on B0 and B1 for LE and OE1

    LE = 0;                     // turn off LE
    OE1 = 1;                    // turn on OE - default off state
    OE2 = 1;                    // off state

    conData.enable = 0;

    cubecon_SM_config();        // initialize state machine
    cubecon_SPI_config();       // initialize the SPI modules and interrupt system
    cubecon_timers_config();    // initialize timing system

    cubecon_layerON(99);        //send anything to turn sources off
}

void cubecon_SPI_config() {


    // SPI 1 config
    RPB13Rbits.RPB13R = 0b0011; // output pin select for SDO1
    SPI1CON = 0;                // turn off the spi module and reset it
    SPI1CONbits.DISSDI = 1;     //disable the SDI, not using it
    SPI1BUF;                    // clear the rx buffer by reading from it
    SPI1BRG = 0x0;              // baud rate to 5MHz [SPI1BRG = (40000000/(2*desired))-1]
    SPI1STATbits.SPIROV = 0;    // clear the overflow bit
    SPI1CONbits.CKE = 1;      // data changes when clock goes from active to inactive - NOPE
    SPI1CONbits.MSTEN = 1;      // master operation

    SPI1CONbits.ON = 1;         // turn on SPI1

    // SPI 2 config
    RPA1Rbits.RPA1R = 0b0100;   // output pin select for SDO2
    SPI2CON = 0;                // turn off the spi module and reset it
    SPI2CONbits.DISSDI = 1;     //disable the SDI, not using it
    SPI2BUF;                    // clear the rx buffer by reading from it
    SPI2BRG = 0x0;              // baud rate to 5MHz [SPI1BRG = (40000000/(2*desired))-1]
    SPI2CONbits.CKE = 1;        // data changes 
    SPI2STATbits.SPIROV = 0;    // clear the overflow bit
    SPI2CONbits.MSTEN = 1;      // master operation
    SPI2CONbits.ON = 1;         // turn on SPI1


}

void cubecon_timers_config() {
    T5CON = 0;                  // disable timer
    T5CONbits.TCKPS = 0b110;    // prescale 1:256
    PR5 = 1000;                 // period = (2000 + 1) * 256ps * 10,000,000 PBclk = 312.5 Hz
    TMR5 = 0;                   // reset timer

    IPC5bits.T5IP = 5;          // priority 5
    IFS0bits.T5IF = 0;          // clear int flag
    IEC0bits.T5IE = 1;          // enable interrupt

    T5CONbits.ON = 1;


    INTEnableSystemMultiVectoredInt();
}

void cubecon_SM_config() {
    // insert state machine here?
}



///////////////////////////
// RAW DISPLAY FUNCTIONS //
///////////////////////////

// permutes bits for each row, depending on wiring
// generated with online permutation generator

unsigned char row_reorder(unsigned char row, char colnum) {
    if (colnum & 0b1) { //even number column
        return ((row & 0x00000010) << 1)
                | ((row & 0x00000004) << 4)
                | ((row & 0x00000001) << 7)
                | ((row & 0x00000080) >> 4)
                | ((row & 0x00000020) >> 3)
                | ((row & 0x00000048) >> 2)
                | ((row & 0x00000002) >> 1);
    } else { //odd number column, just backwards
        return (row & 0x00000084)
                | ((row & 0x00000020) << 1)
                | ((row & 0x00000008) << 2)
                | ((row & 0x00000003) << 3)
                | ((row & 0x00000040) >> 6)
                | ((row & 0x00000010) >> 3);
    }
}

void cubecon_disp_layer(unsigned char *lay) {
    OE1 = 1;

    //loop thru and output each column
    //uses coltable LUT to order the columns
    //uses row_reorder to permute each row
    char col;
    for (col = 0; col < 8; col++) {
        SPI1BUF = row_reorder(lay[columnsLUT[col]], columnsLUT[col]);
        while (SPI1STATbits.SPITBF) ;
    }

    LE = 1;
    LE = 0;
    OE1 = 0;

}


// controller for layers (sources)

void cubecon_layerON(unsigned char layer) {
    OE2 = 1;

    if (layer < 8)
        SPI2BUF = (unsigned char) (0b1 << layersLUT[layer]);
    else
        SPI2BUF = (unsigned char) 0x00;
    while (SPI2STATbits.SPITBF) ;

    //latch data (fast enough to do without pausing
    LE = 1;
    LE = 0;

    if (layer < 8)
        OE2 = 0;        // enable output
}

void cubecon_disable() {
    OE1 = 1;
    OE2 = 1;
    conData.enable = 0;
}

void cubecon_enable() {
    conData.enable = 1;
}

