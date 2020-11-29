#include <bits/stdc++.h>
using namespace std;
using pr = pair<int, int>;
using ll = long long;

int N;
pr A[100005];

bool f(ll x) {
    ll s = A[1].first, e = A[1].second;
    for(int i=2; i<=N; i++) {
        if(s + x > A[i].second) return 0;
        ll _s = s + x, _e = e + x;
        s = max(_s, 1LL * A[i].first);
        e = min(_e, 1LL * A[i].second);
    }
    return 1;
}

int main() {
    scanf("%d", &N);
    for(int i=1, x, y; i<=N; i++) {
        scanf("%d %d", &x, &y);
        A[i] = pr(x, x + y);
    }
    sort(A + 1, A + N + 1);
    ll s = 0, e = 2e9;
    while(s <= e) {
        ll mid = s + e >> 1;
        f(mid) ? s = mid + 1LL : e = mid - 1LL;
    }
    printf("%lld\n", e);
}
