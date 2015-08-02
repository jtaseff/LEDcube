#include "cubeper.h"
#include <xc.h>
#include <plib.h>
#include <string.h>


#define USB_USE_INTERRUPTS

///////////////////////
// private functions //
///////////////////////
void cubeper_usb_init();

void cubeper_init() {


    //    // setup board for USB
    //    U1PWRCbits.USBPWR = 1;      // U1 power on
    //    U1IRCLR = 0xFF;             // clear all interrupt flags
    //    U1IESET = 0x0F;             // enable interrupts TRN, SOF, UERR, URST
    //    IFS1bits.USBIF = 0;         // clear USB int flag
    //    IEC1bits.USBIE = 1;         // enable USB interrupt

    cubeper_usb_init();

}



///////////////////////
// USB library stuff //
///////////////////////

//public

char cubeper_usb_configured() {
    return (usb_is_configured());
}

static void send_string_sync(uint8_t endpoint, const char *str) {
    char *in_buf = (char*) usb_get_in_buffer(endpoint);

    while (usb_in_endpoint_busy(endpoint))
        ;

    strcpy(in_buf, str);
    /* Hack: Get the length from strlen(). This is inefficient, but it's
     * just a demo. strlen()'s return excludes the terminating NULL. */
    usb_send_in_buffer(endpoint, strlen(in_buf));
}

uint8_t char_to_send = 'A';
bool send = true;
bool loopback = false;
unsigned char *sercubedata[64];
int taskret = 0;

int cubeper_tasks() {

    taskret = 0;

    if (usb_is_configured() &&
            !usb_out_endpoint_halted(2) &&
            usb_out_endpoint_has_data(2)) {

        const unsigned char *out_buf;
        size_t out_buf_len;
        int i;

        /* Check for an empty transaction. */
        out_buf_len = usb_get_out_buffer(2, &out_buf);
        if (out_buf_len <= 0) {
            taskret = 1;
            goto empty;
        }

        if (out_buf_len == 64) {
            //have a full cube of data - display that shit
            send_string_sync(2, "\r\nGot full cube\r\n");
            //memcpy(usb_get_in_buffer(2), sercubedata, 64);
            cubecon_update_frame(usb_get_in_buffer(2));
            taskret = 69;


        } else {
            send_string_sync(2, "\r\nGot partial data\r\n");
            taskret = 2;
        }

empty:
        usb_arm_out_endpoint(2);
    }


    return (taskret);
}

void cubeper_usb_init() {
    SYSTEMConfigPerformance(40000000);

    IPC7bits.USBIP = 4;     // usb interrupt priority
    IPC7bits.USBIS = 1;
    INTCONbits.MVEC = 1;
    INTEnableSystemMultiVectoredInt();
    __asm volatile("ei");

    usb_init();
}

/* Callbacks. These function names are set in usb_config.h. */
void app_set_configuration_callback(uint8_t configuration) {

}

uint16_t app_get_device_status_callback() {
    return 0x0000;
}

void app_endpoint_halt_callback(uint8_t endpoint, bool halted) {

}

int8_t app_set_interface_callback(uint8_t interface, uint8_t alt_setting) {
    return 0;
}

int8_t app_get_interface_callback(uint8_t interface) {
    return 0;
}

void app_out_transaction_callback(uint8_t endpoint) {

}

void app_in_transaction_complete_callback(uint8_t endpoint) {

}

int8_t app_unknown_setup_request_callback(const struct setup_packet *setup) {
    /* To use the CDC device class, have a handler for unknown setup
     * requests and call process_cdc_setup_request() (as shown here),
     * which will check if the setup request is CDC-related, and will
     * call the CDC application callbacks defined in usb_cdc.h. For
     * composite devices containing other device classes, make sure
     * MULTI_CLASS_DEVICE is defined in usb_config.h and call all
     * appropriate device class setup request functions here.
     */
    return process_cdc_setup_request(setup);
}

int16_t app_unknown_get_descriptor_callback(const struct setup_packet *pkt, const void **descriptor) {
    return -1;
}

void app_start_of_frame_callback(void) {

}

void app_usb_reset_callback(void) {

}

/* CDC Callbacks. See usb_cdc.h for documentation. */

int8_t app_send_encapsulated_command(uint8_t interface, uint16_t length) {
    return -1;
}

int16_t app_get_encapsulated_response(uint8_t interface,
        uint16_t length, const void **report,
        usb_ep0_data_stage_callback *callback,
        void **context) {
    return -1;
}

void app_set_comm_feature_callback(uint8_t interface,
        bool idle_setting,
        bool data_multiplexed_state) {

}

void app_clear_comm_feature_callback(uint8_t interface,
        bool idle_setting,
        bool data_multiplexed_state) {

}

int8_t app_get_comm_feature_callback(uint8_t interface,
        bool *idle_setting,
        bool *data_multiplexed_state) {
    return -1;
}

void app_set_line_coding_callback(uint8_t interface,
        const struct cdc_line_coding *coding) {

}

int8_t app_get_line_coding_callback(uint8_t interface,
        struct cdc_line_coding *coding) {
    /* This is where baud rate, data, stop, and parity bits are set. */
    return -1;
}

int8_t app_set_control_line_state_callback(uint8_t interface,
        bool dtr, bool dts) {
    return 0;
}

int8_t app_send_break_callback(uint8_t interface, uint16_t duration) {
    return 0;
}
