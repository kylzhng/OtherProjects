#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct data{
  char* operation;
  int index1, index2, outputIndex;
}data;

typedef struct node{
  struct data* data;
  struct node* next;
}node;

void print(node* head){
  node* ptr = head;
  int count = 1;
  while(ptr != NULL){
    printf("op%d: %s ", count,  ptr->data->operation);
    ptr = ptr->next;
    count++;
  }  
}

node* insert(void* d, node* head){
  node* prev = NULL, *ptr = head;
  while(ptr != NULL){
    prev = ptr;
    ptr = ptr->next;
  }  

  node* new_node = malloc(sizeof(node));
  new_node->data = d;
  new_node->next = NULL;

  if(prev != NULL){
    prev->next = new_node;
  }
  else head = new_node;
  return head;
}

int getSize(node* head){
  node *ptr = head;
  int count = 0;
  while(ptr != NULL){
    count++;
    ptr = ptr->next;
  }
  return count;
}

void freeList(node* head) {
  if (head == NULL) return;
  node* ptr = head;
  while (ptr->next != NULL) {
    node* next = ptr->next;
    free(ptr->data);
    free(ptr);
    ptr = next;
  }
  free(ptr->data);
  free(ptr);
}

int performOp(char* str, int v1, int v2){
  if (strcmp("AND", str) == 0){
    return v1 && v2;
  }
  else if (strcmp("OR", str) == 0){
    return v1 || v2;
  }
  else if (strcmp("NOT", str) == 0){
    return !v1;
  }
  else if (strcmp("NAND", str) == 0){
    return !(v1 && v2);
  }
  else if (strcmp("NOR", str) == 0){
    return !(v1 || v2);
  }
  else{ //XOR
    return (v1 && !v2) || (!v1 && v2);
  }
}

int getbit(int n, int shift){
  return (n >> shift) & 1;
}

int powOf2(int power){
  return 1 << power;
}

int getI(char** inputs, char* str, int num){
  int i;
  for(i = 0; i < num; i++){
    if(strcmp(inputs[i], str) == 0){
      return i;
    }
  }
  return -1;
}

int getTempI(node* head, char* str){
  node* ptr = head;
  int tmpI = 0;
  while (ptr != NULL) {
    if (strcmp((char*)ptr->data, str) == 0) {
      return tmpI;
    }
    tmpI++;
    ptr = ptr->next;
  }
  return -1;
}



int* eval(node* head, int numI, int numO, int tempSize, int *inputs){
  int rowSize = numI + numO;
  int i;
  int *row =  malloc(sizeof(int) * rowSize);
  int *temp = malloc(sizeof(int) * tempSize);
  for(i = 0; i < numI; i++){
    row[i] = inputs[i];
  }
  node* ptr = head;
  while(ptr != NULL){
    data *d = (data*)ptr->data;
    int i1, i2;
    if(d->index1 < numI){
      i1 = inputs[d->index1];
    }
    else{
      i1 = temp[d->index1 - rowSize]; 
    }
    if(d->index2 >= 0){
      if(d->index2 < numI){
	i2 = inputs[d->index2];
      }
      else{
	if(d->index2-rowSize >= 0)i2 = temp[d->index2 - rowSize];
      }
    }
    int out = performOp(d->operation, i1, i2);
    if(d->outputIndex >= numI && d->outputIndex < numI + numO){
      row[d->outputIndex] = out;
    }
    else{
      temp[d->outputIndex - rowSize] = out;
    }
    ptr = ptr->next;
  }
  free(temp);
  return row;
}

int** evaluate(node *head, int numI, int numO, int tempSize){
  int maxCombos = powOf2(numI);
  int **result = malloc(sizeof(int*) * maxCombos);
  int i, j;
  for(i = 0; i < maxCombos; i++){
    int *vars = (int*) malloc(sizeof(int) * numI);
    for(j = 0; j < numI; j++){
      vars[numI-j-1] = getbit(i, j);
    }
    int* row = eval(head, numI, numO, tempSize, vars);
    free(vars);
    result[i] = row;
  }
  return result;
}

int main(int argc, char* argv[])
{
  if(argc == 1){
    printf("Input file error.\n");
    exit(0);
  }
  FILE* fptr = fopen(argv[1], "r");
  
  if(fptr == NULL) exit(0);
  
  
  int numI;
  fscanf(fptr, "INPUTVAR\t%d\t", &numI);
  int i;
  char **in = (char**) malloc(sizeof(char*) * numI);
  for(i = 0; i < numI; i++){
    in[i] = (char*) malloc(sizeof(char) * 10);
    fscanf(fptr, "%s\t", in[i]);
  }
  
  int numO;
  fscanf(fptr, "OUTPUTVAR\t%d\t", &numO);
  char **out = (char**) malloc(sizeof(char*) * numO);
  for(i = 0; i < numO; i++){
    out[i] = (char*) malloc(sizeof(char) * 10);
    fscanf(fptr, "%s\t", out[i]);
  }
  int maxCombos =  powOf2(numI);
  node *head =  NULL;
  node *tmpHead = NULL;
  int counter = numI+numO;
  while(1){
    char *input1, *input2, *output, *op;
    input1 = (char*) malloc(sizeof(char) * 10);
    input2 = (char*) malloc(sizeof(char) * 10);
    output = (char*) malloc(sizeof(char) * 10);
    op = (char*) malloc(sizeof(char) * 10);
    int x = fscanf(fptr, "%s", op);
   if(x != 1) break;
    data *command = (data*) malloc(sizeof(data));
    command->operation = op;
    
    if(strcmp(op, "NOT") == 0){
      fscanf(fptr, "%s\t%s\t", input1, output);
      command->index2 = -1;
    }
    else{
      fscanf(fptr, "%s\t%s\t%s\t", input1, input2, output);
    }   
    int i1 = getI(in, input1, numI);
    if(i1 >= 0) command->index1 = i1;
    else{
      command->index1 = getTempI(tmpHead, input1) + numI + numO;
    }
    int i2 = getI(in, input2, numI);
    if(i2 >= 0) command->index2 = i2;
    else{
      command->index2 = getTempI(tmpHead, input2) + numI + numO;
    }
    int OI = getI(out, output, numO);
    if(OI >= 0) command->outputIndex = numI + OI;
    else{
      char* tmp_out = (char*) calloc(strlen(output) + 1, sizeof(char));
      strcpy(tmp_out, output);
      tmpHead = insert(tmp_out, tmpHead);
      command->outputIndex = counter++;
    }
    head = insert(command, head);
  }  
  
  int **answer = evaluate(head, numI, numO, getSize(tmpHead));
  int j;
  for(i = 0; i < maxCombos; i++){
    for(j = 0; j < numI + numO; j++){
      printf("%d ", answer[i][j]);
    }
    printf("\n");
  }

  
  for(i = 0; i < numI; i++){
    free(in[i]);
  }
  free(in);
  for(i = 0; i < numO; i++){
    free(out[i]);
  }
  for(i = 0; i < maxCombos; i++){
    free(answer[i]);
  } 
  free(answer);
  freeList(head);
  freeList(tmpHead);
  fclose(fptr);
  return 0;
}
