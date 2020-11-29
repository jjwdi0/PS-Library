#include <bits/stdc++.h>
using namespace std;

int M, N, A[10005], B[503][2], D[10005][2];

int main() {
    scanf("%d %d", &M, &N);
    for(int i=1; i<=M; i++) scanf("%d", A+i);
    for(int i=0; i<N; i++) scanf("%d%d", &B[i][0], &B[i][1]);
    sort(A+1, A+M+1, greater<int>());
    for(int i=1; i<=M; i++) A[i] += A[i-1];
    for(int i=0; i<=M; i++) D[i][0] = D[i][1] = -1;
    D[0][0] = 0;
    for(int i=0; i<N; i++) for(int j=0; j<=M; j++) if(~D[j][i&1]) {
        D[j][(i+1)&1] = max(D[j][(i+1)&1], D[j][i&1]);
        D[min(j + B[i][0], M)][(i+1)&1] = max(D[min(j + B[i][0], M)][(i+1)&1], D[j][i&1] + A[min(j + B[i][0], M)] - A[j] - B[i][1]);
    }
    int ans = 0;
    for(int i=0; i<=M; i++) ans = max(ans, D[i][N&1]);
    printf("%d\n", ans);
}
