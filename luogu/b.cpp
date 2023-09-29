#include <bits/stdc++.h>
using namespace std;
int n,x1,yy,x2,y2;
int k[100000][4],m[100000],mt,c[100000],ct,a[5000][5000];
long long ans;
int main(){
    cin>>n;
    for(int i=0;i<n;i++){
        scanf("%d%d%d%d",&x1,&yy,&x2,&y2);
        yy--;
        x2--;
        k[i][0]=x1;
        k[i][1]=yy;
        k[i][2]=x2;
        k[i][3]=y2;
        m[mt++]=x1;
        m[mt++]=x2;
        m[mt++]=yy;
        m[mt++]=y2;
    }
    sort(m,m+mt);
    c[ct++]=m[0];
    for(int i=1;i<mt;i++){
        if(m[i]!=m[i-1])c[ct++]=m[i];
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<4;j++)k[i][j]=lower_bound(c,c+ct,k[i][j])-c;
        a[k[i][0]][k[i][3]]++;
        a[k[i][0]][k[i][1]+1]--;
        a[k[i][2]+1][k[i][3]]--;
        a[k[i][2]+1][k[i][1]+1]++;
    }
    for(int i=0;i<ct;i++){
        for(int j=0;j<ct;j++){
            if(i>0){
                if(j>0)a[i][j]+=a[i][j-1]-a[i-1][j-1]+a[i-1][j];
                else a[i][j]+=a[i-1][j];
            }
            else{
                if(j>0)a[i][j]+=a[i][j-1];
            }
            
        }
    }
    for(int i=0;i<ct;i++){
        for(int j=0;j<ct;j++){
            if(a[i][j]){
                if(i>0){
                    if(j>0)ans+=(c[i]-c[i-1])*(c[j]-c[j-1]);
                    else ans+=(c[i]-c[i-1]);
                }
                else{
                    if(j>0)ans+=c[j]-c[j-1];
                }
            }
        }
    }
    cout<<ans;
}