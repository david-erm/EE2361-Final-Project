/*
 * File:   ps2_interface__lib.c
 * Author: raleigh
 *
 * Created on November 15, 2026, 2:38 PM
 */


#include "xc.h"
#include "stdbool.h"


volatile uint8_t buffer[256] = {0};
volatile uint8_t endPos = 0;
volatile uint8_t readPos = 0;

volatile uint8_t currByte = 0;
volatile uint8_t bitPos = 255; //start bit is considered position 255, wraps around to 0-7 for faster interrupt
volatile uint8_t parityCounter = 0; //counts each 1 to make parity detection easier




void ps2_interface_setup(){ //sets up the PS/2 interface
    //LATB7-8 stay low
    _LATB7 = 0;
    _LATB8 = 0;
    
    //TRISB7-8 = 1: PS/2-controlled
    //TRISB7-8 = 0: LOW for sending commands to the PS/2 device
    _TRISB7 = 1;
    _TRISB8 = 1;
    
    //INT0 interrupt setup (RB7)
    _INT0IF = 0;    //clear flag
    _INT0EP = 1;    //trigger on negative edge
    _INT0IP = 6;    //second-highest priority
    _INT0IE = 1;    //enable interrupt
    
    //TMR 5 setup
    TMR5 = 0;
    T5CONbits.TCKPS = 0;
    PR5 = 3999;    //200us
    T5CONbits.TON = 1;
    _T5IP = 7;  //highest interrupt priority
    _T5IE = 0;  //don't enable interrupt for now
    _T5IF = 0;
}

void __attribute__((__interrupt__,__auto_psv__)) _INT0Interrupt(void){  //triggers every negative PS/2 Clock edge
    TMR5 = 0;
    _T5IE = 1;
    
    if (bitPos < 8){
        currByte = currByte | (_RB8 << bitPos++);
        parityCounter++;
    }
    else if (bitPos == 255){
        bitPos++;
    }
    else if (bitPos == 8){  //odd parity bit detection
        parityCounter += _RB8;
        if (!(parityCounter & 1)){  //if no odd parity
            _T5IE = 0;
            currByte = 0;
            bitPos = 255;
        }
        else {
            bitPos++;
        }
    }
    else { //if bitPos == 9
        _T5IE = 0;
        if (_RB8){  //stop bit successful
            buffer[endPos++] = currByte;
        }
        currByte = 0;
        bitPos = 255;
    }
}

void __attribute__((__interrupt__,__auto_psv__)) _T5Interrupt(void){    //only triggers if too much time passes between bits
    _T5IF = 0;
    _T5IE = 0;
    currByte = 0;
    bitPos = 255;
}

uint8_t read_scan_code(void){
    if (readPos == endPos){
        return 0x80;    //unused scan code in PS/2 to signify that the buffer is empty
    }
    else {
        return(buffer[readPos++]);  //return actual scan code otherwise
    }
}