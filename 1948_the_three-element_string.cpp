#include <iostream>
#include <cstring>
#include <string>
using namespace std;
int h,t,n,ans,k,a[4];
string s;
bool flag;
int main(){
    cin>>n;
    while (n--)
    {
        cin>>s;
        ans=s.size();h=t=k=0;flag=0;
        memset(a,0,sizeof(a));
        while(t<s.size() && h <= t){
            while (t<s.size() && k<3)
            {
                a[s[t++]-'0']++;
                if(a[s[t-1]-'0']==1)k++;
            }
            if(k==3){
                ans=min(t-h,ans);
                flag=1;
            }
            h++;
            if(a[s[h-1]-'0']--==1)k--;
        }
        if(!flag)ans=0;
        cout<<ans;
    }   
}