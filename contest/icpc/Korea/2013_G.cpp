#include <stdio.h>

long long DT[103] = {0, 1, 1, 1, 2, 2, 3, 4};
int t, n;

long long f(int x) {
	if(DT[x]) return DT[x];
	return DT[x] = f(x - 1) + f(x - 5);
}

int main() {
	scanf("%d", &n);
	for(int i=0; i<n; i++) {
		scanf("%d", &t);
		printf("%lld\n", f(t));
	}
}