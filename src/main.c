// 16MHz CPU clock for util/delay.h
#define F_CPU 16000000UL

#include "cal.h"
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    cal_pin_mode(&DDRB, DDB5, OUTPUT);

    while (1) {
        cal_digital_write(&PORTB, PORTB5, HIGH);
        _delay_ms(500);
        cal_digital_write(&PORTB, PORTB5, LOW);
        _delay_ms(500);
    }

    return 0;
}
