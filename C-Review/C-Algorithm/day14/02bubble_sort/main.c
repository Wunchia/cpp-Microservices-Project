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

void bubble_sort(int arr[], int len) {
    for (int i = 0; i < len; i++) {
        bool swap_flag = false;
        for (int j = 0; j < len - i - 1; j++) {
            if (arr[j] > arr[j+1]) {
                SWAP(arr, j, j+1);
                swap_flag = true;
            }
        }
        if (swap_flag == false) {
            break;
        }
        print_arr(arr, len);
    }
}

int main(void) {
    int arr[] = { 16,1,45,23,99,2,18,67,42,10 };
    print_arr(arr, ARR_LEN(arr));

    bubble_sort(arr, ARR_LEN(arr));

    print_arr(arr, ARR_LEN(arr));
    return 0;
}