#include <bits/stdc++.h>
using namespace std;
using pr = pair<int, int>;

int T, N, K;
pr A[10005];

bool f(int x) {
	int cnt = 1, mx = -1e9, mn = 1e9;
	for(int i=1; i<=N; i++) {
		mx = max(mx, A[i].second), mn = min(mn, A[i].second);
		if(mx - mn > x + x) cnt++, mx = mn = A[i].second;
		if(cnt > K) return 0;
	}
	return 1;
}

int main() {
	scanf("%d", &T);
	while(T--) {
		scanf("%d %d", &N, &K);
		for(int i=1; i<=N; i++) scanf("%d %d", &A[i].first, &A[i].second), A[i].second <<= 1;
		sort(A + 1, A + N + 1);
		int s = 0, e = 1e9;
		while(s <= e) {
			int mid = s + e >> 1;
			f(mid) ? e = mid - 1 : s = mid + 1;
		}
		printf("%d.%d\n", s >> 1, (s & 1 ? 5 : 0));
	}
}
