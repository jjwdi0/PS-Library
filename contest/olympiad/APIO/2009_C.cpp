#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define rem(x) (x).resize(unique(all(x))-(x).begin())
using namespace std;

int V, E, S, M, cost[500005], num[1000005], visited[500005], c, ans;
vector<pair<int, bool>> v[500005];
vector<int> SCC[500005], adj[500005];
int SCC_belong[500005], D[500005], indeg[500005];
bool chk1[500005], chk2[500005], vi[500005];
queue<int> q;

void dfs(int x) {
	visited[x] = ++c;
	for(auto it : v[x]) {
		if(!visited[it.first] && it.second) dfs(it.first);
	}
	visited[x] = ++c;
}

void dfs2(int x, int y) {
	SCC[y].pb(x);
	SCC_belong[x] = y;
	vi[x] = 1;
	for(auto it : v[x]) {
		if(!vi[it.first] && !it.second) dfs2(it.first, y);
	}
}

void dfs3(int x) {
	vi[x] = 1;
	for(auto it : adj[x]) {
		indeg[it]++;
		if(!vi[it]) dfs3(it);
	}
}

int main() {
	scanf("%d %d", &V, &E);
	for(int i=0, x, y; i<E; i++) {
		scanf("%d %d", &x, &y);
		v[x].pb(mp(y, 1));
		v[y].pb(mp(x, 0));
	}
	for(int i=1; i<=V; i++) if(!visited[i]) dfs(i);
	c = 0;
	for(int i=1; i<=V; i++) num[visited[i]] = i;
	for(int i=V*2; i; i--) if(num[i] && !vi[num[i]]) dfs2(num[i], ++c);
	for(int i=1; i<=V; i++) {
		for(auto it : v[i]) {
			if(it.second && SCC_belong[it.first] != SCC_belong[i]) {
				adj[SCC_belong[i]].pb(SCC_belong[it.first]);
			}
		}
	}
	for(int i=1, x; i<=V; i++) {
		scanf("%d", &x);
		cost[SCC_belong[i]] += x;
	}
	scanf("%d %d", &S, &M);
	for(int i=0, x; i<M; i++) {
		scanf("%d", &x);
		chk1[SCC_belong[x]] = 1;
	}
	for(int i=1; i<=c; i++) {
		sort(all(adj[i]));
		rem(adj[i]);
	}
	for(int i=1; i<=V; i++) vi[i] = 0;
	dfs3(SCC_belong[S]);
	q.push(SCC_belong[S]);
	D[SCC_belong[S]] = cost[SCC_belong[S]];
	while(!q.empty()) {
		int u = q.front(); q.pop();
		if(chk1[u]) ans = max(ans, D[u]);
		for(auto it : adj[u]) {
			indeg[it]--;
			if(!indeg[it]) q.push(it);
			D[it] = max(D[it], D[u] + cost[it]);
		}
	}
	printf("%d\n", ans);
}