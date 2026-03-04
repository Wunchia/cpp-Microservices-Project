#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
/*
先在堆上申请创建一个长度为10的int数组，编写一个函数用于以"[xx, xx, ..., xx]"的格式打印这个int数组。
紧接着执行以下操作：
在申请int数组成功后，直接调用函数打印这个int数组，思考一下：应该用哪个函数来申请创建这个数组？
截断这个int数组，将其变为长度为5的int数组，然后再打印这个数组。
将长度为5的int数组，再次扩容回10个元素，将最后五个元素初始化为888，最后再次打印这个数组。
最后不要忘记free释放内存块。
非常简单且基础的语法练习题，如果还不太会做，不妨直接查看参考代码。
重点需要注意realloc函数的调用格式！
*/


void print_arr(int* arr,int len) {
    printf("[");
    for (int i = 0; i < len; i++) {
        if (i < len - 1) {
            printf(" %d ,", arr[i]);
        }
        else if (i == len - 1) {
            printf(" %d ", arr[i]);
        }
    }
    printf("]\n");
}

int main(void) {
    int* p = (int*)malloc(sizeof(int) * 10);
    if (p == NULL) {
        printf("malloc failed\n");
        return -1;
    }
    for (int i = 0; i < 10; i++) {
        p[i] = i;
    }
    print_arr(p, 10);
    //
    int* p_temp = realloc(p, 5*sizeof(int));
    if (p_temp == NULL) {
        printf("realloc failed\n");
        return -1;
    }
    p = p_temp;
    print_arr(p, 5);
    //
    p_temp = realloc(p, 10*sizeof(int));
    if (p_temp == NULL) {
        printf("realloc failed\n");
        return -1;
    }
    p = p_temp;
    for (int i = 5; i < 10;i++) {
        p[i] = 888;
    }
    print_arr(p, 10);

    free(p);
    return 0;
}