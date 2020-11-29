#include <bits/stdc++.h>
#define sz(x) ((int)(x).size())
using namespace std;
typedef long long ll;
typedef pair<int, ll> pr;

struct convex_hull_trick {
	deque<pr> v;
	deque<int> idx;
	int ind;
	double cross(pr x, pr y) {return (double)(y.second - x.second) / (x.first - y.first);}
	bool bad(pr x, pr y, pr z) {
		if(y.first == z.first) return y.second <= z.second;
		return cross(x, y) >= cross(y, z);
	}
	void push(int x, ll y, int i) {
		while(sz(v) >= 2 && bad(v[sz(v)-2], v[sz(v)-1], pr(x, y))) v.pop_back(), idx.pop_back();
		if(sz(v) == 1 && v[sz(v)-1].first == x && v[sz(v)-1].second <= y) v.pop_back(), idx.pop_back();
		v.push_back(pr(x, y)), idx.push_back(i);
	}
	pr q(int x) {
		while(sz(v) >= 2 && cross(v[ind], v[ind+1]) <= x) v.pop_front(), idx.pop_front();
		return pr(idx.front(), 1LL * x * v.front().first + v.front().second);
	}
	void clear() {while(sz(v)) v.pop_back(), idx.pop_back(); ind = 0;}
}cht;

int N, K, A[100005];
ll D[100001][2];
int trace[100003][203];

int main() {
	scanf("%d %d", &N, &K);
	for(int i=1; i<=N; i++) scanf("%d", A+i), A[i] += A[i-1];
	for(int j=1; j<=K; j++) {
		cht.clear();
		cht.push(0, 0, 0);
		for(int i=1; i<=N; i++) {
			D[i][j&1] = cht.q(A[i]).second;
			trace[i][j] = cht.q(A[i]).first;
			cht.push(A[i], D[i][(j+1)&1] - 1LL * A[i] * A[i], i);
		}
	}
	printf("%lld\n", D[N][K&1]);
	for(int i=N, j=K; j; j--) {
		printf("%d ", trace[i][j]);
		i = trace[i][j];
	}
}