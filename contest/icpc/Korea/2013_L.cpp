#include <bits/stdc++.h>
using namespace std;

int T, N, A[100005], indeg[100005];

int main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> T;
	while(T--) {
		cin >> N;
		for(int i=1; i<=N; i++) indeg[i] = 0;
		for(int i=1; i<=N; i++) cin >> A[i], indeg[A[i]]++;
		queue<int> q;
		for(int i=1; i<=N; i++) if(!indeg[i]) q.push(i);
		int ans = 0;
		while(!q.empty()) {
			int u = q.front(); q.pop();
			ans++;
			if(!--indeg[A[u]]) q.push(A[u]);
		}
		cout << ans << "\n";
	}
}