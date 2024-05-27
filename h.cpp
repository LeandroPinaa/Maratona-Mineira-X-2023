#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
#define NMAX 21
#define MOD 1000000007
#define int long long
#define INF 1e18
#define faster ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define ost tree<int,null_type,less_equal<int>,rb_tree_tag,tree_order_statistics_node_update>
#define m (l+r)/2

int qtd[1<<NMAX];
int id[100];

int32_t main(){ faster
    int cont=0;
    for(int i='a';i<='z';i++){
        if(i=='a' || i=='e' || i=='i' || i=='o' || i=='u' || i=='y') continue;
        id[i-'a'] = cont++;
    }
    int n,ans=0,mask=0;
    cin >> n;
    string s;
    cin >> s;
    qtd[0] = 1;
    for(int i=0;i<n;i++){
        mask ^= (1<<id[s[i]-'a']);
        ans += qtd[mask];
        for(int j=0;j<20;j++){
            ans += qtd[mask^(1<<j)];
        }
        qtd[mask]++;
    }
    cout << ans << '\n';   
}