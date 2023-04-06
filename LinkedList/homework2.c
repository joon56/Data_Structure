#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0


typedef struct Node {

	char name[50];
	char sex;
	int age;
	float bmi;

	struct Node* link;

}Node;


typedef struct {

	Node* head;
	int length;

}linkedList;



linkedList* initList() {

	linkedList* L;
	L = (linkedList*)malloc(sizeof(linkedList));

	L->head = NULL;
	L->length = 0;

	return L;
}


void displayList(linkedList* L) {

	Node* p;
	p = L->head;

	if (p == NULL) {
		printf("The list is empty. Quit!\n");
	}
	else {
		printf("\nname    age   BMI\n");

		while (p != NULL) {

			printf("%s  %3d  %.1f\n", p->name, p->age, p->bmi);
			p = p->link;
		}
	}
}


/* �Լ� ������ �Ʒ��� ���� ������ ���� ������ */


void insertFirst(linkedList* L, Node* N) {
	N->link = L->head;
	L->head = N;
	L->length++;
}

void insertLastNode(linkedList* L, Node* N) {
	Node* temp;
	N->link = NULL;

	if (L->head == NULL)
		L->head = N;
	else {
		temp = L->head;
		while (temp->link != NULL)
			temp = temp->link;
		temp->link = N;
	}
	L->length++;
}


Node* deleteNode(linkedList* L, Node* p) {
	Node* pre;

	if (L->head == NULL) return FALSE;
	if (p == NULL) return FALSE;
	pre = L->head;

	while (pre->link != p) {
		pre = pre->link;
		if (pre == NULL) return FALSE;
	}
	pre->link = p->link;
	free(p);

	L->length--;
	return TRUE;

}

void insert(linkedList* L, Node* pre, Node* N) {
	if (L->head == NULL) {
		N->link = NULL;
		L->head = N;
	}
	else if (pre == NULL) {
		N->link = L->head;
		L->head = N;
	}
	else {
		N->link = pre->link;
		pre->link = N;
	}
	L->length++;
	
}

void swap(Node* a, Node* b) {
	char temp_name[50];
	int temp_age;
	float temp_bmi;

	strcpy(temp_name, a->name);
	strcpy(a->name, b->name);
	strcpy(b->name, temp_name);

	temp_age = a->age;
	a->age = b->age;
	b->age = temp_age;

	temp_bmi = a->bmi;
	a->bmi = b->bmi;
	b->bmi = temp_bmi;
}

void sort_list(linkedList* L) {
	Node* current;
	//current = (Node*)malloc(sizeof(Node));
	Node* next;
	//next = (Node*)malloc(sizeof(Node));
	int swapped;
	if (L->head == NULL)
		return;
	do {
		swapped = 0;
		current = L->head;
		while (current->link != NULL) {
			next = current->link;
			if (current->age > next->age) {
				swap(current, next);
				swapped = 1;
			}
			current = current->link;
		}
	} while (swapped);
}


int main(void)
{

	FILE* fp;
	char buf[40];

	fp = fopen("C:\\C_Programming\\patientdata.txt", "r");


	/*
		Q1: ����Ʈ�� �ִ� �� ����� �����͸� ����ϱ�
	*/

	// list1 �ʱ�ȭ
	linkedList* list1;
	list1 = initList();

	// ������ �о�鿩 ���������� ��� ����
	int i;
	for (i = 0; i < 3; i++) {
		fscanf(fp, "%s", buf); // skip the first line in the text file.
	}

	while ((fscanf(fp, "%s", buf)) != EOF) {

		Node* newNode;
		newNode = (Node*)malloc(sizeof(Node)); // ���ο� ��� ����

		// ���ο� ��忡 ������ ����
		strcpy(newNode->name, buf);
		fscanf(fp, "%d", &newNode->age);
		fscanf(fp, "%f", &newNode->bmi);

		// insertFirst �Լ��� �� �ڸ��� �ֱ�.
		insertFirst(list1, newNode);
	}



	printf("\n1. ����Ʈ�� �ִ� �� ����� �����͸� ����ϱ� \n");

	displayList(list1);
	printf("\nlist1�� ���� = % d\n", list1->length);


	/*
		Q2: ������ ��°� �ݴ�� ������ �Ųٷ� ����ϱ�.
	*/

	printf("\n\n2. ����Ʈ ������ �Ųٷ� ����ϱ� \n");

	// list2 �ʱ�ȭ
	linkedList* list2;
	list2 = initList();

	rewind(fp);

	for (i = 0; i < 3; i++) {
		fscanf(fp, "%s", buf); // skip the first line in the text file.
	}

	while ((fscanf(fp, "%s", buf)) != EOF) {

		Node* newNode;
		newNode = (Node*)malloc(sizeof(Node)); // ���ο� ��� ����

		// ���ο� ��忡 ������ ����
		strcpy(newNode->name, buf);
		fscanf(fp, "%d", &newNode->age);
		fscanf(fp, "%f", &newNode->bmi);

		// insertLastNode �Լ��� �� �ڸ��� �ֱ�
		insertLastNode(list2, newNode);
	}

	displayList(list2);
	printf("\nlist2�� ���� = % d\n", list2->length);


	/*
		Q3: list1�����Ϳ��� BMI�� 25�̸��� ȯ�ڴ� ������ �� ����Ʈ �� ��� ������ ����ϱ�.
	*/

	printf("\n\n3. list1�����Ϳ��� BMI�� 25�̸��� ȯ�ڴ� ������ �� ����Ʈ �� ��� ������ ����ϱ�. \n");


	printf("\n ���� �� list1\n");
	displayList(list1);


	// ����Ʈ���� BMI�� 25�̸��� ȯ�� �����ϵ��� �ڵ��ϱ�. 
	Node* cur;
	
	Node* newNode;
	newNode = (Node*)malloc(sizeof(Node));

	strcpy(newNode->name, buf);
	fscanf(fp, "%d", &newNode->age);
	fscanf(fp, "%f", &newNode->bmi);

	for (cur = list1->head; cur != NULL;) {
		if (cur->bmi < 25) {
			deleteNode(list1, cur);
			cur = list1->head;
		}
		else {
			cur = cur->link;
		}
	}


	printf("\n ���� �� list1\n");
	displayList(list1);
	printf("\n���� �� list1�� ���� = % d\n", list1->length);


	/*
		Q4: Age ������������ ������ ����Ʈ ����ϱ�.
	*/
	
	printf("\n\n4. Age ������������ ������ ����Ʈ ����ϱ�. \n");

	// list4 �ʱ�ȭ
	linkedList* list4;
	list4 = initList();

	rewind(fp);

	for (i = 0; i < 3; i++) {
		fscanf(fp, "%s", buf); // skip the first line in the text file.
	}

	while ((fscanf(fp, "%s", buf)) != EOF) {

		Node* newNode;
		newNode = (Node*)malloc(sizeof(Node)); // ���ο� ��� ����

		// ���ο� ��忡 ������ ����
		strcpy(newNode->name, buf);
		fscanf(fp, "%d", &newNode->age);
		fscanf(fp, "%f", &newNode->bmi);


		// Age ������������ �����ϵ��� �ڵ��ϱ�.
		newNode->link = NULL;
		insertFirst(list4, newNode);
		sort_list(list4);


		displayList(list4);

	}

	fclose(fp);

}
