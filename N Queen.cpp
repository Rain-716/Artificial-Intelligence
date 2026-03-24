#include <bits/stdc++.h>
using namespace std;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin>>n;
    if (n%6!=2&&n%6!=3){
        for (int c=1;c<n;c+=2){
            cout<<c<<'\n';
        }
        for (int c=0;c<n;c+=2){
            cout<<c<<'\n';
        }
    }
    else if (n%6==2){
        for (int c=1;c<n;c+=2){
            cout<<c<<'\n';
        }
        cout<<2<<'\n'<<0<<'\n';
        for (int c=6;c<n;c+=2){
            cout<<c<<'\n';
        }
        cout<<4<<'\n';
    }
    else {
        for (int c=3;c<n;c+=2){
            cout<<c<<'\n';
        }
        cout<<1<<'\n';
        for (int c=4;c<n;c+=2){
            cout<<c<<'\n';
        }
        cout<<0<<'\n'<<2<<'\n';
    }
    return 0;
}