#include <bits/stdc++.h>
#define pb push_back
using namespace std;
using ll = long long;
using pr = pair<int, int>;
using pl = pair<ll, int>;

int N, M, C;
vector<pr> v[100005];
ll ans = 1e18, cnt;
ll dist[100005];
bool chk[100005];
priority_queue<pl, vector<pl>, greater<pl>> pq;

int main() {
    scanf("%d %d %d", &N, &M, &C);
    for(int i=0, x, y, z; i<M; i++) {
        scanf("%d %d %d", &x, &y, &z);
        v[x].pb(pr(y, z));
        v[y].pb(pr(x, z));
        cnt += z;
    }
    pq.push(pl(0LL, 1));
    for(int i=1; i<=N; i++) dist[i] = 1e18;
    while(!pq.empty()) {
        ll c = pq.top().first; int r = pq.top().second; pq.pop();
        if(dist[r] < c) continue;
        dist[r] = c;
        for(auto it : v[r]) {
            int u = it.first; ll p = c + it.second;
            if(dist[u] > p) {
                dist[u] = p;
                pq.push(pl(dist[u], u));
            }
        }
    }
    for(int i=1; i<=N; i++) pq.push(pl(dist[i], i));
    while(!pq.empty()) {
        ll c = pq.top().first; int r = pq.top().second; pq.pop();
        chk[r] = 1;
        for(auto it : v[r]) if(chk[it.first]) cnt -= it.second;
        ans = min(ans, 1LL * C * c + cnt);
    }
    printf("%lld\n", ans);
}
