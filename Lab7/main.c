#include <stdio.h>
#include <math.h>

struct Point {
    float x;
    float y;
};

struct  Circle {
    struct Point center;
    float radius;
};

double find_circumference(struct Circle c) {
    return 2 * M_PI * c.radius;
}

struct CardReader {
    unsigned switched_on: 1;
    unsigned sd_card: 1;
    unsigned compact_flash_card: 1;
    unsigned memory_stick_card: 1;
};

int main(int argc, char *argv[]) {

    enum music_genres {classic, pop, rock, rap, new_age, electronic} cur_genre = rock;
    printf("1. The value of the current music genre is %d.\n", cur_genre);

    printf("The circle.\n");
    struct Circle circle;
    float x1, y1, r;
    printf("Print coordinates of tne center:\n");
    printf("x1 = ");
    scanf("%f", &x1);
    getc(stdin);
    printf("y1 = ");
    scanf("%f", &y1);
    getc(stdin);
    struct Point p;
    p.x = x1;
    p.y = y1;
    printf("Print the length of the radius:\n");
    scanf("%f", &r);
    getc(stdin);

    circle.center = p;
    circle.radius = r;

    printf("2. The circumference of the circle is %f\n", find_circumference(circle));

    struct CardReader cur_state;
    int entered_num;

    printf("3. Enter card-reader's state (hex): ");
    scanf("%x", &entered_num);
    getc(stdin);

    union hex_state {
        unsigned int num;
        struct CardReader state;
    } hs;
    hs.num = entered_num;

    cur_state = hs.state;

    printf("Current state: swicted_on: %d, SD card: %d, MemoryStick card: %d, CompactFlash card: %d.\n",
           cur_state.switched_on, cur_state.sd_card, cur_state.memory_stick_card, cur_state.compact_flash_card);

    return 0;
}