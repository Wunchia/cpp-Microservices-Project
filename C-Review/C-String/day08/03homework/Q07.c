#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/*
给定一个字符串，要求它可能包含数字和字母。
请编写函数，统计该字符串中每个字符出现的次数，统计过程中忽略大小写的差异，并打印最终每个字符出现的次数。
提示：
用一个int数组存储字符出现的次数，可以用一个128长度的数组，这样数组下标位置的元素就是该编码值字符出现的次数，缺点是浪费空间，但你可以先写一个这样的实现。

（扩展）做完后，你可以思考一下：
实际上只会有36个字符(10个数字和26个不区分大小写的字母)，所以int数组的长度实际上只需要36就可以了。
那么怎么把数组的长度缩短到36呢？
*/

void count_ch(int* count, int count_len,char* str) {
    int i = 0;
    while (str[i]!='\0') {
        count[str[i]]++;
        i++;
    }
    for (char c = 'A'; c <= 'Z'; c++) {
        count[c + ('a' - 'A')] += count[c];
        count[c] = 0;
    }
    i = 0;
    while (i < count_len) {
        if (count[i] > 0) {
            if (i >= ' ' && i <= '~') {  // 只打印可见字符
                printf("'%c' 出现 %d 次\n", (char)i, count[i]);
            }
            else {
                printf("ASCII码 %d 出现 %d 次\n", i, count[i]);
            }
        }
        i++;
    }
}

void count_c(int* count, int count_len, char* str) {
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] >= '0' && str[i] <= '9') {
            count[str[i]-'0']++;
        }
        else if (str[i] >= 'a' && str[i] <= 'z') {
            count[10 + (str[i] - 'a')]++;
        }
        else if (str[i] >= 'A' && str[i] <= 'Z') {
            count[10+(str[i]-'A')]++;
        }
        i++;
    }
    for (int i = 0; i < 36; i++) {
        if (count[i] > 0) {
            if (i < 10) {
                printf(" %c出现的次数为%d\n",(char)('0'+i),count[i]);
            }
            else {
                printf(" %c出现的次数为%d\n",(char)('a'+(i-10)), count[i]);
            }
        }
    }
}


int main(void) {
    char str[] = "abc239 ,. rg";
    /*int count1[128] = { 0 };
    count_ch(count1, 128, str);*/
    int count2[36] = { 0 };
    count_c(count2, 36, str);
    return 0;
}