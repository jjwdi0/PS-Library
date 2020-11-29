#include <bits/stdc++.h>
using namespace std;

struct seg_tree {
    int tree[444444], base;
    void init(int x) { for(base = 1; base < x; base <<= 1); }
    void update(int x, int y) {
        x += base - 1;
        if(tree[x] >= y) return;
        tree[x] = y;
        x >>= 1;
        while(x) {
            if(tree[x] == max(tree[x * 2], tree[x * 2 + 1])) break;
            tree[x] = max(tree[x * 2], tree[x * 2 + 1]);
            x >>= 1;
        }
    }
    int RMQ(int x, int y) {
        x += base - 1, y += base - 1;
        int res = 0;
        while(x < y) {
            if(x & 1) res = max(tree[x++], res);
            if(!(y & 1)) res = max(tree[y--], res);
            x >>= 1, y >>= 1;
        }
        if(x == y) res = max(res, tree[x]);
        return res;
    }
}S;

int N, A[100005], B[100005], idx[100005][9], chk[100005];
int D[100005][9], ans;

int main() {
    scanf("%d", &N);
    S.init(N);
    for(int i=1; i<=N; i++) scanf("%d", A+i);
    for(int i=1; i<=N; i++) scanf("%d", B+i);
    for(int i=1; i<=N; i++) chk[A[i]] = i;
    for(int i=1; i<=N; i++) for(int j=0; j<9; j++) {
        if(B[i] + j - 4 <= 0) continue;
        if(B[i] + j - 4 >  N) continue;
        idx[i][j] = chk[B[i] + j - 4];
    }
    for(int i=1; i<=N; i++) {
        for(int j=0; j<9; j++) {
            if(idx[i][j] == 0) continue;
            D[i][j] = S.RMQ(1, idx[i][j] - 1) + 1;
            ans = max(ans, D[i][j]);
        }
        for(int j=0; j<9; j++) {
            if(!idx[i][j]) continue;
            S.update(idx[i][j], D[i][j]);
        }
    }
    printf("%d\n", ans);
}
