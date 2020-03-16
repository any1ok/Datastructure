#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable: 4996)
char a[10];
char in[5];
FILE *ifp;
FILE *ofp;
int Hash(int *arr, int size, int solution,int value)// 같은것이 있으면 멈추고 가는길에 0 이있으면 0에서 멈춰 그 위치를 리턴하는 함수
{
	int i=0;
	int h = value % size;
	int hstart = h;
	int istart = 0;
	if (solution == 1) {
		while (arr[h] != 0) {
			if (arr[h] == value)
				return h;
			i++;
			h = hstart + i;
			h = h % size;
		}
		return h;
	}
	else if (solution == 2) {
		while (arr[h] != 0) {
			if (arr[h] == value)
				return h;
			istart++;
			i = istart * istart;
			h = hstart + i;
			h = h % size;
		}
		return h;

	}
	else {
		while (arr[h] != 0) {
			if (arr[h] == value)
				return h;
			istart++;
			i = istart * ((7 - value % 7) % size);
			h = hstart + i;
			h = h % size;
		}
		return h;
	}
}
int main() {
	ifp = fopen("input.txt", "r");
	ofp = fopen("output.txt", "w");
	int test=0;
	fscanf(ifp,"%d", &test);
	int size;
	while (test--) // 전부 해쉬 함수 하나를 기반으로 위치 찾아 insert find delete 해준다.
	{
		int *arr;
		fscanf(ifp,"%s", a);
		fscanf(ifp,"%d", &size);
		arr = (int*)malloc(sizeof(int)*size);
		for (int i = 0; i < size; i++) 
			arr[i] = 0;
		int solution = 0;
		if (a[0] == 'L') 
			solution = 1;
		else if (a[0] == 'Q') 
			solution = 2;
		else
		 solution = 3;
		
		while (1) {
			fscanf(ifp,"%s", in);
			if (in[0] == 'i') {
				int value=0;
				fscanf(ifp,"%d", &value);
				int pt =Hash(arr, size, solution, value);
				if (arr[pt] == 0) {
					arr[pt] = value;
					fprintf(ofp,"insert %d \n",value);
					}
				else 
					fprintf(ofp,"Already exists\n");
			}
			else if (in[0] == 'd') {
				int value = 0;
				fscanf(ifp,"%d", &value);
				int pt = Hash(arr, size, solution, value);
				if (arr[pt] != 0) {
					arr[pt] = 0;
					fprintf(ofp,"delete %d \n", value);
				}
				else 
					fprintf(ofp,"%d not exists\n",value);
			}
			else if (in[0] == 'f') {
				int value = 0;
				fscanf(ifp,"%d", &value);
				int pt = Hash(arr, size, solution, value);
				if (arr[pt] != 0)
					fprintf(ofp, "%d\n", pt);
				else 
					fprintf(ofp,"Not found\n");
			}
			else if (in[0] == 'p') {
				for (int i = 0; i < size; i++) 
					fprintf(ofp,"%d ",arr[i]);	
				fprintf(ofp,"\n");
			}
			else if (in[0] == 'q') {
				break;
		}
		}
		free(arr);
	}
}