#include<stdio.h>
#include<stdlib.h>
#include<string.h>

FILE* fp;
FILE* fp1;

typedef struct TreeNode tree;
struct TreeNode {
 int gap_input;
 tree* l_child;
 tree* r_child;
};

// gap_input-> print error, or insert
tree* InsertNode(int gap_input, tree* root)
{
 if (root == 0)
 {
  root = (tree*)malloc(sizeof(tree));
  root->gap_input = gap_input;
  root->l_child = 0;
  root->r_child = 0;
 }
 else if (gap_input < root->gap_input)
  root->l_child = InsertNode(gap_input, root->l_child);
 else if (gap_input > root->gap_input)
  root->r_child = InsertNode(gap_input, root->r_child);
 else
  fprintf(fp1, "%d already exists.\n", gap_input);
 return root;
}

//tree most big return tree*  if(  root is null then root return
tree* FindMax(tree* root)
{
 if (root == 0)
  return root;
 while (root->r_child != 0)
  root = root->r_child;
 return root;
}

 

//find node or return 0
tree* FindNode(int gap_input, tree *root)
{
 if (root == 0)
  return root;
 else if (root->gap_input == gap_input)
  return root;
 else if (root->gap_input > gap_input)
  return FindNode(gap_input, root->l_child);
 else
  return FindNode(gap_input, root->r_child);
}
// delete node
tree* DeleteNode(int gap_input, tree *root)
{
 if (root == 0)
  fprintf(fp1, "Deletion failed. %d does not exist.\n", gap_input);
 else if (root->gap_input > gap_input)
  root->l_child = DeleteNode(gap_input, root->l_child);
 else if (root->gap_input < gap_input)
  root->r_child = DeleteNode(gap_input, root->r_child);
 else if (root->r_child != 0 && root->l_child != 0)
 {
  tree* tmp = FindMax(root->l_child);
  root->gap_input = tmp->gap_input;
  root->l_child = DeleteNode(tmp->gap_input, root->l_child);
 }
 else
 {
  tree* tmp = root;
  if (root->l_child == 0)
   root = root->r_child;
  else if (root->r_child == 0)
   root = root->l_child;
  free(tmp);
 }
 return root;
}

//print tree inorder
void PrintInorder(tree *root)
{
 if (root == 0)
  return;
 else
 {
  PrintInorder(root->l_child);
  fprintf(fp1, "%d ", root->gap_input);
  PrintInorder(root->r_child);
 }
}

//print tree preorder
void PrintPreorder(tree *root)
{
 if (root == 0)
  return;
 else
 {
  fprintf(fp1, "%d ", root->gap_input);
  PrintPreorder(root->l_child);
  PrintPreorder(root->r_child);
 }
}

//print tree postorder
void PrintPostorder(tree *root)
{
 if (root == 0)
  return;
 else
 {
  PrintPostorder(root->l_child);
  PrintPostorder(root->r_child);
  fprintf(fp1, "%d ", root->gap_input);
 }
}

 

int main()
{
 fp = fopen("input.txt", "r");
 fp1 = fopen("output.txt", "w");
 //make tree
 tree* tr = 0;
 while (1)
 {
  char ch[3];
  if (fscanf(fp, "%s", ch) == EOF)
   break;
  else if (ch[0] == 'i')
  {
   // insert k
   int input;
   fscanf(fp, "%d", &input);
   tr = InsertNode(input, tr);
  }
  else if (ch[0] == 'd')
  {
   //input delete
   int input;
   fscanf(fp, "%d", &input);
   tr = DeleteNode(input, tr);
  }
  else if (ch[0] == 'f')
  {
   //input find
   int input;
   fscanf(fp, "%d", &input);
   tree* tmp = FindNode(input, tr);
   if (tmp == 0)
    fprintf(fp1, "%d is not in the tree.\n", input);
   else
    fprintf(fp1, "%d is in the tree.\n", input);
  }
  else if (strcmp(ch, "pi") == 0)
  {
   //print inorder
   fprintf(fp1, "pi - ");
   PrintInorder(tr);
   fprintf(fp1, "\n");
  }
  else if (strcmp(ch, "pr") == 0)
  {
   //print preorder
   fprintf(fp1, "pr - ");
   PrintPreorder(tr);
   fprintf(fp1, "\n");
  }
  else if (strcmp(ch, "po") == 0)
  {
   //print postorder
   fprintf(fp1, "po - ");
   PrintPostorder(tr);
   fprintf(fp1, "\n");
  }
 }
 //free every node
 while (tr != 0)
  tr = DeleteNode(tr->gap_input, tr);
}
