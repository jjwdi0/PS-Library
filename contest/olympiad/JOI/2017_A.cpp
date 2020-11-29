#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int N, Q, S, T, A[200005];
ll ans, B[200005];

ll f(int x, int y) {
    if(x > N) return 0LL;
    ll res = 0LL;
    if(B[x] >= 0LL && B[x] + y >= 0LL) res = -1LL * S * y;
    else if(B[x] < 0LL && B[x] + y < 0LL) res = -1LL * T * y;
    else if(B[x] >= 0LL && B[x] + y < 0LL) res = 1LL * S * B[x] - 1LL * T * (B[x] + y);
    else res = 1LL * T * B[x] - 1LL * S * (B[x] + y);
    B[x] += y;
    return res;
}

int main() {
    scanf("%d %d %d %d", &N, &Q, &S, &T);
    for(int i=0; i<=N; i++) scanf("%d", A+i);
    for(int i=1; i<=N; i++) B[i] = A[i] - A[i-1];
    for(int i=1; i<=N; i++) {
        if(B[i] > 0) ans -= 1LL * S * B[i];
        else ans -= 1LL * T * B[i];
    }
    while(Q--) {
        int l, r, x;
        scanf("%d %d %d", &l, &r, &x);
        ans += f(l, x) + f(r + 1, -x);
        printf("%lld\n", ans);
    }
}
