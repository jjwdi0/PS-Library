#include <bits/stdc++.h>
using namespace std;

int N, Q, st[50005][17], A[50005], lev[50005];
vector<int> v[50005];

void dfs(int x, int p) {
    st[x][0] = p, lev[x] = lev[p] + 1;
    for(int it : v[x]) {
        if(it == p) continue;
        dfs(it, x);
    }
}

int LCA(int x, int y) {
    if(lev[x] > lev[y]) swap(x, y);
    for(int i=16; ~i; i--) if(lev[x] <= lev[st[y][i]]) y = st[y][i];
    if(x == y) return x;
    for(int i=16; ~i; i--) if(st[x][i] != st[y][i]) x = st[x][i], y = st[y][i];
    return st[x][0];
}

int dfs2(int x, int p) {
    int res = 0;
    for(int it : v[x]) {
        if(it == p) continue;
        res = max(res, dfs2(it, x));
        A[x] += A[it];
    }
    return max(res, A[x]);
}

int main() {
    scanf("%d %d", &N, &Q);
    for(int i=1, x, y; i<N; i++) {
        scanf("%d %d", &x, &y);
        v[x].push_back(y), v[y].push_back(x);
    }
    dfs(1, 0);
    for(int i=1; i<=16; i++) for(int j=1; j<=N; j++) st[j][i] = st[ st[j][i-1] ][i-1];
    while(Q--) {
        int x, y, u;
        scanf("%d %d", &x, &y);
        u = LCA(x, y);
        A[x]++, A[y]++, A[st[u][0]]--, A[u]--;
    }
    printf("%d\n", dfs2(1, 0));
}
