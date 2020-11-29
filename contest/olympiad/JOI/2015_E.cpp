#include <bits/stdc++.h>
using namespace std;
using pr = pair<int, int>;

struct BIT {
    int tree[4005], base;
    void init(int x) { base = x; }
    void add(int x, int y) { while(x <= base) tree[x] += y, x += x & -x; }
    int q(int x) {
        int res = 0;
        while(x) res += tree[x], x -= x & -x;
        return res;
    }
} bit[8005];

int N, M, minL, K;
short A[4005][4005];
short L[4005][4005], R[4005][4005], U[4005][4005], D[4005][4005];
priority_queue<pr, vector<pr>, greater<pr>> pq[8005];

int main() {
    scanf("%d %d %d %d", &N, &M, &minL, &K);
    if(N > M) {
        for(int i=1; i<=N; i++) for(int j=M+1; j<=N; j++) A[i][j] = 1;
        M = N;
    }
    else {
        for(int i=N+1; i<=M; i++) for(int j=1; j<=M; j++) A[i][j] = 1;
        N = M;
    }
    for(int i=0, x, y; i<K; i++) scanf("%d %d", &x, &y), A[x][y] = 1;
    for(int i=1; i<=N; i++) for(int j=1; j<=M; j++) if(A[i][j]) {
        for(int k=1, c=0; i-k   &&!A[i-k][j]; k++) D[i-k][j] = ++c;
        for(int k=1, c=0; j-k   &&!A[i][j-k]; k++) R[i][j-k] = ++c;
        for(int k=1, c=0; i+k<=N&&!A[i+k][j]; k++) U[i+k][j] = ++c;
        for(int k=1, c=0; j+k<=M&&!A[i][j+k]; k++) L[i][j+k] = ++c;
    }
    for(int i=1; i<=N; i++) for(int j=1; j<=M; j++) if(!A[i][j]) {
        if(!D[i][j]) D[i][j] = N - i + 1;
        if(!L[i][j]) L[i][j] = j;
        if(!U[i][j]) U[i][j] = i;
        if(!R[i][j]) R[i][j] = M - j + 1;
    }
    for(int i=1; i<N+M; i++) bit[i].init(N);
    long long ans = 0LL;
    for(int i=1; i<=N; i++) for(int j=1; j<=M; j++) if(!A[i][j]) {
        int idx = j - i + N, sub = min(i, j);
        int mx = N - abs(i - j) - sub + 1;
        pq[idx].push(pr(min(R[i][j], D[i][j]) - mx, sub));
        bit[idx].add(sub, 1);
        while(!pq[idx].empty() && pq[idx].top().first <= -mx) {
            bit[idx].add(pq[idx].top().second, -1);
            pq[idx].pop();
        }
        int l = sub - min(L[i][j], U[i][j]), r = sub - minL + 1;
        if(l < r) ans += bit[idx].q(r) - bit[idx].q(l);
    }
    printf("%lld\n", ans);
}
