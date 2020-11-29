#include <bits/stdc++.h>
#define log_N 18
#define MAX_N 100005
#define MAX_M 300005
using namespace std;
typedef long long ll;
typedef pair<int, int> pr;

struct E {
    int u, v, x, idx, vtx;
    bool operator < (const E &a) const{
        return x == a.x ? idx < a.idx : x < a.x;
    }
}A[MAX_M];

int N, M, par[MAX_N], sp[MAX_N][log_N], col[MAX_M];
ll output[MAX_M], ans;
bool chk[MAX_M];
vector<int> v[MAX_N];
int dep[MAX_N], num[MAX_N];

int f(int x) {return par[x] = (x == par[x] ? x : f(par[x]));}

void dfs(int x, int p) {
    sp[x][0] = par[x] = p;
    dep[x] = dep[p] + 1;
    for(int i : v[x]) {
        if(A[i].u == p || A[i].v == p) num[x] = A[i].idx, A[i].vtx = x;
        else dfs(A[i].u == x ? A[i].v : A[i].u, x);
    }
}

int LCA(int u, int v) {
    if(dep[u] < dep[v]) swap(u, v);
    for(int i=0; i<log_N; i++) if((dep[u] - dep[v]) & (1 << i)) u = sp[u][i];
    if(u == v) return u;
    for(int i=log_N-1; ~i; i--) if(sp[u][i] != sp[v][i]) u = sp[u][i], v = sp[v][i];
    return sp[u][0];
}

int paint(int s, int e, int c) {
    if(dep[s] <= dep[e]) return s;
    if(col[num[s]] < 0) col[num[s]] = c;
    return par[s] = paint(par[s], e, c);
}

int main() {
    scanf("%d %d", &N, &M);
    for(int i=1; i<=M+N-1; i++) col[i] = -1;
    for(int i=1; i<=N; i++) par[i] = i;
    for(int i=1; i<N; i++) {
        scanf("%d %d", &A[i+M].u, &A[i+M].v);
        A[i+M].x = 1;
        A[i+M].idx = i + M;
    }
    for(int i=1; i<=M; i++) {
        scanf("%d %d %d", &A[i].u, &A[i].v, &A[i].x);
        A[i].idx = i;
    }
    int _M = M;
    M += N - 1;
    sort(A+1, A+M+1);
    int cnt = 1;
    for(int i=1; i<=M; i++) {
        if(f(A[i].u) == f(A[i].v)) continue;
        v[A[i].u].push_back(i);
        v[A[i].v].push_back(i);
        par[f(A[i].u)] = A[i].v;
        cnt++;
        chk[A[i].idx] = 1;
        ans += A[i].x;
        if(cnt == N) break;
    }
    for(int i=1; i<=M; i++) if(!chk[i]) output[i] = ans;
    dfs(1, 0);
    for(int i=1; i<log_N; i++) for(int j=1; j<=N; j++) sp[j][i] = sp[sp[j][i-1]][i-1];
    for(int i=1; i<=M; i++) {
        if(chk[A[i].idx]) continue;
        int u = LCA(A[i].u, A[i].v);
        paint(A[i].u, u, A[i].x);
        paint(A[i].v, u, A[i].x);
    }
    for(int i=1; i<=M; i++) if(chk[A[i].idx]) {
        if(col[A[i].idx] < 0) output[A[i].idx] = -1;
        else output[A[i].idx] = ans - (ll)A[i].x + (ll)col[A[i].idx];
    }
    for(int i=1; i<N; i++) printf("%lld\n", output[i+_M] == -1 ? -1 : output[i+_M] - N + 2);
}
