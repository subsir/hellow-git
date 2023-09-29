#include<iostream>
using namespace std;
long long dep;
long long st[(long long)(1e7+10)],ans[(long long)(1e7+10)],flag;
long long gcd(long long x,long long y){
    if(y==0)return x;
    return gcd(y,x%y);
}
void dfs(long long a,long long b,long long x){
    if(x>dep)return;
    if(a==1 && b>st[x-1]){
        st[x]=b;
        if(!flag || st[x]<ans[x])
            for(long long i=1;i<=dep;i++){
                ans[i]=st[i];
            }
        flag =1;
        return;
    }
    long long l,r=(dep-x+1)*b/a;
    l=max(st[x-1]+1,b/a);
    if(flag && r>=ans[dep])r=ans[dep]-1;
    for(long long i=l;i<r;i++){
        st[x]=i;
        long long o=a*i-b;
        long long p=b*i;
        long long c=gcd(o,p);
        o/=c;
        p/=c;
        dfs(o,p,x+1);
    }
}
long long main(){
    long long a,b;
    cin>>a>>b;
    long long c=gcd(a,b);
    a/=c;
    b/=c;
    for(dep=1;dep<=10;dep++){
        dfs(a,b,1);
        if(flag){
            for(long long i=1;i<=dep;i++){
                prlong longf("%lld ",ans[i]);
            }
            return 0;
        }
    }    
}