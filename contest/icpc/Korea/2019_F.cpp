#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pr = pair<ll, ll>;

ll ccw(pr x, pr y, pr z) {
	ll r1 = x.first * y.second + y.first * z.second + z.first * x.second;
	ll r2 = x.second * y.first + y.second * z.first + z.second * x.first;
	return r1 - r2;
}

int N, idx[1005];
pr A[1005];

struct Line {
	int i, j;
	ll dx, dy;
	Line(int i, int j): i(i), j(j) {
		dx = A[i].first - A[j].first, dy = A[i].second - A[j].second;
		if(dx < 0) dx = -dx, dy = -dy;
		if(dx == 0) dy = abs(dy);
	}
};

vector<Line> v;

int main() {
	scanf("%d", &N);
	for(int i=1; i<=N; i++) {
		scanf("%lld %lld", &A[i].first, &A[i].second);
		idx[i] = i;
	}
	sort(A + 1, A + N + 1);
	for(int i=1; i<=N; i++) for(int j=i+1; j<=N; j++) v.push_back(Line(i, j));
	sort(v.begin(), v.end(), [&](const Line &X, const Line &Y) {
		return X.dy * Y.dx < X.dx * Y.dy;
	});
	ll mn = 9e18, ans = 0;
	int cnt = 0;
	for(auto it : v) {
		int p = it.i, q = it.j;
		swap(A[idx[p]], A[idx[q]]);
		swap(idx[p], idx[q]);
		p = idx[p], q = idx[q];
		if(p > q) swap(p, q);
		ans += 1LL * (p - 1) * (N - q);
		for(int i=max(1, p-2); i<p; i++) for(int j=min(N, q+2); j>q; j--) {
			ll area = abs(ccw(A[p], A[q], A[i])) + abs(ccw(A[p], A[q], A[j]));
			if(area < mn) mn = area, cnt = 0;
			if(area == mn) cnt += 1 + ((ccw(A[i], A[j], A[p]) > 0) == (ccw(A[i], A[j], A[q]) > 0));
		}
	}
	printf("%lld\n", ans + cnt);
}