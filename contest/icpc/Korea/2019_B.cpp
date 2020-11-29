#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pr = pair<int, int>;

int N;
ll cnt[100005], sum[100005], sq[100005], ans[100005];
vector<pr> v[100005];

void dfs(int x, int p) {
    if(v[x].size() == 1) {
        cnt[x] = 1LL;
        return;
    }
    for(auto it : v[x]) if(it.first != p) {
        int u = it.first, l = it.second;
        dfs(u, x);
        cnt[x] += cnt[u];
        sum[x] += cnt[u] * l + sum[u];
        sq[x] += cnt[u] * l * l + 2LL * sum[u] * l + sq[u];
        ans[x] += ans[u] + ans[u];
    }
    for(auto it : v[x]) if(it.first != p) {
        int u = it.first, l = it.second;
        ans[x] += (cnt[u] * l * l + 2LL * sum[u] * l + sq[u]) * (cnt[x] - cnt[u]);
        ans[x] += 2LL * (cnt[u] * l + sum[u]) * (sum[x] - (cnt[u] * l + sum[u]));
        ans[x] += (sq[x] - (cnt[u] * l * l + 2LL * sum[u] * l + sq[u])) * cnt[u];
    }
    ans[x] >>= 1;
}

int main() {
    scanf("%d", &N);
    for(int i=1, x, y, z; i<N; i++) {
        scanf("%d %d %d", &x, &y, &z);
        v[x].push_back(pr(y, z));
        v[y].push_back(pr(x, z));
    }
    for(int i=1; i<=N; i++) if(v[i].size() > 1) { dfs(i, 0); return !printf("%lld\n", ans[i]); }
}
