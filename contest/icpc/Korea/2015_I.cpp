#include <bits/stdc++.h>
using namespace std;

stack<int> s;
int T, N, A[1000003];
long long S[1000003], D[1000003];

int main() {
	scanf("%d", &T);
	while(T--) {
		while(!s.empty()) s.pop();
		long long ans = 0;
		scanf("%d", &N);
		for(int i=1; i<=N; i++) scanf("%d", A+i), S[i] = S[i-1] + A[i];
		A[0] = 2e9;
		s.push(0);
		for(int i=1; i<=N; i++) {
			while(A[s.top()] < A[i]) s.pop();
			D[i] = D[s.top()] + (long long)(i - s.top() - 1) * A[i] - (S[i-1] - S[s.top()]);
			s.push(i);
			ans = max(ans, D[i]);
		}
		printf("%lld\n", ans);
	}
}