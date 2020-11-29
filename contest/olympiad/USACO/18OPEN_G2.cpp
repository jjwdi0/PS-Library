#include <bits/stdc++.h>
using namespace std;

int N, M, indeg[100005];
vector<int> obs[50005], v[100005], ans;
priority_queue<int, vector<int>, greater<int>> pq;

bool f(int x) {
	memset(indeg, 0, sizeof(indeg));
	for(int i=1; i<=N; i++) v[i].clear();
	while(!pq.empty()) pq.pop();
	ans.clear();
	for(int i=1; i<=x; i++) {
		for(int j=1; j<obs[i].size(); j++) v[obs[i][j-1]].push_back(obs[i][j]), indeg[obs[i][j]]++;
	}
	for(int i=1; i<=N; i++) if(!indeg[i]) pq.push(i);
	while(!pq.empty()) {
		int u = pq.top(); pq.pop();
		ans.push_back(u);
		for(auto it : v[u]) if(!--indeg[it]) pq.push(it);
	}
	return ans.size() == N;
}

int main() {
	scanf("%d %d", &N, &M);
	for(int i=1, n; i<=M; i++) {
		scanf("%d", &n);
		for(int j=0, x; j<n; j++) {
			scanf("%d", &x);
			obs[i].push_back(x);
		}
	}
	int s = 1, e = M;
	while(s <= e) {
		int mid = s + e >> 1;
		f(mid) ? s = mid + 1 : e = mid - 1;
	}
	f(e);
	for(auto it : ans) printf("%d ", it);
}