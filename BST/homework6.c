#pragma warning(disable:4996)
//#define _CRT_SECUER_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define COUNT 10

typedef struct {

	int key;
	char name[50];
	int age;
	int HTN;
	int DM;
	int Lipid;
	int Smoke;
}Data;


typedef struct _BinTree {
	Data* data;
	struct _BinTree* left, * right;
}BinTree;


BinTree* searchBST(BinTree* node, int key) {

	if (node == NULL) {
		printf("ERROR: 찾는 키가 없습니다.\n");
		return NULL;
	}
	if (key == node->data->key) return node;
	if (key < node->data->key)
		return searchBST(node->left, key);
	else
		return searchBST(node->right, key);
}


BinTree* new_node_record(Data* dat) {

	BinTree* newNode = (BinTree*)malloc(sizeof(BinTree));

	newNode->data = dat;
	newNode->left = NULL;
	newNode->right = NULL;

	return newNode;
}

BinTree* insertBST_recur(BinTree* node, Data* dat) {

	if (node == NULL)
		return new_node_record(dat);

	if (dat->key < node->data->key)
		node->left = insertBST_recur(node->left, dat);
	else if (dat->key > node->data->key)
		node->right = insertBST_recur(node->right, dat);
	else {
		printf("ERROR: 이미 같은 키가 있습니다.\n");
		return node;
	}

	return node;
}


int insertBST(BinTree* node, Data* dat) {

	// 재귀적으로 구현하지 않기. 강의 슬라이드 코드를 활용하여 구현. 

	BinTree* p = node;
	BinTree* parent = NULL;

	while (p != NULL) {
		if (dat->key == p->data->key) {
			printf("ERROR");

		}
		parent = p;
		if (dat->key < p->data->key)
			p = p->left;
		else
			p = p->right;
	}

	BinTree* newNode = (BinTree*)malloc(sizeof(BinTree));
	newNode->data = dat;
	newNode->left = NULL;
	newNode->right = NULL;

	if (node == NULL) node = newNode;
	if (dat->key < parent->data->key) parent->left = newNode;
	else parent->right = newNode;

	return 1;
}



BinTree* maxNode(BinTree* node) {
	// 해당 트리에서 최대인 노드를 찾기.
	BinTree* q = node->left;
	while (q->right != NULL) {
		q = q->right;
	}
	return q;

}

BinTree* deleteBST(BinTree* node, BinTree* root, int key) {

	// 강의 슬라이드에 나오는 코드를 참고하여 구현. 

	printf("이진트리에서 key값에 해당하는 노드 및 관련 데이터를 삭제하기.\n");
	printf("key to be deleted = %d\n", key);

	BinTree* p = node;
	BinTree* parent = NULL;
	BinTree* q;

	// 키 찾기
	p = searchBST(p, key);
	parent = root;

	while (parent != NULL)
	{
		if (parent->right == p || parent->left == p)
			break;
		if (parent->data->key > key) {
			parent = parent->left;
		}
		else {
			parent = parent->right;
		}
	}

	while (p != NULL) {
		if (p->data->key == key) {
			break;
		}
		parent = p;
		if (key < p->data->key)
			p = p->left;
		else
			p = p->right;
	}

	// case 1: 삭제할 노드의 차수가 0인 경우
	if (p->left == NULL && p->right == NULL) {
		if (parent == NULL) {
			node = NULL;
			return 0;
		}
		else {
			if (parent->left == p)
				parent->left = NULL;
			else
				parent->right = NULL;
		}
	}

	// case 2: 삭제할 노드의 차수가 1인 경우
	else if (p->left == NULL || p->right == NULL) {
		if (p->left != NULL) {
			if (parent->left == p)
				parent->left = p->left;
			else
				parent->right = p->left;
		}
		else {
			if (parent == NULL) {
				node = p->right;
				return node;
			}
			if (parent->left == p)
				parent->left = p->right;
			else
				parent->right = p->right;
		}
	}

	// case 3: 삭제할 노드의 차수가 2인 경우
	else if (p->left != NULL && p->right != NULL) {
		q = maxNode(p->left);
		p->data->key = q->data->key;
		deleteBST(p->left, root, q->data->key);
		p->data = q->data;
		p->data->key = q->data->key;
	}


	return node;
}


void inorderBST(BinTree* root) {

	if (root) {
		inorderBST(root->left);
		printf("%d, ", root->data->key);
		inorderBST(root->right);
	}
}

void preorderBST(BinTree* root) {

	if (root) {
		printf("[%d ->(", root->data->key);
		if (root->left) {
			printf("%d, ", root->left->data->key);
		}
		else {
			printf("null, ");
		}
		if (root->right) {
			printf("%d)]\n", root->right->data->key);
		}
		else {
			printf("null)]\n");
		}
		preorderBST(root->left);
		preorderBST(root->right);
	}
}


int heightBST(BinTree* node) {

	int height = 0;
	if (node != NULL)
		height = 1 + max(heightBST(node->left), heightBST(node->right));

	return height;
}

int countNodeBST(BinTree* node) {

	int count = 0;
	if (node != NULL)
		count = 1 + countNodeBST(node->left) + countNodeBST(node->right);
	return count;
}

void inorderBST_forDisplay(BinTree* root) {

	if (root) {
		inorderBST_forDisplay(root->left);

		// node에 있는 데이터를 하나의 라인으로 디스플레이
		printf("%d\t %s\t %d\t %d\t %d\t %d\t %d\n", root->data->key, root->data->name, root->data->age, root->data->HTN, root->data->DM, root->data->Lipid, root->data->Smoke);

		inorderBST_forDisplay(root->right);
	}
}

void display_help(void) {
	printf("문자 입력: d=자료삭제, h=트리높이, i=자료입력, l=자료출력, n=노드개수, p=노드연결출력, g = 중위순회 출력, s=탐색, v=트리구조출력, q=종료 \n");
}

void display_record(BinTree* node) {
	// key의 오름차순으로 디스플레이 하도록 구현함 
	inorderBST_forDisplay(node);
}

void display_search_result(BinTree* node) {
	printf("*****  Search Result  *****");
	printf("\nkey\t name\t age\t HTN\t DM\t Lipid\t Smoke\t\n");
	printf("%d\t %s\t %d\t %d\t %d\t %d\t %d\n", node->data->key, node->data->name, node->data->age, node->data->HTN, node->data->DM, node->data->Lipid, node->data->Smoke);
}


void display_tree_structure(BinTree* root)
{
	
	if (root == NULL)
		return;

	struct BinTree** queue = malloc(sizeof(struct Node*) * 1024);
	int front = 0, rear = 0;

	queue[rear++] = root;
	queue[rear++] = NULL;

	while (front != rear) {
		
		BinTree* node = queue[front++];

		if (node == NULL) {
			printf("\n");
			
			if (front != rear)
				queue[rear++] = NULL;
		}
		else {
			printf("%d ", node->data->key);

			
			if (node->left != NULL)
				queue[rear++] = node->left;

			
			if (node->right != NULL)
				queue[rear++] = node->right;
		}
	}

	free(queue);
}



void display_tree_structure_2(BinTree* node, int space) {
	
	//printf("(bonus point) Display your tree structure. \n");
	int count = 5;

	if (node == NULL) {
		return;
	}

	// 노드의 깊이에 비례하는 공백을 추가
	space += count;

	// 오른쪽 자식을 먼저 출력
	display_tree_structure_2(node->right, space);

	// 새 줄을 시작하고 해당 노드를 출력
	printf("\n");
	for (int i = count; i < space; i++) {
		printf(" ");
	}
	printf("%d\n", node->data->key);

	// 왼쪽 자식을 출력
	display_tree_structure_2(node->left, space);
	
}

void save_file(void) {
	printf("save data to .txt file.\n");
}

int main(int argc, char* argv[])
{
	FILE* fp;
	char buf[40];
	char input;
	int tmp, key;
	int i;
	int count = 0;
	BinTree* root = NULL;
	BinTree* p;
	Data* dat2;

	for (i = 0; i < argc; i++) {
		printf("argv[%d] = %s\n", i, argv[i]);

	}
	fp = fopen(argv[1], "r");
	/*
	텍스트 파일을 읽어들여 순차적으로 노드 생성 후 트리에 insert
	*/

	for (i = 0; i < 7; i++) {
		tmp = fscanf(fp, "%s", buf); // skip the first line in the text file.
	}

	printf("\nkey\t name\t age\t HTN\t DM\t Lipid\t Smoke\t\n");

	while ((fscanf(fp, "%d", &key)) != EOF) {
		Data* dat = (Data*)malloc(sizeof(Data));

		// 새 노드에 데이터 저장
		dat->key = key;
		tmp = fscanf(fp, "%s", buf);
		strcpy(dat->name, buf);
		tmp = fscanf(fp, "%d", &dat->age);
		tmp = fscanf(fp, "%d", &dat->HTN);
		tmp = fscanf(fp, "%d", &dat->DM);
		tmp = fscanf(fp, "%d", &dat->Lipid);
		tmp = fscanf(fp, "%d", &dat->Smoke);

		root = insertBST_recur(root, dat);

		printf("%2d\t %s\t %d\t %d\t %d\t %d\t %d\t \n", dat->key, dat->name, dat->age, dat->HTN, dat->DM, dat->Lipid, dat->Smoke);
		count++;
	}
	printf("\n\n이진 트리: 높이 = %d. 노드 개수 =  %d\n", heightBST(root), countNodeBST(root));

	fclose(fp);



	/*
	앞에서 만든 트리에 사용자가 직접 key를 포함한 레코드를 만든 후 트리에 insert
	*/

	display_help();

	while ((input = getchar()) != 'q') {

		switch (input) {

		case 'f':
			save_file();
			display_help();
			break;

		case 'i':
			dat2 = (Data*)malloc(sizeof(Data));
			printf("다음을 입력하시오. key는 중복되지 않는 값을 입력하시오. \n");
			printf("key (1-99)    : "); scanf_s("%d", &dat2->key);
			printf("이름          : "); scanf("%s", buf);	strcpy(dat2->name, buf);
			printf("나이          : "); scanf_s("%d", &dat2->age);
			printf("고혈압(0/1)   : "); scanf_s("%d", &dat2->HTN);
			printf("당뇨(0/1)     : "); scanf_s("%d", &dat2->DM);
			printf("고지혈증(0/1) : "); scanf_s("%d", &dat2->Lipid);
			printf("흡연(0/1)     : "); scanf_s("%d", &dat2->Smoke);
			insertBST(root, dat2);

			printf("레코드를 트리에 저장하였습니다. \n");
			display_help();
			break;

		case 'h':
			printf("트리의 높이 = %d\n", heightBST(root));
			display_help();
			break;

		case 'n':
			printf("노드의 총 개수 = %d\n", countNodeBST(root));
			display_help();
			break;

		case 'd':
			printf("삭제할 데이터의 key값을 입력하시오 : ");
			scanf_s("%d", &key);
			root = deleteBST(root, root, key);
			display_help();
			break;

		case 'l':
			printf("레코드를 출력하기\n");
			printf("\nkey\t name\t age\t HTN\t DM\t Lipid\t Smoke\t\n");
			display_record(root);
			display_help();
			break;

		case 'p':
			printf("전위순회 이용하여 노드간 연결성 표기하기\n");
			preorderBST(root);
			display_help();
			break;

		case 'g':
			printf("중위순회 출력\n");
			inorderBST(root);
			break;
		
		case 's':
			printf("탐색할 데이터의 key값을 입력하시오 : ");
			scanf_s("%d", &key);
			p = searchBST(root, key);
			display_search_result(p);
			display_help();
			break;

		case 'v':
			/*
				[Extra point]
				트리 구조를 화면에 시각화하여 보여주기
			*/
			printf("----------------------------------In Vertical Tree Structure-------------------------------------");
			display_tree_structure(root);
			printf("----------------------------------In Horizontal Tree Structure-------------------------------------");
			display_tree_structure_2(root, 0);
			display_help();
			break;

		case 'q':
			printf("Quit!\n");
			break;
		}
	}

	return 0;
}