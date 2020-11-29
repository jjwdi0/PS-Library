#include <bits/stdc++.h>
using namespace std;

int N, K, D[404][404], A[404];

int main() {
	scanf("%d %d", &N, &K), K++;
	for(int i=1; i<=N; i++) scanf("%d", A+i), A[i] += A[i-1];
	for(int i=1; i<=N; i++) D[i][0] = 1e9;
	for(int i=1; i<=N; i++) for(int j=1; j<=K; j++) {
	    D[i][j] = D[i][j-1];
        int mx = 0;
        for(int k=i; k; k--) {
            mx = max(mx, A[k] - A[k-1]);
            D[i][j] = min(D[k-1][j-1] + mx * (i - k + 1), D[i][j]);
        }
	}
	printf("%d\n", D[N][K] - A[N]);
}
