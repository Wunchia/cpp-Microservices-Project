#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
/*

*/

bool is_odd(int n) {
    return (n & 1) == 1;
}

bool is_power_2(int n) {
    return (n & (n - 1)) == 0;
}

int findLSB(int n) {
    return (n & (-n));
}

int main(void) {
    int a=2, b=3;
    printf("交换前：a=%d,b=%d\n", a, b);
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
    printf("交换后：a=%d,b=%d\n", a, b);

    /*int nums[9] = { 1,2,1,3,2,4,5,4,5 };
    int single = 0;
    for (int i = 0; i < 9; i++) {
        single ^= nums[i];
    }
    printf("只出现一次的元素是%d\n", single);*/
    
    int nums[10]= { 1,2,1,3,2,4,5,4,5 ,6};
    int ret = 0;
    for (int i = 0; i < 10; i++) {
        ret ^= nums[i];//ret是两个只出现一次的数的异或，其最后一位1必然表示在该位上两个数一个是1，一个是0
    }
    int lsb = ret & (-ret);//找到分组依据
    int ret1 = 0;
    int ret2 = 0;
    for (int i = 0; i < 10; i++) {
        if ((lsb & nums[i]) == 0) {
            ret1 ^= nums[i];
        }
        else{
            ret2 ^= nums[i];
        }
    }
    printf("只出现一次的元素是：%d,%d\n", ret1, ret2);


    return 0;
}