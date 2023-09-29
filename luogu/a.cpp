#include <bits/stdc++.h>
using namespace std;
int ans,n,q;
const int MAXN = 100010;
int d[MAXN],c[MAXN],f[MAXN][20],v[MAXN][20],log_2[MAXN],rmax[MAXN][20];
int qmax(int x,int y){
    int u=log_2[y-x+1];
    return max(rmax[x][u],rmax[y-(1<<u)+1][u]);
}
int main(){
#ifndef ONLINE_JUDGE
    freopen("1.in","r",stdin);
#endif
    cin>>n>>q;
    log_2[0]--;
    for(int i=1;i<MAXN;i++){
        log_2[i]=log_2[i/2]+1;
    }
    for(int i=0;i<n;i++){
        scanf("%d%d",&d[i],&c[i]);
        rmax[i][0]=d[i];
    }
    d[n]=(int)(1e9+10);
    c[n]=(int)(1e9+10);
    for(int j=1;(1<<j)-1<=n;j++)
        for(int i=0;(1<<j)+i-1<=n;i++){
            rmax[i][j]=max(rmax[i][j-1],rmax[i+(1<<j-1)][j-1]);
        }
    for(int i=0;i<n;i++){
        int l=i+1,r=n;
        while (l<r)
        {
            int mid=(l+r)/2;
            if(qmax(l,mid)<=d[i]){
                l=mid+1;
            }
            else{
                r=mid;
            }
        }
        f[i][0]=l;
        v[i][0]=c[l];
    }
    f[n-1][0]=n;
    v[n-1][0]=c[n];
    for(int j=1;(1<<j)<=n;j++)
        for(int i=0;i+(1<<j)<=n;i++){
            f[i][j]=f[f[i][j-1]][j-1];
            if(f[i][j]>n){
                f[i][j]=0;
                break;
            }
            if(f[i][j])v[i][j]=v[i][j-1]+v[f[i][j-1]][j-1];
        }
    while (q--)
    {
        int o,p;
        scanf("%d%d",&o,&p);
        o--;
        /*p-=c[o];
        for(int t=19;t>=0;t--){
            if(v[o][t]){
                if(p>=v[o][t]){
                    o=f[o][t];
                    p-=v[o][t];
                }
            }
        }
        if(p>0)o=f[o][0];
        if(o==n)o=-1;
        o++;
        printf("%d\n",o);
    }
    return 0;*/
        if(p>c[o]){
            p-=c[o]; 
            for(int t=19;t>=0;t--)
                if(v[o][t]&&p>v[o][t]){
                    p-=v[o][t];
                    o=f[o][t];
                }
            o=f[o][0];
        }       
        if(o==n)o=-1;
        o++;
        printf("%d\n",o);
    }
}