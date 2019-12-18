#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int set(unsigned int x, int n, int val){
  if(val == 1){
    x |= (1u << n);
  }
  else{
    x &= ~(1u << n);
  }
  return x;
}

int comp(unsigned int x, int n){
  x ^= (1u << n);
  return x;
}

int get(unsigned int x, int n){
  return ((x >> n) & 1);
}

int main(int argc, char* argv[])
{
  FILE* fptr = fopen(argv[1], "r");
  unsigned int x;
  fscanf(fptr, "%d\n", &x);
  char* scan = malloc(sizeof(char) * 5);
  int n, v;
  
  while(fscanf(fptr, "%s\t%d\t%d\n", scan, &n, &v) == 3){
    if(strcmp(scan, "set") == 0){
      x = set(x, n, v);
      printf("%d\n", x);
    }
    else if(strcmp(scan, "get") == 0){
      printf("%d\n", get(x, n));
    }
    else if(strcmp(scan, "comp") == 0){
      x = comp(x, n);
      printf("%d\n", x);
    }
  }
}
