#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/*

*/

typedef int ElemType;


void swap(ElemType *a, ElemType *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int compare(ElemType a, ElemType b) {
    return a - b;
}

int partition(ElemType* arr, int front, int end) {
    ElemType pivot = arr[front+(end-front) / 2];
    int i = front - 1;
    int j = end + 1;
    while (1) {
        do { i++; } while (arr[i] < pivot);
        do { j--; } while (arr[j] > pivot);
        if (i >= j) return j;
        swap(&arr[i], &arr[j]);
    }
    return j;
}

void quick_sort(ElemType* arr, int front, int end) {
    if (front < end) {
        ElemType pivot = partition(arr, front, end);
        quick_sort(arr, front, pivot);
        quick_sort(arr, pivot + 1, end);
    }
}

int main(void) {
    int a[10] = { 4,3,5,5,6,7,5,3,1,2 };
    for (int i = 0; i < 10; i++) {
        printf("%d", a[i]);
    }
    printf("\n");
    quick_sort(a, 0, 9);
    for (int i = 0; i < 10; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
    return 0;
}