#include <iostream>
#include <cstring>
using namespace std;
int main(){
    string x,y;
    cin>>x>>y;
    int t=0;
    string s="";
    int xx=x[3]-'0';
    int yy=y[3]-'0';
    int ss=(xx+yy)%2;
    if(t==1){
        if(ss==1)ss=0;
        else {
            ss=1;
            t=0;
        }
    }
    if(x[3]==y[3] and x[3]=='1')t=1;
    s=(char)(ss+'0')+s;
    xx=x[2]-'0';
    yy=y[2]-'0';
    ss=(xx+yy)%2;
    if(t==1){
        if(ss==1)ss=0;
        else {
            ss=1;
            t=0;
        }
    }
    if(x[2]==y[2] and x[2]=='1')t=1;
    s=(char)(ss+'0')+s;

    xx=x[1]-'0';
    yy=y[1]-'0';
    ss=(xx+yy)%2;
    if(t==1){
        if(ss==1)ss=0;
        else {
            ss=1;
            t=0;
        }
    }
    if(x[1]==y[1] and x[1]=='1')t=1;
    s=(char)(ss+'0')+s;
    xx=x[0]-'0';
    yy=y[0]-'0';
    ss=(xx+yy)%2;
    if(t==1){
        if(ss==1)ss=0;
        else {
            ss=1;
            t=0;
        }
    }
    if(x[0]==y[0] and x[0]=='1')t=1;
    s=(char)(ss+'0')+s;
    cout<<s;
}