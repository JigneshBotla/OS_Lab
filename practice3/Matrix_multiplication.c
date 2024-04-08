#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

#define m 2
#define k 2
#define n 2

float C[m][n];
float A[m][k];
float B[k][n];

void *Matrix_Mul(void *arg) {
    int *params = (int *)arg;
    int row = params[0];
    int col = params[1];

    C[row][col] = 0;
    for (int i = 0; i < k; i++) {
        C[row][col] += A[row][i] * B[i][col];
    }
    pthread_exit(NULL);
}

int main() {
    printf("Enter the numbers of matrix A(%d * %d) :\n", m, k);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < k; j++) {
            scanf("%f", &A[i][j]);
        }
    }

    printf("Enter the numbers of matrix B(%d * %d) :\n", k, n);
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%f", &B[i][j]);
        }
    }

    pthread_t perform_Mul[m][n];
    int params[m * n][2];
    int idx = 0;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            params[idx][0] = i;
            params[idx][1] = j;
            pthread_create(&perform_Mul[i][j], NULL, Matrix_Mul, &params[idx]);
            idx++;
        }
    }
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            pthread_join(perform_Mul[i][j], NULL);
        }
    }

    printf("Resultant Matrix C:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%f  ", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}
