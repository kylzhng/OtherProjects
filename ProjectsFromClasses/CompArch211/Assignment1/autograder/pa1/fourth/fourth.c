#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]){
  FILE* fptr = fopen(argv[1], "r");
  if(fptr == NULL){
    printf("File not found\n");
    exit(0);
  }
  
  int row1, col1, row2, col2,  r, c;
  fscanf(fptr, "%d %d", &row1, &col1);
  int** m1 = malloc(sizeof(int*) * row1);
  for(r = 0; r < row1; r++){
    m1[r] = malloc(sizeof(int) * col1);
    for(c = 0; c < col1; c++){
      fscanf(fptr, "%d", &m1[r][c]);
    }
  }
  fscanf(fptr, "%d %d", &row2, &col2);
  int** m2 = malloc(sizeof(int*) * row2);

  for(r = 0; r < row2; r++){
    m2[r] = malloc(sizeof(int) * col2);
    for(c = 0; c < col2; c++){
      fscanf(fptr, "%d", &m2[r][c]);
    }
  }
  if(col1 != row2){
    printf("bad-matrices");
    exit(0);
  }
  int** res = malloc(sizeof(int*) * row1);
  int k;
  int j = col1;
  for(r = 0; r < row1; r++){
    res[r] = malloc(sizeof(int) * col2);
    for(c = 0; c < col2; c++){
      res[r][c] = 0;
      for(k = 0; k < j; k++){
	res[r][c] += m1[r][k] * m2[k][c];
      }
    }
  }
  for(r = 0; r < row1; r++){
    for(c = 0; c < col2; c++){
      printf("%d\t", res[r][c]);
    }
    printf("\n");
  }
  free(m1);
  free(m2);
  free(res);
  return 0;
}
