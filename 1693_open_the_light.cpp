//    f2(s2[h],t2[h]+1);
//    h++;
//与
//    f2(s2[h],t2[h++]+1);
//后者s2[h]中h也会++,直接超范围
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cstdlib>
using namespace std;
int t1[1000],t2[1000];
int top1=1,top2=1,h;
vector <string> s1,s2;
void f1(string s,int x){
  string u;
  for(int i=0;i<9;i++){
    u=s;
    u[i]^=1;
    if(i%3)u[i-1]^=1;
    if(i>2)u[i-3]^=1;
    if(i<6)u[i+3]^=1;
    if(i%3!=2)u[i+1]^=1;
    auto v = find(s2.begin(),s2.end(),u);
    if(v!=s2.end()){
      cout<<t2[v-s2.begin()]+x;
      exit(0);
    }
    s1.push_back(u);
    t1[top1++]=x;
  }
}
void f2(string s,int x){
  string u;
  for(int i=0;i<9;i++){
    u=s;
    u[i]^=1;
    if(i%3)u[i-1]^=1;
    if(i>2)u[i-3]^=1;
    if(i<6)u[i+3]^=1;
    if(i%3!=2)u[i+1]^=1;
    auto v = find(s1.begin(),s1.end(),u);
    if(v!=s1.end()){
      cout<<t1[v-s1.begin()]+x;
      exit(0);
    }
    s2.push_back(u);
    t2[top2++]=x;
  }
}
int main(){
  char c;
  string temp="";
  s2.push_back("111111111");
  for(int i=0;i<9;i++){
    cin>>c;
    temp+=c;
  }
  s1.push_back(temp);
  while (1)
  {
    f1(s1[h],t1[h]+1);
    f2(s2[h],t2[h]+1);
    h++;
  }
}