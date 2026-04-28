#include <iostream>
using std::cin;
using std::cout;
using std::endl;

// 异常处理的关键字
// try:代码块，包裹可能出现的异常
// catch:捕获异常，对异常进行处理
// throw:抛出异常信息

// try{
//
// }catch(异常类型 变量名){
//  对异常进行处理
// }catch(){
//
// }
// 可以有多个catch，但catch匹配是从上到下依次匹配
// 只有try中有异常了，并且catch中捕获的类型和throw的类型一样，
// 匹配成功，才能进入到catch代码块中执行
//

/*
 * 另一种使用场景，作为函数的一个特殊的返回结果
 * int func(int arr[],int index){
 *      if(index<0||index>=size){
 *          throw "index is illegal";
 *      }
 *      return arr[index];
 * }
 * 
 * stack：push pop
 * 
 */

int division(int x, int y)
{
    //针对特殊情况 分母为0时进行异常处理
    if(y==0){
        //抛出一个异常信息
        //throw+异常类型信息
        //throw "y is zero";
        throw 0;
    }
    cout << "in division" << endl;
    return x / y;
}

void test1()
{
    try
    {
        cout << "test1 start" << endl;
        int x = 9;
        int y = 0;
        cout << "division start" << endl;
        division(x, y);
        cout << "division end" << endl;
    }catch(const char *msg){
        //对异常信息进行处理
        cout<<"msg:"<<msg<<endl;
    }catch(int stateCode){
        cout<<"stateCode:"<<stateCode<<endl;
    }
    cout << "test1 end" << endl;
}

int main(int argc, char *argv[])
{
    cout << "main start" << endl;
    test1();
    cout << "main end" << endl;
    return 0;
}
