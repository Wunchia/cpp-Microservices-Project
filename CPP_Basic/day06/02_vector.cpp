#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::vector;

/*
 * vector：顺序的数据容器，可以存储任意类型的数据
 * 可以是内置类型，也可以是自定义类型的
 * 
 * 特点：自动扩容  
 * vector类内有三个指针作为数据成员：
 * _M_start //首地址
 * _M_finish //最后一个元素（size）的下一个位置：size=finish-start
 * _M_end_of_storage //最大容量（capacity）的后一个位置：capacity=end_of_storagy-start
 * 
 * finish=end_of_storage时扩容：
 * 按1.5倍（MSVC）或2倍（gcc）大小扩容
 * 
 * 使用时需要指明要存储的数据的类型
 * vector<int> v1;
 * vector<Point> v2;
 *
 */

//vector容器的构建
void test1(){
    //无参构造函数 空容器
    vector <int> box1;

    //初始化列表方式构建容器
    vector<int> box2{1,2,3};

    //迭代器范围构建
    vector<int> box3{box2.begin()+1,box2.end()};

    //count个元素进行构建
    vector<int> box4(3,10);//要用小括号，以免重载至列表初始化
    //3个10进行创建

    //拷贝构造
    vector<int> box5{box2};
    vector<int> box6=box2;//和box5的构建等价
}

//vector常用操作
void test2(){
    vector<int> box;
    cout<<box.empty()<<endl;
    cout<<box.size()<<endl;
    cout<<box.capacity()<<endl;
    cout<<"---------->"<<endl;
    vector<int> box2{1,2,3};
    cout<<box2.empty()<<endl;
    cout<<box2.size()<<endl;
    cout<<box2.capacity()<<endl;
    cout<<"----------->"<<endl;
    box2.push_back(4);
    cout<<box2.empty()<<endl;
    cout<<box2.size()<<endl;
    cout<<box2.capacity()<<endl;
    cout<<"----------->"<<endl;
}

//vector遍历操作
void visitVector(const vector<int> &box){
    //增强for循环做遍历
    for(auto &element:box){
        cout<<element<<" ";
    }
    cout<<endl;
}

void test3(){
    vector<int>box{1,2,3,4,5};
    visitVector(box);
    box.push_back(6);//尾加
    box.push_back(7);
    visitVector(box);
    box.pop_back();//尾删
    visitVector(box);
    box.clear();//清除内容
    visitVector(box);
    cout<<"size:"<<box.size()<<endl;
    cout<<"capacity:"<<box.capacity()<<endl;
    cout<<"---------->"<<endl;
    box.push_back(1);
    box.shrink_to_fit();//缩减多余空间
    cout<<"size:"<<box.size()<<endl;
    cout<<"capacity:"<<box.capacity()<<endl;
    cout<<"----------->"<<endl;
    vector<int> box2;
    box2.reserve(5);//预留空间
    cout<<"size:"<<box2.size()<<endl;
    cout<<"capacity:"<<box2.capacity()<<endl;
}

//元素访问
void test4(){
    vector<int> box{1,2,3,4,5};
    //at(index)
    cout<<box.at(0)<<endl;
    //通过下标访问
    cout<<box.operator[](1)<<endl;//下面那种写法的本质即此
    cout<<box[2]<<endl;//等价于operator[]()
    cout<<box.front()<<endl;
    cout<<box.back()<<endl;
    cout<<"----------------->"<<endl;
    //通过迭代器访问
    // vector<int>::iterator it=box.begin();
    auto it=box.begin();
    cout<<*it<<endl;
    it++;
    cout<<*it<<endl;
}

int main(int argc,char *argv[])
{
    // test1();    
    // test2();
    // test3();
    test4();
    return 0;
}

