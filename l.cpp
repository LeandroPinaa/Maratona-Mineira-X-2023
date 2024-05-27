#include <bits/stdc++.h>
using namespace std;
#define NMAX 100005
#define LOGMAX 15
#define INF 1e18
#define m (l+r)/2
#define faster ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define int long long
typedef pair<int,int>pii;

vector<int>grafo[NMAX];
int v[NMAX]; //valores do grafo
int t[NMAX<<2];
vector<int>lz(NMAX<<2,-1);
int nivel[NMAX]; //raiz tem nivel[1] = 0
int parent[NMAX]; //ancestral de um heavy path
int heavy[NMAX]; //qual heavy path tal vert pertence, caso base -1
int head[NMAX]; //cabeça de um heavy path, o mais acima
int pos[NMAX]; //qual a pos daquele vert na seg
int at[NMAX];
int anc[NMAX][LOGMAX+1]; //query(a,b) é mais rapido se for query(a,lca(a,b))+query(b,lca(a,b))
int tamanhocada[NMAX]; //tamanho de cada heavy path,
//especifico para esse problema do CF pq a op1 necessita um update de toda a heavy path
//caso base = 1, todo vertice tem pelo menos ele
int N;

int DFS(int v){
    int size=1,max_c_size = 0;
    for(auto c:grafo[v]){
        if(c != parent[v]){
            parent[c] = v;
            anc[c][0] = parent[c];
            nivel[c] = nivel[v]+1;
            int c_size = DFS(c); //tamanho dessa subarvore
            size += c_size;
            if(c_size > max_c_size){ //definição de heavy: a subarvore de maior tamanho
                max_c_size = c_size;
                heavy[v] = c;
            }
        }
    }
    return tamanhocada[v] = size;
}

int cur_pos=1; //vai salvar as pos dos verts q ficam na seg
void decompose(int v, int h){
    at[cur_pos] = v;
    head[v] = h, pos[v] = cur_pos++;
    if(heavy[v]!=-1) decompose(heavy[v],h); //fazem parte do mesmo heavy path
    //essa recursão vem antes pq já garante que todos os vert do msm heavy path estarão em ordem na seg
    for(int c:grafo[v]){
        if(c != parent[v] && c != heavy[v]) decompose(c, c);
    }
}

void push(int i, int l, int r){
    if(lz[i]!=-1){
        t[i] = lz[i]*(r-l+1);
        if(l!=r){
            lz[i*2] = lz[i];
            lz[i*2+1] = lz[i];
        }
        lz[i] = -1;
    }
}

int STquery(int i, int l, int r, int ql, int qr){
    push(i,l,r);
    if(ql<=l&&r<=qr) return t[i];
    if(ql>r || qr<l) return 0;
    int LChild = STquery(i*2,l,m,ql,qr);
    int RChild = STquery(i*2+1,m+1,r,ql,qr);
    return LChild + RChild;
}

int query(int a, int b){
    int resp = 0;
    for(; head[a] != head[b]; b = parent[head[b]]){
        if(nivel[head[a]] > nivel[head[b]]) swap(a,b); //o nivel de b tem que ser o mais abaixo
        int cur = STquery(1,1,N,pos[head[b]],pos[b]);
        resp += cur;
    }
    if(nivel[a] > nivel[b]) swap(a,b); //agora eles são do mesmo heavy path, mesma chain
    int last = STquery(1,1,N,pos[a],pos[b]);
    resp += last;
    return resp;
}

void STupdate(int i, int l, int r, int ql, int qr, int x){
    push(i,l,r);
    if(ql<=l&&r<=qr){
        lz[i] = x;
        push(i,l,r);
        return;
    }
    if(ql>r || qr<l) return;
    STupdate(i*2,l,m,ql,qr,x);
    STupdate(i*2+1,m+1,r,ql,qr,x);
    t[i] = t[i*2] + t[i*2+1];
}

void update(int a, int b, int x){
    for(; head[a] != head[b]; b = parent[head[b]]){
        if(nivel[head[a]] > nivel[head[b]]) swap(a,b);
        STupdate(1,1,N,pos[head[b]],pos[b],x);
    }
    if(nivel[a] > nivel[b]) swap(a,b);
    STupdate(1,1,N,pos[a],pos[b],x);
}

int querysubtree(int x){
    return STquery(1,1,N,pos[x],pos[x]+tamanhocada[x]-1);
}

int32_t main(){ faster
    int x,y,op;
    cin >> N;
    for(int i=1;i<=N;i++){
        //cin >> v[i];
        heavy[i] = -1;
        tamanhocada[i] = 1;
    } 
    for(int i=0;i<N-1;i++){
        cin >> x >> y;
        grafo[x].push_back(y);
        grafo[y].push_back(x);
    }
    DFS(1); //pre processamento, definir tudo
    decompose(1,1); //decompor a arvore em segmentos heavy paths
    for(int j=1;j<=LOGMAX;j++){
        for(int i=1;i<=N;i++){
            anc[i][j] = anc[ anc[i][j-1] ][j-1];
        }
    }
    //for(int i=1;i<=N;i++) update(i,i,v[i]);
    int Q;
    cin >> Q;
    while(Q--){
        cin >> op >> x;
        if(op==1){
            // acende o vertice x e os abaixo dele
            STupdate(1,1,N,pos[x],pos[x]+tamanhocada[x]-1,1);
            // agora precisa verificar os ancestrais de x se precisa acender ou não
            int vv = x;
            for(int i=LOGMAX;i>=0;i--){
                if(anc[vv][i]==0) continue;
                int cur = anc[vv][i];
                int dist = nivel[x] - nivel[cur] + 1;
                if( (tamanhocada[cur] - querysubtree(cur)) == (dist - query(x,cur))){
                    vv = cur;
                }
            }
            update(vv,x,1);
        }
        else if(op==2){
            STupdate(1,1,N,pos[x],pos[x]+tamanhocada[x]-1,0);
            update(1,x,0);
        } 
        else cout << STquery(1,1,N,pos[x],pos[x]+tamanhocada[x]-1) << '\n';
    }
}
/*
5
1 2
2 3
3 4
4 5
3
3 1
1 5
3 1

 
7
1 2
1 3
2 4
2 5
4 6
4 7
5
1 3
1 5
1 7
1 6
3 1
*/