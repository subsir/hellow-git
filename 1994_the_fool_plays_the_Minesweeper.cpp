// string列存数据的问题： 1、非个位数 2、char 越界
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
int rows, columns;
int a[1010][1010], b[1010][1010], c[1010][1010];
int ans1, ans2;
queue <int> q;

string Sequence_of_the_surrounding_blocks(int row, int column) { // 用字符串方式返回方块周围的方块坐标，其中偶数位是row，奇数位是column
  string sequence = "";
  if (row > 0) { // 存在上方的方块
    sequence += (char)('0' - 1);
    sequence += (char)('0');
  }
  if (row < rows - 1) { // 存在下方的方块
    sequence += (char)('0' + 1);
    sequence += (char)('0');
  }
  if (column > 0) { // 存在左方的方块
    sequence += (char)('0');
    sequence += (char)('0' - 1);
  }
  if (column < columns - 1) { // 存在右方的方块
    sequence += (char)('0');
    sequence += (char)('0' + 1);
  }
  if (row > 0 and column > 0) { // 存在左上方的方块
    sequence += (char)('0' - 1);
    sequence += (char)('0' - 1);
  }
  if (row > 0 and column < columns - 1) { // 存在右上方的方块
    sequence += (char)('0' - 1);
    sequence += (char)('0' + 1);
  }
  if (row < rows - 1 and column > 0) { // 存在左下方的方块
    sequence += (char)('0' + 1);
    sequence += (char)('0' - 1);
  }
  if (row < rows - 1 and column < columns - 1) { // 存在右下方的方块
    sequence += (char)('0' + 1);
    sequence += (char)('0' + 1);
  }
  return sequence; // 返回方块队列
}

void Visit_unvisited_blocks(int row, int column) { // 访问未访问的方块
  string s = Sequence_of_the_surrounding_blocks(row, column);
  for (int i = 0; i < s.size(); i += 2) {
    int rr = s[i] - '0' + row;
    int cc = s[i + 1] - '0' + column;
    if (a[rr][cc] == 0 and c[rr][cc] == 0) {
      c[rr][cc] = 1;
      q.push(rr * columns + cc);
    }
  }
  if (q.empty()) {
    return;
  }
  int x = q.front();
  q.pop();
  Visit_unvisited_blocks(x / columns, x % columns);
}

int main() {
  int t;
  cin >> rows >> columns;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      scanf("%d", &t);
      if (t == 1) {
        string s = Sequence_of_the_surrounding_blocks(i, j);
        for (int k = 0; k < s.size(); k += 2) {
          int x = s[k] - '0' + i;
          int y = s[k + 1] - '0' + j;
          if (a[x][y] == 0) {
            a[x][y] = 1;
          }
        }
        a[i][j] = -1;
      }
    }
  }
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      if (a[i][j] == 0) {
        string s = Sequence_of_the_surrounding_blocks(i, j);
        for (int k = 0; k < s.size(); k += 2) {
          int x = s[k] - '0' + i;
          int y = s[k + 1] - '0' + j;
          b[x][y] = 1;
        }  
        if (c[i][j] == 0) {
          c[i][j] = 1;
          ans2++;
          Visit_unvisited_blocks(i, j);
        }
      }
    }
  }
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      if (b[i][j] == 0 and a[i][j] == 1) {
        ans1++;
      }
    }
  }
  cout << ans1 + ans2 << endl;
}