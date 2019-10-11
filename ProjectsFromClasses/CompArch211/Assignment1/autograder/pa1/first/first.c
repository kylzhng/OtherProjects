#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int main(int argc, char *argv[]){
	FILE *fptr = fopen(argv[1], "r");
	int num;	

	if(fptr == NULL){
	  printf("File not found\n");
	  exit(0);
	}
	fscanf(fptr, "%d\n", &num);
	int i;
	int odd = 0;
	int even = 0;
	int* arr = malloc(sizeof(int) * num);
	for(i = 0; i < num; i++){
	  fscanf(fptr, "%d\t", &arr[i]);
	  if(arr[i] % 2 == 0) even++;
	  else odd++;
	}
	fclose(fptr);

	int* oddArr = malloc(sizeof(int) * odd);
	int* evenArr = malloc (sizeof(int) * even);
	odd = 0;
	even = 0;
	for(i = 0; i < num; i++){
	  if(arr[i] % 2 == 0){
	    evenArr[even] = arr[i];
	    even++;
	  }
	  else{
	    oddArr[odd] = arr[i];
	    odd++;
	  }
	}
	int temp;
	int j;
	for(i = 1; i < odd; i++){
	  j = i-1;
	  temp = oddArr[i];
	  while(j >= 0 && oddArr[j] < temp){	
	    oddArr[j+1] = oddArr[j];
	    j--;
	  }
	  oddArr[j+1] = temp;
	}

	for(i = 1; i < even; i++){
	  j = i-1;
	  temp = evenArr[i];
	  while(j >= 0 && evenArr[j] > temp){
	    evenArr[j+1] = evenArr[j];
	    j--;	
	  }
	  evenArr[j+1] = temp;
	}
	
	for(i = 0; i < even; i++){
	  printf("%d\t", evenArr[i]);
	}
	for(i = 0; i < odd; i++){
	  printf("%d\t", oddArr[i]);
	}
	printf("\n");
	free(arr);
	free(evenArr);
	free(oddArr);
	return 0;
}
