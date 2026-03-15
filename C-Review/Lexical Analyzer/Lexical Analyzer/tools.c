#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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

// 下面我给大家提供了很多会用到的辅助函数,建议使用
// 检查字符c是否是字母或下划线。
static bool isAlpha(char c) {
    return (c >= 'a' && c <= 'z') ||
        (c >= 'A' && c <= 'Z') ||
        c == '_';
}

// 检查字符c是否是数字。
static bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

// 判断词法分析器当前正在处理的字符是不是空字符(即判断是否处理完了)，curr不动
static bool isAtEnd() {
    return *scanner.current == '\0';
}

// curr指针前进一个字符,并返回之前curr指针指向的元素
static char advance() {
    return *scanner.current++;
}

// 查看当前正在处理的字符是什么,curr不动
static char peek() {
    return *scanner.current;
}

// 如果当前正在处理的字符不是空字符,那就返回下一个要处理的字符,但curr不动
static char peekNext() {
    if (isAtEnd()) {
        // 如果已经在处理空字符了，那么直接返回空字符
        return '\0';
    }
    return *(scanner.current + 1);
}

// 检查词法分析器当前正在处理的字符是不是符合预期,如果符合预期,curr前进一位
static bool match(char expected) {
    if (isAtEnd()) {
        // 如果已经在处理空字符了，那么直接返回false
        return false;
    }
    if (peek() != expected) {
        // 如果当前处理的字符不符合预期，直接返回false
        return false;
    }
    scanner.current++;  // 在返回true之前, 将curr向后移动一位
    return true;
}

// 根据传入的TokenType类型来制造返回一个Token
static Token makeToken(TokenType type) {
    Token token;
    token.type = type;
    token.start = scanner.start;    // scanner.start是当前Token的第一个字符
    // 当此Token结束时,也就是处理它最后一个字符时,curr指向该Token后的第一个字符,此时指针相减就是Token的字符串长度
    token.length = (int)(scanner.current - scanner.start);
    token.line = scanner.line;  // 更新line行
    return token;
}

// 当遇到不可识别的字符时,就返回一个TOKEN_ERROR类型的Token
// 比如遇到@，$等不在处理范围内的符号时，比如处理字符串，字符没有对应的右引号时。
static Token errorToken(const char* message) {
    Token token;
    token.type = TOKEN_ERROR;
    token.start = message;
    token.length = (int)strlen(message);
    token.line = scanner.line;
    return token;
}

static void skipWhitespace() {
    // 跳过空白字符: ' ', '\r', '\t', '\n'和注释
    // 注释以'//'开头, 一直到行尾
    // 注意更新scanner.line！
    /*
       * 思路:
       * 不知道究竟有多少个 所以要死循环
       * 瞥一眼下一个字符然后switch判断
       * 碰到空格,制表,回车就advance前进..
       * 如果碰到换行 那就sc.line++再前进
       * 注释:
       * 如果下一个字符是/,那就再瞥一眼下下个字符,如果还是/,那就是注释
       * 此时要把一整行都要跳过,用while循环
       * 结束:
       * 只要不是下一个字符不是上面提出来的几个,就结束死循环
       */
    for (;;) {
        char c = peek();
        switch (c) {
        case ' ':
        case '\r':
        case '\t':
            advance();
            break;
        case '\n':
            scanner.line++;
            advance();
            break;
        case '/':
            if (peekNext() == '/') {
                // 跳过一整行注释
                while (!isAtEnd() && peek() != '\n') advance();
            }
            else {
                return;
            }
            break;
        default:
            return;
        }
    }
}
// 用于检查当前扫描的Token的类型是不是type 如果是就返回type
static TokenType checkKeyword(int start, int length, const char* rest, TokenType type) {
    /*
        start: 待检查序列的起始字符下标
            比如要检查关键字break，那么在case b的前提下，需要传入reak来进行检查
            这里start就等于1，scanner.start[1]
        length: 待检查序列的长度，如果检查的是break，就是检查剩余的reak
            需要传入4
        rest指针，待检查的剩余序列字符串，这里直接传入一个字面值字符串就行了
            比如检查break，传入"reak"就好了
        type：你要检查的关键字Token的类型，比如检查break，那就传入Token_BREAK

        检查从start位置开始，长度为length的字符串是否与给定的rest字符串相匹配
        先判断长度是否一致 再判断内容
    */
    if (scanner.current - scanner.start == start + length &&
        /*
                    int memcmp(const void *s1, const void *s2, size_t n);
                    这里的参数分别是：

                    s1：指向第一块内存区域的指针。
                    s2：指向第二块内存区域的指针。
                    n：要比较的字节数。
                    memcmp 函数会逐字节比较 s1 和 s2 指向的内存区域，直到有不相等的字节或比较了 n 个字节为止。
                    如果两个内存区域完全相同，
                    则 memcmp 返回 0；如果第一个不同的字节在 s1 中的值小于 s2 中对应的值，返回负数；
                    反之，返回正数。
        */
        memcmp(scanner.start + start, rest, length) == 0) {
        return type;
    }
    return TOKEN_IDENTIFIER;
}

static TokenType identifierType() {
    // 确定identifier类型主要有两种方式：
    // 1. 将所有的关键字放入哈希表中，然后查表确认 
    // Key-Value 就是"关键字-TokenType" 可以做 但存在额外内存占用且效率不如下一个方式好
    // 2. 将所有的关键字放入Trie树(读踹，字典查找树)中，然后查表确认
    // Trie树的方式不管是空间上还是时间上都优于哈希表的方式
    char c = scanner.start[0];
    // 用switch...switch...if组合构建逻辑上的trie树
    switch (c) {
        // keywords
    case 'b': return checkKeyword(1, 4, "reak", TOKEN_BREAK);
    case 'c': {
        int len = scanner.current - scanner.start;
        if (len > 1) {
            switch (scanner.start[1]) {
            case 'a': return checkKeyword(2, 2, "se", TOKEN_CASE);
            case 'h': return checkKeyword(2, 2, "ar", TOKEN_CHAR);
            case 'o':
                if (len > 3 && scanner.start[2] == 'n') {
                    switch (scanner.start[3]) {
                    case 's': return checkKeyword(4, 1, "t", TOKEN_CONST);
                    case 't': return checkKeyword(4, 4, "inue", TOKEN_CONTINUE);
                    }
                }
            }
        }
        break;
    }
    case 'd': {
        int len = scanner.current - scanner.start;
        if (len > 1) {
            switch (scanner.start[1]) {
            case 'e': return checkKeyword(2, 5, "fault", TOKEN_DEFAULT);
            case 'o':
                if (len == 2) return TOKEN_DO;
                else return checkKeyword(2, 4, "uble", TOKEN_DOUBLE);
            }
        }
        break;
    }
    case 'e': {
        int len = scanner.current - scanner.start;
        if (len > 1) {
            switch (scanner.start[1]) {
            case 'l': return checkKeyword(2, 2, "se", TOKEN_ELSE);
            case 'n': return checkKeyword(2, 2, "um", TOKEN_ENUM);
            }
        }
        break;
    }
    case 'f': {
        int len = scanner.current - scanner.start;
        if (len > 1) {
            switch (scanner.start[1]) {
            case 'l': return checkKeyword(2, 3, "oat", TOKEN_FLOAT);
            case 'o': return checkKeyword(2, 1, "r", TOKEN_FOR);
            }
        }
        break;
    }
    case 'g': return checkKeyword(1, 3, "oto", TOKEN_GOTO);
    case 'i': {
        int len = scanner.current - scanner.start;
        if (len > 1) {
            switch (scanner.start[1]) {
            case 'f': return checkKeyword(2, 0, "", TOKEN_IF);
            case 'n': return checkKeyword(2, 1, "t", TOKEN_INT);
            }
        }
        break;
    }
    case 'l': return checkKeyword(1, 3, "ong", TOKEN_LONG);
    case 'r': return checkKeyword(1, 5, "eturn", TOKEN_RETURN);
    case 's': {
        int len = scanner.current - scanner.start;
        if (len > 1) {
            switch (scanner.start[1]) {
            case 'h': return checkKeyword(2, 3, "ort", TOKEN_SHORT);
            case 'i':
                if (len > 2) {
                    switch (scanner.start[2]) {
                    case 'g': return checkKeyword(3, 3, "ned", TOKEN_SIGNED);
                    case 'z': return checkKeyword(3, 3, "eof", TOKEN_SIZEOF);
                    }
                }
                break;
            case 't': return checkKeyword(2, 4, "ruct", TOKEN_STRUCT);
            case 'w': return checkKeyword(2, 4, "itch", TOKEN_SWITCH);
            }
        }
        break;
    }
    case 't': return checkKeyword(1, 6, "ypedef", TOKEN_TYPEDEF);
    case 'u': {
        int len = scanner.current - scanner.start;
        if (len > 2 && scanner.start[1] == 'n') {
            switch (scanner.start[2]) {
            case 'i': return checkKeyword(3, 2, "on", TOKEN_UNION);
            case 's': return checkKeyword(3, 5, "igned", TOKEN_UNSIGNED);
            }
        }
        break;
    }
    case 'v': return checkKeyword(1, 3, "oid", TOKEN_VOID);
    case 'w': return checkKeyword(1, 4, "hile", TOKEN_WHILE);
    }

    // 没有在上面switch中返回，那肯定不是关键字，而是标识符
    return TOKEN_IDENTIFIER;
}

// 当前Token的开头是下划线或字母判断它是不是标识符Token
static Token identifier() {
    // 判断curr指针当前正在处理的字符是不是 字母 下划线 数字
    while (isAlpha(peek()) || isDigit(peek())) {
        advance();  // 继续前进看下一个字符 直到碰到下一个字符不是字母 下划线 以及数字 结束Token
    }
    // 当while循环结束时，scanner.curr指针指向的是该Token字符串的下一个字符
    // 这个函数的意思是: 只要读到字母或下划线开头的Token我们就进入标识符模式
    // 然后一直找到此Token的末尾
    // 但代码运行到这里还不确定Token是标识符还是关键字, 因为它可能是break, var, goto, max_val...
    // 于是执行identifierType()函数，它是用来确定Token类型的
    return makeToken(identifierType());
}

static Token number() {
    // 简单起见，我们将NUMBER的规则定义如下:
    // 1. NUMBER可以包含数字和最多一个'.'号
    // 2. '.'号前面要有数字
    // 3. '.'号后面也要有数字
    // 这些都是合法的NUMBER: 123, 3.14
    // 这些都是不合法的NUMBER: 123., .14(虽然在C语言中合法)
    // 这个过程要不断的前进跳过所有的数字,
    // 比如数字123.456 最终要保证sc.start指向1,curr指向6后面第一个非数字字符
    while (isDigit(peek())) advance();

    // 查找有无小数部分
    if (peek() == '.' && isDigit(peekNext())) {
        // 跳过小数点
        advance();
        while (isDigit(peek())) advance();
    }
    return makeToken(TOKEN_NUMBER);
}

static Token string() {
    // 字符串以"开头，以"结尾，而且不能跨行
    // 为了简化工作量
    // 如果下一个字符不是末尾也不是双引号，全部跳过(curr可以记录长度，不用担心)
    while (!isAtEnd() && peek() != '"') {
        if (peek() == '\n') {
            return errorToken("Not support multi-line string.");
        }
        advance();
    }
    if (isAtEnd()) {
        return errorToken("Unterminated string.");
    }
    advance();
    return makeToken(TOKEN_STRING);
}

// 进入字符处理模式
static Token character() {
    // 字符'开头，以'结尾，而且不能跨行，不支持转义字符，''中间必须只有一个字符
    // 如果下一个字符不是末尾也不是单引号，全部跳过(curr可以记录长度，不用担心)

    // 1.判断当前curr指向的是不是空字符,如果是空字符,那就返回一个errToken
    if (isAtEnd()) {
        return errorToken("此字符不完整,缺少右单引号!");
    }
    // 2.让curr指针继续走,找到右单引号
    while (!isAtEnd() && peek() != '\'') {
        // 如果当前正在处理的字符既不是空字符,也不是右单引号,那就继续走
        if (peek() == '\n') {
            return errorToken("不支持多行字符!");
        }
        advance();
    } // while循环结束时,要么处理到了空字符,要么处理到了右单引号
    if (isAtEnd()) {
        return errorToken("此字符不完整,缺少右单引号!");
    }
    // （重点）结束一个Token处理时，要保证curr指针移动向此Token的下一个位置！！！！
    advance();
    // 接下来要判断一下此字符是不是单个长度,单引号中出现多个字符是不允许的
    int charLen = scanner.current - scanner.start - 2;
    if (charLen == 1 || charLen == 0) {
        return makeToken(TOKEN_CHARACTER);
    }
    // 需求: 现在单引号中间的字符序列长度超长了,于是要打印这个超长的序列
    // 输出效果是: 非单字符Token: xxx(单引号中间的序列)
    char* charStart = scanner.start + 1;
    // 我们需要格式化的向目标字符数组中输出一个字符串
    sprintf(message, "非单字符Token: %.*s", charLen, charStart);
    return errorToken(message);
}

// 处理无法识别的字符
static Token errorTokenWithChar(char character) {
    // 将无法识别的字符是什么输出
    sprintf(message, "Unexpected character: %c", character);
    return errorToken(message);
}