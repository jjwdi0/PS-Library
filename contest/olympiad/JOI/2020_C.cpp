#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int N, L, X[205], T[205];
ll D[205][205][205][2];

int dist(int x, int y) { return min({ abs(X[x] - X[y]), L + X[x] - X[y], L + X[y] - X[x] }); }

int main() {
	scanf("%d %d", &N, &L);
	for(int i=1; i<=N; i++) scanf("%d", X+i);
	for(int i=1; i<=N; i++) scanf("%d", T+i);
	X[0] = X[N+1] = L;
	for(int i=0; i<=N+1; i++) for(int j=0; j<=N+1; j++) for(int k=0; k<=N+1; k++) for(int p=0; p<2; p++) D[i][j][k][p] = 1e18;
	D[0][N+1][0][0] = D[0][N+1][0][1] = 0;
	for(int i=N+1; i; i--) for(int j=0; i+j<=N+1; j++) for(int k=0; k<=N+1-i; k++) {
		int s = j, e = i + j;
		if(D[s][e][k][0] > 1e15 && D[s][e][k][1] > 1e15) continue;
		int dist1 = dist(s + 1, s), dist2 = dist(s + 1, e);
		int can1 = (D[s][e][k][0] + dist1 <= 1LL * T[s+1] && e != s + 1);
		int can2 = (D[s][e][k][1] + dist2 <= 1LL * T[s+1] && e != s + 1);
		D[s+1][e][k+can1][0] = min(D[s+1][e][k+can1][0], D[s][e][k][0] + dist1);
		D[s+1][e][k+can2][0] = min(D[s+1][e][k+can2][0], D[s][e][k][1] + dist2);

		int dist3 = dist(e - 1, s), dist4 = dist(e - 1, e);
		int can3 = (D[s][e][k][0] + dist3 <= 1LL * T[e-1] && s != e - 1);
		int can4 = (D[s][e][k][1] + dist4 <= 1LL * T[e-1] && s != e - 1);
		D[s][e-1][k+can3][1] = min(D[s][e-1][k+can3][1], D[s][e][k][0] + dist3);
		D[s][e-1][k+can4][1] = min(D[s][e-1][k+can4][1], D[s][e][k][1] + dist4);
	}
	int ans = 0;
	for(int i=1; i<=N; i++) for(int j=0; j<=N; j++) if(D[i][i][j][0] <= 1e15 || D[i][i][j][1] <= 1e15) ans = max(ans, j);
	printf("%d\n", ans);
}
