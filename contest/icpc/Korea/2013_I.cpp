#include <bits/stdc++.h>
using namespace std;

struct BIT {
    int tree[100005], base;
    void init(int x) {base = x; for(int i=0; i<=base; i++) tree[i] = 0;}
    void add(int x, int y) {while(x <= base) tree[x] += y, x += x & -x;}
    int q(int x) {
        int res = 0;
        while(x) res += tree[x], x -= x & -x;
        return res;
    }
}bit;

int T, N, A[100005];

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &N);
        bit.init(N);
        for(int i=1, x; i<=N; i++) {
            scanf("%d", &x);
            A[x] = i;
        }
        long long ans = 0LL;
        for(int i=1, x; i<=N; i++) {
            scanf("%d", &x);
            x = A[x];
            ans += (long long)(bit.q(N) - bit.q(x));
            bit.add(x, 1);
        }
        printf("%lld\n", ans);
    }
}
