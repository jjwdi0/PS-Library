#include <bits/stdc++.h>
#define log_N 18
using namespace std;

struct BIT {
	int base, tree[222222];
	void init(int x) { base = x; }
	void add(int x, int y) { while(x <= base) tree[x] += y, x += (x & -x); }
	int q(int x) {
		int res = 0;
		while(x) res += tree[x], x -= (x & -x);
		return res;
	}
} bit;
int N, Q, sparse_table[222222][log_N], discovered[222222], sz[222222], cnt, level[222222];
vector<int> v[222222];

void dfs(int x) {
	sz[x] = 1;
	discovered[x] = ++cnt;
	for(auto it : v[x]) {
		level[it] = level[x] + 1;
		dfs(it);
		sz[x] += sz[it];
	}
}

int LCA(int x, int y) {
	if(level[x] > level[y]) swap(x, y);
	int u = level[y] - level[x];
	for(int i=0; i<log_N; i++) {
		if((u >> i) & 1) y = sparse_table[y][i];
	}
	if(x == y) return x;
	for(int i=log_N-1; i>=0; i--) if(sparse_table[x][i] != sparse_table[y][i]) x = sparse_table[x][i], y = sparse_table[y][i];
	return sparse_table[x][0];
}

int main() {
	scanf("%d %d", &N, &Q);
	bit.init(N);
	for(int i=2, x; i<=N; ++i) {
		scanf("%d", &x);
		sparse_table[i][0] = x;
		v[x].push_back(i);
	}
	for(int i=1; i<18; i++) {
		bool flag = false;
		for(int j=1; j<=N; j++) {
			int u = sparse_table[sparse_table[j][i-1]][i-1];
			if(u) flag = true;
			sparse_table[j][i] = u;
		}
		if(!flag) break;
	}
	dfs(1);
	while(Q--) {
		int x, y, z;
		scanf("%d %d %d", &x, &y, &z);
		int dist = bit.q(discovered[x]) + bit.q(discovered[y]) - 2 * bit.q(discovered[LCA(x, y)]);
		if(!dist) puts("YES"); else puts("NO");
		if(z) {
			int cut_vertex = (dist ? y : x);
			bit.add(discovered[cut_vertex], 1);
			bit.add(discovered[cut_vertex] + sz[cut_vertex], -1);
		}
	}
}