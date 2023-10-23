// map 访问不存在元素会出意想不到的问题
// map.count 不存在的元素会创建一个元素
// auto iter = m.find(temp);
// iter->second.push_back(arg); 感谢Dark教授的卡常优化
// 感谢薛佳悦助教的count帮助
#include <iostream>
#include <cstring>
#include <map>                                                                                                                                                                                  
#include <vector>
#include <set>
using namespace std;

string temp;

struct Activity {
  int avg;
  int level;
  string name;
  bool operator < (const Activity &a) const {
    if (avg == a.avg and level == a.level) {
      return name < a.name; 
    }
    if (avg == a.avg) {
      return level < a.level;
    }
    return avg > a.avg;
  }
};

map <string, vector <int> > m;
set <Activity> s;

int main() {
  do {
    cin >> temp;
    if (temp == "map") {
      cin >> temp; // 读入操作
      if (temp == "size") {
        cout << m.size() << endl;
      } else {
        if (temp == "insert") {
          int num;
          cin >> temp >> num; // 读入name和num
          if (m.find(temp) == m.end()) {
            while (num--) {
              int arg;
              cin >> arg;
              m[temp].push_back(arg);
            }
          } else { // 加入元素已存在
            cout << "Error" << endl;
            string bin;
            getline(cin, bin);
          }
        } else {
          if (temp == "erase") {
            cin >> temp;
            if (m.erase(temp) == 0) { // 删除元素不存在
              cout << "Error" << endl;
              string bin;
              getline(cin, bin);
            }
          } else {
            if (temp == "count") { 
              cin >> temp;
              cout << m.count(temp) << endl;
            } else {
              if (temp == "traverse") { 
                for (auto i : m) {
                  cout << i.first; // 输出键
                  for (auto j : i.second) {
                    cout << " " << j; // 输出值
                  }
                  cout << endl;
                }
              } else {
                if (temp == "visitVec") {
                  int index;
                  cin >> temp >> index; // 输入name和index
                  auto iter = m.find(temp);
                  if (iter != m.end() and index < iter->second.size()) {
                    cout << iter->second[index] << endl;                    
                  } else { // 不存在这个vector或者vector访问越界
                    cout << "Error" << endl;
                    string bin;
                    getline(cin, bin);
                  }
                } else {
                  if (temp == "visit") {
                    cin >> temp;
                    auto iter = m.find(temp);
                    if (iter != m.end()) {
                      cout << iter->second.size() << ' '; // 先输出vector大小
                      for (int i = 0; i < iter->second.size(); i++) {
                        cout << iter->second[i]; // 再输出vector元素
                        if (i != iter->second.size() - 1) {
                          cout << " ";
                        } //在下面换行
                      }
                    } else { // 访问不存在vector
                      cout << "Error";
                      string bin;
                      getline(cin, bin);
                    }
                    cout << endl;
                  } else {
                    if (temp == "append") {
                      int element;
                      cin >> temp >> element; // 输入name和element
                      auto iter = m.find(temp);
                      if (iter != m.end()) { 
                        iter->second.push_back(element);   
                      } else { // 加入未创建vector
                        cout << "Error" << endl;
                        string bin;
                        getline(cin, bin);
                      }
                    } else { // 其他错误
                      cout << "Error" <<endl;
                      string bin;
                      getline(cin, bin);
                    }
                  }
                }
              }
            }
          }
        }
      }
    } else {
      if (temp == "set") {
        cin >> temp; // 读取操作
        if (temp == "size") {
          cout << s.size() << endl;
        } else {
          if (temp == "insert") {
            int arg, level;
            cin >> arg >> level >> temp; // 读入avg、level和name
            if (s.find(Activity {arg, level, temp}) != s.end()) {
              cout << "Error" << endl;

            } else {
              s.insert((Activity {arg, level, temp}));
            }
          } else {
            if (temp == "erase") {
              int arg, level;
              cin >> arg >> level >> temp;
              if (s.erase(Activity {arg, level, temp}) == 0) { // 擦除不存在元素
                cout << "Error" << endl;
                string bin;
                getline(cin, bin);
              }
            } else {
              if (temp == "count") { 
                int arg, level;
                cin >> arg >> level >> temp;
                cout << s.count(Activity {arg, level, temp}) << endl;
              } else {
                if (temp == "traverse") {
                  for (auto i : s) {
                    cout << i.avg << " " << i.level << " " << i.name << endl;
                  }
                } else { // 其他错误
                    cout << "Error" <<endl;
                    string bin;
                    getline(cin, bin);
                  }
              }
            }
          }
        }
      } else {
        if (temp != "end") {
          cout << "Error" <<endl;
          string bin;
          getline(cin, bin);
        }
      }
    } 
  } while (temp != "end");
}