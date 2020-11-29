#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define sz(x) ((int)(x).size())
using namespace std;
using pr = pair<int, int>;

struct Query { int l, r, s, e; } A[100005];

struct Disjoint_Set {
    int par[100005], sz;
    void init(int x) {
        sz = x;
        for(int i=1; i<=sz; i++) par[i] = i;
    }
    int f(int x) { return par[x] = (par[x] == x ? x : f(par[x])); }
    void uni(int x, int y) { par[f(x)] = f(y); }
} F;

int N, M, K, Q, D[100005];
vector<pr> v[100005], dist;
vector<int> pbs[100005], coor;
bool chk[100005];
priority_queue<pr, vector<pr>, greater<pr>> pq;

int main() {
    scanf("%d %d %d %d", &N, &M, &K, &Q);
    for(int i=0, x, y, z; i<M; i++) {
        scanf("%d %d %d", &x, &y, &z);
        v[x].push_back(pr(y, z));
        v[y].push_back(pr(x, z));
    }
    for(int i=1; i<=N; i++) D[i] = 2e9;
    for(int i=0, x; i<K; i++) {
        scanf("%d", &x);
        D[x] = 0;
        pq.push(pr(0, x));
    }
    while(!pq.empty()) {
        int u = pq.top().second, c = pq.top().first; pq.pop();
        for(auto it : v[u]) {
            int next = it.first, cost = it.second;
            if(D[next] > c + cost) {
                D[next] = c + cost;
                pq.push(pr(D[next], next));
            }
        }
    }
    for(int i=1; i<=N; i++) coor.push_back(D[i]), dist.push_back(pr(D[i], i));
    sort(all(coor)), sort(all(dist));
    coor.resize(unique(all(coor)) - coor.begin());
    reverse(all(coor));
    reverse(all(dist));
    for(int i=1; i<=Q; i++) {
        scanf("%d %d", &A[i].s, &A[i].e);
        A[i].l = 1, A[i].r = sz(coor);
    }
    for(;;) {
        for(int i=1; i<=N; i++) pbs[i].clear(), chk[i] = 0;
        bool flag = 0;
        for(int i=1; i<=Q; i++) if(A[i].l <= A[i].r) {
            pbs[A[i].l+A[i].r>>1].push_back(i);
            flag = 1;
        }
        if(!flag) break;
        F.init(N);
        int l = 0, r = 0;
        for(int i=1; i<=sz(coor); i++) {
            while(r < sz(dist) && dist[r].first == dist[l].first) r++;
            for(int j=l; j<r; j++) {
                int u = dist[j].second;
                chk[u] = 1;
                for(auto it : v[u]) if(chk[it.first]) F.uni(u, it.first);
            }
            for(int it : pbs[i]) {
                if(chk[A[it].s] && chk[A[it].e] && F.f(A[it].s) == F.f(A[it].e)) A[it].r = i - 1;
                else A[it].l = i + 1;
            }
            l = r;
        }
    }
    for(int i=1; i<=Q; i++) printf("%d\n", coor[A[i].l-1]);
}
