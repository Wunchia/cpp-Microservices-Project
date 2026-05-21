#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <memory>
#include <algorithm>
using std::string;
using std::vector;
using std::map;
using std::set;
using std::ifstream;
using std::istringstream;
using std::ostream;
using std::shared_ptr;
using std::cin;
using std::cout;
using std::endl;

//=======================类的设计===========================
class QueryResult;

class TextQuery{
public:
    using line_no =vector<string>::size_type;

    TextQuery(ifstream &);
    QueryResult query(const string&)const;

private:
    //用一个智能指针指向vector 避免多次复制
    shared_ptr<vector<string>> _lines=std::make_shared<vector<string>>();

    //用set存行号 用智能指针指向set避免多次复制
    //map 建立 单词 到 行号集合 的映射
    map<string,shared_ptr<set<line_no>>> _word2Numbers;
};

class QueryResult{
friend ostream& print(ostream&,const QueryResult&);
public:
    using line_no=TextQuery::line_no;

    //有参构造 将查询的单词、行号set、文本集传入
    QueryResult(string s,
                shared_ptr<set<line_no>> p,
                shared_ptr<vector<string>> f)
            :sought(s),_line_no(p),_lines(f){}

private:
    string sought;//查询的单词
    shared_ptr<set<line_no>> _line_no;//单词出现的行号 和TextQuery类共享
    shared_ptr<vector<string>> _lines;//输入的文本
};

//======================函数的实现=========================
//辅助函数
string clean_word(const string &word){
    string ret;
    for(char ch:word){
        if(!ispunct(static_cast<unsigned char>(ch))){
            ret+=tolower(static_cast<unsigned char>(ch));
        }
    }
    return ret;
}

//有参构造 构造过程即解析过程
TextQuery::TextQuery(ifstream &is)
:_lines(std::make_shared<vector<string>>())
{
    string text;
    while(getline(is,text)){//对读入的文件的每一行
        _lines->push_back(text);//保存此行文本
        int n=_lines->size()-1;//当前行号
        istringstream line(text);//将文本分解为单词
        string word;
        while(line>>word){
            string cleaned=clean_word(word);
            if(cleaned.empty()) continue;
            //如果单词不在_word2Numbers中，以之为key在其中添加一项
            auto& lines=_word2Numbers[cleaned];//lines是一个指向set的 shared_ptr
            if(!lines){ //在我们第一次遇到这个单词时，此指针为空
                lines=std::make_shared<set<line_no>>();
            }
            lines->insert(n);//将此行号插入set中
        }
    }
}

QueryResult TextQuery::query(const string &sought)const{
    //如果未找到 sought，我们将返回一个指向行号的空set的 QueryResult对象
    static shared_ptr<set<line_no>> nodata(new set<line_no>);
    auto loc=_word2Numbers.find(sought);
    if(loc==_word2Numbers.end()){
        return QueryResult(sought,nodata,_lines);
    }else{
        return QueryResult(sought,loc->second,_lines);
    }
}

//工具函数 格式化打印时的time 加不加 s
string make_plural(size_t ctr,const string &word,const string &ending){
    return (ctr>1)? word+ending : word;
}

ostream& print(ostream& os,const QueryResult &qr){
    os<<qr.sought<<" 出现了 "<<qr._line_no->size()<<" "
    <<make_plural(qr._line_no->size(),"time","s")<<endl;

    for(auto num:*qr._line_no){
        os<<"\t(line "<<num+1<<") "
        <<*(qr._lines->begin()+num)<<endl;
    }
    return os;
}

void runQueries(ifstream& infile){
    TextQuery tq(infile);
    while(true){
        cout<<"enter word to look for, or q to quit:"<<endl;
        string s;
        if(!(cin>>s)||s=="q"){
            break;
        }
        string cleaned_s=clean_word(s);
        if(cleaned_s.empty()){
            cout<<"Invalid input"<<endl;
            continue;
        } 
        print(cout,tq.query(s))<<endl;
    }
}

int main(int argc,char *argv[])
{
    if(argc!=2){
        cout<<"Usage: "<<argv[0]<<" file"<<endl;
        return 1;
    }
    ifstream infile(argv[1]);
    if(!infile){
        cout<<"could not open the file "<<argv[1]<<endl;
        return 1;   
    }else{
        runQueries(infile);
    }
    return 0;
}

