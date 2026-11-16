/*
 * File:   main.c
 * Author: raleigh
 *
 * Created on November 9, 2026, 6:25 PM
 */


#include "xc.h"

#include "display.h"

#pragma config ICS = PGx1          // Comm Channel Select (Emulator EMUC1/EMUD1 pins are shared with PGC1/PGD1)
#pragma config FWDTEN = OFF        // Watchdog Timer Enable (Watchdog Timer is disabled)
#pragma config GWRP = OFF          // General Code Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF           // General Code Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = OFF        // JTAG Port Enable (JTAG port is disabled)
#pragma config POSCMOD = NONE           // Primary Oscillator Select (Primary oscillator disabled. 
#pragma config I2C1SEL = PRI       // I2C1 Pin Location Select (Use default SCL1/SDA1 pins)
#pragma config IOL1WAY = OFF       // IOLOCK Protection (IOLOCK may be changed via unlocking seq)
#pragma config OSCIOFNC = ON       // OSC2/CLKO/RC15 functions as port I/O (RC15)
#pragma config FCKSM = CSECME      // Clock Switching and Monitor (Clock switching is enabled, 
#pragma config FNOSC = FRCPLL      // Oscillator Select (Fast RC Oscillator with PLL module (FRCPLL))

void setup(void) {
    CLKDIVbits.RCDIV = 0;
    AD1PCFG = 0x9fff;

    display_init();
}

uint16_t colors[3] = {0xF800, 0x07E0, 0x001F};

int main(void) {
    setup();

    int count = 0;
    while(1){
        display_clear(colors[count]);
        count = (count + 1) % 3;
    };
    return 0;
}
