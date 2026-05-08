#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::endl;

struct Record{
    string _word;
    int _frequency;
};

class Dictionary{
public:
    void read(const string &filename){
        std::ifstream ifs(filename);
        if(!ifs){
            std::cerr<<"Error: cannot open input file: "<<filename<<endl;
            return;
        }

        string word;
        while(ifs>>word){
            preprocess(word);
            if(word.empty()) continue;

            bool found =false;
            for (auto &record:_dict){
                if(record._word==word){
                    record._frequency++;
                    found=true;
                    break;
                }
            }

            if(!found){
                _dict.push_back({word,1});
            }
        }

        ifs.close();
    }

    void store(const string&filename){
        std::ofstream ofs(filename);
        if(!ofs){
            std::cerr<<"Error: cannot open output file: "<<filename<<endl;
            return;
        }

        for(const auto &record:_dict){
            ofs<<record._word<<" : "<<record._frequency<<"\n";
        }

        ofs.close();
        cout<<"Stored Successfully in"<<filename<<endl;
    }

private:
    vector<Record> _dict;

    void preprocess(string &word){
        for(auto &ch:word){
            ch=tolower(ch);
        }

        word.erase(std::remove_if(word.begin(),word.end(),ispunct),word.end());
    }
};

int main(int argc,char *argv[])
{
    Dictionary dict;
    
    dict.read("The_Holy_Bible.txt");
    dict.store("dict.txt");

    return 0;
}

