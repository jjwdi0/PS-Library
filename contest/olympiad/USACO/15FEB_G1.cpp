#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define sz(x) ((int)(x).size())
#define MOD 1000000007
using namespace std;
using ll = long long;

struct BIT {
    int base;
    vector<ll> tree;
    void init(int x) { base = x; tree.resize(x + 1); }
    void add(int x, ll y) { while(x <= base) tree[x] += y, x += x & -x; }
    ll q(int x) {
        ll res = 0LL;
        while(x) res += tree[x], x -= x & -x;
        return res;
    }
} bit[600005];

int N, M, K, A[755][755], ind[755][755];
ll D[755][755], C[755][755];
vector<int> v[600005];

int main() {
    scanf("%d %d %d", &N, &M, &K);
    for(int i=1; i<=N; i++) for(int j=1; j<=M; j++) {
        scanf("%d", &A[i][j]);
        v[A[i][j]].push_back(j);
    }
    for(int i=1; i<=K; i++) sort(all(v[i])), v[i].resize(unique(all(v[i])) - v[i].begin());
    for(int i=1; i<=K; i++) bit[i].init(sz(v[i]));
    bit[A[1][1]].add(1, 1);
    for(int i=1; i<=M; i++) D[1][i] = 1LL;
    for(int i=2; i<=N; i++) {
        for(int j=1; j<=M; j++) {
            ll c = D[i-1][j-1];
            int k = A[i][j];
            int idx = lower_bound(all(v[k]), j) - v[k].begin();
            if(idx) c -= bit[k].q(idx);
            c = (c + MOD) % MOD;
            ind[i][j] = idx, C[i][j] = c;
            D[i][j] = ((D[i-1][j] + D[i][j-1] - D[i-1][j-1]) % MOD + c + MOD) % MOD;
        }
        for(int j=1; j<=M; j++) bit[A[i][j]].add(ind[i][j] + 1, C[i][j]);
    }
    printf("%lld\n", ((D[N][M] - D[N-1][M] - D[N][M-1]) % MOD + D[N-1][M-1] + MOD) % MOD);
}
