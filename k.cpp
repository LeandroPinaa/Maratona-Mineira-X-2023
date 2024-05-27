#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
#define NMAX 105
#define MOD 1000000007
#define int long long
#define INF 1e18
#define faster ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define ost tree<int,null_type,less_equal<int>,rb_tree_tag,tree_order_statistics_node_update>

typedef struct{
    int r,g,b;
}cor;

bool comp(cor a, cor b){
    if(a.r == b.r){
        if(a.g == b.g){
            return a.b < b.b;
        }
        return a.g < b.g;
    }
    return a.r < b.r;
}

int32_t main(){ faster
    int n;
    cin >> n;
    vector<cor>v(n);
    for(int i=0;i<n;i++){
        cin >> v[i].r >> v[i].g >> v[i].b;
    }
    int maior = -INF;
    for(int r=0;r<=255;r++){
        for(int g=0;g<=255;g++){
            for(int b=0;b<=255;b++){
                int menor = INF;
                for(int i=0;i<n;i++){
                    int d = abs(r-v[i].r) + abs(g-v[i].g) + abs(b-v[i].b);
                    menor = min(menor,d);
                }
                maior = max(maior,menor);
            }
        }
    }
    vector<cor>ans;
    for(int r=0;r<=255;r++){
        for(int g=0;g<=255;g++){
            for(int b=0;b<=255;b++){
                int menor = INF;
                for(int i=0;i<n;i++){
                    int d = abs(r-v[i].r) + abs(g-v[i].g) + abs(b-v[i].b);
                    menor = min(menor,d);
                }
                if(menor==maior){
                    ans.push_back({r,g,b});
                }
            }
        }
    }
    sort(ans.begin(),ans.end(),comp);
    cout << ans[0].r << " " << ans[0].g << " " << ans[0].b << '\n';
    //for(auto it:ans) cout << it.r << " " << it.g << " " << it.b << '\n';
}