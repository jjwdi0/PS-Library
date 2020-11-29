#include <bits/stdc++.h>
#define init(x) (x).resize(V+1)
using namespace std;
using pr = pair<int, int>;

struct MCMF {
    int V, src, snk;
    vector<vector<int>> C, F, W, v;
    vector<int> dist, pre;
    vector<bool> inQ;
    queue<int> q;

    MCMF() {}
    MCMF(int _V, int _src, int _snk) {
        V = _V, src = _src, snk = _snk;
        init(C), init(F), init(W), init(v), init(dist), init(pre), init(inQ);
        for(int i=1; i<=V; i++) init(C[i]), init(F[i]), init(W[i]);
    }

    void add_edge(int s, int t, int w, int c) {
        C[s][t] = c;
        W[s][t] = w, W[t][s] = -w;
        v[s].push_back(t), v[t].push_back(s);
    }

    int SPFA() {
        for(int i=src; i<=snk; i++) dist[i] = 1e9, pre[i] = -1;
        dist[src] = 0;
        q.push(src);
        inQ[src] = 1;
        while(!q.empty()) {
            int u = q.front(); q.pop();
            inQ[u] = 0;
            for(auto it : v[u]) if(C[u][it] > F[u][it] && dist[it] > dist[u] + W[u][it]) {
                dist[it] = dist[u] + W[u][it];
                pre[it] = u;
                if(!inQ[it]) q.push(it), inQ[it] = 1;
            }
        }
        return pre[snk];
    }

    pr maxflow() {
        int ans = 0, cost = 0;
        while(~SPFA()) {
            int res = 1e9;
            for(int u=snk; u!=src; u=pre[u]) res = min(res, C[pre[u]][u] - F[pre[u]][u]);
            for(int u=snk; u!=src; u=pre[u]) {
                cost += res * W[pre[u]][u];
                F[pre[u]][u] += res;
                F[u][pre[u]] -= res;
            }
            ans++;
        }
        return pr(ans, cost);
    }
};

int T, N, M, A[505][505], B[505], C[505];

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d %d", &N, &M);
        MCMF mcmf = MCMF(N + N + 2, 1, N + N + 2);
        for(int i=1; i<=N; i++) for(int j=1; j<=N; j++) A[i][j] = (i == j ? 0 : 1e9);
        for(int i=0, x, y; i<M; i++) {
            scanf("%d %d", &x, &y);
            A[x][y] = A[y][x] = 1;
        }
        for(int j=1; j<=N; j++) for(int i=1; i<=N; i++) for(int k=1; k<=N; k++) A[i][k] = min(A[i][k], A[i][j] + A[j][k]);
        for(int i=1; i<=N; i++) scanf("%d", B+i);
        for(int i=1; i<=N; i++) scanf("%d", C+i);
        for(int i=1; i<=N; i++) for(int j=1; j<=N; j++) if(B[i] == C[j]) mcmf.add_edge(i + 1, j + N + 1, A[i][j], 1);
        for(int i=1; i<=N; i++) {
            mcmf.add_edge(mcmf.src, i + 1, 0, 1);
            mcmf.add_edge(i + N + 1, mcmf.snk, 0, 1);
        }
        printf("%d\n", mcmf.maxflow().second / 2);
    }
}
