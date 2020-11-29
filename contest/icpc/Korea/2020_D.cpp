#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int N, X[1005], Y[1005], C[1005];
int W, D;
vector<int> v[1005];
ll dp[12][1005][2005];
vector<int> vtx[1005][2005];
int dist[1005][1005], ni[1005][1005];
vector<int> adj[1005];

int main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> N;
	for(int i=1; i<=N; i++) cin >> X[i] >> Y[i] >> C[i];
	for(int i=1; i<=N; i++) for(int j=i+1; j<=N; j++) dist[i][j] = dist[j][i] = abs(X[i] - X[j]) + abs(Y[i] - Y[j]);
	cin >> W >> D;
	for(int i=1; i<=N; i++) {
		for(int j=1; j<=N; j++) {
			int dst = dist[i][j];
			if(W >= dst) v[i].push_back(dst), v[i].push_back(W - dst);
			if(W >= dst && i != j) adj[i].push_back(j);
		}
		sort(v[i].begin(), v[i].end());
		v[i].resize(unique(v[i].begin(), v[i].end()) - v[i].begin());
		for(int j : adj[i]) {
			int dst = dist[i][j];
			int idx = (lower_bound(v[i].begin(), v[i].end(), dst) - v[i].begin());
			vtx[i][idx].push_back(j);
		}
	}
	for(int i=1; i<=N; i++) for(int j : adj[i]) {
		int idx = (lower_bound(v[j].begin(), v[j].end(), W - dist[i][j]) - v[j].begin());
		ni[i][j] = idx;
	}
	for(int k=0; k<=D+1; k++) for(int i=1; i<=N; i++) for(int j=0; j<=N*2+1; j++) dp[k][i][j] = 1e18;
	dp[1][1][0] = 0;
	for(int ii=1; ii<=D; ii++) {
		for(int i=1; i<=N; i++) for(int j=0; j<v[i].size(); j++) {
			int u = i, w = j, d = ii;
			dp[d][u][w+1] = min(dp[d][u][w+1], dp[d][u][w] + 1LL * C[u] * (v[u][w+1] - v[u][w]));
			if(w == (int)v[u].size() - 1) {
				for(int i : adj[u]) {
					int idx = ni[u][i];
					dp[d+1][i][idx] = min(dp[d+1][i][idx], dp[d][u][w]);
				}
			}
			for(auto it : vtx[u][w]) dp[d+1][it][0] = min(dp[d+1][it][0], dp[d][u][w]);
		}
	}
	ll ans = 1e18;
	for(int j=1; j<=D+1; j++) for(int i=0; i<(int)v[2].size(); i++) ans = min(ans, dp[j][2][i]);
	cout << (ans == 1e18 ? -1LL : ans) << "\n";
}