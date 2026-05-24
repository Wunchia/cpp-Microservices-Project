#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
using namespace std;

unordered_map<string,string> buildMap(ifstream &map_file){
    unordered_map<string,string> trans_map;
    string key;
    string value;
    while(map_file>>key && getline(map_file,value)){
        if(value.size()>1){
            trans_map[key]=value.substr(1);
        }else{
            throw runtime_error("no rule for "+key);
        }
    }
    return trans_map;
}

const string& treansform(const string &s,const unordered_map<string,string> &m){
    auto map_it=m.find(s);
    if(map_it!=m.end()){
        return map_it->second;
    }
    return s;
}

void wordTransform(ifstream &map_file,ifstream &input_file){
    auto trans_map=buildMap(map_file);

    string text;
    while(getline(input_file,text)){
        istringstream stream(text);
        string word;
        bool firstword=true;

        while(stream>>word){
            if(firstword){
                firstword=false;
            }else{
                cout<<" ";
            }
            cout<<treansform(word,trans_map);
        }
        cout<<endl;
    }
}


int main(int argc,char *argv[])
{
    ifstream map_file("map.txt");
    ifstream input_file("file.txt");
    
    if(!map_file || !input_file){
        std::cerr<<"Error: Cannot open file "<<endl;
        return 1;
    }

    wordTransform(map_file,input_file);
    
    return 0;
}

