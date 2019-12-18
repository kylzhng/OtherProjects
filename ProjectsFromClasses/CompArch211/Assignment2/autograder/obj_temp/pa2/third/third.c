#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
  unsigned short x = atoi(argv[1]);
  int i, j = 15, isPalindrome = 0;
  for(i = 0; i < 8; i++){
    if(((x>>i) & 1)  == ((x>>j) & 1)) isPalindrome = 1;
    else{
      isPalindrome = 0;
      break;
    }
    j--;
  }
  if(isPalindrome) printf("Is-Palindrome\n");
  else printf("Not-Palindrome\n");
}
