#include <bits/stdc++.h>
#define sz(x) ((int)(x).size())
#define INF 987654321
using namespace std;

struct edge {
    int v, c, rev;
    edge(int v, int c, int rev): v(v), c(c), rev(rev) {}
};

int T, N, M, V, A[55][55], num[55][55], d[4] = { 0,0,1,-1 }, idx[2505], source, sink, lev[2505];
vector<edge> v[2505];

void add_edge(int s, int e, int c) {
    v[s].push_back(edge(e, c, sz(v[e])));
    v[e].push_back(edge(s, 0, sz(v[s]) - 1));
}

bool bfs() {
    queue<int> q;
    for(int i=1; i<=V; i++) lev[i] = -1;
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
    scanf("%d", &T);
    while(T--) {
        scanf("%d %d", &N, &M);
        V = N * M + 2;
        source = V - 1, sink = V;
        int ans = 0;
        for(int i=1; i<=N; i++) for(int j=1; j<=M; j++) scanf("%d", &A[i][j]), ans += A[i][j];
        for(int i=1; i<=V; i++) v[i].clear();
        for(int i=1; i<=N; i++) for(int j=1; j<=M; j++) {
            if(!((i + j) % 2)) add_edge(source, (i - 1) * M + j, A[i][j]);
            else add_edge((i - 1) * M + j, sink, A[i][j]);
        }
        for(int i=1; i<=N; i++) for(int j=1; j<=M; j++) if((i + j) % 2 == 0) {
            for(int k=0; k<4; k++) {
                int x = i + d[k], y = j + d[3-k];
                if(x < 1 || y < 1 || x > N || y > M) continue;
                add_edge((i - 1) * M + j, (x - 1) * M + y, 1001);
            }
        }
        while(bfs()) {
            for(int i=1; i<=V; i++) idx[i] = 0;
            for(int r=1; r; ans-=r) r = dfs(source, INF);
        }
        printf("%d\n", ans);
    }
}
