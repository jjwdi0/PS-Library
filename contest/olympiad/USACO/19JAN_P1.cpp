#include <bits/stdc++.h>
using namespace std;
using pr = pair<int, int>;

struct segtree {
    int tree[1234567], base;
    void init(int x) { for(base=1; base<x; base<<=1); }
    void update(int x, int y) {
        x += base - 1;
        tree[x] = y, x >>= 1;
        while(x) tree[x] = min(tree[x*2], tree[x*2+1]), x >>= 1;
    }
    int RMQ(int s, int e) {
        s += base - 1, e += base - 1;
        int res = 1e9;
        while(s < e) {
            if(s & 1) res = min(res, tree[s++]);
            if(!(e & 1)) res = min(res, tree[e--]);
            s >>= 1, e >>= 1;
        }
        if(s == e) res = min(res, tree[e]);
        return res;
    }
} seg;

int N, K, S[300005], D[300005];
char A[300005];
pr T[300005];

int main() {
    scanf("%d %d %s", &N, &K, A);
    for(int i=0; i<N; i++) S[i+1] = S[i] + (A[i] == 'H' ? 1 : -1);
    for(int i=1; i<=N; i++) T[i] = pr(S[i], i);
    swap(T[0], T[N]);
    sort(T + 1, T + N + 1);
    seg.init(N);
    for(int i=1; i<=N; i++) seg.update(i, 1e9);
    seg.update((int)(lower_bound(T + 1, T + N + 1, pr(0, 0)) - T), 0);
    for(int i=1; i<=N; i++) {
        int idx = (int)(lower_bound(T + 1, T + N + 1, pr(S[i], -1e9)) - T);
        D[i] = min(seg.RMQ(1, idx - 1), seg.RMQ(idx, N) + 1);
        idx = (int)(lower_bound(T + 1, T + N + 1, pr(S[i], i)) - T);
        seg.update(idx, D[i]);
        if(i >= K) {
            idx = (int)(lower_bound(T + 1, T + N + 1, pr(S[i-K], i - K)) - T);
            seg.update(idx, 1e9);
        }
    }
    printf("%d\n", D[N]);
}
