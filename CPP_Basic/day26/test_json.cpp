#include <iostream>
#include <nlohmann/json.hpp> // 引入头文件

// 为了省事，可以起个别名
using json = nlohmann::json;

int main() {
    // 1. 极其丝滑的字面量创建 JSON 对象
    json j;
    j["name"] = "vincio";
    j["status"] = "perfect";
    j["skills"] = {"C++", "Linux", "Workflow", "wfrest"};
    j["env"] = {{"os", "Ubuntu"}, {"compiler", "g++"}};

    // 2. 序列化输出（4 代表缩进 4 个空格，美化打印）
    std::cout << j.dump(4) << std::endl;

    // 3. 反序列化测试（解析 JSON 字符串）
    std::string json_str = "{\"project\":\"network storage\",\"version\":2.0}";
    auto parsed_json = json::parse(json_str);
    
    std::cout << "\nParsed project: " << parsed_json["project"] << std::endl;

    return 0;
}