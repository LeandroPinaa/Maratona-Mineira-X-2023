#include <bits/stdc++.h>
using namespace std;

int main(){
    
    int N;
    cin >> N;
    int S=0;
    for(int i=0;i<N-1;i++){
        int X;
        cin >> X;
        S+=X;
    }
    int D[N]; 
    for(int i=0;i<N;i++)D[(S+i)%N]=i;
    for(int i=0;i<N;i++){
        if(D[i]>20) cout << -1 << endl;
        else cout << D[i] << endl;
    }

    return 0;
}