#include "peripherals.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include <util/atomic.h>

// ------------------ MATH ------------------
inline int roundf_fast(float x) {
    return (x >= 0.0f) ? (int)(x + 0.5f) : (int)(x - 0.5f);
}

// ------------------ USART ------------------
static int usart_putchar(char data, FILE* stream) {
    // Wait until buffer is empty
    while (READ_BIT(UCSR0A, UDRE0) == 0) {
    }
    UDR0 = data;
    return 0;
}

static FILE usart_stdout = FDEV_SETUP_STREAM(usart_putchar, NULL, _FDEV_SETUP_WRITE);

void usart_init() {
    // Enable the use of regular stdio.h functions to print over USART
    stdout = &usart_stdout;

    // Table 19-1, ATmega328P data sheet
    const uint16_t UBRR = roundf_fast((F_CPU / (16 * (float)BAUD)) - 1);
    UBRR0H = (uint8_t)(UBRR >> 8); // 4 most significant bits
    UBRR0L = (uint8_t)UBRR;        // 8 least significant bits

    WRITE_BIT(UCSR0A, U2X0, 0); // Don't double USART transmission speed

    WRITE_BIT(UCSR0B, RXEN0, 1);  // Enable receiver
    WRITE_BIT(UCSR0B, TXEN0, 1);  // Enable transmitter
    WRITE_BIT(UCSR0B, UCSZ02, 0); // 8-bit character size

    UCSR0C = (0 << UMSEL01) | (0 << UMSEL00) | // Set asynchronous mode
             (0 << UPM01) | (0 << UPM00) |     // Disable parity
             (0 << USBS0) |                    // 1-bit stop bit
             (1 << UCSZ01) | (1 << UCSZ00) |   // 8-bit character size
             (0 << UCPOL0);                    // clock polarity = 0 because asynchronous mode
}

// ------------------ TIMER ------------------
static uint32_t millis = 0;

// Interrupt for when timer counts up to 1ms
ISR(TIMER0_COMPA_vect) {
    millis++;
}

void timer_init() {
    // Enable Clear Timer On Compare (CTC) mode
    WRITE_BIT(TCCR0B, WGM02, 0);
    WRITE_BIT(TCCR0A, WGM01, 1);
    WRITE_BIT(TCCR0A, WGM02, 1);

    // Set timer's clock source to system clock / 64
    WRITE_BIT(TCCR0B, CS02, 0);
    WRITE_BIT(TCCR0B, CS01, 1);
    WRITE_BIT(TCCR0B, CS00, 1);

    // Enable interrupts when OCR0A matches with timer
    WRITE_BIT(TIMSK0, OCIE0A, 1);

    // System clock / 64 = 16'000'000 / 64 = 250'000 ticks/s = 250 ticks/ms
    // Generate an interrupt whenever the timer counts to 250 (to get an interrupt each ms)
    OCR0A = 250;
}

uint32_t timer_ms() {
    uint32_t m;
    ATOMIC_BLOCK(ATOMIC_FORCEON) {
        m = millis;
    }
    return m;
}
