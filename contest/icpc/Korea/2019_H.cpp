#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define sz(x) ((int)(x).size())
#define INF 1000000000
using namespace std;
using pr = pair<int, int>;

struct Node { int l, r, mx, sum; };

Node max_node(Node x, Node y) {
    Node res;
    res.l = max(x.l, x.sum + y.l);
    res.r = max(y.r, y.sum + x.r);
    res.sum = x.sum + y.sum;
    res.mx = max({ x.mx, y.mx, x.r + y.l });
    return res;
}

struct segtree {
    Node tree[8888];
    int base;
    void init(int x) { for(base=1; base<x; base<<=1); for(int i=1; i<=base+base; i++) tree[i] = { 0,0,0,0 }; }
    void update(int x, int y) {
        x += base - 1;
        tree[x] = { y, y, y, y }, x >>= 1;
        while(x) tree[x] = max_node(tree[x+x], tree[x+x+1]), x >>= 1;
    }
    int RMQ(int s, int e) {
        s += base - 1, e += base - 1;
        Node res1 = { -INF, -INF, -INF, 0 }, res2 = { -INF, -INF, -INF, 0 };
        while(s < e) {
            if(s & 1) res1 = max_node(res1, tree[s++]);
            if(!(e & 1)) res2 = max_node(tree[e--], res2);
            s >>= 1, e >>= 1;
        }
        if(s == e) res1 = max_node(res1, tree[s]);
        return max({ res1.mx, res2.mx, res1.r + res2.l });
    }
} seg;

int N, M, c1, c2;
vector<int> X, Y;
vector<pr> v[2005];
pr A[1005], B[1005];

int main() {
    scanf("%d", &N);
    for(int i=1; i<=N; i++) scanf("%d %d", &A[i].first, &A[i].second), X.push_back(A[i].first), Y.push_back(A[i].second);
    scanf("%d", &M);
    for(int i=1; i<=M; i++) scanf("%d %d", &B[i].first, &B[i].second), X.push_back(B[i].first), Y.push_back(B[i].second);
    scanf("%d %d", &c1, &c2), c2 = -c2;
    sort(all(X)), sort(all(Y));
    X.resize(unique(all(X)) - X.begin()), Y.resize(unique(all(Y)) - Y.begin());
    for(int i=1; i<=N; i++) {
        int x = A[i].first, y = A[i].second;
        x = lower_bound(all(X), x) - X.begin() + 1;
        y = lower_bound(all(Y), y) - Y.begin() + 1;
        v[x].push_back(pr(y, c1));
    }
    for(int i=1; i<=M; i++) {
        int x = B[i].first, y = B[i].second;
        x = lower_bound(all(X), x) - X.begin() + 1;
        y = lower_bound(all(Y), y) - Y.begin() + 1;
        v[x].push_back(pr(y, c2));
    }
    int ans = 0;
    for(int i=1; i<=sz(X); i++) {
        seg.init(sz(Y));
        for(int j=i; j<=sz(X); j++) {
            for(auto it : v[j]) seg.update(it.first, it.second);
            ans = max(ans, seg.RMQ(1, sz(Y)));
        }
    }
    printf("%d\n", ans);
}
