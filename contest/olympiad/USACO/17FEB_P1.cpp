#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct BIT {
    int tree[100005], base;
    void init(int x) { base = x + 2; for(int i=0; i<=base; i++) tree[i] = 0; }
    void add(int x, int y) {
        x += 2;
        while(x <= base) tree[x] += y, x += x & -x;
    }
    int q(int x) {
        int res = 0;
        x += 2;
        while(x) res += tree[x], x -= x & -x;
        return res;
    }
}bit;

int N, A[100005][2], B[100005], idx[100005];
ll ans, cnt;

ll f(int x) {
    bit.init(N);
    ans = cnt = 0LL;
    for(int i=1; i<=N; i++) idx[A[i][1-x]] = i;
    for(int i=N; i; i--) {
        cnt += (ll)(idx[A[i][x]] - 1);
        cnt -= (ll)(N - idx[A[i][x]]);
        ans = min(ans, cnt);
    }
    for(int i=1; i<=N; i++) {
        ans += (ll)(i - 1 - bit.q(idx[A[i][x]]));
        bit.add(idx[A[i][x]], 1);
    }
    return ans;
}

int main() {
    scanf("%d", &N);
    for(int i=1; i<=N; i++) scanf("%d", &A[i][0]);
    for(int i=1; i<=N; i++) scanf("%d", &A[i][1]);
    printf("%lld\n", min(f(0), f(1)));
}
