#include<stdio.h>
#include<stdlib.h>


#pragma warning(disable: 4996)
int min(int X, int Y) {
	return  (X) > (Y) ? (Y) : (X);
}
int arr[101];
int matrix[101][101];

typedef struct Node {
	int key;
	int wgt;
	int path;
}Node;
typedef struct Heap {
	int cap;
	int size;
	Node* element;
}Heap;
typedef Heap* heap;

FILE *out;

heap createMinHeap(int heapsize)// 힙사이즈로 힙만들기
{
	heap H = (heap)malloc(sizeof(Heap));
	H->cap = 0;

	H->size = heapsize;

	H->element = (Node*)malloc(sizeof(Node)*H->size);
	for (int i = 1; i<H->size; i++) {
		H->element[i].wgt = 99999;
		H->element[i].path = 0;
	}
	return H;
}
int insert(heap H, int vertex, int distance, int pre)//거리 삽입
{
	int ai = 0;
	for (int i = 1; i <= H->cap; i++) {
		if (H->element[i].key == vertex) {
			if (H->element[i].wgt>distance) {
				
				H->element[i].path = pre;
				H->element[i].wgt = distance;
				
			}
			ai = 1;
		}
	}
	if (ai == 1)
		return 1;
	else {
		int i;
		for (i = ++H->cap; H->element[i / 2].wgt>distance; i /= 2) {
			H->element[i].key = H->element[i / 2].key;
			H->element[i].path = H->element[i / 2].path;
			H->element[i].wgt = H->element[i / 2].wgt;
			
		}
		H->element[i].key = vertex;
		H->element[i].path = pre;
		H->element[i].wgt = distance;
		
		return 0;
	}
}
Node* deleteMin(heap H)//힙 삭제
{
	Node* temp1 = (Node*)malloc(sizeof(Node));
	temp1->key = H->element[1].key;
	temp1->wgt = H->element[1].wgt;
	temp1->path = H->element[1].path;
	int i, ch, k, w, p;
	k = H->element[H->cap].key;
	w = H->element[H->cap].wgt;
	p = H->element[H->cap--].path;
	for (i = 1; i * 2 <= H->cap; i = ch) {
		ch = i * 2;
		if (ch != H->cap&&H->element[ch].wgt>H->element[ch + 1].wgt)
			ch++;
		if (w>H->element[ch].wgt) {
			H->element[i].key = H->element[ch].key;
			H->element[i].wgt = H->element[ch].wgt;
			H->element[i].path = H->element[ch].path;
		}
		else
			break;
	}
	H->element[i].key = k;
	H->element[i].wgt = w;
	H->element[i].path = p;
	return temp1;
}

int IsEmpty(int matrix[][101], int size)// 엠티 체크
{
	for (int i = 0; i<size; i++) {
		for (int j = 0; j<size; j++)
			if (matrix[i][j]<99999)
				return 0;
	}
	return 1;
}
void daikstra(int arr[],int matrix[][101], heap H, int size, int st)//힙을 사용한 다익스트라 시작
{
	if (IsEmpty(matrix, size) == 0) {
		int m, president=0, t, te = 0;
		int next[101][2];
		for (int i = 0; i<size; i++) {
			if (H->element[i].key == arr[st])
				president = H->element[i].wgt;
		}
		for (int i = 0; i<size; i++) {
			if (matrix[st][i]<99999) {
				t = insert(H, arr[i], president + matrix[st][i], arr[st]);
				if (t == 0) {
					next[te][0] = i;
					next[te++][1] = matrix[st][i];
				}
				matrix[st][i] = 99999;
			}
		}
		for (int i = 0; i<te - 1; i++)
		{
			int Imin = i;
			for (int j = i + 1; j<te; j++)
			{
				if (next[j][1] < next[Imin][1])
				{
					Imin = j;
				}
			}
			int temp = next[Imin][0];
			next[Imin][0] = next[i][0];
			next[i][0] = temp;
			temp = next[Imin][1];
			next[Imin][1] = next[i][1];
			next[i][1] = temp;
		}
		for (int i = 0; i<te; i++) {
			daikstra(arr, matrix, H, size, next[i][0]);
		}
	}

}
void printShortestPath(int* path, int end, int size)//결과 출력
{
	int arr[101];
	int temp = 0;
	arr[temp++] = end;
	while (path[end] >= 0) {
		if (temp>size || path[end] == 0) {
			fprintf(out, "error\n");
			return;
		}
		
		arr[temp++] = path[end];
		end = path[end];
	}
	for (int i = temp - 1; i >= 0; i--)
		fprintf(out, "%d ", arr[i]);

}
int main() {
	FILE* in;
	in = fopen("input.txt", "r");
	out = fopen("output.txt", "w");

	int size = 0, a, b, c, ta = 0;
	char t, te, tem=0;
	fscanf(in, "%d%c", &arr[size++], &t);
	while (t != '\n') {
		fscanf(in, "%d%c", &arr[size++], &t);
	}
	for (int i = 0; i < 101; i++) {
		for (int j = 0; j < 101; j++) {
			matrix[i][j] = 99999;

		}
}

	while (tem != '\n') {
		fscanf(in, "%d%c%d%c%d%c", &a, &t, &b, &te, &c, &tem);
		int i, j;
		for (i = 0; i<size; i++) {
			if (arr[i] == a)
				break;
		}
		for (j = 0; j<size; j++) {
			if (arr[j] == b)
				break;
		}
		matrix[i][j] = c;
		ta++;
	}
	heap H = createMinHeap(ta);
	int start, end;
	fscanf(in, "%d%c%d", &start, &t, &end);
	insert(H, start, 0, -1);
	int st;
	for (st = 0; st<size; st++) {
		if (arr[st] == start)
			break;
	}
	daikstra(arr, matrix, H, size, st);
	Node* temp;
	int* ar = (int*)malloc(sizeof(int)*(size + 1));
	while (H->cap>0) {
		temp = deleteMin(H);
		ar[temp->key] = temp->path;
	}
	printShortestPath(ar, end, size);
	fclose(in);
	fclose(out);
	return 0;
}

