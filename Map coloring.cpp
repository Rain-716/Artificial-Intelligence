#include <bits/stdc++.h>
using namespace std;
int n,m,bestAns=-1;
vector <int> bestColor,curColor;
vector <unsigned> adj,adjColor;
vector <vector<int>> cnt;
int ChooseVertex(unsigned uncolored)
{
    int bestVer=-1,bestColNum=-1,bestDeg=-1;
    for (unsigned i=uncolored;i;i&=(i-1)){
        int ver=__builtin_ctz(i);
        int num=__builtin_popcount(adjColor[ver]);
        int deg=__builtin_popcount(adj[ver]);
        if (num>bestColNum||(num==bestColNum&&deg>bestDeg)){
            bestVer=ver;
            bestColNum=num;
            bestDeg=deg;
        }
    }
    return bestVer;
}
void addColor(int v,int c)
{
    for (unsigned i=adj[v];i;i&=(i-1)){
        int u=__builtin_ctz(i);
        if (++cnt[u][c]==1){
            adjColor[u]|=(1u<<c);
        }
    }
}
void removeColor(int v,int c)
{
    for (unsigned i=adj[v];i;i&=(i-1)){
        int u=__builtin_ctz(i);
        if (--cnt[u][c]==0){
            adjColor[u]&=~(1u<<c);
        }
    }
}
void UpperBound()
{
    int used=0;
    unsigned uncolored=(1u<<n)-1;
    vector <int> tmpColor(n,-1);
    adjColor.assign(n,0u);
    cnt.assign(n,vector<int>(n,0));
    while (uncolored){
        int v=ChooseVertex(uncolored);
        int c=__builtin_ctz(~adjColor[v]);
        tmpColor[v]=c;
        used=max(used,c+1);
        addColor(v,c);
        uncolored&=~(1u<<v);
    }
    bestAns=used;
    bestColor=tmpColor;
}
int LowerBound(unsigned uncolored)
{
    int res=0;
    while (uncolored){
        int pick=-1,bestDeg=-1;
        for (unsigned i=uncolored;i;i&=(i-1)){
            int v=__builtin_ctz(i);
            int deg=__builtin_popcount(adj[v]&uncolored);
            if (deg>bestDeg){
                pick=v;
                bestDeg=deg;
            }
        }
        res++;
        uncolored&=adj[pick];
    }
    return res;
}
void dfs(int coloredVer,int colorCnt,unsigned uncolored)
{
    if (coloredVer==n){
        if (colorCnt<bestAns){
            bestAns=colorCnt;
            bestColor=curColor;
        }
        return;
    }
    if (colorCnt>=bestAns){
        return;
    }
    if (max(colorCnt,LowerBound(uncolored))>=bestAns){
        return;
    }
    int v=ChooseVertex(uncolored);
    for (int c=0;c<colorCnt;c++){
        if (adjColor[v]&(1u<<c)){
            continue;
        }
        curColor[v]=c;
        addColor(v,c);
        dfs(coloredVer+1,colorCnt,uncolored&~(1u<<v));
        curColor[v]=-1;
        removeColor(v,c);
    }
    if (colorCnt+1<bestAns){
        int c=colorCnt;
        curColor[v]=c;
        addColor(v,c);
        dfs(coloredVer+1,colorCnt+1,uncolored&~(1u<<v));
        curColor[v]=-1;
        removeColor(v,c);
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin>>n>>m;
    adj.assign(n,0u);
    bestColor.assign(n,-1);
    curColor.assign(n,-1);
    while (m--){
        int x,y;
        cin>>x>>y;
        adj[x]|=(1u<<y);
        adj[y]|=(1u<<x);
    }
    UpperBound();
    adjColor.assign(n,0u);
    cnt.assign(n,vector<int>(n,0));
    fill(curColor.begin(),curColor.end(),-1);
    dfs(0,0,(1u<<n)-1);
    cout<<bestAns<<'\n';
    for (int& i:bestColor){
        cout<<i<<'\n';
    }
    return 0;
}