#include <bits/stdc++.h>
using namespace std;

int N, D[10003];
pair<int, int> A[10005];

int main() {
	scanf("%d", &N);
	for(int i=1; i<=N; i++) scanf("%d %d", &A[i].first, &A[i].second);
	sort(A+1, A+N+1);
	for(int i=1; i<=N; i++) {
		int u = abs(A[i].second) * 2;
		D[i] = 2e9;
		for(int j=i; j>0; j--) {
			u = max(u, abs(A[j].second) * 2);
			D[i] = min(D[i], D[j-1] + max(u, A[i].first - A[j].first));
		}
	}
	printf("%d", D[N]);
}