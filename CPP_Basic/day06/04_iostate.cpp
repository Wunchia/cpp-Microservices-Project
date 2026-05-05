#include <iostream>
#include <limits>
using std::cin;
using std::cout;
using std::endl;
using std::istream;

/*
 * 流的四种状态
 * 1.good() : 没错，流可以正常使用
 * 2.bad() ：物理因素可能会导致 比如磁盘坏了
 * 3.fail()：输入的数据和接收端的类型不匹配
 * 4.eof()：流中的数据不可用 到末尾了
 *
 * cin:标准输入流 istream类型的对象
 * 
 */

void printState(istream &is){
    cout<<"good:"<<is.good()<<endl;
    cout<<"bad:"<<is.bad()<<endl;
    cout<<"fail:"<<is.fail()<<endl;
    cout<<"eof:"<<is.eof()<<endl;
    cout<<"---------->"<<endl;
}

void test1(){
    printState(cin);
    cout<<"input a num:"<<endl;
    int num;
    cin>>num;
    cout<<"num="<<num<<endl;
    cout<<"--------->"<<endl;
    printState(cin);
    //恢复流的状态 clear()
    cin.clear();//只恢复流的状态，不清理缓冲区
    //忽略指定大小的缓冲区的大小
    cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    printState(cin);
    int num2;
    cout<<"input a num:"<<endl;
    cin>>num2;//类型不匹配的数据存放在缓冲区，一cin就又拿到了
    cout<<"---------"<<endl;
    printState(cin);
    cout<<"num2="<<num2<<endl;

}

//用户可以连续进行输入，直到输入正确为止
void test2(){
    int num;
    while(true){
        cout<<"input a num : "<<endl;
        cin>>num;
        if(cin.bad()){
            cout<<"badboy!!!!"<<endl;
        }else if(cin.eof()){
            cout<<"eof!!!!"<<endl;
        }else if(cin.fail()){
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            cout<<"input again:"<<endl;
        }else{
            cout<<"OK!"<<endl;
            break;
        }
    }
    cout<<"num="<<num<<endl;
}

void test3(){
    int num;
    while(!cin.eof()){
        cout<<"input a num : "<<endl;
        cin>>num;
        if(cin.bad()){
            cout<<"badboy!!!!"<<endl;
        }else if(cin.fail()){
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            cout<<"input again:"<<endl;
        }else{
            cout<<"OK!"<<endl;
            break;
        }
    }
    cout<<"num="<<num<<endl;
}

int main(int argc,char *argv[])
{
    // test1();
    // test2();
    test3();
    return 0;
}

