#include <bits/stdc++.h>
using namespace std;

struct node { int lr, xr, lx, xx; };
node merge(node l, node r) {
	int lr = max({ l.lr + r.xr, l.lx + r.lr, l.lx + r.xr });
	int xr = max({ l.xx + r.lr, l.xx + r.xr, l.xr + r.xr });
	int lx = max({ l.lx + r.lx, l.lx + r.xx, l.lr + r.xx });
	int xx = max({ l.xr + r.xx, l.xx + r.lx, l.xx + r.xx });
	return { lr, xr, lx, xx };
}

struct segtree {
	node tree[161616];
	int base;
	void init(int x) { for(base=1; base<x; base<<=1); }
	void update(int x, int y) {
		x += base - 1;
		tree[x] = { y, 0, 0, 0 }, x >>= 1;
		while(x) tree[x] = merge(tree[x+x], tree[x+x+1]), x >>= 1;
	}
	int query() { return max({ tree[1].lr, tree[1].lx, tree[1].xr, tree[1].xx }); }
} seg;

int N, Q;

int main() {
	scanf("%d %d", &N, &Q);
	seg.init(N);
	for(int i=1, x; i<=N; i++) {
		scanf("%d", &x);
		seg.update(i, x);
	}
	long long ans = 0;
	while(Q--) {
		int x, y;
		scanf("%d %d", &x, &y);
		seg.update(x, y);
		ans += seg.query();
	}
	printf("%lld\n", ans);
}