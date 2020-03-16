#include<stdio.h>
#include<stdlib.h>

typedef struct {
   char in;
   int pre;
}type;
type a[100];
char save[100];
int number[100];

int add(int a, int b) {
   return a + b;
}
int m(int a, int b) {
   return a - b;
}
int di(int a, int b) {
   return a / b;
}
int mul(int a, int b) {
   return a * b;
}
int namu(int a, int b) {
   return a % b;
}

int main() {
   FILE *fp;
   FILE *tp;
   fp = fopen("input.txt", "r");
   tp = fopen("output.txt", "w");
   int size = 0;
   fprintf(tp, "Infix Form : ");
   // 아래는 중요도 순서대로 입력을 하였어요;
   //구조체를 이용하요 in은 char 받구요 pre 에는 중요도를 받았어요.
   while (fscanf(fp, "%c", &a[size].in) != EOF) {
      if (a[size].in == '#') {
         a[size].pre = 5;
         break;
      }

      else if (a[size].in == ')') {
         a[size].pre = 4;

      }
      else if (a[size].in == '(') {
         a[size].pre = 3;

      }
      else if (a[size].in == '*' || a[size].in == '%' || a[size].in == '/') {
         a[size].pre = 2;

      }

      else if (a[size].in == '+' || a[size].in == '-') {
         a[size].pre = 1;

      }
      else {
         a[size].pre = 0;

      }
      fprintf(tp, "%c", a[size].in);
      size++;// 배열크기 측정이요;


   }
   fprintf(tp, "\n");
   fprintf(tp, "Postfix Form : ");

   char stack[100];//스택 사용;

   int idx = -1, ssize = 0;// 비어있음을 나타내는 인뎃스
                     // 이 밑은 배운것처럼 중요도에따라 출력을 해왔어요
   for (int i = 0; i <= size; i++) {

      if (a[i].pre == 5) {
         while (!(idx == -1)) {
            fprintf(tp, "%c", stack[idx]);
            save[ssize++] = stack[idx];
            idx--;
         }
         break;
      }
      else if (a[i].pre == 0) {
         fprintf(tp, "%c", a[i].in);
         save[ssize++] = a[i].in;
      }
      else if (a[i].pre == 1) {
         while (!(idx == -1 || stack[idx] == '(')) {
            //fprintf(tp,"%c",stack[idx]);
            fprintf(tp, "%c", stack[idx]);
            save[ssize++] = stack[idx];
            idx--;
         }
         stack[++idx] = a[i].in;
      }
      else if (a[i].pre == 2) {
         while (!(idx == -1 || stack[idx] == '(' || stack[idx] == '+' || stack[idx] == '-')) {
            //fprintf(tp,"%c",stack[idx]);
            fprintf(tp, "%c", stack[idx]);
            save[ssize++] = stack[idx];
            idx--;
         }
         stack[++idx] = a[i].in;
      }
      else if (a[i].pre == 3) {
         stack[++idx] = a[i].in;
      }
      else {
         while (!(stack[idx] == '(')) {
            //fprintf(tp,"%c",stack[idx]);
            fprintf(tp, "%c", stack[idx]);
            save[ssize++] = stack[idx];
            idx--;
         }
         idx--;
      }

   }
   fprintf(tp, "\n");
   int pts = 0;
   for (int i = 0; i < ssize; i++) {
      if (save[i] == '+') {
         pts--;
         number[pts - 1] = add(number[pts - 1], number[pts]);
      }
      else if (save[i] == '-') {
         pts--;
         number[pts - 1] = m(number[pts - 1], number[pts]);
      }
      else if (save[i] == '/') {
         pts--;
         number[pts - 1] = di(number[pts - 1], number[pts]);
      }
      else if (save[i] == '*') {
         pts--;
         number[pts - 1] = mul(number[pts - 1], number[pts]);
      }
      else if (save[i] == '%') {
         pts--;
         number[pts - 1] = namu(number[pts - 1], number[pts]);
      }
      else {
         number[pts] = save[i] - 48;
         pts++;
      }
   }
   fprintf(tp, "Evalutation Result : ");
   fprintf(tp, "%d", number[0]);
} 

