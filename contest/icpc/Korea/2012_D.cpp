#include <bits/stdc++.h>
using namespace std;

int T, X, Y;

pair<int, int> f(int x) {
    int cnt = 0;
    for(int i=0; i<=x; i++) {
        cnt += i;
        if(cnt < x && x <= cnt + i + 1) return pair<int, int>(x - cnt, i + 2 - x + cnt);
    }
}

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d %d", &X, &Y);
        int X1 = f(X).first, X2 = f(Y).first;
        int Y1 = f(X).second, Y2 = f(Y).second;
        printf("%d\n", (X1 + X2 + Y1 + Y2 - 1) * (X1 + X2 + Y1 + Y2 - 2) / 2 + (X1 + X2));
    }
}
