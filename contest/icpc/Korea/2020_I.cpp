#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct BIT2D {
	ll tree[2005][2005]; int base;
	void init(int x) { base = x; for(int i=1; i<=x; i++) for(int j=1; j<=x; j++) tree[i][j] = -1e18; }
	void add(int x, int y, ll z) {
		while(x <= base) {
			int _y = y;
			while(y <= base) tree[x][y] = max(tree[x][y], z), y += y & -y;
			y = _y, x += x & -x;
		}
	}
	ll q(int x, int y) {
		ll res = -1e18;
		while(x) {
			int _y = y;
			while(y) res = max(res, tree[x][y]), y -= y & -y;
			y = _y, x -= x & -x;
		}
		return res;
	}
} bit;

int N, Q, S[2200005], E[2200005], ord[2200005], L[200005], R[200005], qord[200005];
ll A[2005], V[2200005], X[200005], ans[200005];

int main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> N >> Q;
	int sz = 0;
	for(int i=1; i<=N; i++) {
		cin >> A[i];
		ll x = 0;
		for(int j=i; j>0; j--) {
			x += A[j];
			S[++sz] = j;
			E[sz] = i;
			V[sz] = x;
		}
	}
	iota(ord, ord + sz + 1, 0);
	sort(ord + 1, ord + sz + 1, [&](const int &x , const int &y) {
		return V[x] < V[y];
	});
	bit.init(N);
	for(int i=1; i<=Q; i++) {
		qord[i] = i;
		cin >> L[i] >> R[i] >> X[i];
	}
	sort(qord + 1, qord + Q + 1, [&](const int &x, const int &y) {
		return X[x] < X[y];
	});
	for(int i=1, j=1; i<=Q; i++) {
		int k = j;
		while(k <= sz && V[ord[k]] <= X[qord[i]]) bit.add(N + 1 - S[ord[k]], E[ord[k]], V[ord[k]]), k++;
		j = k;
		ans[qord[i]] = bit.q(N + 1 - L[qord[i]], R[qord[i]]);
	}
	for(int i=1; i<=Q; i++) {
		if(ans[i] == -1e18) cout << "NONE" << "\n";
		else cout << ans[i] << "\n";
	}
}