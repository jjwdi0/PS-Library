#include <bits/stdc++.h>
using namespace std;

vector<pair<int, pair<int, int>>> v;
int N, A[1002][2], par[1002];

int find(int x){return par[x] = x == par[x] ? x : find(par[x]);}
int sz(int x){return x*x;}

int main() {
	scanf("%d", &N);
	for(int i=1; i<=N; i++) {
		scanf("%d %d", &A[i][0], &A[i][1]);
		par[i] = i;
	}
	for(int i=1; i<=N; i++) for(int j=i+1; j<=N; j++) {
		v.push_back({sz(A[i][0] - A[j][0]) + sz(A[i][1] - A[j][1]), {i, j}});
	}
	sort(v.begin(), v.end());
	for(int i=0, cnt=0; i<v.size(); i++) {
		int p = v[i].second.first, q = v[i].second.second;
		if(find(p) == find(q)) continue;
		cnt++;
		par[find(p)] = par[find(q)];
		if(cnt == N - 1) return printf("%d", v[i].first),0;
	}
	puts("0");
}