/*try{

}catch(...){

}
或者catch(const exception& e){
    cout<<e.what();
}
stoi()尝试读到一个数后就不会报错
*/
#include <iostream>
#include <cstring>
using namespace std;
string s;
int main(){
    int n;
    cin>>n;
    while (n--)
    {
        cin>>s;
        char c=s[0];
        switch (c)
        {
            case('S'):
                try{
                    int x=stoi(s.substr(1));
                    if(to_string(x)!=s.substr(1)){
                        cout<<"Invalid";
                        break;
                    }
                    if(101<=x && x<=9998)cout<<"Shijiao";
                    else cout<<"Invalid";                    
                }catch(...){
                    cout<<"Invalid";
                }
                break;
            case('Z'):
                try{
                    int x=stoi(s.substr(1));
                    if(to_string(x)!=s.substr(1)){
                        cout<<"Invalid";
                        break;
                    }
                    if(1<=x && x<=9998)cout<<"Zhikuai";
                    else cout<<"Invalid";
                }catch(...){
                    cout<<"Invalid";
                }
                break;
            case('T'):
                try{
                    int x=stoi(s.substr(1));
                    if(to_string(x)!=s.substr(1)){
                        cout<<"Invalid";
                        break;
                    }
                    if(1<=x && x<=9998)cout<<"Tekuai";
                    else cout<<"Invalid";
                }catch(...){
                    cout<<"Invalid";
                }
                break;
            case('K'):
                try{
                    int x=stoi(s.substr(1));
                    if(to_string(x)!=s.substr(1)){
                        cout<<"Invalid";
                        break;
                    }
                    if(1<=x && x<=9998)cout<<"Kuaisu";
                    else cout<<"Invalid";
                }catch(...){
                    cout<<"Invalid";
                }
                break;
            case('Y'):
                try{
                    int x=stoi(s.substr(1));
                    if(to_string(x)!=s.substr(1)){
                        cout<<"Invalid";
                        break;
                    }
                    if(1<=x && x<=998)cout<<"Lyuyou";
                    else cout<<"Invalid";
                }catch(...){
                    cout<<"Invalid";
                }
                break;    
            default:
                try
                {
                    int x=stoi(s);
                    if(to_string(x)!=s){
                        cout<<"Invalid";
                        break;
                    }
                    if(1001<=x && x<=5998)cout<<"Pukuai";
                    else if(6001<=x && x<=7598)cout<<"Puke";
                    else if(7601<=x && x<=8998)cout<<"Tongqin";
                    else cout<<"Invalid";
                }
                catch(...)
                {
                    cout<<"Invalid";
                }
                
        }
        cout<<endl;
        }
}