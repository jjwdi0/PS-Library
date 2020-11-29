#include <bits/stdc++.h>
using namespace std;

int N, A[1003][2], D[1003][1003];

bool f(int x, int y) {return abs(x - y) <= 4;}

int main() {
    scanf("%d", &N);
    for(int i=1; i<=N; i++) scanf("%d", &A[i][0]);
    for(int i=1; i<=N; i++) scanf("%d", &A[i][1]);
    for(int i=1; i<=N; i++) for(int j=1; j<=N; j++) {
        if(f(A[i][0], A[j][1])) D[i][j] = D[i-1][j-1] + 1;
        else D[i][j] = max(D[i-1][j], D[i][j-1]);
    }
    printf("%d\n", D[N][N]);
}