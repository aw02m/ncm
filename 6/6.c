#include<stdio.h>
#include<math.h>
#include"matrix.h"

#define N 3
#define LOOP 100

void jacobi(double **A, double **V)
{
  int i, j;
  int p, q;
  int loop = 0;
  double s, c, sc, s2, c2, theta; // sin, cos, sin*cos, sin^2, cos^2, θ
  double max;
  double **tempA;
  double **tempV;
  tempA = matrix(N,N);
  tempV = matrix(N,N);

  // copy A to tempA, V to tempV
  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      tempA[i][j] = A[i][j];
      tempV[i][j] = V[i][j];
    }
  }

  while(loop < LOOP){
    max = 0;
    // search p and q
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

    theta = (atan(2 * A[p][q] / (A[p][p] - A[q][q]))) / 2;

    s = sin(theta);
    c = cos(theta);
    sc = s * c;
    s2 = pow(s, 2);
    c2 = pow(c, 2);

    for (j = 0; j < N; j++) {
      if (j != p && j != q) {
        tempA[p][j] = A[p][j] * c + A[q][j] * s;
        tempA[q][j] = -A[p][j] * s + A[q][j] * c;
      }
    }
    
    for (i = 0; i < N; i++) {
      if (i != p && i != q) {
        tempA[i][p] = A[i][p] * c + A[i][q] * s;
        tempA[i][q] = -A[i][p] * s + A[i][q] * c;
      }
      tempV[i][p] = V[i][p] * c + V[i][q] * s;
      tempV[i][q] = -V[i][p] * s + V[i][q] * c;
    }
    
    tempA[p][p] = A[p][p] * c2 + 2 * A[p][q] * sc + A[q][q] * s2;
    tempA[p][q] = sc * (A[q][q] - A[p][p]) + (c2 - s2) * A[p][q];
    tempA[q][p] = tempA[p][q];
    tempA[q][q] = A[p][p] * s2 - 2 * A[p][q] * sc + A[q][q] * c2;

    // copy tempA to A, tempV to V
    for (i = 0; i < N; i++) {
      for (j = 0; j < N; j++) {
        A[i][j] = tempA[i][j];
        V[i][j] = tempV[i][j];
      }
    }
    loop++;
  }

  free(tempA);
  free(tempV);
}

int main(void)
{
  int i,j;
  double **A;
  double **V;

  A = matrix(N, N);
  V = matrix(N, N);

  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      A[i][j] = 0;
      if (i != j) {
        V[i][j] = 0;
      } else {
        V[i][j] = 1;
      }
    }
  }
   
	A[0][0] = 2; A[0][1] = 5;  A[0][2] = 7;
  A[1][0] = 5; A[1][1] = 7;  A[1][2] = 9;
  A[2][0] = 7; A[2][1] = 9;  A[2][2] = -3;

  jacobi(A, V);
  
  // A
  printf("A(k+1)\n");
  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      printf("%f ", A[i][j]);
    }
    printf("\n");
  }

  // V
  printf("V(k+1)\n");
  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      printf("%f ", V[i][j]);
    }
    printf("\n");
  }

  free(A);
  free(V);
  
	return 0;
}
