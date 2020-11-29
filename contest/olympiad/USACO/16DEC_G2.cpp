#include <stdio.h>
typedef long long ll;
const ll INF = 98765432111111;

int N, M, A[2][1003][2], B[1003][2];
ll D[1003][1003][2];
ll min(ll X, ll Y){return X>Y?Y:X;}
ll sz(ll x){return x*x;}
ll dist(int x1, int y1, int x2, int y2){return sz(x1 - x2) + sz(y1 - y2);}
int main() {
	scanf("%d %d", &N, &M);
	for(int i=0; i<N; i++) scanf("%d %d", &A[0][i][0], &A[0][i][1]);
	for(int i=0; i<M; i++) scanf("%d %d", &A[1][i][0], &A[1][i][1]);
	for(int i=0; i<=N; i++) for(int j=0; j<=M; j++) D[i][j][0] = D[i][j][1] = INF;
	D[1][0][0] = 0LL;
	for(int i=1; i<=N; i++) {
		for(int j=0; j<=M; j++) {
			for(int k=0; k<2; k++) {
				if(D[i][j][k] != INF) {
					if(i < N) D[i+1][j][0] = min(D[i][j][k] + dist(A[k][(k?j:i)-1][0], A[k][(k?j:i)-1][1], A[0][i][0], A[0][i][1]), D[i+1][j][0]);
					if(j < M) D[i][j+1][1] = min(D[i][j][k] + dist(A[k][(k?j:i)-1][0], A[k][(k?j:i)-1][1], A[1][j][0], A[1][j][1]), D[i][j+1][1]);
				}
			}
		}
	}
	printf("%lld", D[N][M][0]);
}