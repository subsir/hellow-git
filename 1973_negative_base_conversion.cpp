#include <iostream>
using namespace std;
int a[100000],top;
int main(){
  int x,y;
  cin>>x>>y;
  while (x)
  {
    int c=x%y;
    int d=x/y;
    if(c<0){
      c-=y;
      d+=1;
    }
    a[top++]=c;
    x=d;
  }
  while (top--)
  {
    if(a[top]<=9 and a[top]>=0)
      cout<<a[top];
    else
      cout<<(char)(a[top]-10+'A');
  }
  
}