#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Node {
  int data;
  struct Node* next;
}node;

node* insert(int d, node* head){
  node *prev = NULL, *ptr = head;
  while(ptr != NULL){
    if( ((prev == NULL) || (prev!= NULL && prev->data <= d)) && d <= ptr->data) break;
    prev = ptr;
    ptr = ptr->next;
  }
  
  node* nodeToAdd = malloc(sizeof(node));
  nodeToAdd->data = d;
  nodeToAdd->next = ptr;
  if(prev != NULL) prev->next = nodeToAdd;
  else head = nodeToAdd;
  return head;
}

node* delete(int d, node* head){
  node *prev = NULL, *ptr = head;
  while(ptr != NULL){
    if(ptr->data == d) break;
    prev = ptr;
    ptr = ptr->next;
  }
  if(ptr != NULL){
    if(prev == NULL){
      head = ptr->next;
    }
    else{
      prev->next = ptr->next;
    }
  }
  free(ptr);
  return head;
}

int getSize(node* head){
  node* ptr = head;
  int size = 0;
  while(ptr != NULL){
    size++;
    ptr = ptr->next;
  }
  return size;
}

void print(node* head){
  node* ptr = head;
  int last;
  while(ptr != NULL){
    if(ptr == head || last != ptr->data){
      printf("%d", ptr->data);
      if(ptr->next == NULL) printf("\n");
      else printf("\t");
    }
      last = ptr->data;
      ptr = ptr->next;
  }
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

int main(int argc, char** argv){
  FILE *fptr = fopen(argv[1], "r");
  if(fptr == NULL){
    printf("error\n");
    exit(0);
  }
  char c;
  int d;
  node* head = NULL;

  while(fscanf(fptr, "%c\t%d\n", &c, &d) == 2){
    if(c == 'i'){
      if(head == NULL){
	head = malloc(sizeof(node));
	head->data = d;
	head->next = NULL;
      }
      else head = insert(d, head);
    }
    else if(c == 'd'){
      head = delete(d, head);
    }
  }
  int size = getSize(head);
  printf("%d\n", size);
  if(size > 0) print(head);

  freeList(head);
  fclose(fptr);
  return 0;
}
