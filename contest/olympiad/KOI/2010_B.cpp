#include <bits/stdc++.h>
#define INF 1000000007
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
using namespace std;
using pr = pair<int, int>;
using qr = pair<pr, pr>;

struct segtree {
    int tree[844444], base;
    void init(int x) { for(base=1; base<x; base<<=1); for(int i=1; i<base*2; i++) tree[i] = 1e9; }
    void update(int x, int y) {
        x += base - 1;
        tree[x] = min(y, tree[x]);
        x /= 2;
        while(x) tree[x] = min(tree[x*2], tree[x*2+1]), x /= 2;
    }
    int RMQ(int s, int e) {
        s += base - 1, e += base - 1;
        int res = INF;
        while(s < e) {
            if(s & 1) res = min(res, tree[s++]);
            if(!(e & 1)) res = min(res, tree[e--]);
            s >>= 1, e >>= 1;
        }
        if(s == e) res = min(res, tree[s]);
        return res;
    }
} seg;

int N, A, B, C, M, T, D[3][100005];
vector<int> coor;
vector<pr> v[100005];
qr query[100005];
bool chk[100005];
set<pr> s;
priority_queue<pr, vector<pr>, greater<pr>> pq;

int index(int x) { return lower_bound(all(coor), x) - coor.begin() + 1; }

void get_dijkstra(int idx, int start) {
    for(int i=1; i<=N; i++) D[idx][i] = INF;
    D[idx][start] = 0;
    pq.push(pr(0, start));
    while(!pq.empty()) {
        int u = pq.top().second, cost = pq.top().first; pq.pop();
        for(auto it : v[u]) {
            if(D[idx][it.first] > cost + it.second) {
                D[idx][it.first] = cost + it.second;
                pq.push(pr(D[idx][it.first], it.first));
            }
        }
    }
}

int main() {
    scanf("%d %d %d %d %d", &N, &A, &B, &C, &M);
    for(int i=0, x, y, z; i<M; i++) {
        scanf("%d %d %d", &x, &y, &z);
        v[x].push_back(pr(y, z));
        v[y].push_back(pr(x, z));
    }
    get_dijkstra(0, A);
    get_dijkstra(1, B);
    get_dijkstra(2, C);
    for(int i=1; i<=N; i++) query[i] = qr(pr(D[0][i], i), pr(D[1][i], D[2][i]));
    sort(query+1, query+N+1);

    for(int i=1; i<=N; i++) coor.push_back(query[i].second.first), coor.push_back(query[i].second.second);
    sort(all(coor));
    coor.resize(unique(all(coor)) - coor.begin());
    for(int i=1; i<=N; i++) {
        query[i].second.first = index(query[i].second.first);
        query[i].second.second = index(query[i].second.second);
    }
    seg.init(sz(coor));

    for(int i=1; i<=N;) {
        int j = i;
        while(query[i].first.first == query[j].first.first) j++;
        for(int k=i; k<j; k++) {
            int mn = seg.RMQ(1, query[k].second.first - 1);
            if(mn < query[k].second.second) chk[query[k].first.second] = 1;
        }
        for(int k=i; k<j; k++) seg.update(query[k].second.first, query[k].second.second);
        i = j;
    }

    scanf("%d", &T);
    while(T--) {
        int q;
        scanf("%d", &q);
        puts(chk[q] ? "NO" : "YES");
    }
}
