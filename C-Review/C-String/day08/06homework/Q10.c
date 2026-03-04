#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_BOOKS 10

//请定义一个Book书籍结构体类型来存储一本书的信息，以及Genre这个书籍类别枚举类型。
typedef enum Genre {
SCIENCE_FICTION,
LITERATURE,
HISTORY,
TECHNOLOGY,
OTHER
}Genre;

typedef struct book {
	int id;
	char name[20];
	char author[20];
	Genre genre;
}Book;

//书籍类别的枚举类型包含以下类别：
//科幻（SCIENCE_FICTION）
//文学（LITERATURE）
//历史（HISTORY）
//科技（TECHNOLOGY）
//其他（OTHER）
//现在给定你一个Book结构体对象数组的数据，一共十本书：
//#define MAX_BOOKS 10
//Book books[MAX_BOOKS] = {
//    {1, "三体", "刘慈欣", SCIENCE_FICTION},
//    {2, "红楼梦", "曹雪芹", LITERATURE},
//    {3, "中国通史", "吕思勉", HISTORY},
//    {4, "时间简史", "史蒂芬·霍金", TECHNOLOGY},
//    {5, "围城", "钱钟书", LITERATURE},
//    {6, "傲慢与偏见", "简·奥斯汀", LITERATURE},
//    {7, "呼啸山庄", "艾米莉·勃朗特", LITERATURE},
//    {8, "活着", "余华", LITERATURE},
//    {9, "明朝那些事儿", "当年明月", HISTORY},
//    {10, "乌合之众", "古斯塔夫·勒庞", OTHER}
//};
//请实现以下功能：
//程序启动，即打印所有书籍的信息。
//根据用户输入的书籍类别编号，查找并输出该类别的所有书籍信息。

char* get_genre_name(Genre genre) {
    switch (genre) {
    case 0:
        return "科幻";
    case 1:
        return "文学";
    case 2:
        return "历史";
    case 3:
        return "科技";
    case 4:
        return "其他";
    default:
        return NULL;
    }
};

void find_Genre(Book *books,Genre genre){
    printf("%s 类别的书有：\n", get_genre_name(genre));
    for (int i = 0; i < MAX_BOOKS; i++) {
        if (books[i].genre == genre) {
            printf("编号：%d\t\t书名：%s\t\t作者：%s\n", books[i].id, books[i].name, books[i].author);
        }
    }
    printf("=====END====\n");
}

int main(void) {
    Book books[MAX_BOOKS] = {
        {1, "三体", "刘慈欣", SCIENCE_FICTION},
        {2, "红楼梦", "曹雪芹", LITERATURE},
        {3, "中国通史", "吕思勉", HISTORY},
        {4, "时间简史", "史蒂芬·霍金", TECHNOLOGY},
        {5, "围城", "钱钟书", LITERATURE},
        {6, "傲慢与偏见", "简·奥斯汀", LITERATURE},
        {7, "呼啸山庄", "艾米莉·勃朗特", LITERATURE},
        {8, "活着", "余华", LITERATURE},
        {9, "明朝那些事儿", "当年明月", HISTORY},
        {10, "乌合之众", "古斯塔夫·勒庞", OTHER}
    };
    for (int i = 0; i < MAX_BOOKS; i++) {
        printf("编号：%d\t\t书名：%s\t\t作者：%s\t\t类别：%s\n", books[i].id, books[i].name, books[i].author, get_genre_name(books[i].genre));
    }
    Genre genre = -1;
    printf("请输入想要寻找的类别编号：(0:科幻 1:文学 2:历史 3:科技 4:其他）\n");
    scanf("%d", &genre);
    if (genre < 0 || genre>4) {
        printf("输入错误！\n");
        return -1;
    }
    find_Genre(books, genre);
    return 0;
}