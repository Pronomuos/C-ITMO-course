#ifndef PROG_11_RHOMBUS_H
#define PROG_11_RHOMBUS_H

struct Point {
    double x, y;
};

struct Rhombus {
    struct Point upper;
    struct Point left;
    struct Point right;
    struct Point lower;
};


float dist (struct Point, struct Point);
struct Rhombus create_rhombus (struct Point, struct Point, struct Point, struct Point);
float find_perimeter (struct Rhombus);
float find_area (struct Rhombus);

#endif //PROG_11_RHOMBUS_H
