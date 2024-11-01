#include <stdio.h>
#include <stdlib.h>

#define M 3
#define N 3

int main(int argc, char *argv[]) {
    double r[M][N];
    int o = 1;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            r[i][j] = atof(argv[o]);
            o++;
        }
    }
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            printf("%.2f ", r[i][j]);
        }
        printf("\n");
    }
    return 0;
}
