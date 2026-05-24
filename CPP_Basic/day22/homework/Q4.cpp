#include <iostream>
#include <stack>
#include <queue>
#include <list>
#include <string>
using namespace std;

int main(int argc,char *argv[])
{
    // 1. 栈
    stack<int,list<int>> st;

    st.push(1);
    st.push(2);
    st.push(3);

    while(!st.empty()){
        cout<<st.top()<<" ";
        st.pop();
    }
    cout<<endl;

    // 2. 队列
    queue<string,list<string>> q;

    q.push("a");
    q.push("b");
    q.push("c");

    while(!q.empty()){
        cout<<q.front()<<" ";
        q.pop();
    }
    cout<<endl;

    return 0;
}

