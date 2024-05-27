#include <bits/stdc++.h>
using namespace std;
#define int long long
#define NMAX 505
#define TMAX 505
#define INF 1e18
#define pii pair<int,int>
#define faster ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

int dp[NMAX][50002];
vector<pii>peias[TMAX];
int n;

int f(int i, int tam, int cap){
    if(cap<0) return -INF;
    if(i==peias[tam].size()) return 0;
    if(dp[i][cap]!=-1) return dp[i][cap];
    dp[i][cap] = max(f(i+1,tam,cap-peias[tam][i].first)+peias[tam][i].second,f(i+1,tam,cap));
    return dp[i][cap];
}

int32_t main(){ faster
    int t;
    cin >> n >> t;
    for(int i=0;i<n;i++){
        int pes,tamanho,maj;
        cin >> pes >> tamanho >> maj;
        pes /= 2;
        peias[tamanho].push_back({pes,maj});
    }
    memset(dp,-1,sizeof dp);
    int ans = 0,esq,dir;
    for(int tam=1;tam<=t;tam++){
        cin >> esq >> dir;
        int cap = min(esq,dir); // basta verificar o minimo
        ans += f(0,tam,cap);
        for(int i=0;i<peias[tam].size();i++){
            for(int j=0;j<=cap;j++){
                dp[i][j] = -1;
            }
        }
    }
    cout << ans << '\n';
}   
/*

*/