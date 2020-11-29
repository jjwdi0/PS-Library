#include <stdio.h>
typedef long long ll;

int N, M, A[100005], cnt[100005], B[100003][3];

void f(int x, int y) {
	if(x > y) x ^= y ^= x ^= y;
	cnt[x]++, cnt[y]--;
}
ll min(ll X, ll Y){return X>Y?Y:X;}
int main() {
	scanf("%d %d", &N, &M);
	for(int i=0; i<M; i++) scanf("%d", A+i);
	for(int i=1; i<N; i++) {
		scanf("%d %d %d", &B[i][0], &B[i][1], &B[i][2]);
	}
	for(int i=1; i<M; i++) f(A[i-1], A[i]);
	for(int i=1; i<N; i++) cnt[i] += cnt[i-1];
	ll ans = 0LL;
	for(int i=1; i<N; i++) {
		ans += min(1LL * cnt[i] * B[i][0], 1LL * cnt[i] * B[i][1] + 1LL * B[i][2]);
	}
	printf("%lld", ans);
}