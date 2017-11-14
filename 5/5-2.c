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

int main(void)
{
  int i,j;
  double **A,**L,**U,**B,**X,**Y,**E,**Xi;

  A = matrix(N,N);
  L = matrix(N,N);
  U = matrix(N,N);
  B = matrix(N,N);
  X = matrix(N,N);
  Y = matrix(N,N);
  E = matrix(N,N);
  Xi = matrix(N,N);

  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      A[i][j] = 0;
      L[i][j] = 0;
      U[i][j] = 0;
      B[i][j] = 0;
      X[i][j] = 0;
      Y[i][j] = 0;
      Xi[i][j] = 0;
      if(i == j){
        E[i][j] = 1;
      }else{
        E[i][j] = 0;
      }
    }
  }
   
	A[0][0] = 1; A[0][1] = 1;  A[0][2] = 2;
  A[1][0] = -2; A[1][1] = 1; A[1][2] = 0;
  A[2][0] = 1; A[2][1] = 2;  A[2][2] = 3;

	B[0][0] = -5; B[0][1] = -2; B[0][2] = 1;
  B[1][0] = -3; B[1][1] = 4;  B[1][2] = 3;
  B[2][0] = -5; B[2][1] = -3; B[2][2] = 3;

	disassembleLU(A,L,U);
  solveMatrix(L,U,E,Xi,Y);
  solveMatrix(L,U,B,X,Y);

  // L
  printf("L\n");
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			printf("%f ", L[i][j]);
		}
		printf("\n");
	}
  
  // U
	printf("U\n");
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			printf("%f ", U[i][j]);
		}
		printf("\n");
	}
  printf("Y\n");

  // Y
  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      printf("%f ", Y[i][j]);
    }
    printf("\n");
  }
  printf("X\n");

  // X
  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      printf("%f ", X[i][j]);
    }
    printf("\n");
  }
  printf("Xi\n");

  // Xi
  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      printf("%f ", Xi[i][j]);
    }
    printf("\n");
  }

  free(A); free(L); free(U); free(B);
  free(X); free(Y); free(E); free(Xi);
  
	return 0;
}
