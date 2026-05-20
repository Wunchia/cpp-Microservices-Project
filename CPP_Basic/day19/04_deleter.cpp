#include <iostream>
#include <string>
#include <memory>
using std::unique_ptr;
using std::string;
using std::cin;
using std::cout;
using std::endl;

/*
 * 删除器：回收资源
 * 针对其他资源：文件资源、网络资源……
 * 需要针对特殊的资源进行特殊的回收处理--->自定义删除器
 * 
 * 
 */

void test1(){
    FILE *fp=fopen("temp.txt","a+");;
    string msg="hello world";
    fwrite(msg.c_str(),1,msg.size(),fp);
    fclose(fp);
}

//自定义一个删除器
struct FileDeleter{
    //operator()重载函数调用运算符，参数是需要回收的资源
    void operator()(FILE *fp){
        if(fp){
            fclose(fp);
            cout<<"文件资源已释放"<<endl;
        }
    }
};

//unique_ptr
void test2(){
    unique_ptr<FILE,FileDeleter>up{fopen("temp.txt","a+"),FileDeleter()};
    string msg="hello world";
    fwrite(msg.c_str(),1,msg.size(),up.get());
    // fclose(fp); // 不需要手动关闭，unique_ptr会自动调用删除器

}

int main(int argc,char *argv[])
{
    // test1();    
    test2();
    return 0;
}

