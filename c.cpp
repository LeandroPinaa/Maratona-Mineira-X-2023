#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
#define NMAX 100005
#define MOD 998244353
#define int long long
#define INF 1e18
#define faster ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define ost tree<int,null_type,less_equal<int>,rb_tree_tag,tree_order_statistics_node_update>
#define m (l+r)/2

int mdc(int a, int b){
    if(a==0) return b;
    return mdc(b%a,a);
}
int tem[NMAX]; // se tem[2] = 1 significa q existe o primo 2

vector<int>fat(int n){
    vector<int>primos;
    int value = n;
    for(int i=2;i<=sqrt(n);i++){
        while(value%i==0){
            primos.push_back(i);
            value /= i;
        }
    }
    if(value!=1) primos.push_back(value);
    return primos;
}

int32_t main(){ faster
    vector<int>v;
    int n;
    cin >> n;
    for(int i=0;i<n;i++){
        int a,b;
        cin >> a >> b;
        b /= mdc(a,b);
        v.push_back(b);
    }
    bool tempelomenosum = false;
    for(auto b:v){
        // busca os primos de cada
        vector<int>primos = fat(b);
        for(auto it:primos){
            tempelomenosum = true;
            tem[it] = 1;
        }
    }
    if(!tempelomenosum) cout << "2\n";
    else{
        int ans = 1;
        for(int i=2;i<=NMAX;i++){
            if(tem[i]) ans = (ans*i)%MOD;
        }
        cout << ans << '\n';
    }
}