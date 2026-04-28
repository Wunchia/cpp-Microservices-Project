#include <iostream>
#include <string>
using std::string;
using std::cin;
using std::cout;
using std::endl;
/*
 * 张三养了三只狗
 * 1岁白色萨摩耶
 * 2岁黄白色柯基
 * 3岁黄色金毛
 * 后续再增加信息量，变量会急剧增加
 * 
 */
// 用变量的方式描述
void test1(){
    int dog1Age=1;
    string dog1Color="white";
    string dog1Name="萨摩耶";

    int dog2Age=2;
    string dog2Color="yellow white";
    string dog2Name="柯基";

    int dog3Age=3;
    string dog3Color="yellow";
    string dog3Name="金毛";

    //如果信息比较多，变量随之变多
    //数据维护起来就比较麻烦
}

class dog{
    int age;
    string color;
    string name;
};

int main(int argc,char *argv[])
{
    
    return 0;
}

