#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct node{
  struct node* next;
  int data;
} node;

const int table_size = 10000;
node** hashtable;

void initialize(){
  hashtable = malloc(sizeof(node*)* table_size);
  int i;
  for(i = 0; i < table_size; i++){
    hashtable[i] = NULL;
  }
}

int hash(int v){
  int x = v % table_size;
  if(x<0) x+= table_size;
  return x;
}

int insert(int v){
  int key = hash(v);
  node* nodeToAdd = malloc(sizeof(node));
  nodeToAdd->data = v;
  if(hashtable[key] != NULL){
    nodeToAdd->next = hashtable[key];
    hashtable[key] = nodeToAdd;
    return 1;
  }
  nodeToAdd->next = NULL;
  hashtable[key] = nodeToAdd;
  return 0;
}

int search(int v){
  int key = hash(v);
  node* ptr = hashtable[key];
  while(ptr != NULL){
    if(ptr->data == v) return 1;
    ptr = ptr->next;
  }
  return 0;
}

void freeList(node* head){
  if(head == NULL) return;
  node* ptr = head;
  while(ptr != NULL){
    node* next = ptr->next;
    free(ptr);
    ptr = next;
  }
}

void freeTable(){
  int i;
  for(i = 0; i < table_size; i++){
    node* ptr = hashtable[i];
    freeList(ptr);
  }
  free(hashtable);
}

int main(int argc, char* argv[]){
  initialize();
  
  FILE* fptr = fopen(argv[1], "r");

  int collisions = 0, searches = 0;

  char type;
  int val;
  while(fscanf(fptr, "%c\t%d\n", &type, &val) == 2){
    if(type == 'i'){
      int res = insert(val);
      if(res) collisions++;
    }
    else if(type == 's'){
      int res = search(val);
      if(res) searches++;
    }
  }

  printf("%d\n%d\n", collisions, searches);

  freeTable();
  fclose(fptr);
  return 0;
}
