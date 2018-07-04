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
#define ipp pair<ip,ip>
#define ff first
#define ss second
#define MAXN 200005
#define MOD 1000000007
#define INF 1e18

struct BIT{
	int *t;
	int N;
	BIT(int n){
		N = n;
		t = new int[N+1];
		for(int i=1;i<=N;i++)
			t[i]=0;
	}

	void update(int idx, int val){
		while(idx<=N){
			t[idx] += val;
			idx += (idx&-idx);
		}
	}

	int query(int idx){
		int sum=0;
		while(idx>0){
			sum += t[idx];
			idx -= (idx&-idx);
		}
		return sum;
	}
};

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);

	int n,q;
	scanf("%d",&n);
	BIT b(n);
	ip a[n];
	for(int i=0;i<n;i++){
		sc(a[i].ff);
		a[i].ss = i+1;
	}
	sort(a,a+n);

	scanf("%d",&q);
	ipp queries[q];
	for(int i=0;i<q;i++){
		sc3(queries[i].ss.ff,queries[i].ss.ss,queries[i].ff.ff);
		queries[i].ff.ss = i;
	}
	int ans[q];

	sort(queries,queries+q);
	int i=0,j=0;
	while(i<n && j<q){
		if(a[i].ff<=queries[j].ff.ff){
			b.update(a[i].ss,1);
			++i;
		}
		else{
			ans[queries[j].ff.ss] = 1+queries[j].ss.ss-queries[j].ss.ff-b.query(queries[j].ss.ss)+b.query(queries[j].ss.ff-1);
			++j;
		}
	}

	while(j<q){
		ans[queries[j].ff.ss] = 0;
		++j;
	}

	for(j=0;j<q;j++)
		printf("%d\n",ans[j]);
}
