#include <bits/stdc++.h>
using namespace std;
#define INF 1987654321

int dp[103][103][103][4], n, a[3][103], sz[3], ind[3];

int f(int x, int y) {
	int num[3];
	if(x == 0) {
		num[0] = a[0][ind[0]-1];
		num[1] = (num[0] + n / 3 - 1) % n + 1;
		num[2] = (num[0] + n / 3 * 2 - 1) % n + 1;
	}
	if(x == 1) {
		num[1] = a[1][ind[1]-1];
		num[0] = (num[1] + n / 3 * 2 - 1) % n + 1;
		num[2] = (num[1] + n / 3 - 1) % n + 1;
	}
	if(x == 2) {
		num[2] = a[2][ind[2]-1];
		num[0] = (num[2] + n / 3 - 1) % n + 1;
		num[1] = (num[2] + n / 3 * 2 - 1) % n + 1;
	}
	return abs(num[y] - a[y][ind[y]]);
}

int main() {
	scanf("%d", &n);
	for(int i=0; i<3; i++) {
		scanf("%d", sz+i);
		for(int j=0; j<sz[i]; j++) {
			scanf("%d", &a[i][j]);
		}
	}
	for(int i=0; i<=sz[0]+1; i++) for(int j=0; j<=sz[1]+1; j++) for(int k=0; k<=sz[2]+1; k++) for(int p=0; p<3; p++) dp[i][j][k][p]=INF;
	dp[1][0][0][0] = min(a[0][0] - 1, n - a[0][0] + 1);
	dp[0][1][0][1] = min(abs(a[1][0] - n / 3 - 1), n - abs(a[1][0] - n / 3 - 1));
	dp[0][0][1][2] = min(abs(a[2][0] - n / 3 * 2 - 1), n - abs(a[2][0] - n / 3 * 2 - 1));
	for(ind[0]=0; ind[0]<=sz[0]; ind[0]++) {
		for(ind[1]=0; ind[1]<=sz[1]; ind[1]++) {
			for(ind[2]=0; ind[2]<=sz[2]; ind[2]++) {
				for(int p=0; p<3; p++) {
					if(dp[ind[0]][ind[1]][ind[2]][p]!=INF) {
						dp[ind[0]+1][ind[1]][ind[2]][0] = min(dp[ind[0]+1][ind[1]][ind[2]][0], dp[ind[0]][ind[1]][ind[2]][p] + min(abs(f(p, 0)), n - abs(f(p, 0))));
						dp[ind[0]][ind[1]+1][ind[2]][1] = min(dp[ind[0]][ind[1]+1][ind[2]][1], dp[ind[0]][ind[1]][ind[2]][p] + min(abs(f(p, 1)), n - abs(f(p, 1))));
						dp[ind[0]][ind[1]][ind[2]+1][2] = min(dp[ind[0]][ind[1]][ind[2]+1][2], dp[ind[0]][ind[1]][ind[2]][p] + min(abs(f(p, 2)), n - abs(f(p, 2))));
					}
				}
			}
		}
	}
	int ans = 1987654321;
	for(int i=0; i<3; i++) ans = min(ans, dp[sz[0]][sz[1]][sz[2]][i]);
	printf("%d", ans);
}