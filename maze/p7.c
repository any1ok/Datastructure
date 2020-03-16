#include<stdio.h>
#include<stdlib.h>
#include<time.h>


FILE* ffp;

int search1(int X, int* MAP)//search X in map  
{
	if (MAP[X] <= 0)
		return X;
	else
		return(MAP[X] = search1(MAP[X], MAP));
}

int search2(int X, int* MAP)//search X  MAP 
{
	while (MAP[X]>0)
		X = MAP[X];
	return X;
}
void Sum(int* MAP, int root1, int root2)//sum MAP1 and MAP2
{
	if (MAP[root1]>MAP[root2])
		MAP[root1] = root2;
	else
	{
		if (MAP[root1] == MAP[root2])
			MAP[root1]--;
		MAP[root2] = root1;
	}
}

int inMAPone(int* MAP, int a)//check  MAP in array
{
	int tp = 0;
	for (int i = 1; i <= a; i++) {
		if (MAP[i] <= 0)
			tp++;
	}
	if (tp == 1)
		return 0;
	else
		return 1;
}

void printMaze(int** Maze, int tp, int temp)//print maze 
{
	int * tem1 = (int*)malloc(2*sizeof(int)*tp * (tp - 1));

	for (int i = 0; i<tp * 2 * (tp - 1); i++)
		tem1[i] = 0;
	for (int i = 0; i<temp; i++) {
		int x = Maze[i][0], y = Maze[i][1];
		if (y - x == 1)
			tem1[x - x / tp - 1] = 1;
		else
			tem1[tp*(tp - 1) + x - 1] = 1;
	}
	fprintf(ffp, "+");
	for (int i = 0; i<tp; i++) {
		fprintf(ffp, "-+");
	}
	fprintf(ffp, "\n");
	for (int i = 0; i<2 * tp - 1; i++) {
		if (i % 2 == 0) {
			if (i == 0)
				fprintf(ffp, " ");
				
			else
				fprintf(ffp, "|");
			for (int j = 0; j<tp - 1; j++) {
				fprintf(ffp, " ");
				if (tem1[j + i / 2 * (tp - 1)] == 1)
					fprintf(ffp, "|");
				else
					fprintf(ffp, " ");
			}
			if (i != 2 * tp - 2)
				fprintf(ffp, " |\n");
			else
				fprintf(ffp, "  \n");
		}
		else if (i % 2 == 1) {
			for (int j = 0; j<tp; j++) {
				fprintf(ffp, "+");
				if (tem1[tp*(tp - 1) + j + ((i - 1) / 2)*tp] == 1)
					fprintf(ffp, "-");
				else
					fprintf(ffp, " ");
			}
			fprintf(ffp, "+\n");
		}
	}
	fprintf(ffp, "+");
	for (int i = 0; i<tp; i++)
		fprintf(ffp, "-+");
}


int main() {
	FILE* fp;
	ffp = fopen("output.txt", "w");
	fp = fopen("input.txt", "r");
	int a;
	fscanf(fp, "%d", &a);
	int* MAP = (int*)malloc(sizeof(int)*(a*a + 1));
	for (int i = 1; i <= a * a; i++) {
		MAP[i] = 0;
	}
	int** wall = (int**)malloc(sizeof(int*) * 2 * a*(a - 1));
	int** Maze = (int**)malloc(sizeof(int*) * 2 * (a - 1)*a);
	int tp = 0;

	for (int i = 0; i<a*(a - 1) * 2; i++) {
		wall[i] = (int*)malloc(sizeof(int) * 2);
		Maze[i] = (int*)malloc(sizeof(int) * 2);
	}

	for (int i = 0; i<a; i++) {
		for (int j = i * a + 1; j <= i * a + a - 1; j++) {
			wall[tp][0] = j;
			wall[tp][1] = j + 1;
			tp++;
		}
	}

	for (int i = 0; i<a - 1; i++) {
		for (int j = i * a + 1; j <= i * a + a; j++) {
			wall[tp][0] = j;
			wall[tp][1] = j + a;
			tp++;
		}
	}
	int temp = 0;
	srand((unsigned int)time(NULL));

	while (inMAPone(MAP, a*a) == 1) {
		int x;


		x = rand() % tp;
		int y = wall[x][0], z = wall[x][1];
		int u = search1(y, MAP);
		int v = search1(z, MAP);

		for (int i = x; i<tp - 1; i++) {
			wall[i][0] = wall[i + 1][0];
			wall[i][1] = wall[i + 1][1];
		}
		tp--;

		if (u != v)
			Sum(MAP, u, v);
		else {
			Maze[temp][0] = y;
			Maze[temp][1] = z;
			temp++;
		}
	}

	for (int i = 0; i<tp; i++) {
		Maze[temp][0] = wall[i][0];
		Maze[temp][1] = wall[i][1];
		temp++;
	}

	for (int i = 0; i<2 * a*(a - 1); i++) {
		free(wall[i]);
	}

	free(wall);
	printMaze(Maze, a, temp);
	for (int i = 0; i<2 * a*(a - 1); i++) {
		free(Maze[i]);
	}

	free(Maze);
	fclose(fp);

	fclose(ffp);
	return 0;
}