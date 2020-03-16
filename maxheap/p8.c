#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* in;
FILE* out;
typedef struct {
	int cap;
	int size;
	int *arr;
}t;
typedef t* heap;
heap makeheap(heap h, int size) {
	h = (heap)malloc(sizeof(t));
	h->size = 0;
	h->cap = size;
	h->arr = (int*)malloc(sizeof(int)*(size + 1));
	return h;
}
int is_in(int n, heap h) {
	int i;
	for (i = 1; i <= h->size; ++i) {
		if (h->arr[i] == n)
			return 0;
	}

	return 1;
}

void insert(int element, heap h) {
	int i;
	if (!is_in(element, h)) {
		fprintf(out, "%d is already in the heap.\n", element);
		return;
	}
	else if (h->size == h->cap) {
		fprintf(out, "heap is full\n");
		return;
	}
	fprintf(out, "insert %d\n", element);
	++(h->size);
	h->arr[(h->size)] = element;
	for (i = h->size; i > 1 && h->arr[i / 2] < h->arr[i]; i /= 2) {
		h->arr[i] = h->arr[i / 2];
		h->arr[i / 2] = element;
	}
}
void find(int element, heap h) {
	int i;
	for (i = 1; i <= h->size; ++i)
		if (h->arr[i] == element) {
			fprintf(out, "%d is in the heap.\n", element);
			return;
		}

	fprintf(out, "%d is not in the heap.\n", element);
	return;

}
void print(heap h) {
	int i;
	for (i = 1; i <= h->size; ++i)
		fprintf(out, "%d ", h->arr[i]);
	fprintf(out, "\n");
}




int main() {
	in = fopen("input.txt", "r");
	out = fopen("output.txt", "w");
	int n=0;
	fscanf(in, "%d", &n);
	heap h=NULL; 
	h =makeheap(h, n);
	char a[10];
	while (1) {
		fscanf(in, "%s", a);
		if (a[0] == 'i') {
			int k=0;
			fscanf(in, "%d", &k);
			insert(k, h);
		}
		else if (a[0] == 'f') {
			int k;
			fscanf(in, "%d", &k);
			find(k, h);
		}
		else if (a[0] == 'p') {
			print(h);
			fclose(in);
			fclose(out);
			free(h->arr);
			free(h);
			return 0;
		}

	}


}

