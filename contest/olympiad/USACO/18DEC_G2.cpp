#include <bits/stdc++.h>
#define sz(x) ((int)(x).size())
#define rep(i, x, n) for(int (i)=(x); (i)<(n); (i)++)
using namespace std;
using pr = pair<int, int>;
using tr = pair<int, pr>;
using qr = pair<int, tr>;
using Pr = pair<int, qr>;
using ll = long long;

int N, A[10];
map<int, int> m1;
map<pr, int> m2;
map<tr, int> m3;
map<qr, int> m4;
map<Pr, int> m5;

int main() {
    scanf("%d", &N);
    for(int i=1; i<=N; i++) {
        rep(j, 0, 5) scanf("%d", A+j);
        sort(A, A+5);
        rep(j, 0, 5) m1[A[j]]++;
        rep(j, 0, 5) rep(k, j+1, 5) m2[pr(A[j], A[k])]++;
        rep(i1, 0, 5) rep(i2, i1+1, 5) rep(i3, i2+1, 5) m3[tr(A[i1], pr(A[i2], A[i3]))]++;
        rep(i1, 0, 5) rep(i2, i1+1, 5) rep(i3, i2+1, 5) rep(i4, i3+1, 5) m4[qr(A[i1], tr(A[i2], pr(A[i3], A[i4])))]++;
        rep(i1, 0, 5) rep(i2, i1+1, 5) rep(i3, i2+1, 5) rep(i4, i3+1, 5) rep(i5, i4+1, 5) m5[Pr(A[i1], qr(A[i2], tr(A[i3], pr(A[i4], A[i5]) ) ) )]++;
    }
    ll cnt = 0LL, ans = 0LL;
    for(auto it : m1) cnt += 1LL * (it.second - 1) * it.second / 2;
    ans += cnt, cnt = 0LL;
    for(auto it : m2) cnt += 1LL * (it.second - 1) * it.second / 2;
    ans -= cnt, cnt = 0LL;
    for(auto it : m3) cnt += 1LL * (it.second - 1) * it.second / 2;
    ans += cnt, cnt = 0LL;
    for(auto it : m4) cnt += 1LL * (it.second - 1) * it.second / 2;
    ans -= cnt, cnt = 0LL;
    for(auto it : m5) cnt += 1LL * (it.second - 1) * it.second / 2;
    ans += cnt, cnt = 0LL;
    printf("%lld\n", 1LL * N * (N - 1) / 2 - ans);
}
