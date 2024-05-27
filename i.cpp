#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
#define NMAX 5005
#define MOD 1000000007
#define int long long
#define INF 1e18
#define faster ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define ost tree<int,null_type,less_equal<int>,rb_tree_tag,tree_order_statistics_node_update>
#define pii pair<int,int>

vector<int>invFatorial(NMAX),fatorial(NMAX);

int inv(int a, int b){
	return a > 1 ? b - inv(b%a, a)*b/a : 1;
}

int combinacao(int n, int k, int m){
    if(n<k || k<0) return 0; 
    if(n==k) return 1;
    int ans = (fatorial[n]*((invFatorial[k]*invFatorial[n-k])%m))%m;
    return ans;
}

int32_t main(){ faster
    int n,m,ans=0; // n = qtd movimentos do bebado
    cin >> n >> m;
    //pré processamento
    invFatorial[0] = invFatorial[1] = 1;
    fatorial[0] = fatorial[1] = 1;
    for(int i=2;i<NMAX;i++){
        fatorial[i] = (fatorial[i-1]*i)%m;
        invFatorial[i] = inv(fatorial[i],m);
    }
    // (n-2*i) é a quantidade de movimentos que eu fico parado
    for(int i=0;i<=n/2;i++){ // cuido da vertical
        for(int j=(n-2*i+1)/2;j<=n/2;j++){ // cuido da horizontal
            ans = (ans+((combinacao(n,2*i,m)*combinacao(2*i,i,m)%m)*(combinacao(2*i,2*j-(n-2*i),m)*combinacao(2*j,j,m)%m)%m))%m;
        }
    }
    cout << ans << '\n';
}
/*
sem diagonais: 
for(int i=0;i<=n/2;i++){ // cuido da vertical
    for(int j=0;j<=n/2;j++){ // cuido da horizontal
        if (i + j > n) break;
        int rest = n - i - j;
        if (rest % 2 != 0) continue;
        ans = (ans + ((((combinacao(n,i,m)%m)*combinacao(n-i,j,m)%m))%m))%m;
    }
}
*/