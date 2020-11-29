#include <stdio.h>
using ll = long long;

int N, L, R, T;
ll D[22][22][22];

int main() {
	D[1][1][1] = 1LL;
	for(int i=1; i<20; i++) for(int j=1; j<=i; j++) for(int k=1; k<=i; k++) if(D[i][j][k]) D[i+1][j+1][k] += D[i][j][k], D[i+1][j][k] += D[i][j][k] * (ll)(i-1), D[i+1][j][k+1] += D[i][j][k];
	for(scanf("%d", &T); T--;) {
		int x, y, z;
		scanf("%d %d %d", &x, &y, &z);
		printf("%lld\n", D[x][y][z]);
	}
}