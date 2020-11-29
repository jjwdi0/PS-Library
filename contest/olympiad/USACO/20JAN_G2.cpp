#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pr = pair<int, int>;

int N, Q, A[5005];
pr B[5005];
ll D[5005][5005];

int f(int s, int e, int x) {
	return upper_bound(B + 1, B + N + 1, pr(x, e)) - lower_bound(B + 1, B + N + 1, pr(x, s));
}

int main() {
	scanf("%d %d", &N, &Q);
	for(int i=1; i<=N; i++) {
		scanf("%d", A+i);
		B[i] = pr(A[i], i);
	}
	sort(B + 1, B + N + 1);
	for(int i=2; i<=N; i++) for(int j=1; i+j<=N; j++) {
		int s = j, e = i + j;
		D[s][e] = D[s+1][e] + D[s][e-1] - D[s+1][e-1] + f(s + 1, e - 1, -(A[s] + A[e]));
	}
	while(Q--) {
		int x, y;
		scanf("%d %d", &x, &y);
		printf("%lld\n", D[x][y]);
	}
}