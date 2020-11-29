#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pr;

struct Line {
	int s, e, w;
	Line() {s = e = w = 0;}
	Line(int _s, int _e, int _w) {
		s = _s, e = _e, w = _w;
	}
	bool operator < (const Line &x) const{
		return w == x.w ? s < x.s : w < x.w;
	}
};

int N, K, A[100005], ans;
pr ne[100005], pre[100005];
set<Line> S;

int main() {
	scanf("%d %d", &N, &K);
	for(int i=1; i<=N; i++) scanf("%d", A+i);
	A[0] = -1e9, A[N+1] = 2e9;
	A[0]--;
	for(int i=0; i<=N; i++) S.insert(Line(i, i + 1, A[i+1] - A[i]));
	for(int i=1; i<=N; i++) ne[i] = pr(i + 1, A[i+1] - A[i]), pre[i] = pr(i - 1, A[i] - A[i-1]);
	for(int i=0; i<K; i++) {
		Line T = *S.begin(); S.erase(S.begin());
		int s = T.s, e = T.e;
		ans += T.w;
		int u = pre[s].second + ne[e].second - T.w;
		ne[pre[s].first] = pr(ne[e].first, u);
		pre[ne[e].first] = pr(pre[s].first, u);
		S.erase(S.find(Line(pre[s].first, s, pre[s].second)));
		S.erase(S.find(Line(e, ne[e].first, ne[e].second)));
		S.insert(Line(pre[s].first, ne[e].first, u));
	}
	printf("%d\n", ans);
}
