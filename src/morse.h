#ifndef MORSE_HEADER
#define MORSE_HEADER

#include <avr/pgmspace.h>

typedef struct Node Node;
struct Node {
    const char val;
    const Node* dot;
    const Node* dash;
};

// Returns pointer to the root node of morse code tree
const Node* PROGMEM morse_get_root();

// Returns node value from program memory
// If node is NULL, returns '\0'
char morse_read_node_val(const Node* PROGMEM node);

// Returns node's pointer to dot node, copied from program memory to SRAM
// If node is NULL, returns NULL
const Node* morse_read_node_dot(const Node* PROGMEM node);

// Returns node's pointer to dash node, copied from program memory to SRAM
// If node is NULL, returns NULL
const Node* morse_read_node_dash(const Node* PROGMEM node);

#endif
