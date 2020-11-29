#include <stdio.h>
#include <algorithm>
using namespace std;

int sum[10005], a[10005], n, k, i;

int main() {
    scanf("%d", &n);
    for(i=0; i<n; i++) scanf("%d", a+i);
    sort(a, a+n);
    scanf("%d", &k);
    for(i=1; i<=n; i++) sum[i] = a[i-1] + sum[i-1];
    for(i=0; i<n; i++) if(a[i] > (k - sum[i]) / (n - i)) {
		printf("%d", (k - sum[i]) / (n - i));
    	return 0;
	}
    printf("%d", a[n-1]);
}