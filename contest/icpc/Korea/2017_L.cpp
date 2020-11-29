#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pr = pair<int, int>;

int P, N[4], M[4], G[4], H[4][55];
ll D[4][2][55];
vector<pr> v[4][55];

int main() {
    scanf("%d", &P);
	for(int i=1; i<=P; i++) {
		scanf("%d %d", N+i, M+i);
		for(int j=1; j<=N[i]; j++) {
			scanf("%d", &H[i][j]);
			v[i][j].push_back(pr(j, H[i][j]));
		}
		for(int j=0, x, y, z; j<M[i]; j++) {
			scanf("%d %d %d", &x, &y, &z);
			v[i][x].push_back(pr(y, z));
		}
		scanf("%d", G+i);
	}
	for(int i=P+1; i<=3; i++) {
		N[i] = M[i] = G[i] = 1;
		v[i][1].push_back(pr(1, 0));
	}
	for(int i=0; i<4; i++) for(int j=0; j<55; j++) D[i][0][j] = D[i][1][j] = 1e18;
	D[1][0][1] = D[2][0][1] = D[3][0][1] = 0LL;
	ll ans = 1e18;
	for(int i=0; i<126000; i++) {
		int ii = (i + 1) & 1;
		for(int p=1; p<=3; p++) for(int j=0; j<=N[p]; j++) D[p][ii][j] = 1e18;
		for(int p=1; p<=3; p++) for(int j=1; j<=N[p]; j++) if(D[p][i&1][j] < 1e18) {
			for(auto it : v[p][j]) {
				int next = it.first, cost = it.second;
				D[p][ii][next] = min(D[p][ii][next], D[p][i&1][j] + cost);
			}
		}
		for(int p=1; p<=3; p++) ans = min(ans, D[1][i&1][G[1]] + D[2][i&1][G[2]] + D[3][i&1][G[3]]);
	}
	printf("%lld\n", ans);
}
