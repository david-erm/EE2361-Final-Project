#include "display.h"

#include <stdint.h>
#include "xc.h"

#include "delay.h"

void display_pin_config(void) {
    CS = 1;
    DC = 1;
    RST = 1;
    BL = 1;
    
    TRISAbits.TRISA2 = 0; // CS
    TRISAbits.TRISA3 = 0; // DC
    TRISBbits.TRISB4 = 0; // RST
    TRISAbits.TRISA4 = 0; // BL

    TRISBbits.TRISB2 = 0; // SDO
    TRISBbits.TRISB3 = 0; // SCK

    __builtin_write_OSCCONL(OSCCON & 0xbf); // unlock PPS
    RPOR1bits.RP2R = 10; // RP2 = SDO2 
    RPOR1bits.RP3R = 11; // RP3 = SCK2OUT
    RPINR22bits.SCK2R = 3;
    __builtin_write_OSCCONL(OSCCON | 0x40); // lock   PPS
    
    SPI2CON1 = 0;
    SPI2CON1bits.MSTEN = 1;  // master mode
    SPI2CON1bits.MODE16 = 0; // byte mode
    SPI2CON1bits.CKE = 1;
    SPI2CON1bits.CKP = 0;

    SPI2CON1bits.SPRE = 0b111;
    SPI2CON1bits.PPRE = 0b11;

    SPI2CON2 = 0;
    SPI2STAT = 0;
    SPI2STATbits.SISEL = 0b101; // IF set when last bit is shifted out
                                // That means the SPI xfer is complete.
    SPI2STATbits.SPIEN = 1; //enable

    _SPI2IF = 0;
}

void display_cmd(uint8_t dc, uint8_t cmd) {
    DC = dc;    
    CS = 0;
    SPI2BUF = cmd;
    while(!_SPI2IF);
    _SPI2IF = 0;
    int temp = SPI2BUF;
    CS = 1;
}

void display_reset(void) {
    CS = 1;
    delay_ms(100);
    RST = 0;
    delay_ms(100);
    RST = 1;
    delay_ms(130);
}

void display_init(void) {
    display_pin_config();
    display_reset();

    // Ripped the init sequence from official driver
    // https://files.waveshare.com/upload/8/8d/LCD_Module_RPI_code.7z

    display_cmd(0, 0x11); // Sleep out
    delay_ms(120);

    display_cmd(0, 0xCF);
    display_cmd(1, 0x00);
    display_cmd(1, 0xC1);
    display_cmd(1, 0x30);

    display_cmd(0, 0xED);
    display_cmd(1, 0x64);
    display_cmd(1, 0x03);
    display_cmd(1, 0x12);
    display_cmd(1, 0x81);

    display_cmd(0, 0xE8);
    display_cmd(1, 0x85);
    display_cmd(1, 0x00);
    display_cmd(1, 0x79);

    display_cmd(0, 0xCB);
	  display_cmd(1, 0x39);
	  display_cmd(1, 0x2C);
	  display_cmd(1, 0x00);
	  display_cmd(1, 0x34);
	  display_cmd(1, 0x02);

	  display_cmd(0, 0xF7);
	  display_cmd(1, 0x20);

	  display_cmd(0, 0xEA);
    display_cmd(1, 0x00);
    display_cmd(1, 0x00);

    display_cmd(0, 0xC0);
    display_cmd(1, 0x1D);

    display_cmd(0, 0xC1);
    display_cmd(1, 0x12);

    display_cmd(0, 0xC5);
    display_cmd(1, 0x33);
    display_cmd(1, 0x3f);

    display_cmd(0, 0xC7);
    display_cmd(1, 0x92);

    display_cmd(0, 0x3a);
    display_cmd(1, 0x55);

    display_cmd(0, 0x36);
    display_cmd(1, 0x08);

    display_cmd(0, 0xB1);
    display_cmd(1, 0x00);
    display_cmd(1, 0x12);

    display_cmd(0, 0xB6);
    display_cmd(1, 0x0A);
    display_cmd(1, 0xA2);

    display_cmd(0, 0x44);
    display_cmd(1, 0x02);

    display_cmd(0, 0xF2);
    display_cmd(1, 0x00);

    display_cmd(0, 0x26);
    display_cmd(1, 0x01);

    display_cmd(0, 0x26);
    display_cmd(1, 0x01);

    display_cmd(0, 0xE0);
	  display_cmd(1, 0x0F);
	  display_cmd(1, 0x22);
	  display_cmd(1, 0x1C);
	  display_cmd(1, 0x1B);
	  display_cmd(1, 0x08);
	  display_cmd(1, 0x0F);
	  display_cmd(1, 0x48);
	  display_cmd(1, 0xB8);
	  display_cmd(1, 0x34);
	  display_cmd(1, 0x05);
	  display_cmd(1, 0x0C);
	  display_cmd(1, 0x09);
	  display_cmd(1, 0x0F);
	  display_cmd(1, 0x07);
	  display_cmd(1, 0x00);

	  display_cmd(0, 0xE1);
	  display_cmd(1, 0x00);
	  display_cmd(1, 0x23);
	  display_cmd(1, 0x24);
	  display_cmd(1, 0x07);
	  display_cmd(1, 0x10);
	  display_cmd(1, 0x07);
	  display_cmd(1, 0x38);
	  display_cmd(1, 0x47);
	  display_cmd(1, 0x4B);
	  display_cmd(1, 0x0A);
	  display_cmd(1, 0x13);
	  display_cmd(1, 0x06);
	  display_cmd(1, 0x30);
	  display_cmd(1, 0x38);
	  display_cmd(1, 0x0F);

	  display_cmd(0, 0x29);
}

void display_clear(uint16_t color) {
    display_cmd(0, 0x2C);
    CS = 0;
    DC = 1;

    for (int i = 0; i < 320; i++) {
        for (int j = 0; j < 240; j++) {
            SPI2BUF = color>>8;
            while(!_SPI2IF);
            _SPI2IF = 0;
            int temp = SPI2BUF; (void)temp;

            SPI2BUF = color & 0xff;
            while(!_SPI2IF);
            _SPI2IF = 0;
            temp = SPI2BUF; (void)temp;
        }
    }

    CS = 1;
}
