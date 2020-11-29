#include <stdio.h>

int test, n, a[1003], visited[1003];

int main() {
	scanf("%d", &test);
	while(test--) {
		int cnt = 0;
		scanf("%d", &n);
		for(int i=1; i<=n; visited[i]=0,i++) {
			scanf("%d", a+i);
		}
		for(int i=1; i<=n; i++) {
			if(!visited[i]) {
				int temp = i;
				while(!visited[temp]) {
					visited[temp] = 1;
					temp = a[temp];
				}
				cnt++;
			}
		}
		printf("%d\n", cnt);
	}
}