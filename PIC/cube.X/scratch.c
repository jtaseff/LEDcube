/* Send data to the PC */
    if (usb_is_configured() &&
            !usb_in_endpoint_halted(2) &&
            !usb_in_endpoint_busy(2) && send) {

        int i;
        unsigned char *buf = usb_get_in_buffer(2);

        for (i = 0; i < 16; i++) {
            buf[i] = char_to_send++;
            if (char_to_send > 'Z')
                char_to_send = 'A';
        }
        buf[i++] = '\r';
        buf[i++] = '\n';
        usb_send_in_buffer(2, i);
    }

    /* Handle data received from the host */
    if (usb_is_configured() &&
            !usb_out_endpoint_halted(2) &&
            usb_out_endpoint_has_data(2)) {
        const unsigned char *out_buf;
        size_t out_buf_len;
        int i;

        /* Check for an empty transaction. */
        out_buf_len = usb_get_out_buffer(2, &out_buf);
        if (out_buf_len <= 0)
            goto empty;

        if (send) {
            /* Stop sendng if a key was hit. */
            send = false;
            send_string_sync(2, "Data send off ('h' for help)\r\n");
        } else if (loopback) {
            /* Loop data back to the PC */

            /* Wait until the IN endpoint can accept it */
            while (usb_in_endpoint_busy(2))
                ;

            /* Copy contents of OUT buffer to IN buffer
             * and send back to host. */
            memcpy(usb_get_in_buffer(2), out_buf, out_buf_len);
            usb_send_in_buffer(2, out_buf_len);

            /* Send a zero-length packet if the transaction
             * length was the same as the endpoint
             * length. This is for demo purposes. In real
             * life, you only need to do this if the data
             * you're transferring ends on a multiple of
             * the endpoint length. */
            if (out_buf_len == EP_2_LEN) {
                /* Wait until the IN endpoint can accept it */
                while (usb_in_endpoint_busy(2))
                    ;
                usb_send_in_buffer(2, 0);
            }

            /* Scan for ~ character to end loopback mode */
            for (i = 0; i < out_buf_len; i++) {
                if (out_buf[i] == '~') {
                    loopback = false;
                    send_string_sync(2, "\r\nLoopback off ('h' for help)\r\n");
                    break;
                }
            }
        } else {
            /* Scan for commands if not in loopback or
             * send mode.
             *
             * This is a hack. One should really scan the
             * entire string. In this case, since this
             * is a demo, assume that the user is using
             * a terminal program and typing the input,
             * all but ensuring the data will come in
             * single-character transactions. */
            if (out_buf[0] == 'h' || out_buf[0] == '?') {
                /* Show help.
                 * Make sure to not try to send more
                 * than 63 bytes of data in one
                 * transaction */
                send_string_sync(2,
                        "\r\nHelp:\r\n"
                        "\ts: send data\r\n"
                        "\tl: loopback\r\n");
                send_string_sync(2,
                        "\tn: send notification\r\n"
                        "\th: help\r\n");
            } else if (out_buf[0] == 's')
                send = true;
            else if (out_buf[0] == 'l') {
                loopback = true;
                send_string_sync(2, "loopback enabled; press ~ to disable\r\n");
            } else if (out_buf[0] == 'n') {
                /* Send a Notification on Endpoint 1 */
                struct cdc_serial_state_notification *n =
                        (struct cdc_serial_state_notification *)
                        usb_get_in_buffer(1);

                n->header.REQUEST.bmRequestType = 0xa1;
                n->header.bNotification = CDC_SERIAL_STATE;
                n->header.wValue = 0;
                n->header.wIndex = 1; /* Interface */
                n->header.wLength = 2;
                n->data.serial_state = 0; /* Zero the whole bit mask */
                n->data.bits.bRxCarrier = 1;
                n->data.bits.bTxCarrier = 1;
                n->data.bits.bBreak = 0;
                n->data.bits.bRingSignal = 0;
                n->data.bits.bFraming = 0;
                n->data.bits.bParity = 0;
                n->data.bits.bOverrun = 0;

                /* Wait for the endpoint to be free */
                while (usb_in_endpoint_busy(1))
                    ;

                /* Send to to host */
                usb_send_in_buffer(1, sizeof (*n));

                send_string_sync(2, "Notification Sent\r\n");
            }
        }
empty:
        usb_arm_out_endpoint(2);
