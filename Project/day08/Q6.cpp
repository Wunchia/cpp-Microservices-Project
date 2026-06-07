#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include <tinyxml2.h>

using json = nlohmann::json;
using namespace std;
using namespace tinyxml2;

// 递归：JSON → XMLElement
void json_to_element(XMLDocument& doc, XMLElement* parent, const string& tag, const json& j) {
    if (j.is_object()) {
        XMLElement* elem = doc.NewElement(tag.c_str());

        for (auto& [key, val] : j.items()) {
            if (key[0] == '@') {
                // "@attr" → XML 属性（去掉 @）
                string attr_name = key.substr(1);
                if (val.is_number_integer())
                    elem->SetAttribute(attr_name.c_str(), val.get<int>());
                else if (val.is_number_float())
                    elem->SetAttribute(attr_name.c_str(), val.get<double>());
                else
                    elem->SetAttribute(attr_name.c_str(), val.get<string>().c_str());
            } else if (key == "value") {
                // "value" → 文本内容
                string text;
                if (val.is_number_integer())
                    text = to_string(val.get<int>());
                else if (val.is_number_float())
                    text = to_string(val.get<double>());
                else
                    text = val.get<string>();
                elem->SetText(text.c_str());
            } else if (val.is_object()) {
                // 嵌套对象 → 递归
                json_to_element(doc, elem, key, val);
            } else if (val.is_array()) {
                // 数组 → 逐个递归
                for (auto& item : val)
                    json_to_element(doc, elem, key, item);
            } else {
                // 普通值 → 子元素
                XMLElement* child = doc.NewElement(key.c_str());
                string text;
                if (val.is_number_integer())
                    text = to_string(val.get<int>());
                else if (val.is_number_float())
                    text = to_string(val.get<double>());
                else
                    text = val.get<string>();
                child->SetText(text.c_str());
                elem->InsertEndChild(child);
            }
        }

        parent->InsertEndChild(elem);
    }
}

int main() {
    string raw = R"([
      {"@id": "B001", "author": "刘慈欣", "price": {"@currency": "CNY", "value": 68.0}, "title": "三体", "year": 2008},
      {"@id": "B002", "author": "加西亚·马尔克斯", "price": {"@currency": "CNY", "value": 55.0}, "title": "百年孤独", "year": 2011}
    ])";

    // 解析 JSON
    json books = json::parse(raw);

    // 构建 XML
    XMLDocument doc;
    XMLElement* library = doc.NewElement("library");
    doc.InsertFirstChild(library);

    for (auto& book : books)
        json_to_element(doc, library, "book", book);

    // 输出到控制台
    XMLPrinter printer;
    doc.Print(&printer);
    cout << printer.CStr() << endl;

    // 保存到文件
    doc.SaveFile("library.xml");
    cout << "已保存至 library.xml" << endl;

    return 0;
}

