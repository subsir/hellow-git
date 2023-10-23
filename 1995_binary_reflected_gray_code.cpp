#include <iostream>
#include <cmath>
using namespace std;

int n, b;
int times;
int a[66000][25], bb[25];

void print() {
    for (int i = 1; i <= times; i++) {
      for (int j = n - 1; j > -1; j--) {
        if (a[i][j] < 10) {
          cout << a[i][j];
        } else {
          cout << (char)(a[i][j] + 55);
        }
      }
      cout << '\n';
    }
}

int main() {
  cin >> n >> b; 
  times = pow(b, n);
  int i = 0;
  while (i++ < times)
  {
    bool jerk = true;
    for (int j = 0; j < n; j++) {
      if (bb[j] == 0) {
        bb[j] = 1;
      }
      if (i != 1) {
        if (jerk) {
          a[i][j] = a[i - 1][j] + bb[j];
          jerk = false;
        } else {
          a[i][j] = a[i - 1][j];
        }
        if (a[i][j] >= b or a[i][j] < 0) {
          a[i][j] = a[i - 1][j];
          bb[j] *= -1;
          jerk = true;
        }
      }
    }
  }
  print();
}