#include <stdio.h>
#include <queue>
#include <vector>
using namespace std;
typedef long long ll;
typedef pair<int, int> pr;
typedef pair<ll, pr> tr;

int N, M;
int price[2505];
ll D[2505][2505];
vector<pr> v[2505];
priority_queue<tr, vector<tr>, greater<tr>> pq;

int main() {
    scanf("%d %d", &N, &M);
    for(int i=1; i<=N; i++) scanf("%d", price + i);
    for(int i=0, x, y, z; i<M; i++) {
        scanf("%d %d %d", &x, &y, &z);
        v[x].push_back(pr(y, z));
        v[y].push_back(pr(x, z));
    }
    for(int i=1; i<=N; i++) for(int j=0; j<=2500; j++) D[i][j] = 1e15;
    pq.push(tr(0, pr(1, price[1])));
    while(!pq.empty()) {
        int u = pq.top().second.first, lo = pq.top().second.second; ll cost = pq.top().first; pq.pop();
        if(u == N) return printf("%lld\n", cost),0;
        if(D[u][lo] < cost) continue;
        D[u][lo] = cost;
        for(int i=0; i<(int)v[u].size(); i++) {
            int to = v[u][i].first, c = v[u][i].second;
            if(D[to][min(price[to], lo)] > cost + (ll)c * (ll)lo) {
                D[to][min(price[to], lo)] = cost + 1LL * c * lo;
                pq.push(tr(D[to][min(price[to], lo)], pr(to, min(price[to], lo))));
            }
        }
    }
}
