#include <bits/stdc++.h>
using namespace std;

bool chk[100005];
int N;

int main() {
    scanf("%d", &N);
    int p = N, _N = 0;
    while(p) {
        _N += (p % 10) * (p % 10);
        p /= 10;
    }
    N = _N;
    while(!chk[N]) {
        if(N < 100000) chk[N] = 1;
        if(N == 1) break;
        int i = N, cnt = 0;
        while(i) {
            cnt += (i % 10) * (i % 10);
            i /= 10;
        }
        N = cnt;
    }
    puts(N == 1 ? "HAPPY" : "UNHAPPY");
}
