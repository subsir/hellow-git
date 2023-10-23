#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdlib>
using namespace std;

int n;
int l, r;
int a[100];
int b[65];
int factor[100], factor_num;
int lower_temp[100];

void divide(int x) {
  for (int i = 1; i * i <= x; i++) {
    if (x % i == 0) {
      factor[factor_num++] = i;
      factor[factor_num++] = x / i;
    }
  }
}

void trial(int x, int rest_len, int rest_num, int temp) {
  if (rest_len == 0) {
    trial(x, x, rest_num - 1, a[n - 1]);
    return;
  }
  if (rest_num == 0) {
    cout << x << endl;
    exit(0);
  }
  while (temp > 0 and rest_len < temp) {
    temp = lower_temp[temp];
  }
  while (temp > 0 and b[temp] == 0) {
    temp = lower_temp[temp];
  }
  while (temp > 0) {
    if (b[temp]) {
      b[temp]--;
      trial(x, rest_len - temp, rest_num, temp);
      b[temp]++;
      if (rest_len == temp or rest_len == x) {
        return;
      }
    }
    temp = lower_temp[temp];
  }
}

int main() {
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    l = max(l, a[i]);
    r += a[i];
    b[a[i]]++;
  }
  sort(a, a + n);
  divide(r);
  sort(factor, factor + factor_num);
  lower_temp[a[0]] = 0;
  for(int i = 1; i < n; i++) {
    if (a[i] != a[i - 1]) {
      lower_temp[a[i]] = a[i - 1];
    }
  }
  for (int i = 0; i < factor_num; i++) {
    trial(factor[i], factor[i], r / factor[i], a[n - 1]);
  }
}
