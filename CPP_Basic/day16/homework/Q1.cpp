#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <regex>
#include "tinyxml2.h" 

using namespace std;
using namespace tinyxml2;

// RSS 条目结构体
struct RssItem {
    string title;
    string link;
    string description;
    string content;
};

// RSS 解析器类
class RssReader {
public:
    RssReader() = default;
    
    // 解析指定的 RSS 文件（这里为了灵活性，给接口增加了文件名参数）
    void parseRss(const string& xmlPath);
    
    // 输出到指定文件
    void dump(const string& filename);

private:
    // 辅助函数：使用正则表达式去除 HTML 标签
    string cleanHtml(const string& text);

    vector<RssItem> _rss;
};

// 使用正则表达式去除 HTML 标签
string RssReader::cleanHtml(const string& text) {
    // 匹配 <...> 形式的 HTML 标签
    regex htmlRegex("<[^>]*>");
    // 将匹配到的标签替换为空字符串
    return regex_replace(text, htmlRegex, "");
}

// 解析 RSS 文件
void RssReader::parseRss(const string& xmlPath) {
    XMLDocument doc;
    // 加载 XML 文件
    XMLError error = doc.LoadFile(xmlPath.c_str());
    if (error != XML_SUCCESS) {
        cerr << "Error: Unable to load XML file. Error ID: " << error << endl;
        return;
    }

    // 获取根节点 <rss>
    XMLElement* rssRoot = doc.FirstChildElement("rss");
    if (!rssRoot) {
        cerr << "Error: Invalid RSS file, missing <rss> root." << endl;
        return;
    }

    // 获取 <channel> 节点
    XMLElement* channel = rssRoot->FirstChildElement("channel");
    if (!channel) {
        cerr << "Error: Missing <channel> element." << endl;
        return;
    }

    // 遍历所有的 <item> 节点
    XMLElement* item = channel->FirstChildElement("item");
    while (item) {
        RssItem rssItem;

        // 1. 解析 title
        XMLElement* titleElement = item->FirstChildElement("title");
        if (titleElement && titleElement->GetText()) {
            rssItem.title = titleElement->GetText();
        }

        // 2. 解析 link
        XMLElement* linkElement = item->FirstChildElement("link");
        if (linkElement && linkElement->GetText()) {
            rssItem.link = linkElement->GetText();
        }

        // 3. 解析 description 并清洗 HTML
        XMLElement* descElement = item->FirstChildElement("description");
        if (descElement && descElement->GetText()) {
            rssItem.description = cleanHtml(descElement->GetText());
        }

        // 4. 解析 content:encoded 并清洗 HTML
        XMLElement* contentElement = item->FirstChildElement("content:encoded");
        if (contentElement && contentElement->GetText()) {
            rssItem.content = cleanHtml(contentElement->GetText());
        } else if (rssItem.description.size() > 0) {
            // 如果没有 content:encoded，可以用 description 兜底
            rssItem.content = rssItem.description;
        }

        // 存入容器
        _rss.push_back(rssItem);

        // 移动到下一个 <item>
        item = item->NextSiblingElement("item");
    }

    cout << "Successfully parsed " << _rss.size() << " RSS items." << endl;
}

// 导出成网页库格式
void RssReader::dump(const string& filename) {
    ofstream ofs(filename);
    if (!ofs.is_open()) {
        cerr << "Error: Unable to open file " << filename << " for writing." << endl;
        return;
    }

    int docId = 1;
    for (const auto& item : _rss) {
        ofs << "<doc>\n"
            << "\t<docid>" << docId++ << "</docid>\n"
            << "\t<title>" << item.title << "</title>\n"
            << "\t<link>" << item.link << "</link>\n"
            << "\t<description>" << item.description << "</description>\n"
            << "\t<content>" << item.content << "</content>\n"
            << "</doc>\n";
    }

    ofs.close();
    cout << "Dumped to " << filename << " successfully." << endl;
}

int main() {
    RssReader reader;
    
    string inputXml = "feed.xml"; 
    string outputTxt = "pagelib.txt";

    cout << "Starting to parse RSS..." << endl;
    reader.parseRss(inputXml);
    
    cout << "Starting to dump to webpage library..." << endl;
    reader.dump(outputTxt);

    return 0;
}