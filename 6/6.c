#include<stdio.h>
#include"matrix.h"

#define N 3

void disassembleLU(double **a, double **l, double **u)
{
  int i,k,m;
  double sum;

  for(k=0;k<N;k++){
    for(i=k;i<N;i++){
      // L
      sum = 0;
      for(m=0;m<k;m++){
        sum += l[i][m] * u[m][k];
      }
      l[i][k] = a[i][k] - sum;
      // U
      sum = 0;
      for(m=0;m<k;m++){
        sum += l[k][m] * u[m][i];
      }
      u[k][i] = (a[k][i] - sum) / l[k][k];
    }
  }
}

void solveMatrix(double **L, double **U, double **B, double **X, double **Y)
{
  int i,k,m;
  double sum;

  for(i=0;i<N;i++){
    // 前進代入 (yを求める)
    for(k=0;k<N;k++){
      sum = 0;
      for(m=0;m<=k;m++){
        sum += L[k][m] * Y[m][i];
      }
      Y[k][i] = (B[k][i] - sum) / L[k][k];
    }

    // 後退代入 (xを求める)
    for(k=N-1;k>=0;k--){
      sum = 0;
      for(m=k;m<N;m++){
        sum += U[k][m] * X[m][i];
      }
      X[k][i] = Y[k][i] - sum;
    }
  }
}

float **jacobi()
{
  int i, j;
  int p, q;
  int end = 0;
  double max;

  while (end > 0 &&  k < 
  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      if (i != j) {
        if (max < fabs(A[i][j])) {
          p = i;
          q = j;
          max = fabs(A[i][j]);
        }
      }
    }
  }

  
}

int main(void)
{
  int i,j;
  double **A, **X, **E;

  A = matrix(N,N);
  X = matrix(N,N);
  E = matrix(N,N);

  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      A[i][j] = 0;
      X[i][j] = 0;
      if(i == j){
        E[i][j] = 1;
      }else{
        E[i][j] = 0;
      }
    }
  }
   
	A[0][0] = 2; A[0][1] = 5;  A[0][2] = 7;
  A[1][0] = 5; A[1][1] = 7;  A[1][2] = 9;
  A[2][0] = 7; A[2][1] = 9;  A[2][2] = -3;
  
  // X
  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      printf("%f ", X[i][j]);
    }
    printf("\n");
  }

  free(A);
  free(X);
  free(E);
  
	return 0;
}
