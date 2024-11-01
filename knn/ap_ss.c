#include <stdio.h>
#include <stdlib.h>

#define M 3
#define L 3
#define N 3

typedef struct {
    double m[M];
} AP;

int main(int argc, char *argv[]) {
    AP ap[N];
    int argi = 1;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            ap[i].m[j] = atof(argv[argi]);
            argi++;
        }
    }
    double D[L][M] = {0};
    for (int i = 0; i < L && i < M; i++) {
        D[i][i] = 1.0;
    }
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < M; j++) {
            printf("%.1f ", D[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%.2f ", ap[i].m[j]);
        }
        printf("\n");
    }
    return 0;
}