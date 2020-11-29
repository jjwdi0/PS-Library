#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pr = pair<ll, ll>;

int N;
pr A[500005];

int main() {
    scanf("%d", &N);
    for(int i=1; i<=N; i++) scanf("%lld %lld", &A[i].first, &A[i].second);
    sort(A+1, A+N+1);
    for(int i=1; i<=N; i++) A[i].second += A[i-1].second;
    ll mn = A[0].second - A[1].first, ans = -1e18;
    for(int i=1; i<=N; i++) {
        mn = min(mn, -A[i].first + A[i-1].second);
        ans = max(ans, A[i].second - A[i].first - mn);
    }
    printf("%lld\n", ans);
}
