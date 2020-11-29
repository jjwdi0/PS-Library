#include <bits/stdc++.h>
using namespace std;
using pr = pair<int, int>;

int N, M, M1, M2, S, D[25005];
vector<pr> v[25005];
bool inQ[25005];
deque<int> q;

void SLF() {
	if(!q.empty() && D[q.front()] > D[q.back()]) {
		int u = q.back(); q.pop_back();
		q.push_front(u);
	}
}

int main() {
	scanf("%d %d %d %d", &N, &M1, &M2, &S);
	M = M1 + M2;
	for(int i=0, x, y, z; i<M; i++) {
		scanf("%d %d %d", &x, &y, &z);
		v[x].push_back(pr(y, z));
		if(i < M1) v[y].push_back(pr(x, z));
	}
	for(int i=1; i<=N; i++) D[i] = 2e9;
	D[S] = 0, inQ[S] = 1;
	q.push_back(S);
	while(!q.empty()) {
		int u = q.front(); q.pop_front(); inQ[u] = 0;
		for(auto it : v[u]) if(D[it.first] > D[u] + it.second) {
			D[it.first] = D[u] + it.second;
			if(!inQ[it.first]) {
				q.push_back(it.first);
				inQ[it.first] = 1;
				SLF();
			}
		}
	}
	for(int i=1; i<=N; i++) {
		if(D[i] >= 1e9) puts("NO PATH");
		else printf("%d\n", D[i]);
	}
}