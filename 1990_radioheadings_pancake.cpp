#include <iostream>
#include <cmath>
using namespace std;

int v, n;
int r, h;
int ans = (1 << 30);

void build(int rest_v, int s, int current_r, int current_h, int rest_layers) {
  if (rest_v == 0 and rest_layers == 0) {
    ans = min(ans, s);
    return;
  }
  if (rest_layers == 0) {
    return;
  }
  if (rest_v >= (current_r - 1) * (current_r - 1) * (current_h - 1) * rest_layers) {
    return;
  }
  for (int i = current_r - 1; i >= rest_layers; i--) {
    for (int j = current_h - 1; j >= rest_layers; j--) {
      if (rest_v >= i * i * j and s + 2 * i * j <= ans) {
        build(rest_v - i * i * j, s + 2 * i * j, i, j, rest_layers - 1);
      }
    }
  }
}

int main() {
  cin >> v >> n;
  r = (int) (sqrt(v));
  h = v;
  for (int i = r; i > n - 1; i--) {
    for (int j = h; j > n - 1; j--) {
      if (v >= i * i * j) {
        build(v - i * i * j, 2 * i * j + i * i, i, j, n - 1);
      }
    }
  }
  cout << ans % (1 << 30) << endl;
}
