#include <bits/stdc++.h>
using namespace std;

int N, H, D[1048577], A[22], B[22], C[22];
int ans = -1;

int f(int x) {
    if(~D[x]) return D[x];
    if(x == 0) return D[x] = 0;
    D[x] = 0;
    if(__builtin_popcount(x) == 1) {
        for(int i=0; i<N; i++) if(x & (1 << i)) return D[x] = C[i];
    }
    for(int i=0; i<N; i++) {
        if(x & (1 << i)) {
            if(f(x - (1 << i)) < B[i]) continue;
            D[x] = max(D[x], min(f(x - (1 << i)) - B[i], C[i]));
        }
    }
    return D[x];
}

int main() {
    scanf("%d %d", &N, &H);
    for(int i=0; i<N; i++) scanf("%d %d %d", A+i, B+i, C+i);
    for(int i=0; i<1<<N; i++) D[i] = -1;
    D[(1<<N)-1] = f((1 << N) - 1);
    for(int i=0; i<1<<N; i++) {
        int cnt = 0;
        for(int j=0; j<N; j++) if(i & (1 << j)) cnt += A[j];
        if(cnt < H) continue;
        ans = max(ans, D[i]);
    }
    if(ans <= 0) puts("Mark is too tall");
    else printf("%d\n", ans);
}
