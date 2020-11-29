#include <bits/stdc++.h>
using namespace std;

int N, M, K, A[1505][1505], D1[1505][1505], D2[1505][1505], D3[1505][1505], D4[1505][1505], ans;
int maxrow[1505], maxcol[1505];

int sum(int x, int y) {
    int xx = x - K, yy = y - K;
    if(xx < 0 || yy < 0) return 0;
    return A[x][y] - A[xx][y] - A[x][yy] + A[xx][yy];
}

int main() {
	scanf("%d %d %d", &N, &M, &K);
	for(int i=1; i<=N; i++) for(int j=1; j<=M; j++) scanf("%d", &A[i][j]), A[i][j] += A[i-1][j] + A[i][j-1] - A[i-1][j-1];
	for(int i=K; i<=N; i++) for(int j=K; j<=M; j++) D1[i][j] = max({ D1[i-1][j], D1[i][j-1], sum(i, j) });
	for(int i=K; i<=N; i++) for(int j=M-K+1; j>0; j--) D2[i][j] = max({ D2[i-1][j], D2[i][j+1], sum(i, j + K - 1) });
	for(int i=N-K+1; i>0; i--) for(int j=K; j<=M; j++) D3[i][j] = max({ D3[i+1][j], D3[i][j-1], sum(i + K - 1, j) });
	for(int i=N-K+1; i>0; i--) for(int j=M-K+1; j>0; j--) D4[i][j] = max({ D4[i+1][j], D4[i][j+1], sum(i + K - 1, j + K - 1) });
	for(int i=1; i<=N; i++) for(int j=1; j<=M; j++) maxrow[i] = max(maxrow[i], sum(i, j));
	for(int i=1; i<=M; i++) for(int j=1; j<=N; j++) maxcol[i] = max(maxcol[i], sum(j, i));
	for(int i=1; i<=N; i++) for(int j=1; j<=M; j++) ans = max({ ans, D1[i][j] + D2[i][j+1] + D4[i+1][1], D2[i][j] + D4[i+1][j] + D3[1][j-1], D4[i][j] + D3[i][j-1] + D1[i-1][M], D3[i][j] + D1[i-1][j] + D2[N][j+1] });
	for(int i=K; i<=N; i++)  {
        int u = 0;
        for(int j=i+K; j<=N-K; j++) {
            u = max(u, maxrow[j]);
            ans = max(ans, D1[i][M] + u + D4[j+1][1]);
        }
	}
	for(int i=K; i<=M; i++) {
        int u = 0;
        for(int j=i+K; j<=M-K; j++) {
            u = max(u, maxcol[j]);
            ans = max(ans, D1[N][i] + u + D4[1][j+1]);
        }
	}
	printf("%d\n", ans);
}
