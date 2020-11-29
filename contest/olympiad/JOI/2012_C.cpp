#include <bits/stdc++.h>
using namespace std;

int N, K, S, D[3005][3005], A[3005][2];

int main() {
    scanf("%d %d %d", &N, &K, &S);
    for(int i=0; i<N; i++) scanf("%d %d", &A[i][0], &A[i][1]);
    for(int i=0; i<=3000; i++) for(int j=0; j<=3000; j++) D[i][j] = -1;
    D[0][0] = 0;
    for(int i=0; i<N; i++) for(int j=0; j<=K; j++) if(~D[i][j]) {
        D[i+1][j] = max(D[i+1][j], D[i][j]);
        if(j + A[i][1] > K) continue;
        if(j < S && j + A[i][1] > S) {
            if(S+A[i][1] <= K) D[i+1][S+A[i][1]] = max(D[i+1][S+A[i][1]], D[i][j] + A[i][0]);
        }
        else D[i+1][j+A[i][1]] = max(D[i+1][j+A[i][1]], D[i][j] + A[i][0]);
    }
    int ans = 0;
    for(int i=0; i<=K; i++) ans = max(ans, D[N][i]);
    printf("%d\n", ans);
}
