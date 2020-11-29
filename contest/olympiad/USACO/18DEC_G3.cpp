#include <bits/stdc++.h>
using namespace std;

int N, K, A[10005], D[10005];

int main() {
    scanf("%d %d", &N, &K);
    for(int i=1; i<=N; i++) scanf("%d", A+i);
    for(int i=1; i<=N; i++) {
        int mx = A[i];
        for(int j=1; j<=min(i, K); j++) {
            D[i] = max(D[i], D[i-j] + mx * j);
            mx = max(mx, A[i-j]);
        }
    }
    printf("%d\n", D[N]);
}
