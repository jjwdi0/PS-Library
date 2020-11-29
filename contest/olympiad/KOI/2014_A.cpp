#include <bits/stdc++.h>
using namespace std;

int a, b, gcd1, cnt, det[2005][2005];

int gcd(int x, int y) {
    if(y % x == 0) return x;
    return gcd(y % x, x);
}

int main() {
    scanf("%d %d", &a, &b);
    for(int i=a; i<=b; i++) for(int j=1; j<=i; j++) {
		gcd1 = gcd(j, i);
    	det[j/gcd1][i/gcd1]++;
	}
    for(int i=0; i<=b; i++) for(int j=0; j<=b; j++) if(det[i][j]) cnt++;
    printf("%d\n", cnt);
}