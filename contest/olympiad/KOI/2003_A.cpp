#include<cstdio>
#include<algorithm>
using namespace std;
const int MAX_N = 1e4;
int rt, n, ck[MAX_N + 1], left[MAX_N + 1], right[MAX_N + 1];
struct st {
    int l, r, lc, rc;
}t[MAX_N + 1];
int dfs(int h) {
    if (h == -1) return 0;
    t[h].lc = dfs(t[h].l);
    t[h].rc = dfs(t[h].r);
    return t[h].lc + t[h].rc + 1;
}
void dfs2(int h, int lv, int p) {
    left[lv] = min(left[lv], p);
    right[lv] = max(right[lv], p);
    if (t[h].l != -1) dfs2(t[h].l, lv + 1, p - t[t[h].l].rc - 1);
    if (t[h].r != -1) dfs2(t[h].r, lv + 1, p + t[t[h].r].lc + 1);
}
int main() {
    scanf("%d", &n);
    for (int i = 0, x, y, z; i < n; i++) {
        scanf("%d %d %d", &x, &y, &z);
        t[x].l = y;
        t[x].r = z;
        if (y != -1)ck[y] = 1;
        if (z != -1) ck[z] = 1;
    }
    for (int i = 1; i <= n; i++) {
        right[i] = -1e8;
        left[i] = 1e8;
        if (!ck[i]) rt = i;
    }
    dfs(rt);
    dfs2(rt, 1, 0);
    int res = 0, tmp;
    for (int i = 1; i <= n; i++) {
        int tt = right[i] - left[i] + 1;
        if (res < tt) res = tt, tmp = i;
    }
    printf("%d %d", tmp, res);
    return 0;
}