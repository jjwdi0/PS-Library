#include <bits/stdc++.h>
using namespace std;

int T, N, A[100005][2];
int dp[100005][3];

int main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> T;
	while(T--) {
		cin >> N;
		for(int i=0; i<2; i++) for(int j=1; j<=N; j++) cin >> A[j][i];
		for(int i=1; i<=N; i++) {
			dp[i][0] = max({ dp[i-1][0], dp[i-1][1], dp[i-1][2] });
			dp[i][1] = max(dp[i-1][0], dp[i-1][2]) + A[i][0];
			dp[i][2] = max(dp[i-1][0], dp[i-1][1]) + A[i][1];
		}
		cout << max({ dp[N][0], dp[N][1], dp[N][2] }) << "\n";
	}
}