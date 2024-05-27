#include <bits/stdc++.h>
using namespace std;
#define int long long

int32_t main(){
    int n,m;
    cin >> n >> m;
    vector<vector<int>>mat(n+2,vector<int>(m+2));
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin >> mat[i][j];
        }
    }
    int ans = 1;
    for(int i=1;i<=n;i++){
        int qtd=1;
        for(int j=2;j<=m;j++){
            if(abs(mat[i][j-1]-mat[i][j])<=1){
                qtd++;
                ans = max(ans,qtd);
            }
            else qtd=1;
        }
    }
    for(int j=1;j<=m;j++){
        int qtd=1;
        for(int i=2;i<=n;i++){
            if(abs(mat[i-1][j]-mat[i][j])<=1){
                qtd++;
                ans = max(ans,qtd);
            }
            else qtd=1;
        }
    }
    cout << ans << '\n';
}
/*
3 6
5 7 5 7 5 7
5 1 3 1 1 7
5 7 5 7 5 7


*/