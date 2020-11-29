#include <bits/stdc++.h>
#define MAX_N 100005
#define MAX_LN 18
using namespace std;
using pr = pair<int, int>;

struct BIT {
	int tree[100005], base;
	void init(int x) { base = x; }
	void add(int x, int y) { while(x <= base) tree[x] ^= y, x += x & -x; }
	int q(int x) {
		int res = 0;
		while(x) res ^= tree[x], x -= x & -x;
		return res;
	}
} bit;

struct query {
	int a, b, c, idx;
	bool operator < (const query &X) const { return c < X.c; }
} T[MAX_N];

int N, Q, A[MAX_N], sz[MAX_N], lev[MAX_N], st[MAX_N][MAX_LN];
int dfn[MAX_N], HLD, head[MAX_N], DFS, G[MAX_N];
vector<int> v[MAX_N], col[MAX_N];
set<pr> s[MAX_N];

void dfs(int x, int p) {
    lev[x] = lev[p] + 1;
    sz[x] = 1;
    st[x][0] = p;
    for(auto it : v[x]) if(it != p) dfs(it, x), sz[x] += sz[it];
}

void hld(int x, int p) {
    sort(v[x].begin(), v[x].end(), [](const int &X, const int &Y) { return sz[X] > sz[Y]; });
    int cnt = 0;
    for(auto it : v[x]) if(it != p) {
        int u = it;
        G[u] = (HLD += !!cnt);
        dfn[u] = ++DFS;
        head[HLD] = (cnt++ ? u : head[HLD]);
        hld(u, x);
    }
}

int LCA(int s, int e) {
    if(lev[s] > lev[e]) swap(s, e);
    for(int i=0; i<MAX_LN; i++) if((lev[e] - lev[s]) & (1 << i)) e = st[e][i];
    if(s == e) return s;
    for(int i=MAX_LN-1; ~i; i--) if(st[s][i] != st[e][i]) s = st[s][i], e = st[e][i];
    return st[s][0];
}

int query(int x, int y) {
	if(x == y) return A[x];
    int res = 0;
    while(G[x] != G[y]) {
		int h = head[G[x]];
		res ^= bit.q(dfn[x]) ^ bit.q(dfn[h] - 1);
        x = st[h][0];
    }
	return res ^ bit.q(dfn[x]) ^ bit.q(dfn[y] - 1);
}

int main() {
    scanf("%d %d", &N, &Q);
	bit.init(N);
	for(int i=1; i<=N; i++) scanf("%d", A+i);
    for(int i=1, x, y; i<N; i++) {
        scanf("%d %d", &x, &y);
        v[x].push_back(y);
        v[y].push_back(x);
    }
    dfs(1, 0);
    for(int i=1; i<MAX_LN; i++) for(int j=1; j<=N; j++) st[j][i] = st[st[j][i-1]][i-1];
    head[1] = G[1] = HLD = DFS = 1;
    hld(1, 0);
	dfn[1] = 1;
	for(int i=1; i<=N; i++) bit.add(dfn[i], A[i]);
	while(Q--) {
		int q, x, y;
		scanf("%d %d %d", &q, &x, &y);
		if(q == 1) {
			bit.add(dfn[x], y ^ A[x]);
			A[x] = y;
		} else {
			int lca = LCA(x, y);
			printf("%d\n", query(x, lca) ^ query(y, lca) ^ A[lca]);
		}
	}
}
