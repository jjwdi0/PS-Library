#include <bits/stdc++.h>
using namespace std;

int N, M, A[5003][5003];

int main() {
    scanf("%d %d", &N, &M);
    for(int i=0, x, y, z; i<M; i++) {
        scanf("%d %d %d", &x, &y, &z);
        A[x][y]++, A[x+z+1][y]--, A[x+z+2][y+1]++, A[x][y+1]--, A[x+z+1][y+z+2]++, A[x+z+2][y+z+2]--;
    }
    for(int i=1; i<=N; i++) for(int j=1; j<=N; j++) A[i][j] += A[i-1][j];
    for(int i=1; i<=N; i++) for(int j=1; j<=N; j++) A[i][j] += A[i][j-1];
    for(int i=1; i<=N; i++) for(int j=1; j<=N; j++) A[i][j] += A[i-1][j-1];
    int ans = 0;
    for(int i=1; i<=N; i++) for(int j=1; j<=N; j++) ans += A[i][j] > 0;
    printf("%d\n", ans);
}
