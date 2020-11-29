#include <bits/stdc++.h>
using namespace std;
using pr = pair<int, int>;
using ll = long long;

struct BIT {
	int tree[100005], base;
	void init(int x) { base = x; }
	void add(int x, int y) { while(x <= base) tree[x] += y, x += x & -x; }
	int q(int x) {
		int res = 0;
		while(x) res += tree[x], x -= x & -x;
		return res;
	}
} bit;

int N;
ll ans;
vector<int> v[100005];

int main() {
	scanf("%d", &N);
	bit.init(N);
	for(int i=1, x; i<=N; i++) {
		scanf("%d", &x);
		v[x].push_back(i);
		bit.add(i, 1);
	}
	for(int i=0; i<N; i++) {
		printf("%lld\n", ans);
		for(auto it : v[i]) bit.add(it, -1), ans += bit.q(it);
	}
}