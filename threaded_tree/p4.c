#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* fp;
FILE* fp1;

typedef struct NODE tree;
struct NODE {
 int left_thr;
 tree* left_c; //left child
 char data;
 tree* right_c;//right child
 int right_thr;
};

//make a Tree
tree* createTree()
{
 tree* t = (tree*)malloc(sizeof(tree));
 t->left_thr = 1;
 t->left_c = 0;
 t->right_c = 0;
 t->right_thr = 1;
 
 return t;
}

//do inorder traversal and return tree next to t
tree* insucc(tree* t)
{
 tree* temp = t->right_c;
 if (!t->right_thr)
  while (!temp->left_thr)
   temp = temp->left_c;
 return temp;
}

//do tinorder traversal and print it to file
void tinorder(tree* t)
{
 tree* temp = t;
 while (1)
 {
  temp = insucc(temp);
  if (temp == t)
   break;
  fprintf(fp1, "%c ", temp->data);
 }
}

int main()
{
 int n;
 fp = fopen("input.txt", "r");
 fp1 = fopen("output.txt", "w");

 fscanf(fp, "%d", &n);
 char ch[101];

 //make root
 tree* t = createTree();
 t->right_thr = 0;
 t->right_c = t;

 //creat trees with value A to I and put into array
 tree** tr = (tree**)malloc(sizeof(tree*) * (n + 1));

 for (int i = 1; i <= n; i++)
 {
  tr[i] = createTree();
  fscanf(fp, "%s", ch);
  tr[i]->data = ch[0];
 }
 //connect root's child to A
 t->left_c = tr[1];
 t->left_thr = 0;
 //connect nodes that are not thread child
 for (int i = 1; i <= n / 2; i++)
 {
  tr[i]->left_c = tr[i * 2];
  tr[i]->left_thr = 0;
  if (i * 2 + 1 <= n)
  {
   tr[i]->right_c = tr[i * 2 + 1];
   tr[i]->right_thr = 0;
  }
 }
 //connect thread child 
 tr[5]->left_c = tr[2];
 tr[5]->right_c = tr[1];
 tr[6]->left_c = tr[1];
 tr[6]->right_c = tr[3];
 tr[7]->left_c = tr[3];
 tr[7]->right_c = t;
 tr[8]->left_c = t;
 tr[8]->right_c = tr[4];
 tr[9]->left_c = tr[4];
 tr[9]->right_c = tr[2];
 tinorder(t);
 for (int i = 1; i <= n; i++)
  free(tr[i]);
 free(tr);
 free(t);
} 

