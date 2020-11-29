#include <stdio.h>
#include <string.h>

char goal[25], a[105], b[105];
int alen, blen, cnt, dp[2][105][105], glen;

int f(int func, int x, int y) {
	if(x == glen) {
		return dp[func][x][y] = 1;
	}
	if(dp[func][x][y] + 1) return dp[func][x][y];
	if(func == 0) {
		if(y == alen) return dp[func][x][y] = 0;
		for(int it=y; it<alen; it++) {
			if(a[it] == goal[x]) {
				dp[func][x][y] += f(1 - func, x + 1, it + 1);
			}
		}
		dp[func][x][y]++;
		return dp[func][x][y];
	} else {
		if(y==blen)return dp[func][x][y]=0;
		for(int it=y; it<blen; it++) {
			if(b[it] == goal[x]) {
				dp[func][x][y] += f(1 - func, x + 1, it + 1);
			}
		}
		dp[func][x][y]++;
		return dp[func][x][y];
	}
}

int main() {
	scanf("%s\n%s\n%s", goal, a, b);
	alen = strlen(a);
	blen = strlen(b);
	glen = strlen(goal);
	for(int i=0; i<2; i++) for(int j=0; j<105; j++) for(int k=0; k<105; k++) dp[i][j][k] = -1;
	for(int i=0; i<alen; i++) {
		if(a[i] == goal[0]) {
			cnt += f(1, 1, i + 1);
		}
		if(b[i] == goal[0]) {
			cnt += f(0, 1, i + 1);
		}
	}
	printf("%d", cnt);
}