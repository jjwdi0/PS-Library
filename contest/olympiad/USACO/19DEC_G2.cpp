#include <bits/stdc++.h>
#define MAX_N 100005
#define MAX_LN 18
using namespace std;

struct BIT {
	int tree[MAX_N], base;
	void init(int x) { base = x; }
	void add(int x, int y) { while(x <= base) tree[x] += y, x += x & -x; }
	int q(int x) {
		int res = 0;
		while(x) res += tree[x], x -= x & -x;
		return res;
	}
} bit;

struct query {
	int a, b, c, idx;
	bool operator < (const query &X) const { return c < X.c; }
} T[MAX_N];

int N, Q, sz[MAX_N], lev[MAX_N], st[MAX_N][MAX_LN], A[MAX_N];
int dfn[MAX_N], HLD, head[MAX_N], DFS, G[MAX_N];
vector<int> v[MAX_N], col[MAX_N];
bool ans[MAX_N];

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
    if(x == y) return bit.q(dfn[x]) - bit.q(dfn[x] - 1);
    int res = 0;
    while(G[x] != G[y]) {
		// assert(lev[x] >= lev[y]);
        int h = head[G[x]];
        res += bit.q(dfn[x]) - bit.q(dfn[h] - 1);
        x = st[h][0];
    }
    return res + bit.q(dfn[x]) - bit.q(dfn[y] - 1);
}

int main() {
    scanf("%d %d", &N, &Q);
    bit.init(N);
	for(int i=1; i<=N; i++) scanf("%d", A+i), col[A[i]].push_back(i);
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
	for(int i=1, x, y, z; i<=Q; i++) {
		scanf("%d %d %d", &x, &y, &z);
		T[i] = { x, y, z, i };
	}
	sort(T + 1, T + Q + 1);
	for(int i=1; i<=Q; ) {
		int j = i;
		while(j <= Q && T[j].c == T[i].c) j++;
		for(auto it : col[T[i].c]) bit.add(dfn[it], 1);
		for(int k=i; k<j; k++) {
			int lca = LCA(T[k].a, T[k].b);
			ans[T[k].idx] = !!(query(T[k].a, lca) + query(T[k].b, lca));
		}
		for(auto it : col[T[i].c]) bit.add(dfn[it], -1);
		i = j;
	}
    for(int i=1; i<=Q; i++) printf("%d", ans[i]);
}
