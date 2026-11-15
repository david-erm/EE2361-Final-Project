/*
 * File:   ps2.c
 * Author: aruna
 *
 * Created on November 9, 2026, 5:29 PM
 */
#include "xc.h"
// I am working on the software input translation + hardware output display side of things.



#define MAXBUFFERSIZE 15 // in a sentence, what are the chances someone is typing a 15 letter word? 
// this gives enough time for the buffer to process and circulate new words.
// the 15 letters will process in nanoseconds and be ready for the next word.
// and even if you type in a 20 letter word, the circular buffer
// will be able to account for that by 

volatile long int startofbuffer = 0; // we need this because the start of the buffer
volatile long int endofbuffer = 0; // we need this to check if the ending element of the output translation buffer is null
volatile char processedcharacter = " ";
volatile char bufferofchars[MAXBUFFERSIZE]; // circ buff
volatile long int processingbuffer[]; 
// how many bytes do we need? well, think about the combinations that we have.
// there must be a datasheet listing the various combos and what letters they
// associate to. For example:
// 10111010 is the same as the letter "T".
// like that.
// if we want to process 104 keys, we need to have at least 8 bits.
// we'll have room for 23 other keys before the code will have to be expanded.

// here's how I understand it:
/*
 
1. we need buffer beginning because the buffer is FIFO.
 * example: type in C-A-T. in the buffer, it'll become:
 * |    T   |
 * |    A   |
 * |    C   |
 * so we need to start with the beginning of the buffer actually.
 * 
 * 2. we take in the bytes and convert them to characters using switch case, and then we put those 
 * // characters into our buffer.
 * 
 
 
 
 
 
 */

void setup () {
    // i'll need output compare.
    OC1CON = 0;
    
}


void processBytes(inputbufferfromraleigh){ // take the bits from input and convert them to output
    
    while (inputbufferfromraleigh.BNE); // im going to use polling for that part.
    
    
}

// basically what I'm thinking is that the processingbuffer will process the input

// we will need buffernotempty somewhere to see if the processing buffer is empty, then we can add the 
// inputs that we get from inputbufferfromraleigh

// example: if your buffer is only 3 elements long and you type in "DOG"
// the processing buffer will do just fine; 

// we need to FIRST always check: if the processing buffer is NOT empty. if it is not,

// we'll take first element D, display it using our function convertbytestodisplayoutput,
// check if the first and second element of the processing buffer have some value that is not null,
// (so in other words, check if the processing buffer is not empty)

// if yes, slide everything in the processing buffer left
// if no, don't slide anything. the processing buffer is done.


// then take O, display it using our function convertbytestodisplayoutput
// check if the first and second element of the processing buffer have something
// (or if the buffer is not empty / has elements). 

// If yes, slide everything in the processing buffer left,

// then take G, display it using our function convertbytestodisplayoutput
// check if the first and second element of the processing buffer have something
// (or if the buffer is not empty / has elements).
// if no, the buffer IS empty and when the buffer is empty, there isn't a specific action that you do.s


// but if inputbufferfromraleigh has "DOGRA", the processing buffer has to process the "D" part first and then
// it has to check 2 things:
//      1. if the ending element of the buffer is empty, and
//      2. if there is something inside the inputbufferfromraleigh,
        // we put that element at the end of the buffer, which can change because the 
        // "end" could be new every time.
            // example: DOG [] the end in this case is at element 4.
            // but DOGRAAR [], the end in this case is at element 7.
            // so we have to use the length of the processingbuffer as a reference
            // length(buffer) so that we know where to put the first input of
            // the items in "inputbufferfromraleigh".


// wait a second. we don't iterate through the buffer like [0], [1], [2].
// we have to finish with D, move left, and then there is space at the end to put "R".
// then finish with O, move left, then there is space at the end for "A".
// so we have to check: is the ending element of the buffer null?


// so there has to be a check that only allows a certain amount of bytes from the input
// to be converted to output. and that depends on the size of the buffer. something like:
// if (theamountofbytesthatiamgoingtopassin < sizeofmyoutputtranslationbuffer)

void convertbytestodisplayoutput(processingbuffer) {
    // this function will take in the processed bytes and convert then to a display output
    // buffercharsofmaxsize
    // 
}
        

