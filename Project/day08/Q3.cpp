#include <iostream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

using namespace std;
using json=nlohmann::json;

//定义对象
struct Book{
    string title;
    string author;
    double price;
    string publisher;
    vector<string> tags;
};

// JSON -> Book
void from_json(const json& j, Book& b){
    j.at("title").get_to(b.title);
    j.at("author").get_to(b.author);
    j.at("price").get_to(b.price);
    j.at("publisher").get_to(b.publisher);
    j.at("tags").get_to(b.tags);
}

int main(int argc,char *argv[])
{
    string raw=R"(
        {
        "book": {
        "title": "JavaScript 高级程序设计",
        "author": "Nicholas C. Zakas",
        "price": 129.00,
        "publisher": "人民邮电出版社",
        "tags": ["前端", "JavaScript", "编程"]
        }
        }
    )";

    json j=json::parse(raw);

    string title=j["book"]["title"];
    double price=j["book"]["price"];
    auto& tags=j["book"]["tags"];
    cout << "书名: " << title << endl;
    cout << "价格: " << price << endl;
    cout << "标签: ";
    for (auto& t : tags)
    cout << t.get<string>() << " ";
    cout << endl;

    Book book=j["book"].get<Book>();
    cout<< "\n--- 通过 from_json 还原 ---\n";
    cout << "书名: " << book.title << endl;
    cout << "作者: " << book.author << endl;
    cout << "价格: " << book.price << endl;
    cout << "出版社: " << book.publisher << endl;
    cout << "标签: ";
    for (auto& t : book.tags)
    cout << t << " ";
    cout << endl;

    return 0;
}
