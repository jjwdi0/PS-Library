#include <bits/stdc++.h>
using namespace std;

int N, A[1005];

bool ok(int x, int y) {
    for(int i=1; x-i-i>=0; i++) if(y == A[x-i] + A[x-i] - A[x-i-i]) return 0;
    return 1;
}

int main() {
    scanf("%d", &N);
    A[0] = A[1] = 1;
    for(int i=2; i<=N; i++) {
        for(int j=1; j<=100; j++) if(ok(i, j)) { A[i] = j; break; }
    }
    printf("%d\n", A[N]);
}
