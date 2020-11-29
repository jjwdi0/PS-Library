#include <bits/stdc++.h>
#define MOD 2019201997
#define X -84
#define Y -48
using namespace std;
using pr = pair<int, int>;
using tr = pair<int, pr>;

int N, K, par[7505];
bool chk[7505][7505];
priority_queue<tr, vector<tr>, greater<tr>> pq;

int f(int x) { return par[x] = (par[x] == x ? x : f(par[x])); }
void uni(int x, int y) { par[f(x)] = f(y); }

int g(int x, int y) {
    return x * X + y * Y;
}

int main() {
    scanf("%d %d", &N, &K);
    for(int i=1; i<=N; i++) par[i] = i;
    for(int i=1; i<N; i++) pq.push(tr(g(i, i + 1), pr(i, i + 1)));
    int cur = N;
    while(!pq.empty()) {
        tr t = pq.top(); pq.pop();
        int u = t.first, x = t.second.first, y = t.second.second;
        if(f(x) != f(y)) cur--;
        else continue;
        uni(x, y);
        if(x > 1 && !chk[x-1][y]) pq.push(tr(g(x - 1, y), pr(x - 1, y))), chk[x-1][y] = 1;
        if(cur == K - 1) return printf("%d\n", MOD + u), 0;
    }
}
