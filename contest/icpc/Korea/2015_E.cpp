#include <bits/stdc++.h>
using namespace std;

int T, N, A[10005];

int main() {
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &N);
        for(int i=0; i<N; i++) scanf("%d", A + i);
        sort(A, A + N);
        int ans = 0;
        for(int i=2; i<N; i+=2) ans = max(ans, A[i] - A[i-2]);
        ans = max(ans, A[N-1] - A[N-2]);
        for(int i=3; i<N; i+=2) ans = max(ans, A[i] - A[i-2]);
        ans = max(ans, A[1] - A[0]);
        printf("%d\n", ans);
    }
}
