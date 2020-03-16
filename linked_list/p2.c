#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stack>
#include <queue>
#include <vector>
#include <string>
#include <string.h>

using namespace std;

typedef struct {
   int ID;
   char *Name;
} Student;

typedef struct asdf{
   Student S;
   asdf *next;
} node;

void Insert(FILE *p_in, FILE *p_out, node *Head);
void Delete(FILE *p_in, FILE *p_out, node *Head);
void Find(FILE *p_in, FILE *p_out, node *Head);
void Print(FILE *p_out, node *Head);
void pt(FILE *p_out, node* Head);

int main() {
   char option;
   node Head;
   Head.next = NULL;

   FILE *p_in = fopen("input.txt", "r");
   FILE *p_out = fopen("output.txt", "w");

   while (EOF != fscanf(p_in, "%c", &option)) {
      switch (option) {
      case 'i': Insert(p_in, p_out, &Head);
         break;
      case 'd': Delete(p_in, p_out, &Head);
         break;
      case 'f': Find(p_in, p_out, &Head);
         break;
      case 'p': Print(p_out, &Head);
         break;
      }
   }

   fclose(p_in);
   fclose(p_out);
   for (node *idx = Head.next; idx != NULL; ) {
      node* temp = idx;
      free(temp->S.Name);
      idx = idx->next;
      free(temp);
   }
   return 0;
}

void Insert(FILE *p_in, FILE *p_out, node *Head) {
   int Num;
   fscanf(p_in, "%d", &Num);
   char line[10010];
   fscanf(p_in, "%*c");
   fscanf(p_in, "%[^\n]", line);

   node* idx = Head;

   while (idx->next != NULL && (idx->next->S).ID < Num)  
      idx = idx->next;

   if (idx->next == NULL) {
      idx->next = (node*)malloc(sizeof(node));
      (idx->next->S).ID = Num;
      (idx->next->S).Name = (char*)malloc(strlen(line));
      idx->next->next = NULL;
      strcpy((idx->next->S).Name, line);
      fprintf(p_out, "Insertion Success : %d\n", Num);
      pt(p_out, Head);
      return;
   }

   if ((idx->next->S).ID == Num) {
      fprintf(p_out, "Insertion Failed. Student ID %d already exists.\n", Num);
   }
   else {
      node* temp = (node*)malloc(sizeof(node));
      temp->next = idx->next;
      idx->next = temp;
      (temp->S).ID = Num;
      (temp->S).Name = (char*)malloc(strlen(line));
      strcpy((temp->S).Name, line);
      fprintf(p_out, "Insertion Success : %d\n", Num);
      pt(p_out, Head);
   }
}

void Delete(FILE *p_in, FILE *p_out, node *Head) {
   int Num;
   fscanf(p_in, "%d", &Num);
   node* idx = Head;
   while (idx->next != NULL && (idx->next->S).ID != Num)
      idx = idx->next;

   if (idx->next == NULL)
      fprintf(p_out, "Deletion Failed. Student ID %d is not in the list.\n", Num);
   else
   {
      node* temp = idx->next;
      idx->next = idx->next->next;
      free((temp->S).Name);
      free(temp);
      pt(p_out, Head);
   }
}

void Find(FILE *p_in, FILE *p_out, node *Head) {
   int Num;
   fscanf(p_in, "%d", &Num);
   node* idx = Head;
   while (idx->next != NULL && (idx->next->S).ID != Num)
      idx = idx->next;

   if (idx->next == NULL)
      fprintf(p_out, "Find %d Failed. There is no student ID.\n", Num);
   else
      fprintf(p_out, "Find Success : %d %s\n", (idx->next->S).ID, ((idx->next->S).Name));
}

void Print(FILE *p_out, node *Head) {
   fprintf(p_out, "-----LIST-----\n");
   node* idx = Head;
   while (NULL != idx->next)
   {
      fprintf(p_out, "%d %s\n", (idx->next->S).ID, ((idx->next->S).Name));
      idx = idx->next;
   }
   fprintf(p_out, "--------------\n");
}

void pt(FILE *p_out, node *Head)
{
   fprintf(p_out, "Current List > ");
   node* idx = Head;
   bool check = false;
   while (NULL != idx->next)
   {
      if (check)
         fprintf(p_out, "-%d %s", (idx->next->S).ID, (idx->next->S).Name);
      else
         fprintf(p_out, "%d %s", (idx->next->S).ID, (idx->next->S).Name);
      check = true;
      idx = idx->next;
   }
   fprintf(p_out, "\n");
}
