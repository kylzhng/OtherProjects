#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
  int data;
  struct node* left;
  struct node* right;
} node;

node* insert(int k, node* root){
  node* prev = NULL, *ptr = root;
  int c = 0;
  while(ptr != NULL){
    if(k < ptr->data) c = -1;
    else if (k > ptr->data) c = 1;
    else c = 0;
    if(c == 0) return root;
    prev = ptr;
    if(c < 0) ptr = ptr->left;
    else ptr = ptr->right;
  }
  node* nodeToAdd = malloc(sizeof(node));
  nodeToAdd->data = k;
  nodeToAdd->left = NULL;
  nodeToAdd->right = NULL;
  
  if(prev == NULL) root = nodeToAdd;
  else if(c<0) prev->left = nodeToAdd;
  else prev->right = nodeToAdd;

  return root;
}

void inOrderPrint(node* root){
  if(root == NULL) return;
  inOrderPrint(root->left);
  printf("%d\t", root->data);
  inOrderPrint(root->right);
}

void freeBST(node* root){
  if(root == NULL) return;
  freeBST(root->left);
  freeBST(root->right);
  free(root);
}

int main(int argc, char* argv[]){
  FILE* fptr = fopen(argv[1], "r");
  
  node* root = NULL;
  int key;
  while(fscanf(fptr, "i\t%d\n", &key) == 1){
    root = insert(key, root);
  }
  inOrderPrint(root);
  printf("\n");
  
  freeBST(root);
  fclose(fptr);
  return 0;

}
