#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int N;
ll A[1000005], K;

int main() {
	ios::sync_with_stdio(0), cin.tie(0);
	ll ans = 1e18;
	cin >> N >> K;
	for(int i=1; i<=N; i++) cin >> A[i];
	for(int j=0; j<2; j++) {
		ll mn = 1e18, mx = -1e18;
		for(int i=1; i<=N; i++) {
			mn = min(mn, A[i] - i * K);
			mx = max(mx, A[i] - i * K);
		}
		ans = min(ans, mx - mn);
		reverse(A + 1, A + N + 1);
	}
	printf("%lld.%lld\n", ans / 2, (ans % 2) * 5);
}