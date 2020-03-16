
#include<stdio.h>
#include<stdlib.h>

int arr[100];
int size = 0;
int main() {
 FILE *fp= NULL;
 FILE *tp = NULL;
 int n;// 파일 ㅁ입출력 입니다.
 fp = fopen("input.txt", "rt");
 
 
 fscanf(fp, "%d", &n);
 tp = fopen("output.txt", "wt");
 
 // size 를 올려가면 현재 top 위치를 받는 형식으로 구현했어요
 while (n--) {
  
  char *str = (char*)malloc(sizeof(char) * 10);
  fscanf(fp, "%s", str);
  if (str[1] == 'u') {
   int npush;
   fscanf(fp, "%d", &npush);
   if (size == 99) {
    fprintf(fp,"%d\n","Full");

   }
   else{
    arr[size] = npush;
    size++;
   }

  }
  if (str[1] == 'o') {
   if (size == 0) {
    fprintf(tp,"empty");
   }
   else {
    fprintf(tp, "%d\n", arr[size-1]);
    size--;
   }


  }

 }
 fclose(fp);
 fclose(tp);
} 

