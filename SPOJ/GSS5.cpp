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
	ll pre,suf,total,best;

	node(){
		pre = suf = total = best = 0;
	}

	void split(node &a, node &b){
		
	}

	void merge(node &a, node &b){
		total = a.total+b.total;
		pre = max(a.pre,a.total+b.pre);
		suf = max(b.suf,a.suf+b.total);
		best = max(max(a.best,b.best),a.suf+b.pre);
	}
};

struct Segtree{
	node t[4*MAXN];
	ll a[MAXN];

	void build(ll v, ll s, ll e){
		if(s+1 == e){
			t[v].pre = t[v].suf = t[v].total = t[v].best = a[s];
			return;
		}

		ll m = (s+e)>>1;
		build(v<<1,s,m);
		build(v<<1|1,m,e);
		t[v].merge(t[v<<1],t[v<<1|1]);
	}

	node query(ll v, ll s, ll e, ll l, ll r){
		if(l==r)
			return node();
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
	ll n,q,l1,r1,l2,r2,tests,ans;
	sc(tests);	
	while(tests--){
		sc(n);
		Segtree st;
		for(int i=0;i<n;i++)
			sc(st.a[i]);
		st.build(1,0,n);
		sc(q);
		while(q--){
			sc2(l1,r1);
			sc2(l2,r2);
			--l1;--r1;--l2;--r2;
			if(r1<l2)
				ans = st.query(1,0,n,l1,r1+1).suf+st.query(1,0,n,r1+1,l2).total+st.query(1,0,n,l2,r2+1).pre;
			else{
				ans = st.query(1,0,n,l1,l2).suf + st.query(1,0,n,l2,r2+1).pre;
				ans = max(ans,st.query(1,0,n,l2,r1+1).suf + st.query(1,0,n,r1+1,r2+1).pre);
				ans = max(ans,st.query(1,0,n,l2,r1+1).best);
			}
			printf("%lld\n",ans);
		}
	}
}
