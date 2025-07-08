#include <stdbool.h>

#define HIGH 1
#define LOW 0

#define OUTPUT 1
#define INPUT 0

#define WRITE_BIT(reg, num, val)                                               \
    if (val == 0) {                                                            \
        reg &= ~(1 << num);                                                    \
    } else {                                                                   \
        reg |= 1 << num;                                                       \
    }

#define READ_BIT(reg, num) ((reg & (1 << num)) >> num)
