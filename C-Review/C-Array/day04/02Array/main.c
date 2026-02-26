#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define ARR_LEN(arr) (sizeof(arr)/sizeof(arr[0]))
/*

*/

void test01() {
    char str1[10] = { 'a', 'B', 'c', '0', '9', '+', '*', 'b', 'e', 'm' };
    int count = 0;
    for (int i = 0; i < ARR_LEN(str1); i++) {
        if (str1[i] >= 'a' && str1[i] <= 'z') {
            count++;
        }
    }
    printf("小写字母个数为：%d\n", count);
}

void test02() {
    char str1[10] = { 'a', 'B', 'c', '0', '9', '+', '*', 'b', 'e', 'm' };
    for (int i = 0; i < ARR_LEN(str1); i++) {
        printf("%c", str1[i]);
    }
    printf("\n============\n");
    for (int i = 0; i < ARR_LEN(str1); i++) {
        if (str1[i] >= 'a' && str1[i] <= 'z') {
            str1[i] -= ('a' - 'A');
        }
        else if (str1[i] >= 'A' && str1[i] <= 'Z') {
            str1[i] += ('a' - 'A');
        }
    }
    for (int i = 0; i < ARR_LEN(str1); i++) {
        printf("%c", str1[i]);
    }
    printf("\n");
   
}

void test03() {
    int arr[3][3] = {
        {1,2,3},
        {4,5,6}
    };
    printf("%d\n", arr[1][1]);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf(" %d ", arr[i][j]);
        }
        printf("\n");
    }
}

void test04() {
    const int arr[3][3] = {
        {1,2,3},
        {4,5,6},
        {7,8,9}
    };
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf(" %d ", arr[i][j]);
        }
        printf("\n");
    }
    printf("=========\n");
    //arr[1][1] = 7;
    int* p = arr;
    p[5] = 7;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf(" %d ", arr[i][j]);
        }
        printf("\n");
    }

}

int main(void) {
      int arr1[] = { 1,2,3 };
      int arr2[3] = { 1,2,3 };
      int arr3[3] = { 0 };
      int arr4[3] = { 1 ,2 };
      for (int i = 0; i < ARR_LEN(arr1); i++) {
          printf("======%d\n", arr1[i]);
      }
      for (int i = 0; i < ARR_LEN(arr2); i++) {
          printf("-----%d\n", arr2[i]);
      }
      for (int i = 0; i < ARR_LEN(arr3); i++) {
          printf("======%d\n", arr3[i]);
      }
      for (int i = 0; i < ARR_LEN(arr4); i++) {
          printf("......%d\n", arr4[i]);
          arr4[i] = 0;
      }
      for (int i = 0; i < ARR_LEN(arr4); i++) {
          printf("......%d\n", arr4[i]);
      }
    test01();
    test02();
    char str[1024 * 1024];//局部变量数组在栈空间，不宜太大
    test03();
    const int num = 123;
    //num = 5;
    printf("%d\n", num);
    //scanf("%d", &num);
    int* p = &num;
    *p = 5;
    printf("%d\n", num);
    test04();
    return 0;
}