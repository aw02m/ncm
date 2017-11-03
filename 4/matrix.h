#ifndef MATRIX_H
#define MATRIX_H

#include<stdio.h>
#include<stddef.h>
#include<stdlib.h>

float **matrix(int r, int c)
{
  int i;
  float **m;

  m = (float **)malloc((size_t)(sizeof(float*) * r));
  if(!m){
    fprintf(stderr, "matrix row allocation error.");
    exit(1);
  }

  m[0] = (float *)malloc((size_t)(sizeof(float) * (r*c)));
  if(!m[0]){
    fprintf(stderr, "matrix column allocation error.");
    exit(1);
  }

  for(i=1;i<r;i++){
    m[i] = m[i-1]+c;
  }

  return m;
}

#endif
