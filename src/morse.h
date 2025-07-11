#ifndef MORSE_HEADER
#define MORSE_HEADER

#include <avr/pgmspace.h>

typedef struct Node Node;
struct Node {
    const char val;
    const Node* dot;
    const Node* dash;
};

extern const Node MORSE_ROOT;

// Returns node value from program memory
char morse_read_node_val(const Node* progmem_ptr);

// Returns node's pointer to dot node, copied from program memory to SRAM
const Node* morse_read_node_dot(const Node* progmem_ptr);

// Returns node's pointer to dash node, copied from program memory to SRAM
const Node* morse_read_node_dash(const Node* progmem_ptr);

#endif
