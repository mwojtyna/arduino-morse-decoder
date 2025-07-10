#include "math.h"

inline int roundf_fast(float x) {
    return (x >= 0.0f) ? (int)(x + 0.5f) : (int)(x - 0.5f);
}
