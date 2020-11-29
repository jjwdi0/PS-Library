#include <stdio.h>

int test, n, m, a[103][103];

int main() {
	scanf("%d", &test);
	while(test--) {
		scanf("%d %d", &n, &m);
		int ans = 0;
		for(int i=0; i<n; i++) {
			for(int j=0; j<m; j++) {
				scanf("%d", &a[i][j]);
			}
		}
		for(int i=0; i<m; i++) {
			int cnt1 = 0, cnt2 = 0;
			for(int j=0; j<n; j++) {
				if(a[j][i]) {
					cnt1++; cnt2 += n - j;
				}
			}
			cnt1 = cnt1 * (cnt1 + 1) / 2;
			ans += cnt2 - cnt1;
		}
		printf("%d\n", ans);
	}
}