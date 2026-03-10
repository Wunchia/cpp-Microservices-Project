#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define ARR_LEN(arr)(sizeof(arr)/sizeof(arr[0]))
#define SWAP(arr,i,j){\
    int temp = arr[i];\
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

void select_sort(int arr[], int len) {//找到最小的，选到最前面；再找次小的，选到第二个，类推
    for (int i = 0; i < len; i++) {
        int min_index = i;
        for (int j = i + 1; j < len; j++) {
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }
        SWAP(arr, i, min_index);
        print_arr(arr, len);
    }
}


int main(void) {
    int arr[] = { 16,1,45,23,99,2,18,67,42,10 };
    print_arr(arr, ARR_LEN(arr));

    select_sort(arr, ARR_LEN(arr));

    print_arr(arr, ARR_LEN(arr));
    return 0;
}