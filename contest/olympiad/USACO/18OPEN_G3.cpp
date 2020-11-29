#include <bits/stdc++.h>
using namespace std;

int N, W, D[255][1005], A[255], B[255], C[255], E[255];

int main() {
	scanf("%d %d", &N, &W);
	for(int i=1; i<=N; i++) {
		scanf("%d %d", A+i, B+i);
		C[i] = i;
	}
	sort(C + 1, C + N + 1, [&](const int &x, const int &y) { return B[x] * A[y] < A[x] * B[y]; });
	for(int i=1; i<=N; i++) E[i] = A[C[i]];
	for(int i=1; i<=N; i++) A[i] = A[i-1] + E[i];
	for(int i=1; i<=N; i++) E[i] = B[C[i]];
	for(int i=1; i<=N; i++) B[i] = B[i-1] + E[i];
	for(int i=0; i<=N; i++) for(int j=0; j<=W; j++) D[i][j] = -1e9;
	D[0][0] = 0;
	double ans = 0;
	for(int i=0; i<N; i++) for(int j=0; j<W; j++) if(D[i][j] > -1) {
		D[i+1][j] = max(D[i+1][j], D[i][j]);
		if(j + A[i+1] - A[i] >= W) ans = max(ans, 1.0 * (D[i][j] + B[N] - B[i]) / (j + A[N] - A[i]));
		else D[i+1][j+A[i+1]-A[i]] = max(D[i+1][j+A[i+1]-A[i]], D[i][j] + B[i+1] - B[i]);
	}
	printf("%d\n", int(1000.0 * ans));
}