#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int N;
ll T[100005], C[100005], num[100005], ans;
vector<int> v[100005];

void dfs(int x) {
    for(auto it : v[x]) {
        dfs(it);
        num[x] += num[it];
        T[x] = min(T[x], T[it]);
    }
    if(num[x] < C[x]) ans += T[x] * (C[x] - num[x]), num[x] = C[x];
}

int main() {
    scanf("%d", &N);
    for(int i=1, x, y, z; i<=N; i++) {
        scanf("%d %d %d", &x, &y, &z);
        if(~x) v[x].push_back(i);
        C[i] = (ll)y, T[i] = (ll)z;
    }
    dfs(1);
    printf("%lld\n", ans);
}
