#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


void swap(int* arr, int i, int j) {
    int temp = *(arr + i);
    *(arr + i) = *(arr + j);
    *(arr + j) = temp;
}

void reverse_01(int* arr, int len) {
    for (int i = 0; i < (len/2); i++) {
        swap(arr, i, len - i-1);
    }
}

void reverse_02(int arr[], int len) {
    for (int i = 0; i < (len / 2); i++) {
        int temp = arr[i];
        arr[i] = arr[len - i-1];
        arr[len - i - 1] = temp;
    }
}

int arr_sum(int *arr,int len) {
    int sum = 0;
    for (int i = 0; i < len; i++) {
        sum += *arr++;
    }
    return sum;
}

void find_index(int* arr,int len,int target,int* index) {
    for (int i = 0; i < len; i++) {
        if (arr[i] == target) {
            *index = i;
            return;
        }
    }
    printf("数组内未找到：%d\n", target);
}

bool is_palindormic(int* arr, int len) {
    for (int i = 0; i < (len/2); i++) {
        if (*(arr + i) != *(arr + len - i - 1)) {
            return false;
        }
    }
    return true;
}

void copy_array(int* src, int len_src, int* dest, int len_dest) {
    for (int i = 0; i < len_src; i++) {
        *dest++ = *src++;
    }
}

void odd_front(int* arr, int len) {
    int* temp1 = (int*)malloc(sizeof(int) * len);
    int* temp2 = (int*)malloc(sizeof(int) * len);
    int len1 = 0, len2 = 0;
    for (int i = 0; i < len; i++) {
        if (arr[i] % 2 == 0) {
            temp2[len2++] = arr[i];
        }
        else {
            temp1[len1++] = arr[i];
        }
    }
    for (int i = 0; i < len; i++) {
        if (i < len1) {
            arr[i] = temp1[i];
        }
        else {
            arr[i] = temp2[i-len1];
        }
    }
    free(temp1);
    free(temp2);
}

void print_arr(int* p, int len) {
    for (int i = 0; i < len; i++) {
        printf("%d", p[i]);
    }
    printf("\n");
}
int main(void) {
    int a[5] = { 1,2,3,2,1 };
    int b[5] = { 1,2,3,4,5 };
    print_arr(b,5);
    swap(b, 0, 4);
    print_arr(b,5);
    swap(b, 0, 4);
    print_arr(b, 5);
    reverse_01(b,5);
    print_arr(b, 5);
    printf("sum=%d\n",arr_sum(b, 5));
    int i = 0;
    print_arr(a, 5);
    find_index(a, 5, 3, &i);
    printf("index of 3 in a = %d\n", i);
    if (is_palindormic(a, 5)) {
        printf("a 是回文数组\n");
    }
    else {
        printf("a 不是回文数组\n");
    }
    print_arr(a, 5);
    copy_array(b, 5, a, 5);
    print_arr(a, 5);
    odd_front(a, 5);
    print_arr(a, 5);

    return 0;
}