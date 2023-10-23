#include <iostream>
#include <algorithm>
using namespace std;
int a[3],mi,ma;
int main(){
    for(int i=0;i<3;i++)cin>>a[i];
    sort(a,a+3);
    int x=a[1]-a[0];
    int y=a[2]-a[1];
    if(x>y){
        int c=x;
        x=y;
        y=c;
    }
    if(x==2){
        mi=1;
    }
    else if(x==y==1){
        mi=0;
    }
    else if(x==1 && y==2){
        mi=1;
    }
    else mi=2;
    ma=y-1;
    cout<<mi<<endl<<ma<<endl;
}