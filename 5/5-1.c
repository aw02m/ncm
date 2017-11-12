#include<stdio.h>
#include<math.h>
#include"matrix.h"

#define N 3

void disassemble(double **A, double **L, double **Lt)
{
  int i, j, k;
  double sum;

  for (j = 0; j < N; j++) {
    for(i = 0; i <= j; i++) {
      sum = 0;
      if (i != j) {
        // 非対角成分
        for (k = 0; k < i; k++) {
          sum += L[i][k] * L[j][k];
        }
        L[j][i] = (A[i][j] - sum) / L[i][i];
        Lt[i][j] = L[j][i]; // Lt
      } else {
        // 対角成分
        for (k = 0; k < i; k++) {
          sum += L[i][k] * L[i][k];
        }
        L[i][i] = sqrt(A[i][i] - sum);
        Lt[i][i] = L[i][i];
      }
    }
  }
}

// 前回のものを流用
void solveMatrix(double **L, double **U, double *x, double *y, double *b)
{
  int k, m;
  double sum;

  // 前進代入 (yを求める)
  for (k = 0; k < N; k++) {
    sum = 0;
    for (m = 0; m <= k; m++) {
      sum += L[k][m] * y[m];
    }
    y[k] = (b[k] - sum) / L[k][k];
  }

  // 後退代入 (xを求める)
  for (k = N-1; k >= 0; k--) {
    sum = 0;
    for(m = k; m < N; m++) {
      sum += U[k][m] * x[m];
    }
    x[k] = y[k] - sum;
  }
}

int main(void)
{
  int i, j;
  double **A, **L, **Lt, **multi;
  double *b, *x, *y;

  A = matrix(N, N);
  L = matrix(N, N);
  Lt = matrix(N, N);
  multi = matrix(N, N); // L*Ltの確認用
  b = vector(N);
  x = vector(N);
  y = vector(N);
  
	A[0][0] = 3.0; A[0][1] = 2.0; A[0][2] = 1.0;
  A[1][0] = 2.0; A[1][1] = 3.0; A[1][2] = 2.0;
  A[2][0] = 1.0; A[2][1] = 2.0; A[2][2] = 3.0;

	b[0] = 1;
  b[1] = 3;
  b[2] = -1;

  for (i = 0; i < N; i++) {
    for(j = 0; j < N; j++) {      
      L[i][j] = 0;
      Lt[i][j] = 0;
      multi[i][j] = 0;
    }
    x[i] = 0;
    y[i] = 0;
  }

  disassemble(A, L, Lt);
  solveMatrix(L, Lt, x, y, b);
  multi = multiplyMatrix(N, L, Lt); // L*Ltが正しいか確認

  // L
  printf("L\n");
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			printf("%f ", L[i][j]);
		}
		printf("\n");
	}
  // Lt
  printf("Lt\n");
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			printf("%f ", Lt[i][j]);
		}
		printf("\n");
	}
  // L*Lt
  printf("L*Lt\n");
  for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			printf("%f ", multi[i][j]);
		}
		printf("\n");
  }
  // y
  printf("y\n");
  for (i = 0; i < N; i++) {
    printf("%f", y[i]);
    printf("\n");
  }
  // x
  printf("x\n");
  for (i = 0; i < N; i++) {
    printf("%f", x[i]);
    printf("\n");
  }

  free(A); free(L); free(Lt);
  free(b); free(x); free(y);
  
	return 0;
}
