#include <iostream>
#include <string>
#include <vector>
#include <numeric>              // accumulate
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;

struct Student {
    string name;
    int age;
    string gender;
    vector<int> scores;
};

void from_json(const json& j, Student& s) {
    j.at("name").get_to(s.name);
    j.at("age").get_to(s.age);
    j.at("gender").get_to(s.gender);
    j.at("scores").get_to(s.scores);
}

int main() {
    string raw = R"([
        {"name": "赵一", "age": 18, "gender": "男", "scores": [85, 92, 78]},
        {"name": "钱二", "age": 19, "gender": "女", "scores": [96, 88, 94]},
        {"name": "孙三", "age": 18, "gender": "男", "scores": [76, 81, 69]}
    ])";

    // 解析 JSON 数组 → vector<Student>
    vector<Student> students = json::parse(raw).get<vector<Student>>();

    // ── 1. 每个学生的平均分 ──
    cout << "1. 平均分:\n";
    for (auto& s : students) {
        double avg = accumulate(s.scores.begin(), s.scores.end(), 0.0) / s.scores.size();
        cout << "   " << s.name << ": " << avg << endl;
    }

    // ── 2. 所有 18 岁的学生 ──
    cout << "\n2. 18岁的学生:\n";
    for (auto& s : students) {
        if (s.age == 18)
            cout << "   " << s.name << endl;
    }

    // ── 3. 总分最高的学生 ──
    cout << "\n3. 总分最高的学生:\n";
    int max_total = 0;
    string top_name;

    for (auto& s : students) {
        int total = accumulate(s.scores.begin(), s.scores.end(), 0);
        if (total > max_total) {
            max_total = total;
            top_name = s.name;
        }
    }
    cout << "   " << top_name << " (总分: " << max_total << ")\n";

    return 0;
}
