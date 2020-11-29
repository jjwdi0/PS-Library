#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int N, A[1000005];
ll ans;
vector<int> v1, v2;

void do_dp(int s, int e, int l, int r) {
	if(s > e) return;
	int idx = l, mid = (s + e) >> 1;
	ll mx = 0LL;
	for(int i=l; i<=r; i++) {
		if(v2[mid] <= v1[i]) break;
		if(mx < 1LL * (v2[mid] - v1[i]) * (A[v2[mid]] + A[v1[i]])) {
			mx = 1LL * (v2[mid] - v1[i]) * (A[v2[mid]] + A[v1[i]]);
			idx = i;
		}
	}
	ans = max(ans, mx);
	do_dp(s, mid - 1, l, idx);
	do_dp(mid + 1, e, idx, r);
}

int main() {
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> N;
	for(int i=1; i<=N; i++) cin >> A[i];
	for(int i=1; i<=N; i++) if(v1.empty() || A[v1.back()] < A[i]) v1.push_back(i);
	for(int i=N; i>0; i--) if(v2.empty() || A[v2.back()] < A[i]) v2.push_back(i);
	reverse(v2.begin(), v2.end());
	do_dp(0, (int)v2.size() - 1, 0, (int)v1.size() - 1);
	cout << ans << "\n";
}