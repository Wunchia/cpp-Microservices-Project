#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define ARR_LEN(arr)(sizeof(arr)/sizeof(arr[0]))
#define SWAP(arr,i,j){\
    int temp=arr[i];\
    arr[i]=arr[j];\
    arr[j]=temp;\
}

/*
三层函数，各行其职
*/

void print_arr(int arr[], int len) {
    for (int i = 0; i < len; i++) {
        printf("%d\t", arr[i]);
    }
    printf("\n");
}

void merge_left_and_right(int arr[], int left, int mid, int right, int* tmp) {
    int cur_l = left;
    int cur_r = mid+1;
    int total_index = left;
    while (cur_l <= mid && cur_r <= right) {
        if (arr[cur_l] < arr[cur_r]) {
            tmp[total_index++] = arr[cur_l++];
        }
        else {
            tmp[total_index++] = arr[cur_r++];
        }
    }
    while (cur_l <= mid) {
        tmp[total_index++] = arr[cur_l++];
    }
    while (cur_r <= right) {
        tmp[total_index++] = arr[cur_r++];
    }
    for (int i = left; i <= right; i++) {
        arr[i] = tmp[i];
    }
}

void divide_and_merge(int arr[], int left, int right, int* tmp) {
    if (left >= right) {
        return;
    }
    int mid = left + (right - left) / 2;
    divide_and_merge(arr, left, mid, tmp);
    divide_and_merge(arr, mid + 1, right, tmp);
    merge_left_and_right(arr, left, mid, right, tmp);
}

void merge_sort(int arr[], int len) {
    int* tmp = calloc(len, sizeof(int));
    divide_and_merge(arr, 0, len - 1, tmp);
    free(tmp);
}

int main(void) {
    int arr[] = { 16,1,45,23,99,2,18,67,42,10 };
    print_arr(arr, ARR_LEN(arr));

    merge_sort(arr, ARR_LEN(arr));

    print_arr(arr, ARR_LEN(arr));
    return 0;
}