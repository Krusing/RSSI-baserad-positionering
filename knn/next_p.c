#include <stdio.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

typedef struct {
    double N;
    double E;
} P;

P nextP(P current, double L, double phi) {
    P next;

    double r = phi * (M_PI / 180.0);
    next.N = current.N + L * cos(r);
    next.E  = current.E  + L * sin(r);

    return next;
}

int main() {
    P current;
    double L, phi;

    printf("P North: ");
    scanf("%lf", &current.N);
    printf("P East:  ");
    scanf("%lf", &current.E);
    printf("Move length: ");
    scanf("%lf", &L);
    printf("Move angle:  ");
    scanf("%lf", &phi);

    P next = nextP(current, L, phi);

    printf("\n");
    printf("Next P_N: %.2f\n", next.N);
    printf("Next P_E: %.2f\n", next.E);

    printf("\nPress any key to exit.");
    getchar();
    getchar();

    return 0;
}    
