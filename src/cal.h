#include <stdint.h>

// cal - Common AVR Library

#define HIGH 1
#define LOW 0

#define OUTPUT 1
#define INPUT 0

/** 
 * Set pin mode
 *
 * `cal_pin_mode(&DDRB, DDB5, OUTPUT);`
 * `cal_pin_mode(&DDRB, DDB5, INPUT);`
 */
void cal_pin_mode(volatile uint8_t* ddr, uint8_t num, uint8_t mode);

/** 
 * Write 
 * `cal_digital_write(&PORTB, PORTB5, HIGH);`
 * `cal_digital_write(&PORTB, PORTB5, LOW);`
 */
void cal_digital_write(volatile uint8_t* reg, uint8_t num, uint8_t value);
