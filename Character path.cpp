#include <bits/stdc++.h>
using namespace std;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n,m,k;
    cin>>n>>m>>k;
    vector <vector<char>> a(n,vector<char>(m));
    for (int i=0;i<n;i++){
        for (int j=0;j<m;j++){
            cin>>a[i][j];
        }
    }
    string s;
    cin>>s;
    vector <vector<int>> dp(n,vector<int>(m,199));
    for (int i=0;i<n;i++){
        for (int j=0;j<m;j++){
            if (a[i][j]==s[0]){
                dp[i][j]=0;
            }
        }
    }
    for (int h=0;h<k;h++){
        vector <vector<int>> temp=dp;
        for (int i=0;i<n;i++){
            for (int j=1;j<m;j++){
                temp[i][j]=min(temp[i][j],temp[i][j-1]+1);
            }
            for (int j=m-2;j>=0;j--){
                temp[i][j]=min(temp[i][j],temp[i][j+1]+1);
            }
        }
        vector <vector<int>> ndp=temp;
        for (int j=0;j<m;j++){
            for (int i=1;i<n;i++){
                ndp[i][j]=min(ndp[i][j],ndp[i-1][j]+1);
            }
            for (int i=n-2;i>=0;i--){
                ndp[i][j]=min(ndp[i][j],ndp[i+1][j]+1);
            }
        }
        for (int i=0;i<n;i++){
            for (int j=0;j<m;j++){
                if (a[i][j]!=s[h]){
                    ndp[i][j]=199;
                }
            }
        }
        dp.swap(ndp);
    }
    int ans=199;
    for (int i=0;i<n;i++){
        for (int j=0;j<m;j++){
            ans=min(ans,dp[i][j]);
        }
    }
    cout<<ans<<'\n';
    return 0;
}