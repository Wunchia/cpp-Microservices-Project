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

void insert_sort(int arr[], int len) {
    for (int i = 0; i < len; i++) {
        int need_insert_value = arr[i];//逐个取数
        int need_check_index = i - 1;
        while (need_check_index >= 0 && need_insert_value < arr[need_check_index]) {//向有序部分插入
            arr[need_check_index + 1] = arr[need_check_index];
            need_check_index--;//会多减一次，指到等于或大于的位置
        }
        arr[need_check_index + 1] = need_insert_value;//把多减的那一次加回来
        print_arr(arr, len);
    }
}

int main(void) {
    int arr[] = { 16,1,45,23,99,2,18,67,42,10 };
    print_arr(arr, ARR_LEN(arr));

    insert_sort(arr, ARR_LEN(arr));

    print_arr(arr, ARR_LEN(arr));
    return 0;
}