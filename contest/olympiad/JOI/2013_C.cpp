#include <bits/stdc++.h>
#define pb push_back
#define all(x) (x).begin(),(x).end()
#define sz(x) ((int)(x).size())
using namespace std;
using ll = long long;
using pr = pair<int, int>;
using tr = pair<ll, pr>;

int R, C, K, X[200005], Y[200005];
ll D[200005][2], ans = 1e18;
vector<pr> xv[100005], yv[100005];
priority_queue<tr, vector<tr>, greater<tr>> pq;

void f(int idx, int st, ll c, ll x2, ll x1) {
    if(D[idx][st] > c + x2 - x1) {
        D[idx][st] = c + x2 - x1;
        pq.push(tr(D[idx][st], pr(idx, st)));
    }
}

int main() {
    scanf("%d %d %d", &R, &C, &K);
    for(int i=1; i<=K; i++) {
        D[i][0] = D[i][1] = 1e18;
        scanf("%d %d", X+i, Y+i);
        xv[X[i]].pb(pr(Y[i], i));
        yv[Y[i]].pb(pr(X[i], i));
    }
    for(int i=1; i<=R; i++) sort(all(xv[i]));
    for(int i=1; i<=C; i++) sort(all(yv[i]));
    if(!sz(xv[1])) return puts("-1"), 0;
    pq.push(tr(xv[1][0].first - 1, pr(xv[1][0].second, 0)));
    while(!pq.empty()) {
        int idx = pq.top().second.first; ll cost = pq.top().first; int st = pq.top().second.second; pq.pop();
        int x = X[idx], y = Y[idx];
        if(x == R && !st) { ans = min(ans, cost + C - y); continue; }
        if(y == C && st) { ans = min(ans, cost + R - x); continue; }
        if(D[idx][st] < cost) continue;
        D[idx][st] = cost;
        if(D[idx][st^1] > cost + 1) D[idx][st^1] = cost + 1, pq.push(tr(cost + 1, pr(idx, st ^ 1)));
        if(!st) {
            auto it = lower_bound(all(xv[x]), pr(y, 0));
            if(it + 1 != xv[x].end()) {
                auto jt = it + 1;
                f(jt->second, st, cost, jt->first, y);
            }
            if(it != xv[x].begin()) {
                auto jt = it - 1;
                f(jt->second, st, cost, y, jt->first);
            }
        }
        else {
            auto it = lower_bound(all(yv[y]), pr(x, 0));
            if(it + 1 != yv[y].end()) {
                auto jt = it + 1;
                f(jt->second, st, cost, jt->first, x);
            }
            if(it != yv[y].begin()) {
                auto jt = it - 1;
                f(jt->second, st, cost, x, jt->first);
            }
        }
    }
    printf("%lld\n", ans > 1e17 ? -1 : ans);
}
