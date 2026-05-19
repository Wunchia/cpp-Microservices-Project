#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <memory>
#include <algorithm>
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

class QueryResult;

class TextQuery{
public:
    using line_no=vector<string>::size_type;

    void readFile(const string filename){
        ifstream infile(filename);
        if(!infile){
            std::cerr<<"open file" <<filename<<"failed"<<endl;
            return;
        }
        string line;
        line_no line_num=1;

        while(getline(infile,line)){
            _lines->push_back(line);

            istringstream iss(line);
            string word;
            while(iss>>word){
                word.erase(remove_if(word.begin(),word.end(),::ispunct),word.end());
                if(word.empty()) continue;

                auto&lines_set=_word2Numbers[word];
                if(!lines_set){
                    lines_set.reset(new set<line_no>);
                }
                lines_set->insert(line_num);
            }
            ++line_num;
        }
    }

    QueryResult query(const string &word)const;

private:
    shared_ptr<vector<string>> _lines=std::make_shared<vector<string>>();
    map<string,shared_ptr<set<line_no>>> _word2Numbers;
};


class QueryResult{
    friend ostream& print(ostream&,const QueryResult&);

public:
    using line_no=TextQuery::line_no;

    QueryResult(string w,
                shared_ptr<set<line_no>> f,
                shared_ptr<vector<string>> l)
            :_sought(w)
            ,_lines(l)
            ,_file(f)
            {}
private:
    string _sought;
    shared_ptr<vector<string>> _lines;
    shared_ptr<set<line_no>> _file;
};

QueryResult TextQuery::query(const string &word)const{
    static shared_ptr<set<line_no>> no_maps(new set<line_no>);

    auto loc= _word2Numbers.find(word);
    if(loc==_word2Numbers.end()){
        return QueryResult(word,no_maps,_lines);
    }else{
        return QueryResult(word,loc->second,_lines);
    }
}

ostream& print(ostream &os,const QueryResult &qr){
    os<<qr._sought<<" occurs "<<qr._file->size()<<" times."<<endl;

    for(auto num: *qr._file){
        os<<"\t(line "<<num<<")"<<*(qr._lines->begin()+num-1)<<endl;
    }

    return os;
}

void test(){
    string queryWord("element");

    TextQuery tq;
    tq.readFile("china_daily.txt");

    QueryResult result=tq.query(queryWord);

    print(cout,result);
}

int main(int argc,char *argv[])
{
    if(argc!=3){
        cout<<"input wrong"<<endl;
        return -1;
    }
    string queryWord(argv[1]);

    TextQuery tq;
    tq.readFile(argv[2]);

    QueryResult result=tq.query(queryWord);

    print(cout,result);
    return 0;
}

