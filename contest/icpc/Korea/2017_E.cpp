#include <bits/stdc++.h>
#define MAX_V 103
#define INF 987654321
#define sz(x) ((int)(x).size())
using namespace std;
using pr = pair<int, int>;
using tr = pair<int, pr>;

struct edge {
    int v, c, rev;
    edge(int v, int c, int rev): v(v), c(c), rev(rev) {}
};

int N, M, idx[MAX_V], source, sink, lev[MAX_V];
vector<edge> v[MAX_V];
vector<tr> E;

void add_edge(int s, int e, int c) {
    v[s].push_back(edge(e, c, sz(v[e])));
    v[e].push_back(edge(s, 0, sz(v[s]) - 1));
}

bool bfs() {
    queue<int> q;
    for(int i=1; i<=N; i++) lev[i] = -1;
    lev[source] = 0;
    q.push(source);
    while(!q.empty()) {
        int u = q.front(); q.pop();
        for(auto it : v[u]) {
            if(lev[it.v] < 0 && it.c > 0) {
                lev[it.v] = lev[u] + 1;
                q.push(it.v);
            }
        }
    }
    return ~lev[sink];
}

int dfs(int x, int c) {
    if(x == sink) return c;
    for(int &i=idx[x]; i<sz(v[x]); i++) {
        if(lev[v[x][i].v] == lev[x] + 1 && v[x][i].c > 0) {
            int flow = dfs(v[x][i].v, min(c, v[x][i].c));
            if(flow > 0) {
                v[x][i].c -= flow;
                v[v[x][i].v][v[x][i].rev].c += flow;
                return flow;
            }
        }
    }
    return 0;
}

int main() {
    scanf("%d %d", &N, &M);
    for(int i=0, x, y, z; i<M; i++) {
        scanf("%d %d %d", &x, &y, &z);
        E.push_back(tr(z, pr(x, y)));
    }
    sort(E.begin(), E.end());
    int ans = 0;
    for(int i=0; i<sz(E); i++) {
        for(int i=1; i<=N; i++) v[i].clear();
        for(int j=0; j<i; j++) if(E[j].first < E[i].first) add_edge(E[j].second.first, E[j].second.second, 1), add_edge(E[j].second.second, E[j].second.first, 1);
        memset(lev, 0, sizeof(lev));
        source = E[i].second.first, sink = E[i].second.second;
        while(bfs()) {
            memset(idx, 0, sizeof(idx));
            for(int r=1; r; ans+=r) r = dfs(source, INF);
        }
    }
    printf("%d\n", ans);
}
