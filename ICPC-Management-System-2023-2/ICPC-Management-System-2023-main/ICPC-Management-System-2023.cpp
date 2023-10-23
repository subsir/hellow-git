// 内含hash重载，需要记忆请查阅

#include <iostream>
#include <set>
#include <queue>
#include <cstring>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>

int duration, problem_count, team_count;
int status; // 记录封榜滚榜，0表示未开始封榜，1表示封榜，-1表示滚榜
int problem_complement[10010][27]; // 记录问题完成情况，第0位记录通过题目总数，1~27位记录具体的题目通过情况，其中-3表示3次未过，4表示第4次ac，初始为0
int freeze_complement[10010][27]; // 记录封榜期间提交情况 [team_num][problem_num]，第0位记录冻结题目总数
int freeze_accept[10010][27][2]; // 在冻结状态通过了题目，[team_num][problem_num][]，第0位是ac时提交的次数，第1位是ac时的时间
int penalty_time[10010][27]; // 若罚时为400，记为-400，方便set升序排序，第0位记为总罚时，其余位记录ac时的时间，同理为负数
std::unordered_set <std::string> team_name; // 用于查重
std::unordered_map <std::string, int> team_num; // 团队名称->团队编号，为problem_complement服务
std::unordered_map <std::string, int> rank_map; // 名字->排名，用于Query_Ranking
std::string map_rank[10010]; // 排名->名字，为rank_map的逆映射

bool compare(const std::string  & name1, const std::string & name2) { // 比较name1和name2先后顺序
  int num_self = team_num[name1];
  int num_other = team_num[name2];
  if (problem_complement[num_self][0] != problem_complement[num_other][0]) {
    return problem_complement[num_self][0] > problem_complement[num_other][0];
  }
  std::sort(penalty_time[num_self], penalty_time[num_self] + problem_complement[num_self][0] + 1);
  std::sort(penalty_time[num_other], penalty_time[num_other] + problem_complement[num_other][0] + 1);
  for (int i = 0; i < problem_complement[num_self][0] + 1; i++) { // 从总罚时到小题罚时的遍历
    if (penalty_time[num_self][i] != penalty_time[num_other][i]) {
      return penalty_time[num_self][i] > penalty_time[num_other][i]; // 罚时记成负数，方便sort直接排序
    }
  }
  return name1 < name2;
}

struct Rank_info { // 排名的information
  std::string name_of_team;
  bool operator<(const Rank_info &r) const {
    return compare(name_of_team, r.name_of_team);
  }
};

struct Submit_Query_ALL_INFO { // 服务于QUERY_SUBMISSION的全信息查找
  std::string team_name;
  char problem_name;
  std::string status;
  bool operator<(const Submit_Query_ALL_INFO &r) const {
    if (team_name != r.team_name) {
      return team_name < r.team_name;
    }
    if (problem_name != r.problem_name) {
      return problem_name < r.problem_name;
    }
    return status < r.status;
  }  
  bool operator==(const Submit_Query_ALL_INFO &r) const { // 必要的==运算符重载
    return team_name == r.team_name && problem_name == r.problem_name && status == r.status;
  }
};

struct Submit_Query_ALL_INFO_hash { // hash重载
    size_t operator()(const struct Submit_Query_ALL_INFO & _r) const {
    std::string tmp = _r.team_name + _r.problem_name + _r.status;
    return std::hash<std::string>()(tmp);
    }
};

struct Submit_Query_STATUS_ONLY { // 服务于QUERY_SUBMISSION的查找指定status
  std::string team_name;
  std::string status;
  bool operator<(const Submit_Query_STATUS_ONLY &r) const {
    if (team_name != r.team_name) {
      return team_name < r.team_name;
    }
    return status < r.status;
  }
  bool operator==(const Submit_Query_STATUS_ONLY &r) const { // 必要的==运算符重载
    return team_name == r.team_name && status == r.status;
  }
};

struct Submit_Query_STATUS_ONLY_hash { // hash重载
    size_t operator()(const struct Submit_Query_STATUS_ONLY & _r) const {
    std::string tmp = _r.team_name + _r.status;
    return std::hash<std::string>()(tmp);
    }
};

struct Submit_Query_STATUS_ONLY_COMPLEMENT { // status_only的信息在所有信息集合内的补集
  char problem_name;
  int time;
};

struct Submit_Query_PROBLEM_ONLY { // 服务于QUERY_SUBMISSION的查找指定problem
  std::string team_name;
  char problem_name;
  bool operator<(const Submit_Query_PROBLEM_ONLY &r) const {
    if (team_name != r.team_name) {
      return team_name < r.team_name;
    }
    return problem_name < r.problem_name;
  }
  bool operator==(const Submit_Query_PROBLEM_ONLY &r) const { // 必要的==运算符重载
    return team_name == r.team_name && problem_name == r.problem_name;
  }
};
 
struct Submit_Query_PROBLEM_ONLY_hash { // hash重载
    size_t operator()(const struct Submit_Query_PROBLEM_ONLY & _r) const {
    std::string tmp = _r.team_name + _r.problem_name;
    return std::hash<std::string>()(tmp);
    }
};
struct Submit_Query_PROBLEM_ONLY_COMPLEMENT { // problem_only的信息在所有信息集合内的补集
  std::string status;
  int time;
};

struct Submit_Query_TEAMNAME_ONLY_COMPLEMENT { // teamname_only的信息在所有信息集合内的补集
  char problem_name;
  std::string status;
  int time; 
};

std::set <Rank_info> rank_set; // 用于维护榜单
std::priority_queue <Rank_info> freeze_submit; // 冻结时提交的队伍名称，大根堆
std::unordered_map <Submit_Query_ALL_INFO, int, Submit_Query_ALL_INFO_hash> submission_load_all_info; // 保存提交信息
std::unordered_map <Submit_Query_STATUS_ONLY, Submit_Query_STATUS_ONLY_COMPLEMENT, Submit_Query_STATUS_ONLY_hash> submission_load_status_only; // 保存提交信息，只关心status
std::unordered_map <Submit_Query_PROBLEM_ONLY, Submit_Query_PROBLEM_ONLY_COMPLEMENT, Submit_Query_PROBLEM_ONLY_hash> submission_load_problem_only; // 保存提交信息，只关心problem
std::unordered_map <std::string, Submit_Query_TEAMNAME_ONLY_COMPLEMENT> submission_load_teamname_only; // 保存提交信息，只关心teamname

void Print_list() {
  for (int j = 1; j <= team_count; j++) {
    std::string name_of_team = map_rank[j];
    int num_of_team = team_num[name_of_team];
    std::cout << name_of_team << ' ' << j << ' ' << problem_complement[num_of_team][0] << ' ' << - penalty_time[num_of_team][0] << ' ';
    for (int i = 1; i <= problem_count; i++) {
      if (problem_complement[num_of_team][i] > 0) { // 已通过
        if (problem_complement[num_of_team][i] == 1) { // 1次就过
          std::cout << '+' << ' ';
        } else {
          std::cout << '+' << problem_complement[num_of_team][i] - 1 << ' ';
        }
      } else if (freeze_complement[num_of_team][i] == 0) { // 未通过未冻结
        if (problem_complement[num_of_team][i] == 0) { // 未提交
          std::cout << '.' << ' ';
        } else {
          std::cout << problem_complement[num_of_team][i] << ' ';
        }
      } else { // 已冻结
        std::cout << problem_complement[num_of_team][i] << '/' << abs(freeze_complement[num_of_team][i]) << ' ';
      }
    }
    std::cout << '\n';
  }
}

int main() {
  std::ios::sync_with_stdio(false); // 关闭C++的标准输入输出流与C标准库输入输出流之间的同步
  std::cin.tie(nullptr); // 将标准输入流与标准输出流解绑
  std::cout.tie(nullptr); // 将标准输出流与标准输入流解绑
  std::string temp_team_name, temp_order;
 while (true) { // ADD
    std::cin >> temp_order;
    if (temp_order == "START") {
      std::cin >> temp_order >> duration >> temp_order >> problem_count;
      auto iter = rank_set.begin();
      for (int j = 1; j <= team_count; j++) { // map_rank、rank_map初始化
        rank_map[iter->name_of_team] = j;
        map_rank[j] = iter->name_of_team;
        iter++;
      }
      std::cout << "[Info]Competition starts.\n";
      break;
    } else if (temp_order == "ADDTEAM") {
      std::cin >> temp_team_name;
      if (team_name.insert(temp_team_name).second) {
        std::cout << "[Info]Add successfully.\n";
        team_num[temp_team_name] = team_count++;
        rank_set.insert({Rank_info{temp_team_name}});
      } else {
        std::cout << "[Error]Add failed: duplicated team name.\n";
      }
    }
  }
  while (true) {
    std::cin >> temp_order;
    if (temp_order == "ADDTEAM") {
      std::cout << "[Error]Add failed: competition has started.\n";
      std::cin >> temp_order;
    } else if (temp_order == "START") {
      std::cout << "[Error]Start failed: competition has started.\n";
      std::string bin;
      getline(std::cin, bin);
    } else if (temp_order == "SUBMIT") {
      int temp_time;
      char temp_problem;
      std::string temp_status;
      std::cin >> temp_problem >> temp_order >> temp_team_name >> temp_order >> temp_status >> temp_order >> temp_time;
      int num_of_team = team_num[temp_team_name];
      int num_of_problem = temp_problem - 'A' + 1;
      submission_load_all_info[{Submit_Query_ALL_INFO{temp_team_name, temp_problem, temp_status}}] = temp_time;
      submission_load_status_only[{Submit_Query_STATUS_ONLY{temp_team_name, temp_status}}] = {Submit_Query_STATUS_ONLY_COMPLEMENT{temp_problem, temp_time}};
      submission_load_problem_only[{Submit_Query_PROBLEM_ONLY{temp_team_name, temp_problem}}] = {Submit_Query_PROBLEM_ONLY_COMPLEMENT{temp_status, temp_time}};
      submission_load_teamname_only[temp_team_name] = {Submit_Query_TEAMNAME_ONLY_COMPLEMENT{temp_problem, temp_status, temp_time}};
      if (status == 0) { // 未封榜
        if (problem_complement[num_of_team][num_of_problem] <= 0) { // 未通过
          problem_complement[num_of_team][num_of_problem]--; 
        }
        if (temp_status == "Accepted" and problem_complement[num_of_team][num_of_problem] <= 0) {
          rank_set.erase({Rank_info{temp_team_name}});
          problem_complement[num_of_team][num_of_problem] *= -1; // 已通过记为正数
          problem_complement[num_of_team][0]++; // 通过总数+1
          int each_penalty = - (20 * (problem_complement[num_of_team][num_of_problem] - 1) + temp_time);
          penalty_time[num_of_team][0] += each_penalty;
          penalty_time[num_of_team][problem_complement[num_of_team][0]] = - temp_time;
          rank_set.insert({Rank_info{temp_team_name}});
        }
      } else if (problem_complement[num_of_team][num_of_problem] <= 0) { // 封榜，只冻结未通过题目
        if (freeze_complement[num_of_team][0] == 0) {
          freeze_submit.push({Rank_info{temp_team_name}}); // 封榜到解榜期间排名不变
        }
        if (freeze_complement[num_of_team][num_of_problem] == 0) { // 新冻结的题目
          freeze_complement[num_of_team][0]++;
        }
        if (freeze_complement[num_of_team][num_of_problem] <= 0) { // 冻结期间未通过
          freeze_complement[num_of_team][num_of_problem]--;
        } else {
          freeze_complement[num_of_team][num_of_problem]++;
        }
        if (temp_status == "Accepted" and freeze_complement[num_of_team][num_of_problem] <= 0) { // 冻结后第一次提交通过
          freeze_complement[num_of_team][num_of_problem] *= -1;
          freeze_accept[num_of_team][num_of_problem][0] = freeze_complement[num_of_team][num_of_problem];
          freeze_accept[num_of_team][num_of_problem][1] = temp_time;
        }
      }
    } else if (temp_order == "FLUSH") {
      auto iter = rank_set.begin();
      for (int j = 1; j <= team_count; j++) {
        rank_map[iter->name_of_team] = j;
        map_rank[j] = iter->name_of_team;
        iter++;
      }
      std::cout << "[Info]Flush scoreboard.\n";
    } else if (temp_order == "FREEZE") {
      if (status == 1) {
        std::cout << "[Error]Freeze failed: scoreboard has been frozen.\n";
      } else {
        status = 1;
        std::cout << "[Info]Freeze scoreboard.\n";
      }
    } else if (temp_order == "SCROLL") {
      if (status != 1) {
        std::cout << "[Error]Scroll failed: scoreboard has not been frozen.\n";
      } else {
        status = -1;
        std::cout << "[Info]Scroll scoreboard.\n";
        auto iter0 = rank_set.begin(); // 先FLUSH
        for (int j = 1; j <= team_count; j++) {
          rank_map[iter0->name_of_team] = j;
          map_rank[j] = iter0->name_of_team;
          iter0++;
        }
        Print_list();
        while (freeze_submit.empty() != true) {
          auto iter = freeze_submit.top();
          freeze_submit.pop();
          std::string name_of_team = iter.name_of_team;
          int num_of_team = team_num[name_of_team];
          int j = 1; // 寻找冻结题目编号
          for (; j <= problem_count and freeze_complement[num_of_team][j] == 0; j++);
          if (freeze_complement[num_of_team][j] != 0) { // 存在冻结题目 
            if (freeze_accept[num_of_team][j][0] != 0) { // 冻结期间通过
              auto iter2 = rank_set.find({Rank_info{name_of_team}});
              problem_complement[num_of_team][j] -= freeze_accept[num_of_team][j][0];
              problem_complement[num_of_team][j] *= -1; // 已通过记为正数
              problem_complement[num_of_team][0]++; // 通过总数+1
              int each_penalty = - (20 * (problem_complement[num_of_team][j] - 1) + freeze_accept[num_of_team][j][1]);
              penalty_time[num_of_team][0] += each_penalty;
              penalty_time[num_of_team][problem_complement[num_of_team][0]] = -freeze_accept[num_of_team][j][1]; 
              freeze_accept[num_of_team][j][0] = 0;
              freeze_accept[num_of_team][j][1] = 0;
              freeze_complement[num_of_team][0]--;
              freeze_complement[num_of_team][j] = 0;
              if (iter2 != rank_set.begin()) { // 第一名也不可能上升
                iter2--;
                std::string lower_name = iter2->name_of_team;
                if (compare(name_of_team, lower_name)) { // 排名会发生变化
                  iter2++;
                  rank_set.erase(iter2);
                  rank_set.insert({Rank_info{name_of_team}});
                  iter2++;
                  std::string team_name2 = iter2->name_of_team;
                  std::cout << name_of_team << ' ' << team_name2 << ' ' << problem_complement[num_of_team][0] << ' ' << - penalty_time[num_of_team][0] << '\n';
                }
              }
            } else {
              problem_complement[num_of_team][j] += freeze_complement[num_of_team][j];
              freeze_complement[num_of_team][j] = 0;
              freeze_complement[num_of_team][0]--;
            }
            if (freeze_complement[num_of_team][0] > 0) { // 未完全解冻
              freeze_submit.push({Rank_info{name_of_team}});
            }
          } 
        }      
        auto iter = rank_set.begin(); // 先FLUSH
        for (int j = 1; j <= team_count; j++) {
          rank_map[iter->name_of_team] = j;
          map_rank[j] = iter->name_of_team;
          iter++;
        }
        Print_list();
        status = 0;
      }
    } else if (temp_order == "QUERY_RANKING") {
      std::cin >> temp_team_name;
      if (team_name.count(temp_team_name) == 0) {
        std::cout << "[Error]Query ranking failed: cannot find the team.\n";
      } else {
        std::cout << "[Info]Complete query ranking.\n";
        if (status == 1) { // 封榜
          std::cout << "[Warning]Scoreboard is frozen. The ranking may be inaccurate until it were scrolled.\n";
        }
        std::cout << temp_team_name << " NOW AT RANKING " << rank_map[temp_team_name] << '\n';
      }
    } else if (temp_order == "QUERY_SUBMISSION") {
      std::cin >> temp_team_name >> temp_order >> temp_order;
      std::string temp_problem = temp_order.substr(8);
      std::cin >> temp_order >> temp_order;
      std::string temp_status = temp_order.substr(7);
      if (team_name.count(temp_team_name) == 0) { // 找不到队伍
        std::cout << "[Error]Query submission failed: cannot find the team.\n";
      } else {
        std::cout << "[Info]Complete query submission.\n";
        if (temp_problem == "ALL") {
          if (temp_status == "ALL") { // 只关心teamname
            auto iter = submission_load_teamname_only.find(temp_team_name);
            if (iter != submission_load_teamname_only.end()) {
              std::cout << temp_team_name << ' ' << iter->second.problem_name << ' ' << iter->second.status << ' ' << iter->second.time << '\n';
            } else {
              std::cout << "Cannot find any submission.\n";
            }
          } else { // 只关心status和teamname
            auto iter = submission_load_status_only.find({Submit_Query_STATUS_ONLY{temp_team_name, temp_status}});
            if (iter != submission_load_status_only.end()) {
              std::cout << temp_team_name << ' ' << iter->second.problem_name << ' ' << temp_status << ' ' << iter->second.time << '\n';
            } else {
              std::cout << "Cannot find any submission.\n";
            }
          }
        } else {
          char temp_problem_char = temp_problem[0];
          if (temp_status == "ALL") { // 只关心problem和teamname
            auto iter = submission_load_problem_only.find({Submit_Query_PROBLEM_ONLY{temp_team_name, temp_problem_char}});
            if (iter != submission_load_problem_only.end()) {
              std::cout << temp_team_name << ' ' << temp_problem_char << ' ' << iter->second.status << ' ' << iter->second.time << '\n';
            } else {
              std::cout << "Cannot find any submission.\n";
            }
          } else { // 全条件查找
            auto iter = submission_load_all_info.find({Submit_Query_ALL_INFO{temp_team_name, temp_problem_char, temp_status}});
            if (iter != submission_load_all_info.end()) { 
              std::cout << temp_team_name << ' ' << temp_problem_char << ' ' << temp_status << ' ' << iter->second << '\n';
            } else {
              std::cout << "Cannot find any submission.\n";
            }
          }
        }
      }
    } else if (temp_order == "END") {
      std::cout << "[Info]Competition ends.\n";
      break;
    }
  }
}