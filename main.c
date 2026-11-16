#include <p24Fxxxx.h>
#include <xc.h>

// PIC24FJ64GA002 Configuration Bit Settings
// CW1: FLASH CONFIGURATION WORD 1 (see PIC24 Family Reference Manual 24.1)
#pragma config ICS = PGx1          // Comm Channel Select (Emulator EMUC1/EMUD1 pins are shared with PGC1/PGD1)
#pragma config FWDTEN = OFF        // Watchdog Timer Enable (Watchdog Timer is disabled)
#pragma config GWRP = OFF          // General Code Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF           // General Code Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = OFF        // JTAG Port Enable (JTAG port is disabled)


// CW2: FLASH CONFIGURATION WORD 2 (see PIC24 Family Reference Manual 24.1)
#pragma config POSCMOD = NONE           // Primary Oscillator Select (Primary oscillator disabled. 
					// Primary Oscillator refers to an external osc connected to the OSC1 and OSC2 pins)
#pragma config I2C1SEL = PRI       // I2C1 Pin Location Select (Use default SCL1/SDA1 pins)
#pragma config IOL1WAY = OFF       // IOLOCK Protection (IOLOCK may be changed via unlocking seq)
#pragma config OSCIOFNC = ON       // OSC2/CLKO/RC15 functions as port I/O (RC15)
#pragma config FCKSM = CSECME      // Clock Switching and Monitor (Clock switching is enabled, 
                                       // Fail-Safe Clock Monitor is enabled)
#pragma config FNOSC = FRCPLL      // Oscillator Select (Fast RC Oscillator with PLL module (FRCPLL))


void __attribute__((__interrupt__,__auto_psv__)) _T1Interrupt(void) {
    _T1IF = 0;
}

void __attribute__((__interrupt__,__auto_psv__)) _T2Interrupt(void) {
    _T2IF = 0;
}

void __attribute__((__interrupt__,__auto_psv__)) _SPI2Interrupt(void) {
    _SPI2IF = 0;
}

void __attribute__((__interrupt__,__auto_psv__)) _INT1Interrupt(void) {
    
}

void setup(void)
{
    CLKDIVbits.RCDIV = 0; 
    AD1PCFG = 0x9fff; 
    TRISBbits.TRISB14 = 1; //input to handle clock from the PS2 keyboard
    TRISBbits.TRISB15 = 1; //input to handle data from the PS2 keyboard

    //set up timer 1
    T1CON = 0;   
    PR1 = 15999;  
    TMR1 = 0;
    T1CONbits.TON = 1;
    _T1IF = 0;
    _T1IE = 1;
    
    //set up timer 2
    T2CON = 0;   
    PR2 = 15999;  
    TMR2 = 0;
    T2CONbits.TON = 1;
    _T2IF = 0;
    _T2IE = 1;
    
    //set up PPS
    __builtin_write_OSCCONL(OSCCON & 0xbf);
    RPOR6bits.RP12R = 10;   //pin RP12 is set to be SDO2
    RPOR6bits.RP13R = 11;   //pin RP13 is set to be SCK2OUT
    RPINR0bits.INT1R = 14;  //pin RP14 is set to external interrupt 1 to handle the clock from the PS2 input
                            //if you wanna change this back to RP7 and INT0, lemme know
                            //cuz I see that you guys are using RB5-RB11 to handle 5V input
    __builtin_write_OSCCONL(OSCCON | 0x40);

    //set up INT1
    _INT1IF = 0;
    _INT1IE = 1;
    _INT1EP = 0; //interrupt on low edge
    IPC5bits.INT1IP = 0b111; //highest priority
    
    //set up SPI2 for LCD display
    SPI2CON1 = 0;
    SPI2CON1bits.MSTEN = 1;
    SPI2CON1bits.MODE16 = 0; //for byte-wide I assume. Is it byte-wide or word-wide?
    SPI2CON1bits.CKE = 1;
    SPI2CON1bits.CKP = 0;
    SPI2CON1bits.SPRE = 0b110;
    SPI2CON1bits.PPRE = 0b11;
    SPI2CON2 = 0;
    
    SPI2STATbits.SISEL = 0b101;
    SPI2STATbits.SPIEN = 1;
    
    _SPI2IF = 0;
    _SPI2IE = 1;
    
}


int main(void)
{
    setup();
    while (1) {               
             
    }
    return 0;
}
