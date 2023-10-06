#include <iostream>
#include <cmath>
using namespace std;

long long order(int x) {
    long long u=1;
    for(int i=1;i<=x;i++) {
        u*=i;
    }
    return u;
}
int main() {
    int n;
    cin>>n;
    float b = order(n) * exp(1.0);
    cout<<b- (int)(b)<<endl;
    return main();
}