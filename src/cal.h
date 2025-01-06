/* cal - Common AVR Library */

#define HIGH 1
#define LOW 0

#define OUTPUT 1
#define INPUT 0

/** 
 * Set pin mode
 *
 * Examples:
 * `CAL_PIN_MODE(DDRB, DDB5, OUTPUT);`
 * `CAL_PIN_MODE(DDRB, DDB5, INPUT);`
 */
#define CAL_PIN_MODE(ddr, num, mode)                                           \
    if (mode == INPUT) {                                                       \
        ddr &= ~(1 << num);                                                    \
    } else {                                                                   \
        ddr |= 1 << num;                                                       \
    }

/** 
 * Write to port
 *
 * Examples:
 * `CAL_WRITE_PORT(PORTB, PORTB5, HIGH);`
 * `CAL_WRITE_PORT(PORTB, PORTB5, LOW);`
 */
#define CAL_WRITE_PORT(reg, num, val)                                          \
    if (val == LOW) {                                                          \
        reg &= ~(1 << num);                                                    \
    } else {                                                                   \
        reg |= 1 << num;                                                       \
    }
