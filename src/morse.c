#include "morse.h"
#include <stdio.h>

// I'm defining characters from the leaves up to root
// Nodes beginning with INT_ are intermediate nodes, which themselves hold no value but lead to other nodes (see linked image)
// https://upload.wikimedia.org/wikipedia/commons/1/19/Morse-code-tree.svg

#define MORSE_NODE(Name, Val, Dot, Dash)                                                           \
    const Node Name PROGMEM = {.val = Val, .dot = Dot, .dash = Dash}

// Depth 5
MORSE_NODE(MORSE_FIVE, '5', NULL, NULL);
MORSE_NODE(MORSE_FOUR, '4', NULL, NULL);
MORSE_NODE(MORSE_THREE, '3', NULL, NULL);
MORSE_NODE(MORSE_TWO, '2', NULL, NULL);
MORSE_NODE(MORSE_PLUS, '+', NULL, NULL);
MORSE_NODE(MORSE_ONE, '1', NULL, NULL);
MORSE_NODE(MORSE_SIX, '6', NULL, NULL);
MORSE_NODE(MORSE_EQUALS, '=', NULL, NULL);
MORSE_NODE(MORSE_SLASH, '/', NULL, NULL);
MORSE_NODE(MORSE_SEVEN, '7', NULL, NULL);
MORSE_NODE(MORSE_EIGHT, '8', NULL, NULL);
MORSE_NODE(MORSE_NINE, '9', NULL, NULL);
MORSE_NODE(MORSE_ZERO, '0', NULL, NULL);

// Depth 4
MORSE_NODE(MORSE_H, 'H', &MORSE_FIVE, &MORSE_FOUR);
MORSE_NODE(MORSE_V, 'V', NULL, &MORSE_THREE);
MORSE_NODE(MORSE_F, 'F', NULL, NULL);
MORSE_NODE(MORSE_INT_U, '\0', NULL, &MORSE_TWO);
MORSE_NODE(MORSE_L, 'L', NULL, NULL);
MORSE_NODE(MORSE_INT_R, '\0', &MORSE_PLUS, NULL);
MORSE_NODE(MORSE_P, 'P', NULL, NULL);
MORSE_NODE(MORSE_J, 'J', NULL, &MORSE_ONE);
MORSE_NODE(MORSE_B, 'B', &MORSE_SIX, &MORSE_EQUALS);
MORSE_NODE(MORSE_X, 'X', &MORSE_SLASH, NULL);
MORSE_NODE(MORSE_C, 'C', NULL, NULL);
MORSE_NODE(MORSE_Y, 'Y', NULL, NULL);
MORSE_NODE(MORSE_Z, 'Z', &MORSE_SEVEN, NULL);
MORSE_NODE(MORSE_Q, 'Q', NULL, NULL);
MORSE_NODE(MORSE_INT_O_LEFT, '\0', &MORSE_EIGHT, NULL);
MORSE_NODE(MORSE_INT_O_RIGHT, '\0', &MORSE_NINE, &MORSE_ZERO);

// Depth 3
MORSE_NODE(MORSE_S, 'S', &MORSE_H, &MORSE_V);
MORSE_NODE(MORSE_U, 'U', &MORSE_F, &MORSE_INT_U);
MORSE_NODE(MORSE_R, 'R', &MORSE_L, &MORSE_INT_R);
MORSE_NODE(MORSE_W, 'W', &MORSE_P, &MORSE_J);
MORSE_NODE(MORSE_D, 'D', &MORSE_B, &MORSE_X);
MORSE_NODE(MORSE_K, 'K', &MORSE_C, &MORSE_Y);
MORSE_NODE(MORSE_G, 'G', &MORSE_Z, &MORSE_Q);
MORSE_NODE(MORSE_O, 'O', &MORSE_INT_O_LEFT, &MORSE_INT_O_RIGHT);

// Depth 2
MORSE_NODE(MORSE_I, 'I', &MORSE_S, &MORSE_U);
MORSE_NODE(MORSE_A, 'A', &MORSE_R, &MORSE_W);
MORSE_NODE(MORSE_N, 'N', &MORSE_D, &MORSE_K);
MORSE_NODE(MORSE_M, 'M', &MORSE_G, &MORSE_O);

// Depth 1
MORSE_NODE(MORSE_E, 'E', &MORSE_I, &MORSE_A);
MORSE_NODE(MORSE_T, 'T', &MORSE_N, &MORSE_M);

// Depth 0
MORSE_NODE(MORSE_ROOT, '\0', &MORSE_E, &MORSE_T);

const Node* PROGMEM morse_get_root() {
    return &MORSE_ROOT;
}

char morse_read_node_val(const Node* PROGMEM node) {
    if (node == NULL) {
        return '\0';
    }
    return pgm_read_byte(&(node->val));
}

const Node* morse_read_node_dot(const Node* PROGMEM node) {
    if (node == NULL) {
        return NULL;
    }
    return (const Node*)pgm_read_ptr(&(node->dot));
}

const Node* morse_read_node_dash(const Node* PROGMEM node) {
    if (node == NULL) {
        return NULL;
    }
    return (const Node*)pgm_read_ptr(&(node->dash));
}

bool morse_is_intermediate_node(const Node* PROGMEM node) {
    return morse_read_node_val(node) == '\0';
}
