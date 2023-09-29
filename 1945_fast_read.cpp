//感恩 ChatGPT 提供Horner法则
//脑筋转不过来QWQ
#include <iostream>
using namespace std;
// definition of seed
long long seed;
int n,x;
const int MOD=int(1e9)+7;
// function def.
int getA() {
    long long ret = seed;
    seed = (seed * 7ll + 13ll) % 1000000007ll;
    return ret;
}
int main(){
    cin>>n>>x>>seed;
    x%=MOD;
    long long t=getA();
    while (n--)
    {
        t=(t*x)%MOD+getA();
    }
    t%=MOD;
    cout<<t;
    
}