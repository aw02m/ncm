#include<stdio.h>

#define N 4

void disassembleLU(double a[N][N], double l[N][N], double u[N][N])
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

void solveMatrix(double L[N][N], double U[N][N], double x[N], double y[N], double b[N])
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
	double A[N][N] = {{1, 0, -2, 3},
										{5, -1, 1, 0},
										{3, 0, -2, 1},
										{0, 3, 1, 2}};

	double b[N] = {7.5,
								 1,
								 6.5,
                 -1.5};

	double L[N][N]={}, U[N][N]={};
  double x[N] = {}, y[N] = {};
	int i,j;

	disassembleLU(A,L,U);
  solveMatrix(L,U,x,y,b);

  // L U
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			printf("%f ", L[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			printf("%f ", U[i][j]);
		}
		printf("\n");
	}
  printf("\n");

  // y
  for(i=0;i<N;i++){
    printf("%f", y[i]);
    printf("\n");
  }
  printf("\n");

  // x
  for(i=0;i<N;i++){
    printf("%f", x[i]);
    printf("\n");
  }
  printf("\n");
  
	return 0;
}
