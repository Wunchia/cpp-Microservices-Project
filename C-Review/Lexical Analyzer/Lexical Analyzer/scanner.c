#define _CRT_SECURE_NO_WARNINGS

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "tools.h"
#include "scanner.h"

typedef struct {
    // start一开始应该指向源代码字符串的起始位置
    // 当开始扫描一个新的Token时，这个指针指向Token的第一个字符。
    const char* start;
    // 词法分析器当前正在扫描处理的字符,会从某个Token的开头字符开始,一直移到Token结束,指向此Token的下一个字符
    const char* current;
    // 当前读取的行
    int line;
} Scanner;

// 全局变量结构体对象,后续所有函数的操作都基于同一个scanner结构体对象
static Scanner scanner;
static char message[50];		// 该全局变量字符数组用于存储打印errToken时,存放错误信息

void initScanner(const char* source) {
    // 初始化全局变量scanner
    // start和current一开始都可以指向源代码字符串的起始位置
    scanner.start = source;
    scanner.current = source;
    scanner.line = 1;
}


// Scanner核心逻辑,用于返回制作好的Token对象
Token scanToken() {
    // 跳过前置空白字符和注释
    skipWhitespace();
    /*
        curr指针在处理完一个Token后,就会指向该Token的下一个字符位置
        而且由于skipWhitespace的存在会跳过前面的空白字符
        所以curr指针此时一定指向下一个Token的开始字符
        于是记录下一个Token的起始位置
        此时scanner.start就指向这一个要处理Token的首字符
    */
    scanner.start = scanner.current;

    // 如果当前正在处理的字符就是空字符,那就返回TOKEN_EOF,表示处理结束了
    if (isAtEnd()) {
        return makeToken(TOKEN_EOF);
    }

    // curr指针现在指向当前Token的第二个字符,即curr指针前进了一位
    // 但这个字符c仍然是该Token的第一个字符，因为advance函数会返回curr指针移动前指向的一个字符
    char c = advance();

    // 如果Token的第一个字符是字母和下划线就进入标识符的处理模式
    if (isAlpha(c)) {
        return identifier();
    }
    // 如果Token的第一个字符是数字,那就进入数字的处理模式
    if (isDigit(c)) return number();

    // 如果Token的第一个字符既不是数字也不是字母和下划线,那么就switch处理它
    switch (c) {
        // 第一部分: 处理单字符Token
    case '(': return makeToken(TOKEN_LEFT_PAREN);
    case ')': return makeToken(TOKEN_RIGHT_PAREN);
    case '[': return makeToken(TOKEN_LEFT_BRACKET);
    case ']': return makeToken(TOKEN_RIGHT_BRACKET);
    case '{': return makeToken(TOKEN_LEFT_BRACE);
    case '}': return makeToken(TOKEN_RIGHT_BRACE);
    case ',': return makeToken(TOKEN_COMMA);
    case '.': return makeToken(TOKEN_DOT);
    case ';': return makeToken(TOKEN_SEMICOLON);
    case '~': return makeToken(TOKEN_TILDE);

        // 可单可双字符的Token处理会稍微复杂一点,但不多
        // 如果当前字符是+号
    case '+':
        // 如果Token的第二个字符也是+,那就生产++双字符Token返回
        if (match('+')) {
            return makeToken(TOKEN_PLUS_PLUS);
        }
        // 如果Token的第二个字符是=,那就生产+=双字符Token返回
        else if (match('=')) {
            return makeToken(TOKEN_PLUS_EQUAL);
        }
        // 如果上面都不是,说明就是单字符+ Token
        else {
            return makeToken(TOKEN_PLUS);
        }
    case '-':
        if (match('-')) {
            return makeToken(TOKEN_MINUS_MINUS);
        }
        else if (match('=')) {
            return makeToken(TOKEN_MINUS_EQUAL);
        }
        else if (match('>')) {
            return makeToken(TOKEN_MINUS_GREATER);
        }
        else {
            return makeToken(TOKEN_MINUS);
        }
    case '*':
        return makeToken(match('=') ? TOKEN_STAR_EQUAL : TOKEN_STAR);
    case '/':
        return makeToken(match('=') ? TOKEN_SLASH_EQUAL : TOKEN_SLASH);
    case '%':
        return makeToken(match('=') ? TOKEN_PERCENT_EQUAL : TOKEN_PERCENT);
    case '&':
        if (match('=')) {
            return makeToken(TOKEN_AMPER_EQUAL);
        }
        else if (match('&')) {
            return makeToken(TOKEN_AMPER_AMPER);
        }
        else {
            return makeToken(TOKEN_AMPER);
        }
    case '|':
        if (match('=')) {
            return makeToken(TOKEN_PIPE_EQUAL);
        }
        else if (match('|')) {
            return makeToken(TOKEN_PIPE_PIPE);
        }
        else {
            return makeToken(TOKEN_PIPE);
        }
    case '^':
        return makeToken(match('=') ? TOKEN_HAT_EQUAL : TOKEN_HAT);
    case '=':
        return makeToken(match('=') ? TOKEN_EQUAL_EQUAL : TOKEN_EQUAL);
    case '!':
        return makeToken(match('=') ? TOKEN_BANG_EQUAL : TOKEN_BANG);
    case '<':
        if (match('=')) {
            return makeToken(TOKEN_LESS_EQUAL);
        }
        else if (match('<')) {
            return makeToken(TOKEN_LESS_LESS);
        }
        else {
            return makeToken(TOKEN_LESS);
        }
    case '>':
        if (match('=')) {
            return makeToken(TOKEN_GREATER_EQUAL);
        }
        else if (match('>')) {
            return makeToken(TOKEN_GREATER_GREATER);
        }
        else {
            return makeToken(TOKEN_GREATER);
        }
        // 多字符Token处理,上面已经处理过标识符和数字了 
    case '"': return string(); // 如果Token的第一个字符是双引号,那就进入字符串处理模式
    case '\'': return character();	// 如果Token的第一个字符是单引号,那就进入字符处理模式
    }
    // 如果读到的字符不在上面的所有之列,那就无法识别,于是制造一个errorToken返回
    // 比如代码中的#(预处理阶段就没了) $(C语言不用该字符) 注释中的中文
    return errorTokenWithChar(c);
}