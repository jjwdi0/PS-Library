#include <bits/stdc++.h>
#define MOD 1000000007
using namespace std;
using ll = long long;

int N, S[2005][2005];
char A[2005][2005];
ll dp1[2005][2005][2], dp2[2005][2005][2];
ll P[2005*2005], inv[2005*2005];

ll ipow(ll x, int y) {
	if(!y) return 1LL;
	ll u = ipow(x, y >> 1);
	return y & 1 ? u * u % MOD * x % MOD : u * u % MOD;
}

int sum(int a, int b, int x, int y) {
	return S[x][y] - S[a-1][y] - S[x][b-1] + S[a-1][b-1];
}

int main() {
	scanf("%d", &N);
	for(int i=1; i<=N; i++) scanf("%s", A[i] + 1);
	P[0] = 1LL;
	for(int i=1; i<=N*N; i++) P[i] = P[i-1] * 2 % MOD;
	inv[N*N] = ipow(P[N*N], MOD - 2);
	for(int i=N*N-1; ~i; i--) inv[i] = inv[i+1] * 2 % MOD;
	for(int i=1; i<=N; i++) for(int j=1; j<=N; j++) {
		S[i][j] = S[i-1][j] + S[i][j-1] - S[i-1][j-1] + (A[i][j] == '.');
	}
	for(int i=1; i<=N; i++) for(int j=1; j<=N; j++) {
		if(i == 1) {
			dp1[i][j][0] = P[sum(1,1,N,j)-1];
			dp2[i][j][0] = dp1[i][j][0];
		} else {
			dp1[i][j][0] = (P[sum(i,1,N,j)-1] * dp2[i-1][j][1]) % MOD;
			dp2[i][j][0] = dp1[i][j][0] * inv[sum(1,j+1,i-1,N)] % MOD;
		}
		if(A[i][j] != '.') dp1[i][j][0] = dp2[i][j][0] = 0LL;
		dp2[i][j][0] = (dp2[i][j][0] + dp2[i-1][j][0]) % MOD;

		if(j == 1) {
			dp1[i][j][1] = P[sum(1,1,i,N)-1];
			dp2[i][j][1] = dp1[i][j][1];
		} else {
			dp1[i][j][1] = (P[sum(1,j,i,N)-1] * dp2[i][j-1][0]) % MOD;
			dp2[i][j][1] = dp1[i][j][1] * inv[sum(i+1,1,N,j-1)] % MOD;
		}
		if(A[i][j] != '.') dp1[i][j][1] = dp2[i][j][1] = 0LL;
		dp2[i][j][1] = (dp2[i][j][1] + dp2[i][j-1][1]) % MOD;
	}
	ll ans = 0LL;
	for(int i=1; i<=N; i++) ans = (ans + dp1[N][i][1] + dp1[i][N][0]) % MOD;
	printf("%lld\n", ans);
}