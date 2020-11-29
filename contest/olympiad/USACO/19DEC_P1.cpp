#include <bits/stdc++.h>
using namespace std;

int N, M;
int W[45005], S[45005], E[45005];
int dp[305][305], mx[305][305][305];

int main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> N >> M;
	for(int i=1; i<=M; i++) {
		cin >> W[i] >> S[i] >> E[i];
		for(int k=S[i]; k<=E[i]; k++) mx[k][S[i]][E[i]] = max(mx[k][S[i]][E[i]], W[i]);
	}
	for(int i=1; i<=N; i++) for(int j=1; j<N; j++) for(int k=1; j+k<=N; k++) {
		int s = k, e = j + k;
		mx[i][s][e] = max({ mx[i][s][e], mx[i][s+1][e], mx[i][s][e-1] });
	}
	for(int i=0; i<N; i++) for(int j=1; i+j<=N; j++) {
		int s = j, e = i + j;
		for(int k=s; k<=e; k++) {
			dp[s][e] = max(dp[s][e], dp[s][k-1] + dp[k+1][e] + mx[k][s][e]);
		}
	}
	cout << dp[1][N] << "\n";
}