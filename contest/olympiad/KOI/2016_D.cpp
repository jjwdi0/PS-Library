#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pr = pair<ll, ll>;

pr t[33333];
int N, T;
vector<pr> v;
struct star { ll xpos, ypos, xval, yval; } STAR[33333];

ll cross(pr x, pr y){ return x.first * y.second - x.second * y.first; }
ll sz(pr x){ return x.first * x.first + x.second * x.second; }
bool cmp(const pr &x, const pr &y){ return cross(x, y) ? ( cross(x, y) < 0 ) : ( sz(x) < sz(y) ); }
ll dist(pr x, pr y){ return sz({x.first - y.first, x.second - y.second}); }

int ccw(int x1, int y1, int x2, int y2, int x3, int y3) {
	ll res = cross({x1, y1}, {x2, y2}) + cross({x2, y2}, {x3, y3}) + cross({x3, y3}, {x1, y1});
	if(res > 0LL) return 1;
	if(res) return -1;
	return 0;
}

pr f(pr x, pr y){ return {x.first - y.first, x.second - y.second}; }

ll get_farthest_dist(ll x) {
	ll ans = 0LL;
	for(int i = 0; i < N; i++) t[i] = {STAR[i].xpos + STAR[i].xval * x, STAR[i].ypos + STAR[i].yval * x};
	sort(t, t + N);
	for(int i = 1; i < N; i++) t[i] = f(t[i], t[0]);
	t[0] = {0LL, 0LL};
	sort(t + 1, t + N, cmp);
	v.clear();
	for(int i = 0; i < N; i++) {
		while(v.size() >= 2 && (cross( f(v[v.size() - 2], v.back()), f(t[i], v.back()) ) <= 0) )v.pop_back();
		v.push_back(t[i]);
	}
	int j = 1;
	for(int i = 0; i < (int)v.size(); i++) {
		int k = (i + 1) % ((int)v.size());
		while( ccw(0, 0, f(v[k], v[i]).first, f(v[k], v[i]).second, f(v[(j + 1) % ((int)v.size())], v[j]).first, f(v[(j + 1) % ((int)v.size())], v[j]).second) < 0 ) j = (j + 1) % ((int)v.size());
		ll D = dist(v[i], v[j]);
		ans = max(ans, D);
	}
	return ans;
}

int main() {
	scanf("%d %d", &N, &T);
	for(int i = 0; i < N; i++) scanf("%lld %lld %lld %lld", &STAR[i].xpos, &STAR[i].ypos, &STAR[i].xval, &STAR[i].yval);
	
	int lo = 0, hi = T;
	
	while(lo + 1 < hi) {
		int mid = lo + hi >> 1;
		if(get_farthest_dist(mid) > get_farthest_dist(mid + 1)) lo = mid + 1;
		else hi = mid;
	}
	
	int ans;
	
	if(get_farthest_dist(lo) <= get_farthest_dist(hi)) ans = lo;
	else ans = hi;
	printf("%d %lld\n", ans, get_farthest_dist(ans));
}