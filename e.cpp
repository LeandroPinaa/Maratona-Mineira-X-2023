#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
#define NMAX 100005
#define LOGMAX 17
#define MOD 1000000007
#define INF 1e18
#define int long long
#define faster ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define ost tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update>
#define pii pair<int,int>
#define m (l+r)/2

pii v[NMAX];
int n;

pair<int,vector<int>> solve(int i){
	vector<int>ans2;
	int menor2 = 0;
	int l = i, r = i;
	while(true){
		ans2.push_back(i);
		if(l==0 && r+1==n){
			menor2 += min(v[i].first,v[i].second);
			break;
		}
		if(l==0){
			menor2 += v[i].second;
			i = ++r;
			continue;
		}
		if(r+1==n){
			menor2 += v[i].first;
			i = --l;
			continue;
		}
		
		if(v[i].first < v[i].second){
			menor2 += v[i].first;
			i = --l;
		}
		else{
			menor2 += v[i].second;
			i = ++r;
		}
	}
	return {menor2,ans2};
}

int32_t main(){ faster
	int x=0; //x = quantos left minimo tem, começo do x-1
	cin >> n;
	for(int i=0;i<n;i++){
		cin >> v[i].first >> v[i].second;
		if(v[i].first < v[i].second) x++;
	} 
	vector<int>ans;
	int menor = INF;
	for(int i=max(0LL,x-1);i<=min(n-1,x);i++){
		auto [menor2,ans2] = solve(i);
		if(menor2 < menor){
			menor = menor2;
			ans = ans2;
		}
	}
	for(int i=0;i<n;i++) cout << ans[i]+1 << " ";
	cout << '\n';
}