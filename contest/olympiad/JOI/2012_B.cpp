#include <stdio.h>

int N, M, A[5555], B[5555];

bool chk(int x) {
	for(int i=0; i<=M-x; i++) {
		int j = 0, k = i;
		while(j < N && k < i + x) if(A[j++] == B[k]) k++;
		if(k == i + x) return true;
	}
	return false;
}

int main() {
	scanf("%d %d", &N, &M);
	for(int i=0; i<N; i++) scanf("%d", A+i);
	for(int i=0; i<M; i++) scanf("%d", B+i);
	int lo = 0, hi = N;
	while(lo <= hi) {
		int mid = lo + hi >> 1;
		if(chk(mid)) lo = mid + 1;
		else hi = mid - 1;
	}
	printf("%d", lo - 1);
}