#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable : 4996)
int min(int a, int b) {
	if (a > b)
		return b;
	return a;
}



FILE* output;
void Merge(int a[], int tp[], int left, int right, int rightend);//


void Msortrecursive(int a[], int tp[], int left, int right)//recursive sort
{
	int Ctr;
	if (left<right) {
		Ctr = (left + right) / 2;
		Msortrecursive(a, tp, left, Ctr);
		Msortrecursive(a, tp, Ctr + 1, right);
		Merge(a, tp, left, Ctr + 1, right);
	}
}
void Merge(int a[], int tp[], int left, int right, int rightend) {
	int i, leftend, num, tem;
	int tmp = left, tmp2 = rightend;
	leftend = right - 1;
	tem = left;
	num = rightend - left + 1;

	while (left <= leftend && right <= rightend) {
		if (a[left] <= a[right])
			tp[tem++] = a[left++];
		else
			tp[tem++] = a[right++];
	}
	while (left <= leftend)
		tp[tem++] = a[left++];
	while (right <= rightend)
		tp[tem++] = a[right++];
	for (i = 0; i<num; i++, rightend--)
		a[rightend] = tp[rightend];
	for (int j = tmp; j <= tmp2; j++)
		fprintf(output, "%d ", a[j]);
	fprintf(output, "\n");

}

int main() {
	FILE* input;
	int size;
	input = fopen("input.txt", "r");
	output = fopen("output.txt", "w");
	fprintf(output, "input : \n");

	fscanf(input, "%d", &size);
	int* tp, *a, tem;
	a = (int*)malloc(sizeof(int)*size);
	tp = (int*)malloc(sizeof(int)*size);

	for (int i = 0; i<size; i++) {
		fscanf(input, "%d", &tem);
		fprintf(output, "%d ", tem);
		a[i] = tem;
	}
	
	fprintf(output, "\n\n");
	fprintf(output, "recursive : \n");
	Msortrecursive(a, tp, 0, size - 1);
	fclose(input);
	fclose(output);
	return 0;
}
