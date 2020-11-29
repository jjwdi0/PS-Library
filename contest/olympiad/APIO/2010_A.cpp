#include <bits/stdc++.h>
#define sz(x) ((int)(x).size())
using namespace std;
typedef long long ll;

struct CHT {
	vector<pair<ll, ll>> v;
	int ind = 0;
	double cross(ll x1, ll y1, ll x2, ll y2) {
		return (double)(y1 - y2) / (x2 - x1);
	}
	double f(pair<ll, ll> X, pair<ll, ll> Y) { return cross(X.first, X.second, Y.first, Y.second); }
	void push(ll m, ll b) {
		while(sz(v) >= 2 && f(v[sz(v)-2], {m, b}) > f(v[sz(v)-1], {m, b})) v.pop_back();
		v.push_back({m, b});
	}
	ll q(double x) {
		while(ind < sz(v) - 1 && f(v[ind], v[ind+1]) <= x) ind++;
		return v[ind].first * x + v[ind].second;
	}
}cht;
int N;
ll A, B, C, sum[1000003], D[1000003];

int main() {
	scanf("%d %lld %lld %lld", &N, &A, &B, &C);
	for(int i=1; i<=N; i++) scanf("%lld", sum+i), sum[i] += sum[i-1];
	for(int i=1; i<=N; i++) {
		cht.push(-2 * A * sum[i-1], A * sum[i-1] * sum[i-1] - B * sum[i-1] + D[i-1]);
		D[i] = cht.q(sum[i]) + A * sum[i] * sum[i] + B * sum[i] + C;
	}
	printf("%lld", D[N]);
}