#include <iostream>
#include <cmath>
#include <cstring>
#include <queue>
using namespace std;
#define maxn 1000
int n,m,s,t;
double x[maxn],y[maxn];
bool edge[maxn][maxn];
int pos[maxn];
double length;
vector<int> path;
double gi[maxn],f[maxn];
double distance(int A,int B)
{
    return sqrt((x[A]-x[B])*(x[A]-x[B])+(y[A]-y[B])*(y[A]-y[B]));
}
double A_star(int s,int t);
int main()
{
    cin>>n>>m>>s>>t;
    for (int i=0;i<n;i++){
        cin>>x[i]>>y[i];
    }
    for (int i=0;i<m;i++){
        int A,B;
        cin>>A>>B;
        edge[A][B]=edge[B][A]=true;
    }
    memset(f,-1,sizeof(f));
    length=A_star(s,t);
    int tmp=t;
    while (tmp!=s){
        path.push_back(tmp);
        tmp=pos[tmp];
    }
    path.push_back(tmp);
    cout<<length<<'\n';
    for (int i=path.size()-1;i>0;i--){
        cout<<path[i]<<" ";
    }
    cout<<path[0]<<'\n';
    return 0;
}
double A_star(int s,int t)
{
    if (s==t){
        return 0.0;
    }
    for (int i=0;i<n;i++){
        gi[i]=1e100;
        f[i]=1e100;
        pos[i]=-1;
    }
    vector<double> h(n);
    for (int i=0;i<n;i++){
        h[i]=distance(i,t);
    }
    priority_queue<pair<double,int>,vector<pair<double,int>>,greater<pair<double,int>>> pq;
    vector<bool> closed(n,false);
    gi[s]=0.0;
    f[s]=h[s];
    pos[s]=-1;
    pq.push({f[s],s});
    while (!pq.empty()){
        int u=pq.top().second;
        double curF=pq.top().first;
        pq.pop();
        if (curF>f[u]||closed[u]){
            continue;
        }
        if (u==t){
            return gi[u];
        }
        closed[u]=true;
        for (int v=0;v<n;v++){
            if (!edge[u][v]||!edge[v][u]||closed[v]){
                continue;
            }
            double gv=gi[u]+distance(u,v);
            if (gv>=gi[v]){
                continue;
            }
            gi[v]=gv;
            f[v]=gi[v]+h[v];
            pos[v]=u;
            pq.push({f[v],v});
        }
    }
    return -1.0;
}