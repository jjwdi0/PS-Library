#include <bits/stdc++.h>
using namespace std;
using pr = pair<int, int>;
using tr = pair<int, pr>;

int N, Q, par[100005], sz[100005], ans[100005];
tr A[100005], B[100005];

int f(int x) { return par[x] = (par[x] == x ? x : f(par[x])); }
void uni(int x, int y) {
	x = f(x), y = f(y);
	sz[x] += sz[y];
	par[y] = x;
}

int main() {
	scanf("%d %d", &N, &Q);
	iota(par, par + N + 1, 0);
	fill(sz, sz + N + 1, 1);
	for(int i=1, x, y, z; i<N; i++) {
		scanf("%d %d %d", &x, &y, &z);
		A[i] = tr(-z, pr(x, y));
	}
	sort(A + 1, A + N);
	for(int i=1, x, y; i<=Q; i++) {
		scanf("%d %d", &x, &y);
		B[i] = tr(-x, pr(y, i));
	}
	sort(B + 1, B + Q + 1);
	int idx = 1;
	for(int i=1; i<=Q; i++) {
		int w = B[i].first;
		while(idx < N && A[idx].first <= w) {
			uni(A[idx].second.first, A[idx].second.second);
			idx++;
		}
		ans[B[i].second.second] = sz[f(B[i].second.first)] - 1;
	}
	for(int i=1; i<=Q; i++) printf("%d\n", ans[i]);
}