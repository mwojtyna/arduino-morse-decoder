#include "cal.h"

void cal_pin_mode(volatile uint8_t* ddr, uint8_t num, uint8_t mode) {
    if (mode == INPUT) {
        *ddr &= ~(1 << num);
    } else {
        *ddr |= 1 << num;
    }
}

void cal_digital_write(volatile uint8_t* reg, uint8_t num, uint8_t value) {
    if (value == LOW) {
        *reg &= ~(1 << num);
    } else {
        *reg |= 1 << num;
    }
}
