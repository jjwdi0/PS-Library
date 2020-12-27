#include <bits/stdc++.h>
#define MOD 20070713
using namespace std;
using ll = long long;
using pr = pair<int, int>;

struct BIT {
	ll tree[200005]; int base;
	void init(int x) { base = x; }
	void add(int x, ll y) { while(x <= base) tree[x] = (tree[x] + y) % MOD, x += x & -x; }
	ll q(int x) {
		ll res = 0;
		while(x) res = (res + tree[x]) % MOD, x -= x & -x;
		return res;
	}
} bit;

int N;
pr A[100005];
vector<int> v;

int main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> N;
	bit.init(2 * N + 1);
	for(int i=1; i<=N; i++) {
		cin >> A[i].first >> A[i].second;
		v.push_back(A[i].first);
		v.push_back(A[i].second);
	}
	v.push_back(-1);
	sort(v.begin(), v.end());
	for(int i=1; i<=N; i++) {
		A[i].first = (lower_bound(v.begin(), v.end(), A[i].first) - v.begin()) + 1;
		A[i].second = (lower_bound(v.begin(), v.end(), A[i].second) - v.begin()) + 1;
	}
	bit.add(1, 1);
	sort(A + 1, A + N + 1);
	for(int i=1; i<=N; i++) {
		ll x = bit.q(A[i].first - 1);
		bit.add(A[i].second, x);
	}
	cout << bit.q(N * 2 + 1) % MOD;
}