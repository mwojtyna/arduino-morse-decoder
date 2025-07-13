#include "morse.h"
#include "peripherals.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>

#define DOT_MS 175
#define DEBOUNCE_MS 25
#define ACCEPT_LETTER_MS (3 * DOT_MS)

int main() {
    usart_init();
    timer_init();
    sei(); // Enable interrupts

    WRITE_BIT(DDRD, DDD6, INPUT);  // Set port D6 as input
    WRITE_BIT(PORTD, PORTD6, 1);   // Activate pin D6's pull-up resistor
    WRITE_BIT(DDRD, DDD7, OUTPUT); // Set port D7 as output

    time debounce_timer = 0;
    time hold_begin_time = 0;
    time last_released_time = 0;
    bool last_button_state = false;

    const Node* PROGMEM morse_letter = morse_get_root();

    while (true) {
        // Because of the pull-up resistor, when the button is pressed the pin reads low
        bool button_pressed = READ_BIT(PIND, PIND6) == 0 ? true : false;

        // Handle debounce
        if (button_pressed != last_button_state) {
            debounce_timer = timer_ms();
        }

        if (timer_ms() - debounce_timer > DEBOUNCE_MS) {
            if (button_pressed) {
                if (hold_begin_time == 0) {
                    hold_begin_time = timer_ms();
                }

                WRITE_BIT(PORTD, PORTD7, 1);
            } else {
                if (hold_begin_time != 0) {
                    if (timer_ms() - hold_begin_time <= DOT_MS) {
                        const Node* dot = morse_read_node_dot(morse_letter);

                        if (dot != NULL) {
                            morse_letter = dot;
                        } else {
                            morse_letter = NULL;
                        }
                    } else {
                        const Node* dash = morse_read_node_dash(morse_letter);

                        if (dash != NULL) {
                            morse_letter = dash;
                        } else {
                            morse_letter = NULL;
                        }
                    }

                    last_released_time = timer_ms();
                    hold_begin_time = 0;
                }

                // Select current letter as final if enough time elapsed
                if (timer_ms() - last_released_time >= ACCEPT_LETTER_MS &&
                    morse_letter != morse_get_root()) {

                    // TODO: Display on LCD
                    if (morse_letter == NULL || morse_read_node_val(morse_letter) == '\0') {
                        printf_P(PSTR("invalid morse code\r\n"));
                    } else {
                        printf_P(PSTR("%c\r\n"), morse_read_node_val(morse_letter));
                    }

                    morse_letter = morse_get_root();
                }

                WRITE_BIT(PORTD, PORTD7, 0);
            }
        }

        last_button_state = button_pressed;
    }

    return 0;
}
