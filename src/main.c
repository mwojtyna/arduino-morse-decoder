// 16MHz CPU clock for util/delay.h
#define F_CPU 16000000UL

#include "cal.h"
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    CAL_PIN_MODE(DDRB, DDB5, OUTPUT);

    while (1) {
        CAL_WRITE_PORT(PORTB, PORTB5, HIGH);
        _delay_ms(500);
        CAL_WRITE_PORT(PORTB, PORTB5, LOW);
        _delay_ms(500);
    }

    return 0;
}
