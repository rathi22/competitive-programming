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
	ll best,pre,suf,li,ri;
	void split(node &a, node &b){
		
	}

	void merge(node &lt, node &rt){
		li = lt.li;
		ri = rt.ri;
		best = max(lt.best,rt.best);
		suf = rt.suf;
		pre = lt.pre;
		if(lt.ri == rt.li){
			best = max(best,lt.suf+rt.pre);
			if(lt.li == lt.ri)
				pre = lt.pre+rt.pre;
			if(rt.li == rt.ri)
				suf = rt.suf+lt.suf;
		}
	}
};

struct Segtree{
	node t[4*MAXN];
	ll a[MAXN];

	void build(ll v, ll s, ll e){
		t[v].li = a[s];	// Value of left-most in segment
		t[v].ri = a[e-1];	// Value of right-most in segment
		if(s+1 == e){
			t[v].best = t[v].pre = t[v].suf = 1;
			return;
		}

		ll m = (s+e)>>1;
		build(v<<1,s,m);
		build(v<<1|1,m,e);
		t[v].merge(t[v<<1],t[v<<1|1]);
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
};

int main(){
	ll n,q;	
	while(1){
		sc(n);
		if(n==0)
			break;
		sc(q);
		Segtree st;
		for(int i=0;i<n;i++)
			sc(st.a[i]);
		st.build(1,0,n);
		ll l,r;
		while(q--){
			sc2(l,r);
			printf("%lld\n", st.query(1,0,n,l-1,r).best);
		}
	}
}
