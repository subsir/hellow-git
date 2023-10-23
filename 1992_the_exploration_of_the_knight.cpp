#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

queue <int> q, q1;
int n, l, x1, yy1, x2, y2;
int shift[8][2] = {{1, 2}, {1, -2}, {2, 1}, {2, -1}, {-1, 2}, {-1, -2}, {-2, 1}, {-2, -1}}; 
int visited[310][310][2];

bool Inplace(int x, int y) {
  if (x >= 0 and x < l and y >= 0 and y < l) {
    return true;
  }
  return false;
}

void Map1(int x, int y, int step);
void Map(int x, int y, int step) {
  for (auto i : shift) {
    int nx = x + i[0];
    int ny = y + i[1];
    if (Inplace(nx, ny) and visited[nx][ny][0] != 1) {
      if (visited[nx][ny][0] == -1) {
        cout << visited[nx][ny][1] + step + 1 << endl;
        return;
      }
      q.push(nx * l + ny);
      visited[nx][ny][0] = 1;
      visited[nx][ny][1] = step + 1;
    }
  }
  int tx = q1.front() / l;
  int ty = q1.front() % l;
  q1.pop();
  Map1(tx, ty, visited[tx][ty][1]);
}

void Map1(int x, int y, int step) {
  for (auto i : shift) {
    int nx = x + i[0];
    int ny = y + i[1];
    if (Inplace(nx, ny) and visited[nx][ny][0] != -1) {
      if (visited[nx][ny][0] == 1) {
        cout << visited[nx][ny][1] + step + 1 << endl;
        return;
      }
      q1.push(nx * l + ny);
      visited[nx][ny][0] = -1;
      visited[nx][ny][1] = step + 1;
    }
  }
  int tx = q.front() / l;
  int ty = q.front() % l;
  q.pop();
  Map(tx, ty, visited[tx][ty][1]);
}
int main() {
  cin >> n;
  while (n--)
  {
    while (!q.empty()) {
      q.pop();
    }
    while (!q1.empty()) {
      q1.pop();
    }
    memset(visited, 0, sizeof(visited));
    cin >> l >> x1 >> yy1 >> x2 >> y2;
    if (x1 == x2 and yy1 == y2) {
      cout << 0 << endl;
      continue;
    }
    visited[x1][yy1][0] = 1;
    visited[x2][y2][0] = -1;
    q1.push(x2 * l + y2);
    Map(x1, yy1, 0);
  } 
}