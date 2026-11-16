#ifndef DELAY_H
#define DELAY_H

void wait_1ms();
void wait_100us();
void wait_1us();

void delay_ms(int ms) {
  for(int i = 0; i < ms; i++){
      wait_1ms();
  }
}

void delay_us(int us) {
  for(int i = 0; i < us; i++){
      wait_1us();
  }
}

#endif
