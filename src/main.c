#include "morse.h"
#include "peripherals.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>

#define DOT_MS 175
#define DEBOUNCE_MS 25

int main() {
    usart_init();
    timer_init();
    sei(); // Enable interrupts

    WRITE_BIT(DDRD, DDD6, INPUT);  // Set port D6 as input
    WRITE_BIT(PORTD, PORTD6, 1);   // Activate pin D6's pull-up resistor
    WRITE_BIT(DDRD, DDD7, OUTPUT); // Set port D7 as output

    uint32_t hold_time = 0;
    uint32_t debounce_time = 0;
    bool last_button_state = false;

    const Node* morse_letter = &MORSE_ROOT;

    while (true) {
        // Because of the pull-up resistor, when the button is pressed the pin reads low
        bool button_pressed = READ_BIT(PIND, PIND6) == 0 ? true : false;

        if (button_pressed != last_button_state) {
            debounce_time = timer_ms();
        }

        if (timer_ms() - debounce_time > DEBOUNCE_MS) {
            if (button_pressed) {
                if (hold_time == 0) {
                    hold_time = timer_ms();
                }
                WRITE_BIT(PORTD, PORTD7, 1);
            } else {
                if (hold_time > 0) {
                    if (timer_ms() - hold_time <= DOT_MS) {
                        const Node* dot = morse_read_node_dot(morse_letter);

                        if (dot != NULL) {
                            morse_letter = dot;
                            printf_P(PSTR("short: %c\r\n"), morse_read_node_val(morse_letter));
                        } else {
                            printf_P(PSTR("final: %c\r\n\n"), morse_read_node_val(morse_letter));
                            morse_letter = &MORSE_ROOT;
                        }
                    } else {
                        const Node* dash = morse_read_node_dash(morse_letter);

                        if (dash != NULL) {
                            morse_letter = dash;
                            printf_P(PSTR("LONG: %c\r\n"), morse_read_node_val(morse_letter));
                        } else {
                            printf_P(PSTR("final: %c\r\n\n"), morse_read_node_val(morse_letter));
                            morse_letter = &MORSE_ROOT;
                        }
                    }

                    hold_time = 0;
                }

                WRITE_BIT(PORTD, PORTD7, 0);
            }
        }

        last_button_state = button_pressed;
    }

    return 0;
}
