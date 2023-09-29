#include <iostream>
using namespace std;
int a[10000];
int f(int x){
  int ans=1;
  for(int i=1;i<=(x>>1);i++){
    if(a[i]==0){
      a[i]=f(i);
    }
    ans+=a[i];
  }
  return ans;
}
int main(){
  int n;
  cin>>n;
  cout<<f(n);
}