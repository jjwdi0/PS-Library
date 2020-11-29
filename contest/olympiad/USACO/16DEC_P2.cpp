#include <bits/stdc++.h>
#define MOD 1000000009
using namespace std;
using ll = long long;
using pr = pair<int, int>;

int N, M, K;
ll D[2005][11][11];
pr A[2005];

int main() {
	scanf("%d %d %d", &N, &M, &K);
	for(int i=1, x; i<=N; i++) scanf("%d", &x), A[i] = pr(x, 1);
	for(int i=1, x; i<=M; i++) scanf("%d", &x), A[i+N] = pr(x, 2);
	sort(A + 1, A + N + M + 1);
	D[0][0][0] = 1LL;
	for(int i=1; i<=N+M; i++) for(int j=0; j<=K; j++) for(int k=0; k<=K; k++) {
		D[i][j][k] += D[i-1][j][k];
		if(A[i].second == 1 && j && j <= k) D[i][j][k] += D[i-1][j-1][k];
		if(A[i].second == 2 && k) D[i][j][k] += D[i-1][j][k-1];
		D[i][j][k] %= MOD;
	}
	printf("%lld\n", D[N+M][K][K]);
}
