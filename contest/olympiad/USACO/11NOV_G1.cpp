#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct BIT {
    int tree[100005];
    int base;
    void init(int x) { base = x + 2; }
    void add(int x, int y) {
        x += 2;
        while(x <= base) tree[x] += y, x += x & -x;
    }
    int q(int x) {
        int res = 0;
        x += 2;
        while(x) res += tree[x], x -= x & -x;
        return res;
    }
}bit;

int N, P, input[100005];
ll A[100005], B[100005], ans;

int get_idx(ll x) { return (int)(upper_bound(B, B+N+1, x) - B); }

int main() {
    scanf("%d %d", &N, &P);
    bit.init(N + 1);
    for(int i=1; i<=N; i++) scanf("%d", input + i), input[i] = (input[i] >= P ? 1 : -1);
    for(int i=1; i<=N; i++) A[i] = A[i-1] + (ll)input[i], B[i] = A[i];
    sort(B, B+N+1);
    for(int i=0; i<=N; i++) bit.add(get_idx(B[i]), 1);
    for(int i=N; i; i--) {
        int idx = get_idx(A[i]);
        bit.add(idx, -1);
        ans += bit.q(idx);
    }
    printf("%lld\n", ans);
}
