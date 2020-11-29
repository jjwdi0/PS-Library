#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pr = pair<ll, int>;

int N, M, K, H[100005];
ll D[100005];
vector<pr> v[100005];
priority_queue<pr> pq;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> N >> M >> K;
    for(int i=1; i<=N; i++) cin >> H[i];
    for(int i=0, x, y, z; i<M; i++) {
        cin >> x >> y >> z;
        v[x].push_back(pr(y, z));
        v[y].push_back(pr(x, z));
    }
    for(int i=1; i<=N; i++) D[i] = -1e18;
    pq.push(pr(K, 1)), D[1] = K;
    while(!pq.empty()) {
        int u = pq.top().second;
        ll c = pq.top().first; pq.pop();
        if(D[u] > c) continue;
        for(auto it : v[u]) {
            int next = it.first, cost = it.second;
            if(H[u] < cost || D[next] >= min(c - cost, 1LL * H[next])) continue;
            D[next] = min(c - cost, 1LL * H[next]);
            pq.push(pr(min(c - cost, 1LL * H[next]), next));
        }
    }
    if(D[N] < -1e17) cout << "-1\n";
    else cout << -2LL * D[N] + K + H[N] << '\n';
}