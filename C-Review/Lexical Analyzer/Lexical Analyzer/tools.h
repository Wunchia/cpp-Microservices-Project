#ifndef TOOLS_H
#define TOOLS_H

typedef struct {
    // start一开始应该指向源代码字符串的起始位置
    // 当开始扫描一个新的Token时，这个指针指向Token的第一个字符。
    const char* start;
    // 词法分析器当前正在扫描处理的字符,会从某个Token的开头字符开始,一直移到Token结束,指向此Token的下一个字符
    const char* current;
    // 当前读取的行
    int line;
} Scanner;


#endif // !TOOLS_H


