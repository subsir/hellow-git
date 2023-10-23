#include <iostream>
#include <cstring>
using namespace std;
int n;
string s;
int door[100][3],road[100][3],td,tr;
int main(){
    cin>>n;
    int i=0;
    while (i++<n)
    {
        cin>>s;
        if(s=="on"){
            door[td][0]=i;
            cin>>door[td][1]>>door[td++][2];
        }
        else if(s=="off"){
            int x,y;
            cin>>x>>y;
            door[td][0]=i;
            door[td][1]=-y;
            door[td++][2]=-x;
        }
        else {
            road[tr][0]=i;
            cin>>road[tr][1]>>road[tr++][2];
        }
    }
    int up=0,down=0,j=0,ma=1000,mi=0;
    for(i=0;i<tr;i++){
        while (j<td && road[i][0]>door[j][0])
        {
            up-=door[j][1];
            down-=door[j][2];
            j++;
        }
        mi=max(mi,down+road[i][1]);
        ma=min(ma,up+road[i][2]);
    }
    cout<<mi<<' '<<ma<<endl;
    up=0,down=0,j=td-1,ma=1000,mi=0;
    for(i=tr-1;i>=0;i--){
        while (j>=0 && road[i][0]<door[j][0])
        {
            up+=door[j][2];
            down+=door[j][1];
            j--;
        }
        mi=max(mi,down+road[i][1]);
        ma=min(ma,up+road[i][2]);
    }
    cout<<mi<<' '<<ma<<endl;
}