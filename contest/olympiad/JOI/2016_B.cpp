#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N;
char A[100005];
ll J[100005], O[100005], I[100005];
ll FO[100005], EO[100005];

int main() {
	scanf("%d %s", &N, A+1);
	for(int i=1; i<=N; i++) {
		if(A[i] == 'J') J[i]++;
		if(A[i] == 'O') O[i]++;
		if(A[i] == 'I') I[i]++;
	}
	for(int i=1; i<=N; i++) {
		J[i] += J[i-1];
		O[i] += O[i-1];
		I[i] += I[i-1];
	}
	for(int i=1; i<=N; i++) {
		if(A[i] != 'O') continue;
		FO[i] = J[i-1];
		EO[i] = I[N] - I[i];
	}
	for(int i=1; i<=N; i++) FO[i] += FO[i-1], EO[i] += EO[i-1];
	ll ans = EO[N];
	for(int i=1; i<=N; i++) ans = max({ans, EO[N] - EO[i], FO[i], J[i] * (I[N] - I[i])});
	for(int i=1; i<=N; i++) if(A[i] == 'J') ans += EO[N] - EO[i];
	printf("%lld\n", ans);
}