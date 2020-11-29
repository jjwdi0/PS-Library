#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int N, A[4005];
ll D[4005][4005], ans;

ll f(int s, int e) {
    if(D[s][e]) return D[s][e];
    if(s == e) return D[s][e] = A[s];
    if(s > e) return 0;
    if(A[s+1] < A[e]) D[s][e] = max(D[s][e], f(s + 1, e - 1) + A[s]);
    else D[s][e] = max(D[s][e], f(s + 2, e) + A[s]);
    if(A[s] < A[e-1]) D[s][e] = max(D[s][e], f(s, e - 2) + A[e]);
    else D[s][e] = max(D[s][e], f(s + 1, e - 1) + A[e]);
    return D[s][e];
}

int main() {
    scanf("%d", &N);
    for(int i=1; i<=N; i++) scanf("%d", A+i), A[N + i] = A[i];
    for(int i=1; i<=N; i++) {
        if(A[i+1] < A[N+i-1]) ans = max(ans, f(i + 1, N + i - 2) + A[i]);
        else ans = max(ans, f(i + 2, N + i - 1) + A[i]);
    }
    printf("%lld\n", ans);
}
