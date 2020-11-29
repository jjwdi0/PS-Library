#include <bits/stdc++.h>
#define INF 987654321
using namespace std;

int dx[4][2] = {1, 0, -1, 0, 0, 1, 0, -1}, N, M, A[111][111], B[111][111], cnt, vc;
bool visited[111][111];
vector<vector<bool>> adj;
vector<vector<int>> v;
vector<int> chk;
queue<int> q;

int ans = INF;

bool get(int x, int y){return !(x<0 || y<0 || x>=N || y>=M || visited[x][y]);}
void dfs1(int x, int y) {
	visited[x][y] = 1;
	B[x][y] = cnt;
	for(int i=0; i<4; i++) {
		int xx = x + dx[i][0], yy = y + dx[i][1];
		if(get(xx, yy) && A[xx][yy] == A[x][y]) dfs1(xx, yy);
	}
}
void dfs2(int x, int y) {
	visited[x][y] = 1;
	for(int i=0; i<4; i++) {
		int xx = x + dx[i][0], yy = y + dx[i][1];
		if(get(xx, yy)) {
			if(B[xx][yy] == B[x][y]) dfs2(xx, yy);
			else adj[B[x][y]][B[xx][yy]] = adj[B[xx][yy]][B[x][y]] = 1;
		}
	}
}
void bfs(int x) {
	int res = 0;
	while(!q.empty()) q.pop();
	q.push(x);
	chk[x] = 0;
	while(!q.empty()) {
		int u = q.front(); q.pop();
		res = max(res, chk[u]);
		if(chk[u] >= ans) return;
		for(auto it : v[u]) {
			if(chk[it] > chk[u] + 1) {
				chk[it] = chk[u] + 1;
				q.push(it);
			}
		}
	}
	ans = min(ans, res);
}
int main() {
	scanf("%d %d", &N, &M);
	for(int i=0; i<N; i++) for(int j=0; j<M; j++) scanf("%d", &A[i][j]);
	for(int i=0; i<N; i++) for(int j=0; j<M; j++) if(!visited[i][j]) ++cnt, dfs1(i, j);
	for(int i=0; i<N; i++) for(int j=0; j<M; j++) visited[i][j] = 0;
	adj.resize(cnt + 3);
	for(int i=1; i<=cnt; i++) adj[i].resize(cnt + 3);
	for(int i=0; i<N; i++) for(int j=0; j<M; j++) if(!visited[i][j]) dfs2(i, j);
	v.resize(cnt + 3);
	chk.resize(cnt + 3);
	for(int i=1; i<=cnt; i++) for(int j=1; j<=cnt; j++) if(adj[i][j]) v[i].push_back(j);
	for(int i=1; i<=cnt; i++) chk[i] = INF;
	bfs(cnt);
	for(int i=1; i<=min(5800, cnt); i++) {
		for(int j=1; j<=cnt; j++) chk[j] = INF;
		bfs(i);
	}
	printf("%d", ans);
}