#include <stdio.h>

int n, a[20005], chk[20005], k, b[20005];
int key;

void f(int x, int cnt) {
    if(chk[a[x]]) { b[k++] = cnt; return; }
    chk[x] = 1;
    f(a[x], cnt + 1);
}

int gcd(int x, int y) {
    if(y == 0) return x;
    return gcd(y, x % y);
}

int main() {
    scanf("%d", &n);
    for(int i=0; i<n; i++) scanf("%d", a+i+1);
    for(int i=1; i<=n; i++) {
        if(chk[i]) continue;
        chk[i] = 1;
        f(i, 1);
    }
    key = b[0];
    for(int i=1; i<k; i++) {
        key = key / gcd(key, b[i]) * b[i];
    }
    printf("%d", key);
}