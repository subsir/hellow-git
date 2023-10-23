#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

int w, h;
int start[2][2], pos;
int step1[110][110], step2[110][110];
int ans;
string map[110][110];
string shift[] = {"10 ", "/0 ", "01 ", "0/ "};
queue <int> q;

void shift1(int x, int y) {
  for (auto i : shift) {
    int xx = i[0] - '0' + x;
    int yy = i[1] - '0' + y;
    if (map[x][y].find(i) == -1 and step1[xx][yy] == 0 and (xx != start[0][0] or xx != start[1][0] or yy != start[1][1] or yy != start[0][1])) {
      q.push(xx);
      q.push(yy);
      step1[xx][yy] = step1[x][y] + 1;
    }
  }
  if (q.empty()) {
    return;
  }
  int tx = q.front();
  q.pop();
  int ty = q.front();
  q.pop();
  shift1(tx, ty);
}

void shift2(int x, int y) {
  for (auto i : shift) {
    int xx = i[0] - '0' + x;
    int yy = i[1] - '0' + y;
    if (map[x][y].find(i) == -1 and step2[xx][yy] == 0 and (xx != start[0][0] or xx != start[1][0] or yy != start[1][1] or yy != start[0][1])) {
      q.push(xx);
      q.push(yy);
      step2[xx][yy] = step2[x][y] + 1;
    }
  }
  if (q.empty()) {
    return;
  }
  int tx = q.front();
  q.pop();
  int ty = q.front();
  q.pop();
  shift2(tx, ty);
}

int main() {
  char temp;
  cin >> w >> h;
  cin.ignore();
  for (int i = 1; i <= 2 * h + 1; i++) {
    for (int j = 1; j <= 2 * w + 2; j++) {
      temp = getchar();
      if (temp == '-') {
        map[i / 2][j / 2] += "10 ";
        map[(i + 1) / 2][j / 2]  += "/0 ";
      }
      if (temp == '|') {
        map[i / 2][j / 2] += "01 ";
        map[i / 2][(j + 1) / 2] += "0/ ";
      }
      if (i == 1 and temp == ' ') {
        start[pos][0] = 0;
        start[pos++][1] = j / 2;
        map[0][j / 2] += "/0 01 0/ ";
      }
      if (i == 2 * h + 1 and temp == ' ') {
        start[pos][0] = h + 1;
        start[pos++][1] = j / 2;
        map[h + 1][j / 2] += "10 0/ 01 ";
      }
      if (j == 1 and temp == ' ') {
        start[pos][0] = i / 2;
        start[pos++][1] = 0;
        map[i / 2][0] += "0/ 10 /0 ";
      }
      if (j == 2 * w + 1 and temp == ' ') {
        start[pos][0] = i / 2;
        start[pos++][1] = w + 1;
        map[i / 2][w + 1] += "01 10 /0 ";
      }
    }
  }
  shift1(start[0][0], start[0][1]);
  shift2(start[1][0], start[1][1]);
  for (int i = 1; i <= h; i++) {
    for (int j = 1; j <= w; j++) {
      ans = max(min(step1[i][j], step2[i][j]), ans);
    }
  }
  cout << ans << endl;
}