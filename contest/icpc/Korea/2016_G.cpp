#include <bits/stdc++.h>
using namespace std;

int A[1003][1003], par[1111111], N, M;
int d[4][2] = {1, 0, -1, 0, 0, 1, 0, -1};

int get(int x, int y) {
	return (x < 0 || y < 0 || x >= N || y >= M) ? -1 : A[x][y];
}

int find(int x) {
	if(par[x] == x) return x;
	return par[x] = find(par[x]);
}

void uni(int x, int y) {
	x = find(x); y = find(y);
	par[max(x, y)] = min(x, y);
}

int main() {
	scanf("%d %d", &N, &M);
	for(int i=0; i<N; i++) for(int j=0; j<M; j++) par[i*M+j] = i * M + j;
	for(int i=0; i<N; i++) for(int j=0; j<M; j++) scanf("%1d", &A[i][j]);
	for(int i=0; i<N; i++) for(int j=0; j<M; j++) {
		for(int k=0; k<4; k++) {
			int x = i + d[k][0], y = j + d[k][1];
			if(A[i][j] == get(x, y)) uni(i * M + j, x * M + y);
		}
	}
	for(int i=0; i<M; i++) {
		if(!A[N-1][i] && find((N - 1) * M + i) < M)return puts("YES"),0;
	}
	puts("NO");
}