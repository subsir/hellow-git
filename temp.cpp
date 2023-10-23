#include <iostream>
using namespace std;

int n;

int cal(int x, int y) {
  int k = (1 << (n - 1));
  while (k >= 1 and (x >= k or y >= k)) {
    x %= k;
    y %= k;
    k = (k >> 1);
  }
  if (k == 0) {
    return 1;
  }
  return 0;
}

int main() {
  cin >> n;
  for (int i = 0; i < (1 << n); i++) {
    for (int j = 0; j < (1 << n); j++) {
      cout << cal(i, j) << ((j == (1 << n) - 1) ? '\n' : ' ');
    }
  }
}