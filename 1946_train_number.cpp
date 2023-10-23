#include <iostream>
#include <cstring>
using namespace std;
string s;
int main(){
    cin>>s;
    char c=s[0];
    switch (c)
    {
    case 'G':
        cout<<"Gaosu";
        break;
    case 'C':
        cout<<"Chengji";
        break;
    case 'D':
        cout<<"Dongche";
        break;
    case 'S':
        cout<<"Shijiao";
        break;
    case 'Z':
        cout<<"Zhikuai";
        break;
    case 'T':
        cout<<"Tekuai";
        break;
    case 'K':
        cout<<"Kuaisu";
        break;
    case 'Y':
        cout<<"Lyuyou";
        break;
    default:
        int x=stoi(s);
        if(x<6000)cout<<"Pukuai";
        else if(x<7600)cout<<"Puke";
        else cout<<"Tongqin";
        break;
    }
}