#include <stdio.h>
#include <stdlib.h>
int main(int argc, char* argv[])
{
  unsigned short x = atoi(argv[1]);
  int count = 0, pairs = 0;
  while(x > 0){
    if((x & 1) == 1){
      count++;
      if(((x >> 1) & 1) == 1){
          count++;
          pairs++;
          x >>= 2;
      }
      else x >>= 1;
    }
    else{
      x >>= 1;
    }
  }
  if(count % 2 == 0){
    printf("Even-Parity\t%d\n", pairs);
  }
  else{
    printf("Odd-Parity\t%d\n", pairs); 
  }
  return 0;
}
