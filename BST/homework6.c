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
		printf("ERROR: ã�� Ű�� �����ϴ�.\n");
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
		printf("ERROR: �̹� ���� Ű�� �ֽ��ϴ�.\n");
		return node;
	}

	return node;
}


int insertBST(BinTree* node, Data* dat) {

	// ��������� �������� �ʱ�. ���� �����̵� �ڵ带 Ȱ���Ͽ� ����. 

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
	// �ش� Ʈ������ �ִ��� ��带 ã��.
	BinTree* q = node->left;
	while (q->right != NULL) {
		q = q->right;
	}
	return q;

}

BinTree* deleteBST(BinTree* node, BinTree* root, int key) {

	// ���� �����̵忡 ������ �ڵ带 �����Ͽ� ����. 

	printf("����Ʈ������ key���� �ش��ϴ� ��� �� ���� �����͸� �����ϱ�.\n");
	printf("key to be deleted = %d\n", key);

	BinTree* p = node;
	BinTree* parent = NULL;
	BinTree* q;

	// Ű ã��
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

	// case 1: ������ ����� ������ 0�� ���
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

	// case 2: ������ ����� ������ 1�� ���
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

	// case 3: ������ ����� ������ 2�� ���
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

		// node�� �ִ� �����͸� �ϳ��� �������� ���÷���
		printf("%d\t %s\t %d\t %d\t %d\t %d\t %d\n", root->data->key, root->data->name, root->data->age, root->data->HTN, root->data->DM, root->data->Lipid, root->data->Smoke);

		inorderBST_forDisplay(root->right);
	}
}

void display_help(void) {
	printf("���� �Է�: d=�ڷ����, h=Ʈ������, i=�ڷ��Է�, l=�ڷ����, n=��尳��, p=��忬�����, g = ������ȸ ���, s=Ž��, v=Ʈ���������, q=���� \n");
}

void display_record(BinTree* node) {
	// key�� ������������ ���÷��� �ϵ��� ������ 
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

	// ����� ���̿� ����ϴ� ������ �߰�
	space += count;

	// ������ �ڽ��� ���� ���
	display_tree_structure_2(node->right, space);

	// �� ���� �����ϰ� �ش� ��带 ���
	printf("\n");
	for (int i = count; i < space; i++) {
		printf(" ");
	}
	printf("%d\n", node->data->key);

	// ���� �ڽ��� ���
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
	�ؽ�Ʈ ������ �о�鿩 ���������� ��� ���� �� Ʈ���� insert
	*/

	for (i = 0; i < 7; i++) {
		tmp = fscanf(fp, "%s", buf); // skip the first line in the text file.
	}

	printf("\nkey\t name\t age\t HTN\t DM\t Lipid\t Smoke\t\n");

	while ((fscanf(fp, "%d", &key)) != EOF) {
		Data* dat = (Data*)malloc(sizeof(Data));

		// �� ��忡 ������ ����
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
	printf("\n\n���� Ʈ��: ���� = %d. ��� ���� =  %d\n", heightBST(root), countNodeBST(root));

	fclose(fp);



	/*
	�տ��� ���� Ʈ���� ����ڰ� ���� key�� ������ ���ڵ带 ���� �� Ʈ���� insert
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
			printf("������ �Է��Ͻÿ�. key�� �ߺ����� �ʴ� ���� �Է��Ͻÿ�. \n");
			printf("key (1-99)    : "); scanf_s("%d", &dat2->key);
			printf("�̸�          : "); scanf("%s", buf);	strcpy(dat2->name, buf);
			printf("����          : "); scanf_s("%d", &dat2->age);
			printf("������(0/1)   : "); scanf_s("%d", &dat2->HTN);
			printf("�索(0/1)     : "); scanf_s("%d", &dat2->DM);
			printf("��������(0/1) : "); scanf_s("%d", &dat2->Lipid);
			printf("��(0/1)     : "); scanf_s("%d", &dat2->Smoke);
			insertBST(root, dat2);

			printf("���ڵ带 Ʈ���� �����Ͽ����ϴ�. \n");
			display_help();
			break;

		case 'h':
			printf("Ʈ���� ���� = %d\n", heightBST(root));
			display_help();
			break;

		case 'n':
			printf("����� �� ���� = %d\n", countNodeBST(root));
			display_help();
			break;

		case 'd':
			printf("������ �������� key���� �Է��Ͻÿ� : ");
			scanf_s("%d", &key);
			root = deleteBST(root, root, key);
			display_help();
			break;

		case 'l':
			printf("���ڵ带 ����ϱ�\n");
			printf("\nkey\t name\t age\t HTN\t DM\t Lipid\t Smoke\t\n");
			display_record(root);
			display_help();
			break;

		case 'p':
			printf("������ȸ �̿��Ͽ� ��尣 ���Ἲ ǥ���ϱ�\n");
			preorderBST(root);
			display_help();
			break;

		case 'g':
			printf("������ȸ ���\n");
			inorderBST(root);
			break;
		
		case 's':
			printf("Ž���� �������� key���� �Է��Ͻÿ� : ");
			scanf_s("%d", &key);
			p = searchBST(root, key);
			display_search_result(p);
			display_help();
			break;

		case 'v':
			/*
				[Extra point]
				Ʈ�� ������ ȭ�鿡 �ð�ȭ�Ͽ� �����ֱ�
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