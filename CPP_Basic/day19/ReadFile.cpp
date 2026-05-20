// ==================== 1. 引入标准库头文件 ====================
#include <iostream>   // 输入输出流，用于 cin, cout
#include <fstream>    // 文件流，用于读取文件 (ifstream)
#include <sstream>    // 字符串流，用于将一行文本拆分成一个个单词 (istringstream)
#include <string>     // 字符串类
#include <vector>     // 动态数组（向量），可以自动扩容。这里用来按顺序保存文件的每一行文本
#include <map>        // 字典（映射），用来保存 "单词" 到 "包含该单词的行号集合" 的对应关系
#include <set>        // 集合，特点是里面的元素不重复且自动排序。这里用来保存行号
#include <memory>     // 内存管理，这里主要是为了使用智能指针 shared_ptr
#include <algorithm>  // 算法库，这里为了使用 remove_if 函数来去除标点符号

// 声明我们即将使用的标准库中的名字，这样后面写代码就不用到处加 std:: 前缀了
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::map;
using std::set;
using std::shared_ptr;
using std::ostream;
using std::ifstream; 
using std::istringstream;

// ==================== 2. 类的提前声明 ====================
class QueryResult; // 提前告诉编译器有这么一个类，因为 TextQuery 类里需要用到它作为返回值类型

// ==================== 3. 核心类：TextQuery (文本查询类) ====================
// 负责读取文件并解析，构建 "单词" -> "行号" 的映射数据库
class TextQuery{
public:
    // 为 vector<string> 的大小类型起个别名叫 line_no (行号)，让代码更好读
    using line_no = vector<string>::size_type;

    // 读取文件并解析的方法
    void readFile(const string filename){
        // 尝试打开文件
        ifstream infile(filename);
        if(!infile){
            std::cerr << "open file " << filename << " failed" << endl;
            return; // 如果文件打开失败，报错并退出此函数
        }
        
        string line; // 用来临时存放读取到的一行文本
        line_no line_num = 1; // 行号计数器，从第一行开始算

        // getline() 每次从文件中读取一行，存入 line，直到读完整个文件
        while(getline(infile, line)){
            // 把读到的这一行完整地保存到 _lines 这个动态数组里
            _lines->push_back(line);

            // 将整行文本转换为字符串流，方便后面按空格提取单词
            istringstream iss(line);
            string word;
            
            // 只要还能从流里提取出单词，就继续循环
            while(iss >> word){
                // 【核心技巧：去除标点符号】
                // 比如把 "hello," 变成 "hello"。remove_if 配合 ::ispunct 识别并移走标点，erase 负责真正删除它们
                word.erase(remove_if(word.begin(), word.end(), ::ispunct), word.end());
                
                // 如果删掉标点后这个单词空了（比如原来只有一个逗号），就跳过
                if(word.empty()) continue;

                // 去 map 字典里找这个单词对应的 行号集合
                // 注意这里用了引用 auto&，表示我们要直接修改字典里的值
                auto& lines_set = _word2Numbers[word];
                
                // 如果这个单词是第一次遇到，它的智能指针默认是空的(nullptr)
                if(!lines_set){
                    // 给它分配一块新的内存（一个空的 set 集合）
                    lines_set.reset(new set<line_no>);
                }
                
                // 把当前的行号加进集合里
                // 由于用的是 set，如果这个词在同一行出现了两次，行号也只会保留一个
                lines_set->insert(line_num);
            }
            ++line_num; // 这一行处理完了，行号+1，准备处理下一行
        }
    }

    // 声明查询方法：传入一个单词，返回查询结果。
    // 结尾的 const 表示这个方法不会修改 TextQuery 类的成员变量
    QueryResult query(const string &word) const;

private:
    // 指向存放所有文件内容的动态数组的智能指针
    // 使用 shared_ptr 是为了查询结束后，QueryResult 也能直接拿去用，不用复制那么多文本数据
    shared_ptr<vector<string>> _lines = std::make_shared<vector<string>>();
    
    // 核心字典：保存 "单词" -> "指向包含该单词的行号集合的智能指针"
    // 例如： "apple" -> {1, 5, 9}
    map<string, shared_ptr<set<line_no>>> _word2Numbers;
};


// ==================== 4. 核心类：QueryResult (查询结果类) ====================
// 用于保存查询到的数据，并负责打印
class QueryResult{
    // 声明 print 为友元函数，允许 print 函数访问当前类的 private 私有成员
    friend ostream& print(ostream&, const QueryResult&);

public:
    using line_no = TextQuery::line_no;

    // 构造函数，用初始值列表给类的私有成员赋值
    // 参数分别是：查询的单词(w)，行号集合指针(f)，文件内容指针(l)
    QueryResult(string w,
                shared_ptr<set<line_no>> f,
                shared_ptr<vector<string>> l)
            : _sought(w)    // 初始化查询的单词
            , _lines(l)     // 初始化指向全文的指针
            , _file(f)      // 初始化指向行号集合的指针
            {}
private:
    string _sought;                      // 我们查询的那个单词
    shared_ptr<vector<string>> _lines;   // 指向 TextQuery 中保存的那份文件内容的指针
    shared_ptr<set<line_no>> _file;      // 指向包含该单词的所有行号集合的指针
};


// ==================== 5. TextQuery::query 的具体实现 ====================
// 在类外部实现刚刚在类里声明的 query 方法
QueryResult TextQuery::query(const string &word) const {
    // 静态局部变量：创建一个空的行号集合。
    // 如果用户查了一个文件中根本不存在的词，我们就返回这个空集合。
    // static 保证这块内存只初始化一次，不用每次查询失败都去 new 一个空集合。
    static shared_ptr<set<line_no>> no_maps(new set<line_no>);

    // 在字典里寻找指定的单词
    auto loc = _word2Numbers.find(word);
    
    if(loc == _word2Numbers.end()){
        // 如果没找到，返回包含空集合的 QueryResult 对象
        return QueryResult(word, no_maps, _lines);
    } else {
        // 如果找到了，loc->second 就是包含行号集合的那个智能指针。返回包含结果的 QueryResult 对象
        return QueryResult(word, loc->second, _lines);
    }
}


// ==================== 6. 打印结果的全局函数 ====================
// 格式化输出查询到的结果
ostream& print(ostream &os, const QueryResult &qr) {
    // 先打印总计信息，例如 "element occurs 3 times."
    os << qr._sought << " occurs " << qr._file->size() << " times." << endl;

    // 遍历行号集合中的每一个行号
    for(auto num : *qr._file) {
        // 打印行号和对应那行的文本。
        // 注意：行号(num)是从 1 开始计算的，但 vector 数组是从 0 开始索引的。
        // 所以取数据时要用 num - 1
        // *(qr._lines->begin() + num - 1) 是一种迭代器访问方式，等同于 (*qr._lines)[num - 1]
        os << "\t(line " << num << ") " << *(qr._lines->begin() + num - 1) << endl;
    }

    return os;
}


// ==================== 7. 测试函数 (未使用) ====================
// 这是一个硬编码的测试函数，开发者写的，但实际程序入口（main）并没有调用它
void test(){
    string queryWord("element");  // 写死要查的单词

    TextQuery tq;                 // 创建查询对象
    tq.readFile("china_daily.txt"); // 读取写死的文件名

    QueryResult result = tq.query(queryWord); // 执行查询

    print(cout, result);          // 打印结果
}


// ==================== 8. 程序主入口 ====================
// int argc: 运行程序时传入的参数个数
// char *argv[]: 运行程序时传入的参数字符串数组
int main(int argc, char *argv[])
{
    // 这个程序期望接收 3 个参数，例如在命令行里输入：
    // ./myprogram apple mybook.txt
    // argv[0] 是 "./myprogram" (程序本身的名字)
    // argv[1] 是 "apple" (我们要查的单词)
    // argv[2] 是 "mybook.txt" (我们要读的文件名)
    if(argc != 3){
        cout << "input wrong" << endl; // 如果参数不是正好3个，报错退出
        return -1;
    }
    
    // 把第二个参数（索引为1）当做要查询的单词
    string queryWord(argv[1]);

    TextQuery tq;
    // 把第三个参数（索引为2）当做文件名，交给 readFile 去读取
    tq.readFile(argv[2]);

    // 执行查询，获取结果
    QueryResult result = tq.query(queryWord);

    // 调用刚刚写的 print 函数打印最终结果
    print(cout, result);
    
    return 0; // 程序完美结束
}
