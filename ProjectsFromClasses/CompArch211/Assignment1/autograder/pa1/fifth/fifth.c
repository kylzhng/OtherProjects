#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isVowel(char c){
  return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U');
}

int main(int argc, char** argv){
  int count = argc-1;
  int i, j, length, numOfVowels = 0, vowels = 0;
  
  for(i = 0; i < count; i++){
    char* str = argv[i+1];
    length = strlen(str);
    for(j = 0; j < length; j++){
      if(isVowel(str[j])) numOfVowels++;
    }
  }
  char* result = malloc(sizeof(char) * (numOfVowels + 1));
  result[numOfVowels] = '\0';
  for(i = 0; i < count; i++){
    char* str = argv[i+1];
    length = strlen(str);
    for(j = 0; j < length; j++){
      if(isVowel(str[j])) result[vowels++] = str[j];
    }
  }

  printf("%s\n", result);
  free(result);

  
  return 0;
}
