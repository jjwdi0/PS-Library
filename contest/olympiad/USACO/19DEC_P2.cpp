#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Segtree {
	ll tree[444444], lazy[444444];
	void push(int node, int s, int e) {
		if(lazy[node]) {
			ll x = lazy[node];
			lazy[node] = 0LL;
			tree[node] += 1LL * (e - s + 1) * x;
			if(s < e) lazy[node*2] += x, lazy[node*2+1] += x;
		}
	}
	void update(int node, int s, int e, int l, int r, ll x) {
		push(node, s, e);
		if(e < l || r < s) return;
		if(l <= s && e <= r) {
			lazy[node] += x;
			push(node, s, e);
			return;
		}
		int mid = (s + e) >> 1;
		update(node * 2, s, mid, l, r, x);
		update(node * 2 + 1, mid + 1, e, l, r, x);
		tree[node] = tree[node*2] + tree[node*2+1];
	}
	ll query(int node, int s, int e, int l, int r) {
		push(node, s, e);
		if(e < l || r < s) return 0LL;
		if(l <= s && e <= r) return tree[node];
		int mid = (s + e) >> 1;
		return query(node * 2, s, mid, l, r) + query(node * 2 + 1, mid + 1, e, l, r);
	}
} seg;

int N, Q, dfn[100005], rdfn[100005], HLD, DFS, sz[100005], head[100005], G[100005], par[100005];
set<int> s[100005];
vector<int> v[100005];

void dfs(int x, int p) {
	sz[x] = 1, par[x] = p;
	for(int it : v[x]) if(it != p) {
		dfs(it, x);
		sz[x] += sz[it];
	}
}

void hld(int x, int p) {
    sort(v[x].begin(), v[x].end(), [](const int &X, const int &Y) { return sz[X] > sz[Y]; });
    int cnt = 0;
    for(auto it : v[x]) if(it != p) {
        int u = it;
        G[u] = (HLD += !!cnt);
        dfn[u] = ++DFS;
		rdfn[DFS] = u;
        head[HLD] = (cnt++ ? u : head[HLD]);
        hld(u, x);
    }
}

bool get(int x, int y, int c) {
    while(G[x] != G[y]) {
		int h = head[G[x]];
		auto it = s[c].lower_bound(dfn[h]);
		if(it != s[c].end() && *it <= dfn[x]) return 1;
        x = par[h];
    }
	auto it = s[c].lower_bound(dfn[y]);
	return it != s[c].end() && *it <= dfn[x];
}

int main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> N >> Q;
	for(int i=1, x, y; i<N; i++) {
		cin >> x >> y;
		v[x].push_back(y), v[y].push_back(x);
	}
	dfs(1, 0);
	head[1] = G[1] = HLD = DFS = dfn[1] = rdfn[1] = 1;
	hld(1, 0);
	while(Q--) {
		int q, x, y;
		cin >> q;
		if(q == 1) {
			cin >> x >> y;
			int l = dfn[x], r = dfn[x] + sz[x] - 1;
			if(get(x, 1, y)) continue;
			auto it1 = s[y].lower_bound(l), it2 = s[y].upper_bound(r);
			for(auto it = it1; it != it2; it++) {
				int x = *it;
				int ll = x, rr = x + sz[rdfn[x]] - 1;
				seg.update(1, 1, N, ll, rr, -1LL);
			}
			s[y].erase(it1, it2);
			seg.update(1, 1, N, l, r, 1LL);
			s[y].insert(dfn[x]);
		} else {
			cin >> x;
			cout << seg.query(1, 1, N, dfn[x], dfn[x] + sz[x] - 1) << "\n";
		}
	}
}