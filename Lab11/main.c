#include <stdio.h>
#include "Rhombus.h"


int main() {
    struct Rhombus r = { {20, 0}, {0, 10}, {40, 10}, {20, 20}};
    printf("The perimeter of the rhombus is %f.\n", find_perimeter(r));
    printf("The area of the rhombus is %f.\n", find_area(r));
    return 0;
}
