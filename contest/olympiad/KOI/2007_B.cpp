#include <stdio.h>
#include <algorithm>
#define MOD 20070713
using namespace std;
typedef long long ll;

int N, B[100005];
pair<int, int> A[100005];
ll D[100005], S[100005];

bool cmp(const pair<int, int> &x, const pair<int, int> &y) {
	return x.second == y.second ? x.first < y.first : x.second < y.second;
}

int main() {
	scanf("%d", &N);
	for(int i=1; i<=N; i++) scanf("%d %d", &A[i].first, &A[i].second);
	sort(A + 1, A + N + 1, cmp);
	for(int i=1; i<=N; i++) B[i] = A[i].second;
	D[0] = S[0] = 1;
	for(int i=1; i<=N; i++) {
		S[i] += S[i-1];
		D[i] = S[lower_bound(B, B + N + 1, A[i].first) - B - 1];
		S[i] += D[i];
		S[i] %= MOD;
	}
	printf("%lld", S[N]);
}