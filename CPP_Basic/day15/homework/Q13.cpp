#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::map;
using std::set;
using std::string;
using std::ifstream;
using std::ofstream;
using std::stringstream;

class TextQuery{
public:
    //读取文件并建立索引
    void readFile(const string& filename){
        ifstream ifs(filename);
        if(!ifs){
            std::cerr<<"无法打开文件："<<filename<<endl;
            return;
        }

        string line;
        int lineNum=0;//行号
        while(getline(ifs,line)){
            _lines.push_back(line);
            lineNum++;//第一行加进来 行号为1

            //将行转换为字符串流以提取单词
            stringstream ss(line);
            string word;
            while(ss>>word){
                //清理标点符号
                word=preprocess(word);
                if(word.empty()){continue;}

                _dict[word]++;//记录单词出现的总次数 用下标添加元素 或 更新记录
                _wordNumbers[word].insert(lineNum);//记录行号 用下标添加未出现过的词进map 再用insert加入行号的set
            }
        }
        ifs.close();
    }

    //查询单词
    void query(const string& word){
        string target=preprocess(word);
        
        auto it=_dict.find(target);
        if(it==_dict.end()){
            cout<<"word: '"<<target<<"' not found."<<endl;
            return;
        }

        cout<<target<<" occurs "<<it->second<<" times."<<endl;

        //获取该单词对应的行号集合
        const set<int>& lineSet=_wordNumbers[target];
        for(int num:lineSet){
            //打印对应行号 和 该行内容
            cout<<"(line "<< num <<") "<<_lines[num-1]<<endl;
        }
    }

private:
    vector<string> _lines;//存储 原始行 文本内容
    map<string,set<int>> _wordNumbers;//单词 到 行号集合 的映射
    map<string,int> _dict; //单词 到 出现总次数 的映射

    //辅助函数 去除标点符号
    string preprocess(string s){
        string result;
        for(char ch:s){
            if(!ispunct(ch)){
                result+=(char)tolower(ch);
            }
        }
        return result;
    }
};

int main(int argc,char *argv[])
{
    string fileName = "china_daily.txt"; 
    string queryWord = "is";

    TextQuery tq;
    tq.readFile(fileName);
    tq.query(queryWord);
    
    return 0;
}

