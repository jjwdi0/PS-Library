#include <bits/stdc++.h>
using namespace std;
using pr = pair<int, int>;

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
pr A[100005];

int main() {
	scanf("%d", &N);
	for(int i=1, x; i<=N; i++) scanf("%d", &x), A[i] = pr(x, i);
	bit.init(N);
	sort(A + 1, A + N + 1);
	int ans = 1;
	for(int i=1; i<=N; i++) {
		bit.add(A[i].second, 1);
		ans = max(ans, i - bit.q(i));
	}
	printf("%d\n", ans);
}