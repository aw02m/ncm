#include<stdio.h>
#include"matrix.h"

#define N 4

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

void solveMatrix(double **L, double **U, double *x, double *y, double *b)
{
  int k,m;
  double sum;

  // 前進代入 (yを求める)
  for(k=0;k<N;k++){
    sum = 0;
    for(m=0;m<=k;m++){
      sum += L[k][m] * y[m];
    }
    y[k] = (b[k] - sum) / L[k][k];
  }

  // 後退代入 (xを求める)
  for(k=N-1;k>=0;k--){
    sum = 0;
    for(m=k;m<N;m++){
      sum += U[k][m] * x[m];
    }
    x[k] = y[k] - sum;
  }
}

int main(void)
{
  int i,j;
  double **A,**L,**U;
  double *b,*x,*y;

  A = matrix(N,N);
  L = matrix(N,N);
  U = matrix(N,N);
  b = vector(N);
  x = vector(N);
  y = vector(N);
  
	A[0][0] = 1; A[0][1] = 0;  A[0][2] = -2; A[0][3] = 3;
  A[1][0] = 5; A[1][1] = -1; A[1][2] = 1;  A[1][3] = 0;
  A[2][0] = 3; A[2][1] = 0;  A[2][2] = -2; A[2][3] = 1;
  A[3][0] = 0; A[3][1] = 3;  A[3][2] = 1;  A[3][3] = 2;

	b[0] = 7.5;
  b[1] = 1;
  b[2] = 6.5;
  b[3] = -1.5;

  for(i=0;i<N;i++){
    for(j=0;j<N;j++){      
      L[i][j] = 0;
      U[i][j] = 0;
    }
    x[i] = 0;
    y[i] = 0;
  }

	disassembleLU(A,L,U);
  solveMatrix(L,U,x,y,b);

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
  printf("y\n");

  // y
  for(i=0;i<N;i++){
    printf("%f", y[i]);
    printf("\n");
  }
  printf("x\n");

  // x
  for(i=0;i<N;i++){
    printf("%f", x[i]);
    printf("\n");
  }

  free(A); free(L); free(U);
  free(b); free(x); free(y);
  
	return 0;
}
