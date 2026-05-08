#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <algorithm>
using std::string;
using std::unordered_map;
using std::cin;
using std::cout;
using std::endl;

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

            _dict[word]++;
        }
        ifs.close();
    }

    void store(const string&filename){
        std::ofstream ofs(filename);
        if(!ofs){
            std::cerr<<"Error: cannot open output file: "<<filename<<endl;
            return;
        }

        for(const auto &[word,freq]:_dict){
            ofs<<word<<" : "<<freq<<"\n";
        }

        ofs.close();
        cout<<"Stored Successfully in"<<filename<<endl;
    }

private:
    unordered_map<string,int> _dict;

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

