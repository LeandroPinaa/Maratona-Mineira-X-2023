#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
#define NMAX 100005
#define MOD 1000000007
#define int long long
#define INF 1e18
#define faster ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define ost tree<int,null_type,less_equal<int>,rb_tree_tag,tree_order_statistics_node_update>
#define pii pair<int,int>
#define m (l+r)/2


int v[NMAX];
vector<int>estab[NMAX]; //pos de cada estabelecimento
vector<pii>arestas; //guarda as arestas entre mesmo estabelecimentos
vector<int>grafo[NMAX]; //novo grafo que basta verificar se é bipartido, se for, n há cruzamentos
int cor[NMAX];

bool areFriends(pii a, pii b){
    if(a.first > b.first) swap(a,b);
    if(a.first == b.first || a.first == b.second) return true;
    if(a.second == b.first || a.second == b.second) return true;
    if(a.second < b.first) return true;
    if(a.second > b.second) return true;
    return false;
    // ex: a=(1,3) e b=(2,4) há cruzamento, retorna true
    // ex> a=(1,2) e b=(3,4) não há cruzamento, retorna false
}

void colore(int v){
    cor[v] = 0;
    queue<int>fila;
    fila.push(v);
    while(!fila.empty()){
        int u = fila.front(); fila.pop();
        for(auto viz:grafo[u]){
            if(cor[viz]==-1){
                cor[viz] = 1-cor[u];
                fila.push(viz);
            }
        }
    }
}

bool bipartido(int n){
    memset(cor,-1,sizeof cor);
    for(int i=0;i<n;i++){
        if(cor[i]==-1) colore(i);
    }
    for(int i=0;i<n;i++){
        for(auto viz:grafo[i]){
            if(cor[i]==cor[viz]) return false;
        }
    }
    return true;
}

int32_t main(){ faster
    int n;
    bool flag=false;
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> v[i];
        estab[v[i]].push_back(i);
        if(estab[v[i]].size()>4) flag=true;
    }
    if(flag){ //se tem 5 ou mais do mesmo tipo, é impossivel n ter cruzamento
        cout << "N\n";
        return 0;
    }
    for(int e=1;e<=n;e++){ //adiciona todas as arestas entre estab do mesmo tipo
        for(int i=0;i<estab[e].size();i++){
            for(int j=i+1;j<estab[e].size();j++){
                arestas.push_back({estab[e][i],estab[e][j]});
            }
        }
    }
    for(int i=0;i<arestas.size();i++){
        for(int j=i+1;j<arestas.size();j++){
            // se um par de arestas tem relação, vai haver cruzamento, então ignora
            if( areFriends(arestas[i],arestas[j]) ) continue;
            grafo[i].push_back(j);
            grafo[j].push_back(i);
        }
    }
    if(bipartido(arestas.size())) cout << "S\n";
    else cout << "N\n";
}