#include <bits/stdc++.h>
#define MAX_N 100005
#define MAX_LN 18
using namespace std;
using pr = pair<int, int>;
using ll = long long;

struct Z { ll v, lz; };

struct segtree {
    Z tree[MAX_N*8];
    int base;
    void init(int x) { for(base=1; base<x; base<<=1); }
    void update(int x, ll y, bool arr = 0) {
        if(!arr) x += base - 1;
        while(x) tree[x].v += y, x >>= 1;
    }
    int f(int x) {
        int res = 1;
        while(base > x) x <<= 1, res <<= 1;
        return res;
    }
    void g(int x) {
    	if(x == 0) return;
    	g(x / 2);
    	tree[x*2].lz += tree[x].lz, tree[x*2+1].lz += tree[x].lz;
    	tree[x].v += tree[x].lz * f(x);
    	tree[x].lz = 0;
    }
    ll RMQ(int x, int y) {
        ll res = 0LL;
        x += base - 1, y += base - 1;
        while(x < y) {
            if(x & 1) g(x), res += tree[x].v, x++;
            if(!(y & 1)) g(y), res += tree[y].v, y--;
            x >>= 1, y >>= 1;
        }
        if(x == y) g(y), res += tree[y].v;
        return res;
    }
    void modify(int x, int y, ll v) {
        x += base - 1, y += base - 1;
        while(x < y) {
            if(x & 1) tree[x].lz += v, update(x / 2, v * f(x), 1), x++;
            if(!(y & 1)) tree[y].lz += v, update(y / 2, v * f(y), 1), y--;
            x >>= 1, y >>= 1;
        }
        if(x == y) tree[x].lz += v, update(y / 2, v * f(y), 1);
    }
} seg;

int N, Q, sz[MAX_N], lev[MAX_N], st[MAX_N][MAX_LN];
int U[MAX_N], V[MAX_N], W[MAX_N], cost[MAX_N];
int dfn[MAX_N], HLD, head[MAX_N], DFS, G[MAX_N];
vector<pr> v[MAX_N];

void dfs(int x, int p) {
    lev[x] = lev[p] + 1;
    sz[x] = 1;
    st[x][0] = p;
    for(auto it : v[x]) if(it.first != p) dfs(it.first, x), cost[it.first] = it.second;
}

void hld(int x, int p) {
    sort(v[x].begin(), v[x].end(), [](const pr &X, const pr &Y) { return sz[X.first] > sz[Y.first]; });
    int cnt = 0;
    for(auto it : v[x]) if(it.first != p) {
        int u = it.first;
        G[u] = (HLD += !!cnt);
        dfn[u] = ++DFS;
        if(cnt++) head[HLD] = u;
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

void edit(int x, int y) {
    if(x == y) return;
    while(G[x] != G[y]) {
        int h = head[G[x]];
        seg.modify(dfn[h], dfn[x], 1LL);
        x = st[h][0];
    }
    seg.modify(dfn[y] + 1, dfn[x], 1LL);
}

ll query(int x, int y) {
    if(x == y) return 0LL;
    ll res = 0LL;
    while(G[x] != G[y]) {
        int h = head[G[x]];
        res += seg.RMQ(dfn[h], dfn[x]);
        x = st[h][0];
    }
    res += seg.RMQ(dfn[y] + 1, dfn[x]);
    return res;
}

int main() {
    scanf("%d %d", &N, &Q);
    seg.init(N);
    for(int i=1; i<N; i++) {
        scanf("%d %d", U+i, V+i);
        v[U[i]].push_back(pr(V[i], W[i]));
        v[V[i]].push_back(pr(U[i], W[i]));
    }
    dfs(1, 0);
    for(int i=1; i<MAX_LN; i++) for(int j=1; j<=N; j++) st[j][i] = st[st[j][i-1]][i-1];
    dfn[1] = head[1] = G[1] = HLD = DFS = 1;
    hld(1, 0);
    while(Q--) {
        int x, y;
        char q;
        scanf(" %c %d %d", &q, &x, &y);
        int lca = LCA(x, y);
        if(q == 'P') edit(x, lca), edit(y, lca);
        else printf("%lld\n", query(x, lca) + query(y, lca));
    }
}
