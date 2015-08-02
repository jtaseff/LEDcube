/* 
 * File:   main.c
 * Author: John
 *
 * Created on June 11, 2015, 5:01 PM
 */

#include <stdio.h>
#include <stdlib.h>

#include "config_pic32_mx250.h"
#include "cubecon.h"
#include "cubeper.h"
#include "graphics_test_data.h"

/*
 * 
 */
int main(int argc, char** argv) {

    startup();

    
    cubecon_init();     //initialize cube controller

    cubecon_update_frame(cooldata2[0]);
    cubecon_enable();

    cubeper_init();     //initialize peripherals - USB for now
    
    cubecon_update_frame(cooldata1[0]);
    

    char which = 0;

    while (1) {

        cubeper_tasks();

        //        if (cubeper_usb_configured()) {
        //            if (which != 1) {
        //                cubecon_update_frame(cooldata2[0]);
        //            }
        //
        //            which = 1;
        //        }

        if (btn2) {
            if (which != 2) {
                cubecon_update_frame(cooldata1[0]);
            }

            which = 2;
        }

        if (btn3) {
            if (which != 3) {
                cubecon_update_frame(cooldata2[0]);
            }

            which = 3;
        }




    }

    return (EXIT_SUCCESS);
}

