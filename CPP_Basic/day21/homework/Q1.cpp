#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <algorithm>
#include <numeric>
#include <ctime>
using namespace std;

class Person{
public:
    Person(string name, double score)
    :_name(name),_score(score)
    {}
    string _name;
    double _score;
};

void createPerson(vector<Person>& v){
    string nameSeed="ABCDE";
    for(int i=0;i<5;i++){
        string name="选手";
        name+=nameSeed[i];

        double score=0;

        v.push_back(Person(name,score));
    }
}

void setScore(vector<Person>& v){
    for(auto it=v.begin();it!=v.end();it++){
        deque<double> d;
        for(int i=0;i<10;++i){
            double score=rand()%41+60;
            d.push_back(score);
        }

        sort(d.begin(),d.end());

        d.pop_front();
        d.pop_back();
        
        double sum=0;
        for(auto dit=d.begin();dit!=d.end();dit++){
            sum+=*dit;
        }
        double avg=sum/d.size();

        it->_score=avg;
    }
}

void showScore(vector<Person>& v){
    cout<<"========score========"<<endl;
    for(auto it=v.begin();it!=v.end();it++){
        cout<<"选手："<<it->_name<<" 平均得分："<<it->_score<<endl;
    }
}

int main(int argc,char *argv[])
{
    srand((unsigned int)time(NULL));

    vector<Person> v;
    createPerson(v);
    setScore(v);
    showScore(v);
    
    return 0;
}

