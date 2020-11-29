#include <bits/stdc++.h>
#define MOD 1000000007
using namespace std;
using ll = long long;

int N, K, C[100005];
vector<int> v[100005];
ll D[100005][4];

int mn(int x) { return x == 1 ? 2 : 1; }
int mx(int x) { return x == 3 ? 2 : 3; }

ll f(int x, int c, int p) {
    if(~D[x][c]) return D[x][c];
    if(C[x] && C[x] != c) return D[x][c] = 0LL;
    ll &res = D[x][c] = 1LL;
    for(auto it : v[x]) {
        if(it == p) continue;
        res = res * (f(it, mn(c), x) + f(it, mx(c), x)) % MOD;
    }
    return res;
}

int main() {
    scanf("%d %d", &N, &K);
    for(int i=1, x, y; i<N; i++) {
        scanf("%d %d", &x, &y);
        v[x].push_back(y);
        v[y].push_back(x);
    }
    for(int i=1; i<=N; i++) D[i][1] = D[i][2] = D[i][3] = -1LL;
    for(int i=1, x, y; i<=K; i++) {
        scanf("%d %d", &x, &y);
        C[x] = y;
    }
    if(C[1]) printf("%lld\n", f(1, C[1], 0));
    else printf("%lld\n", (f(1, 1, 0) + f(1, 2, 0) + f(1, 3, 0)) % MOD);
}
