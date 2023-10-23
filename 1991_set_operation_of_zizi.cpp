// (1uul << 64) 会直接溢出，需要(1uul << 63) + (1uul << 63)
#include <iostream>
#include <cstring>
using namespace std;
unsigned long long a[10010];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, num;
    string s;
    cin >> n >> m >> num;
    while (num--)
    {
        cin >> s;
        int x, y;
        if (s == "reset") {
            cin >> x;
            a[x] = 0;
        }
        else if (s == "full") {
            cin >> x;
            a[x] = (1ULL << (n - 1)) +(1ULL << (n - 1)) - 1;
        }
        else if (s == "query_exist") {
            cin >> x >> y;
            unsigned long long u = (1ULL << y);
            if (u & a[x]) {
                cout << "yes" << endl;
            } else {
                cout << "no" << endl;
            }
        }
        else if (s == "add") {
            cin >> x >> y;
            unsigned long long u = (1ULL << y);
            if ((u & a[x]) == 0) {
                a[x] += u;
            }
        }
        else if (s == "erase") {
            cin >> x >> y;
            unsigned long long u = (1ULL << y);
            if (u & a[x]) {
                a[x] -= u;
            }
        }
        else if (s == "query_adjacent") {
            cin >> x;
            bool flag = false;
            unsigned long long u = (a[x] >> 1);
            while (u)
            {
                if (u % 2) {
                    u >>= 1;
                    if (u % 2) {
                        flag = true;
                        break;
                    }
                    else {
                        u >>= 1;
                    }
                } else {
                    u >>= 1;
                }
            }
            if (flag) {
                cout << "adj" << endl;
            }
            else {
                cout << "not adj" << endl;
            }
        }
        else if (s == "intersect") {
            cin >> x >> y;
            a[x] &= a[y];
        }
        else if (s == "union") {
            cin >> x >> y;
            a[x] |= a[y];
        }
    }
}