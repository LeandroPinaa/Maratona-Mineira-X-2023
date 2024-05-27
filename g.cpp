#include <bits/stdc++.h>
using namespace std;

int main(){
    
    int N;
    cin >> N;
    int X=2;
    for(int i=0;i<N;i++){
        int A,B;
        cin >> A >> B;
        if(A==X)X=B;
        else if(B==X) X=A;
    }
    cout << X << endl;

    return 0;
}