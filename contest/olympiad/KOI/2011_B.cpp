#include <bits/stdc++.h>
#define INF 987654321
using namespace std;

map<int, int> a, dp[2];
int par[20005], test = 5, n, m;

int find(int x) {
	if(x == par[x])return x;
	return par[x] = find(par[x]);
}

void uni(int x, int y) {
	x = find(x); y = find(y);
	par[x] = y;
}

int f(int x) { return x>n?-1:1; }

int main() {
	while(test--) {
		scanf("%d %d", &n, &m);
		for(int i=1; i<=2*n; i++) par[i] = i;
		a.clear();
		for(int i=0; i<=1; i++) dp[i].clear();
		bool fin = false;
		for(int i=0; i<m; i++) {
			int t1, t2, t3;
			scanf("%d %d %d", &t1, &t2, &t3);
			if(t1 > 0) {
				uni(t2, t3); uni(t2 + n, t3 + n);
			} else {
				uni(t2, t3 + n); uni(t2 + n, t3);
			}
		}
		for(int i=1; i<=n; i++) {
			if(find(i) == find(i + n)) {
				puts("-1");
				fin = true;
				break;
			}
		}
		if(fin) continue;
		for(int i=1; i<=n; i++) {
			if(a.find(find(i)) == a.end()) {
				if(a.find(find(i + n)) == a.end()) {
					a[find(i)] = f(i);
				}
				else a[find(i + n)] += f(i + n);
			}
			else a[find(i)] += f(i);
		}
		dp[0][0] = 1;
		auto j = a.begin();
		for(int i=0; i<a.size(); i++) {
			dp[(i+1)%2].clear();
			for(auto it : dp[i%2]) {
				dp[(i+1)%2][it.first+j->second] = 1;
				dp[(i+1)%2][it.first-j->second] = 1;
			}
			j++;
		}
		int ans = INF;
		for(auto it : dp[a.size()%2]) {
			if(ans > abs(it.first)) ans = abs(it.first);
		}
		printf("%d\n", ans);
	}
}