// TODO: USART, morse code decoding

// 16MHz CPU clock for util/delay.h
#define F_CPU 16000000UL

#include "lib.h"
#include <avr/io.h>
#include <util/delay.h>

int __attribute__((section(".init9"))) main(void) {
    WRITE_BIT(DDRD, DDD6, INPUT);   // Set port D6 as input
    WRITE_BIT(PORTD, PORTD6, HIGH); // Activate pin D6's pull-up resistor
    WRITE_BIT(DDRD, DDD7, OUTPUT);  // Set port D7 as output

    while (1) {
        // Because of the pull-up resistor, when the button is pressed the pin reads low
        if (READ_BIT(PIND, PIND6) == LOW) {
            WRITE_BIT(PORTD, PORTD7, HIGH);
        } else {
            WRITE_BIT(PORTD, PORTD7, LOW);
        }
    }

    return 0;
}
