#include<stdio.h>
#include<stdlib.h>

int arr[100];
int size = 0;
int idx = 0;
int main() {
 FILE *fp;//파일 입출력
 FILE *tp;
 int n;
 fp = fopen("input.txt", "r");

 fscanf(fp, "%d", &n);
 tp = fopen("output.txt", "w");

 // idx 를 사용하여 queue 의 first in first out 을 구현했습니다.

 while (n--) {
  // 이하 부분은 enQ 할때
  char *str = (char*)malloc(sizeof(char) * 10);
  fscanf(fp, "%s", str);
  if (str[0] == 'e') {
   int npush;
   fscanf(fp, "%d", &npush);
   if (size == 99) {
    fprintf(fp, "%d\n", "Full");

   }
   else {
    arr[size] = npush;
    size++;
   }

  }
  // 이하 부분은 deQ 할때
  if (str[0] == 'd') {
   if (size == idx) {
    fprintf(tp,"empty");
   }
   else {
    fprintf(tp, "%d\n", arr[idx]);
    idx++;
   }


  }

 }
 fclose(fp);
 fclose(tp);
} 

