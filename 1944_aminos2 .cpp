//1944 阿米诺斯（加强版 2）
//substr(开始索引，长度)
//stoi() from string 字符串转换为int 相应有 stof stol stod
#include <iostream>
#include <string>
#include <cstring>
using namespace std;
string s;
int a[1010],top;
void split(string r){ 
    bool flag=1;
    int k=0;  
    for(int i=0;i<r.size();i++){
        if(r[i]==' '){
            if(flag){
                flag=0;
                a[top++]=stoi(s.substr(0,i)); 
                k=i;               
            }
            else{
                a[top++]=stoi(s.substr(k+1,i-k-1));
                k=i; 
            }
        }
    }
}
int main(){
    int t;
    cin>>t;
    cin.ignore();
    while (t--)
    {
        getline(cin,s);
        top=0;
        split(s);
        while (top--)
        {
            cout<<a[top];
            if(top)cout<<' ';
        }
        cout<<endl;
    } 
}