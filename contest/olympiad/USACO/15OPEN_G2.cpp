#include <bits/stdc++.h>
#define MOD 1000000007
#define X first
#define Y second
using namespace std;
typedef long long ll;
typedef pair<int, int> pr;

char a[503][503];
int n;
ll dp[2][503][503];

char get(int x, int y) {
	if(x < 0 || y < 0 || x >= n || y >= n) return '?';
	return a[x][y];
}

int main() {
	scanf("%d", &n);
	for(int i=0; i<n; i++) {
		scanf("%s", a[i]);
	}
	if(a[0][0] == a[n-1][n-1]) dp[0][0][0] = 1LL;
	for(int i=0; i<n-1; i++) {
		for(int j=0; j<=i; j++) {
			for(int k=0; k<=i; k++) {
				if(dp[i%2][j][k]) {
					if(dp[i%2][j][k] >= MOD) dp[i%2][j][k] %= MOD;
					pr t1 = {j, i - j};
					pr t2 = {n - 1 - k, n - 1 - i + k};
					if(get(t1.X + 1, t1.Y) == get(t2.X - 1, t2.Y)) dp[!(i&1)][j+1][k+1] += dp[i%2][j][k];
					if(get(t1.X + 1, t1.Y) == get(t2.X, t2.Y - 1)) dp[!(i&1)][j+1][k] += dp[i%2][j][k];
					if(get(t1.X, t1.Y + 1) == get(t2.X - 1, t2.Y)) dp[!(i&1)][j][k+1] += dp[i%2][j][k];
					if(get(t1.X, t1.Y + 1) == get(t2.X, t2.Y - 1)) dp[!(i&1)][j][k] += dp[i%2][j][k];
					dp[i%2][j][k]=0LL;
				}
			}
		}
	}
	ll ans = 0;
	for(int i=0; i<n; i++) {
		ans += dp[!(n%2)][i][n-1-i];
		if(ans >= MOD) ans %= MOD;
	}
	printf("%lld", ans);
}