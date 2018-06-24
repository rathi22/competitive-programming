#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
#define pb push_back
#define mp make_pair
#define ip pair<ll,ll>
#define ff first
#define ss second
#define MAXN 100005
#define MOD 1000000007

struct node{
	ll val;

	void make_node(ll c){
		
	}

	void split(node &a, node &b){

	}

	void merge(node &a, node &b){
		
	}
};

ll n;
node t[4*MAXN];
ll a[MAXN];

void build(ll v, ll s, ll e){
	if(s+1 == e){
		t[v].make_node(a[s]);
		return;
	}

	ll m = (s+e)>>1;
	build(v<<1,s,m);
	build(v<<1|1,m,e);
	t[v].merge(t[v<<1],t[v<<1|1]);
}


void update_node(node &nd, ll c){
	nd.val = c;
}

void update(ll v, ll s, ll e, ll l, ll r, ll c){
	if(e<=l || r<=s)
		return;
	if(l<=s && e<=r)
		return update_node(t[v],c);
	ll lchild = v<<1;
	ll rchild = lchild+1;
	t[v].split(t[lchild],t[rchild]);
	ll m = (s+e)>>1;
	update(lchild,s,m,l,r,c);
	update(rchild,m,e,l,r,c);
	t[v].merge(t[lchild],t[rchild]);
}

node query(ll v, ll s, ll e, ll l, ll r){
	if(l<=s && e<=r)
		return t[v];
	ll lchild = v<<1;
	ll rchild = lchild+1;
	t[v].split(t[lchild],t[rchild]);
	ll m = (s+e)>>1;
	node nd,lt,rt;
	int f1=0,f2=0;
	if(m>l){
		lt = query(lchild,s,m,l,r);
		f1=1;
	}
	if(r>m){	
		rt = query(rchild,m,e,l,r);
		f2=1;
	}

	t[v].merge(t[lchild],t[rchild]);
	
	if(!f1)
		return rt;
	if(!f2)
		return lt;
	nd.merge(lt,rt);
	return nd;
}

int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);
	
	/*
	scanf("%lld",&n);
	for(int i=0;i<n;i++)
		scanf("%lld",a+i);
	
	build(1,0,n);
	*/
}