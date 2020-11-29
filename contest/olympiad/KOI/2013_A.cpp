#include <stdio.h>
#include <algorithm>
using namespace std;

int M, N, K, A[100005];
int cnt;

int main() {
    scanf("%d %d %d", &M, &N, &K);
    for(int i=1; i<=M; i++) scanf("%d", A+i);
    sort(A+1, A+M+1);
    for(int i=1, x, y; i<=N; i++) {
        scanf("%d %d", &x, &y);
        if(K < y) continue;
        int hi = x - y + K, lo = x + y - K;
        cnt += !!(int)(upper_bound(A+1, A+M+1, hi) - lower_bound(A+1, A+M+1, lo));
    }
    printf("%d\n", cnt);
}
