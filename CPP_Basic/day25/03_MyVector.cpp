#include <iostream>
#include <memory>
#include <algorithm>
using namespace std;

template <typename T>
class MyVector
{
public:
    MyVector();
    ~MyVector();

    void push_back(const T&);
    void pop_back();
    int size() const;
    int capacity() const;

private:
    void reallocate();

    static std::allocator<T> m_alloc;

    T* m_start;
    T* m_finish;
    T* m_end_of_storage;
};

template<typename T>
std::allocator<T> MyVector<T>::m_alloc; //调用allocator的默认构造函数初始化

template<typename T>
void MyVector<T>::reallocate()
{
    int oldCapacity=capacity();
    int oldSize=size();
    int newCapacity=oldCapacity>0?oldCapacity*2:1;
    //申请空间 allocate()
    T *temp=m_alloc.allocate(newCapacity);
    //数据迁移
    //使用算法库中的uninitialized_copy()函数
    std::uninitialized_copy(m_start,m_finish,temp);
    //销毁所有元素
    while(m_start!=m_finish){
        m_alloc.destroy(--m_finish);
    }
    //释放所有空间
    m_alloc.deallocate(m_start,oldCapacity);
    //更新指针
    m_start=temp;
    m_finish=m_start+oldSize;
    m_end_of_storage=m_start+newCapacity;
}

//末尾添加元素
template<typename T>
void MyVector<T>::push_back(const T& value)
{
    //判断是否需要扩容
    if(size()>=capacity())
    {
        reallocate();
    }
    m_alloc.construct(m_finish,value);
    ++m_finish;
}

//删除末尾元素
template<typename T>
void MyVector<T>::pop_back()
{
    if(size())
    {   //只销毁末尾元素 不用释放空间
        m_alloc.destroy(--m_finish);
    }
}

//构造函数
template<typename T>
MyVector<T>::MyVector()
:m_start(nullptr)
,m_finish(nullptr)
,m_end_of_storage(nullptr)
{}

//析构函数
template<typename T>
MyVector<T>::~MyVector()
{
    //判断确实是有效地址
    if(m_start){
        //销毁所有元素
        while(m_start!=m_finish){
            m_alloc.destroy(--m_finish);
        }
        //释放所有空间
        m_alloc.deallocate(m_start,capacity());
    }
}

//获取容器大小
template<typename T>
int MyVector<T>::size() const{
    return m_finish-m_start;
}

//获取容器容量
template<typename T>
int MyVector<T>::capacity() const{
    return m_end_of_storage-m_start;
}

void test(){
    MyVector<int> vec;
    vec.push_back(1);
    cout<<"size:"<<vec.size()<<endl;
    cout<<"capacity:"<<vec.capacity()<<endl;
    cout<<"------------"<<endl;
    vec.push_back(2);
    cout<<"size:"<<vec.size()<<endl;
    cout<<"capacity:"<<vec.capacity()<<endl;
    cout<<"------------"<<endl;
    vec.push_back(3);
    cout<<"size:"<<vec.size()<<endl;
    cout<<"capacity:"<<vec.capacity()<<endl;
    cout<<"------------"<<endl;
    vec.push_back(4);
    cout<<"size:"<<vec.size()<<endl;
    cout<<"capacity:"<<vec.capacity()<<endl;
    cout<<"------------"<<endl;
    vec.push_back(5);
    cout<<"size:"<<vec.size()<<endl;
    cout<<"capacity:"<<vec.capacity()<<endl;
    cout<<"------------"<<endl;
    vec.push_back(6);
    cout<<"size:"<<vec.size()<<endl;
    cout<<"capacity:"<<vec.capacity()<<endl;
    cout<<"------------"<<endl;
    vec.pop_back();
    cout<<"size:"<<vec.size()<<endl;
    cout<<"capacity:"<<vec.capacity()<<endl;
}

int main(int argc,char *argv[])
{
    test();
    return 0;
}

