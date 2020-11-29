#include <bits/stdc++.h>
using namespace std;

int N, K, A[100005], lev[100005], st[100005][18];
int B[100005], ans;
vector<int> v[100005];

void dfs(int x, int p) {
	lev[x] = lev[p] + 1;
	st[x][0] = p;
	for(int it : v[x]) if(it != p) dfs(it, x);
}

int LCA(int x, int y) {
	if(lev[x] > lev[y]) swap(x, y);
	for(int i=0; i<18; i++) if((lev[y] - lev[x]) & (1 << i)) y = st[y][i];
	if(x == y) return x;
	for(int i=17; ~i; i--) if(st[x][i] != st[y][i]) x = st[x][i], y = st[y][i];
	return st[x][0];
}

void cal(int x, int p) {
	for(int it : v[x]) if(it != p) cal(it, x), B[x] += B[it];
	ans += !!(B[x]);
}

int main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> N >> K;
	for(int i=1, x, y, z; i<N; i++) {
		cin >> x >> y >> z;
		v[x].push_back(y);
		v[y].push_back(x);
	}
	dfs(1, 0);
	for(int i=1; i<18; i++) for(int j=1; j<=N; j++) st[j][i] = st[st[j][i-1]][i-1];
	for(int i=1; i<=K; i++) cin >> A[i];
	int lca = A[1];
	for(int i=2; i<=K; i++) lca = LCA(lca, A[i]);
	for(int i=1; i<=K; i++) B[A[i]]++, B[st[lca][0]]--;
	cal(1, 0);
	cout << ans << "\n";
}