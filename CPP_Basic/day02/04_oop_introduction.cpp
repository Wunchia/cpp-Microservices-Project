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

void test2(){
    const char*dog1[]={"1","白色","萨摩耶"};
    const char*dog2[]={"2","黄白色","柯基"};
    const char*dog3[]={"3","黄色","金毛"};
    cout<<dog1[0]<<" "<<dog1[1]<<" "<<dog1[2]<<endl;
    cout<<dog2[0]<<" "<<dog2[1]<<" "<<dog2[2]<<endl;
    cout<<dog3[0]<<" "<<dog3[1]<<" "<<dog3[2]<<endl;
    //数据类型受到限制
    //属性名和属性值之间的映射关系不够友好
    //name="萨摩耶"
    //age=1
}

class Dog{
public:
    int age;
    string color;
    string name;
    void bark(){
        cout<<" wof wof "<<endl;
    }
};

void test3(){
    int num=1;
    Dog dog1;
    dog1.age=1;
    dog1.color="白色";
    dog1.name="萨摩耶";
    Dog dog2;
    dog2.age=2;
    dog2.color="黄白色";
    dog2.name="柯基";
    Dog dog3;
    dog3.age=3;
    dog3.color="黄色";
    dog3.name="金毛";
}

int main(int argc,char *argv[])
{
    // test1();
    test2();
    return 0;
}

