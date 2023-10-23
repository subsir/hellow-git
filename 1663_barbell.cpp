//感恩ChatGPT提供的异或想法
#include <iostream>
#include <cstdio>
using namespace std;
int n,t,result;
int main(){
    std::ios::sync_with_stdio(false);
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d",&t);
        result=result^t;
    }
    printf("%d",result);
}