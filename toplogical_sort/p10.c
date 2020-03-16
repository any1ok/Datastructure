#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

typedef struct Graph {
	int size;
	int* node;
	int** matrix;
}Gnode;
typedef struct Queue {
	int* key;
	int front;
	int rear;
	int qsize;
	int max_queue_size;
}Qnode;
typedef Gnode* Graph;
typedef Qnode* Queue;
FILE *output;
void printGraphMatrix(Graph G)//그래프 프린트하기
{
	fprintf(output, "Adjacency matrix\n  ");
	for (int i = 0; i<G->size; i++)
		fprintf(output, "%d ", G->node[i]);
	fprintf(output, "\n");
	for (int i = 0; i<G->size; i++) {
		fprintf(output, "%d ", G->node[i]);
		for (int j = 0; j<G->size; j++)
			fprintf(output, "%d ", G->matrix[i][j]);
		fprintf(output, "\n");
	}
}
Graph CreateGraph(int* nodes, int size)// create graph with nodes
{
	Graph G = (Graph)malloc(sizeof(Gnode));
	G->size = size;
	G->node = (int*)malloc(sizeof(int)*(G->size));
	G->matrix = (int**)malloc(sizeof(int*)*(G->size));
	for (int i = 0; i<G->size; i++) {
		G->matrix[i] = (int*)malloc(sizeof(int)*G->size);
		G->node[i] = nodes[i];
	}
	return G;
}
void InsertEdge(Graph G, int a, int b)//그래프 정점에 숫자 넣기
{
	int i, j;
	for (i = 0; i<G->size; i++)
		if (G->node[i] == a)
			break;
	for (j = 0; j<G->size; j++)
		if (G->node[j] == b)
			break;
	G->matrix[i][j]++;
}
void Topsort(Graph G);// 위상정렬 프린트
Queue MakeNewQueue(int num)// 큐 생성
{
	Queue queue = (Queue)malloc(sizeof(Qnode));
	queue->key = (int*)malloc(sizeof(int)*num*num);
	queue->rear = -1;
	queue->front = -1;
	queue->qsize = 0;
	queue->max_queue_size = num * num;
	return queue;
}
void Enqueue(Queue queue, int num)//마지막큐에 값넣기
{
	queue->key[++queue->rear] = num;
	queue->qsize++;
}
int Dequeue(Queue queue)//디큐
{
	int tp = queue->key[++queue->front];
	queue->qsize--;
	return tp;
}
int IsEmpty(Queue queue)//엠티인지 보기
{
	return(queue->rear == queue->front);
}
int Find(Queue queue, int num)//숫자 찾기
{
	for (int i = 0; i <= queue->rear; i++) {
		if (queue->key[i] == num)
			return 0;
	}
	return 1;
}
void Topsort(Graph G) {
	Queue queue;
	queue = MakeNewQueue(G->size);
	int tp, tmp;
	for (int i = 0; i<G->size; i++) {
		tp = 0;
		for (int j = 0; j<G->size; j++) {
			tp = tp + G->matrix[j][i];
		}
		if (tp == 0)
			Enqueue(queue, G->node[i]);
	}
	fprintf(output, "TopSort Result : ");
	while (!IsEmpty(queue)) {
		tp = Dequeue(queue);
		for (int i = 0; i<G->size; i++) {
			if (tp == G->node[i]) {
				tmp = i;
				break;
			}
		}
		fprintf(output, "%d ", tp);
		for (int i = 0; i<G->size; i++)
			if (G->matrix[tmp][i]>0)
				--G->matrix[tmp][i];
		for (int i = 0; i<G->size; i++) {
			tp = 0;
			for (int j = 0; j<G->size; j++) {
				tp = tp + G->matrix[j][i];
			}
			if (tp == 0 && Find(queue, G->node[i]) != 0)
				Enqueue(queue, G->node[i]);
		}
	}
}

int main() {
	FILE *input;
	input = fopen("input.txt", "r");
	output = fopen("output.txt", "w");
	char c;
	char a1[3];
	int i, size = 0;
	int* node = (int*)malloc(sizeof(int) * 10);
	while (c != '\n') {
		fscanf(input, "%c", &c);
		if (isdigit(c)) {
			i = c - '0';
			node[size++] = i;
		}
	}
	Graph G;
	G = CreateGraph(node, size);
	while (EOF != fscanf(input, "%s", a1)) {
		InsertEdge(G, a1[0] - '0', a1[2] - '0');
	}
	printGraphMatrix(G);
	fprintf(output, "\n\n");
	Topsort(G);
	fclose(input);
	fclose(output);
	return 0;
}
