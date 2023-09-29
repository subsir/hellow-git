//a[top+1]=a[top]*a[top++]%MOD;会先加top再对top+1赋值，导致空了一个没有赋值
#include <iostream>
using namespace std;
constexpr int MOD=2022;
int a[10000];
int main(){
  int x,n,ans=1;
  cin>>x>>n;
  int nn=n,top=0;
  a[0]=x;
  do
  {
    a[top+1]=a[top]*a[top]%MOD;
    top++;
    nn=(nn>>1);
  } while (nn);
  a[top+1]=a[top]*a[top]%MOD;
  while (n)
  {
    while ((1<<top)>n)
    {
      top--;
    }
    n-=(1<<top);
    ans*=a[top];
    ans%=MOD;
  }
  cout<<ans;
  
}