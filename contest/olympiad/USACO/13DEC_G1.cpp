#include <bits/stdc++.h>
using namespace std;
using pr = pair<int, int>;

int N, M, K, Q, D[2][305][20005], A[305];
vector<pr> v[20005][2];
priority_queue<pr, vector<pr>, greater<pr>> pq;

void dijkstra(int x, int rev) {
	for(int i=1; i<=N; i++) D[rev][x][i] = 1e9;
	int st = A[x];
	D[rev][x][st] = 0;
	pq.push(pr(0, st));
	while(!pq.empty()) {
		int u = pq.top().second, c = pq.top().first; pq.pop();
		for(auto it : v[u][rev]) {
			if(D[rev][x][it.first] > c + it.second) {
				D[rev][x][it.first] = c + it.second;
				pq.push(pr(c + it.second, it.first));
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> N >> M >> K >> Q;
	for(int i=0, x, y, z; i<M; i++) {
		cin >> x >> y >> z;
		v[x][0].push_back(pr(y, z));
		v[y][1].push_back(pr(x, z));
	}
	for(int i=1; i<=K; i++) cin >> A[i];
	for(int i=1; i<=K; i++) {
		dijkstra(i, 0);
		dijkstra(i, 1);
	}
	long long ans = 0;
	int cnt = 0;
	for(int x, y; Q--;) {
		cin >> x >> y;
		long long cur = 1e9;
		for(int i=1; i<=K; i++) cur = min(cur, 0LL + D[1][i][x] + D[0][i][y]);
		if(cur < 1e9) {
			ans += cur;
			cnt++;
		}
	}
	cout << cnt << "\n" << ans << "\n";
}