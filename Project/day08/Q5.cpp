#include <iostream>
#include <string>
#include <vector>
#include <cctype>               // isdigit
#include <nlohmann/json.hpp>
#include <tinyxml2.h>           // 需要下载 tinyxml2

using json = nlohmann::json;
using namespace std;
using namespace tinyxml2;

// 去除首尾空白
string trim(const string& s) {
    size_t start = s.find_first_not_of(" \t\n\r");
    if (start == string::npos) return "";
    size_t end = s.find_last_not_of(" \t\n\r");
    return s.substr(start, end - start + 1);
}

// 文本转数字（智能判断 int / double / string）
json parse_value(const string& text) {
    string t = trim(text);
    if (t.empty()) return t;

    // 带小数点 → double
    if (t.find('.') != string::npos) {
        return stod(t);
    }

    // 全数字 → int
    bool all_digit = true;
    for (char c : t) {
        if (!isdigit(static_cast<unsigned char>(c))) {
            all_digit = false;
            break;
        }
    }
    if (all_digit) return stoi(t);

    // 其他 → string
    return t;
}

// XMLElement → JSON
json element_to_json(XMLElement* elem) {
    json result;

    // 1. 属性 → "@" 前缀
    for (const XMLAttribute* attr = elem->FirstAttribute(); attr; attr = attr->Next()) {
        result["@" + string(attr->Name())] = attr->Value();
    }

    // 2. 遍历子元素
    for (XMLElement* child = elem->FirstChildElement(); child; child = child->NextSiblingElement()) {
        string tag = child->Name();
        bool has_attr = child->FirstAttribute() != nullptr;

        if (has_attr) {
            // 有属性 → 嵌套对象 {"@attr":..., "value":...}
            json sub = element_to_json(child);
            const char* text = child->GetText();
            if (text) sub["value"] = parse_value(text);
            result[tag] = sub;
        } else {
            // 无属性 → 直接存值
            const char* text = child->GetText();
            result[tag] = text ? parse_value(text) : "";
        }
    }

    return result;
}

int main() {
    string raw = R"(<library>
  <book id="B001">
    <title>三体</title>
    <author>刘慈欣</author>
    <year>2008</year>
    <price currency="CNY">68.00</price>
  </book>
  <book id="B002">
    <title>百年孤独</title>
    <author>加西亚·马尔克斯</author>
    <year>2011</year>
    <price currency="CNY">55.00</price>
  </book>
</library>)";

    // 解析 XML
    XMLDocument doc;
    doc.Parse(raw.c_str());

    // 遍历所有 <book>
    json result = json::array();
    XMLElement* library = doc.FirstChildElement("library");
    for (XMLElement* book = library->FirstChildElement("book");
         book != nullptr;
         book = book->NextSiblingElement("book")) {
        result.push_back(element_to_json(book));
    }

    cout << result.dump(2) << endl;

    return 0;
}

