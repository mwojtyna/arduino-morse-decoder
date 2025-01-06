#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    DDRB |= 1 << DDB5; // set PB5 as output

    while (1) {
        PORTB |= 1 << PORTB5;
        _delay_ms(500);
        PORTB &= ~(1 << PORTB5);
        _delay_ms(500);
    }

    return 0;
}
