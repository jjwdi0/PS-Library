#include <bits/stdc++.h>
using namespace std;

int N, M, O[3003][3003], I[3003][3003];
char A[3003][3003];

int main() {
    scanf("%d %d", &N, &M);
    for(int i=1; i<=N; i++) scanf("%s", A[i] + 1);
    for(int i=1; i<=N; i++) for(int j=1; j<=M; j++) {
        O[i][j] += O[i][j-1], I[i][j] += I[i-1][j];
        if(A[i][j] == 'O') O[i][j]++;
        if(A[i][j] == 'I') I[i][j]++;
    }
    long long ans = 0LL;
    for(int i=1; i<=N; i++) for(int j=1; j<=M; j++) if(A[i][j] == 'J')
        ans += 1LL * (O[i][M] - O[i][j]) * (I[N][j] - I[i][j]);
    printf("%lld\n", ans);
}
