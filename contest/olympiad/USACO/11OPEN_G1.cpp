#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll D[100005], A[100005];
int N, K;
deque<int> dq;

int main() {
    scanf("%d %d", &N, &K);
    for(int i=1; i<=N; i++) {
        scanf("%lld", A+i);
        A[i] += A[i-1];
    }
    dq.push_back(0);
    for(int i=1; i<=N; i++) {
        if(dq.front() < i - K - 1) dq.pop_front();
        D[i] = D[dq.front()] - A[dq.front()] + A[i - 1];
        while(!dq.empty() && D[dq.back()] - A[dq.back()] <= D[i] - A[i]) dq.pop_back();
        dq.push_back(i);
    }
    ll ans = D[N];
    for(int i=N-K; i<N; i++) ans = max(ans, D[i] + A[N] - A[i]);
    printf("%lld\n", ans);
}
