#include <stdio.h>
#include <math.h>

int a, b, k;

int gcd(int x, int y) {
	if(y % x == 0)
	return x;
	return gcd(y % x, x);
}

int main() {
	scanf("%d %d", &a, &b);
	if(b==0) {
		printf("0 %d", a); return 0;
	}
	k = (int)(sqrt(a) * sqrt(b));
	for(int i=k; i>0; i--) if(b % i == 0) {
		if(gcd(i, b / i * a) == a) {
			printf("%d %d", i, b / i * a);
			return 0;
		}
	}
}