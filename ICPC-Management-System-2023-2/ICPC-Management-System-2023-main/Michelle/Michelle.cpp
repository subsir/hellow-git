#include <iostream>
#include <set>
#include <unordered_map>
#include <cstring>
#include <vector>

struct Rank_info { // 用来排序的信息
  int major_score; // 总分
  long long attach_score; // 每门课加权(*101)相加
  std::string name; // 姓名
  bool operator<(const Rank_info &rhs) const {
    if ((major_score / 9) != (rhs.major_score / 9)) {
      return (major_score / 9) > (rhs.major_score / 9);
    }
    if (attach_score != rhs.attach_score) {
      return attach_score > rhs.attach_score;
    }
    return name < rhs.name;
  }
};

struct All_info { // 完整信息
  std::string name;
  std::string gender;
  int clas;
  std::vector <int> score;
  int total_score;
  long long attach_score;
};

std::unordered_map <std::string, All_info> all_info; // 名字->所有信息的unordered_map
std::unordered_map <std::string, int> rank_map; // 名字->排名的unordered_map
std::set <Rank_info> rank_info; // 用于排名的信息
std::string map_rank[10010]; // 排名->名字的string数组，为rank_map的逆映射
long long base[9]; // 以101为基的101^0 101^1 ... 101^8
int n; // 学生人数n

int main() {
//  freopen("data/10.in", "r", stdin);
//  freopen("../../compare/self10.out", "w", stdout);
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::string temp_order, temp_name, temp_gender; // 用于输入
  int temp_clas, total_score = 0, temp_score, temp_code; // 加和总分
  long long attach_score = 0; // 计算小分
  long long temp_base = 1;
  for (int i = 0; i < 9; i++) {
    base[i] = temp_base;
    temp_base *= 101;
  }
  while (true) { // ADD
    std::vector <int> all_score;
    std::cin >> temp_order;
    if (temp_order == "START") {
      break;
    }
    std::cin >> temp_name >> temp_gender >> temp_clas;
    total_score = 0, attach_score = 0;
    for (int i = 0; i < 9; i++) {
      std::cin >> temp_score;
      total_score += temp_score;
      all_score.push_back(temp_score);
      attach_score *= 101;
      attach_score += temp_score;
    }
    auto iter = all_info.find(temp_name);
    if (iter == all_info.end()) {
      rank_info.insert({Rank_info{total_score, attach_score, temp_name}});
      all_info[temp_name] = {All_info{temp_name, temp_gender, temp_clas, all_score, total_score, attach_score}};
    } else {
      std::cout << "[Error]Add failed.\n";
    }
  }
  auto i = rank_info.begin(); // rank_map map_rank初始化
  for (int j = 1; i != rank_info.end(); j++) {
    rank_map[i->name] = j;
    map_rank[j] = i->name;
    i++; 
    n++;
  }
  while (true) {
    std::cin >> temp_order;
    if (temp_order == "END") {
      break;
    }
    if (temp_order == "UPDATE") {
      std::cin >> temp_name >> temp_code >> temp_score;
      auto iter = all_info.find(temp_name); // 所有成绩迭代器
      if (iter != all_info.end()) {
        auto iter2 = rank_info.find({Rank_info{iter->second.total_score, iter->second.attach_score, temp_name}});
        long long old_score = iter2->attach_score; // 原小分
        int erase_score = iter->second.score[temp_code]; // 需要更改的原成绩
        old_score -= base[8 - temp_code] * erase_score;
        old_score += base[8 - temp_code] * temp_score;
        int new_score = iter2->major_score - erase_score + temp_score; // 总分更新
        iter->second.score[temp_code] = temp_score;  // all_info更新
        iter->second.total_score = new_score; // all_info更新
        iter->second.attach_score = old_score; // all_info更新
        rank_info.erase(iter2);
        rank_info.insert({Rank_info{new_score, old_score, temp_name}}); // rank_info更新 
      } else {
        std::cout << "[Error]Update failed.\n";
      }
    } else {
      if (temp_order == "ADD") {
        std::cout << "[Error]Cannot add student now.\n";
        std::string bin;
        getline(std::cin, bin);
      } else {
        if (temp_order == "FLUSH") {
          auto i = rank_info.begin();
          for (int j = 1; i != rank_info.end(); j++) {
            rank_map[i->name] = j;
            map_rank[j] = i->name;
            i++; 
          }
        } else {
          if (temp_order == "PRINTLIST") {
            for (int j = 1; j <= n; j++) {
              auto i = all_info[map_rank[j]];
              std::cout << j << ' ' << map_rank[j] << ' ' << ((i.gender == "F") ? "female" : "male") << ' ' << i.clas << ' ' << i.total_score / 9 << '\n';
            }
          } else {
            if (temp_order == "QUERY") {
              std::cin >> temp_name;
              auto iter = rank_map.find(temp_name);
              if (iter != rank_map.end()) {
                std::cout << "STUDENT " << temp_name << " NOW AT RANKING " << iter->second << '\n'; 
              } else {
                std::cout << "[Error]Query failed.\n";
              }
            }
          }
        }
      }
    }
  }
  return 0;
}