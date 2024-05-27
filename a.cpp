#include <bits/stdc++.h>
using namespace std;
 
int main(){
    
    int A,B,C,D;
    cin >> A >> B >> C >> D;
    if(B==1 && C==2 && D==3) cout << 1 << endl;
    else if(A==1 && C==1 && D==2) cout << 2 << endl;
    else if(A==2 && B==1 && D==1) cout << 3 << endl;
    else if(A==3 && B==2 && C==1) cout << 4 << endl;
    
    return 0;
}