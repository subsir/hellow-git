#include <iostream>
using namespace std;
int n,m;
int ans[110],a[110][110];
bool re;
bool check(int x){
    for(int i=1;i<=a[x][0];i++){
        if(ans[a[x][i]]==ans[x])return false;
    }
    return true;
}
int main(){
    cin>>n>>m;
    int t1,t2,t;
    for(int i=0;i<m;i++){
        scanf("%d%d",&t1,&t2);
        a[t1][++a[t1][0]]=t2;
        a[t2][++a[t2][0]]=t1;
    }
    for(int i=1;i<=n;i++){
        if(!ans[i]){
            re=false;
            ans[i]++;
        }
        if(re){
            ans[i]++;
            if(ans[i]==5){
                ans[i]=0;
                i-=2;
            }
        }
        while (!check(i))
        {
            ans[i]++;
            if(ans[i]==5){
                re=true;
                ans[i]=0;
                i-=2;
            }
        }
        
    }
    for(int i=1;i<=n;i++)cout<<ans[i];
}