#include <stdio.h>

int n, k, a, b, p;

int main() {
    scanf("%d %d", &p, &k);
    for(int i=0; i<k; i++) {
        n = p;
        scanf("%d %d", &a, &b);
        if(a >= b){
            a -= b;
            n -= b;
            b = 0;
            if(a <= n / 2 + 1) printf("1\n");
            else printf("0\n");
        } else {
            b -= a;
            n -= a;
            a = 0;
            if(b <= (n + 1) / 2) printf("1\n");
            else printf("0\n");
		}
    }
}