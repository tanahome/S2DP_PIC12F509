/*
 * S2DP for PIC12F509
 * Copyright (c) 2018  tana-home@outlook.com
 *
 * This software is released under the MIT License.
 * http://opensource.org/licenses/mit-license.php
 *
 */

#include <xc.h>

#define _XTAL_FREQ 4000000  

#pragma config CP    = OFF
#pragma config MCLRE = OFF
#pragma config WDT   = OFF
#pragma config OSC   = IntRC

////////////////////////////////

#define TRISGPIO_DEFAULT 0b111110 // set all pins input except GP0

#define GP_CLOCK  GP1
#define GP_RESET_ GP2
#define GP_WP_    GP4
#define GP_DATA   GP5

#define N_CLOCK  1
#define N_RESET_ 2
#define N_WP_    4
#define N_DATA   5

#define TRIS_INPUT  1
#define TRIS_OUTPUT 0

#define PROTECTED   0
#define UNPROTECTED 1

#define RST_ENABLED  0
#define RST_DISABLED 1

////////////////////////////////
// Customizable

#define PRE_UNLOCK_DELAY 0 // msec

#define RST_POLLING_DELAY 10 // msec
#define POST_SYSRST_DELAY 100 // msec

#define CLKTD 0 // clock switching delay after DAT bit changing (msec)
#define CLKTH 5 // high duration (msec)
#define CLKTL 5 // low duration (msec) / CLKTD must be smaller than CLKTL

#define DATALEN 16
#define DATA {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}

void main()
{
    const unsigned char data[DATALEN] = DATA;

    OPTION = 0b10000000;
    TRISGPIO = TRISGPIO_DEFAULT;
    GPIO = 0x00;

    // wait system reset release
    while (GP_RESET_ == RST_DISABLED)
        __delay_ms(RST_POLLING_DELAY);
    
#if PRE_UNLOCK_DELAY > 0
    __delay_ms(PRE_UNLOCK_DELAY);
#endif
    
    // change GPIO direction to output
    TRISGPIO = TRISGPIO_DEFAULT ^ ((1 << N_DATA ) | (1 << N_CLOCK) | (1 << N_RESET_) | (1 << N_WP_));

    // disable write protection
    GP_WP_ = UNPROTECTED;
    // enable reset
    GP_RESET_ = RST_ENABLED;
    GP_DATA  = 0;
    GP_CLOCK = 0;

#if POST_SYSRST_DELAY > 0
    __delay_ms(POST_SYSRST_DELAY);
#endif
    
    // program data
    for (int i = 0; i < DATALEN; i++) {
        for (int b = 7; b >= 0; b--) {
            GP_DATA = (data[i] >>  b) & 0x01;
#if CLKTD > 0
            __delay_ms(CLKTD);
#endif
            GP_CLOCK = 1;
            __delay_ms(CLKTH);
            GP_CLOCK = 0;
            __delay_ms(CLKTL - CLKTD);
        }
    }

    // change GPIO direction to nput
    TRISGPIO = TRISGPIO_DEFAULT;
    
    SLEEP();
}
