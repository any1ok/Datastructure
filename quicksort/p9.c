#include<stdio.h>
#include<stdlib.h>

#define order 3
FILE *output;
struct B_node
{
	int n_keys; //키 수
	struct B_node *node[order + 1];
	int data[order];
};
typedef struct B_node* B_tree;
B_tree ptr = NULL;
B_tree Findpre(B_tree root, int k) {
	for (int i = 0; i<root->n_keys; i++)
		if (root->data[i] == k)
			return NULL;
	if (root->n_keys == 1) {
		if (root->data[0]<k) {
			for (int i = 0; i<root->node[0]->n_keys; i++) {
				if (root->node[0]->data[i] == k)
					return root;
			}
			return Findpre(root->node[3], k);
		}
		else {
			for (int i = 0; i<root->node[3]->n_keys; i++) {
				if (root->node[3]->data[i] == k)
					return root;
			}
			return Findpre(root->node[0], k);
		}
	}
	else {
		if (root->data[0]>k) {
			for (int i = 0; i<root->node[0]->n_keys; i++)
				if (root->node[0]->data[i] == k)
					return root;
			return Findpre(root->node[0], k);
		}
		else if (root->data[2]<k) {
			for (int i = 0; i<root->node[3]->n_keys; i++)
				if (root->node[3]->data[i] == k)
					return root;
			return Findpre(root->node[3], k);
		}
		else {
			for (int i = 0; i<root->node[1]->n_keys; i++)
				if (root->node[1]->data[i] == k)
					return root;
			return Findpre(root->node[1], k);
		}
	}
}
B_tree split(B_tree ptr, B_tree root)//b 트리를 split 해주는 함수
{
	int k = ptr->data[1];
	B_tree tmp = Findpre(root, k);
	if (tmp == NULL) {
		B_tree tem1, tem2;
		tem1 = (B_tree)malloc(sizeof(struct B_node));
		tem2 = (B_tree)malloc(sizeof(struct B_node));
		ptr->n_keys = tem1->n_keys = tem2->n_keys = 1;
		tem1->data[0] = ptr->data[0];
		tem2->data[0] = ptr->data[2];
		ptr->data[0] = ptr->data[1];
		ptr->data[1] = ptr->data[2] = 0;
		tem1->node[0] = ptr->node[0];
		tem1->node[3] = ptr->node[1];
		tem2->node[0] = ptr->node[2];
		tem2->node[3] = ptr->node[3];
		ptr->node[0] = tem1;
		ptr->node[1] = NULL;
		ptr->node[2] = NULL;
		ptr->node[3] = tem2;
		return  ptr;
	}
	else {
		B_tree tem1, tem2;
		tem2 = (B_tree)malloc(sizeof(struct B_node));
		tem1 = (B_tree)malloc(sizeof(struct B_node));
		
		tem1->n_keys = tem2->n_keys = 1;
		tem1->data[0] = ptr->data[0];
		tem2->data[0] = ptr->data[2];
		tem1->node[0] = ptr->node[0];
		tem1->node[3] = ptr->node[1];
		tem2->node[0] = ptr->node[2];
		tem2->node[3] = ptr->node[3];
		if (tmp->n_keys == 1) {
			if (k>tmp->data[0]) {
				tmp->data[2] = k;
				tmp->node[1] = tem1;
				tmp->node[3] = tem2;
			}
			else {
				tmp->data[2] = tmp->data[0];
				tmp->data[0] = k;
				tmp->node[0] = tem1;
				tmp->node[1] = tem2;
			}
		}
		else {
			if (k<tmp->data[0]) {
				tmp->data[1] = tmp->data[0];
				tmp->data[0] = k;
				tmp->node[2] = tmp->node[1];
				tmp->node[0] = tem1;
				tmp->node[1] = tem2;
			}
			else {
				tmp->data[1] = tmp->data[2];
				tmp->data[2] = k;
				tmp->node[2] = tem1;
				tmp->node[3] = tem2;
			}
		}
		tmp->n_keys++;
	}
	return tmp;
}
B_tree wherego(int k, B_tree root)// 어느 노드로 가야할지 정해주는 합수
{
	B_tree tmp = root;
	if (tmp->n_keys == 0)
		return tmp;
	while (tmp->node[0] != NULL && tmp != NULL) {
		if (tmp->n_keys == 1) {
			if (tmp->data[0]>k)
				tmp = tmp->node[0];
			else
				tmp = tmp->node[3];
		}
		else {
			if (tmp->data[0]>k)
				tmp = tmp->node[0];
			else if (tmp->data[2]<k)
				tmp = tmp->node[3];
			else
				tmp = tmp->node[1];
		}
	}
	return tmp;
}
void Insert(int key, B_tree tmp)//insert 함수
{
	tmp = wherego(key, tmp);
	if (tmp == NULL)
		tmp = malloc(sizeof(struct B_node));
	if (tmp->n_keys == 0) {
		tmp->n_keys = 1;
		tmp->data[0] = key;
	}
	else if (tmp->node[0] == NULL) {
		if (tmp->n_keys == 1) {
			if (tmp->data[0]>key) {
				tmp->data[2] = tmp->data[0];
				tmp->data[0] = key;
			}
			else if (tmp->data[0]<key) {
				tmp->data[2] = key;
			}
			tmp->n_keys++;
		}
		else if (tmp->n_keys == 2) {
			if (key>tmp->data[2]) {
				tmp->data[1] = tmp->data[2];
				tmp->data[2] = key;
			}
			else if (key<tmp->data[0]) {
				tmp->data[1] = tmp->data[0];
				tmp->data[0] = key;
			}
			else {
				tmp->data[1] = key;
			}
			tmp->n_keys++;

			while (tmp->n_keys == 3) {
				tmp = split(tmp, ptr);
			}
		}
	}

}
void Inorder(B_tree tmp)//순서에 따라 출력
{
	if (tmp) {
		Inorder(tmp->node[0]);
		fprintf(output, "%d ", tmp->data[0]);
		if (tmp->node[1] != NULL)
			Inorder(tmp->node[1]);
		if (tmp->n_keys == 2) {
			fprintf(output, "%d ", tmp->data[2]);
		}
		Inorder(tmp->node[3]);
	}
}

int main() {
	FILE *input;
	input = fopen("input.txt", "r");
	output = fopen("output.txt", "w");
	int intemp;
	char chartemp;
	ptr = malloc(sizeof(struct B_node)); //
	while (EOF != fscanf(input, "%c", &chartemp)) {
		if (chartemp == '\n' || chartemp == ' ') {
			fscanf(input, "%c", &chartemp);
		}
		if (chartemp == 'i') {
			fscanf(input, "%d", &intemp);
			Insert(intemp, ptr);
		}
		else if (chartemp == 'p') {
			Inorder(ptr);
			fprintf(output, "\n");
		}
	}
	fclose(input);
	fclose(output);
	return 0;
}