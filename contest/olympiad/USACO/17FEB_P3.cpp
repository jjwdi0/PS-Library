#include <bits/stdc++.h>
#define SQRT 1000
using namespace std;
typedef long long ll;

struct Bucket {
    int sum[SQRT], st[200005];
    void add(int x, int y) { st[x] += y, sum[x / SQRT] += y; }
    int q(int s, int e) {
        int res = 0;
        if(s / SQRT + 1 >= e / SQRT) {
            for(int i=s; i<=e; i++) res += st[i];
            return res;
        }
        else {
            int l = s, r = e;
            while(l / SQRT == s / SQRT) res += st[l++];
            while(r / SQRT == e / SQRT) res += st[r--];
            for(int i=l/SQRT; i<=r/SQRT; i++) res += sum[i];
            return res;
        }
    }
}B;

struct query {
    int s, e, num, ti;
    bool operator < (const query &A) const { return s / SQRT == A.s / SQRT ? e < A.e : s < A.s; }
}T[100005];

int N, K, A[200005], chk[200005], on;
ll ans;

void f(int x, int y) {
    if(chk[x] == 2) B.add(x, -1), on--;
    chk[x] += y;
    if(chk[x] == 2) B.add(x, 1), on++;
}

int main() {
    scanf("%d %d", &N, &K);
    for(int i=1; i<=N*2; i++) scanf("%d", A+i);
    for(int i=1; i<=N*2; i++) {
        if(i <= N) T[A[i]].s = i;
        else T[A[i]].e = i;
    }
    sort(T + 1, T + 1 + N);
    int s = 1, e = 0;
    for(int i=1; i<=N; i++) {
        while(T[i].e > e) f(A[++e], 1);
        while(T[i].e < e) f(A[e--], -1);
        while(T[i].s > s) f(A[s++], -1);
        while(T[i].s < s) f(A[--s], 1);
        int u = min(N, A[s] + K);
        int d = max(0, A[s] - K - 1);
        ans += (ll)(on - B.q(d + 1, u));
    }
    printf("%lld\n", ans);
}
