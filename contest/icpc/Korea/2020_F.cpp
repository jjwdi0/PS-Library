#include <bits/stdc++.h>
#define INIT(X) memset((X),0,sizeof((X)))
using namespace std;

const int MAXN = 100010;

struct DominatorTree {
	vector<int> E[MAXN], RE[MAXN], rdom[MAXN];
	int S[MAXN], RS[MAXN], cs;
	int par[MAXN], val[MAXN], sdom[MAXN], rp[MAXN], dom[MAXN];

	void clear(int n) {
		cs = 0;
		INIT(par); INIT(val); INIT(sdom); INIT(rp); INIT(dom); INIT(S); INIT(RS);
		for(int i=0; i<=n; i++) E[i].clear(), RE[i].clear(), rdom[i].clear();
	}
	void add_edge(int x, int y) { E[x].push_back(y); }
	void Union(int x, int y) { par[x] = y; }
	int Find(int x, int c = 0) {
		if(par[x] == x) return c ? -1 : x;
		int p = Find(par[x], 1);
		if(p == -1) return c ? par[x] : val[x];
		if(sdom[val[x]] > sdom[val[par[x]]]) val[x] = val[par[x]];
		par[x] = p;
		return c ? p : val[x];
	}
	void dfs(int x) {
		RS[ S[x] = ++cs ] = x;
		par[cs] = sdom[cs] = val[cs] = cs;
		for(int e : E[x]) {
			if(S[e] == 0) dfs(e), rp[S[e]] = S[x];
			RE[S[e]].push_back(S[x]);
		}
	}
	int solve(int s, int *up) {
		dfs(s);
		for(int i=cs; i; i--) {
			for(int e : RE[i]) sdom[i] = min(sdom[i], sdom[Find(e)]);
			if(i > 1) rdom[sdom[i]].push_back(i);
			for(int e : rdom[i]) {
				int p = Find(e);
				if(sdom[p] == i) dom[e] = i;
				else dom[e] = p;
			}
			if(i > 1) Union(i, rp[i]);
		}
		for(int i=2; i<=cs; i++) if(sdom[i] != dom[i]) dom[i] = dom[dom[i]];
		for(int i=2; i<=cs; i++) up[RS[i]] = RS[dom[i]];
		return cs;
	}
} DT;

int N, M, K, Q, par[MAXN];

int main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> N >> K >> M;
	for(int i=0, x, y; i<M; i++) {
		cin >> x >> y;
		DT.add_edge(x + 1, y + 1);
	}
	for(int i=1; i<=K; i++) DT.add_edge(1, i + 1);
	DT.solve(1, par);
	int ans = 0;
	for(int i=1; i<=N; i++) if(par[i+1] == 1) ans++;
	cout << ans << "\n";
}