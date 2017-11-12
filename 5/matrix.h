#ifndef MATRIX_H
#define MATRIX_H

#include<stdio.h>
#include<stddef.h>
#include<stdlib.h>

double *vector(int n)
{
  double *v;

  v = (double *)malloc((size_t)(sizeof(double) * n));
  if (!v) {
    fprintf(stderr, "vector allocation error.");
    exit(1);
  }

  return v;
}

double **matrix(int r, int c)
{
  int i;
  double **m;

  m = (double **)malloc((size_t)(sizeof(double*) * r));
  if (!m) {
    fprintf(stderr, "matrix row allocation error.");
    exit(1);
  }

  m[0] = (double *)malloc((size_t)(sizeof(double) * (r*c)));
  if (!m[0]) {
    fprintf(stderr, "matrix column allocation error.");
    exit(1);
  }

  for (i = 1; i < r; i++) {
    m[i] = m[i-1] + c;
  }

  return m;
}

double  **multiplyMatrix(int n, double **a, double **b)
{
  int i, j, k;
  double **m;
  
  m = matrix(n, n);

  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      m[i][j] = 0;
    }
  }

  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      for (k = 0; k < n; k++) {
        m[i][j] += a[i][k] * b[k][j];
      }
    }
  }

  return m;
}

#endif
