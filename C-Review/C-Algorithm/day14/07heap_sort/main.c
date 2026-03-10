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

void heapify(int arr[], int root_idx, int tree_len) {//单个节点的下沉逻辑
    while (1) {
        int max_idx = root_idx;
        int left_idx = root_idx * 2 + 1;
        int right_idx = root_idx * 2 + 2;

        if (left_idx<tree_len && arr[left_idx]>arr[max_idx]) {
            max_idx = left_idx;
        }
        if (right_idx<tree_len && arr[right_idx]>arr[max_idx]) {
            max_idx = right_idx;
        }

        if (max_idx != root_idx) {
            SWAP(arr, max_idx, root_idx);
            root_idx = max_idx;
        }
        else {
            break;
        }
    }
}

void heap_sort(int arr[], int len) {
    for (int i = len - 1; i >= 0; i--) {
        heapify(arr, i, len);
    }
    int tree_len = len;
    for (int i = 0; i < len; i++) {
        SWAP(arr, 0, tree_len - 1);
        tree_len--;
        heapify(arr, 0, tree_len);
    }
}

int main(void) {
    int arr[] = { 16,1,45,23,99,2,18,67,42,10 };
    print_arr(arr, ARR_LEN(arr));

    heap_sort(arr, ARR_LEN(arr));

    print_arr(arr, ARR_LEN(arr));
    return 0;
}