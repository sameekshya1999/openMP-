#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define N 1024

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
    #pragma omp parallel for num_threads(3)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            double sum = 0.0;
            for (int k = 0; k < N; k++) {
                sum += A[i][k] * B[k][j];
            }
            result[i][j] = sum;
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

    double start, end;
    start = omp_get_wtime();

    multiplyMatrices(A, B, result);

    end = omp_get_wtime();
    double time_spent = end - start;

    printf("Time taken for matrix multiplication with 3 threads: %f seconds\n", time_spent);

    freeMatrix(A, N);
    freeMatrix(B, N);
    freeMatrix(result, N);
return 0;
}
