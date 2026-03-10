#include <bits/stdc++.h>
using namespace std;
vector<char> dir={'u','d','l','r'};
vector<int> dx={0,0,-1,1};
vector<int> dy={-1,1,0,0};
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s,t="12345678x";
    cin>>s;
    int inv=0;
    for (int i=0;i<9;i++){
        if (s[i]=='x'){
            continue;
        }
        for (int j=i+1;j<9;j++){
            if (s[j]=='x'){
                continue;
            }
            if (s[i]>s[j]){
                inv++;
            }
        }
    }
    if (inv%2){
        cout<<"unsolvable\n";
    }
    queue<string> q;
    unordered_map<string,string> par;
    unordered_map<string,char> move;
    q.push(s);
    par[s]="";
    while (!q.empty()){
        string cur=q.front();
        q.pop();
        int pos=cur.find('x');
        int x=pos%3,y=pos/3;
        for (int i=0;i<4;i++){
            int xx=x+dx[i],yy=y+dy[i];
            if (xx<0||xx>=3||yy<0||yy>=3){
                continue;
            }
            string nex=cur;
            swap(nex[pos],nex[yy*3+xx]);
            if (par.find(nex)==par.end()){
                par[nex]=cur;
                move[nex]=dir[i];
                if (nex==t){
                    string ans;
                    while (nex!=s){
                        ans+=move[nex];
                        nex=par[nex];
                    }
                    reverse(ans.begin(),ans.end());
                    cout<<ans<<'\n';
                }
                else {
                    q.push(nex);
                }
            }
        }
    }
    return 0;
}