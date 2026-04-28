#include <iostream>
#include <vector>

int g_global_var=10;//全局区
static int s_static_var=20;//全局/静态区

int main(int argc,char *argv[])
{
    int local_var=30;//栈区
    int *heap_ptr=new int(40);//堆区    
    const char*str="hello";//"hello"在常量区，str指针在栈区

    std::cout << "代码区 (main地址):   " << (void*)main << std::endl;
    std::cout << "常量区 (字符串地址): " << (void*)str << std::endl;
    std::cout << "全局区 (全局变量):   " << &g_global_var << std::endl;
    std::cout << "静态区 (静态变量):   " << &s_static_var << std::endl;
    std::cout << "堆区 (new分配):      " << heap_ptr << std::endl;
    std::cout << "栈区 (局部变量):     " << &local_var << std::endl;

    delete heap_ptr;
    return 0;
}

