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
	ll flip,size,sum;

	void split(node &a, node &b){
		if(flip){
			a.sum = a.size-a.sum;
			b.sum = b.size-b.sum;
			a.flip ^= 1;
			b.flip ^= 1;
			flip = 0;
		}
	}

	void merge(node &a, node &b){
		sum = a.sum + b.sum;
	}
};

struct Segtree{
	node t[4*MAXN];

	void build(ll v, ll s, ll e){
		t[v].size = e-s;
		t[v].flip = 0;
		if(s+1 == e){
			t[v].sum = 0;
			return;
		}

		ll m = (s+e)>>1;
		build(v<<1,s,m);
		build(v<<1|1,m,e);
		t[v].merge(t[v<<1],t[v<<1|1]);
	}

	
	void update_node(node &nd){
		nd.sum = nd.size-nd.sum;
		nd.flip ^= 1;
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
	int tests;
	scanf("%d",&tests);
	for(int t0=0;t0<tests;t0++){
		ll nx,ny,nz,q;
		scanf("%lld %lld %lld %lld",&nx,&ny,&nz,&q);
		Segtree x,y,z;
		x.build(1,0,nx);
		y.build(1,0,ny);
		z.build(1,0,nz);

		ll type,i,j,x1,x2,y1,y2,z1,z2;
		while(q--){
			scanf("%lld",&type);
			if(type == 0){
				scanf("%lld %lld",&i,&j);
				x.update(1,0,nx,i,j+1);
			}
			else if(type == 1){
				scanf("%lld %lld",&i,&j);
				y.update(1,0,ny,i,j+1);	
			}
			else if(type == 2){
				scanf("%lld %lld",&i,&j);
				z.update(1,0,nz,i,j+1);	
			}
			else{
				scanf("%lld %lld %lld %lld %lld %lld",&x1,&y1,&z1,&x2,&y2,&z2);
				++x2;++y2;++z2;
				ll xr = x.query(1,0,nx,x1,x2).sum;
				ll yr = y.query(1,0,ny,y1,y2).sum;
				ll zr = z.query(1,0,nz,z1,z2).sum;
				ll xg = x2-x1-xr;
				ll yg = y2-y1-yr;
				ll zg = z2-z1-zr;
				printf("%lld\n", xr*yr*zr + xr*yg*zg + xg*yr*zg + xg*yg*zr);
			}
		}
	}
}
