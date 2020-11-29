#include <bits/stdc++.h>
#define y1 __y1__
using namespace std;
using ll = long long;

int T, N, X[100005], Y[100005], A[100005];
int mxx, mxy, mnx, mny;

bool possible(int sz, ll d) {
	ll _mxx = -2e9, _mxy = -2e9, _mnx = 2e9, _mny = 2e9;
	for(int i=1; i<=sz; i++) {
		_mxx = max(_mxx, (ll)X[A[i]]), _mnx = min(_mnx, (ll)X[A[i]]);
		_mxy = max(_mxy, (ll)Y[A[i]]), _mny = min(_mny, (ll)Y[A[i]]);
	}
	bool ret = 1;
	for(int i=1; i<=sz; i++) {
		int x = X[A[i]], y = Y[A[i]];
		if((y > _mny + d || x > _mnx + d) && (y < _mxy - d || x < _mxx - d)) {
			ret = 0;
			break;
		}
	}
	if(ret) return ret;
	for(int i=1; i<=sz; i++) {
		int x = X[A[i]], y = Y[A[i]];
		if((y < _mxy - d || x > _mnx + d) && (y > _mny + d || x < _mxx - d)) return 0;
	}
	return 1;
}

bool f(ll x) {
	ll x1[4] = { mnx, mnx, mxx - x, mxx - x };
	ll y1[4] = { mxy - x, mny, mxy - x, mny };
	ll x2[4] = { mnx + x, mnx + x, mxx, mxx };
	ll y2[4] = { mxy, mny + x, mxy, mny + x };
	for(int i=0; i<4; i++) {
		int sz = 0;
		for(int j=1; j<=N; j++) {
			if(x1[i] > X[j] || X[j] > x2[i] || y1[i] > Y[j] || Y[j] > y2[i]) A[++sz] = j;
		}
		if(!sz || possible(sz, x)) return 1;
	}
	return 0;
}

int main() {
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &N);
		mxx = -2e9, mxy = -2e9, mnx = 2e9, mny = 2e9;
		for(int i=1; i<=N; i++) {
			scanf("%d %d", X+i, Y+i);
			mxx = max(mxx, X[i]), mnx = min(mnx, X[i]);
			mxy = max(mxy, Y[i]), mny = min(mny, Y[i]);
		}
		ll s = 0, e = 2e9;
		while(s <= e) {
			ll mid = s + e >> 1;
			f(mid) ? e = mid - 1LL : s = mid + 1LL;
		}
		printf("%lld\n", s);
	}
}