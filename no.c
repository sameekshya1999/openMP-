#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000

double** allocateMatrix(int rows, int cols) {
double** mat = (double**)malloc(rows * sizeof(double*));
    for (int i = 0; i < rows; i++) {
        mat[i] = (double*)malloc(cols * sizeof(double));
    }
    return mat;
}

void freeMatrix(double** mat, int rows) {
for (int i = 0; i < rows; i++) {
        free(mat[i]);
    }
    free(mat);
}

void initializeMatrix(double** mat, int rows, int cols) {
for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
            mat[i][j] = (double)rand() / RAND_MAX;
        }
    }
}

void multiplyMatrices(double** A, double** B, double** result) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            result[i][j] = 0;
            for (int k = 0; k < N; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    srand(time(NULL)); 

    double** A = allocateMatrix(N, N);
    double** B = allocateMatrix(N, N);
    double** result = allocateMatrix(N, N);

    initializeMatrix(A, N, N);
    initializeMatrix(B, N, N);

    clock_t start, end;
    start = clock();

    multiplyMatrices(A, B, result);

    end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Time taken for matrix multiplication: %f seconds\n", time_spent);

    freeMatrix(A, N);
    freeMatrix(B, N);
    freeMatrix(result, N);
    return 0;
}
