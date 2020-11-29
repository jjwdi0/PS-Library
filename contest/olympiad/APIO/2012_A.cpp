#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int N, M, num[100003];
vector<int> v[100003];
ll sum[100003], C[100003], L[100003], ans;
priority_queue<ll> pq[100003];

void dfs(int x) {
	num[x] = x;
	sum[x] = C[x];
	pq[x].push(C[x]);
	for(auto it : v[x]) {
		dfs(it);
		if(pq[num[x]].size() < pq[num[it]].size()) swap(num[x], num[it]);
		while(!pq[num[it]].empty()) pq[num[x]].push(pq[num[it]].top()), pq[num[it]].pop();
		sum[x] += sum[it];
	}
	while(sum[x] > M) {
		sum[x] -= pq[num[x]].top();
		pq[num[x]].pop();
	}
	ans = max(ans, (ll)pq[num[x]].size() * L[x]);
}

int main() {
	scanf("%d %d", &N, &M);
	for(int i=1, x; i<=N; i++) {
		scanf("%d %lld %lld", &x, C+i, L+i);
		v[x].push_back(i);
	}
	dfs(1);
	printf("%lld", ans);
}