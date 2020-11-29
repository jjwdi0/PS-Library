#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
using namespace std;
using pr = pair<int, int>;

int N, M, dist[30005];
int s, t;
vector<int> v[30005];
priority_queue<pr, vector<pr>, greater<pr>> pq;

bool chk(int to, int cost, int j, int i) {
    if(dist[to] > cost + j) {
        dist[to] = cost + j;
        pq.push(pr(dist[to], to));
    }
    auto it = lower_bound(all(v[to]), i);
    if(it != v[to].end() && *it == i) return false;
    return true;
}

int main() {
    scanf("%d %d", &N, &M);
    for(int i=0, x, y; i<M; i++) {
        scanf("%d %d", &x, &y);
        v[x].push_back(y);
        if(i == 0) s = x;
        if(i == 1) t = x;
    }
    for(int i=0; i<N; i++) sort(all(v[i])), v[i].resize(unique(all(v[i])) - v[i].begin());
    for(int i=0; i<N; i++) dist[i] = 2e9;
    pq.push(pr(0, s));
    while(!pq.empty()) {
        int u = pq.top().second, cost = pq.top().first; pq.pop();
        if(dist[u] < cost) continue;
        dist[u] = cost;
        if(u == t) return printf("%d\n", cost), 0;
        for(int i : v[u]) {
            for(int j = 1; u + j * i < N; j++) {
                int to = u + j * i;
                if(!chk(to, cost, j, i)) break;
            }
            for(int j = 1; u - j * i >= 0; j++) {
                int to = u - j * i;
                if(!chk(to, cost, j, i)) break;
            }
        }
    }
    puts("-1");
}
