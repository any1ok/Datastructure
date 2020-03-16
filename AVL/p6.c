#include <stdio.h>
#include <string.h>
#include <stdlib.h>

FILE* fp;
FILE* fp1;
typedef struct A tree;
struct A
{
 int data;
 tree* left_child;
 tree* Right_child;
 int height;
};

// a,b 중 큰값 리턴
int Max(int a, int b)
{
 if (a > b)
  return a;
 else
  return b;
}

//height 를 리턴 널이면 -1
int Height(tree* t)
{
 if (t == NULL)
  return -1;
 else
  return t->height;
}

//execute SingleLeft
tree* SL(tree* t)
{
 tree* t1 = t->left_child;
 t->left_child = t1->Right_child;
 t1->Right_child = t;
 t->height = Max(Height(t->left_child), Height(t->Right_child)) + 1;
 t1->height = Max(t->height, Height(t1->left_child)) + 1;
 return t1;
}

//execute SingleRight
tree* SR(tree* t)
{
 tree* t1 = t->Right_child;
 t->Right_child = t1->left_child;
 t1->left_child = t;
 t->height = Max(Height(t->left_child), Height(t->Right_child)) + 1;
 t1->height = Max(t->height, Height(t1->Right_child)) + 1;
 return t1;
}

//execute DoubleLeft
tree* DL(tree* t)
{
 t->left_child = SR(t->left_child);
 return SL(t);
}

//execute DoubleRight
tree* DR(tree* t)
{
 t->Right_child = SL(t->Right_child);
 return SR(t);
}

//find tree 없으면 -1
tree* Find(int n, tree* t)
{
 if (t == NULL)
  return t;
 else if (n < t->data)
  return Find(n, t->left_child);
 else if (n > t->data)
  return Find(n, t->Right_child);
 return t;
}

//return max value in tree
tree* FindMax(tree* t)
{
 if (t == NULL)
  return t;
 tree* temp = t;
 while (temp->Right_child != NULL)
  temp = temp->Right_child;
 return temp;
}

//return min value in tree
tree* FindMin(tree* t)
{
 if (t == NULL)
  return t;
 tree* temp = t;
 while (temp->left_child != NULL)
  temp = temp->left_child;
 return temp;
}

//tree에서 insert를 실행해주며 AVL tree로 만들어준다
tree* insert(int n, tree* t)
{
 if (t == NULL)
 {
  t = (tree*)malloc(sizeof(tree));
  t->data = n;
  t->height = 0;
  t->left_child = NULL;
  t->Right_child = NULL;
 }
 else if (n < t->data)
 {
  t->left_child = insert(n, t->left_child);
  if (Height(t->left_child) - Height(t->Right_child) == 2)
  {
   if (n < t->left_child->data)
    t = SL(t);
   else
    t = DL(t);
  }
 }
 else if (n > t->data)
 {
  t->Right_child = insert(n, t->Right_child);
  if (Height(t->Right_child) - Height(t->left_child) == 2)
  {
   if (n > t->Right_child->data)
    t = SR(t);
   else
    t = DR(t);
  }
 }
 t->height = Max(Height(t->left_child), Height(t->Right_child)) + 1;
 return t;
}

//delete tree
tree* Delete(int n, tree* t)
{
 if (n > t->data)
  t = Delete(n, t->Right_child);
 else if (n < t->data)
  t = Delete(n, t->left_child);
 else if (t->left_child && t->Right_child)
 {
  tree* temp = FindMax(t->left_child);
  t->data = temp->data;
  t->left_child = Delete(temp->data, t->left_child);
 }
 else
 {
  tree* temp = t;
  if (t->left_child == NULL)
   t = t->Right_child;
  else if (t->Right_child == NULL)
   t = t->left_child;
  free(temp);
 }
 return t;
}

//inorder 순으로 tree 높이 출력
void printInorder(tree* t)
{
 if (t)
 {
  printInorder(t->left_child);
  fprintf(fp1, "%d(%d) ", t->data, t->height);
  printInorder(t->Right_child);
 }
}

int main()
{
 fp = fopen("input.txt", "r");
 fp1 = fopen("output.txt", "w");
 tree* t = NULL;
 while (1)
 {
  int n;
  if (fscanf(fp, "%d", &n) == EOF)
   break;
  //n 을 찾고 있으면 오류 없으면 삽입
  if (Find(n, t) != NULL)
   fprintf(fp1, "%d already in the tree!\n", n);
  else
  {
   t = insert(n, t);
   printInorder(t);
   fprintf(fp1, "\n");
  }
 }
 //해제!!!!!
 while (t != NULL)
  t = Delete(t->data, t);
} 

