#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N, M;
ll D[20005], A[20005], K;

int main() {
	scanf("%d %d %lld", &N, &M, &K);
	for(int i=1; i<=N; i++) {
		scanf("%lld", A+i);
		D[i] = 1e18;
		ll s = A[i], t = A[i];
		for(int j=i-1; j>=max(0, i-M); j--) {
			D[i] = min(D[i], D[j] + K + (ll)(i - j) * (s - t));
			s = max(s, A[j]), t = min(t, A[j]);
		}
	}
	printf("%lld\n", D[N]);
}