#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
/*
* 两数之和
* 给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出 和为目标值 target  的那 两个 整数，并返回它们的数组下标。
* 你可以假设每种输入只会对应一个答案，并且你不能使用两次相同的元素。
* 你可以按任意顺序返回答案。
*/

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    for (int i = 0; i < numsSize; i++) {
        for (int j = i + 1; j < numsSize; j++) {
            if (nums[i] + nums[j] == target) {
                *returnSize = 2;
                int *ret = (int*)malloc(sizeof(int) * (*returnSize));
                if (ret != NULL) {
                    ret[0] = i;
                    ret[1] = j;
                }
                return ret;
            }
        }
    }
    *returnSize = 0;
    return NULL;
}


int main(void) {
    int* p = (int*)malloc(sizeof(int) * 10);
    for (int i = 0; i < 9; i++) {
        p[i] = i;
    }
    p[9] = 5;
    int len = 10;
    int target = 0;
    printf("请输入target：\n");
    scanf("%d", &target);
    int returnSize = 0;
    int* ret = twoSum(p, len, target, &returnSize);
    if (ret != NULL && returnSize == 2) {
        printf("找到下标：%d, %d\n", ret[0], ret[1]);
        printf("对应的值：%d + %d = %d\n", p[ret[0]], p[ret[1]], target);
    }
    else {
        printf("未找到符合条件的两个数\n");
    }
    free(p);
    free(ret);

    return 0;
}