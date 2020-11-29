#include <bits/stdc++.h>
using namespace std;

int N, K, D[100005][3][22], A[100005];

int main() {
    scanf("%d %d", &N, &K);
    for(int i=1; i<=N; i++) {
        char x;
        scanf(" %c", &x);
        A[i] = (x == 'H' ? 0 : (x == 'P' ? 1 : 2));
    }
    D[1][(A[1]+1)%3][0] = 1;
    for(int i=2; i<=N; i++) for(int j=0; j<3; j++) for(int k=0; k<=K; k++) {
        for(int it=0; it<3; it++) {
            if(it == j) D[i][j][k] = max(D[i-1][j][k] + (A[i] == (j + 2) % 3), D[i][j][k]);
            else if(k) D[i][j][k] = max(D[i-1][it][k-1] + (A[i] == (j + 2) % 3), D[i][j][k]);
        }
    }
    printf("%d\n", max({ D[N][0][K], D[N][1][K], D[N][2][K] }));
}
