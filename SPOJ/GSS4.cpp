#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
#define sc(x) scanf("%lld",&x)
#define sc2(x,y) scanf("%lld %lld",&x,&y)
#define sc3(x,y,z) scanf("%lld %lld %lld",&x,&y,&z)
#define pb push_back
#define mp make_pair
#define ip pair<ll,ll>
#define ff first
#define ss second
#define MAXN 100005
#define MOD 1000000007

struct node{
	ll lazy,sum;
	int all_one;

	node(){
		all_one = 0;
		lazy = 0;
		sum = 0;
	}

	void split(node &a, node &b){
		if(lazy>0){
			a.lazy += lazy;
			b.lazy += lazy;
			lazy = 0;
		}
	}

	void merge(node &a, node &b){
		sum = a.sum + b.sum;
		if(a.all_one && b.all_one)
			all_one = 1;
	}
};

struct Segtree{
	node t[4*MAXN];
	ll a[MAXN];

	void build(ll v, ll s, ll e){
		if(s+1 == e){
			t[v].sum = a[s];
			if(t[v].sum == 1)
				t[v].all_one = 1;
			return;
		}

		ll m = (s+e)>>1;
		build(v<<1,s,m);
		build(v<<1|1,m,e);
		t[v].merge(t[v<<1],t[v<<1|1]);
	}

	
	void update_node(node &nd){
		if(!nd.all_one)
			++nd.lazy;
	}

	void update(ll v, ll s, ll e, ll l, ll r){
		if(e<=l || r<=s)
			return;
		if(l<=s && e<=r)
			return update_node(t[v]);
		ll lchild = v<<1;
		ll rchild = lchild+1;
		t[v].split(t[lchild],t[rchild]);
		ll m = (s+e)>>1;
		update(lchild,s,m,l,r);
		update(rchild,m,e,l,r);
		t[v].merge(t[lchild],t[rchild]);
	}

	node query(ll v, ll s, ll e, ll l, ll r){
		if(l<=s && e<=r){
			if(t[v].all_one)
				return t[v];
			else if(s+1 == e){
				while(t[v].lazy>0){
					--t[v].lazy;
					t[v].sum = sqrt(t[v].sum);
				}
				if(t[v].sum == 1)
					t[v].all_one = 1;
				return t[v];
			}
		}
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
};

int main(){
	ll n,q,l,r;	
	int cnt = 1;
	while(sc(n)!=EOF){
		printf("Case #%d:\n", cnt++);
		Segtree st;
		for(int i=0;i<n;i++)
			sc(st.a[i]);
		st.build(1,0,n);
		sc(q);
		int type;
		while(q--){
			scanf("%d",&type);
			sc2(l,r);
			if(l>r)
				swap(l,r);
			if(type)
				printf("%lld\n",st.query(1,0,n,l-1,r).sum);
			else
				st.update(1,0,n,l-1,r);
		}
		printf("\n");
	}
}
