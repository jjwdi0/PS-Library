#include <bits/stdc++.h>
using namespace std;
using pr = pair<int, int>;
using tr = pair<int, pr>;

struct BIT {
    int tree[100005], base;
    void init(int x) { base = x; }
    void add(int x, int y) { while(x <= base) tree[x] += y, x += x & -x; }
    int q(int x) {
        int res = 0;
        while(x) res += tree[x], x -= x & -x;
        return res;
    }
} bit;

int N, rev[100005], output[100005];
vector<int> v[100005];

void dfs(int x, int p) {
    bit.add(rev[x], 1);
    for(int it : v[x]) if(it != p) dfs(it, x);
    output[rev[x]] = bit.q(rev[x] - 1);
    bit.add(rev[x], -1);
}

int main() {
    scanf("%d", &N);
    bit.init(N);
    for(int i=1, x, y; i<N; i++) {
        scanf("%d %d", &x, &y);
        v[x].push_back(y);
        v[y].push_back(x);
    }
    for(int i=1, x; i<=N; i++) scanf("%d", &x), rev[x] = i;
    dfs(1, 0);
    for(int i=1; i<=N; i++) printf("%d\n", output[i]);
}
