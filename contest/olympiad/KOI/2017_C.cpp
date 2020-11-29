#include <bits/stdc++.h>
using namespace std;
using pr = pair<int, int>;

int N, M, S, E, T, D[3005][3005];
int sum[3005][3005], imp[3005], mn[3005][3];
deque<pr> dq[3005];
priority_queue<pr, vector<pr>, greater<pr>> pq;

int main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> N >> M >> S >> E >> T;
	for(int i=1; i<=N; i++) for(int j=1; j<=M; j++) {
		cin >> sum[i][j];
		sum[i][j] += sum[i][j-1];
	}
	for(int i=1; i<=N; i++) cin >> imp[i];
	for(int i=1; i<=N; i++) D[0][i] = -T;
	for(int i=1; i<=M; i++) for(int j=1; j<=N; j++) D[i][j] = 1e9;
	for(int j=S; j<=M+S-1; j++) {
		while(!pq.empty()) pq.pop();
		for(int i=1; i<=N; i++) pq.push(pr(D[j-S][i], i));
		int x = pq.top().second; pq.pop();
		int y = pq.top().second; pq.pop();
		int z = pq.top().second; pq.pop();
		for(int i=1; i<=N; i++) {
			int cur = 0;
			if(x != imp[i] && x != i) cur = D[j-S][x];
			else if(y != imp[i] && y != i) cur = D[j-S][y];
			else cur = D[j-S][z];
			while(!dq[i].empty() && dq[i].front().second < (j <= M ? j - E : -100000)) dq[i].pop_front();
			while(!dq[i].empty() && dq[i].back().first >= cur - sum[i][j-S]) dq[i].pop_back();
			dq[i].push_back(pr(cur - sum[i][j-S], j - S));
			if(j <= M) D[j][i] = min(D[j][i], dq[i].front().first + sum[i][j] + T);
		}
	}
	int ans = 1e9;
	for(int i=1; i<=N; i++) {
		ans = min(ans, dq[i].front().first + sum[i][M] + T);
	}
	assert(0 <= ans && ans < 1e9);
	cout << ans << "\n";
}