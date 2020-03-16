#include<stdio.h>
#include<stdlib.h>


int main() {
	FILE *fp;
	fp = fopen("input.txt", "r");
	int temp;
	int siz;
	int *num_arr;
	fscanf(fp,"%d", &siz);

	num_arr=(int*)malloc(siz * sizeof(int));
	for (int i = 0; i < siz; i++) {
		fscanf(fp, "%d", &num_arr[i]);

	}
	for (int i = 0; i < siz; i++) {
		for (int j = 0; j < siz - 1; j++) {
			if (num_arr[j] > num_arr[j + 1]) {
				temp = num_arr[j];
				num_arr[j] = num_arr[j + 1];
				num_arr[j + 1] = temp;
			}


		}

	}
	fclose(fp);
	fp = fopen("output.txt", "w");
	for (int i = 0; i < siz; i++) {
		fprintf(fp, "%d ", num_arr[i]);
	}
	fclose(fp);


}
