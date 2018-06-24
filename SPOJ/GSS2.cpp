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
	ll cur,best,lazy,bestlazy;
	void make_node(ll c){
		cur = best = c;
		lazy = bestlazy = 0;
	}

	void split(node &a, node &b){
		a.bestlazy = max(a.bestlazy,a.lazy+bestlazy);
		b.bestlazy = max(b.bestlazy,b.lazy+bestlazy);
		a.lazy += lazy;
		b.lazy += lazy;
		a.best = max(a.best,a.cur+bestlazy);
		b.best = max(b.best,b.cur+bestlazy);
		a.cur += lazy;
		b.cur += lazy;
		lazy = bestlazy = 0;
	}

	void merge(node &a, node &b){
		best = max(a.best,b.best);
		cur = max(a.cur,b.cur);	
	}
};

ll n;
node t[4*MAXN];
ll a[MAXN];

void build(ll v, ll s, ll e){
	if(s+1 == e){
		t[v].make_node(0);
		return;
	}

	ll m = (s+e)>>1;
	build(v<<1,s,m);
	build(v<<1|1,m,e);
	t[v].merge(t[v<<1],t[v<<1|1]);
}

void update_node(node &nd, ll c){
	nd.lazy += c;
	nd.cur += c;
	nd.bestlazy = max(nd.bestlazy,nd.lazy);
	nd.best = max(nd.best,nd.cur);
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
	scanf("%lld",&n);
	vector<ll> last(2*MAXN,-1);
	ll prev[n];
	for(int i=0;i<n;i++){
		scanf("%lld",a+i);
		prev[i] = last[a[i]+MAXN];
		last[a[i]+MAXN] = i;
	}
	
	build(1,0,n);
	ll q,x,y;
	node nd;
	scanf("%lld",&q);
	ip queries[q];
	ip order[q];
	for(int i=0;i<q;i++){
		scanf("%lld %lld",&queries[i].ff,&queries[i].ss);
		order[i] = mp(queries[i].ss,i);
	}
	sort(order,order+q);
	vector<ll> v[MAXN];
	for(int i=0;i<q;i++)
		v[order[i].ff-1].pb(order[i].ss);

	vector<ll> ans(q);
	for(int i=0;i<n;i++){
		update(1,0,n,prev[i]+1,i+1,a[i]);
		for(int j=0;j<v[i].size();j++)
			ans[v[i][j]] = query(1,0,n,queries[v[i][j]].ff-1,i+1).best;
	}

	for(int i=0;i<q;i++)
		printf("%lld\n",ans[i]);
}	