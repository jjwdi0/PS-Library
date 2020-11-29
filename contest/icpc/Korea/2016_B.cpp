#include <bits/stdc++.h>
using namespace std;

int N, A[11111];

int main() {
	scanf("%d", &N);
	for(int i=0; i<N; i++) scanf("%d", A+i);
	sort(A, A + N);
	int sum = 0;
	for(int i=0; i<N; i++) {
		sum += A[i];
		if(sum < i * (i + 1) / 2) return puts("-1"),0;
	}
	puts(sum == N * (N - 1) / 2 ? "1" : "-1");
}