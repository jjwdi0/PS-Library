#include <bits/stdc++.h>
using namespace std;

int N, M, par[200005], sz[200005], P[200005], ans[200005];
vector<int> v[200005];
bool chk[200005];

int f(int x) { return par[x] = (par[x] == x ? x : f(par[x])); }
void uni(int x, int y) {
    x = f(x), y = f(y);
    if(x == y) return;
    sz[x] += sz[y], par[y] = x;
}

int main() {
    scanf("%d %d", &N, &M);
    for(int i=0, x, y; i<M; i++) {
        scanf("%d %d", &x, &y);
        v[x].push_back(y);
        v[y].push_back(x);
    }
    for(int i=1; i<=N; i++) scanf("%d", P+i), par[i] = i, sz[i] = 1;
    for(int i=N; i; i--) {
        chk[P[i]] = 1;
        for(auto it : v[P[i]]) if(chk[it]) uni(P[i], it);
        ans[i] = (sz[f(P[i])] == N - i + 1);
    }
    for(int i=1; i<=N; i++) puts(ans[i] ? "YES" : "NO");
}
