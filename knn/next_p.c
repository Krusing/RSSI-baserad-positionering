#include <stdio.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

typedef struct {
    double N;
    double E;
} P;

int main(int argc, char *argv[]) {
    P current, next;

    current.N = atof(argv[1]);
    current.E = atof(argv[2]);
    double L = atof(argv[3]);
    double phi = atof(argv[4]);

    double r = phi * (M_PI / 180.0);
    next.N = current.N + L * cos(r);
    next.E = current.E + L * sin(r);

    printf("%.2f %.2f\n", next.N, next.E);
    return 0;
}
