#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define sz(x) ((int)(x).size())
using namespace std;

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

int N, A[100005], L[100005], R[100005];
vector<int> v;

int main() {
    scanf("%d", &N);
    for(int i=1; i<=N; i++) scanf("%d", A+i), v.push_back(A[i]);
    sort(all(v));
    bit.init(sz(v));
    for(int i=1, idx; i<=N; i++) {
        idx = (int)(lower_bound(all(v), A[i]) - v.begin()) + 1;
        L[i] = bit.q(N) - bit.q(idx);
        bit.add(idx, 1);
    }
    for(int i=1; i<=N; i++) bit.add(i, -1);
    for(int i=N, idx; i; i--) {
        idx = (int)(lower_bound(all(v), A[i]) - v.begin()) + 1;
        R[i] = bit.q(N) - bit.q(idx);
        bit.add(idx, 1);
    }
    int ans = 0;
    for(int i=1; i<=N; i++) ans += (L[i] > R[i] + R[i] || R[i] > L[i] + L[i]);
    printf("%d\n", ans);
}
