#include <bits/stdc++.h>
using namespace std;
using pr = pair<int, int>;
using ll = long long;
 
int N, M, idx[300005];
ll sum[300005];
vector<pr> v;
ll ans;
 
int main() {
    scanf("%d", &N);
    for(int i=0, x, y; i<N; i++) {
        scanf("%d %d", &x, &y);
        sum[i+1] = 1LL * y;
        idx[i+1] = x;
    }
    scanf("%d", &M);
    for(int i=0, x, y; i<M; i++) {
        scanf("%d %d", &x, &y);
        v.push_back(pr(x, y));
    }
    int s, e;
    scanf("%d %d", &s, &e);
    for(int i=1; i<=N; i++) {
        sum[i] += sum[i-1];
    }
 
    for(auto it : v) {
        int idx1 = lower_bound(idx+1, idx+N+1, it.first - e) - idx,
            idx2 = upper_bound(idx+1, idx+N+1, it.first - s) - idx;
        ans += 1LL * (1LL * sum[idx2-1] - 1LL * sum[idx1-1]) * it.second;
    }
    printf("%lld\n", ans);
}