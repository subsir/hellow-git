//cout.width() 输出指定个数的字符，不足左侧用空格补齐，超出用原样输出 from ChatGPT
//log(x)/log(10)的算法存在误差：1e9的位数为9
#include <iostream>
using namespace std;
int a[1010][1010],n;
int main(){
    cin>>n;
    int l=0,x=0,y=0;
    a[x][y]=1;
    for(int i=1;i<n*n;i++){
        if(!l){
            if(x-1>=0 && y+1 <n){
                x--;y++;
            }
            else if(y+1<n){
                y++;
                l=1;
            }
            else {
                x++;
                l=1;
            }
        }
        else{
            if(x+1<n && y-1>=0){
                x++;y--;
            }
            else if(x+1<n){
                x++;
                l=0;
            }
            else {
                y++;
                l=0;
            }
        }
        a[x][y]=i+1;
    }
    for(int i=0;i<n;i++){
        for(int j=n-1;j>=0;j--){
            cout.width(9);
            cout<<a[i][j];
        }
        cout<<endl;
    }
}