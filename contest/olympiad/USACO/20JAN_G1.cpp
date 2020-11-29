#include <bits/stdc++.h>
using namespace std;

int N, M, K, D[1005][1005], A[1005];
vector<int> v[1005];

int main() {
	scanf("%d %d %d", &N, &M, &K);
	for(int i=1; i<=N; i++) scanf("%d", A+i);
	for(int i=0, x, y; i<M; i++) {
		scanf("%d %d", &x, &y);
		v[x].push_back(y);
	}
	for(int i=0; i<=1000; i++) for(int j=1; j<=N; j++) D[i][j] = -1e9;
	D[0][1] = 0;
	for(int i=0; i<1000; i++) for(int j=1; j<=N; j++) if(D[i][j] >= 0) {
		for(auto it : v[j]) D[i+1][it] = max(D[i+1][it], A[it] + D[i][j] - K * (2 * i + 1));
	}
	int ans = 0;
	for(int i=0; i<=1000; i++) ans = max(ans, D[i][1]);
	printf("%d\n", ans);
}
