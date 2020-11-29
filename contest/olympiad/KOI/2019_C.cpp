#include <bits/stdc++.h>
using namespace std;

int N, B, Q, D1[5005][5005], D2[5005][5005], sz[5005], ans, L[5005], R[5005];
vector<int> v[5005], query[5005];
bool chk[5005];

void dfs(int x, int p) {
	sz[x] = 1;
	D1[x][chk[x]] = D2[x][chk[x]] = 1;
	for(auto it : v[x]) if(it != p) {
		dfs(it, x);
		for(int i=min(B, sz[x]); ~i; i--) for(int j=min(B-i, sz[it]); ~j; j--) {
			D1[x][i+j] = min(D1[x][i+j], D1[x][i] + D1[it][j]);
			D2[x][i+j] = max(D2[x][i+j], D2[x][i] + D2[it][j]);
		}
		sz[x] += sz[it];
	}
	for(int i=0; i<=sz[x] && i<=B; i++) L[i] = min(D1[x][i], L[i]), R[i] = max(D2[x][i], R[i]);
}

int main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> N >> B;
	for(int i=0, x; i<B; i++) {
		cin >> x;
		chk[x] = 1;
		L[i] = N;
	}
	L[B] = N;
	for(int i=1, x, y; i<N; i++) {
		cin >> x >> y;
		v[x].push_back(y), v[y].push_back(x);
	}
	for(int i=1; i<=N; i++) for(int j=0; j<=B; j++) D1[i][j] = 1e9, D2[i][j] = -1e9;
	dfs(1, 0);
	cin >> Q;
	while(Q--) {
		int x, y;
		cin >> x >> y;
		ans += (L[y] <= x && x <= R[y]);
	}
	cout << ans << '\n';
}