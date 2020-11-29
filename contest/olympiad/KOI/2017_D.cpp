#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct BIT {
    ll tree[3333];
    int base;
    void init(int x) { base = x; }
    void add(int x, ll y) { while(x <= base) tree[x] += y, x += x & -x; }
    ll q(int x) {
        ll res = 0LL;
        while(x) res += tree[x], x -= x & -x;
        return res;
    }
} bit[1505];

int N;
ll A[1505][1505], D[1505][1505], ans;

int main() {
    scanf("%d", &N);
    for(int i=1; i<=N; i++) for(int j=1; j<=N; j++) scanf("%lld", &A[i][j]);
    for(int i=1; i<=N; i++) for(int j=1; j<=N; j++) ans += (D[i][j] = max(D[i-1][j], D[i][j-1]) + A[i][j]);
    printf("%lld\n", ans);
    for(int i=1; i<=N; i++) {
        bit[i].init(N);
        for(int j=1; j<=N; j++) bit[i].add(j, D[i][j] - D[i][j-1]);
    }
    for(int i=0, x, y; i<N; i++) {
        char q;
        scanf(" %c %d %d", &q, &x, &y);
        if(q == 'U') {
            A[x][y]++;
            int s = y, e = y + 1;
            for(int j=x; j<=N; j++) {
                while(s <= N && bit[j].q(s) == max(bit[j].q(s - 1), bit[j-1].q(s)) + A[j][s]) s++;
                bit[j].add(s, 1);
                bit[j].add(e, -1);
                while(e <= N && bit[j].q(e) < max(bit[j].q(e - 1), bit[j-1].q(e)) + A[j][e]) {
                    bit[j].add(e++, 1);
                    bit[j].add(e, -1);
                }
                ans += e - s;
            }
        }
        else {
            A[x][y]--;
            int s = y, e = y + 1;
            for(int j=x; j<=N; j++) {
                while(s <= N && bit[j].q(s) == max(bit[j].q(s - 1), bit[j-1].q(s)) + A[j][s]) s++;
                bit[j].add(s, -1);
                bit[j].add(e, 1);
                while(e <= N && bit[j].q(e) > max(bit[j].q(e - 1), bit[j-1].q(e)) + A[j][e]) {
                    bit[j].add(e++, -1);
                    bit[j].add(e, 1);
                }
                ans -= e - s;
            }
        }
        printf("%lld\n", ans);
    }
}
