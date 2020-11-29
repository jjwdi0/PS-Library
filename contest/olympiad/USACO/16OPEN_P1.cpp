#include <bits/stdc++.h>
using namespace std;

int N, A[300005], D[300005][62], ans;

int main() {
    scanf("%d", &N);
    for(int i=1; i<=N; i++) scanf("%d", A+i), D[i][A[i]] = i, ans = max(ans, A[i]);
    for(int j=1; j<=60; j++) {
        for(int i=1; i<=N; i++) {
            if(D[i][j]) continue;
            if(A[i] > j) { D[i][j] = -1; continue; }
            if(D[i][j-1] >= i && D[D[i][j-1]+1][j-1] >= D[i][j-1] + 1) D[i][j] = D[D[i][j-1]+1][j-1];
            else D[i][j] = -1;
            if(D[i][j] > 0) ans = max(ans, j);
        }
    }
    printf("%d\n", ans);
}
