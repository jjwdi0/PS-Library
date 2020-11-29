#include <stdio.h>

int test, n, a[50], num[1005], k;

int main() {
	for(int i=1; i<=50; i++) {
		if(i * (i + 1) / 2 > 1000) { k = i; break; }
		a[i] = i * (i + 1) / 2;
	}
	for(int i=1; i<k; i++) {
		for(int j=1; j<k; j++) {
			for(int p=1; p<k; p++) {
				if(a[i] + a[j] + a[p] > 1000) continue;
				num[a[i]+a[j]+a[p]] = 1;
			}
		}
	}
	for(scanf("%d", &test); test--;) {
		scanf("%d", &n);
		printf("%d\n", num[n]);
	}
}