#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
#define pb push_back
#define mp make_pair
#define ip pair<ll,ll>
#define ipp pair<ll,ip>
#define ff first
#define ss second
#define MAX 100005
#define MOD 1000000007
#define INF 1e12
vector<int> parent(MAX);
vector<ll> r(MAX);

int make_set(int u){
	parent[u] = u;
	r[u] = 0;
}

int find_set(int u){
	if(parent[u] == u)
		return u;
	return parent[u] = find_set(parent[u]);
}

void union_set(int u, int v){
	u = find_set(u);
	v = find_set(v);
	if(u == v)
		return;
	if(r[u]<r[v])
		swap(u,v);
	parent[v] = u;
	if(r[u] == r[v])
		++r[u];
}

int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);

	ll n;
	cin>>n;
	for(int i=1;i<=n;i++)
		make_set(i);
}