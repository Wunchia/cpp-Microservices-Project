#include <iostream>
#include "tinyxml2.h"
using std::cin;
using std::cout;
using std::endl;
using namespace tinyxml2;
int main(int argc,char *argv[])
{
    //加载XML文件
    XMLDocument doc;
    XMLError eResult=doc.LoadFile("example.xml");
    
    //错误检查
    if(eResult!=XML_SUCCESS){
        cout<<"Failed to load file:"<<doc.ErrorStr()<<endl;
        return -1;
    }

    //获取根元素
    XMLElement* root=doc.RootElement();
    if(root==nullptr){return -1;}

    //获取第一个元素 "Element"
    XMLElement *element=root->FirstChildElement("Element");
    if(element==nullptr){return -1;}

    //读取属性(Attribute)
    const char* attrValue=element->Attribute("name");
    if(attrValue){
        cout<<"Attribute 'name':"<<attrValue<<endl;
    }

    //读取文本内容(Text)
    XMLElement* content=element->FirstChildElement("Content");
    if(content){
        const char* text=content->GetText();
        if(text){
            cout<<"Text content: "<<text<<endl;
        }
    }
    return 0;
}

