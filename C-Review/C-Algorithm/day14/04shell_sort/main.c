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

void shell_sort(int arr[], int len) {
    int gap = len / 2;
    while(gap>0){//多一层while循环，内部进行多次插入排序
        for (int i = gap; i < len; i++) {//间隔gap，分组处理
            int need_insert_value = arr[i];//逐个取数
            int need_check_index = i - gap;
            while (need_check_index >= 0 && need_insert_value < arr[need_check_index]) {//向有序部分插入
                arr[need_check_index + gap] = arr[need_check_index];
                need_check_index-=gap;//会多减一次，指到等于或大于的位置
            }
            arr[need_check_index + gap] = need_insert_value;//把多减的那一次加回来
        }
        gap /= 2;
    }
}

int main(void) {
    int arr[] = { 16,1,45,23,99,2,18,67,42,10 };
    print_arr(arr, ARR_LEN(arr));

    shell_sort(arr, ARR_LEN(arr));

    print_arr(arr, ARR_LEN(arr));
    return 0;
}