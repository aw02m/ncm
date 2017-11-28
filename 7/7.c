#include<stdio.h>
#include<math.h>
#include"matrix.h"

#define N 4

void householder(double **A)
{
  int i, j, k, m;
  double s, norm, sum, alpha;
  double *u, *a, *b, *w, *Au;
  double **E, **M, **tempA, **U, **uwt, **wut;

  u = vector(N);
  a = vector(N);
  b = vector(N);
  w = vector(N);
  E = matrix(N, N);
  M = matrix(N, N);
  tempA = matrix(N, N);
  
  for (k = 0; k < N-1; k++) {
    // init
    for (i = 0; i < N; i++) {
      for (j = 0; j < N; j++) {
        M[i][j] = 0;
        tempA[i][j] = 0;
        if ( i != j ) {
          E[i][j] = 0;
        } else {
          E[i][j] = 1;
        }
      }
      u[i] = 0;
      a[i] = 0;
      b[i] = 0;
      w[i] = 0;
    }
    
    // s
    sum = 0;
    for (m = 1; m < N-k; m++) {
      sum += pow(A[k+m][k], 2);
    }
    if ( A[k+1][k] > 0 ) {
      s = -1 * sqrt(sum);
    } else {
      s = sqrt(sum);
    }

    // a b
    for (m = 0; m < N; m++) {
      a[k+m] = A[k+1][k];
    }
    b[k] = s;

    // u
    norm = sqrt(2*s * (s - A[k+1][k]));
    for (m = 0; m < N; m++) {
      u[k+m] = (a[k+m] - b[k+m]) / norm;
    }
    
    // M
    // uu^t
    U = multiplyVectorT(N, u, u);
    for (i = 0; i < N; i++) {
      for (j = 0; j < N; j++) {
        M[i][j] = E[i][j] - 2 * U[i][j];
      }
    }

    // MAM
    // Au
    sum = 0;
    Au = multiplyMatrixVector(N, A, u);
    for (i = 0; i < N; i++) {
      sum = u[i] * Au[i];
    }
    alpha = sum;
    for (i = 0; i < N; i++) {
      w[i] = 2 * (Au[i] - alpha * u[i]);
    }

    uwt = multiplyVectorT(N, u, w);
    wut = multiplyVectorT(N, w, u);
    for (i = 0; i < N; i++) {
      for (j = 0; j < N; j++) {
        tempA[i][j] = A[i][j] - uwt[i][j] -wut[i][j];
      }
    }

    for (i = 0; i < N; i++) {
      for (j = 0; j < N; j++) {
        A[i][j] = tempA[i][j];
      }
    }

    free(U);
    free(Au);
    free(uwt);
    free(wut);
  }
}

int main(void)
{
  int i,j;
  double **A;

  A = matrix(N, N);

  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      A[i][j] = 0;
    }
  }
   
	A[0][0] = 2; A[0][1] = 3; A[0][2] = 5;  A[0][3] = 7;
  A[1][0] = 3; A[1][1] = 5; A[1][2] = 7;  A[1][3] = 9;
  A[2][0] = 5; A[2][1] = 7; A[2][2] = 9;  A[2][3] = 11;
  A[3][0] = 7; A[3][1] = 9; A[3][2] = 11; A[3][3] = 13;

  householder(A);
  
  // A
  printf("A(k+1)\n");
  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      printf("%f ", A[i][j]);
    }
    printf("\n");
  }

  free(A);
  
	return 0;
}
