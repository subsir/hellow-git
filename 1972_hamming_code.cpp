//ans未初始化，本地可以，oj不行
#include <iostream>
#include <cstdio>
using namespace std;
int a[10];
void f(int x,int n){
  if(!x)return;
  int y=x%2;
  if(y)a[n]^=1;
  f(x>>1,n+1);
}
int main(){
  int t,ans=0;
  for(int i=0;i<256;i++){
    scanf("%d",&t);
    if(t)f(i,0);
  }
  for(int i=0;i<9;i++){
    if(a[i]%2)ans+=(1<<i);
  }
  cout<<ans;
  return 0;
}