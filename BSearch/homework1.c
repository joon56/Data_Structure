/*

  ����Ž�� �˰���� ����Ž�� �˰����� ���� ��

*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define CLOCKS_PER_SEC 1000

int LSearch(int ar[], int len, int target) {
    int i;

    for (i = 0; i < len; i++) {
        if (ar[i] == target) return i;
    }
    return -1;
}

int BSearch(int arr[], int len, int target) {

    int first = 0;
    int last = len - 1;
    int mid;

    while (first <= last) {
        mid = (first + last) / 2;

        if (arr[mid] == target) {
            return mid;
        }
        else if (arr[mid] < target) {
            first = mid + 1;
        }
        else {
            last = mid - 1;
        }
    }
    return -1;
}

int main(void) {

    // len��¥�� ������ ������ ���������� �迭�� �����.
    int arr[100000];

    for (int i = 0; i < 100000; i++) {
        arr[i] = i + 1;


    }
    int len = sizeof(arr) / sizeof(int);
    int target;
    int index_ls, index_bs;
    clock_t start_ls, end_ls, start_bs, end_bs;

    // ã���� �ϴ� ���� �Է��Ѵ�. 
    printf("\nEnter a target number (try the worst case): ");
    scanf("%d", &target);

    printf("target = %d\n", target);

    // linear search (����Ž��) ���� 
    start_ls = clock();
    for (int i = 0; i < 10000; i++) {
        index_ls = LSearch(arr, len, target);
    }
    end_ls = clock();
    float time_elapsed_LS = (float)(end_ls - start_ls) / CLOCKS_PER_SEC;
    printf("\n����Ž��: target %d�� ��ġ �ε������� %d�̴�. �ҿ�ð��� %f���̴�", target, index_ls, time_elapsed_LS);

    // binary search (����Ž��) ���� 
    start_bs = clock();
    for (int i = 0; i < 10000; i++) {
        index_bs = LSearch(arr, len, target);
    }
    end_bs = clock();
    float time_elapsed_BS = (float)(end_bs - start_bs) / CLOCKS_PER_SEC;
    printf("\n����Ž��: target %d�� ��ġ �ε������� %d�̴�. �ҿ�ð��� %f���̴�", target, index_bs, time_elapsed_BS);

    return 0;
}