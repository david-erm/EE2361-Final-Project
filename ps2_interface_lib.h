/* 
 * File: ps2_interface_lib.h
 * Author: raleigh
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef PS2_INTERFACE_LIB_H
#define	PS2_INTERFACE_LIB_H

#include <xc.h> // include processor files - each processor file is guarded.  

void ps2_interface_setup(void);

uint8_t read_scan_code(void);

#endif	/* PS2_INTERFACE_LIB_H */

