#include <bits/stdc++.h>
#define MOD1 1000000007
#define MOD2 1000000009
using namespace std;
using ll = long long;
using pr = pair<ll, ll>;
using tr = pair<int, pr>;
using qr = pair<int, tr>;

ll ipow(ll x, ll y, ll mod) {
	if(y == 0LL) return 1LL;
	ll u = ipow(x, y >> 1, mod);
	return y & 1LL ? u * u % mod * x % mod : u * u % mod;
}

int N, R[600006];
char A[300006], B[600006];
ll p1[300005] = { 1LL }, p2[300005] = { 1LL }, hs[300005][2];
map<pr, int> pals;
priority_queue<qr> pq;

ll substr(int s, int e, int idx) {
	ll mod = (idx ? MOD2 : MOD1);
	ll v = (hs[e][idx] - hs[s-1][idx] + mod) % mod;
	return v * ipow(idx ? p2[s] : p1[s], mod - 2, mod) % mod;
}

int main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> A;
	N = strlen(A);
	for(int i=0; i<N; i++) B[i+i+1] = A[i];
	for(int i=0; i<=N+N; i+=2) B[i] = '#';
	for(int i=1; i<=N; i++) p1[i] = p1[i-1] * 31 % MOD1;
	for(int i=1; i<=N; i++) p2[i] = p2[i-1] * 31 % MOD2;
	for(int i=1; i<=N; i++) {
		hs[i][0] = (hs[i-1][0] + p1[i] * (A[i-1] - 'a' + 1)) % MOD1;
		hs[i][1] = (hs[i-1][1] + p2[i] * (A[i-1] - 'a' + 1)) % MOD2;
	}
	int c = 0, r = 0;
	for(int i=0; i<=2*N; i++) {
		R[i] = min(max(0, r - i), R[c+c-i]);
		while(i >= R[i] && B[i-R[i]] == B[i+R[i]]) R[i]++;
		if(i + --R[i] > r) c = i, r = i + R[i];
	}
	for(int i=1; i<N+N; i++) {
		int s = i - R[i], e = i + R[i];
		if(s == e) continue;
		ll v1 = substr(s / 2 + 1, e / 2, 0);
		ll v2 = substr(s / 2 + 1, e / 2, 1);
		auto v = pr(v1, v2);
		if(pals.find(v) == pals.end()) pq.push(qr(e / 2 - s / 2, tr(s / 2, v)));
		pals[v]++;
	}
	ll ans = 0LL;
	ll t1 = ipow(31, MOD1 - 2, MOD1), t2 = ipow(31, MOD2 - 2, MOD2);
	while(!pq.empty()) {
		int s = pq.top().second.first, e = pq.top().first + pq.top().second.first - 1;
		auto v = pq.top().second.second; pq.pop();
		int cur = pals[v]; pals.erase(v);
		ans = max(ans, 1LL * (e - s + 1) * cur);
		if(s + 1 >= e) continue;
		ll v1 = (v.first - (A[s] - 'a' + 1) - p1[e-s] * (A[e] - 'a' + 1) % MOD1 + MOD1 * 2) % MOD1;
		ll v2 = (v.second - (A[s] - 'a' + 1) - p2[e-s] * (A[e] - 'a' + 1) % MOD2 + MOD2 * 2) % MOD2;
		v1 = (v1 * t1) % MOD1;
		v2 = (v2 * t2) % MOD2;
		if(pals.find(pr(v1, v2)) == pals.end()) pq.push(qr(e - s - 1, tr(s + 1, pr(v1, v2))));
		pals[pr(v1, v2)] += cur;
	}
	cout << ans << "\n";
}