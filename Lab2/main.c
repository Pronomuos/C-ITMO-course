#include <stdio.h>
#include <math.h>

double find_z1(double angle) {
    return 2 * pow(sin(3 * M_PI - 2 * angle), 2) * pow(cos(5 * M_PI + 2 * angle), 2);
}

double find_z2(double angle) {
    return 1.f/4 - 1.f/4 * sin(5.f/2 * M_PI - 8 * angle);
}

int main() {
    double a;
    printf("alpha = ");
    scanf("%lf", &a);

    printf("z1(alpha) = %lf\n", find_z1(a));
    printf("z2(alpha) = %lf", find_z2(a));

    return 0;
}
