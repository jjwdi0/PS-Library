#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct seglazy {
	ll sum[1<<20], mn[1<<20], lazy[1<<20];
	void init(int node, int s, int e, int *A) {
		if(s == e) {
			sum[node] = mn[node] = A[s];
			return;
		}
		int mid = (s + e) >> 1;
		init(node * 2, s, mid, A), init(node * 2 + 1, mid + 1, e, A);
		sum[node] = sum[node*2] + sum[node*2+1];
		mn[node] = min(mn[node*2], mn[node*2+1]);
	}
	void push(int node, int s, int e) {
		if(lazy[node]) {
			ll x = lazy[node];
			sum[node] += 1LL * (e - s + 1) * x;
			mn[node] += x;
			lazy[node] = 0LL;
			if(s < e) lazy[node*2] += x, lazy[node*2+1] += x;
		}
	}
	void update(int node, int s, int e, int l, int r, int x) {
		push(node, s, e);
		if(e < l || r < s) return;
		if(l <= s && e <= r) {
			lazy[node] += x;
			push(node, s, e);
			return;
		}
		int mid = (s + e) >> 1;
		update(node * 2, s, mid, l, r, x), update(node * 2 + 1, mid + 1, e, l, r, x);
		sum[node] = sum[node*2] + sum[node*2+1];
		mn[node] = min(mn[node*2], mn[node*2+1]);
	}
	ll RMQ(int node, int s, int e, int l, int r) {
		if(e < l || r < s) return 1e18;
		push(node, s, e);
		if(l <= s && e <= r) return mn[node];
		int mid = (s + e) >> 1;
		return min(RMQ(node * 2, s, mid, l, r), RMQ(node * 2 + 1, mid + 1, e, l, r));
	}
	ll RSQ(int node, int s, int e, int l, int r) {
		if(e < l || r < s) return 0LL;
		push(node, s, e);
		if(l <= s && e <= r) return sum[node];
		int mid = (s + e) >> 1;
		return RSQ(node * 2, s, mid, l, r) + RSQ(node * 2 + 1, mid + 1, e, l, r);
	}
} seg;

int N, Q, A[200005];

int main() {
	scanf("%d %d", &N, &Q);
	for(int i=1; i<=N; i++) scanf("%d", A+i);
	seg.init(1, 1, N, A);
	while(Q--) {
		char q;
		int x, y, z;
		scanf(" %c", &q);
		if(q == 'M') {
			scanf("%d %d", &x, &y);
			printf("%lld\n", seg.RMQ(1, 1, N, x, y));
		} else if(q == 'S') {
			scanf("%d %d", &x, &y);
			printf("%lld\n", seg.RSQ(1, 1, N, x, y));
		} else {
			scanf("%d %d %d", &x, &y, &z);
			seg.update(1, 1, N, x, y, z);
		}
	}
}