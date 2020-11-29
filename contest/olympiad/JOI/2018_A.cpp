#include <bits/stdc++.h>
using namespace std;

int N, K, A[100005], ans;
priority_queue<int> pq;

int main() {
    scanf("%d %d", &N, &K);
    for(int i=1; i<=N; i++) scanf("%d", A+i);
    ans = A[N] - A[1] + 1;
    for(int i=1; i<N; i++) pq.push(A[i+1] - A[i] - 1);
    for(int i=1; i<K; i++) { ans -= pq.top(); pq.pop(); }
    printf("%d\n", ans);
}
