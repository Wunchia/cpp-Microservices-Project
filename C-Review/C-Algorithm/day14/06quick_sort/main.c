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

*/
void print_arr(int arr[], int len) {
    for (int i = 0; i < len; i++) {
        printf("%d\t", arr[i]);
    }
    printf("\n");
}

void pivot(int arr[], int left, int right) {
    if (left >= right) {
        return;
    }
    int pivot_index = left;
    int pivot_value = arr[pivot_index];

    int cur_l = left;
    int cur_r = right;

    while (cur_l < cur_r) {
        while (cur_l<cur_r && arr[cur_r]>pivot_value) {
            cur_r--;
        }
        if (cur_l < cur_r) {
            arr[cur_l] = arr[cur_r];
        }
        while (cur_l < cur_r && arr[cur_l] <= pivot_value) {
            cur_l++;
        }
        if (cur_l < cur_r) {
            arr[cur_r] = arr[cur_l];
        }
    }
    arr[cur_l] = pivot_value;
    pivot(arr, left, cur_l - 1);
    pivot(arr, cur_l + 1, right);
}

void quick_sort(int arr[], int len) {
    pivot(arr, 0, len - 1);
}


int main(void) {
    int arr[] = { 16,1,45,23,99,2,18,67,42,10 };
    print_arr(arr, ARR_LEN(arr));

    quick_sort(arr, ARR_LEN(arr));

    print_arr(arr, ARR_LEN(arr));
    return 0;
}