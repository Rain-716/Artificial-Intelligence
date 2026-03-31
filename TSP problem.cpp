#include <iostream>
#include <cmath>
#include <cstring>
#include <queue>
using namespace std;
#define maxn 1001
int n;
double x[maxn],y[maxn];
double distance(int A,int B)
{
    return sqrt((x[A]-x[B])*(x[A]-x[B])+(y[A]-y[B])*(y[A]-y[B]));
}
double f(const vector<int> &p)
{
    double ans=0;
    for (unsigned i=0;i<p.size()-1;i++){
        ans+=distance(p[i],p[i+1]);
    }
    ans+=distance(p[0],p[p.size()-1]);
    return ans;
}
vector<int> p_new;
vector<int> p_current;
vector<int> p_best;
double t;
void init();
bool termi();
vector<int> N(const vector<int> &p);
double drop(double t);
double calc_p();
void SA()
{
    p_new.clear();
    for (int i=1;i<=n;i++){
        p_new.push_back(i);
    }
    p_best=p_current=p_new;
    init(); 
    while (termi()==false){
        p_new=N(p_current);
        if (f(p_new)<f(p_current)){
            p_current=p_new;
        }
        else {
            double pt=calc_p();
            if (pt>(double)(rand()*1.0/RAND_MAX)){
                p_current=p_new;
            }
        } 
        t=drop(t);
        if (f(p_current)<f(p_best)){
            p_best=p_current;
        }
    }
}
int main()
{
    cin>>n;
    for (int i=1;i<=n;i++){
        cin>>x[i]>>y[i];
    }
    SA();
    cout<<f(p_best)<<endl;
    for (unsigned i=0;i<p_best.size();i++){
        cout<<p_best[i]<<" ";
    }
    cout<<1<<endl;
    return 0;
}
#include <algorithm>
void init()
{
    t=10000.0;
}
bool termi()
{
    return t<1e-8;
}
vector<int> N(const vector<int> &p)
{
    int n=p.size();
    if (n<=2){
        return p;
    }
    vector<int> q=p;
    int L=rand()%(n-1)+1;
    int R=rand()%(n-1)+1;
    while (L==R){
        R=rand()%(n-1)+1;
    }
    if (L>R){
        swap(L,R);
    }
    reverse(q.begin()+L,q.begin()+R+1);
    return q;
}
double drop(double t)
{
    return t*0.999;
}
double calc_p()
{
    return exp((f(p_current)-f(p_new))/t);
}