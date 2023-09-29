#include<iostream>
#include<queue>
#include<cstdio>
using namespace std;
long long n,k,t,ans;

struct node
{
    long long w, h;
    bool operator>(const node& other) const {
        if (w != other.w) {
            return w > other.w;
        }
        return h > other.h;
    }
};                                                                                                                                            

priority_queue <node,vector<node>,greater<node> > q;
int main(){
#ifndef ONLINE_JUDGE
    freopen("P2168_5.in","r",stdin);
#endif
    cin>>n>>k;
    for(long long i=0;i<n;i++){
        scanf("%d",&t);
        q.push(node{t,0});
    }
    while ((n-1)%(k-1))
    {
        n++;
        q.push(node{0,0});
    }
    while (q.size()>1)
    {
        long long x=0,y=0;
        for(long long i=0;i<k;i++){
            x+=q.top().w;
            y=max(y,q.top().h);
            q.pop();
        }
        q.push(node{x,y+1});
        ans+=x;
    }
    cout<<ans<<endl;
    cout<<q.top().h;    
}