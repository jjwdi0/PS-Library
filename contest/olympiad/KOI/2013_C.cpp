#include <stdio.h>
#include <algorithm>
using namespace std;
typedef long long ll;

int N;
ll A[100005];

ll f(ll x) {
    ll res = 0;
    for(int i=1; i<=N; i++) {
        ll coord = (ll)(i - 1) * x;
        res += abs(A[i] - coord);
    }
    return res;
}

int main() {
    scanf("%d", &N);
    for(int i=1; i<=N; i++) scanf("%lld", A+i);
    ll lo = 1LL, hi = 1e9;
    while(lo + 2 < hi) {
        ll m1 = (lo * 2 + hi) / 3, m2 = (lo + hi * 2) / 3;
        f(m1) < f(m2) ? hi = m2 : lo = m1;
    }
    ll ans = 1e18;
    for(ll i=lo; i<=hi; i++) ans = min(ans, f(i));
    printf("%lld\n", ans);
}
