#include "Rhombus.h"
#include <math.h>

float dist (struct Point a, struct Point b) {
    return sqrtf(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

struct Rhombus create_rhombus (struct Point upper, struct Point left,
        struct Point right, struct Point lower) {
    return (struct Rhombus) {upper, left, right, lower};
}

float find_perimeter (struct Rhombus r) {
    float result = 0;

    result += dist(r.left, r.upper);
    result += dist(r.upper, r.right);
    result += dist(r.right, r.lower);
    result += dist(r.lower, r.left);

    return result;
}

float find_area (struct Rhombus r) {
    return 0.5 * dist(r.upper, r.lower) * dist(r.left, r.right);
}