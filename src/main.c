// TODO: morse code decoding

// 16MHz CPU clock for util/delay.h
#define F_CPU 16000000UL
#define BAUD_RATE 115200

#include "lib.h"
#include <avr/interrupt.h>
#include <avr/io.h>

int main() {
    usart_init();
    timer_init();
    sei();

    WRITE_BIT(DDRD, DDD6, INPUT);  // Set port D6 as input
    WRITE_BIT(PORTD, PORTD6, 1);   // Activate pin D6's pull-up resistor
    WRITE_BIT(DDRD, DDD7, OUTPUT); // Set port D7 as output

    while (1) {
        // Because of the pull-up resistor, when the button is pressed the pin reads low
        if (READ_BIT(PIND, PIND6) == 0) {
            WRITE_BIT(PORTD, PORTD7, 1);
            usart_println("Pressed");
        } else {
            WRITE_BIT(PORTD, PORTD7, 0);
        }
    }

    return 0;
}
